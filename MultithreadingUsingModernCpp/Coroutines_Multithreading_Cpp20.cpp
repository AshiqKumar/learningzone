// C++20 Coroutines with Multithreading Integration
// Compile: g++ -std=c++20 -fcoroutines -pthread -o coroutines_multithread coroutines_multithread.cpp
// Run: ./coroutines_multithread

#include <iostream>
#include <coroutine>
#include <thread>
#include <vector>
#include <future>
#include <chrono>
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <optional>
#include <functional>

// 1. Basic coroutine task implementation
template<typename T>
struct Task {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    
    struct promise_type {
        T result_;
        std::exception_ptr exception_;
        
        Task get_return_object() {
            return Task(handle_type::from_promise(*this));
        }
        
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        void return_value(T value) {
            result_ = std::move(value);
        }
        
        void unhandled_exception() {
            exception_ = std::current_exception();
        }
    };
    
    explicit Task(handle_type h) : handle_(h) {}
    
    ~Task() {
        if (handle_) {
            handle_.destroy();
        }
    }
    
    // Move-only type
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    
    Task(Task&& other) noexcept : handle_(other.handle_) {
        other.handle_ = {};
    }
    
    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            if (handle_) {
                handle_.destroy();
            }
            handle_ = other.handle_;
            other.handle_ = {};
        }
        return *this;
    }
    
    T get() {
        if (!handle_) {
            throw std::runtime_error("Task is empty");
        }
        
        if (handle_.promise().exception_) {
            std::rethrow_exception(handle_.promise().exception_);
        }
        
        return handle_.promise().result_;
    }
    
    bool done() const {
        return handle_ && handle_.done();
    }
    
private:
    handle_type handle_;
};

// 2. Generator coroutine for lazy evaluation
template<typename T>
struct Generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    
    struct promise_type {
        T current_value_;
        
        Generator get_return_object() {
            return Generator(handle_type::from_promise(*this));
        }
        
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        std::suspend_always yield_value(T value) {
            current_value_ = std::move(value);
            return {};
        }
        
        void return_void() {}
        void unhandled_exception() {}
    };
    
    explicit Generator(handle_type h) : handle_(h) {}
    
    ~Generator() {
        if (handle_) {
            handle_.destroy();
        }
    }
    
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    
    Generator(Generator&& other) noexcept : handle_(other.handle_) {
        other.handle_ = {};
    }
    
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (handle_) {
                handle_.destroy();
            }
            handle_ = other.handle_;
            other.handle_ = {};
        }
        return *this;
    }
    
    struct iterator {
        handle_type handle_;
        
        iterator(handle_type h) : handle_(h) {}
        
        iterator& operator++() {
            handle_.resume();
            return *this;
        }
        
        const T& operator*() const {
            return handle_.promise().current_value_;
        }
        
        bool operator!=(const iterator& other) const {
            return handle_ != other.handle_ || !handle_.done();
        }
    };
    
    iterator begin() {
        if (handle_) {
            handle_.resume();
        }
        return iterator(handle_);
    }
    
    iterator end() {
        return iterator(nullptr);
    }
    
private:
    handle_type handle_;
};

// 3. Async Task with thread pool integration
class AsyncTaskScheduler {
private:
    std::vector<std::jthread> workers_;
    std::queue<std::coroutine_handle<>> ready_queue_;
    std::mutex queue_mutex_;
    std::condition_variable_any queue_cv_;
    std::atomic<bool> stopping_{false};
    
public:
    explicit AsyncTaskScheduler(size_t num_threads = std::thread::hardware_concurrency()) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers_.emplace_back([this](std::stop_token stoken) {
                worker_loop(stoken);
            });
        }
        std::cout << "AsyncTaskScheduler created with " << num_threads << " threads" << std::endl;
    }
    
    ~AsyncTaskScheduler() {
        stopping_ = true;
        queue_cv_.notify_all();
        
        for (auto& worker : workers_) {
            worker.request_stop();
        }
    }
    
    void schedule(std::coroutine_handle<> handle) {
        {
            std::lock_guard lock(queue_mutex_);
            ready_queue_.push(handle);
        }
        queue_cv_.notify_one();
    }
    
private:
    void worker_loop(std::stop_token stoken) {
        while (!stoken.stop_requested()) {
            std::coroutine_handle<> handle;
            
            {
                std::unique_lock lock(queue_mutex_);
                queue_cv_.wait(lock, stoken, [this]() {
                    return !ready_queue_.empty() || stopping_.load();
                });
                
                if (stoken.stop_requested() || stopping_.load()) {
                    break;
                }
                
                if (!ready_queue_.empty()) {
                    handle = ready_queue_.front();
                    ready_queue_.pop();
                }
            }
            
            if (handle) {
                try {
                    handle.resume();
                } catch (const std::exception& e) {
                    std::cerr << "Coroutine exception: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Unknown coroutine exception" << std::endl;
                }
            }
        }
    }
};

// Global scheduler instance
inline AsyncTaskScheduler& get_scheduler() {
    static AsyncTaskScheduler scheduler(4);
    return scheduler;
}

// 4. Awaitable for thread switching
struct switch_to_background {
    bool await_ready() const noexcept { return false; }
    
    void await_suspend(std::coroutine_handle<> handle) const {
        get_scheduler().schedule(handle);
    }
    
    void await_resume() const noexcept {}
};

// 5. Awaitable for delays
struct delay_awaitable {
    std::chrono::milliseconds duration;
    
    explicit delay_awaitable(std::chrono::milliseconds d) : duration(d) {}
    
    bool await_ready() const noexcept { return false; }
    
    void await_suspend(std::coroutine_handle<> handle) const {
        // Schedule resumption after delay
        std::jthread([handle, duration = this->duration]() {
            std::this_thread::sleep_for(duration);
            get_scheduler().schedule(handle);
        }).detach();
    }
    
    void await_resume() const noexcept {}
};

delay_awaitable delay(std::chrono::milliseconds ms) {
    return delay_awaitable(ms);
}

// 6. Demonstration functions
Task<int> simple_coroutine_task(int input) {
    std::cout << "Coroutine starting with input: " << input 
              << " on thread: " << std::this_thread::get_id() << std::endl;
    
    // Switch to background thread
    co_await switch_to_background{};
    
    std::cout << "Coroutine continuing on thread: " << std::this_thread::get_id() << std::endl;
    
    // Simulate work with delay
    co_await delay(std::chrono::milliseconds(100));
    
    int result = input * input;
    std::cout << "Coroutine computed result: " << result 
              << " on thread: " << std::this_thread::get_id() << std::endl;
    
    co_return result;
}

Generator<int> fibonacci_generator(int count) {
    int a = 0, b = 1;
    
    for (int i = 0; i < count; ++i) {
        co_yield a;
        
        int next = a + b;
        a = b;
        b = next;
        
        // Yield control to allow other work
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

Task<std::string> network_simulation(const std::string& url) {
    std::cout << "Starting network request to: " << url 
              << " on thread: " << std::this_thread::get_id() << std::endl;
    
    // Switch to background for I/O
    co_await switch_to_background{};
    
    // Simulate network delay
    co_await delay(std::chrono::milliseconds(200 + (url.length() % 300)));
    
    std::string response = "Response from " + url;
    std::cout << "Network request completed: " << response 
              << " on thread: " << std::this_thread::get_id() << std::endl;
    
    co_return response;
}

Task<int> parallel_computation(int start, int end) {
    std::cout << "Starting parallel computation [" << start << ", " << end << "] "
              << "on thread: " << std::this_thread::get_id() << std::endl;
    
    // Switch to background thread for computation
    co_await switch_to_background{};
    
    int sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += i;
        
        // Occasionally yield to prevent blocking
        if (i % 1000 == 0) {
            co_await delay(std::chrono::milliseconds(1));
        }
    }
    
    std::cout << "Parallel computation [" << start << ", " << end << "] = " << sum
              << " on thread: " << std::this_thread::get_id() << std::endl;
    
    co_return sum;
}

void demonstrate_basic_coroutines() {
    std::cout << "\n=== 1. Basic Coroutines ===" << std::endl;
    
    std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;
    
    // Create and run simple coroutine tasks
    auto task1 = simple_coroutine_task(5);
    auto task2 = simple_coroutine_task(10);
    auto task3 = simple_coroutine_task(15);
    
    // Wait for completion (busy wait for demonstration)
    while (!task1.done() || !task2.done() || !task3.done()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    std::cout << "Task results: " << task1.get() << ", " 
              << task2.get() << ", " << task3.get() << std::endl;
}

void demonstrate_generator_coroutines() {
    std::cout << "\n=== 2. Generator Coroutines ===" << std::endl;
    
    auto fib_gen = fibonacci_generator(10);
    
    std::cout << "Fibonacci sequence (lazy evaluation): ";
    for (int value : fib_gen) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

void demonstrate_async_coroutines() {
    std::cout << "\n=== 3. Async Coroutines ===" << std::endl;
    
    std::vector<Task<std::string>> network_tasks;
    
    // Start multiple concurrent network requests
    std::vector<std::string> urls = {
        "https://api1.example.com",
        "https://api2.example.com",
        "https://api3.example.com",
        "https://database.internal.com",
        "https://cache.service.com"
    };
    
    for (const auto& url : urls) {
        network_tasks.push_back(network_simulation(url));
    }
    
    // Wait for all to complete
    bool all_done = false;
    while (!all_done) {
        all_done = true;
        for (const auto& task : network_tasks) {
            if (!task.done()) {
                all_done = false;
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    
    // Collect results
    std::cout << "Network responses:" << std::endl;
    for (auto& task : network_tasks) {
        std::cout << "  " << task.get() << std::endl;
    }
}

void demonstrate_parallel_coroutines() {
    std::cout << "\n=== 4. Parallel Computation with Coroutines ===" << std::endl;
    
    constexpr int TOTAL_RANGE = 100000;
    constexpr int NUM_CHUNKS = 4;
    constexpr int CHUNK_SIZE = TOTAL_RANGE / NUM_CHUNKS;
    
    std::vector<Task<int>> computation_tasks;
    
    // Start parallel computations
    for (int chunk = 0; chunk < NUM_CHUNKS; ++chunk) {
        int start = chunk * CHUNK_SIZE + 1;
        int end = (chunk == NUM_CHUNKS - 1) ? TOTAL_RANGE : (chunk + 1) * CHUNK_SIZE;
        
        computation_tasks.push_back(parallel_computation(start, end));
    }
    
    // Wait for completion
    bool all_done = false;
    while (!all_done) {
        all_done = true;
        for (const auto& task : computation_tasks) {
            if (!task.done()) {
                all_done = false;
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    // Aggregate results
    int total_sum = 0;
    for (auto& task : computation_tasks) {
        total_sum += task.get();
    }
    
    std::cout << "Total sum of 1 to " << TOTAL_RANGE << " = " << total_sum << std::endl;
    
    // Verify with formula: sum = n * (n + 1) / 2
    long long expected = static_cast<long long>(TOTAL_RANGE) * (TOTAL_RANGE + 1) / 2;
    std::cout << "Expected: " << expected << ", Match: " << (total_sum == expected ? "Yes" : "No") << std::endl;
}

void demonstrate_producer_consumer_coroutines() {
    std::cout << "\n=== 5. Producer-Consumer with Coroutines ===" << std::endl;
    
    std::queue<int> shared_buffer;
    std::mutex buffer_mutex;
    std::condition_variable buffer_cv;
    std::atomic<bool> production_done{false};
    std::atomic<int> items_produced{0};
    std::atomic<int> items_consumed{0};
    
    auto producer_coroutine = [&](int producer_id) -> Task<void> {
        co_await switch_to_background{};
        
        for (int i = 0; i < 10; ++i) {
            int item = producer_id * 100 + i;
            
            {
                std::lock_guard lock(buffer_mutex);
                shared_buffer.push(item);
                items_produced++;
                std::cout << "Producer " << producer_id << " produced: " << item << std::endl;
            }
            
            buffer_cv.notify_one();
            co_await delay(std::chrono::milliseconds(50));
        }
        
        std::cout << "Producer " << producer_id << " finished" << std::endl;
        co_return;
    };
    
    auto consumer_coroutine = [&](int consumer_id) -> Task<void> {
        co_await switch_to_background{};
        
        while (!production_done.load() || !shared_buffer.empty()) {
            std::unique_lock lock(buffer_mutex);
            
            if (shared_buffer.empty()) {
                lock.unlock();
                co_await delay(std::chrono::milliseconds(10));
                continue;
            }
            
            int item = shared_buffer.front();
            shared_buffer.pop();
            items_consumed++;
            
            lock.unlock();
            
            std::cout << "Consumer " << consumer_id << " consumed: " << item << std::endl;
            co_await delay(std::chrono::milliseconds(30));
        }
        
        std::cout << "Consumer " << consumer_id << " finished" << std::endl;
        co_return;
    };
    
    // Start producers and consumers
    std::vector<Task<void>> tasks;
    
    // 2 producers
    tasks.push_back(producer_coroutine(1));
    tasks.push_back(producer_coroutine(2));
    
    // 3 consumers
    tasks.push_back(consumer_coroutine(1));
    tasks.push_back(consumer_coroutine(2));
    tasks.push_back(consumer_coroutine(3));
    
    // Wait a bit then signal production done
    std::jthread production_monitor([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        production_done = true;
        buffer_cv.notify_all();
    });
    
    // Wait for all tasks to complete
    bool all_done = false;
    while (!all_done) {
        all_done = true;
        for (const auto& task : tasks) {
            if (!task.done()) {
                all_done = false;
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    std::cout << "Production/Consumption complete. Produced: " << items_produced.load() 
              << ", Consumed: " << items_consumed.load() << std::endl;
}

int main() {
    std::cout << "=== C++20 Coroutines with Multithreading ===" << std::endl;
    
    try {
        demonstrate_basic_coroutines();
        demonstrate_generator_coroutines();
        demonstrate_async_coroutines();
        demonstrate_parallel_coroutines();
        demonstrate_producer_consumer_coroutines();
        
        // Give background tasks time to complete
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Coroutine Benefits with Multithreading ===" << std::endl;
    std::cout << "✅ Async/await syntax for readable async code" << std::endl;
    std::cout << "✅ Cooperative multitasking with threads" << std::endl;
    std::cout << "✅ Efficient context switching" << std::endl;
    std::cout << "✅ Natural expression of async workflows" << std::endl;
    std::cout << "✅ Composable async operations" << std::endl;
    std::cout << "✅ Reduced callback complexity" << std::endl;
    std::cout << "✅ Memory efficient (stackless)" << std::endl;
    
    std::cout << "\n=== Use Cases ===" << std::endl;
    std::cout << "• Async I/O operations (network, file)" << std::endl;
    std::cout << "• Event-driven programming" << std::endl;
    std::cout << "• Producer-consumer patterns" << std::endl;
    std::cout << "• Lazy evaluation and generators" << std::endl;
    std::cout << "• State machine implementations" << std::endl;
    std::cout << "• Pipeline processing" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++20 -fcoroutines -pthread -Wall -Wextra -O2 -o coroutines_multithread coroutines_multithread.cpp
./coroutines_multithread

Key Concepts:

C++20 Coroutines:
- co_await: Suspend execution until awaited operation completes
- co_yield: Produce a value and suspend (generators)
- co_return: Return a value and complete coroutine
- promise_type: Defines coroutine behavior and storage

Coroutine Integration with Threads:
- Coroutines can be scheduled across thread pools
- Async operations can switch between threads
- Cooperative multitasking within preemptive threading
- Efficient context switching (no stack copying)

Benefits:

Readability:
- Linear code flow despite async operations
- No callback hell or complex state machines
- Natural error handling with exceptions
- Composable async operations

Performance:
- Stackless coroutines (minimal memory overhead)
- Efficient suspend/resume operations
- Reduced thread context switching
- Better CPU cache utilization

Flexibility:
- Can integrate with any threading model
- Custom awaitables for domain-specific operations
- Generators for lazy evaluation
- Task-based parallel programming

Patterns Demonstrated:

1. Task<T>: Async operations with return values
2. Generator<T>: Lazy sequence generation
3. Thread switching: Moving work between threads
4. Delayed operations: Time-based suspension
5. Parallel computation: Concurrent coroutines
6. Producer-consumer: Coordinated async workflows

Real-world Applications:
- Web servers (async request handling)
- Network clients (concurrent connections)
- File I/O operations (async read/write)
- Database access (connection pooling)
- Event processing systems
- Game engines (frame-based updates)
- Real-time systems (responsive UIs)

Comparison with Traditional Threading:
- Less memory per "task" (no full stack)
- More predictable performance
- Easier debugging (linear control flow)
- Better error propagation
- Reduced synchronization complexity
*/
