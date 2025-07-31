// C++14 Generic Lambdas - Template Lambdas with auto
// Compile: g++ -std=c++14 -o generic_lambdas_demo generic_lambdas_demo.cpp
// Run: ./generic_lambdas_demo

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <memory>

int main() {
    std::cout << "=== C++14 GENERIC LAMBDAS DEMO ===" << std::endl;
    
    // 1. Basic generic lambda
    std::cout << "\n1. Basic Generic Lambdas:" << std::endl;
    
    // C++11 lambda (specific types)
    auto cpp11_add = [](int a, int b) { return a + b; };
    
    // C++14 generic lambda (auto parameters)
    auto generic_add = [](auto a, auto b) { return a + b; };
    
    std::cout << "C++11 lambda: " << cpp11_add(5, 3) << std::endl;
    std::cout << "Generic lambda with ints: " << generic_add(5, 3) << std::endl;
    std::cout << "Generic lambda with doubles: " << generic_add(2.5, 1.5) << std::endl;
    std::cout << "Generic lambda with strings: " << generic_add(std::string("Hello, "), std::string("World!")) << std::endl;
    
    // 2. Generic lambdas with STL algorithms
    std::cout << "\n2. Generic Lambdas with STL Algorithms:" << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<double> decimals = {1.1, 2.2, 3.3, 4.4, 5.5};
    std::vector<std::string> words = {"apple", "banana", "cherry"};
    
    // Generic lambda for printing
    auto print = [](const auto& item) { std::cout << item << " "; };
    
    std::cout << "Numbers: ";
    std::for_each(numbers.begin(), numbers.end(), print);
    std::cout << std::endl;
    
    std::cout << "Decimals: ";
    std::for_each(decimals.begin(), decimals.end(), print);
    std::cout << std::endl;
    
    std::cout << "Words: ";
    std::for_each(words.begin(), words.end(), print);
    std::cout << std::endl;
    
    // 3. Generic lambda with multiple auto parameters
    std::cout << "\n3. Multiple Auto Parameters:" << std::endl;
    
    auto generic_operation = [](auto a, auto b, auto op) {
        return op(a, b);
    };
    
    auto multiply = [](auto x, auto y) { return x * y; };
    auto concatenate = [](auto a, auto b) { return a + b; };
    
    std::cout << "Operation with multiply: " << generic_operation(6, 7, multiply) << std::endl;
    std::cout << "Operation with concatenate: " << generic_operation(std::string("C++"), std::string("14"), concatenate) << std::endl;
    
    // 4. Generic lambdas with containers
    std::cout << "\n4. Generic Lambdas with Containers:" << std::endl;
    
    auto print_container = [](const auto& container) {
        std::cout << "Container contents: ";
        for (const auto& element : container) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    };
    
    print_container(numbers);
    print_container(words);
    
    std::set<int> number_set = {10, 20, 30, 40, 50};
    print_container(number_set);
    
    // 5. Generic lambda with transform
    std::cout << "\n5. Generic Transform Operations:" << std::endl;
    
    auto square = [](auto x) { return x * x; };
    auto to_upper_first = [](auto str) { 
        if (!str.empty()) str[0] = std::toupper(str[0]); 
        return str; 
    };
    
    std::vector<int> squared_numbers;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(squared_numbers), square);
    
    std::cout << "Original numbers: ";
    print_container(numbers);
    std::cout << "Squared numbers: ";
    print_container(squared_numbers);
    
    std::vector<std::string> capitalized_words;
    std::transform(words.begin(), words.end(), std::back_inserter(capitalized_words), to_upper_first);
    
    std::cout << "Original words: ";
    print_container(words);
    std::cout << "Capitalized words: ";
    print_container(capitalized_words);
    
    // 6. Generic lambda with perfect forwarding
    std::cout << "\n6. Perfect Forwarding with Generic Lambdas:" << std::endl;
    
    auto perfect_forward = [](auto&& func, auto&&... args) {
        return func(std::forward<decltype(args)>(args)...);
    };
    
    auto make_pair_func = [](auto a, auto b) { return std::make_pair(a, b); };
    
    auto result_pair = perfect_forward(make_pair_func, 42, std::string("hello"));
    std::cout << "Perfect forwarded pair: (" << result_pair.first << ", " << result_pair.second << ")" << std::endl;
    
    // 7. Generic lambda with capture
    std::cout << "\n7. Generic Lambdas with Capture:" << std::endl;
    
    int multiplier = 3;
    std::string prefix = "Result: ";
    
    auto captured_generic = [multiplier, prefix](auto value) {
        auto result = value * multiplier;
        return prefix + std::to_string(result);
    };
    
    std::cout << captured_generic(10) << std::endl;
    std::cout << captured_generic(5.5) << std::endl;
    
    // 8. Generic lambda for comparison
    std::cout << "\n8. Generic Comparison Operations:" << std::endl;
    
    auto generic_max = [](auto a, auto b) { return (a > b) ? a : b; };
    auto generic_min = [](auto a, auto b) { return (a < b) ? a : b; };
    
    std::cout << "max(10, 20): " << generic_max(10, 20) << std::endl;
    std::cout << "max(3.14, 2.71): " << generic_max(3.14, 2.71) << std::endl;
    std::cout << "max('a', 'z'): " << generic_max('a', 'z') << std::endl;
    
    std::cout << "min(10, 20): " << generic_min(10, 20) << std::endl;
    std::cout << "min('hello', 'world'): " << generic_min(std::string("hello"), std::string("world")) << std::endl;
    
    // 9. Generic lambda with conditional logic
    std::cout << "\n9. Conditional Logic in Generic Lambdas:" << std::endl;
    
    auto safe_divide = [](auto a, auto b) {
        if (b != decltype(b){}) {  // Check for zero using default-constructed value
            return a / b;
        } else {
            std::cout << "Division by zero detected!" << std::endl;
            return decltype(a / b){};  // Return default-constructed result type
        }
    };
    
    std::cout << "safe_divide(10, 2): " << safe_divide(10, 2) << std::endl;
    std::cout << "safe_divide(10.0, 0.0): " << safe_divide(10.0, 0.0) << std::endl;
    std::cout << "safe_divide(10, 0): " << safe_divide(10, 0) << std::endl;
    
    // 10. Generic lambda with map operations
    std::cout << "\n10. Map Operations with Generic Lambdas:" << std::endl;
    
    std::map<std::string, int> int_map = {{"one", 1}, {"two", 2}, {"three", 3}};
    std::map<std::string, std::string> string_map = {{"hello", "world"}, {"foo", "bar"}};
    
    auto print_map = [](const auto& map) {
        std::cout << "Map contents:" << std::endl;
        for (const auto& pair : map) {
            std::cout << "  " << pair.first << " -> " << pair.second << std::endl;
        }
    };
    
    print_map(int_map);
    print_map(string_map);
    
    // 11. Generic lambda for functional programming
    std::cout << "\n11. Functional Programming Style:" << std::endl;
    
    // Generic compose function
    auto compose = [](auto f, auto g) {
        return [f, g](auto x) { return f(g(x)); };
    };
    
    auto add_one = [](auto x) { return x + 1; };
    auto multiply_by_two = [](auto x) { return x * 2; };
    auto to_string = [](auto x) { return std::to_string(x); };
    
    auto composed_func = compose(to_string, compose(multiply_by_two, add_one));
    
    std::cout << "Composed function f(5): " << composed_func(5) << std::endl;  // ((5 + 1) * 2) = "12"
    std::cout << "Composed function f(10): " << composed_func(10) << std::endl; // ((10 + 1) * 2) = "22"
    
    // 12. Generic lambda with filtering
    std::cout << "\n12. Filtering with Generic Lambdas:" << std::endl;
    
    auto is_even = [](auto x) { return x % 2 == 0; };
    auto is_positive = [](auto x) { return x > 0; };
    auto longer_than_5 = [](const auto& str) { return str.length() > 5; };
    
    std::vector<int> test_numbers = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<std::string> test_words = {"hi", "hello", "world", "programming", "C++", "lambda"};
    
    // Generic filter function
    auto filter = [](const auto& container, auto predicate) {
        std::remove_const_t<std::remove_reference_t<decltype(container)>> result;
        std::copy_if(container.begin(), container.end(), std::back_inserter(result), predicate);
        return result;
    };
    
    auto even_numbers = filter(test_numbers, is_even);
    auto positive_numbers = filter(test_numbers, is_positive);
    auto long_words = filter(test_words, longer_than_5);
    
    std::cout << "Even numbers: ";
    print_container(even_numbers);
    
    std::cout << "Positive numbers: ";
    print_container(positive_numbers);
    
    std::cout << "Long words: ";
    print_container(long_words);
    
    // 13. Generic lambda with smart pointers
    std::cout << "\n13. Generic Lambdas with Smart Pointers:" << std::endl;
    
    auto create_unique = [](auto value) {
        return std::make_unique<std::remove_reference_t<decltype(value)>>(value);
    };
    
    auto create_shared = [](auto value) {
        return std::make_shared<std::remove_reference_t<decltype(value)>>(value);
    };
    
    auto unique_int = create_unique(42);
    auto unique_string = create_unique(std::string("C++14"));
    auto shared_double = create_shared(3.14);
    
    std::cout << "unique_ptr<int>: " << *unique_int << std::endl;
    std::cout << "unique_ptr<string>: " << *unique_string << std::endl;
    std::cout << "shared_ptr<double>: " << *shared_double << std::endl;
    
    // 14. Recursive generic lambda (C++14 style)
    std::cout << "\n14. Recursive Generic Lambda:" << std::endl;
    
    auto fibonacci = [](auto self, auto n) -> decltype(n) {
        if (n <= 1) return n;
        return self(self, n - 1) + self(self, n - 2);
    };
    
    std::cout << "fibonacci(10): " << fibonacci(fibonacci, 10) << std::endl;
    std::cout << "fibonacci(15): " << fibonacci(fibonacci, 15) << std::endl;
    
    // 15. Generic lambda with type traits
    std::cout << "\n15. Type Traits with Generic Lambdas:" << std::endl;
    
    auto print_type_info = [](auto value) {
        std::cout << "Value: " << value;
        std::cout << ", Size: " << sizeof(value) << " bytes";
        
        if constexpr (std::is_integral_v<decltype(value)>) {
            std::cout << " (integral type)";
        } else if constexpr (std::is_floating_point_v<decltype(value)>) {
            std::cout << " (floating point type)";
        } else {
            std::cout << " (other type)";
        }
        std::cout << std::endl;
    };
    
    print_type_info(42);
    print_type_info(3.14);
    print_type_info(std::string("hello"));
    print_type_info('A');
    
    std::cout << "\n=== GENERIC LAMBDA BENEFITS ===" << std::endl;
    std::cout << "✅ Write once, use with any type - true generic programming" << std::endl;
    std::cout << "✅ Reduce code duplication - no need for multiple lambdas" << std::endl;
    std::cout << "✅ Perfect for STL algorithms - works with any container type" << std::endl;
    std::cout << "✅ Template parameter deduction - compiler figures out types" << std::endl;
    std::cout << "✅ Composable - easy to combine with other generic functions" << std::endl;
    std::cout << "✅ Perfect forwarding support - efficient parameter passing" << std::endl;
    std::cout << "⚠️  Compile-time instantiation - code size may increase" << std::endl;
    std::cout << "⚠️  Error messages can be complex with template instantiation" << std::endl;
    std::cout << "⚠️  No explicit type checking until instantiation" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++14 -Wall -Wextra -o generic_lambdas_demo generic_lambdas_demo.cpp
./generic_lambdas_demo

C++14 Generic Lambda Features:
1. Auto parameters: [](auto x, auto y) { return x + y; }
2. Works with any types that support the operations used
3. Perfect for generic algorithms and functional programming
4. Reduces code duplication compared to type-specific lambdas
5. Template parameter deduction at call site

Key Syntax:
- auto parameters: [](auto x) { ... }
- Multiple auto: [](auto a, auto b) { ... }
- Perfect forwarding: [](auto&& x) { ... }
- Return type deduction: automatic based on return statement

Benefits:
- True generic programming with lambdas
- Reduces need for function templates in many cases
- Works seamlessly with STL algorithms
- Enables functional programming patterns
- Composable and reusable

Common Patterns:
- Generic algorithms: transform, filter, reduce
- Type-agnostic operations: print, compare, arithmetic
- Container operations that work with any container type
- Functional composition and higher-order functions

Best Practices:
- Use when the lambda logic applies to multiple types
- Combine with STL algorithms for powerful generic code
- Be careful with type requirements (operations must be valid)
- Consider constexpr for compile-time generic lambdas
*/
