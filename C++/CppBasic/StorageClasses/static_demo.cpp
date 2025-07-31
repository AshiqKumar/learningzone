/**
 * @file static_demo.cpp
 * @brief Demonstration of 'static' storage class
 * 
 * Compile: g++ -std=c++17 -Wall -Wextra static_demo.cpp -o static_demo
 * Run: ./static_demo
 */

#include <iostream>
#include <string>
#include <vector>

// Global variables (default external linkage)
int global_var = 100;

// Static global variable (internal linkage - file scope only)
static int static_global = 200;

// Static function (internal linkage)
static void static_function() {
    std::cout << "Static function called (internal linkage)" << std::endl;
}

// Function to demonstrate static local variables
int counter() {
    static int count = 0;  // Static local variable
    count++;
    std::cout << "Counter called " << count << " times" << std::endl;
    return count;
}

// Function with multiple static variables
void multipleStatics() {
    static int call_count = 0;
    static std::string message = "Hello from static!";
    static bool first_call = true;
    
    call_count++;
    
    if (first_call) {
        std::cout << "First call to multipleStatics()" << std::endl;
        first_call = false;
    }
    
    std::cout << "Call #" << call_count << ": " << message << std::endl;
}

// Class demonstrating static members
class StaticDemo {
private:
    static int object_count;     // Static member declaration
    int instance_id;
    
public:
    // Constructor
    StaticDemo() : instance_id(++object_count) {
        std::cout << "StaticDemo object #" << instance_id << " created" << std::endl;
    }
    
    // Destructor
    ~StaticDemo() {
        std::cout << "StaticDemo object #" << instance_id << " destroyed" << std::endl;
        object_count--;
    }
    
    // Static member function
    static int getObjectCount() {
        return object_count;
    }
    
    // Instance member function
    int getInstanceId() const {
        return instance_id;
    }
    
    // Static member function accessing only static data
    static void printObjectCount() {
        std::cout << "Current object count: " << object_count << std::endl;
        // std::cout << instance_id;  // Error: cannot access non-static member
    }
};

// Static member definition (required outside class)
int StaticDemo::object_count = 0;

// Template function with static variables
template<typename T>
void templateStatic(T value) {
    static int call_count = 0;
    static T last_value{};
    
    call_count++;
    std::cout << "Template static call #" << call_count 
              << ", current: " << value 
              << ", last: " << last_value << std::endl;
    last_value = value;
}

// Function demonstrating static initialization order
class InitOrderDemo {
public:
    InitOrderDemo(const std::string& name) {
        std::cout << "InitOrderDemo '" << name << "' constructed" << std::endl;
    }
};

static InitOrderDemo static_obj1("Global Static 1");
InitOrderDemo global_obj("Global Object");
static InitOrderDemo static_obj2("Global Static 2");

// Function with static local object
void staticLocalObject() {
    std::cout << "\nEntering staticLocalObject()" << std::endl;
    static InitOrderDemo local_static("Local Static");
    std::cout << "Exiting staticLocalObject()" << std::endl;
}

// Singleton pattern using static
class Singleton {
private:
    static Singleton* instance;
    int value;
    
    // Private constructor
    Singleton(int val = 0) : value(val) {
        std::cout << "Singleton instance created with value: " << value << std::endl;
    }
    
public:
    // Get singleton instance
    static Singleton* getInstance(int val = 42) {
        if (instance == nullptr) {
            instance = new Singleton(val);
        }
        return instance;
    }
    
    // Better singleton using static local (C++11 thread-safe)
    static Singleton& getInstanceModern(int val = 42) {
        static Singleton instance(val);  // Constructed on first call
        return instance;
    }
    
    void setValue(int val) { value = val; }
    int getValue() const { return value; }
    
    ~Singleton() {
        std::cout << "Singleton instance destroyed" << std::endl;
    }
};

// Static member definition
Singleton* Singleton::instance = nullptr;

int main() {
    std::cout << "=== STATIC STORAGE CLASS DEMO ===" << std::endl;
    
    // 1. Static local variables
    std::cout << "\n1. Static Local Variables:" << std::endl;
    
    std::cout << "Calling counter() multiple times:" << std::endl;
    counter();  // count = 1
    counter();  // count = 2
    counter();  // count = 3
    
    std::cout << "\nCalling multipleStatics():" << std::endl;
    multipleStatics();  // First call
    multipleStatics();  // Second call
    multipleStatics();  // Third call
    
    // 2. Static global variables and functions
    std::cout << "\n2. Static Global Variables and Functions:" << std::endl;
    
    std::cout << "Global variable: " << global_var << std::endl;
    std::cout << "Static global variable: " << static_global << std::endl;
    
    static_function();  // Call static function
    
    // Note: static_global and static_function are not visible outside this file
    
    // 3. Static class members
    std::cout << "\n3. Static Class Members:" << std::endl;
    
    StaticDemo::printObjectCount();  // 0 objects
    
    {
        StaticDemo obj1;             // Object 1 created
        StaticDemo::printObjectCount();
        
        {
            StaticDemo obj2;         // Object 2 created
            StaticDemo obj3;         // Object 3 created
            StaticDemo::printObjectCount();
            
            std::cout << "obj1 ID: " << obj1.getInstanceId() << std::endl;
            std::cout << "obj2 ID: " << obj2.getInstanceId() << std::endl;
            std::cout << "obj3 ID: " << obj3.getInstanceId() << std::endl;
        }  // obj2 and obj3 destroyed
        
        StaticDemo::printObjectCount();
    }  // obj1 destroyed
    
    StaticDemo::printObjectCount();  // Back to 0
    
    // 4. Template static variables
    std::cout << "\n4. Template Static Variables:" << std::endl;
    
    templateStatic(10);        // int template instantiation
    templateStatic(20);        // Same int template
    templateStatic(3.14);      // double template instantiation  
    templateStatic(2.71);      // Same double template
    templateStatic(10);        // Back to int template
    
    // 5. Static initialization order
    std::cout << "\n5. Static Initialization:" << std::endl;
    std::cout << "Global static objects initialized before main()" << std::endl;
    
    staticLocalObject();       // First call - static local constructed
    staticLocalObject();       // Second call - static local already exists
    
    // 6. Singleton pattern with static
    std::cout << "\n6. Singleton Pattern:" << std::endl;
    
    // Traditional singleton
    Singleton* s1 = Singleton::getInstance(100);
    Singleton* s2 = Singleton::getInstance(200);  // Value ignored - same instance
    
    std::cout << "s1 value: " << s1->getValue() << std::endl;
    std::cout << "s2 value: " << s2->getValue() << std::endl;
    std::cout << "s1 == s2: " << (s1 == s2 ? "true" : "false") << std::endl;
    
    // Modern singleton (thread-safe in C++11)
    Singleton& ms1 = Singleton::getInstanceModern(300);
    Singleton& ms2 = Singleton::getInstanceModern(400);  // Value ignored
    
    std::cout << "Modern singleton ms1 value: " << ms1.getValue() << std::endl;
    std::cout << "Modern singleton ms2 value: " << ms2.getValue() << std::endl;
    std::cout << "&ms1 == &ms2: " << (&ms1 == &ms2 ? "true" : "false") << std::endl;
    
    // 7. Static variables in loops
    std::cout << "\n7. Static Variables in Loops:" << std::endl;
    
    for (int i = 0; i < 3; ++i) {
        static int loop_static = 0;
        loop_static += 10;
        std::cout << "Loop iteration " << i << ", static value: " << loop_static << std::endl;
    }
    
    // 8. Static arrays and containers
    std::cout << "\n8. Static Arrays and Containers:" << std::endl;
    
    auto getStaticVector = []() -> std::vector<int>& {
        static std::vector<int> vec = {1, 2, 3, 4, 5};
        return vec;
    };
    
    auto& vec = getStaticVector();
    std::cout << "Static vector size: " << vec.size() << std::endl;
    vec.push_back(6);
    
    auto& vec2 = getStaticVector();  // Same vector
    std::cout << "Static vector size after modification: " << vec2.size() << std::endl;
    
    // 9. Static function variables with different function calls
    std::cout << "\n9. Function-specific Static Variables:" << std::endl;
    
    auto func1 = []() {
        static int count = 0;
        return ++count;
    };
    
    auto func2 = []() {
        static int count = 100;  // Different static variable
        return ++count;
    };
    
    std::cout << "func1(): " << func1() << ", " << func1() << ", " << func1() << std::endl;
    std::cout << "func2(): " << func2() << ", " << func2() << ", " << func2() << std::endl;
    
    // 10. Static vs automatic storage comparison
    std::cout << "\n10. Static vs Automatic Storage:" << std::endl;
    
    auto compareStorage = [](int input) {
        int automatic_var = input;     // New variable each call
        static int static_var = input; // Initialized only once
        
        automatic_var += 10;
        static_var += 10;
        
        std::cout << "Input: " << input 
                  << ", Automatic: " << automatic_var 
                  << ", Static: " << static_var << std::endl;
    };
    
    compareStorage(1);   // auto=11, static=11
    compareStorage(2);   // auto=12, static=21  
    compareStorage(3);   // auto=13, static=31
    
    std::cout << "\n=== STATIC STORAGE CLASS BENEFITS ===" << std::endl;
    std::cout << "✅ Persistent state between function calls" << std::endl;
    std::cout << "✅ Single instance shared across all calls" << std::endl;
    std::cout << "✅ Internal linkage for file-scope privacy" << std::endl;
    std::cout << "✅ Automatic initialization (once)" << std::endl;
    std::cout << "✅ Thread-safe initialization in C++11 (function-local)" << std::endl;
    
    std::cout << "\n=== STATIC STORAGE CLASS CONSIDERATIONS ===" << std::endl;
    std::cout << "⚠️  Static variables persist for program lifetime" << std::endl;
    std::cout << "⚠️  Initialization order fiasco with global statics" << std::endl;
    std::cout << "⚠️  Memory usage - variables never deallocated" << std::endl;
    std::cout << "⚠️  Thread safety concerns (except function-local in C++11+)" << std::endl;
    std::cout << "⚠️  Testing challenges - state persists between tests" << std::endl;
    
    return 0;
}

/*
Static Storage Class Summary:

1. Static Local Variables:
   - Initialized once, persist between function calls
   - Stored in data segment, not stack
   - Thread-safe initialization in C++11+ (function-local)

2. Static Global Variables:
   - Internal linkage (file scope only)
   - Not visible in other translation units
   - Useful for file-private globals

3. Static Class Members:
   - Shared by all instances of the class
   - Must be defined outside class (except inline static)
   - Can be accessed without object instance

4. Common Use Cases:
   - Counters and accumulators
   - Caching expensive computations
   - Singleton pattern implementation
   - Function-local constants
   - File-scope utility functions

5. Memory Layout:
   - Stored in data segment (initialized) or BSS segment (zero-initialized)
   - Exists for entire program lifetime
   - Not allocated on stack or heap

6. Best Practices:
   - Prefer function-local static over global static
   - Use static for file-scope privacy
   - Be aware of initialization order issues
   - Consider thread safety implications
   - Use sparingly - can make testing difficult
*/
