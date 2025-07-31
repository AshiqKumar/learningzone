// C++20 std::latch and std::barrier - Synchronization Primitives
// Compile: g++ -std=c++20 -pthread -o latch_barrier_demo latch_barrier_demo.cpp
// Run: ./latch_barrier_demo

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <latch>
#include <barrier>
#include <random>
#include <atomic>
#include <string>

// 1. std::latch - Single-use countdown synchronization
void demonstrate_basic_latch() {
    std::cout << "=== 1. Basic std::latch Usage ===" << std::endl;
    
    constexpr int NUM_WORKERS = 5;
    std::latch work_done(NUM_WORKERS); // Initialize with count
    std::latch start_signal(1);        // Start gate
    
    auto worker = [&](int id) {
        std::cout << "Worker " << id << " waiting for start signal..." << std::endl;
        start_signal.wait(); // Wait for start signal
        
        // Simulate work
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(100, 500);
        auto work_time = std::chrono::milliseconds(dis(gen));
        
        std::cout << "Worker " << id << " starting work..." << std::endl;
        std::this_thread::sleep_for(work_time);
        std::cout << "Worker " << id << " finished work!" << std::endl;
        
        work_done.count_down(); // Signal completion
    };
    
    // Create workers
    std::vector<std::jthread> workers;
    for (int i = 0; i < NUM_WORKERS; ++i) {
        workers.emplace_back(worker, i);
    }
    
    std::cout << "Main thread: Starting all workers..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    start_signal.count_down(); // Release all workers
    
    std::cout << "Main thread: Waiting for all workers to complete..." << std::endl;
    work_done.wait(); // Wait for all workers to finish
    
    std::cout << "Main thread: All workers completed!" << std::endl;
}

// 2. std::latch for phased initialization
void demonstrate_initialization_latch() {
    std::cout << "\n=== 2. Initialization Latch Pattern ===" << std::endl;
    
    constexpr int NUM_SERVICES = 3;
    std::latch initialization_complete(NUM_SERVICES);
    std::atomic<bool> system_ready{false};
    
    auto initialize_service = [&](const std::string& service_name, int init_time_ms) {
        std::cout << service_name << ": Starting initialization..." << std::endl;
        
        // Simulate initialization work
        std::this_thread::sleep_for(std::chrono::milliseconds(init_time_ms));
        
        std::cout << service_name << ": Initialization complete!" << std::endl;
        initialization_complete.count_down();
        
        // Wait for all services to be ready
        initialization_complete.wait();
        std::cout << service_name << ": All services ready, starting normal operation" << std::endl;
    };
    
    // Start services
    std::jthread db_service(initialize_service, "DatabaseService", 300);
    std::jthread net_service(initialize_service, "NetworkService", 200);
    std::jthread cache_service(initialize_service, "CacheService", 400);
    
    // Main thread waits for complete system initialization
    std::cout << "Main: Waiting for system initialization..." << std::endl;
    initialization_complete.wait();
    system_ready = true;
    std::cout << "Main: System fully initialized and ready!" << std::endl;
}

// 3. std::barrier - Multi-phase synchronization
void demonstrate_basic_barrier() {
    std::cout << "\n=== 3. Basic std::barrier Usage ===" << std::endl;
    
    constexpr int NUM_THREADS = 4;
    constexpr int NUM_PHASES = 3;
    
    // Barrier with a completion function
    std::barrier phase_barrier(NUM_THREADS, []() noexcept {
        static int phase = 0;
        std::cout << "*** Phase " << ++phase << " completed by all threads ***" << std::endl;
    });
    
    auto worker = [&](int id) {
        for (int phase = 1; phase <= NUM_PHASES; ++phase) {
            // Simulate work for this phase
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(100, 300);
            auto work_time = std::chrono::milliseconds(dis(gen));
            
            std::cout << "Thread " << id << " working on phase " << phase 
                      << " (will take " << work_time.count() << "ms)" << std::endl;
            
            std::this_thread::sleep_for(work_time);
            
            std::cout << "Thread " << id << " finished phase " << phase << std::endl;
            
            // Wait for all threads to complete this phase
            phase_barrier.arrive_and_wait();
            
            std::cout << "Thread " << id << " proceeding to next phase" << std::endl;
        }
        std::cout << "Thread " << id << " completed all phases!" << std::endl;
    };
    
    std::vector<std::jthread> threads;
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(worker, i);
    }
    
    // Threads automatically join when jthreads go out of scope
}

// 4. Advanced barrier usage - Producer/Consumer phases
void demonstrate_producer_consumer_barrier() {
    std::cout << "\n=== 4. Producer/Consumer Barrier Pattern ===" << std::endl;
    
    constexpr int NUM_PRODUCERS = 2;
    constexpr int NUM_CONSUMERS = 3;
    constexpr int TOTAL_THREADS = NUM_PRODUCERS + NUM_CONSUMERS;
    constexpr int NUM_BATCHES = 3;
    
    std::vector<int> shared_buffer;
    std::mutex buffer_mutex;
    
    std::barrier batch_barrier(TOTAL_THREADS, [&]() noexcept {
        static int batch = 0;
        batch++;
        std::cout << "*** Batch " << batch << " processing complete ***" << std::endl;
        if (batch < NUM_BATCHES) {
            std::cout << "*** Starting batch " << (batch + 1) << " ***" << std::endl;
        }
    });
    
    auto producer = [&](int id) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        
        for (int batch = 0; batch < NUM_BATCHES; ++batch) {
            // Produce data
            std::vector<int> local_data;
            for (int i = 0; i < 5; ++i) {
                local_data.push_back(dis(gen));
            }
            
            // Add to shared buffer
            {
                std::lock_guard lock(buffer_mutex);
                shared_buffer.insert(shared_buffer.end(), local_data.begin(), local_data.end());
                std::cout << "Producer " << id << " added " << local_data.size() 
                          << " items to buffer (batch " << (batch + 1) << ")" << std::endl;
            }
            
            // Wait for all producers and consumers to complete this batch
            batch_barrier.arrive_and_wait();
        }
        std::cout << "Producer " << id << " completed all batches" << std::endl;
    };
    
    auto consumer = [&](int id) {
        for (int batch = 0; batch < NUM_BATCHES; ++batch) {
            // Process data from buffer
            std::vector<int> consumed_data;
            {
                std::lock_guard lock(buffer_mutex);
                if (!shared_buffer.empty()) {
                    // Take some items (simulate processing)
                    size_t take_count = std::min(size_t(3), shared_buffer.size());
                    consumed_data.assign(shared_buffer.begin(), shared_buffer.begin() + take_count);
                    shared_buffer.erase(shared_buffer.begin(), shared_buffer.begin() + take_count);
                }
            }
            
            if (!consumed_data.empty()) {
                std::cout << "Consumer " << id << " processed " << consumed_data.size() 
                          << " items (batch " << (batch + 1) << ")" << std::endl;
                
                // Simulate processing time
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            
            // Wait for all producers and consumers to complete this batch
            batch_barrier.arrive_and_wait();
        }
        std::cout << "Consumer " << id << " completed all batches" << std::endl;
    };
    
    std::vector<std::jthread> threads;
    
    // Create producers
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        threads.emplace_back(producer, i);
    }
    
    // Create consumers
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        threads.emplace_back(consumer, i);
    }
}

// 5. Barrier with arrive_and_drop for dynamic participation
void demonstrate_arrive_and_drop() {
    std::cout << "\n=== 5. Barrier arrive_and_drop Pattern ===" << std::endl;
    
    constexpr int INITIAL_THREADS = 4;
    std::barrier dynamic_barrier(INITIAL_THREADS);
    std::atomic<int> active_threads{INITIAL_THREADS};
    
    auto worker = [&](int id, bool will_drop) {
        for (int phase = 1; phase <= 3; ++phase) {
            std::cout << "Thread " << id << " working on phase " << phase << std::endl;
            
            // Simulate work
            std::this_thread::sleep_for(std::chrono::milliseconds(100 + id * 50));
            
            if (will_drop && phase == 2) {
                std::cout << "Thread " << id << " dropping out after phase " << phase << std::endl;
                active_threads--;
                dynamic_barrier.arrive_and_drop(); // Leave the barrier group
                break;
            } else {
                std::cout << "Thread " << id << " completed phase " << phase << std::endl;
                dynamic_barrier.arrive_and_wait();
            }
        }
        
        if (!will_drop) {
            std::cout << "Thread " << id << " completed all phases" << std::endl;
        }
    };
    
    std::vector<std::jthread> threads;
    threads.emplace_back(worker, 1, false); // Stays for all phases
    threads.emplace_back(worker, 2, true);  // Drops out after phase 2
    threads.emplace_back(worker, 3, false); // Stays for all phases  
    threads.emplace_back(worker, 4, true);  // Drops out after phase 2
    
    // Monitor active threads
    std::jthread monitor([&]() {
        while (active_threads.load() > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "Monitor: " << active_threads.load() << " threads still active" << std::endl;
        }
        std::cout << "Monitor: All threads completed" << std::endl;
    });
}

// 6. Performance comparison and best practices
void demonstrate_performance_and_practices() {
    std::cout << "\n=== 6. Performance and Best Practices ===" << std::endl;
    
    constexpr int NUM_ITERATIONS = 1000;
    constexpr int NUM_THREADS = 4;
    
    // Measure latch performance
    auto start_time = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::latch sync_latch(NUM_THREADS);
        
        std::vector<std::jthread> threads;
        for (int t = 0; t < NUM_THREADS; ++t) {
            threads.emplace_back([&]() {
                // Minimal work
                volatile int x = 0;
                x++;
                sync_latch.count_down();
            });
        }
        
        sync_latch.wait();
    }
    
    auto latch_time = std::chrono::high_resolution_clock::now() - start_time;
    
    // Measure barrier performance
    start_time = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::barrier sync_barrier(NUM_THREADS);
        
        std::vector<std::jthread> threads;
        for (int t = 0; t < NUM_THREADS; ++t) {
            threads.emplace_back([&]() {
                // Minimal work
                volatile int x = 0;
                x++;
                sync_barrier.arrive_and_wait();
            });
        }
    }
    
    auto barrier_time = std::chrono::high_resolution_clock::now() - start_time;
    
    std::cout << "Performance comparison (" << NUM_ITERATIONS << " iterations):" << std::endl;
    std::cout << "std::latch: " 
              << std::chrono::duration_cast<std::chrono::microseconds>(latch_time).count() 
              << " microseconds" << std::endl;
    std::cout << "std::barrier: " 
              << std::chrono::duration_cast<std::chrono::microseconds>(barrier_time).count() 
              << " microseconds" << std::endl;
    
    std::cout << "\nBest Practices:" << std::endl;
    std::cout << "✅ Use std::latch for one-time synchronization events" << std::endl;
    std::cout << "✅ Use std::barrier for repeated multi-phase synchronization" << std::endl;
    std::cout << "✅ Consider arrive_and_drop for dynamic thread participation" << std::endl;
    std::cout << "✅ Use completion functions in barriers for phase transitions" << std::endl;
    std::cout << "✅ Prefer these over condition variables when appropriate" << std::endl;
}

int main() {
    std::cout << "=== C++20 std::latch and std::barrier Demo ===" << std::endl;
    
    try {
        demonstrate_basic_latch();
        demonstrate_initialization_latch();
        demonstrate_basic_barrier();
        demonstrate_producer_consumer_barrier();
        demonstrate_arrive_and_drop();
        demonstrate_performance_and_practices();
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "\nstd::latch:" << std::endl;
    std::cout << "✅ Single-use countdown synchronization" << std::endl;
    std::cout << "✅ Perfect for initialization phases" << std::endl;
    std::cout << "✅ Lightweight and efficient" << std::endl;
    std::cout << "✅ Cannot be reset (single-use)" << std::endl;
    
    std::cout << "\nstd::barrier:" << std::endl;
    std::cout << "✅ Reusable multi-phase synchronization" << std::endl;
    std::cout << "✅ Supports completion functions" << std::endl;
    std::cout << "✅ Dynamic participation with arrive_and_drop" << std::endl;
    std::cout << "✅ Ideal for iterative parallel algorithms" << std::endl;
    
    std::cout << "\nUse Cases:" << std::endl;
    std::cout << "• Latch: System initialization, one-time events, startup synchronization" << std::endl;
    std::cout << "• Barrier: Parallel algorithms, multi-phase processing, simulation steps" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++20 -pthread -Wall -Wextra -o latch_barrier_demo latch_barrier_demo.cpp
./latch_barrier_demo

Key Concepts:

std::latch:
- Single-use countdown synchronization
- Initialize with count, threads call count_down()
- Other threads wait() until count reaches zero
- Cannot be reused - one-time synchronization
- Lightweight and efficient

std::barrier:
- Reusable synchronization point for multiple threads
- All threads must arrive before any can proceed
- Supports completion functions executed when all arrive
- Can be reused for multiple phases
- arrive_and_drop() allows dynamic participation

Comparison with other synchronization:

vs std::condition_variable:
- Simpler to use correctly
- No spurious wakeups
- Built-in counting mechanism
- Better performance for simple sync patterns

vs std::mutex:
- Designed for synchronization, not mutual exclusion
- Multiple threads can "arrive" simultaneously
- No ownership concept

Use Cases:

std::latch:
- System initialization (wait for all services to start)
- Parallel task completion detection
- Start/stop gates for thread coordination
- One-time setup synchronization

std::barrier:
- Parallel algorithms with phases (like parallel sort)
- Simulation steps where all threads must complete before next iteration
- Producer/consumer batching
- Multi-stage data processing pipelines

Performance Benefits:
- More efficient than condition_variable + mutex combinations
- Optimized for specific synchronization patterns
- Less prone to bugs (no missed notifications)
- Better CPU cache behavior
*/
