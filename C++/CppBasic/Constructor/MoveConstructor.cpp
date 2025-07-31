/*
MOVE CONSTRUCTOR COMPREHENSIVE EXAMPLES
======================================

The move constructor allows efficient transfer of resources from temporary or expiring objects, 
avoiding unnecessary deep copies. This is especially important for:
- Managing dynamic memory efficiently
- Containers like std::vector that may need to move elements around
- Creating move-only types
- Performance optimization in modern C++

This file demonstrates:
1. Basic move constructor usage with containers
2. Move-only classes with deleted copy operations
3. Move assignment operators
4. Performance comparison between copy and move semantics
*/

#include<iostream>
#include<vector>
#include<string>
#include<chrono>
#include<algorithm>
using namespace std;
using namespace std::chrono;

// ============================================================================
// EXAMPLE 1: Basic Move Constructor with Container Operations
// ============================================================================

class BasicDummy
{
private:
    int a, b;
    string name;
    
public:
    // Default constructor
    BasicDummy() : a(0), b(0), name("default") { 
        cout << "BasicDummy default constructor: " << name << endl; 
    }
    
    // Parameterized constructor
    BasicDummy(int x, int y, const string& n) : a(x), b(y), name(n) { 
        cout << "BasicDummy parameterized constructor: " << name << endl; 
    }
    
    // Copy constructor
    BasicDummy(const BasicDummy &x) : a(x.a), b(x.b), name(x.name + "_copy") { 
        cout << "BasicDummy copy constructor: " << name << endl; 
    }
    
    // Move constructor
    BasicDummy(BasicDummy &&x) noexcept : a(move(x.a)), b(move(x.b)), name(move(x.name)) { 
        cout << "BasicDummy move constructor: " << name << endl;
        // Reset moved-from object to valid state
        x.a = 0;
        x.b = 0;
        x.name = "moved_from";
    }
    
    // Copy assignment operator
    BasicDummy& operator=(const BasicDummy& x) {
        if (this != &x) {
            a = x.a;
            b = x.b;
            name = x.name + "_assigned";
            cout << "BasicDummy copy assignment: " << name << endl;
        }
        return *this;
    }
    
    // Move assignment operator
    BasicDummy& operator=(BasicDummy&& x) noexcept {
        if (this != &x) {
            a = x.a;
            b = x.b;
            name = move(x.name);
            cout << "BasicDummy move assignment: " << name << endl;
            // Reset moved-from object
            x.a = 0;
            x.b = 0;
            x.name = "moved_from";
        }
        return *this;
    }
    
    // Destructor
    ~BasicDummy() { 
        cout << "BasicDummy destructor: " << name << endl; 
    }
    
    // Getter for demonstration
    const string& getName() const { return name; }
    void setName(const string& n) { name = n; }
};

// ============================================================================
// EXAMPLE 2: Move-Only Class (Deleted Copy Operations)
// ============================================================================

class MoveOnlyResource
{
private:
    int *data;
    size_t size;
    string identifier;
    
public:
    // Constructor
    MoveOnlyResource(size_t s = 10, const string& id = "resource") 
        : data(new int[s]), size(s), identifier(id) {
        // Initialize with some data
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i * 10);
        }
        cout << "MoveOnlyResource created: " << identifier << " (size: " << size << ")" << endl;
    }
    
    // Destructor
    ~MoveOnlyResource() { 
        if (data) {
            cout << "MoveOnlyResource destroyed: " << identifier << " (size: " << size << ")" << endl;
            delete[] data; 
        } else {
            cout << "MoveOnlyResource destroyed: " << identifier << " (moved-from state)" << endl;
        }
    }
    
    // Delete copy constructor and copy assignment (move-only)
    MoveOnlyResource(const MoveOnlyResource&) = delete;
    MoveOnlyResource& operator=(const MoveOnlyResource&) = delete;
    
    // Move constructor
    MoveOnlyResource(MoveOnlyResource&& other) noexcept
        : data(other.data), size(other.size), identifier(move(other.identifier)) {
        cout << "MoveOnlyResource move constructor: " << identifier << endl;
        // Reset moved-from object to valid state
        other.data = nullptr;
        other.size = 0;
        other.identifier = "moved_from";
    }
    
    // Move assignment operator
    MoveOnlyResource& operator=(MoveOnlyResource&& other) noexcept {
        if (this != &other) {
            // Clean up existing resource
            delete[] data;
            
            // Move from other
            data = other.data;
            size = other.size;
            identifier = move(other.identifier);
            
            cout << "MoveOnlyResource move assignment: " << identifier << endl;
            
            // Reset moved-from object
            other.data = nullptr;
            other.size = 0;
            other.identifier = "moved_from";
        }
        return *this;
    }
    
    // Utility methods
    void printData() const {
        cout << "Resource " << identifier << " data: ";
        if (data && size > 0) {
            for (size_t i = 0; i < min(size, size_t(5)); ++i) {
                cout << data[i] << " ";
            }
            if (size > 5) cout << "...";
        } else {
            cout << "(no data)";
        }
        cout << endl;
    }
    
    const string& getId() const { return identifier; }
    size_t getSize() const { return size; }
};

// ============================================================================
// EXAMPLE 3: Performance Comparison Class
// ============================================================================

class PerformanceTest
{
private:
    vector<int> largeData;
    string description;
    
public:
    // Constructor
    PerformanceTest(size_t dataSize = 1000000, const string& desc = "test") 
        : largeData(dataSize), description(desc) {
        // Fill with random-ish data
        for (size_t i = 0; i < dataSize; ++i) {
            largeData[i] = static_cast<int>(i % 1000);
        }
        cout << "PerformanceTest created: " << description << " (size: " << dataSize << ")" << endl;
    }
    
    // Copy constructor (potentially expensive)
    PerformanceTest(const PerformanceTest& other) 
        : largeData(other.largeData), description(other.description + "_copy") {
        cout << "PerformanceTest COPY constructor: " << description << " (size: " << largeData.size() << ")" << endl;
    }
    
    // Move constructor (efficient)
    PerformanceTest(PerformanceTest&& other) noexcept
        : largeData(move(other.largeData)), description(move(other.description)) {
        cout << "PerformanceTest MOVE constructor: " << description << " (size: " << largeData.size() << ")" << endl;
        other.description = "moved_from";
    }
    
    // Copy assignment
    PerformanceTest& operator=(const PerformanceTest& other) {
        if (this != &other) {
            largeData = other.largeData;
            description = other.description + "_assigned";
            cout << "PerformanceTest COPY assignment: " << description << endl;
        }
        return *this;
    }
    
    // Move assignment
    PerformanceTest& operator=(PerformanceTest&& other) noexcept {
        if (this != &other) {
            largeData = move(other.largeData);
            description = move(other.description);
            cout << "PerformanceTest MOVE assignment: " << description << endl;
            other.description = "moved_from";
        }
        return *this;
    }
    
    ~PerformanceTest() {
        cout << "PerformanceTest destroyed: " << description << endl;
    }
    
    const string& getDescription() const { return description; }
    size_t getDataSize() const { return largeData.size(); }
};

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

void demonstrateBasicMoveConstructor() {
    cout << "\n=== BASIC MOVE CONSTRUCTOR WITH CONTAINERS ===\n";
    
    vector<BasicDummy> v1;
    cout << "\n1. Creating temporary objects for push_back:\n";
    v1.push_back(BasicDummy(1, 2, "first"));
    cout << "\n2. Adding another temporary:\n";
    v1.push_back(BasicDummy(3, 4, "second"));
    
    cout << "\n3. Adding a named object (copy):\n";
    BasicDummy named(5, 6, "named");
    v1.push_back(named);
    
    cout << "\n4. Adding named object with explicit move:\n";
    v1.push_back(move(named));
    cout << "Named object after move: " << named.getName() << "\n";
    
    cout << "\n5. Vector contents will be destroyed when function ends:\n";
}

void demonstrateMoveOnlyClass() {
    cout << "\n=== MOVE-ONLY CLASS DEMONSTRATION ===\n";
    
    cout << "\n1. Creating move-only resource:\n";
    MoveOnlyResource resource1(5, "resource1");
    resource1.printData();
    
    cout << "\n2. Move constructing from resource1:\n";
    MoveOnlyResource resource2(move(resource1));
    resource2.printData();
    resource1.printData();  // Should show moved-from state
    
    cout << "\n3. Creating another resource and move assigning:\n";
    MoveOnlyResource resource3(3, "resource3");
    resource3.printData();
    
    resource3 = move(resource2);
    resource3.printData();
    resource2.printData();  // Should show moved-from state
    
    // These would cause compilation errors (copy operations deleted):
    // MoveOnlyResource copy1(resource3);     // ERROR
    // MoveOnlyResource copy2 = resource3;    // ERROR
    // resource1 = resource3;                 // ERROR (copy assignment)
    
    cout << "\n4. Resources will be destroyed when function ends:\n";
}

void demonstratePerformanceComparison() {
    cout << "\n=== PERFORMANCE COMPARISON ===\n";
    
    cout << "\n1. Creating large object:\n";
    PerformanceTest large(100000, "large_object");
    
    cout << "\n2. Copy vs Move timing:\n";
    
    // Time copy construction
    auto start = high_resolution_clock::now();
    PerformanceTest copy_constructed(large);
    auto end = high_resolution_clock::now();
    auto copy_time = duration_cast<microseconds>(end - start);
    
    // Time move construction
    start = high_resolution_clock::now();
    PerformanceTest move_constructed(move(large));
    end = high_resolution_clock::now();
    auto move_time = duration_cast<microseconds>(end - start);
    
    cout << "\nTiming Results:\n";
    cout << "Copy construction time: " << copy_time.count() << " microseconds\n";
    cout << "Move construction time: " << move_time.count() << " microseconds\n";
    
    auto move_count = move_time.count();
    if (move_count > 0) {
        cout << "Move is " << (copy_time.count() / move_count) << "x faster\n";
    } else {
        cout << "Move was too fast to measure accurately\n";
    }
    
    cout << "\n3. Original object after move: " << large.getDescription() << "\n";
    cout << "Objects will be destroyed when function ends:\n";
}

void demonstrateSTLContainerBehavior() {
    cout << "\n=== STL CONTAINER MOVE BEHAVIOR ===\n";
    
    cout << "\n1. Vector with move-enabled objects:\n";
    vector<BasicDummy> vec;
    vec.reserve(5);  // Prevent reallocation
    
    cout << "\nAdding elements:\n";
    vec.emplace_back(10, 20, "emplace1");
    vec.emplace_back(30, 40, "emplace2");
    
    cout << "\nUsing push_back with temporary:\n";
    vec.push_back(BasicDummy(50, 60, "temp"));
    
    cout << "\n2. Moving entire vector:\n";
    vector<BasicDummy> vec2 = move(vec);
    cout << "Original vector size after move: " << vec.size() << "\n";
    cout << "New vector size: " << vec2.size() << "\n";
    
    cout << "\n3. Vectors will be destroyed when function ends:\n";
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    cout << "COMPREHENSIVE MOVE CONSTRUCTOR DEMONSTRATION\n";
    cout << "===========================================\n";
    
    try {
        demonstrateBasicMoveConstructor();
        demonstrateMoveOnlyClass();
        demonstratePerformanceComparison();
        demonstrateSTLContainerBehavior();
        
        cout << "\n=== PROGRAM COMPLETED SUCCESSFULLY ===\n";
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

/*
COMPILATION AND EXECUTION:
=========================

Compile with:
g++ -std=c++17 -Wall -Wextra -O2 MoveConstructorA.cpp -o move_constructor_demo

Key Learning Points:
==================

1. MOVE SEMANTICS BENEFITS:
   - Avoids expensive deep copies
   - Transfers ownership of resources
   - Enables efficient container operations
   - Critical for performance optimization

2. MOVE CONSTRUCTOR SIGNATURE:
   - Takes rvalue reference (&&)
   - Should be marked noexcept when possible
   - Must leave moved-from object in valid state
   - Use std::move() for member transfers

3. MOVE-ONLY CLASSES:
   - Delete copy constructor and copy assignment
   - Useful for unique resources (file handles, sockets)
   - Forces explicit move semantics
   - Prevents accidental copying

4. BEST PRACTICES:
   - Always mark move operations noexcept when possible
   - Implement both move constructor and move assignment
   - Reset moved-from objects to valid state
   - Use std::move() when transferring ownership
   - Consider Rule of Five (destructor, copy ctor, copy assign, move ctor, move assign)

5. STL INTEGRATION:
   - STL containers automatically use move semantics
   - emplace_back() constructs in-place
   - Vector reallocation uses move when available
   - Move semantics enable efficient container operations
*/