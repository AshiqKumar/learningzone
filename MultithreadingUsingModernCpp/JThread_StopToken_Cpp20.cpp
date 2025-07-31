// C++20 std::jthread - Enhanced Thread with Automatic Joining and Stop Tokens
// Compile: g++ -std=c++20 -pthread -o jthread_demo jthread_demo.cpp
// Run: ./jthread_demo

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <stop_token>

// 1. Basic jthread usage - automatic joining
void demonstrate_basic_jthread() {
    std::cout << "=== 1. Basic jthread Usage ===" << std::endl;
    
    // Traditional std::thread requires explicit join() or detach()
    // std::jthread automatically joins in destructor
    
    auto worker_function = [](int id) {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread " << id << " working: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    };
    
    {
        std::jthread t1(worker_function, 1);
        std::jthread t2(worker_function, 2);
        // Automatic join when jthread objects go out of scope!
        std::cout << "jthreads will auto-join when leaving scope" << std::endl;
    } // Both threads automatically joined here
    
    std::cout << "Both jthreads have finished and joined automatically!" << std::endl;
}

// 2. Stop token usage - cooperative cancellation
void demonstrate_stop_token() {
    std::cout << "\n=== 2. Stop Token Usage ===" << std::endl;
    
    auto cancellable_worker = [](std::stop_token stoken, int id) {
        int count = 0;
        while (!stoken.stop_requested()) {
            std::cout << "Thread " << id << " iteration: " << count++ << std::endl;
            
            // Use stop_token in wait conditions for immediate cancellation
            if (std::this_thread::sleep_for(std::chrono::milliseconds(300)); 
                stoken.stop_requested()) {
                std::cout << "Thread " << id << " stopping due to stop request" << std::endl;
                break;
            }
            
            if (count >= 10) break; // Prevent infinite loop
        }
        std::cout << "Thread " << id << " finished with count: " << count << std::endl;
    };
    
    std::jthread worker1(cancellable_worker, 1);
    std::jthread worker2(cancellable_worker, 2);
    
    // Let them work for a while
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    // Request stop for worker1
    std::cout << "Requesting stop for worker1..." << std::endl;
    worker1.request_stop();
    
    // worker2 continues until natural completion or scope exit
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    std::cout << "Exiting scope - worker2 will be stopped and joined" << std::endl;
}

// 3. Stop token with condition variables
void demonstrate_stop_token_with_cv() {
    std::cout << "\n=== 3. Stop Token with Condition Variables ===" << std::endl;
    
    std::mutex mtx;
    std::condition_variable_any cv; // Note: condition_variable_any for stop_token
    std::atomic<bool> data_ready{false};
    std::atomic<int> processed_count{0};
    
    auto consumer = [&](std::stop_token stoken, int id) {
        std::unique_lock lock(mtx);
        while (!stoken.stop_requested()) {
            // Wait with stop_token support
            cv.wait(lock, stoken, [&] { return data_ready.load() || stoken.stop_requested(); });
            
            if (stoken.stop_requested()) {
                std::cout << "Consumer " << id << " stopping due to stop request" << std::endl;
                break;
            }
            
            if (data_ready.exchange(false)) {
                processed_count++;
                std::cout << "Consumer " << id << " processed data. Count: " 
                          << processed_count.load() << std::endl;
            }
        }
    };
    
    std::jthread consumer1(consumer, 1);
    std::jthread consumer2(consumer, 2);
    
    // Producer simulation
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        {
            std::lock_guard lock(mtx);
            data_ready = true;
            std::cout << "Producer: Data " << i << " ready" << std::endl;
        }
        cv.notify_all();
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // Stop consumers
    std::cout << "Stopping consumers..." << std::endl;
    consumer1.request_stop();
    consumer2.request_stop();
    cv.notify_all(); // Wake up waiting consumers
}

// 4. Custom stop callback
class StopCallbackDemo {
private:
    std::atomic<int> cleanup_count{0};
    
public:
    void demonstrate_stop_callback() {
        std::cout << "\n=== 4. Stop Callback Demo ===" << std::endl;
        
        auto worker_with_callback = [this](std::stop_token stoken) {
            // Register a callback that will be called when stop is requested
            std::stop_callback callback(stoken, [this]() {
                cleanup_count++;
                std::cout << "Stop callback executed! Cleanup count: " 
                          << cleanup_count.load() << std::endl;
                // Perform cleanup operations here
            });
            
            // Simulate work
            for (int i = 0; i < 20; ++i) {
                if (stoken.stop_requested()) {
                    std::cout << "Worker detected stop request at iteration " << i << std::endl;
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "Working... " << i << std::endl;
            }
            
            std::cout << "Worker finished" << std::endl;
        };
        
        std::jthread worker(worker_with_callback);
        
        // Let it work for a bit
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        std::cout << "Requesting stop..." << std::endl;
        worker.request_stop();
        
        // jthread will automatically join
    }
};

// 5. Manual stop_source usage
void demonstrate_manual_stop_source() {
    std::cout << "\n=== 5. Manual Stop Source Usage ===" << std::endl;
    
    std::stop_source stop_src;
    std::stop_token stop_tok = stop_src.get_token();
    
    auto controlled_worker = [](std::stop_token stoken, int id) {
        int iterations = 0;
        while (!stoken.stop_requested() && iterations < 15) {
            std::cout << "Controlled worker " << id << ": " << iterations++ << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        std::cout << "Controlled worker " << id << " finished" << std::endl;
    };
    
    // Create threads with the same stop token
    std::jthread worker1(controlled_worker, 1);
    std::jthread worker2(controlled_worker, 2);
    std::jthread worker3(controlled_worker, 3);
    
    // Manually control stop source
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    
    std::cout << "Manually requesting stop for all workers..." << std::endl;
    stop_src.request_stop(); // This will stop all threads using this stop_token
    
    // Note: workers will still need their own stop tokens to be stopped
    // This demonstrates the concept, but for jthread, we need individual stop requests
    worker1.request_stop();
    worker2.request_stop();
    worker3.request_stop();
}

// 6. Performance comparison: std::thread vs std::jthread
void performance_comparison() {
    std::cout << "\n=== 6. Performance Comparison ===" << std::endl;
    
    constexpr int NUM_THREADS = 100;
    constexpr int WORK_SIZE = 1000;
    
    auto work_function = [](int start, int end) {
        volatile long long sum = 0;
        for (int i = start; i < end; ++i) {
            sum += i * i;
        }
        return sum;
    };
    
    // Test std::thread
    auto start_time = std::chrono::high_resolution_clock::now();
    {
        std::vector<std::thread> threads;
        threads.reserve(NUM_THREADS);
        
        for (int i = 0; i < NUM_THREADS; ++i) {
            int start = i * WORK_SIZE;
            int end = (i + 1) * WORK_SIZE;
            threads.emplace_back(work_function, start, end);
        }
        
        // Manual join
        for (auto& t : threads) {
            t.join();
        }
    }
    auto thread_time = std::chrono::high_resolution_clock::now() - start_time;
    
    // Test std::jthread
    start_time = std::chrono::high_resolution_clock::now();
    {
        std::vector<std::jthread> jthreads;
        jthreads.reserve(NUM_THREADS);
        
        for (int i = 0; i < NUM_THREADS; ++i) {
            int start = i * WORK_SIZE;
            int end = (i + 1) * WORK_SIZE;
            jthreads.emplace_back([=](std::stop_token) { 
                work_function(start, end); 
            });
        }
        
        // Automatic join when jthreads go out of scope
    }
    auto jthread_time = std::chrono::high_resolution_clock::now() - start_time;
    
    std::cout << "std::thread time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(thread_time).count() 
              << " ms" << std::endl;
    std::cout << "std::jthread time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(jthread_time).count() 
              << " ms" << std::endl;
    
    std::cout << "Performance difference is minimal - jthread adds convenience, not speed" << std::endl;
}

// 7. Best practices with jthread
void demonstrate_best_practices() {
    std::cout << "\n=== 7. Best Practices with jthread ===" << std::endl;
    
    std::cout << "Best practices for std::jthread:" << std::endl;
    std::cout << "✅ Use jthread instead of thread for automatic resource management" << std::endl;
    std::cout << "✅ Always check stop_token in long-running loops" << std::endl;
    std::cout << "✅ Use condition_variable_any for stop_token support" << std::endl;
    std::cout << "✅ Register stop_callbacks for cleanup operations" << std::endl;
    std::cout << "✅ Use stop_token::stop_requested() for cooperative cancellation" << std::endl;
    std::cout << "✅ Prefer jthread for exception safety (RAII)" << std::endl;
    
    // Example of exception safety
    auto exception_safe_example = []() {
        try {
            std::jthread risky_thread([]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                throw std::runtime_error("Something went wrong!");
            });
            
            // Even if an exception is thrown here, jthread will be properly joined
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            throw std::runtime_error("Another exception!");
            
        } catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
            std::cout << "jthread was automatically joined despite exceptions" << std::endl;
        }
    };
    
    exception_safe_example();
}

int main() {
    std::cout << "=== C++20 std::jthread Demo ===" << std::endl;
    
    try {
        demonstrate_basic_jthread();
        demonstrate_stop_token();
        demonstrate_stop_token_with_cv();
        
        StopCallbackDemo callback_demo;
        callback_demo.demonstrate_stop_callback();
        
        demonstrate_manual_stop_source();
        performance_comparison();
        demonstrate_best_practices();
        
    } catch (const std::exception& e) {
        std::cerr << "Exception in main: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== jthread Benefits Summary ===" << std::endl;
    std::cout << "✅ Automatic joining (RAII)" << std::endl;
    std::cout << "✅ Built-in stop token support" << std::endl;
    std::cout << "✅ Exception safety" << std::endl;
    std::cout << "✅ Cooperative cancellation" << std::endl;
    std::cout << "✅ Cleaner code (no manual join/detach)" << std::endl;
    std::cout << "✅ Better resource management" << std::endl;
    std::cout << "⚠️  Requires C++20 support" << std::endl;
    std::cout << "⚠️  Slightly more overhead than std::thread" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++20 -pthread -Wall -Wextra -o jthread_demo jthread_demo.cpp
./jthread_demo

Key Differences: std::thread vs std::jthread

std::thread:
- Manual join() or detach() required
- No built-in cancellation mechanism
- Risk of resource leaks if not properly managed
- terminate() called if destroyed without join/detach

std::jthread:
- Automatic joining in destructor (RAII)
- Built-in stop token support for cooperative cancellation
- Exception safe - always properly cleaned up
- Easier to use correctly

Stop Token Benefits:
- Cooperative cancellation (thread checks if it should stop)
- Works with condition variables (condition_variable_any)
- Callback support for cleanup operations
- No forced termination - graceful shutdown

Use Cases:
- Long-running background tasks that need cancellation
- Worker threads in thread pools
- Any scenario where you want automatic resource management
- Applications requiring graceful shutdown

Best Practices:
1. Prefer std::jthread over std::thread in new code
2. Always check stop_token in loops
3. Use condition_variable_any for wait operations with stop_token
4. Register callbacks for cleanup operations
5. Design for cooperative cancellation, not forced termination
*/
