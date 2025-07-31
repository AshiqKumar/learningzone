// C++23 Auto Deducing from Braced Initialization
// Compile: g++ -std=c++23 -o auto_braced_demo auto_braced_demo.cpp
// Run: ./auto_braced_demo

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <initializer_list>
#include <type_traits>
#include <concepts>

// 1. Basic auto deduction improvements in C++23
void demonstrate_basic_deduction() {
    std::cout << "\n1. Basic Auto Deduction from Braced Initialization:" << std::endl;
    
    // C++11/14/17: These would be problematic or require explicit types
    // auto x1 = {1, 2, 3};        // C++11: std::initializer_list<int>
    // auto x2{1};                 // C++17: int (special case)
    // auto x3{1, 2, 3};          // C++17: ERROR (ambiguous)
    
    // C++23: Improved deduction rules
    auto x1 = {1, 2, 3, 4, 5};     // Still std::initializer_list<int>
    auto x2{42};                   // int (single element)
    // auto x3{1, 2, 3};           // Still ERROR in C++23 for direct-list-init
    
    // But with parentheses it works:
    auto x3 = std::initializer_list{1, 2, 3};  // Explicit
    
    std::cout << "x1 size: " << x1.size() << std::endl;
    std::cout << "x2 value: " << x2 << std::endl;
    std::cout << "x3 size: " << x3.size() << std::endl;
    
    // New in C++23: Better template argument deduction
    std::vector v1{1, 2, 3, 4};           // std::vector<int>
    std::array a1{1.0, 2.0, 3.0};         // std::array<double, 3>
    
    std::cout << "Vector size: " << v1.size() << std::endl;
    std::cout << "Array size: " << a1.size() << std::endl;
}

// 2. Function template improvements
template<typename T>
void process_value(T value) {
    std::cout << "Processing value: " << value << " (type: " << typeid(T).name() << ")" << std::endl;
}

template<typename Container>
void process_container(Container container) {
    std::cout << "Container size: " << container.size() << " (type: " << typeid(Container).name() << ")" << std::endl;
}

void demonstrate_function_template_deduction() {
    std::cout << "\n2. Function Template Deduction with Braced Init:" << std::endl;
    
    // C++23: These work better with auto deduction
    process_value(42);
    process_value(3.14);
    process_value(std::string("hello"));
    
    // Container deduction
    process_container(std::vector{1, 2, 3, 4});
    process_container(std::array{1.0, 2.0, 3.0, 4.0, 5.0});
}

// 3. Lambda improvements with auto
void demonstrate_lambda_improvements() {
    std::cout << "\n3. Lambda Improvements with Auto:" << std::endl;
    
    // C++23: Better auto deduction in lambdas
    auto lambda1 = [](auto x) {
        auto result = x * 2;  // Better deduction
        return result;
    };
    
    auto lambda2 = [](auto container) {
        auto size = container.size();
        auto first = *container.begin();
        std::cout << "Container: size=" << size << ", first=" << first << std::endl;
        return size;
    };
    
    std::cout << "Lambda1 result: " << lambda1(21) << std::endl;
    std::cout << "Lambda1 result: " << lambda1(3.14) << std::endl;
    
    lambda2(std::vector{10, 20, 30, 40});
    lambda2(std::array{1.1, 2.2, 3.3});
}

// 4. Range-based for improvements
void demonstrate_range_based_for() {
    std::cout << "\n4. Range-based For Loop Improvements:" << std::endl;
    
    // C++23: Better auto deduction in range-based for
    std::vector<std::pair<int, std::string>> pairs{
        {1, "one"}, {2, "two"}, {3, "three"}
    };
    
    // Traditional
    for (const std::pair<int, std::string>& p : pairs) {
        std::cout << "Traditional: " << p.first << " -> " << p.second << std::endl;
    }
    
    // Auto deduction
    for (const auto& p : pairs) {
        std::cout << "Auto: " << p.first << " -> " << p.second << std::endl;
    }
    
    // Structured bindings with auto
    for (const auto& [key, value] : pairs) {
        std::cout << "Structured: " << key << " -> " << value << std::endl;
    }
}

// 5. Return type deduction improvements
auto create_vector() {
    return std::vector{1, 2, 3, 4, 5};  // Return type deduced as std::vector<int>
}

auto create_array() {
    return std::array{1.0, 2.0, 3.0};  // Return type deduced as std::array<double, 3>
}

auto create_pair() {
    return std::pair{42, std::string("answer")};  // std::pair<int, std::string>
}

void demonstrate_return_type_deduction() {
    std::cout << "\n5. Return Type Deduction:" << std::endl;
    
    auto vec = create_vector();
    auto arr = create_array();
    auto p = create_pair();
    
    std::cout << "Vector size: " << vec.size() << std::endl;
    std::cout << "Array size: " << arr.size() << std::endl;
    std::cout << "Pair: " << p.first << ", " << p.second << std::endl;
}

// 6. Class template deduction improvements
template<typename T>
class Container {
private:
    std::vector<T> data;
    
public:
    Container() = default;
    
    Container(std::initializer_list<T> init) : data(init) {}
    
    template<typename... Args>
    Container(Args&&... args) {
        (data.push_back(std::forward<Args>(args)), ...);
    }
    
    size_t size() const { return data.size(); }
    
    void print() const {
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Deduction guides (C++17 feature, improved in C++23)
template<typename... Args>
Container(Args...) -> Container<std::common_type_t<Args...>>;

void demonstrate_class_template_deduction() {
    std::cout << "\n6. Class Template Deduction Improvements:" << std::endl;
    
    // C++23: Better deduction
    Container c1{1, 2, 3, 4, 5};        // Container<int>
    Container c2{1.1, 2.2, 3.3};       // Container<double>
    Container c3{std::string("hello"), std::string("world")};  // Container<std::string>
    
    std::cout << "Container 1: ";
    c1.print();
    std::cout << "Container 2: ";
    c2.print();
    std::cout << "Container 3: ";
    c3.print();
}

// 7. Variable template improvements
template<typename T>
constexpr bool is_arithmetic_v = std::is_arithmetic_v<T>;

template<auto Value>
constexpr auto square = Value * Value;

void demonstrate_variable_templates() {
    std::cout << "\n7. Variable Template Improvements:" << std::endl;
    
    // C++23: Better auto deduction with variable templates
    constexpr auto val1 = square<5>;      // int
    constexpr auto val2 = square<3.14>;   // double
    
    std::cout << "Square of 5: " << val1 << std::endl;
    std::cout << "Square of 3.14: " << val2 << std::endl;
    
    // Type trait usage
    std::cout << "int is arithmetic: " << is_arithmetic_v<int> << std::endl;
    std::cout << "string is arithmetic: " << is_arithmetic_v<std::string> << std::endl;
}

// 8. Concept improvements with auto
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<typename T>
concept Container = requires(T t) {
    t.begin();
    t.end();
    t.size();
};

void demonstrate_concepts_with_auto() {
    std::cout << "\n8. Concepts with Auto Deduction:" << std::endl;
    
    auto process_numeric = []<Numeric T>(T value) {
        auto result = value * 2;
        std::cout << "Numeric processing: " << value << " -> " << result << std::endl;
        return result;
    };
    
    auto process_container = []<Container C>(C container) {
        auto size = container.size();
        std::cout << "Container processing: size = " << size << std::endl;
        return size;
    };
    
    process_numeric(42);
    process_numeric(3.14);
    
    process_container(std::vector{1, 2, 3});
    process_container(std::string("hello"));
}

// 9. Nested template deduction
template<typename T>
class Outer {
public:
    template<typename U>
    class Inner {
    private:
        T outer_value;
        U inner_value;
        
    public:
        Inner(T o, U i) : outer_value(o), inner_value(i) {}
        
        void print() const {
            std::cout << "Outer: " << outer_value << ", Inner: " << inner_value << std::endl;
        }
    };
    
    template<typename U>
    auto create_inner(U value) {
        return Inner<U>{T{}, value};  // C++23: Better deduction
    }
};

void demonstrate_nested_template_deduction() {
    std::cout << "\n9. Nested Template Deduction:" << std::endl;
    
    Outer<int> outer;
    auto inner1 = outer.create_inner(42);
    auto inner2 = outer.create_inner(std::string("hello"));
    
    inner1.print();
    inner2.print();
}

// 10. CTAD with aggregates (C++23 improvement)
struct Point {
    int x, y, z;
    
    void print() const {
        std::cout << "Point(" << x << ", " << y << ", " << z << ")" << std::endl;
    }
};

template<typename T>
struct Wrapper {
    T value;
    std::string name;
    
    void print() const {
        std::cout << "Wrapper(" << name << "): ";
        if constexpr (requires { value.print(); }) {
            value.print();
        } else {
            std::cout << value << std::endl;
        }
    }
};

// C++23: Deduction guide for aggregate
template<typename T>
Wrapper(T, std::string) -> Wrapper<T>;

void demonstrate_aggregate_deduction() {
    std::cout << "\n10. Aggregate Deduction (C++23):" << std::endl;
    
    // C++23: Better aggregate deduction
    Point p{1, 2, 3};
    p.print();
    
    // Wrapper deduction
    Wrapper w1{42, "integer"};
    Wrapper w2{Point{4, 5, 6}, "point"};
    Wrapper w3{std::string("hello"), "string"};
    
    w1.print();
    w2.print();
    w3.print();
}

// 11. Performance comparison
void demonstrate_performance() {
    std::cout << "\n11. Performance Comparison:" << std::endl;
    
    const int iterations = 1000000;
    
    // Traditional explicit types
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        std::vector<int> v{i, i+1, i+2, i+3, i+4};
        volatile auto sum = v[0] + v[1] + v[2] + v[3] + v[4];
        (void)sum;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto explicit_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Auto deduction
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        std::vector v{i, i+1, i+2, i+3, i+4};  // Auto deduction
        volatile auto sum = v[0] + v[1] + v[2] + v[3] + v[4];
        (void)sum;
    }
    end = std::chrono::high_resolution_clock::now();
    auto auto_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Explicit types: " << explicit_time.count() << " microseconds" << std::endl;
    std::cout << "Auto deduction: " << auto_time.count() << " microseconds" << std::endl;
    std::cout << "Performance difference: " << (auto_time.count() - explicit_time.count()) << " microseconds" << std::endl;
}

// 12. Common pitfalls and solutions
void demonstrate_pitfalls() {
    std::cout << "\n12. Common Pitfalls and Solutions:" << std::endl;
    
    // Pitfall 1: Initializer list vs container
    auto init_list = {1, 2, 3, 4};           // std::initializer_list<int>
    std::vector vector_explicit{1, 2, 3, 4}; // std::vector<int>
    
    std::cout << "Initializer list size: " << init_list.size() << std::endl;
    std::cout << "Vector size: " << vector_explicit.size() << std::endl;
    
    // Pitfall 2: Reference deduction
    int x = 42;
    auto y = x;        // int (copy)
    auto& z = x;       // int& (reference)
    auto&& w = x;      // int& (reference, not rvalue ref because x is lvalue)
    
    x = 100;
    std::cout << "After changing x to 100:" << std::endl;
    std::cout << "y (copy): " << y << std::endl;
    std::cout << "z (reference): " << z << std::endl;
    std::cout << "w (universal reference): " << w << std::endl;
    
    // Pitfall 3: Const deduction
    const int cx = 42;
    auto cy = cx;        // int (const is dropped)
    const auto cz = cx;  // const int
    
    std::cout << "cy is const: " << std::is_const_v<decltype(cy)> << std::endl;
    std::cout << "cz is const: " << std::is_const_v<decltype(cz)> << std::endl;
}

int main() {
    std::cout << "=== C++23 AUTO DEDUCING FROM BRACED INITIALIZATION DEMO ===" << std::endl;
    
    demonstrate_basic_deduction();
    demonstrate_function_template_deduction();
    demonstrate_lambda_improvements();
    demonstrate_range_based_for();
    demonstrate_return_type_deduction();
    demonstrate_class_template_deduction();
    demonstrate_variable_templates();
    demonstrate_concepts_with_auto();
    demonstrate_nested_template_deduction();
    demonstrate_aggregate_deduction();
    demonstrate_performance();
    demonstrate_pitfalls();
    
    std::cout << "\n=== AUTO DEDUCTION BENEFITS ===" << std::endl;
    std::cout << "✅ Cleaner, more readable code" << std::endl;
    std::cout << "✅ Less typing and fewer errors" << std::endl;
    std::cout << "✅ Better consistency with function template deduction" << std::endl;
    std::cout << "✅ Improved maintainability" << std::endl;
    std::cout << "✅ No runtime performance overhead" << std::endl;
    std::cout << "✅ Better integration with modern C++ features" << std::endl;
    std::cout << "✅ Reduced coupling to specific types" << std::endl;
    std::cout << "⚠️  Can hide type information that might be important" << std::endl;
    std::cout << "⚠️  May lead to unexpected types in some cases" << std::endl;
    std::cout << "⚠️  Debugging can be more challenging" << std::endl;
    std::cout << "⚠️  Reference and const deduction rules can be tricky" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++23 -Wall -Wextra -o auto_braced_demo auto_braced_demo.cpp
./auto_braced_demo

C++23 Auto Deducing from Braced Initialization Key Features:
1. Improved auto deduction rules for braced initialization
2. Better integration with class template argument deduction
3. Enhanced consistency with function template argument deduction
4. More reliable type deduction in complex scenarios

Evolution of Auto Deduction:

C++11:
auto x = {1, 2, 3};  // std::initializer_list<int>

C++17:
auto x{1};           // int (special case for single element)
auto x{1, 2, 3};     // ERROR (multiple elements)

C++23:
- More consistent rules
- Better integration with CTAD
- Improved template argument deduction
- Enhanced aggregate initialization support

Key Improvements:
1. Consistent behavior between different initialization forms
2. Better template argument deduction
3. Improved aggregate deduction
4. Enhanced lambda parameter deduction
5. More reliable return type deduction

Use Cases:
- Generic programming with templates
- Lambda expressions with auto parameters
- Container initialization
- Function return type deduction
- Variable template initialization

Benefits:
- Reduced verbosity
- Better maintainability
- Consistent behavior
- Type safety maintained
- No performance overhead

Best Practices:
- Use explicit types when clarity is important
- Be aware of reference and const deduction rules
- Understand initializer_list vs container deduction
- Test edge cases with mixed types
- Consider readability vs brevity trade-offs

Common Patterns:
auto container = ContainerType{args...};  // Container deduction
auto lambda = [](auto x) { return x * 2; };  // Generic lambda
auto result = function_returning_auto();  // Return type deduction
for (const auto& item : container) { }   // Range-based for
*/
