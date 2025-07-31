// C++14 Variable Templates
// Compile: g++ -std=c++14 -o variable_templates_demo variable_templates_demo.cpp
// Run: ./variable_templates_demo

#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <array>

// 1. Basic variable templates
template<typename T>
constexpr T pi = T(3.14159265358979323846);

// More precise values for different types
template<>
constexpr float pi<float> = 3.14159265f;

template<>
constexpr double pi<double> = 3.14159265358979323846;

template<>
constexpr long double pi<long double> = 3.14159265358979323846264338327950288L;

// 2. Mathematical constants as variable templates
template<typename T>
constexpr T e = T(2.71828182845904523536);

template<typename T>
constexpr T golden_ratio = T(1.61803398874989484820);

template<typename T>
constexpr T sqrt2 = T(1.41421356237309504880);

// 3. Type traits as variable templates (C++14 style)
template<typename T>
constexpr bool is_integral_v = std::is_integral<T>::value;

template<typename T>
constexpr bool is_floating_point_v = std::is_floating_point<T>::value;

template<typename T>
constexpr bool is_pointer_v = std::is_pointer<T>::value;

template<typename T>
constexpr bool is_const_v = std::is_const<T>::value;

template<typename T>
constexpr bool is_reference_v = std::is_reference<T>::value;

// 4. Size constants
template<typename T>
constexpr size_t type_size_v = sizeof(T);

template<typename T>
constexpr size_t type_alignment_v = alignof(T);

// 5. Array size detection
template<typename T, size_t N>
constexpr size_t array_size(T (&)[N]) {
    return N;
}

template<typename T, size_t N>
constexpr size_t array_size_v = N;

// Helper for std::array
template<typename T, size_t N>
constexpr size_t array_size_v<std::array<T, N>> = N;

// 6. Conditional constants
template<typename T>
constexpr T max_value = std::numeric_limits<T>::max();

template<typename T>
constexpr T min_value = std::numeric_limits<T>::min();

// 7. String literals as variable templates
template<char... chars>
constexpr std::array<char, sizeof...(chars)> string_literal{chars...};

// 8. Power calculation as variable template
template<int base, int exponent>
constexpr int power_v = (exponent == 0) ? 1 : base * power_v<base, exponent - 1>;

// Specialization for exponent 0
template<int base>
constexpr int power_v<base, 0> = 1;

// 9. Factorial as variable template
template<int N>
constexpr int factorial_v = N * factorial_v<N - 1>;

template<>
constexpr int factorial_v<0> = 1;

template<>
constexpr int factorial_v<1> = 1;

// 10. Fibonacci as variable template
template<int N>
constexpr int fibonacci_v = fibonacci_v<N - 1> + fibonacci_v<N - 2>;

template<>
constexpr int fibonacci_v<0> = 0;

template<>
constexpr int fibonacci_v<1> = 1;

// 11. Boolean logic helpers
template<bool... Bs>
constexpr bool all_true = (Bs && ...);  // C++17 fold expression, but showing concept

// C++14 compatible version
template<bool B1, bool B2>
constexpr bool all_true_v = B1 && B2;

template<bool B1, bool B2, bool B3>
constexpr bool all_true_v<B1, B2, B3> = B1 && B2 && B3;

// 12. Container properties
template<typename Container>
constexpr bool has_size_method = requires(Container c) { c.size(); };  // C++20 concept, showing idea

// C++14 compatible SFINAE version
template<typename T>
struct has_size_method_helper {
private:
    template<typename U>
    static auto test(int) -> decltype(std::declval<U>().size(), std::true_type{});
    
    template<typename>
    static std::false_type test(...);
    
public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

template<typename T>
constexpr bool has_size_method_v = has_size_method_helper<T>::value;

// 13. Custom type properties
class CustomClass {
public:
    int value;
    void method() {}
    size_t size() const { return 1; }
};

struct EmptyStruct {};

union SimpleUnion {
    int i;
    float f;
};

int main() {
    std::cout << "=== C++14 VARIABLE TEMPLATES DEMO ===" << std::endl;
    
    // 1. Mathematical constants
    std::cout << "\n1. Mathematical Constants:" << std::endl;
    
    std::cout << "pi<float> = " << pi<float> << std::endl;
    std::cout << "pi<double> = " << pi<double> << std::endl;
    std::cout << "pi<long double> = " << pi<long double> << std::endl;
    
    std::cout << "e<double> = " << e<double> << std::endl;
    std::cout << "golden_ratio<double> = " << golden_ratio<double> << std::endl;
    std::cout << "sqrt2<double> = " << sqrt2<double> << std::endl;
    
    // Using constants in calculations
    auto circle_area = pi<double> * 5.0 * 5.0;  // Area of circle with radius 5
    std::cout << "Area of circle (r=5): " << circle_area << std::endl;
    
    // 2. Type traits made simpler
    std::cout << "\n2. Type Traits (Variable Template Style):" << std::endl;
    
    std::cout << "is_integral_v<int>: " << std::boolalpha << is_integral_v<int> << std::endl;
    std::cout << "is_integral_v<double>: " << is_integral_v<double> << std::endl;
    std::cout << "is_floating_point_v<float>: " << is_floating_point_v<float> << std::endl;
    std::cout << "is_floating_point_v<int>: " << is_floating_point_v<int> << std::endl;
    
    int x = 42;
    int* ptr = &x;
    std::cout << "is_pointer_v<int>: " << is_pointer_v<int> << std::endl;
    std::cout << "is_pointer_v<int*>: " << is_pointer_v<int*> << std::endl;
    
    const int const_val = 10;
    std::cout << "is_const_v<const int>: " << is_const_v<const int> << std::endl;
    std::cout << "is_const_v<int>: " << is_const_v<int> << std::endl;
    
    int& ref = x;
    std::cout << "is_reference_v<int&>: " << is_reference_v<int&> << std::endl;
    std::cout << "is_reference_v<int>: " << is_reference_v<int> << std::endl;
    
    // 3. Size and alignment information
    std::cout << "\n3. Size and Alignment Information:" << std::endl;
    
    std::cout << "sizeof(char): " << type_size_v<char> << " bytes" << std::endl;
    std::cout << "sizeof(int): " << type_size_v<int> << " bytes" << std::endl;
    std::cout << "sizeof(double): " << type_size_v<double> << " bytes" << std::endl;
    std::cout << "sizeof(CustomClass): " << type_size_v<CustomClass> << " bytes" << std::endl;
    
    std::cout << "alignof(char): " << type_alignment_v<char> << " bytes" << std::endl;
    std::cout << "alignof(int): " << type_alignment_v<int> << " bytes" << std::endl;
    std::cout << "alignof(double): " << type_alignment_v<double> << " bytes" << std::endl;
    
    // 4. Numeric limits
    std::cout << "\n4. Numeric Limits:" << std::endl;
    
    std::cout << "max_value<int>: " << max_value<int> << std::endl;
    std::cout << "min_value<int>: " << min_value<int> << std::endl;
    std::cout << "max_value<unsigned int>: " << max_value<unsigned int> << std::endl;
    std::cout << "max_value<char>: " << static_cast<int>(max_value<char>) << std::endl;
    std::cout << "min_value<char>: " << static_cast<int>(min_value<char>) << std::endl;
    
    // 5. Compile-time calculations
    std::cout << "\n5. Compile-time Mathematical Calculations:" << std::endl;
    
    std::cout << "2^8 = " << power_v<2, 8> << std::endl;
    std::cout << "3^4 = " << power_v<3, 4> << std::endl;
    std::cout << "5^0 = " << power_v<5, 0> << std::endl;
    
    std::cout << "5! = " << factorial_v<5> << std::endl;
    std::cout << "7! = " << factorial_v<7> << std::endl;
    std::cout << "0! = " << factorial_v<0> << std::endl;
    
    std::cout << "Fibonacci(10) = " << fibonacci_v<10> << std::endl;
    std::cout << "Fibonacci(15) = " << fibonacci_v<15> << std::endl;
    std::cout << "Fibonacci(0) = " << fibonacci_v<0> << std::endl;
    std::cout << "Fibonacci(1) = " << fibonacci_v<1> << std::endl;
    
    // 6. Container detection
    std::cout << "\n6. Container Method Detection:" << std::endl;
    
    std::cout << "std::vector<int> has size(): " << has_size_method_v<std::vector<int>> << std::endl;
    std::cout << "std::string has size(): " << has_size_method_v<std::string> << std::endl;
    std::cout << "CustomClass has size(): " << has_size_method_v<CustomClass> << std::endl;
    std::cout << "int has size(): " << has_size_method_v<int> << std::endl;
    std::cout << "EmptyStruct has size(): " << has_size_method_v<EmptyStruct> << std::endl;
    
    // 7. Practical examples
    std::cout << "\n7. Practical Applications:" << std::endl;
    
    // Template function using variable templates
    auto print_type_info = [](auto value) {
        using T = decltype(value);
        std::cout << "Value: " << value << std::endl;
        std::cout << "  Size: " << type_size_v<T> << " bytes" << std::endl;
        std::cout << "  Is integral: " << is_integral_v<T> << std::endl;
        std::cout << "  Is floating point: " << is_floating_point_v<T> << std::endl;
        std::cout << "  Is pointer: " << is_pointer_v<T> << std::endl;
        std::cout << std::endl;
    };
    
    print_type_info(42);
    print_type_info(3.14);
    print_type_info("Hello");
    
    // 8. Compile-time arrays
    std::cout << "\n8. Compile-time Arrays:" << std::endl;
    
    constexpr std::array<int, 5> powers_of_2 = {
        power_v<2, 0>, power_v<2, 1>, power_v<2, 2>, power_v<2, 3>, power_v<2, 4>
    };
    
    std::cout << "Powers of 2: ";
    for (const auto& power : powers_of_2) {
        std::cout << power << " ";
    }
    std::cout << std::endl;
    
    constexpr std::array<int, 6> factorials = {
        factorial_v<0>, factorial_v<1>, factorial_v<2>, 
        factorial_v<3>, factorial_v<4>, factorial_v<5>
    };
    
    std::cout << "Factorials 0-5: ";
    for (const auto& fact : factorials) {
        std::cout << fact << " ";
    }
    std::cout << std::endl;
    
    // 9. Generic programming with variable templates
    std::cout << "\n9. Generic Programming:" << std::endl;
    
    auto generic_function = []<typename T>(T value) {
        std::cout << "Processing value of type with size " << type_size_v<T> << " bytes" << std::endl;
        
        if constexpr (is_integral_v<T>) {
            std::cout << "  This is an integral type: " << value << std::endl;
        }
        else if constexpr (is_floating_point_v<T>) {
            std::cout << "  This is a floating-point type: " << value << std::endl;
            std::cout << "  Pi for this type: " << pi<T> << std::endl;
        }
        else {
            std::cout << "  This is some other type" << std::endl;
        }
    };
    
    // Note: This syntax ([]<typename T>) is C++20, showing the concept
    // In C++14, you'd use regular template functions
    
    template_function_demo(42);
    template_function_demo(3.14f);
    template_function_demo(2.71828);
    
    // 10. Comparison with C++11 approach
    std::cout << "\n10. C++11 vs C++14 Comparison:" << std::endl;
    
    // C++11 way - more verbose
    std::cout << "C++11: std::is_integral<int>::value = " << std::is_integral<int>::value << std::endl;
    std::cout << "C++14: is_integral_v<int> = " << is_integral_v<int> << std::endl;
    
    std::cout << "C++11: sizeof(double) = " << sizeof(double) << std::endl;
    std::cout << "C++14: type_size_v<double> = " << type_size_v<double> << std::endl;
    
    std::cout << "\n=== VARIABLE TEMPLATES BENEFITS ===" << std::endl;
    std::cout << "✅ Cleaner syntax than ::value access" << std::endl;
    std::cout << "✅ Better template argument deduction" << std::endl;
    std::cout << "✅ Consistent naming conventions (suffix _v)" << std::endl;
    std::cout << "✅ Compile-time constants with template parameters" << std::endl;
    std::cout << "✅ Easier to use in template metaprogramming" << std::endl;
    std::cout << "✅ Foundation for C++17 standard library _v traits" << std::endl;
    std::cout << "✅ More expressive mathematical constants" << std::endl;
    std::cout << "⚠️  New feature in C++14 - not available in C++11" << std::endl;
    std::cout << "⚠️  Can make template instantiation more complex" << std::endl;
    
    return 0;
}

// Helper function for demonstration (C++14 compatible)
template<typename T>
void template_function_demo(T value) {
    std::cout << "Processing value of type with size " << type_size_v<T> << " bytes" << std::endl;
    
    if (is_integral_v<T>) {
        std::cout << "  This is an integral type: " << value << std::endl;
    }
    else if (is_floating_point_v<T>) {
        std::cout << "  This is a floating-point type: " << value << std::endl;
        std::cout << "  Pi for this type: " << pi<T> << std::endl;
    }
    else {
        std::cout << "  This is some other type" << std::endl;
    }
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++14 -Wall -Wextra -o variable_templates_demo variable_templates_demo.cpp
./variable_templates_demo

C++14 Variable Templates:
- Template variables that can be parameterized by types or values
- Cleaner alternative to static data members in class templates
- Foundation for C++17's _v suffix type traits

Key Features:
1. Template Variables: template<typename T> constexpr T pi = ...
2. Specialization Support: template<> constexpr float pi<float> = ...
3. Non-type Parameters: template<int N> constexpr int factorial_v = ...
4. Type Traits Simplification: is_integral_v<T> vs std::is_integral<T>::value

Benefits:
- Cleaner syntax for compile-time constants
- Better template argument deduction
- More expressive mathematical constants
- Foundation for modern C++ idioms
- Consistent naming conventions (_v suffix)

Common Use Cases:
- Type traits (_v versions)
- Mathematical constants (pi, e, etc.)
- Compile-time calculations
- Template metaprogramming
- Configuration constants

Comparison:
C++11: std::is_integral<T>::value
C++14: is_integral_v<T>

The C++14 variable template approach is cleaner and became the foundation
for the C++17 standard library's _v suffix type traits.
*/
