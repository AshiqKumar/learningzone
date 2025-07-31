// C++20 std::counting_semaphore - Resource Management and Flow Control
// Compile: g++ -std=c++20 -pthread -o semaphore_demo semaphore_demo.cpp
// Run: ./semaphore_demo

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <semaphore>
#include <random>
#include <atomic>
#include <queue>
#include <mutex>
#include <string>

// 1. Basic counting semaphore usage
void demonstrate_basic_semaphore() {
    std::cout << "=== 1. Basic Counting Semaphore Usage ===" << std::endl;
    
    // Create a semaphore with 3 permits (can have 3 concurrent accesses)
    std::counting_semaphore<10> resource_semaphore(3);
    std::atomic<int> active_users{0};
    std::atomic<int> total_completed{0};
    
    auto user = [&](int id) {
        std::cout << "User " << id << " waiting for resource..." << std::endl;
        
        // Acquire a permit (will block if none available)
        resource_semaphore.acquire();
        
        int current_active = ++active_users;
        std::cout << "User " << id << " acquired resource (active: " << current_active << ")" << std::endl;
        
        // Simulate resource usage
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(100, 500);
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
        
        --active_users;
        ++total_completed;
        std::cout << "User " << id << " releasing resource (completed: " << total_completed.load() << ")" << std::endl;
        
        // Release the permit
        resource_semaphore.release();
    };
    
    // Create more users than permits to see queuing behavior
    constexpr int NUM_USERS = 8;
    std::vector<std::jthread> users;
    
    for (int i = 0; i < NUM_USERS; ++i) {
        users.emplace_back(user, i);
    }
    
    std::cout << "Created " << NUM_USERS << " users for " << 3 << " resources" << std::endl;
    
    // Monitor active users
    std::jthread monitor([&]() {
        while (total_completed.load() < NUM_USERS) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "Monitor: " << active_users.load() << " active users" << std::endl;
        }
        std::cout << "Monitor: All users completed" << std::endl;
    });
}

// 2. Connection pool simulation
class ConnectionPool {
private:
    std::counting_semaphore<20> available_connections;
    std::queue<int> connection_ids;
    std::mutex pool_mutex;
    std::atomic<int> next_connection_id{1};
    
public:
    ConnectionPool(int pool_size) : available_connections(pool_size) {
        // Initialize connection pool
        std::lock_guard lock(pool_mutex);
        for (int i = 0; i < pool_size; ++i) {
            connection_ids.push(next_connection_id++);
        }
        std::cout << "Connection pool initialized with " << pool_size << " connections" << std::endl;
    }
    
    int acquire_connection() {
        // Wait for an available connection
        available_connections.acquire();
        
        // Get a connection from the pool
        std::lock_guard lock(pool_mutex);
        int conn_id = connection_ids.front();
        connection_ids.pop();
        
        std::cout << "Acquired connection " << conn_id << std::endl;
        return conn_id;
    }
    
    void release_connection(int conn_id) {
        // Return connection to pool
        {
            std::lock_guard lock(pool_mutex);
            connection_ids.push(conn_id);
        }
        
        std::cout << "Released connection " << conn_id << std::endl;
        
        // Signal that a connection is available
        available_connections.release();
    }
    
    size_t available_count() const {
        // Note: This is approximate due to race conditions
        return available_connections.max() - (available_connections.max() - connection_ids.size());
    }
};

void demonstrate_connection_pool() {
    std::cout << "\n=== 2. Connection Pool with Semaphore ===" << std::endl;
    
    ConnectionPool pool(4); // 4 connections available
    constexpr int NUM_CLIENTS = 10;
    
    auto client = [&](int id) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> work_time(200, 800);
        
        std::cout << "Client " << id << " requesting connection..." << std::endl;
        
        // Acquire connection (may block if pool is exhausted)
        int conn_id = pool.acquire_connection();
        
        std::cout << "Client " << id << " got connection " << conn_id << ", starting work..." << std::endl;
        
        // Simulate database work
        std::this_thread::sleep_for(std::chrono::milliseconds(work_time(gen)));
        
        std::cout << "Client " << id << " finished work with connection " << conn_id << std::endl;
        
        // Release connection back to pool
        pool.release_connection(conn_id);
    };
    
    std::vector<std::jthread> clients;
    for (int i = 0; i < NUM_CLIENTS; ++i) {
        clients.emplace_back(client, i);
    }
}

// 3. Producer-Consumer with semaphores
template<typename T, size_t Capacity>
class BoundedQueue {
private:
    std::queue<T> queue_;
    std::mutex queue_mutex_;
    std::counting_semaphore<Capacity> empty_slots_;
    std::counting_semaphore<Capacity> filled_slots_;
    
public:
    BoundedQueue() : empty_slots_(Capacity), filled_slots_(0) {}
    
    void push(T item) {
        // Wait for empty slot
        empty_slots_.acquire();
        
        {
            std::lock_guard lock(queue_mutex_);
            queue_.push(std::move(item));
            std::cout << "Produced item, queue size: " << queue_.size() << std::endl;
        }
        
        // Signal filled slot available
        filled_slots_.release();
    }
    
    T pop() {
        // Wait for filled slot
        filled_slots_.acquire();
        
        T item;
        {
            std::lock_guard lock(queue_mutex_);
            item = std::move(queue_.front());
            queue_.pop();
            std::cout << "Consumed item, queue size: " << queue_.size() << std::endl;
        }
        
        // Signal empty slot available
        empty_slots_.release();
        return item;
    }
    
    size_t size() const {
        std::lock_guard lock(queue_mutex_);
        return queue_.size();
    }
};

void demonstrate_producer_consumer() {
    std::cout << "\n=== 3. Producer-Consumer with Bounded Queue ===" << std::endl;
    
    BoundedQueue<int, 5> bounded_queue;
    std::atomic<bool> production_done{false};
    std::atomic<int> items_produced{0};
    std::atomic<int> items_consumed{0};
    
    auto producer = [&](int id, int items_to_produce) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        std::uniform_int_distribution<> delay(50, 150);
        
        for (int i = 0; i < items_to_produce; ++i) {
            int item = dis(gen);
            std::cout << "Producer " << id << " producing item " << item << std::endl;
            
            bounded_queue.push(item);
            items_produced++;
            
            std::this_thread::sleep_for(std::chrono::milliseconds(delay(gen)));
        }
        
        std::cout << "Producer " << id << " finished producing" << std::endl;
    };
    
    auto consumer = [&](int id) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> delay(100, 200);
        
        while (!production_done.load() || bounded_queue.size() > 0) {
            try {
                int item = bounded_queue.pop();
                items_consumed++;
                std::cout << "Consumer " << id << " consumed item " << item 
                          << " (total consumed: " << items_consumed.load() << ")" << std::endl;
                
                std::this_thread::sleep_for(std::chrono::milliseconds(delay(gen)));
            } catch (...) {
                // Handle any exceptions
                break;
            }
        }
        
        std::cout << "Consumer " << id << " finished consuming" << std::endl;
    };
    
    constexpr int ITEMS_PER_PRODUCER = 8;
    constexpr int NUM_PRODUCERS = 2;
    constexpr int NUM_CONSUMERS = 3;
    
    std::vector<std::jthread> threads;
    
    // Start producers
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        threads.emplace_back(producer, i, ITEMS_PER_PRODUCER);
    }
    
    // Start consumers
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        threads.emplace_back(consumer, i);
    }
    
    // Wait for producers to finish
    std::this_thread::sleep_for(std::chrono::seconds(3));
    production_done = true;
    
    std::cout << "Production phase completed. Items produced: " << items_produced.load() 
              << ", Items consumed: " << items_consumed.load() << std::endl;
}

// 4. Binary semaphore (specialized for 0/1 states)
void demonstrate_binary_semaphore() {
    std::cout << "\n=== 4. Binary Semaphore Usage ===" << std::endl;
    
    std::binary_semaphore mutex_semaphore(1); // Acts like a mutex
    std::binary_semaphore signal_semaphore(0); // Acts like a signal
    
    std::shared_ptr<std::string> shared_resource = std::make_shared<std::string>("Initial Value");
    
    auto writer = [&](int id) {
        std::cout << "Writer " << id << " waiting for mutex..." << std::endl;
        mutex_semaphore.acquire();
        
        std::cout << "Writer " << id << " acquired mutex, writing data..." << std::endl;
        *shared_resource = "Data from writer " + std::to_string(id);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        std::cout << "Writer " << id << " signaling readers..." << std::endl;
        signal_semaphore.release(); // Signal readers
        
        std::cout << "Writer " << id << " releasing mutex..." << std::endl;
        mutex_semaphore.release();
    };
    
    auto reader = [&](int id) {
        std::cout << "Reader " << id << " waiting for signal..." << std::endl;
        signal_semaphore.acquire();
        
        std::cout << "Reader " << id << " got signal, acquiring mutex..." << std::endl;
        mutex_semaphore.acquire();
        
        std::cout << "Reader " << id << " reading: " << *shared_resource << std::endl;
        
        mutex_semaphore.release();
        signal_semaphore.release(); // Allow next reader
    };
    
    std::jthread writer_thread(writer, 1);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    std::vector<std::jthread> readers;
    for (int i = 0; i < 3; ++i) {
        readers.emplace_back(reader, i);
    }
}

// 5. Semaphore-based rate limiting
class RateLimiter {
private:
    std::counting_semaphore<100> permits_;
    std::chrono::steady_clock::time_point last_refill_;
    std::mutex refill_mutex_;
    const int max_permits_;
    const std::chrono::milliseconds refill_interval_;
    const int permits_per_interval_;
    
public:
    RateLimiter(int max_permits, std::chrono::milliseconds refill_interval, int permits_per_interval)
        : permits_(max_permits), last_refill_(std::chrono::steady_clock::now()),
          max_permits_(max_permits), refill_interval_(refill_interval),
          permits_per_interval_(permits_per_interval) {}
    
    bool try_acquire() {
        refill_permits();
        return permits_.try_acquire();
    }
    
    void acquire() {
        refill_permits();
        permits_.acquire();
    }
    
private:
    void refill_permits() {
        std::lock_guard lock(refill_mutex_);
        auto now = std::chrono::steady_clock::now();
        auto elapsed = now - last_refill_;
        
        if (elapsed >= refill_interval_) {
            int intervals = elapsed / refill_interval_;
            int new_permits = std::min(intervals * permits_per_interval_, max_permits_);
            
            for (int i = 0; i < new_permits; ++i) {
                permits_.try_acquire(); // Drain first to avoid overflow
            }
            
            for (int i = 0; i < new_permits; ++i) {
                permits_.release();
            }
            
            last_refill_ = now;
        }
    }
};

void demonstrate_rate_limiting() {
    std::cout << "\n=== 5. Rate Limiting with Semaphores ===" << std::endl;
    
    // Allow 5 permits per second, max 10 permits
    RateLimiter rate_limiter(10, std::chrono::milliseconds(200), 1);
    
    auto api_client = [&](int id) {
        for (int request = 0; request < 8; ++request) {
            auto start = std::chrono::steady_clock::now();
            
            if (rate_limiter.try_acquire()) {
                auto end = std::chrono::steady_clock::now();
                auto wait_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                
                std::cout << "Client " << id << " request " << request 
                          << " approved immediately (waited " << wait_time.count() << "ms)" << std::endl;
            } else {
                std::cout << "Client " << id << " request " << request << " rate limited, waiting..." << std::endl;
                rate_limiter.acquire(); // Block until permit available
                
                auto end = std::chrono::steady_clock::now();
                auto wait_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                
                std::cout << "Client " << id << " request " << request 
                          << " approved after waiting " << wait_time.count() << "ms" << std::endl;
            }
            
            // Simulate API processing time
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    };
    
    std::vector<std::jthread> clients;
    for (int i = 0; i < 3; ++i) {
        clients.emplace_back(api_client, i);
    }
}

// 6. Performance comparison and best practices
void demonstrate_performance_and_practices() {
    std::cout << "\n=== 6. Performance and Best Practices ===" << std::endl;
    
    constexpr int NUM_OPERATIONS = 10000;
    constexpr int NUM_THREADS = 4;
    
    // Test semaphore performance
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::counting_semaphore<10> perf_semaphore(2);
    std::atomic<int> completed_ops{0};
    
    std::vector<std::jthread> threads;
    for (int t = 0; t < NUM_THREADS; ++t) {
        threads.emplace_back([&]() {
            for (int i = 0; i < NUM_OPERATIONS / NUM_THREADS; ++i) {
                perf_semaphore.acquire();
                completed_ops++;
                perf_semaphore.release();
            }
        });
    }
    
    // Wait for completion
    for (auto& t : threads) {
        t.join();
    }
    
    auto semaphore_time = std::chrono::high_resolution_clock::now() - start_time;
    
    std::cout << "Semaphore performance (" << NUM_OPERATIONS << " operations): "
              << std::chrono::duration_cast<std::chrono::microseconds>(semaphore_time).count() 
              << " microseconds" << std::endl;
    
    std::cout << "\nBest Practices:" << std::endl;
    std::cout << "✅ Use counting_semaphore for resource counting" << std::endl;
    std::cout << "✅ Use binary_semaphore for simple signaling" << std::endl;
    std::cout << "✅ Consider try_acquire() for non-blocking scenarios" << std::endl;
    std::cout << "✅ Use semaphores for rate limiting and flow control" << std::endl;
    std::cout << "✅ Prefer semaphores over condition variables for counting" << std::endl;
    std::cout << "✅ Remember: acquire() decrements, release() increments" << std::endl;
}

int main() {
    std::cout << "=== C++20 std::counting_semaphore Demo ===" << std::endl;
    
    try {
        demonstrate_basic_semaphore();
        demonstrate_connection_pool();
        demonstrate_producer_consumer();
        demonstrate_binary_semaphore();
        demonstrate_rate_limiting();
        demonstrate_performance_and_practices();
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "\nCounting Semaphore:" << std::endl;
    std::cout << "✅ Resource counting and access control" << std::endl;
    std::cout << "✅ Producer-consumer flow control" << std::endl;
    std::cout << "✅ Connection pooling" << std::endl;
    std::cout << "✅ Rate limiting" << std::endl;
    
    std::cout << "\nBinary Semaphore:" << std::endl;
    std::cout << "✅ Simple signaling between threads" << std::endl;
    std::cout << "✅ Mutex-like behavior" << std::endl;
    std::cout << "✅ Event notification" << std::endl;
    
    std::cout << "\nKey Operations:" << std::endl;
    std::cout << "• acquire() - Decrements counter, blocks if zero" << std::endl;
    std::cout << "• release() - Increments counter, unblocks waiting threads" << std::endl;
    std::cout << "• try_acquire() - Non-blocking acquire attempt" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++20 -pthread -Wall -Wextra -o semaphore_demo semaphore_demo.cpp
./semaphore_demo

Key Concepts:

Counting Semaphore:
- Maintains a counter of available resources
- acquire() decrements counter (blocks if zero)
- release() increments counter (unblocks waiting threads)
- Template parameter specifies maximum count
- Perfect for resource pools, rate limiting

Binary Semaphore:
- Specialized counting semaphore with max count of 1
- Equivalent to counting_semaphore<1>
- Useful for signaling between threads
- Can act like a mutex or event

Use Cases:

Resource Management:
- Database connection pools
- Thread pools
- Memory pools
- File handle limits

Flow Control:
- Producer-consumer queues
- Rate limiting APIs
- Bandwidth throttling
- Request queuing

Synchronization:
- Event signaling
- Worker coordination
- Batch processing
- Phase synchronization

Performance Characteristics:
- Generally faster than mutex + condition_variable
- Optimized for counting operations
- Less context switching overhead
- Better CPU cache behavior

Best Practices:
1. Choose appropriate maximum count
2. Always pair acquire() with release()
3. Use try_acquire() for non-blocking scenarios
4. Consider timeout variants for robustness
5. Use binary_semaphore for simple signaling
6. Prefer over condition variables for counting

Common Patterns:
- Connection pooling (limit concurrent database connections)
- Rate limiting (API request throttling)
- Worker queues (limit concurrent workers)
- Resource allocation (memory, file handles, etc.)
*/
