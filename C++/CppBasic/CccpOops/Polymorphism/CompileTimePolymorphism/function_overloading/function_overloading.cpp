// function_overloading.cpp - Demonstrates function overloading in C++
// Compile: g++ -std=c++17 -Wall -Wextra function_overloading.cpp -o function_overloading

#include <iostream>
#include <string>
#include <vector>
#include <complex>

// 1. Basic Function Overloading - Same name, different parameters
namespace BasicOverloading {
    
    // Different number of parameters
    int add(int a, int b) {
        std::cout << "Adding two integers: ";
        return a + b;
    }
    
    int add(int a, int b, int c) {
        std::cout << "Adding three integers: ";
        return a + b + c;
    }
    
    // Different parameter types
    double add(double a, double b) {
        std::cout << "Adding two doubles: ";
        return a + b;
    }
    
    std::string add(const std::string& a, const std::string& b) {
        std::cout << "Concatenating strings: ";
        return a + b;
    }
    
    // Different parameter order (not recommended but possible)
    void display(int value, const std::string& label) {
        std::cout << label << ": " << value << std::endl;
    }
    
    void display(const std::string& label, int value) {
        std::cout << value << " (" << label << ")" << std::endl;
    }
}

// 2. Constructor Overloading
class Point {
private:
    double x, y;
    
public:
    // Default constructor
    Point() : x(0.0), y(0.0) {
        std::cout << "Point created at origin (0, 0)" << std::endl;
    }
    
    // Parameterized constructor - single parameter
    Point(double val) : x(val), y(val) {
        std::cout << "Point created at (" << x << ", " << y << ")" << std::endl;
    }
    
    // Parameterized constructor - two parameters
    Point(double x_val, double y_val) : x(x_val), y(y_val) {
        std::cout << "Point created at (" << x << ", " << y << ")" << std::endl;
    }
    
    // Copy constructor
    Point(const Point& other) : x(other.x), y(other.y) {
        std::cout << "Point copied to (" << x << ", " << y << ")" << std::endl;
    }
    
    void display() const {
        std::cout << "Point: (" << x << ", " << y << ")" << std::endl;
    }
    
    // Overloaded member functions
    double distance() const {
        return sqrt(x * x + y * y); // Distance from origin
    }
    
    double distance(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
};

// 3. Advanced Function Overloading with const and references
class Calculator {
public:
    // Const vs non-const overloading
    int calculate(int value) {
        std::cout << "Non-const calculate: ";
        return value * 2; // Can modify member variables
    }
    
    int calculate(int value) const {
        std::cout << "Const calculate: ";
        return value * 3; // Cannot modify member variables
    }
    
    // Reference vs value overloading
    void process(int value) {
        std::cout << "Processing by value: " << value << std::endl;
    }
    
    void process(const int& value) {
        std::cout << "Processing by const reference: " << value << std::endl;
    }
    
    void process(int& value) {
        std::cout << "Processing by reference (can modify): " << value << std::endl;
        value *= 10;
    }
};

// 4. Function Overloading with Different Return Types (NOT ALLOWED)
// This is not valid C++ - return type alone cannot distinguish overloads
/*
int getValue();
double getValue(); // ERROR: Cannot overload based on return type alone
*/

// 5. Function Template Overloading
template<typename T>
T maximum(T a, T b) {
    std::cout << "Template maximum: ";
    return (a > b) ? a : b;
}

// Specific overload for const char*
const char* maximum(const char* a, const char* b) {
    std::cout << "String maximum: ";
    return (strcmp(a, b) > 0) ? a : b;
}

// Overload for specific type
int maximum(int a, int b) {
    std::cout << "Integer maximum: ";
    return (a > b) ? a : b;
}

// 6. Variadic Function Overloading (C++11)
template<typename T>
T sum(T value) {
    return value; // Base case
}

template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...); // Recursive call
}

// 7. Perfect Forwarding Overload
template<typename T>
void forwardFunction(T&& value) {
    std::cout << "Perfect forwarding: ";
    if constexpr (std::is_lvalue_reference_v<T>) {
        std::cout << "L-value reference" << std::endl;
    } else {
        std::cout << "R-value reference" << std::endl;
    }
}

// 8. Function Overloading with Smart Pointers
void processPointer(std::unique_ptr<int> ptr) {
    std::cout << "Processing unique_ptr: " << *ptr << std::endl;
}

void processPointer(std::shared_ptr<int> ptr) {
    std::cout << "Processing shared_ptr: " << *ptr << std::endl;
}

void processPointer(int* ptr) {
    std::cout << "Processing raw pointer: " << *ptr << std::endl;
}

// Demonstration function
void demonstrateFunctionOverloading() {
    std::cout << "\n=== BASIC FUNCTION OVERLOADING ===" << std::endl;
    
    using namespace BasicOverloading;
    
    std::cout << add(5, 3) << std::endl;
    std::cout << add(1, 2, 3) << std::endl;
    std::cout << add(2.5, 3.7) << std::endl;
    std::cout << add(std::string("Hello "), std::string("World!")) << std::endl;
    
    display(42, "Answer");
    display("Value", 100);
    
    std::cout << "\n=== CONSTRUCTOR OVERLOADING ===" << std::endl;
    
    Point p1;                    // Default constructor
    Point p2(5.0);              // Single parameter
    Point p3(3.0, 4.0);         // Two parameters
    Point p4(p3);               // Copy constructor
    
    p4.display();
    std::cout << "Distance from origin: " << p4.distance() << std::endl;
    std::cout << "Distance between p3 and p4: " << p3.distance(p4) << std::endl;
    
    std::cout << "\n=== CONST AND REFERENCE OVERLOADING ===" << std::endl;
    
    Calculator calc;
    const Calculator constCalc;
    
    std::cout << calc.calculate(10) << std::endl;         // Non-const version
    std::cout << constCalc.calculate(10) << std::endl;    // Const version
    
    int value = 5;
    calc.process(value);        // Reference version
    calc.process(10);           // Value version
    std::cout << "Modified value: " << value << std::endl;
    
    std::cout << "\n=== TEMPLATE FUNCTION OVERLOADING ===" << std::endl;
    
    std::cout << maximum(10, 20) << std::endl;           // Integer overload
    std::cout << maximum(3.14, 2.71) << std::endl;      // Template version
    std::cout << maximum("hello", "world") << std::endl; // String overload
    
    std::cout << "\n=== VARIADIC FUNCTION OVERLOADING ===" << std::endl;
    
    std::cout << "Sum of 1: " << sum(1) << std::endl;
    std::cout << "Sum of 1,2,3: " << sum(1, 2, 3) << std::endl;
    std::cout << "Sum of 1.1,2.2,3.3,4.4: " << sum(1.1, 2.2, 3.3, 4.4) << std::endl;
    
    std::cout << "\n=== PERFECT FORWARDING ===" << std::endl;
    
    int x = 42;
    forwardFunction(x);         // L-value
    forwardFunction(100);       // R-value
    
    std::cout << "\n=== SMART POINTER OVERLOADING ===" << std::endl;
    
    auto uniquePtr = std::make_unique<int>(123);
    auto sharedPtr = std::make_shared<int>(456);
    int rawValue = 789;
    int* rawPtr = &rawValue;
    
    processPointer(std::move(uniquePtr));
    processPointer(sharedPtr);
    processPointer(rawPtr);
}

int main() {
    std::cout << "=== COMPILE-TIME POLYMORPHISM: FUNCTION OVERLOADING ===" << std::endl;
    std::cout << "Function overloading allows multiple functions with the same name" << std::endl;
    std::cout << "but different parameter lists. Resolution happens at compile time." << std::endl;
    
    demonstrateFunctionOverloading();
    
    std::cout << "\n=== KEY POINTS ===" << std::endl;
    std::cout << "1. Functions must differ in: number, type, or order of parameters" << std::endl;
    std::cout << "2. Return type alone cannot distinguish overloads" << std::endl;
    std::cout << "3. Const vs non-const member functions can be overloaded" << std::endl;
    std::cout << "4. Template functions can be overloaded with non-template functions" << std::endl;
    std::cout << "5. Overload resolution follows specific precedence rules" << std::endl;
    
    return 0;
}

/* Expected Output:
=== COMPILE-TIME POLYMORPHISM: FUNCTION OVERLOADING ===
Function overloading allows multiple functions with the same name
but different parameter lists. Resolution happens at compile time.

=== BASIC FUNCTION OVERLOADING ===
Adding two integers: 8
Adding three integers: 6
Adding two doubles: 6.2
Concatenating strings: Hello World!
Answer: 42
100 (Value)

=== CONSTRUCTOR OVERLOADING ===
Point created at origin (0, 0)
Point created at (5, 5)
Point created at (3, 4)
Point copied to (3, 4)
Point: (3, 4)
Distance from origin: 5
Distance between p3 and p4: 0

=== CONST AND REFERENCE OVERLOADING ===
Non-const calculate: 20
Const calculate: 30
Processing by reference (can modify): 5
Processing by value: 10
Modified value: 50

=== TEMPLATE FUNCTION OVERLOADING ===
Integer maximum: 20
Template maximum: 3.14
String maximum: world

=== VARIADIC FUNCTION OVERLOADING ===
Sum of 1: 1
Sum of 1,2,3: 6
Sum of 1.1,2.2,3.3,4.4: 11

=== PERFECT FORWARDING ===
Perfect forwarding: L-value reference
Perfect forwarding: R-value reference

=== SMART POINTER OVERLOADING ===
Processing unique_ptr: 123
Processing shared_ptr: 456
Processing raw pointer: 789

=== KEY POINTS ===
1. Functions must differ in: number, type, or order of parameters
2. Return type alone cannot distinguish overloads
3. Const vs non-const member functions can be overloaded
4. Template functions can be overloaded with non-template functions
5. Overload resolution follows specific precedence rules
*/
