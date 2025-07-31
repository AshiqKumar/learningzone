/**
 * @file thread_local_demo.cpp
 * @brief Demonstration of 'thread_local' storage class (C++11)
 * 
 * Compile: g++ -std=c++17 -Wall -Wextra -pthread thread_local_demo.cpp -o thread_local_demo
 * Run: ./thread_local_demo
 */

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <atomic>
#include <string>
#include <sstream>

// Global thread_local variable
thread_local int global_thread_counter = 0;

// Thread_local with initialization
thread_local std::string thread_name = "Unnamed Thread";

// Thread_local static variable in function
int getThreadLocalId() {
    thread_local static int id_counter = 0;
    return ++id_counter;
}

// Class with thread_local static member
class ThreadLocalDemo {
private:
    thread_local static int instance_count;
    int id;
    
public:
    ThreadLocalDemo() : id(++instance_count) {
        std::cout << "ThreadLocalDemo instance " << id 
                  << " created in thread " << std::this_thread::get_id() << std::endl;
    }
    
    int getId() const { return id; }
    static int getInstanceCount() { return instance_count; }
};

// Thread_local static member definition
thread_local int ThreadLocalDemo::instance_count = 0;

// Thread-safe output helper
std::mutex output_mutex;

void safe_print(const std::string& message) {
    std::lock_guard<std::mutex> lock(output_mutex);
    std::cout << message << std::endl;
}

// Worker function demonstrating thread_local variables
void worker_function(int worker_id) {
    // Set thread-specific name
    thread_name = "Worker-" + std::to_string(worker_id);
    
    // Get thread-local ID
    int thread_local_id = getThreadLocalId();
    
    std::ostringstream oss;
    oss << thread_name << " (ID: " << thread_local_id << ") starting...";
    safe_print(oss.str());
    
    // Modify global thread_local variable
    for (int i = 0; i < 5; ++i) {
        global_thread_counter++;
        
        std::ostringstream msg;
        msg << thread_name << ": global_thread_counter = " << global_thread_counter;
        safe_print(msg.str());
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    // Create thread_local objects
    ThreadLocalDemo obj1;
    ThreadLocalDemo obj2;
    
    std::ostringstream final_msg;
    final_msg << thread_name << " final state: counter=" << global_thread_counter 
              << ", objects=" << ThreadLocalDemo::getInstanceCount();
    safe_print(final_msg.str());
}

// Demonstrate thread_local with complex types
class ThreadLocalResource {
private:
    std::vector<int> data;
    std::string name;
    
public:
    ThreadLocalResource() {
        name = "Resource-" + std::to_string(reinterpret_cast<uintptr_t>(this));
        data.reserve(100);
        
        std::ostringstream msg;
        msg << "ThreadLocalResource '" << name << "' created in thread " 
            << std::this_thread::get_id();
        safe_print(msg.str());
    }
    
    ~ThreadLocalResource() {
        std::ostringstream msg;
        msg << "ThreadLocalResource '" << name << "' destroyed in thread " 
            << std::this_thread::get_id();
        safe_print(msg.str());
    }
    
    void addData(int value) {
        data.push_back(value);
    }
    
    size_t size() const { return data.size(); }
    const std::string& getName() const { return name; }
};

// Thread_local complex object
thread_local ThreadLocalResource thread_resource;

void complex_worker(int worker_id) {
    thread_name = "Complex-" + std::to_string(worker_id);
    
    // Use thread_local complex object
    for (int i = 0; i < 3; ++i) {
        thread_resource.addData(worker_id * 10 + i);
        
        std::ostringstream msg;
        msg << thread_name << ": Added data, size now " << thread_resource.size();
        safe_print(msg.str());
    }
    
    std::ostringstream final_msg;
    final_msg << thread_name << " finished with resource '" 
              << thread_resource.getName() << "', size: " << thread_resource.size();
    safe_print(final_msg.str());
}

// Demonstrate thread_local initialization timing
void initialization_demo(int id) {
    thread_name = "Init-" + std::to_string(id);
    
    safe_print(thread_name + ": Before accessing thread_local variable");
    
    // First access to thread_local static - initialization happens here
    thread_local std::string expensive_init = []() {
        std::ostringstream msg;
        msg << "Expensive initialization in thread " << std::this_thread::get_id();
        safe_print(msg.str());
        return "Initialized in " + std::to_string(id);
    }();
    
    safe_print(thread_name + ": thread_local variable = '" + expensive_init + "'");
    
    // Second access - no re-initialization
    safe_print(thread_name + ": Second access = '" + expensive_init + "'");
}

// Performance comparison
void performance_comparison() {
    std::cout << "\n=== Performance Comparison ===" << std::endl;
    
    const int iterations = 1000000;
    
    // Global variable (requires synchronization)
    static std::atomic<int> global_atomic{0};
    static int global_var = 0;
    static std::mutex global_mutex;
    
    // Thread_local variable (no synchronization needed)
    thread_local int local_var = 0;
    
    // Test 1: Atomic operations
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        global_atomic++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto atomic_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test 2: Thread_local operations
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        local_var++;
    }
    end = std::chrono::high_resolution_clock::now();
    auto local_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Atomic operations: " << atomic_time.count() << " microseconds" << std::endl;
    std::cout << "Thread_local operations: " << local_time.count() << " microseconds" << std::endl;
    std::cout << "Thread_local is " << (atomic_time.count() / (double)local_time.count()) 
              << "x faster" << std::endl;
}

// Thread_local with RAII
class ThreadRAII {
private:
    std::string name;
    
public:
    ThreadRAII(const std::string& n) : name(n) {
        std::ostringstream msg;
        msg << "ThreadRAII '" << name << "' constructed in thread " 
            << std::this_thread::get_id();
        safe_print(msg.str());
    }
    
    ~ThreadRAII() {
        std::ostringstream msg;
        msg << "ThreadRAII '" << name << "' destructed in thread " 
            << std::this_thread::get_id();
        safe_print(msg.str());
    }
    
    void doWork() {
        std::ostringstream msg;
        msg << "ThreadRAII '" << name << "' doing work in thread " 
            << std::this_thread::get_id();
        safe_print(msg.str());
    }
};

void raii_demo(int id) {
    thread_local ThreadRAII raii_obj("RAII-" + std::to_string(id));
    raii_obj.doWork();
    
    // Object will be destroyed when thread exits
}

int main() {
    std::cout << "=== THREAD_LOCAL STORAGE CLASS DEMO ===" << std::endl;
    
    // 1. Basic thread_local demonstration
    std::cout << "\n1. Basic Thread_Local Variables:" << std::endl;
    
    std::vector<std::thread> threads;
    
    // Create multiple threads
    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back(worker_function, i);
    }
    
    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }
    threads.clear();
    
    // Check main thread's global_thread_counter
    std::cout << "\nMain thread global_thread_counter: " << global_thread_counter << std::endl;
    
    // 2. Complex objects with thread_local
    std::cout << "\n2. Complex Thread_Local Objects:" << std::endl;
    
    for (int i = 1; i <= 2; ++i) {
        threads.emplace_back(complex_worker, i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    threads.clear();
    
    // 3. Initialization timing
    std::cout << "\n3. Thread_Local Initialization Timing:" << std::endl;
    
    for (int i = 1; i <= 2; ++i) {
        threads.emplace_back(initialization_demo, i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    threads.clear();
    
    // 4. Performance comparison
    std::cout << "\n4. Performance Comparison:" << std::endl;
    performance_comparison();
    
    // 5. RAII with thread_local
    std::cout << "\n5. RAII with Thread_Local:" << std::endl;
    
    for (int i = 1; i <= 2; ++i) {
        threads.emplace_back(raii_demo, i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    threads.clear();
    
    // 6. Thread_local in main thread
    std::cout << "\n6. Thread_Local in Main Thread:" << std::endl;
    
    thread_name = "Main Thread";
    global_thread_counter = 100;
    
    std::cout << "Main thread name: " << thread_name << std::endl;
    std::cout << "Main thread counter: " << global_thread_counter << std::endl;
    std::cout << "Main thread ID: " << getThreadLocalId() << std::endl;
    
    ThreadLocalDemo main_obj;
    std::cout << "Main thread object count: " << ThreadLocalDemo::getInstanceCount() << std::endl;
    
    // 7. Demonstrate thread_local lifetime
    std::cout << "\n7. Thread_Local Lifetime:" << std::endl;
    
    auto lifetime_demo = []() {
        thread_local int counter = 0;
        thread_local std::string msg = "Thread-local in lambda";
        
        counter++;
        std::ostringstream oss;
        oss << "Lambda thread_local: " << msg << ", counter: " << counter 
            << ", thread: " << std::this_thread::get_id();
        safe_print(oss.str());
    };
    
    // Call lambda in multiple threads
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back([&lifetime_demo, i]() {
            for (int j = 0; j < 2; ++j) {
                lifetime_demo();
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "\n=== THREAD_LOCAL BENEFITS ===" << std::endl;
    std::cout << "✅ Each thread has its own copy of the variable" << std::endl;
    std::cout << "✅ No synchronization needed for thread_local access" << std::endl;
    std::cout << "✅ Better performance than shared variables with locks" << std::endl;
    std::cout << "✅ Automatic cleanup when thread exits" << std::endl;
    std::cout << "✅ Useful for thread-specific caches, counters, and state" << std::endl;
    
    std::cout << "\n=== THREAD_LOCAL USE CASES ===" << std::endl;
    std::cout << "🎯 Thread-specific error handling state" << std::endl;
    std::cout << "🎯 Per-thread caching mechanisms" << std::endl;
    std::cout << "🎯 Thread-local random number generators" << std::endl;
    std::cout << "🎯 Thread-specific counters and statistics" << std::endl;
    std::cout << "🎯 Thread-local configuration or context" << std::endl;
    
    std::cout << "\n=== THREAD_LOCAL CONSIDERATIONS ===" << std::endl;
    std::cout << "⚠️  Memory usage scales with number of threads" << std::endl;
    std::cout << "⚠️  Initialization happens on first access per thread" << std::endl;
    std::cout << "⚠️  Destructors called when thread exits" << std::endl;
    std::cout << "⚠️  Not suitable for data that needs to be shared" << std::endl;
    std::cout << "⚠️  Be careful with static thread_local in shared libraries" << std::endl;
    
    return 0;
}

/*
Thread_Local Storage Class Summary:

Purpose (C++11):
- Creates separate instance of variable for each thread
- Provides thread-specific storage without synchronization
- Combines benefits of global accessibility with thread safety

Key Features:
1. Each thread gets its own copy
2. No synchronization required
3. Automatic initialization on first access
4. Automatic cleanup on thread exit
5. Can be applied to global, namespace, local static, and class static variables

Common Use Cases:
1. Thread-specific error handling
2. Per-thread caching
3. Thread-local random number generators
4. Thread-specific counters/statistics
5. Thread-local configuration

Initialization:
- Happens on first access in each thread
- Constructor called once per thread
- Destructor called when thread exits

Performance Benefits:
- No locking overhead
- Better cache locality
- Eliminates false sharing
- Faster than atomic operations for frequent access

Memory Considerations:
- Memory usage = (number of threads) × (size of variable)
- Each thread maintains separate copy
- Memory freed when thread exits

Scope Rules:
- Global thread_local: accessible from anywhere
- Local static thread_local: function scope, per-thread instance
- Class static thread_local: class scope, per-thread instance

Best Practices:
1. Use for frequently accessed thread-specific data
2. Avoid for large objects if many threads exist
3. Be careful with initialization costs
4. Consider thread pool scenarios
5. Document thread_local usage clearly

Limitations:
- Cannot be used with non-static class members
- May not work well with thread pools (threads reused)
- Initialization order can be complex
- Debugging can be more difficult

Comparison with Alternatives:
- vs Global + Mutex: Much faster, no contention
- vs TLS APIs: More convenient, RAII support
- vs Thread-specific containers: Automatic cleanup
- vs Atomic variables: Better for complex types
*/
