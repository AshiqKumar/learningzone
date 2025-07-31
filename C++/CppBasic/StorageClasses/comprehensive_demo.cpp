/**
 * @file comprehensive_demo.cpp
 * @brief Comprehensive demonstration of all C++ storage classes
 * 
 * Compile: g++ -std=c++17 -Wall -Wextra -pthread comprehensive_demo.cpp -o comprehensive_demo
 * Run: ./comprehensive_demo
 */

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <typeinfo>

// ===== EXTERN STORAGE CLASS =====
// External variables (would be defined in another file in real scenario)
int global_extern_var = 1000;
extern void external_function();  // Declaration only

// ===== STATIC STORAGE CLASS =====
// Static global variable (internal linkage)
static int static_global = 2000;

// Static function (internal linkage)
static void static_internal_function() {
    std::cout << "Static internal function called" << std::endl;
}

// ===== THREAD_LOCAL STORAGE CLASS =====
thread_local int thread_counter = 0;
thread_local std::string thread_identifier = "Default";

// ===== COMPREHENSIVE STORAGE CLASS DEMONSTRATION CLASS =====
class StorageClassDemo {
private:
    // Regular member variables (automatic storage for local objects)
    int instance_id;
    std::string name;
    
    // Static member variable (shared across all instances)
    static int total_instances;
    
    // Mutable member (can be modified in const methods)
    mutable int access_count;
    mutable std::mutex access_mutex;
    
    // Thread_local static member
    thread_local static int thread_instances;
    
public:
    // Constructor
    StorageClassDemo(const std::string& obj_name) 
        : instance_id(++total_instances), name(obj_name), access_count(0) {
        thread_instances++;
        std::cout << "StorageClassDemo '" << name << "' created (ID: " << instance_id 
                  << ", Thread instances: " << thread_instances << ")" << std::endl;
    }
    
    // Destructor
    ~StorageClassDemo() {
        std::cout << "StorageClassDemo '" << name << "' destroyed (ID: " << instance_id << ")" << std::endl;
        total_instances--;
        thread_instances--;
    }
    
    // Const method using mutable
    int getAccessCount() const {
        std::lock_guard<std::mutex> lock(access_mutex);
        access_count++;  // Modifying mutable member
        return access_count;
    }
    
    // Static method
    static int getTotalInstances() {
        return total_instances;
    }
    
    // Get thread-local instance count
    static int getThreadInstances() {
        return thread_instances;
    }
    
    // Method demonstrating different storage classes
    void demonstrateStorageClasses() {
        // AUTO storage class (modern type deduction)
        auto local_auto = 42;                    // int
        auto local_string = std::string("auto"); // std::string
        auto local_vector = std::vector<int>{1, 2, 3}; // std::vector<int>
        
        // STATIC local variable
        static int static_local = 0;
        static_local++;
        
        // REGISTER (deprecated) - shown for historical context
        // register int reg_var = 100;  // Would be ignored by modern compilers
        int reg_var = 100;  // Modern equivalent
        
        std::cout << "\n--- " << name << " Storage Classes Demo ---" << std::endl;
        std::cout << "Auto int: " << local_auto << " (type: " << typeid(local_auto).name() << ")" << std::endl;
        std::cout << "Auto string: " << local_string << std::endl;
        std::cout << "Auto vector size: " << local_vector.size() << std::endl;
        std::cout << "Static local: " << static_local << std::endl;
        std::cout << "Register equivalent: " << reg_var << std::endl;
        std::cout << "Instance access count: " << getAccessCount() << std::endl;
    }
    
    // Method using thread_local variables
    void demonstrateThreadLocal() {
        thread_counter++;
        thread_identifier = "Thread-" + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()) % 1000);
        
        std::cout << name << " thread demo: counter=" << thread_counter 
                  << ", identifier=" << thread_identifier << std::endl;
    }
};

// Static member definitions
int StorageClassDemo::total_instances = 0;
thread_local int StorageClassDemo::thread_instances = 0;

// Function demonstrating different variable lifetimes
void demonstrateVariableLifetimes() {
    std::cout << "\n=== Variable Lifetimes Demonstration ===" << std::endl;
    
    // Automatic variables (stack)
    int automatic_var = 100;
    std::string automatic_string = "Automatic";
    
    // Static variables (data segment)
    static int static_counter = 0;
    static std::vector<int> static_vector;
    
    static_counter++;
    static_vector.push_back(static_counter);
    
    // Dynamic variables (heap)
    auto dynamic_ptr = std::make_unique<int>(200);
    
    std::cout << "Automatic var: " << automatic_var << std::endl;
    std::cout << "Automatic string: " << automatic_string << std::endl;
    std::cout << "Static counter: " << static_counter << std::endl;
    std::cout << "Static vector size: " << static_vector.size() << std::endl;
    std::cout << "Dynamic value: " << *dynamic_ptr << std::endl;
    
    // Automatic variables destroyed at end of scope
    // Static variables persist between function calls
    // Dynamic variables managed by smart pointer
}

// Thread function for demonstrating thread_local
void threadFunction(int thread_id) {
    thread_identifier = "Worker-" + std::to_string(thread_id);
    
    StorageClassDemo thread_obj("ThreadObj-" + std::to_string(thread_id));
    
    for (int i = 0; i < 3; ++i) {
        thread_obj.demonstrateThreadLocal();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "Thread " << thread_id << " final thread_counter: " << thread_counter << std::endl;
}

// Performance comparison of storage classes
void performanceComparison() {
    std::cout << "\n=== Performance Comparison ===" << std::endl;
    
    const int iterations = 1000000;
    
    // Automatic variable access
    auto start = std::chrono::high_resolution_clock::now();
    {
        int automatic_var = 0;
        for (int i = 0; i < iterations; ++i) {
            automatic_var++;
        }
    }
    auto auto_time = std::chrono::high_resolution_clock::now() - start;
    
    // Static variable access
    start = std::chrono::high_resolution_clock::now();
    {
        static int static_var = 0;
        for (int i = 0; i < iterations; ++i) {
            static_var++;
        }
    }
    auto static_time = std::chrono::high_resolution_clock::now() - start;
    
    // Thread_local variable access
    start = std::chrono::high_resolution_clock::now();
    {
        thread_local int thread_var = 0;
        for (int i = 0; i < iterations; ++i) {
            thread_var++;
        }
    }
    auto thread_time = std::chrono::high_resolution_clock::now() - start;
    
    auto auto_us = std::chrono::duration_cast<std::chrono::microseconds>(auto_time).count();
    auto static_us = std::chrono::duration_cast<std::chrono::microseconds>(static_time).count();
    auto thread_us = std::chrono::duration_cast<std::chrono::microseconds>(thread_time).count();
    
    std::cout << "Automatic variable: " << auto_us << " microseconds" << std::endl;
    std::cout << "Static variable: " << static_us << " microseconds" << std::endl;
    std::cout << "Thread_local variable: " << thread_us << " microseconds" << std::endl;
}

// Memory layout demonstration
void memoryLayoutDemo() {
    std::cout << "\n=== Memory Layout Demonstration ===" << std::endl;
    
    // Stack variables
    int stack_var1 = 10;
    int stack_var2 = 20;
    
    // Static variables (data segment)
    static int static_var1 = 30;
    static int static_var2 = 40;
    
    // Dynamic variables (heap)
    auto heap_var1 = std::make_unique<int>(50);
    auto heap_var2 = std::make_unique<int>(60);
    
    std::cout << "Stack addresses:" << std::endl;
    std::cout << "  stack_var1: " << &stack_var1 << std::endl;
    std::cout << "  stack_var2: " << &stack_var2 << std::endl;
    
    std::cout << "Static addresses (data segment):" << std::endl;
    std::cout << "  static_var1: " << &static_var1 << std::endl;
    std::cout << "  static_var2: " << &static_var2 << std::endl;
    std::cout << "  static_global: " << &static_global << std::endl;
    
    std::cout << "Heap addresses:" << std::endl;
    std::cout << "  heap_var1: " << heap_var1.get() << std::endl;
    std::cout << "  heap_var2: " << heap_var2.get() << std::endl;
    
    std::cout << "Global addresses:" << std::endl;
    std::cout << "  global_extern_var: " << &global_extern_var << std::endl;
}

// Template function demonstrating auto with various types
template<typename T>
void templateAutoDemo(T&& value) {
    auto local_copy = value;                    // Copy
    auto& local_ref = value;                    // Reference
    const auto& local_const_ref = value;        // Const reference
    auto local_moved = std::forward<T>(value);  // Perfect forwarding
    
    std::cout << "Template auto demo with type: " << typeid(T).name() << std::endl;
    std::cout << "  Value type: " << typeid(decltype(local_copy)).name() << std::endl;
    std::cout << "  Reference type: " << typeid(decltype(local_ref)).name() << std::endl;
    std::cout << "  Const ref type: " << typeid(decltype(local_const_ref)).name() << std::endl;
}

// External function definition (normally in another file)
void external_function() {
    std::cout << "External function called" << std::endl;
    std::cout << "Accessing global_extern_var: " << global_extern_var << std::endl;
}

int main() {
    std::cout << "=== COMPREHENSIVE STORAGE CLASSES DEMO ===" << std::endl;
    
    // 1. Basic storage class demonstration
    std::cout << "\n1. Creating objects to demonstrate storage classes:" << std::endl;
    
    {
        StorageClassDemo obj1("MainObject1");
        StorageClassDemo obj2("MainObject2");
        
        obj1.demonstrateStorageClasses();
        obj2.demonstrateStorageClasses();
        
        std::cout << "Total instances: " << StorageClassDemo::getTotalInstances() << std::endl;
        std::cout << "Thread instances: " << StorageClassDemo::getThreadInstances() << std::endl;
    }  // Objects destroyed here
    
    std::cout << "After scope exit - Total instances: " << StorageClassDemo::getTotalInstances() << std::endl;
    
    // 2. Variable lifetimes
    std::cout << "\n2. Demonstrating variable lifetimes:" << std::endl;
    demonstrateVariableLifetimes();
    demonstrateVariableLifetimes();  // Call again to see static persistence
    
    // 3. Thread_local demonstration
    std::cout << "\n3. Thread_local storage demonstration:" << std::endl;
    
    std::vector<std::thread> threads;
    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back(threadFunction, i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Main thread counter: " << thread_counter << std::endl;
    std::cout << "Main thread identifier: " << thread_identifier << std::endl;
    
    // 4. Auto type deduction
    std::cout << "\n4. Auto type deduction:" << std::endl;
    
    auto int_val = 42;
    auto double_val = 3.14;
    auto string_val = std::string("Hello");
    auto vector_val = std::vector<int>{1, 2, 3};
    
    templateAutoDemo(int_val);
    templateAutoDemo(string_val);
    
    // 5. Static and extern demonstration
    std::cout << "\n5. Static and extern demonstration:" << std::endl;
    
    std::cout << "static_global: " << static_global << std::endl;
    static_internal_function();
    
    std::cout << "global_extern_var: " << global_extern_var << std::endl;
    external_function();
    
    // 6. Mutable demonstration
    std::cout << "\n6. Mutable demonstration:" << std::endl;
    
    const StorageClassDemo const_obj("ConstObject");
    std::cout << "Const object access count: " << const_obj.getAccessCount() << std::endl;
    std::cout << "Const object access count: " << const_obj.getAccessCount() << std::endl;
    
    // 7. Performance comparison
    performanceComparison();
    
    // 8. Memory layout
    memoryLayoutDemo();
    
    // 9. Storage class summary
    std::cout << "\n=== STORAGE CLASSES SUMMARY ===" << std::endl;
    
    std::cout << "\nAUTO (type deduction):" << std::endl;
    std::cout << "  ✅ Automatic type deduction from initializer" << std::endl;
    std::cout << "  ✅ Reduces verbosity with complex types" << std::endl;
    std::cout << "  ✅ Required for lambdas and some templates" << std::endl;
    
    std::cout << "\nSTATIC:" << std::endl;
    std::cout << "  ✅ Persistent between function calls" << std::endl;
    std::cout << "  ✅ Internal linkage for file-scope privacy" << std::endl;
    std::cout << "  ✅ Single instance shared across calls" << std::endl;
    
    std::cout << "\nEXTERN:" << std::endl;
    std::cout << "  ✅ External linkage for cross-file sharing" << std::endl;
    std::cout << "  ✅ Forward declarations" << std::endl;
    std::cout << "  ✅ C/C++ interoperability" << std::endl;
    
    std::cout << "\nMUTABLE:" << std::endl;
    std::cout << "  ✅ Logical const-ness vs bitwise const-ness" << std::endl;
    std::cout << "  ✅ Caching in const methods" << std::endl;
    std::cout << "  ✅ Thread-safe const methods" << std::endl;
    
    std::cout << "\nTHREAD_LOCAL:" << std::endl;
    std::cout << "  ✅ Per-thread storage without synchronization" << std::endl;
    std::cout << "  ✅ Better performance than shared variables" << std::endl;
    std::cout << "  ✅ Automatic cleanup on thread exit" << std::endl;
    
    std::cout << "\nREGISTER (deprecated):" << std::endl;
    std::cout << "  ❌ Deprecated in C++17, removed in C++20" << std::endl;
    std::cout << "  ❌ Modern compilers optimize better" << std::endl;
    std::cout << "  ❌ Use compiler optimization flags instead" << std::endl;
    
    std::cout << "\n=== BEST PRACTICES ===" << std::endl;
    std::cout << "1. Use auto for complex types and type deduction" << std::endl;
    std::cout << "2. Use static for persistent local state" << std::endl;
    std::cout << "3. Use extern for cross-file declarations" << std::endl;
    std::cout << "4. Use mutable sparingly for implementation details" << std::endl;
    std::cout << "5. Use thread_local for thread-specific data" << std::endl;
    std::cout << "6. Avoid register - let compiler optimize" << std::endl;
    std::cout << "7. Understand memory layout implications" << std::endl;
    std::cout << "8. Consider thread safety and lifetime management" << std::endl;
    
    return 0;
}

/*
Comprehensive Storage Classes Summary:

1. AUTO (C++11 Type Deduction):
   - Deduces type from initializer
   - Reduces code verbosity
   - Essential for modern C++ idioms

2. STATIC:
   - Local: Persistent between function calls
   - Global: Internal linkage (file scope)
   - Class members: Shared across instances

3. EXTERN:
   - External linkage for global visibility
   - Forward declarations
   - Cross-file variable/function sharing

4. MUTABLE:
   - Allows modification in const methods
   - Logical const-ness
   - Caching and thread safety

5. THREAD_LOCAL (C++11):
   - Per-thread storage
   - No synchronization needed
   - Automatic cleanup

6. REGISTER (Deprecated):
   - Historical CPU register hint
   - Ignored by modern compilers
   - Use optimization flags instead

Memory Layout:
- Stack: Automatic variables
- Data Segment: Static and global variables  
- Heap: Dynamic allocation
- Per-thread: thread_local variables

Performance Characteristics:
- Automatic: Fast stack access
- Static: Fast data segment access
- Thread_local: Fast thread-specific access
- Dynamic: Slower heap access

Thread Safety:
- Automatic: Thread-safe (per-stack)
- Static: Requires synchronization
- Thread_local: Thread-safe (per-thread)
- Global: Requires synchronization

Best Use Cases:
- auto: Complex type declarations
- static: Singletons, counters, caches
- extern: API declarations, global config
- mutable: Const method caching
- thread_local: Thread-specific state
*/
