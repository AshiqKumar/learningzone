// C++11 Initializer Lists - Uniform Initialization
// Compile: g++ -std=c++11 -o init_list_demo initializer_list_demo.cpp
// Run: ./init_list_demo

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <initializer_list>
#include <algorithm>

// Custom class to demonstrate initializer list constructor
class Point {
private:
    double x_, y_;
    
public:
    // Default constructor
    Point() : x_(0), y_(0) {
        std::cout << "Point() - default constructor" << std::endl;
    }
    
    // Regular constructor
    Point(double x, double y) : x_(x), y_(y) {
        std::cout << "Point(" << x_ << ", " << y_ << ") - regular constructor" << std::endl;
    }
    
    // Initializer list constructor
    Point(std::initializer_list<double> coords) {
        std::cout << "Point(initializer_list) - ";
        auto it = coords.begin();
        if (coords.size() >= 1) {
            x_ = *it++;
        } else {
            x_ = 0;
        }
        
        if (coords.size() >= 2) {
            y_ = *it;
        } else {
            y_ = 0;
        }
        std::cout << "(" << x_ << ", " << y_ << ")" << std::endl;
    }
    
    void display() const {
        std::cout << "Point(" << x_ << ", " << y_ << ")" << std::endl;
    }
    
    double getX() const { return x_; }
    double getY() const { return y_; }
};

// Custom container class with initializer list
class IntVector {
private:
    std::vector<int> data_;
    
public:
    // Constructor with initializer list
    IntVector(std::initializer_list<int> list) : data_(list) {
        std::cout << "IntVector created with " << list.size() << " elements" << std::endl;
    }
    
    // Add method that accepts initializer list
    void append(std::initializer_list<int> list) {
        for (auto val : list) {
            data_.push_back(val);
        }
    }
    
    void display() const {
        std::cout << "IntVector: ";
        for (auto val : data_) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    size_t size() const { return data_.size(); }
    
    // Iterator support for range-based for loop
    auto begin() const -> decltype(data_.begin()) { return data_.begin(); }
    auto end() const -> decltype(data_.end()) { return data_.end(); }
};

// Function that accepts initializer list
void print_numbers(std::initializer_list<int> numbers) {
    std::cout << "Function received: ";
    for (auto num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== C++11 INITIALIZER LISTS DEMO ===" << std::endl;
    
    // 1. Uniform initialization syntax
    std::cout << "\n1. Uniform Initialization Syntax:" << std::endl;
    
    // Built-in types
    int a{42};              // Same as int a = 42;
    double b{3.14};         // Same as double b = 3.14;
    char c{'X'};            // Same as char c = 'X';
    
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    
    // Arrays with initializer lists
    int arr1[5]{1, 2, 3, 4, 5};    // C++11 style
    int arr2[]{10, 20, 30};        // Size deduced
    
    std::cout << "arr1: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "arr2: ";
    for (int val : arr2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // 2. STL containers with initializer lists
    std::cout << "\n2. STL Containers with Initializer Lists:" << std::endl;
    
    // vector
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::cout << "vector: ";
    for (auto val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // set
    std::set<std::string> words{"hello", "world", "C++11", "rocks"};
    std::cout << "set: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    
    // map
    std::map<std::string, int> ages{
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };
    
    std::cout << "map:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << "  " << pair.first << " is " << pair.second << " years old" << std::endl;
    }
    
    // 3. Custom class with initializer lists
    std::cout << "\n3. Custom Classes with Initializer Lists:" << std::endl;
    
    Point p1;                    // Default constructor
    Point p2(1.0, 2.0);         // Regular constructor
    Point p3{3.0, 4.0};         // Initializer list constructor
    Point p4{5.0};              // Initializer list with one element
    Point p5{};                 // Initializer list (empty)
    
    std::cout << "Points created:" << std::endl;
    p1.display();
    p2.display();
    p3.display();
    p4.display();
    p5.display();
    
    // 4. Custom container with initializer list
    std::cout << "\n4. Custom Container with Initializer List:" << std::endl;
    
    IntVector myVec{10, 20, 30, 40, 50};
    myVec.display();
    
    myVec.append({60, 70, 80});
    myVec.display();
    
    // 5. Function parameters with initializer lists
    std::cout << "\n5. Functions with Initializer List Parameters:" << std::endl;
    
    print_numbers({1, 2, 3, 4, 5});
    print_numbers({100, 200});
    print_numbers({});  // Empty list
    
    // 6. Preventing narrowing conversions
    std::cout << "\n6. Preventing Narrowing Conversions:" << std::endl;
    
    // These work fine
    int x = 3.14;        // Narrowing allowed with = syntax
    std::cout << "x = " << x << " (narrowed from 3.14)" << std::endl;
    
    // These would cause compilation errors (narrowing prevention)
    // int y{3.14};      // Error: narrowing conversion
    // char z{300};      // Error: value too large for char
    
    std::cout << "Initializer lists prevent dangerous narrowing conversions!" << std::endl;
    
    // 7. Return values with initializer lists
    std::cout << "\n7. Return Values with Initializer Lists:" << std::endl;
    
    auto create_vector = []() -> std::vector<int> {
        return {1, 4, 9, 16, 25};  // Return initializer list
    };
    
    auto squares = create_vector();
    std::cout << "Returned vector: ";
    for (auto val : squares) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // 8. Initializer lists with algorithms
    std::cout << "\n8. Initializer Lists with Algorithms:" << std::endl;
    
    // Find maximum in initializer list
    auto max_val = std::max({10, 5, 20, 15, 8});
    std::cout << "Maximum value: " << max_val << std::endl;
    
    // Find minimum in initializer list
    auto min_val = std::min({10, 5, 20, 15, 8});
    std::cout << "Minimum value: " << min_val << std::endl;
    
    // Sort with initializer list
    std::vector<int> to_sort{64, 34, 25, 12, 22, 11, 90};
    std::cout << "Before sorting: ";
    for (auto val : to_sort) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::sort(to_sort.begin(), to_sort.end());
    std::cout << "After sorting: ";
    for (auto val : to_sort) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // 9. Nested initializer lists
    std::cout << "\n9. Nested Initializer Lists:" << std::endl;
    
    std::vector<std::vector<int>> matrix{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    std::cout << "Matrix:" << std::endl;
    for (const auto& row : matrix) {
        std::cout << "  ";
        for (auto val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    // Complex nested structure
    std::map<std::string, std::vector<int>> groups{
        {"evens", {2, 4, 6, 8, 10}},
        {"odds", {1, 3, 5, 7, 9}},
        {"primes", {2, 3, 5, 7, 11}}
    };
    
    std::cout << "Groups:" << std::endl;
    for (const auto& group : groups) {
        std::cout << "  " << group.first << ": ";
        for (auto val : group.second) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    // 10. Aggregate initialization
    std::cout << "\n10. Aggregate Initialization:" << std::endl;
    
    struct Person {
        std::string name;
        int age;
        double height;
    };
    
    // C++11 aggregate initialization
    Person person1{"Alice", 30, 5.6};
    Person person2{"Bob", 25, 6.0};
    
    std::cout << "Person 1: " << person1.name << ", " << person1.age << ", " << person1.height << std::endl;
    std::cout << "Person 2: " << person2.name << ", " << person2.age << ", " << person2.height << std::endl;
    
    // Array of aggregates
    Person people[]{
        {"Charlie", 35, 5.8},
        {"Diana", 28, 5.4},
        {"Eve", 32, 5.7}
    };
    
    std::cout << "People array:" << std::endl;
    for (const auto& person : people) {
        std::cout << "  " << person.name << " (" << person.age << " years, " << person.height << " ft)" << std::endl;
    }
    
    std::cout << "\n=== INITIALIZER LIST BENEFITS ===" << std::endl;
    std::cout << "✅ Uniform initialization syntax for all types" << std::endl;
    std::cout << "✅ Convenient container initialization" << std::endl;
    std::cout << "✅ Prevents narrowing conversions" << std::endl;
    std::cout << "✅ Direct initialization of aggregates" << std::endl;
    std::cout << "✅ Cleaner, more readable code" << std::endl;
    std::cout << "✅ Works with custom classes and STL containers" << std::endl;
    std::cout << "⚠️  Prefer {} over () for initialization" << std::endl;
    std::cout << "⚠️  Be aware of constructor overload resolution" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -o init_list_demo initializer_list_demo.cpp
./init_list_demo

Initializer List Features:
1. Uniform initialization syntax: Type var{value};
2. Container initialization: std::vector<int> v{1,2,3};
3. Aggregate initialization: struct S{1,2,3};
4. Function parameters: func({1,2,3});
5. Return values: return {1,2,3};
6. Prevents narrowing conversions
7. Works with custom classes via std::initializer_list<T>

Benefits:
- Consistent syntax across all types
- More safety (prevents narrowing)
- Cleaner, more expressive code
- Direct aggregate initialization
*/
