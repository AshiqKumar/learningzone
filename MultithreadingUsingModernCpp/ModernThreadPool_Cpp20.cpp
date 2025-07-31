// Modern C++ Thread Pool Implementation with C++20/23 Features
// Compile: g++ -std=c++20 -pthread -o thread_pool_modern thread_pool_modern.cpp
// Run: ./thread_pool_modern

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <future>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <memory>
#include <type_traits>
#include <semaphore>
#include <latch>
#include <barrier>
#include <stop_token>

// 1. Modern Thread Pool with C++20 features
class ModernThreadPool {
private:
    std::vector<std::jthread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex queue_mutex_;
    std::condition_variable_any condition_;
    std::stop_source stop_source_;
    std::atomic<size_t> active_tasks_{0};
    std::atomic<size_t> completed_tasks_{0};
    
public:
    explicit ModernThreadPool(size_t num_threads = std::thread::hardware_concurrency())
        : workers_() {
        
        workers_.reserve(num_threads);
        
        for (size_t i = 0; i < num_threads; ++i) {
            workers_.emplace_back([this](std::stop_token stoken) {
                worker_loop(stoken);
            });
        }
        
        std::cout << "ModernThreadPool created with " << num_threads << " threads" << std::endl;
    }
    
    ~ModernThreadPool() {
        // Request stop for all worker threads
        for (auto& worker : workers_) {
            worker.request_stop();
        }
        
        // Wake up all waiting workers
        condition_.notify_all();
        
        // jthread automatically joins in destructor
        std::cout << "ModernThreadPool destroyed. Completed " << completed_tasks_.load() << " tasks." << std::endl;
    }
    
    // Submit a task and return a future
    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
        using return_type = std::invoke_result_t<F, Args...>;
        
        // Create a packaged_task for the function call
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> result = task->get_future();
        
        {
            std::unique_lock lock(queue_mutex_);
            
            // Don't accept new tasks if stopping
            if (stop_source_.stop_requested()) {
                throw std::runtime_error("ThreadPool is shutting down");
            }
            
            tasks_.emplace([task]() {
                (*task)();
            });
        }
        
        condition_.notify_one();
        return result;
    }
    
    // Get number of active tasks
    size_t active_tasks() const {
        return active_tasks_.load();
    }
    
    // Get number of completed tasks
    size_t completed_tasks() const {
        return completed_tasks_.load();
    }
    
    // Get number of pending tasks
    size_t pending_tasks() const {
        std::unique_lock lock(queue_mutex_);
        return tasks_.size();
    }
    
    // Wait for all current tasks to complete
    void wait_for_completion() {
        std::unique_lock lock(queue_mutex_);
        condition_.wait(lock, [this]() {
            return tasks_.empty() && active_tasks_.load() == 0;
        });
    }
    
private:
    void worker_loop(std::stop_token stoken) {
        while (!stoken.stop_requested()) {
            std::function<void()> task;
            
            {
                std::unique_lock lock(queue_mutex_);
                
                // Wait for task or stop request
                condition_.wait(lock, stoken, [this]() {
                    return !tasks_.empty();
                });
                
                if (stoken.stop_requested()) {
                    break;
                }
                
                if (!tasks_.empty()) {
                    task = std::move(tasks_.front());
                    tasks_.pop();
                    ++active_tasks_;
                }
            }
            
            if (task) {
                try {
                    task();
                } catch (const std::exception& e) {
                    std::cerr << "Task threw exception: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Task threw unknown exception" << std::endl;
                }
                
                --active_tasks_;
                ++completed_tasks_;
                condition_.notify_all(); // Notify wait_for_completion
            }
        }
    }
};

// 2. Priority Thread Pool with semaphore-based resource management
class PriorityThreadPool {
public:
    enum class Priority { LOW = 0, NORMAL = 1, HIGH = 2 };
    
private:
    struct Task {
        std::function<void()> function;
        Priority priority;
        std::chrono::steady_clock::time_point submission_time;
        
        bool operator<(const Task& other) const {
            // Higher priority first, then earlier submission time
            if (priority != other.priority) {
                return priority < other.priority; // Note: reversed for priority_queue
            }
            return submission_time > other.submission_time;
        }
    };
    
    std::vector<std::jthread> workers_;
    std::priority_queue<Task> tasks_;
    std::mutex queue_mutex_;
    std::condition_variable_any condition_;
    std::counting_semaphore<1000> task_semaphore_;
    std::atomic<bool> stopping_{false};
    std::atomic<size_t> completed_tasks_{0};
    
public:
    explicit PriorityThreadPool(size_t num_threads = std::thread::hardware_concurrency())
        : task_semaphore_(0) {
        
        for (size_t i = 0; i < num_threads; ++i) {
            workers_.emplace_back([this](std::stop_token stoken) {
                worker_loop(stoken);
            });
        }
        
        std::cout << "PriorityThreadPool created with " << num_threads << " threads" << std::endl;
    }
    
    ~PriorityThreadPool() {
        stopping_ = true;
        
        // Wake up all workers
        for (size_t i = 0; i < workers_.size(); ++i) {
            task_semaphore_.release();
        }
        
        for (auto& worker : workers_) {
            worker.request_stop();
        }
        
        condition_.notify_all();
    }
    
    template<typename F, typename... Args>
    auto submit(Priority priority, F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
        using return_type = std::invoke_result_t<F, Args...>;
        
        auto task_ptr = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> result = task_ptr->get_future();
        
        {
            std::lock_guard lock(queue_mutex_);
            tasks_.emplace(Task{
                [task_ptr]() { (*task_ptr)(); },
                priority,
                std::chrono::steady_clock::now()
            });
        }
        
        task_semaphore_.release();
        return result;
    }
    
    size_t completed_tasks() const {
        return completed_tasks_.load();
    }
    
private:
    void worker_loop(std::stop_token stoken) {
        while (!stoken.stop_requested()) {
            // Wait for a task to be available
            if (!task_semaphore_.try_acquire()) {
                if (stopping_.load()) break;
                task_semaphore_.acquire();
            }
            
            if (stopping_.load() && stoken.stop_requested()) break;
            
            std::function<void()> task_func;
            
            {
                std::lock_guard lock(queue_mutex_);
                if (!tasks_.empty()) {
                    task_func = std::move(tasks_.top().function);
                    tasks_.pop();
                }
            }
            
            if (task_func) {
                try {
                    task_func();
                    ++completed_tasks_;
                } catch (const std::exception& e) {
                    std::cerr << "Priority task exception: " << e.what() << std::endl;
                }
            }
        }
    }
};

// 3. Work-Stealing Thread Pool (advanced concept)
class WorkStealingThreadPool {
private:
    struct WorkerData {
        std::queue<std::function<void()>> local_queue;
        std::mutex local_mutex;
        std::atomic<size_t> work_count{0};
    };
    
    std::vector<std::jthread> workers_;
    std::vector<std::unique_ptr<WorkerData>> worker_data_;
    std::atomic<bool> stopping_{false};
    std::atomic<size_t> global_work_count_{0};
    std::condition_variable_any work_available_;
    std::mutex global_mutex_;
    
public:
    explicit WorkStealingThreadPool(size_t num_threads = std::thread::hardware_concurrency()) {
        worker_data_.reserve(num_threads);
        workers_.reserve(num_threads);
        
        for (size_t i = 0; i < num_threads; ++i) {
            worker_data_.emplace_back(std::make_unique<WorkerData>());
            workers_.emplace_back([this, i](std::stop_token stoken) {
                worker_loop(i, stoken);
            });
        }
        
        std::cout << "WorkStealingThreadPool created with " << num_threads << " threads" << std::endl;
    }
    
    ~WorkStealingThreadPool() {
        stopping_ = true;
        work_available_.notify_all();
        
        for (auto& worker : workers_) {
            worker.request_stop();
        }
    }
    
    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
        using return_type = std::invoke_result_t<F, Args...>;
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> result = task->get_future();
        
        // Find worker with least work
        size_t best_worker = 0;
        size_t min_work = worker_data_[0]->work_count.load();
        
        for (size_t i = 1; i < worker_data_.size(); ++i) {
            size_t work = worker_data_[i]->work_count.load();
            if (work < min_work) {
                min_work = work;
                best_worker = i;
            }
        }
        
        {
            std::lock_guard lock(worker_data_[best_worker]->local_mutex);
            worker_data_[best_worker]->local_queue.emplace([task]() {
                (*task)();
            });
            ++worker_data_[best_worker]->work_count;
            ++global_work_count_;
        }
        
        work_available_.notify_one();
        return result;
    }
    
private:
    void worker_loop(size_t worker_id, std::stop_token stoken) {
        WorkerData& my_data = *worker_data_[worker_id];
        
        while (!stoken.stop_requested()) {
            std::function<void()> task;
            
            // Try to get work from local queue
            {
                std::lock_guard lock(my_data.local_mutex);
                if (!my_data.local_queue.empty()) {
                    task = std::move(my_data.local_queue.front());
                    my_data.local_queue.pop();
                    --my_data.work_count;
                    --global_work_count_;
                }
            }
            
            // If no local work, try to steal from other workers
            if (!task) {
                for (size_t i = 0; i < worker_data_.size(); ++i) {
                    if (i == worker_id) continue;
                    
                    WorkerData& other_data = *worker_data_[i];
                    std::lock_guard lock(other_data.local_mutex);
                    
                    if (!other_data.local_queue.empty()) {
                        task = std::move(other_data.local_queue.front());
                        other_data.local_queue.pop();
                        --other_data.work_count;
                        --global_work_count_;
                        break;
                    }
                }
            }
            
            if (task) {
                try {
                    task();
                } catch (const std::exception& e) {
                    std::cerr << "Work stealing task exception: " << e.what() << std::endl;
                }
            } else {
                // No work found, wait for notification
                std::unique_lock lock(global_mutex_);
                work_available_.wait_for(lock, stoken, std::chrono::milliseconds(10), [this]() {
                    return global_work_count_.load() > 0;
                });
            }
        }
    }
};

// 4. Demonstration functions
void demonstrate_basic_thread_pool() {
    std::cout << "\n=== 1. Basic Modern Thread Pool ===" << std::endl;
    
    ModernThreadPool pool(4);
    
    // Submit various tasks
    std::vector<std::future<int>> results;
    
    for (int i = 0; i < 10; ++i) {
        results.push_back(pool.submit([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Task " << i << " completed by thread " 
                      << std::this_thread::get_id() << std::endl;
            return i * i;
        }));
    }
    
    // Collect results
    for (size_t i = 0; i < results.size(); ++i) {
        int result = results[i].get();
        std::cout << "Result " << i << ": " << result << std::endl;
    }
    
    std::cout << "Pool statistics - Completed: " << pool.completed_tasks() 
              << ", Active: " << pool.active_tasks() 
              << ", Pending: " << pool.pending_tasks() << std::endl;
}

void demonstrate_priority_thread_pool() {
    std::cout << "\n=== 2. Priority Thread Pool ===" << std::endl;
    
    PriorityThreadPool pool(3);
    
    // Submit tasks with different priorities
    std::vector<std::future<std::string>> results;
    
    // Submit in mixed order
    results.push_back(pool.submit(PriorityThreadPool::Priority::LOW, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        return std::string("Low priority task");
    }));
    
    results.push_back(pool.submit(PriorityThreadPool::Priority::HIGH, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        return std::string("HIGH priority task");
    }));
    
    results.push_back(pool.submit(PriorityThreadPool::Priority::NORMAL, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        return std::string("Normal priority task");
    }));
    
    results.push_back(pool.submit(PriorityThreadPool::Priority::HIGH, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        return std::string("Another HIGH priority task");
    }));
    
    // Collect results (should show priority ordering)
    for (size_t i = 0; i < results.size(); ++i) {
        std::string result = results[i].get();
        std::cout << "Completed: " << result << std::endl;
    }
}

void demonstrate_work_stealing_pool() {
    std::cout << "\n=== 3. Work-Stealing Thread Pool ===" << std::endl;
    
    WorkStealingThreadPool pool(4);
    
    // Submit many small tasks to see work stealing in action
    std::vector<std::future<int>> results;
    
    for (int i = 0; i < 20; ++i) {
        results.push_back(pool.submit([i]() {
            // Simulate variable work
            std::this_thread::sleep_for(std::chrono::milliseconds(50 + (i % 3) * 50));
            std::cout << "Work-stealing task " << i << " on thread " 
                      << std::this_thread::get_id() << std::endl;
            return i;
        }));
    }
    
    // Wait for all tasks
    for (auto& future : results) {
        future.get();
    }
}

void demonstrate_thread_pool_patterns() {
    std::cout << "\n=== 4. Thread Pool Patterns ===" << std::endl;
    
    ModernThreadPool pool(3);
    
    // Pattern 1: Parallel map operation
    std::cout << "Pattern 1: Parallel Map" << std::endl;
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<std::future<int>> mapped_results;
    
    for (int value : data) {
        mapped_results.push_back(pool.submit([value]() {
            return value * value;
        }));
    }
    
    std::cout << "Squared values: ";
    for (auto& future : mapped_results) {
        std::cout << future.get() << " ";
    }
    std::cout << std::endl;
    
    // Pattern 2: Parallel reduction using latch
    std::cout << "\nPattern 2: Parallel Reduction" << std::endl;
    constexpr int NUM_CHUNKS = 4;
    std::latch reduction_latch(NUM_CHUNKS);
    std::vector<int> partial_sums(NUM_CHUNKS);
    
    std::vector<int> large_data(1000);
    std::iota(large_data.begin(), large_data.end(), 1);
    
    size_t chunk_size = large_data.size() / NUM_CHUNKS;
    
    for (int chunk = 0; chunk < NUM_CHUNKS; ++chunk) {
        pool.submit([&, chunk]() {
            size_t start = chunk * chunk_size;
            size_t end = (chunk == NUM_CHUNKS - 1) ? large_data.size() : (chunk + 1) * chunk_size;
            
            int sum = 0;
            for (size_t i = start; i < end; ++i) {
                sum += large_data[i];
            }
            
            partial_sums[chunk] = sum;
            std::cout << "Chunk " << chunk << " sum: " << sum << std::endl;
            reduction_latch.count_down();
        });
    }
    
    reduction_latch.wait();
    
    int total_sum = 0;
    for (int partial : partial_sums) {
        total_sum += partial;
    }
    
    std::cout << "Total sum: " << total_sum << std::endl;
    
    // Pattern 3: Producer-Consumer with barrier
    std::cout << "\nPattern 3: Producer-Consumer Batches" << std::endl;
    constexpr int NUM_BATCHES = 3;
    std::barrier batch_barrier(2); // Producer and consumer
    std::queue<int> shared_queue;
    std::mutex queue_mutex;
    
    // Producer
    auto producer_future = pool.submit([&]() {
        for (int batch = 0; batch < NUM_BATCHES; ++batch) {
            // Produce items
            {
                std::lock_guard lock(queue_mutex);
                for (int i = 0; i < 5; ++i) {
                    shared_queue.push(batch * 5 + i);
                }
                std::cout << "Produced batch " << batch << std::endl;
            }
            
            batch_barrier.arrive_and_wait(); // Wait for consumer
        }
    });
    
    // Consumer
    auto consumer_future = pool.submit([&]() {
        for (int batch = 0; batch < NUM_BATCHES; ++batch) {
            // Wait for producer
            batch_barrier.arrive_and_wait();
            
            // Consume items
            {
                std::lock_guard lock(queue_mutex);
                std::cout << "Consuming batch " << batch << ": ";
                while (!shared_queue.empty()) {
                    std::cout << shared_queue.front() << " ";
                    shared_queue.pop();
                }
                std::cout << std::endl;
            }
        }
    });
    
    producer_future.get();
    consumer_future.get();
}

int main() {
    std::cout << "=== Modern C++ Thread Pool Implementations ===" << std::endl;
    
    try {
        demonstrate_basic_thread_pool();
        demonstrate_priority_thread_pool();
        demonstrate_work_stealing_pool();
        demonstrate_thread_pool_patterns();
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Thread Pool Benefits ===" << std::endl;
    std::cout << "✅ Reduced thread creation/destruction overhead" << std::endl;
    std::cout << "✅ Controlled resource usage (bounded number of threads)" << std::endl;
    std::cout << "✅ Task queuing and load balancing" << std::endl;
    std::cout << "✅ Exception safety with futures" << std::endl;
    std::cout << "✅ Flexible task submission and result collection" << std::endl;
    std::cout << "✅ Modern C++20 features (jthread, stop_token, latch, barrier)" << std::endl;
    
    std::cout << "\n=== Design Patterns Demonstrated ===" << std::endl;
    std::cout << "• Basic Thread Pool: Simple task submission and execution" << std::endl;
    std::cout << "• Priority Pool: Task prioritization and ordered execution" << std::endl;
    std::cout << "• Work Stealing: Dynamic load balancing between threads" << std::endl;
    std::cout << "• Parallel Map: Data parallelism with result collection" << std::endl;
    std::cout << "• Parallel Reduction: Divide-and-conquer aggregation" << std::endl;
    std::cout << "• Producer-Consumer: Coordinated batch processing" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++20 -pthread -Wall -Wextra -O2 -o thread_pool_modern thread_pool_modern.cpp
./thread_pool_modern

Key Modern C++ Features Used:

C++20 Features:
- std::jthread: Automatic joining and stop token support
- std::stop_token: Cooperative cancellation
- std::latch: One-time synchronization
- std::barrier: Multi-phase synchronization
- std::counting_semaphore: Resource management

C++17/20 Features:
- std::invoke_result_t: Perfect return type deduction
- Perfect forwarding with variadic templates
- RAII resource management
- Exception safety guarantees

Thread Pool Patterns:

1. Basic Thread Pool:
   - Fixed number of worker threads
   - Task queue with mutex protection
   - Future-based result collection
   - Graceful shutdown with stop tokens

2. Priority Thread Pool:
   - Task prioritization with std::priority_queue
   - Semaphore-based task signaling
   - Time-based secondary ordering
   - Resource-aware task distribution

3. Work-Stealing Thread Pool:
   - Per-thread local queues
   - Work stealing from other threads when idle
   - Load balancing across workers
   - Reduced contention on shared data

Benefits:
- Thread reuse reduces creation overhead
- Bounded resource usage
- Task queuing handles load spikes
- Exception safety with futures
- Cooperative cancellation
- Modern synchronization primitives

Use Cases:
- CPU-intensive parallel tasks
- I/O-bound operations
- Background processing
- Web servers and network services
- Data processing pipelines
- Parallel algorithms implementation
*/
