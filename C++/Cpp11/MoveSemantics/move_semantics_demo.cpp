// C++11 Move Semantics - Rvalue References and Move Operations
// Compile: g++ -std=c++11 -o move_demo move_semantics_demo.cpp
// Run: ./move_demo

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>
#include <chrono>

// Example class to demonstrate move semantics
class Resource {
private:
    std::string name_;
    int* data_;
    size_t size_;
    
public:
    // Constructor
    Resource(const std::string& name, size_t size) 
        : name_(name), size_(size), data_(new int[size]) {
        
        // Initialize data
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = static_cast<int>(i * i);
        }
        
        std::cout << "Resource '" << name_ << "' constructed (size: " << size_ << ")" << std::endl;
    }
    
    // Copy constructor (expensive)
    Resource(const Resource& other) 
        : name_(other.name_ + "_copy"), size_(other.size_), data_(new int[other.size_]) {
        
        std::cout << "Resource COPY constructor: " << name_ << std::endl;
        
        // Deep copy
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
    // Move constructor (efficient) - C++11
    Resource(Resource&& other) noexcept 
        : name_(std::move(other.name_)), size_(other.size_), data_(other.data_) {
        
        std::cout << "Resource MOVE constructor: " << name_ << std::endl;
        
        // Transfer ownership
        other.data_ = nullptr;
        other.size_ = 0;
        other.name_ += "_moved";
    }
    
    // Copy assignment operator (expensive)
    Resource& operator=(const Resource& other) {
        std::cout << "Resource COPY assignment: " << other.name_ << " -> " << name_ << std::endl;
        
        if (this != &other) {
            delete[] data_;
            
            name_ = other.name_ + "_copied";
            size_ = other.size_;
            data_ = new int[size_];
            
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    
    // Move assignment operator (efficient) - C++11
    Resource& operator=(Resource&& other) noexcept {
        std::cout << "Resource MOVE assignment: " << other.name_ << " -> " << name_ << std::endl;
        
        if (this != &other) {
            delete[] data_;
            
            // Move data
            name_ = std::move(other.name_);
            size_ = other.size_;
            data_ = other.data_;
            
            // Reset source
            other.data_ = nullptr;
            other.size_ = 0;
            other.name_ += "_moved";
        }
        return *this;
    }
    
    // Destructor
    ~Resource() {
        if (data_) {
            std::cout << "Resource '" << name_ << "' destroyed" << std::endl;
        } else {
            std::cout << "Resource '" << name_ << "' destroyed (moved-from state)" << std::endl;
        }
        delete[] data_;
    }
    
    // Utility methods
    const std::string& getName() const { return name_; }
    size_t getSize() const { return size_; }
    
    void display() const {
        if (data_) {
            std::cout << "Resource '" << name_ << "' has " << size_ << " elements: ";
            size_t show = std::min(size_, static_cast<size_t>(5));
            for (size_t i = 0; i < show; ++i) {
                std::cout << data_[i] << " ";
            }
            if (size_ > 5) std::cout << "...";
            std::cout << std::endl;
        } else {
            std::cout << "Resource '" << name_ << "' is in moved-from state" << std::endl;
        }
    }
};

// Function to demonstrate different return patterns
Resource createResource(const std::string& name, size_t size) {
    std::cout << "Creating resource in function..." << std::endl;
    return Resource(name, size);  // RVO (Return Value Optimization) may apply
}

Resource createAndModify(const std::string& name, size_t size) {
    std::cout << "Creating and modifying resource..." << std::endl;
    Resource res(name, size);
    // Some modifications...
    return res;  // NRVO (Named Return Value Optimization) may apply
}

// Utility functions to demonstrate lvalue vs rvalue
void processResource(const Resource& res) {
    std::cout << "Processing lvalue reference: " << res.getName() << std::endl;
}

void processResource(Resource&& res) {
    std::cout << "Processing rvalue reference: " << res.getName() << std::endl;
    // Could move from res here
}

// Template function to demonstrate perfect forwarding (preview)
template<typename T>
void forwardToProcess(T&& arg) {
    std::cout << "Forwarding to process..." << std::endl;
    processResource(std::forward<T>(arg));
}

int main() {
    std::cout << "=== C++11 MOVE SEMANTICS DEMO ===" << std::endl;
    
    // 1. Basic rvalue references
    std::cout << "\n1. Rvalue References Basics:" << std::endl;
    
    int x = 10;
    int& lref = x;        // Lvalue reference
    int&& rref = 20;      // Rvalue reference to temporary
    // int&& rref2 = x;   // Error: cannot bind rvalue reference to lvalue
    int&& rref3 = std::move(x);  // std::move converts lvalue to rvalue
    
    std::cout << "lref = " << lref << std::endl;
    std::cout << "rref = " << rref << std::endl;
    std::cout << "rref3 = " << rref3 << std::endl;
    
    // 2. Move constructor demonstration
    std::cout << "\n2. Move Constructor vs Copy Constructor:" << std::endl;
    
    Resource original("original", 1000);
    std::cout << "\nCopying resource:" << std::endl;
    Resource copied = original;  // Copy constructor
    
    std::cout << "\nMoving resource:" << std::endl;
    Resource moved = std::move(original);  // Move constructor
    
    std::cout << "\nAfter operations:" << std::endl;
    copied.display();
    moved.display();
    original.display();  // Should be in moved-from state
    
    // 3. Move assignment demonstration
    std::cout << "\n3. Move Assignment vs Copy Assignment:" << std::endl;
    
    Resource res1("res1", 500);
    Resource res2("res2", 300);
    Resource res3("res3", 200);
    
    std::cout << "\nCopy assignment:" << std::endl;
    res2 = res1;  // Copy assignment
    
    std::cout << "\nMove assignment:" << std::endl;
    res3 = std::move(res1);  // Move assignment
    
    std::cout << "\nAfter assignments:" << std::endl;
    res1.display();
    res2.display();
    res3.display();
    
    // 4. Return value optimization and move semantics
    std::cout << "\n4. Function Returns and Move Semantics:" << std::endl;
    
    std::cout << "\nReturning by value (RVO may apply):" << std::endl;
    Resource returned = createResource("returned", 100);
    returned.display();
    
    std::cout << "\nReturning named object (NRVO may apply):" << std::endl;
    Resource named_return = createAndModify("named", 100);
    named_return.display();
    
    // 5. STL containers and move semantics
    std::cout << "\n5. STL Containers and Move Semantics:" << std::endl;
    
    std::vector<Resource> resources;
    resources.reserve(3);  // Avoid reallocation
    
    std::cout << "\nPushing resources to vector:" << std::endl;
    resources.emplace_back("vector1", 50);  // Construct in place
    resources.push_back(Resource("vector2", 60));  // Move temporary
    
    Resource temp("vector3", 70);
    resources.push_back(std::move(temp));  // Explicit move
    
    std::cout << "\nVector contents:" << std::endl;
    for (const auto& res : resources) {
        res.display();
    }
    temp.display();  // Should be moved-from
    
    // 6. std::move and move-only types
    std::cout << "\n6. Move-Only Types (unique_ptr example):" << std::endl;
    
    std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
    std::cout << "ptr1 value: " << *ptr1 << std::endl;
    
    // std::unique_ptr<int> ptr2 = ptr1;  // Error: no copy constructor
    std::unique_ptr<int> ptr2 = std::move(ptr1);  // Move is OK
    
    std::cout << "After move:" << std::endl;
    std::cout << "ptr1 is " << (ptr1 ? "valid" : "null") << std::endl;
    std::cout << "ptr2 value: " << *ptr2 << std::endl;
    
    // 7. String move semantics
    std::cout << "\n7. String Move Semantics:" << std::endl;
    
    std::string str1 = "This is a very long string that will definitely not fit in SSO";
    std::cout << "Original string length: " << str1.length() << std::endl;
    
    std::string str2 = str1;              // Copy
    std::string str3 = std::move(str1);   // Move
    
    std::cout << "After operations:" << std::endl;
    std::cout << "str1 length: " << str1.length() << " ('" << str1 << "')" << std::endl;
    std::cout << "str2 length: " << str2.length() << std::endl;
    std::cout << "str3 length: " << str3.length() << std::endl;
    
    // 8. Overload resolution with rvalue references
    std::cout << "\n8. Overload Resolution:" << std::endl;
    
    Resource lvalue_res("lvalue", 10);
    
    std::cout << "\nCalling with lvalue:" << std::endl;
    processResource(lvalue_res);
    
    std::cout << "\nCalling with rvalue:" << std::endl;
    processResource(Resource("rvalue", 10));
    
    std::cout << "\nCalling with moved lvalue:" << std::endl;
    processResource(std::move(lvalue_res));
    
    // 9. Perfect forwarding preview
    std::cout << "\n9. Perfect Forwarding Preview:" << std::endl;
    
    Resource forward_test("forward", 5);
    
    std::cout << "\nForwarding lvalue:" << std::endl;
    forwardToProcess(forward_test);
    
    std::cout << "\nForwarding rvalue:" << std::endl;
    forwardToProcess(Resource("temp", 5));
    
    // 10. Performance comparison
    std::cout << "\n10. Performance Comparison:" << std::endl;
    
    const int iterations = 1000;
    
    // Measure copy performance
    auto start = std::chrono::high_resolution_clock::now();
    {
        std::vector<Resource> copy_vector;
        for (int i = 0; i < iterations; ++i) {
            Resource temp("perf_test", 100);
            copy_vector.push_back(temp);  // Copy
        }
    }
    auto copy_time = std::chrono::high_resolution_clock::now() - start;
    
    // Measure move performance
    start = std::chrono::high_resolution_clock::now();
    {
        std::vector<Resource> move_vector;
        for (int i = 0; i < iterations; ++i) {
            Resource temp("perf_test", 100);
            move_vector.push_back(std::move(temp));  // Move
        }
    }
    auto move_time = std::chrono::high_resolution_clock::now() - start;
    
    std::cout << "Copy time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(copy_time).count() 
              << " ms" << std::endl;
    std::cout << "Move time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(move_time).count() 
              << " ms" << std::endl;
    
    std::cout << "\n=== MOVE SEMANTICS BENEFITS ===" << std::endl;
    std::cout << "✅ Eliminates unnecessary copies" << std::endl;
    std::cout << "✅ Improves performance for expensive-to-copy objects" << std::endl;
    std::cout << "✅ Enables move-only types (unique_ptr, etc.)" << std::endl;
    std::cout << "✅ Automatic optimization in many scenarios" << std::endl;
    std::cout << "✅ Backward compatible with existing code" << std::endl;
    std::cout << "⚠️  Use std::move() to explicitly convert lvalue to rvalue" << std::endl;
    std::cout << "⚠️  Don't access moved-from objects (except for destruction)" << std::endl;
    std::cout << "⚠️  Implement move operations as noexcept when possible" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -o move_demo move_semantics_demo.cpp
./move_demo

Move Semantics Key Concepts:
1. Rvalue References (T&&): Can bind to temporaries and moved values
2. Move Constructor: Transfer resources instead of copying
3. Move Assignment: Transfer resources in assignment
4. std::move(): Convert lvalue to rvalue reference
5. Move-Only Types: Classes that can't be copied, only moved

Benefits:
- Significant performance improvement for resource-heavy classes
- Enables efficient transfer of ownership
- Reduces memory allocations and deallocations
- Essential for modern C++ idioms (RAII, smart pointers)

Best Practices:
- Mark move operations as noexcept when possible
- Always leave moved-from objects in valid but unspecified state
- Use std::move() sparingly and only when you mean it
- Let compiler optimizations (RVO/NRVO) work first
*/
