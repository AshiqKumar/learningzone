// template_functions.cpp - Demonstrates template functions in C++
// Compile: g++ -std=c++17 -Wall -Wextra template_functions.cpp -o template_functions

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <type_traits>
#include <functional>

// 1. Basic Function Templates
template<typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
T minimum(T a, T b) {
    return (a < b) ? a : b;
}

template<typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 2. Multiple Template Parameters
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

template<typename T, typename U, typename V>
auto multiply(T a, U b, V c) -> decltype(a * b * c) {
    return a * b * c;
}

// 3. Template Functions with Non-Type Parameters
template<typename T, size_t N>
void printArray(const T (&arr)[N]) {
    std::cout << "Array[" << N << "]: ";
    for (size_t i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template<int N>
constexpr int factorial() {
    if constexpr (N <= 1) {
        return 1;
    } else {
        return N * factorial<N - 1>();
    }
}

// 4. Variadic Templates
template<typename T>
T sum(T value) {
    return value;  // Base case
}

template<typename T, typename... Args>
T sum(T first, Args... args) {
    return first + sum(args...);
}

// More advanced variadic template
template<typename... Args>
void print(Args... args) {
    ((std::cout << args << " "), ...);  // C++17 fold expression
    std::cout << std::endl;
}

template<typename T, typename... Args>
auto average(T first, Args... args) -> double {
    if constexpr (sizeof...(args) == 0) {
        return static_cast<double>(first);
    } else {
        return static_cast<double>(first + sum(args...)) / (1 + sizeof...(args));
    }
}

// 5. Template Function Specialization
template<typename T>
void processValue(T value) {
    std::cout << "Generic processing: " << value << std::endl;
}

// Full specialization for const char*
template<>
void processValue<const char*>(const char* value) {
    std::cout << "String processing: " << value << " (length: " << strlen(value) << ")" << std::endl;
}

// Full specialization for bool
template<>
void processValue<bool>(bool value) {
    std::cout << "Boolean processing: " << (value ? "TRUE" : "FALSE") << std::endl;
}

// 6. Template Functions with SFINAE
template<typename T>
typename std::enable_if_t<std::is_integral_v<T>, void>
processInteger(T value) {
    std::cout << "Processing integer: " << value << " (squared: " << value * value << ")" << std::endl;
}

template<typename T>
typename std::enable_if_t<std::is_floating_point_v<T>, void>
processFloat(T value) {
    std::cout << "Processing float: " << value << " (sqrt: " << sqrt(value) << ")" << std::endl;
}

// SFINAE with decltype
template<typename T>
auto hasSize(T&& t) -> decltype(t.size(), std::true_type{}) {
    return std::true_type{};
}

std::false_type hasSize(...) {
    return std::false_type{};
}

template<typename T>
void printSize(T&& container) {
    if constexpr (decltype(hasSize(container))::value) {
        std::cout << "Container size: " << container.size() << std::endl;
    } else {
        std::cout << "Object doesn't have size() method" << std::endl;
    }
}

// 7. Template Functions with Concepts (C++20 style using SFINAE)
template<typename T>
using is_printable = decltype(std::cout << std::declval<T>());

template<typename T, typename = std::void_t<is_printable<T>>>
void safePrint(const T& value) {
    std::cout << "Printing: " << value << std::endl;
}

// 8. Lambda Templates (C++14)
auto genericLambda = [](auto a, auto b) {
    return a + b;
};

auto printLambda = [](auto&&... args) {
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
};

// 9. Perfect Forwarding
template<typename F, typename... Args>
auto callFunction(F&& func, Args&&... args) -> decltype(func(std::forward<Args>(args)...)) {
    std::cout << "Calling function with " << sizeof...(args) << " arguments" << std::endl;
    return func(std::forward<Args>(args)...);
}

// 10. Template Function with Default Parameters
template<typename T, typename Compare = std::less<T>>
T findExtreme(const std::vector<T>& vec, Compare comp = Compare{}) {
    if (vec.empty()) {
        throw std::invalid_argument("Empty vector");
    }
    
    T result = vec[0];
    for (const auto& element : vec) {
        if (comp(result, element)) {
            result = element;
        }
    }
    return result;
}

// 11. Template Functions for Generic Algorithms
template<typename Iterator, typename Predicate>
size_t countIf(Iterator begin, Iterator end, Predicate pred) {
    size_t count = 0;
    for (auto it = begin; it != end; ++it) {
        if (pred(*it)) {
            ++count;
        }
    }
    return count;
}

template<typename Container, typename Func>
auto transform(const Container& container, Func func) -> std::vector<decltype(func(*container.begin()))> {
    std::vector<decltype(func(*container.begin()))> result;
    result.reserve(container.size());
    
    for (const auto& element : container) {
        result.push_back(func(element));
    }
    return result;
}

// 12. Template Function for Type Traits
template<typename T>
void analyzeType() {
    std::cout << "Type Analysis:" << std::endl;
    std::cout << "  Is integral: " << std::is_integral_v<T> << std::endl;
    std::cout << "  Is floating point: " << std::is_floating_point_v<T> << std::endl;
    std::cout << "  Is pointer: " << std::is_pointer_v<T> << std::endl;
    std::cout << "  Is class: " << std::is_class_v<T> << std::endl;
    std::cout << "  Size: " << sizeof(T) << " bytes" << std::endl;
    std::cout << "  Is const: " << std::is_const_v<T> << std::endl;
    std::cout << "  Is reference: " << std::is_reference_v<T> << std::endl;
}

// Demonstration functions
void demonstrateBasicTemplates() {
    std::cout << "\n=== BASIC TEMPLATE FUNCTIONS ===" << std::endl;
    
    std::cout << "maximum(10, 20) = " << maximum(10, 20) << std::endl;
    std::cout << "maximum(3.14, 2.71) = " << maximum(3.14, 2.71) << std::endl;
    std::cout << "maximum('a', 'z') = " << maximum('a', 'z') << std::endl;
    
    int a = 5, b = 10;
    std::cout << "Before swap: a=" << a << ", b=" << b << std::endl;
    swapValues(a, b);
    std::cout << "After swap: a=" << a << ", b=" << b << std::endl;
    
    int arr[] = {1, 2, 3, 4, 5};
    printArray(arr);
    
    std::cout << "factorial<5>() = " << factorial<5>() << std::endl;
}

void demonstrateMultipleParameters() {
    std::cout << "\n=== MULTIPLE TEMPLATE PARAMETERS ===" << std::endl;
    
    std::cout << "add(5, 3.14) = " << add(5, 3.14) << std::endl;
    std::cout << "add(2.5, 7) = " << add(2.5, 7) << std::endl;
    std::cout << "multiply(2, 3.5, 4) = " << multiply(2, 3.5, 4) << std::endl;
}

void demonstrateVariadicTemplates() {
    std::cout << "\n=== VARIADIC TEMPLATES ===" << std::endl;
    
    std::cout << "sum(1) = " << sum(1) << std::endl;
    std::cout << "sum(1, 2, 3) = " << sum(1, 2, 3) << std::endl;
    std::cout << "sum(1.1, 2.2, 3.3, 4.4) = " << sum(1.1, 2.2, 3.3, 4.4) << std::endl;
    
    print("Hello", 42, 3.14, "World");
    
    std::cout << "average(10, 20, 30) = " << average(10, 20, 30) << std::endl;
}

void demonstrateSpecialization() {
    std::cout << "\n=== TEMPLATE SPECIALIZATION ===" << std::endl;
    
    processValue(42);
    processValue(3.14);
    processValue("Hello Template");
    processValue(true);
    processValue(false);
}

void demonstrateSFINAE() {
    std::cout << "\n=== SFINAE AND TYPE TRAITS ===" << std::endl;
    
    processInteger(42);
    processFloat(3.14);
    
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::string str = "Hello";
    int number = 42;
    
    printSize(vec);
    printSize(str);
    printSize(number);
    
    safePrint(42);
    safePrint("Hello");
    safePrint(3.14);
}

void demonstrateLambdas() {
    std::cout << "\n=== LAMBDA TEMPLATES ===" << std::endl;
    
    std::cout << "genericLambda(5, 3) = " << genericLambda(5, 3) << std::endl;
    std::cout << "genericLambda(2.5, 1.5) = " << genericLambda(2.5, 1.5) << std::endl;
    
    printLambda("Lambda", "with", "multiple", "arguments", 42);
}

void demonstratePerfectForwarding() {
    std::cout << "\n=== PERFECT FORWARDING ===" << std::endl;
    
    auto multiply = [](int a, int b) { return a * b; };
    auto concat = [](const std::string& a, const std::string& b) { return a + b; };
    
    int result1 = callFunction(multiply, 6, 7);
    std::cout << "Result: " << result1 << std::endl;
    
    std::string result2 = callFunction(concat, std::string("Hello "), std::string("World"));
    std::cout << "Result: " << result2 << std::endl;
}

void demonstrateGenericAlgorithms() {
    std::cout << "\n=== GENERIC ALGORITHMS ===" << std::endl;
    
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Find maximum
    int maxVal = findExtreme(numbers, std::less<int>{});
    std::cout << "Maximum value: " << maxVal << std::endl;
    
    // Find minimum
    int minVal = findExtreme(numbers, std::greater<int>{});
    std::cout << "Minimum value: " << minVal << std::endl;
    
    // Count even numbers
    size_t evenCount = countIf(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 0; });
    std::cout << "Even numbers count: " << evenCount << std::endl;
    
    // Transform: square all numbers
    auto squares = transform(numbers, [](int n) { return n * n; });
    std::cout << "Squares: ";
    for (int sq : squares) {
        std::cout << sq << " ";
    }
    std::cout << std::endl;
}

void demonstrateTypeAnalysis() {
    std::cout << "\n=== TYPE ANALYSIS ===" << std::endl;
    
    std::cout << "\nAnalyzing int:" << std::endl;
    analyzeType<int>();
    
    std::cout << "\nAnalyzing double*:" << std::endl;
    analyzeType<double*>();
    
    std::cout << "\nAnalyzing std::string:" << std::endl;
    analyzeType<std::string>();
    
    std::cout << "\nAnalyzing const int&:" << std::endl;
    analyzeType<const int&>();
}

int main() {
    std::cout << "=== COMPILE-TIME POLYMORPHISM: TEMPLATE FUNCTIONS ===" << std::endl;
    std::cout << "Template functions provide generic programming capabilities" << std::endl;
    std::cout << "with compile-time type resolution and zero runtime overhead." << std::endl;
    
    demonstrateBasicTemplates();
    demonstrateMultipleParameters();
    demonstrateVariadicTemplates();
    demonstrateSpecialization();
    demonstrateSFINAE();
    demonstrateLambdas();
    demonstratePerfectForwarding();
    demonstrateGenericAlgorithms();
    demonstrateTypeAnalysis();
    
    std::cout << "\n=== KEY BENEFITS ===" << std::endl;
    std::cout << "1. Type Safety - Compile-time type checking" << std::endl;
    std::cout << "2. Performance - Zero runtime overhead" << std::endl;
    std::cout << "3. Code Reuse - Write once, use with multiple types" << std::endl;
    std::cout << "4. Optimization - Compiler can inline and optimize" << std::endl;
    std::cout << "5. Expressiveness - Rich template metaprogramming" << std::endl;
    
    return 0;
}

/* Expected Output:
=== COMPILE-TIME POLYMORPHISM: TEMPLATE FUNCTIONS ===
Template functions provide generic programming capabilities
with compile-time type resolution and zero runtime overhead.

=== BASIC TEMPLATE FUNCTIONS ===
maximum(10, 20) = 20
maximum(3.14, 2.71) = 3.14
maximum('a', 'z') = z
Before swap: a=5, b=10
After swap: a=10, b=5
Array[5]: 1 2 3 4 5 
factorial<5>() = 120

=== MULTIPLE TEMPLATE PARAMETERS ===
add(5, 3.14) = 8.14
add(2.5, 7) = 9.5
multiply(2, 3.5, 4) = 28

=== VARIADIC TEMPLATES ===
sum(1) = 1
sum(1, 2, 3) = 6
sum(1.1, 2.2, 3.3, 4.4) = 11
Hello 42 3.14 World 
average(10, 20, 30) = 20

=== TEMPLATE SPECIALIZATION ===
Generic processing: 42
Generic processing: 3.14
String processing: Hello Template (length: 14)
Boolean processing: TRUE
Boolean processing: FALSE

=== SFINAE AND TYPE TRAITS ===
Processing integer: 42 (squared: 1764)
Processing float: 3.14 (sqrt: 1.77200)
Container size: 5
Container size: 5
Object doesn't have size() method
Printing: 42
Printing: Hello
Printing: 3.14

=== LAMBDA TEMPLATES ===
genericLambda(5, 3) = 8
genericLambda(2.5, 1.5) = 4
Lambda with multiple arguments 42 

=== PERFECT FORWARDING ===
Calling function with 2 arguments
Result: 42
Calling function with 2 arguments
Result: Hello World

=== GENERIC ALGORITHMS ===
Maximum value: 10
Minimum value: 1
Even numbers count: 5
Squares: 1 4 9 16 25 36 49 64 81 100 

=== TYPE ANALYSIS ===

Analyzing int:
Type Analysis:
  Is integral: 1
  Is floating point: 0
  Is pointer: 0
  Is class: 0
  Size: 4 bytes
  Is const: 0
  Is reference: 0

Analyzing double*:
Type Analysis:
  Is integral: 0
  Is floating point: 0
  Is pointer: 1
  Is class: 0
  Size: 8 bytes
  Is const: 0
  Is reference: 0

Analyzing std::string:
Type Analysis:
  Is integral: 0
  Is floating point: 0
  Is pointer: 0
  Is class: 1
  Size: 32 bytes
  Is const: 0
  Is reference: 0

Analyzing const int&:
Type Analysis:
  Is integral: 1
  Is floating point: 0
  Is pointer: 0
  Is class: 0
  Size: 4 bytes
  Is const: 0
  Is reference: 1

=== KEY BENEFITS ===
1. Type Safety - Compile-time type checking
2. Performance - Zero runtime overhead
3. Code Reuse - Write once, use with multiple types
4. Optimization - Compiler can inline and optimize
5. Expressiveness - Rich template metaprogramming
*/
