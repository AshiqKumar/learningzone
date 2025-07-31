/**
 * @file auto_demo.cpp
 * @brief Demonstration of 'auto' storage class and type deduction
 * 
 * Compile: g++ -std=c++17 -Wall -Wextra auto_demo.cpp -o auto_demo
 * Run: ./auto_demo
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <typeinfo>
#include <functional>

// Function to demonstrate auto with return types
auto add(int a, int b) -> int {  // Trailing return type (C++11)
    return a + b;
}

auto multiply(double a, double b) {  // C++14 auto return type deduction
    return a * b;
}

// Template function with auto
template<typename T>
auto getFirst(const std::vector<T>& vec) -> decltype(vec[0]) {
    return vec.empty() ? T{} : vec[0];
}

int main() {
    std::cout << "=== AUTO STORAGE CLASS DEMO ===" << std::endl;
    
    // 1. Traditional variable declarations (before C++11)
    std::cout << "\n1. Traditional Declarations:" << std::endl;
    int traditional_int = 42;
    double traditional_double = 3.14;
    std::string traditional_string = "Hello";
    
    std::cout << "Traditional int: " << traditional_int << std::endl;
    std::cout << "Traditional double: " << traditional_double << std::endl;
    std::cout << "Traditional string: " << traditional_string << std::endl;
    
    // 2. Auto type deduction (C++11)
    std::cout << "\n2. Auto Type Deduction:" << std::endl;
    auto auto_int = 42;                    // Deduced as int
    auto auto_double = 3.14;               // Deduced as double
    auto auto_string = std::string("World"); // Deduced as std::string
    auto auto_char = 'A';                  // Deduced as char
    
    std::cout << "Auto int: " << auto_int << " (type: " << typeid(auto_int).name() << ")" << std::endl;
    std::cout << "Auto double: " << auto_double << " (type: " << typeid(auto_double).name() << ")" << std::endl;
    std::cout << "Auto string: " << auto_string << " (type: " << typeid(auto_string).name() << ")" << std::endl;
    std::cout << "Auto char: " << auto_char << " (type: " << typeid(auto_char).name() << ")" << std::endl;
    
    // 3. Auto with complex types
    std::cout << "\n3. Auto with Complex Types:" << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    auto vec_copy = numbers;               // Deduced as std::vector<int>
    auto& vec_ref = numbers;               // Reference to vector
    const auto& vec_const_ref = numbers;   // Const reference
    
    std::map<std::string, int> ages = {
        {"Alice", 25}, {"Bob", 30}, {"Charlie", 35}
    };
    auto map_copy = ages;                  // Deduced as std::map<std::string, int>
    
    std::cout << "Vector size: " << vec_copy.size() << std::endl;
    std::cout << "Map size: " << map_copy.size() << std::endl;
    
    // 4. Auto with iterators (very useful!)
    std::cout << "\n4. Auto with Iterators:" << std::endl;
    
    // Without auto (verbose)
    for (std::map<std::string, int>::iterator it = ages.begin(); it != ages.end(); ++it) {
        std::cout << "Without auto: " << it->first << " is " << it->second << " years old" << std::endl;
        break; // Just show one example
    }
    
    // With auto (concise)
    for (auto it = ages.begin(); it != ages.end(); ++it) {
        std::cout << "With auto: " << it->first << " is " << it->second << " years old" << std::endl;
    }
    
    // Range-based for loop with auto (C++11)
    std::cout << "\nRange-based for with auto:" << std::endl;
    for (const auto& pair : ages) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }
    
    // 5. Auto with lambda expressions
    std::cout << "\n5. Auto with Lambda Expressions:" << std::endl;
    
    auto lambda_add = [](int a, int b) { return a + b; };
    auto lambda_multiply = [](double x, double y) -> double { return x * y; };
    
    std::cout << "Lambda add(5, 3): " << lambda_add(5, 3) << std::endl;
    std::cout << "Lambda multiply(2.5, 4.0): " << lambda_multiply(2.5, 4.0) << std::endl;
    
    // Generic lambda (C++14)
    auto generic_lambda = [](auto x, auto y) { return x + y; };
    std::cout << "Generic lambda(10, 20): " << generic_lambda(10, 20) << std::endl;
    std::cout << "Generic lambda(1.5, 2.5): " << generic_lambda(1.5, 2.5) << std::endl;
    
    // 6. Auto with function pointers
    std::cout << "\n6. Auto with Function Pointers:" << std::endl;
    
    auto func_ptr = add;                   // Function pointer
    auto func_result = func_ptr(10, 20);
    std::cout << "Function pointer result: " << func_result << std::endl;
    
    // std::function with auto
    auto std_func = std::function<int(int, int)>(add);
    std::cout << "std::function result: " << std_func(7, 8) << std::endl;
    
    // 7. Auto return type deduction (C++14)
    std::cout << "\n7. Auto Return Type Deduction:" << std::endl;
    
    auto add_result = add(15, 25);         // Calls function with trailing return type
    auto mult_result = multiply(3.5, 2.0); // Calls function with auto return type
    
    std::cout << "Add result: " << add_result << std::endl;
    std::cout << "Multiply result: " << mult_result << std::endl;
    
    // 8. Auto with templates
    std::cout << "\n8. Auto with Templates:" << std::endl;
    
    std::vector<std::string> words = {"Hello", "World", "C++", "Auto"};
    auto first_word = getFirst(words);
    std::cout << "First word: " << first_word << std::endl;
    
    std::vector<double> values = {1.1, 2.2, 3.3};
    auto first_value = getFirst(values);
    std::cout << "First value: " << first_value << std::endl;
    
    // 9. Auto with structured bindings (C++17)
    std::cout << "\n9. Auto with Structured Bindings (C++17):" << std::endl;
    
    auto pair = std::make_pair(42, "Answer");
    auto [number, text] = pair;            // Structured binding
    std::cout << "Pair decomposition: " << number << " -> " << text << std::endl;
    
    // With map
    for (const auto& [name, age] : ages) {
        std::cout << "Structured binding: " << name << " is " << age << " years old" << std::endl;
    }
    
    // 10. Common pitfalls and best practices
    std::cout << "\n10. Common Pitfalls:" << std::endl;
    
    // Pitfall 1: auto drops references and const
    const int const_val = 100;
    auto dropped_const = const_val;        // auto -> int, not const int
    const auto preserved_const = const_val; // const auto -> const int
    
    std::cout << "Original const_val: " << const_val << std::endl;
    dropped_const = 200;  // OK - const was dropped
    std::cout << "Modified dropped_const: " << dropped_const << std::endl;
    // preserved_const = 300;  // Error - const preserved
    
    // Pitfall 2: auto with braced initialization
    auto x1 = 42;          // int
    auto x2{42};           // int (C++17), std::initializer_list<int> (C++11/14)
    auto x3 = {42};        // std::initializer_list<int>
    
    std::cout << "x1: " << x1 << std::endl;
    std::cout << "x2: " << x2 << std::endl;
    std::cout << "x3 size: " << x3.size() << std::endl;
    
    // 11. Performance considerations
    std::cout << "\n11. Performance Considerations:" << std::endl;
    
    std::vector<int> large_vector(1000, 42);
    
    // Good: no unnecessary copy
    const auto& vec_ref_good = large_vector;
    
    // Bad: unnecessary copy
    auto vec_copy_bad = large_vector;
    
    std::cout << "Reference size: " << vec_ref_good.size() << std::endl;
    std::cout << "Copy size: " << vec_copy_bad.size() << std::endl;
    
    std::cout << "\n=== AUTO BENEFITS ===" << std::endl;
    std::cout << "✅ Type safety - compiler deduces exact type" << std::endl;
    std::cout << "✅ Less verbose code - especially with complex types" << std::endl;
    std::cout << "✅ Easier maintenance - type changes propagate automatically" << std::endl;
    std::cout << "✅ Better with templates - works with any type" << std::endl;
    std::cout << "✅ Required for lambdas and some template expressions" << std::endl;
    
    std::cout << "\n=== AUTO BEST PRACTICES ===" << std::endl;
    std::cout << "⚠️  Use const auto& for expensive-to-copy types" << std::endl;
    std::cout << "⚠️  Be explicit with const and references when needed" << std::endl;
    std::cout << "⚠️  Avoid auto with braced initialization for single values" << std::endl;
    std::cout << "⚠️  Consider readability - sometimes explicit types are clearer" << std::endl;
    std::cout << "⚠️  Use auto for complex types, explicit types for simple ones" << std::endl;
    
    return 0;
}

/*
Key Takeaways:

1. Auto Storage Class (Pre-C++11):
   - Default storage class for local variables
   - Automatic storage duration (stack allocation)
   - Destroyed when out of scope

2. Auto Type Deduction (C++11+):
   - Compiler deduces type from initializer
   - Reduces verbosity with complex types
   - Essential for lambdas and generic programming

3. Type Deduction Rules:
   - auto drops const and references
   - const auto preserves const
   - auto& creates reference
   - const auto& creates const reference

4. Common Use Cases:
   - Iterator types
   - Lambda expressions
   - Template return types
   - Range-based for loops
   - Complex nested types

5. Best Practices:
   - Use for complex types
   - Be explicit with const/references
   - Consider readability
   - Avoid with simple types where clarity is important
*/
