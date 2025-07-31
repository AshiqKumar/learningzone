// C++14 Auto Return Type Deduction - Functions with auto
// Compile: g++ -std=c++14 -o auto_return_demo auto_return_demo.cpp
// Run: ./auto_return_demo

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>

// 1. Simple auto return type deduction
auto add(int a, int b) {
    return a + b;  // Compiler deduces return type as int
}

auto multiply(double x, double y) {
    return x * y;  // Compiler deduces return type as double
}

// 2. Template functions with auto return type
template<typename T, typename U>
auto generic_add(T a, U b) {
    return a + b;  // Return type deduced from a + b
}

// 3. Complex return type deduction
auto create_vector() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    return vec;  // Return type: std::vector<int>
}

auto create_map() {
    std::map<std::string, int> m;
    m["one"] = 1;
    m["two"] = 2;
    return m;  // Return type: std::map<std::string, int>
}

// 4. Conditional return types
auto conditional_return(bool flag) {
    if (flag) {
        return 42;     // int
    } else {
        return 3.14;   // double - ERROR! Different types
    }
}

// Fixed version with consistent types
auto conditional_return_fixed(bool flag) {
    if (flag) {
        return 42.0;   // double
    } else {
        return 3.14;   // double - OK!
    }
}

// 5. Recursive functions (requires forward declaration)
auto factorial(int n) -> int;  // Forward declaration needed for recursion

auto factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);  // OK with forward declaration
    }
}

// 6. Lambda-like function objects
auto create_multiplier(int factor) {
    return [factor](int x) { return x * factor; };
}

// 7. Auto return with references
auto& get_first_element(std::vector<int>& vec) {
    return vec[0];  // Returns int&
}

const auto& get_const_reference(const std::vector<std::string>& vec) {
    return vec[0];  // Returns const std::string&
}

// 8. Auto return with pointers
auto find_element(std::vector<int>& vec, int target) {
    for (auto& element : vec) {
        if (element == target) {
            return &element;  // Returns int*
        }
    }
    return static_cast<int*>(nullptr);  // Explicit cast needed for consistency
}

// 9. Member function with auto return type
class Calculator {
public:
    auto add(double a, double b) {
        return a + b;
    }
    
    auto get_pi() const {
        return 3.14159;
    }
    
    auto create_pair(int x, int y) {
        return std::make_pair(x, y);  // Returns std::pair<int, int>
    }
};

// 10. Function returning function (higher-order functions)
auto create_adder(int base) {
    return [base](int x) -> int {
        return base + x;
    };
}

auto create_operation(char op) {
    switch (op) {
        case '+':
            return [](int a, int b) { return a + b; };
        case '-':
            return [](int a, int b) { return a - b; };
        case '*':
            return [](int a, int b) { return a * b; };
        default:
            return [](int a, int b) { return 0; };
    }
}

// 11. Auto with complex STL types
auto process_data() {
    std::map<std::string, std::vector<int>> data;
    data["evens"] = {2, 4, 6, 8};
    data["odds"] = {1, 3, 5, 7};
    return data;  // Compiler deduces complex type
}

// 12. SFINAE-friendly auto return
template<typename T>
auto safe_divide(T a, T b) -> decltype(a / b) {
    if (b != T{}) {
        return a / b;
    }
    throw std::runtime_error("Division by zero");
}

// 13. Auto return with smart pointers
auto create_unique_int(int value) {
    return std::make_unique<int>(value);
}

auto create_shared_string(const std::string& str) {
    return std::make_shared<std::string>(str);
}

int main() {
    std::cout << "=== C++14 AUTO RETURN TYPE DEDUCTION DEMO ===" << std::endl;
    
    // 1. Basic auto return type deduction
    std::cout << "\n1. Basic Auto Return Type Deduction:" << std::endl;
    
    auto result1 = add(5, 3);
    auto result2 = multiply(2.5, 4.0);
    
    std::cout << "add(5, 3) = " << result1 << " (type: int)" << std::endl;
    std::cout << "multiply(2.5, 4.0) = " << result2 << " (type: double)" << std::endl;
    
    // 2. Template functions with auto return
    std::cout << "\n2. Template Functions with Auto Return:" << std::endl;
    
    auto int_add = generic_add(10, 20);        // int + int = int
    auto mixed_add = generic_add(10, 2.5);     // int + double = double
    auto string_add = generic_add(std::string("Hello, "), std::string("World!"));
    
    std::cout << "generic_add(10, 20) = " << int_add << std::endl;
    std::cout << "generic_add(10, 2.5) = " << mixed_add << std::endl;
    std::cout << "generic_add(string, string) = " << string_add << std::endl;
    
    // 3. Complex return types
    std::cout << "\n3. Complex Return Types:" << std::endl;
    
    auto vec = create_vector();
    auto map = create_map();
    
    std::cout << "Vector contents: ";
    for (auto value : vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Map contents: ";
    for (const auto& pair : map) {
        std::cout << pair.first << "=" << pair.second << " ";
    }
    std::cout << std::endl;
    
    // 4. Conditional return (fixed version)
    std::cout << "\n4. Conditional Return Types:" << std::endl;
    
    auto cond_result1 = conditional_return_fixed(true);
    auto cond_result2 = conditional_return_fixed(false);
    
    std::cout << "conditional_return_fixed(true) = " << cond_result1 << std::endl;
    std::cout << "conditional_return_fixed(false) = " << cond_result2 << std::endl;
    
    // 5. Recursive functions
    std::cout << "\n5. Recursive Functions:" << std::endl;
    
    auto fact5 = factorial(5);
    auto fact7 = factorial(7);
    
    std::cout << "factorial(5) = " << fact5 << std::endl;
    std::cout << "factorial(7) = " << fact7 << std::endl;
    
    // 6. Lambda-like function objects
    std::cout << "\n6. Function Objects:" << std::endl;
    
    auto times3 = create_multiplier(3);
    auto times5 = create_multiplier(5);
    
    std::cout << "times3(10) = " << times3(10) << std::endl;
    std::cout << "times5(7) = " << times5(7) << std::endl;
    
    // 7. References and pointers
    std::cout << "\n7. References and Pointers:" << std::endl;
    
    std::vector<int> numbers = {100, 200, 300};
    std::vector<std::string> words = {"Hello", "World", "C++14"};
    
    auto& first_num = get_first_element(numbers);
    const auto& first_word = get_const_reference(words);
    
    std::cout << "First number: " << first_num << std::endl;
    std::cout << "First word: " << first_word << std::endl;
    
    // Modify through reference
    first_num = 999;
    std::cout << "After modification, first number: " << numbers[0] << std::endl;
    
    // Pointer return
    auto* found = find_element(numbers, 200);
    if (found) {
        std::cout << "Found element: " << *found << std::endl;
    }
    
    auto* not_found = find_element(numbers, 404);
    if (!not_found) {
        std::cout << "Element 404 not found (nullptr returned)" << std::endl;
    }
    
    // 8. Member functions with auto return
    std::cout << "\n8. Member Functions with Auto Return:" << std::endl;
    
    Calculator calc;
    auto sum = calc.add(15.5, 24.3);
    auto pi = calc.get_pi();
    auto coord = calc.create_pair(10, 20);
    
    std::cout << "Calculator add(15.5, 24.3) = " << sum << std::endl;
    std::cout << "Calculator pi = " << pi << std::endl;
    std::cout << "Calculator pair = (" << coord.first << ", " << coord.second << ")" << std::endl;
    
    // 9. Higher-order functions
    std::cout << "\n9. Higher-Order Functions:" << std::endl;
    
    auto add10 = create_adder(10);
    auto add100 = create_adder(100);
    
    std::cout << "add10(5) = " << add10(5) << std::endl;
    std::cout << "add100(25) = " << add100(25) << std::endl;
    
    auto add_op = create_operation('+');
    auto mul_op = create_operation('*');
    auto sub_op = create_operation('-');
    
    std::cout << "add_op(8, 3) = " << add_op(8, 3) << std::endl;
    std::cout << "mul_op(8, 3) = " << mul_op(8, 3) << std::endl;
    std::cout << "sub_op(8, 3) = " << sub_op(8, 3) << std::endl;
    
    // 10. Complex STL types
    std::cout << "\n10. Complex STL Types:" << std::endl;
    
    auto complex_data = process_data();
    
    for (const auto& category : complex_data) {
        std::cout << category.first << ": ";
        for (auto value : category.second) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    
    // 11. Smart pointers
    std::cout << "\n11. Smart Pointers with Auto Return:" << std::endl;
    
    auto unique_int = create_unique_int(42);
    auto shared_str = create_shared_string("C++14 is awesome!");
    
    std::cout << "unique_ptr<int>: " << *unique_int << std::endl;
    std::cout << "shared_ptr<string>: " << *shared_str << std::endl;
    std::cout << "shared_str use_count: " << shared_str.use_count() << std::endl;
    
    // Create another shared_ptr to the same string
    auto shared_str2 = shared_str;
    std::cout << "After copying, use_count: " << shared_str.use_count() << std::endl;
    
    // 12. Type deduction examples
    std::cout << "\n12. Type Deduction Examples:" << std::endl;
    
    // The compiler deduces these types automatically
    auto deduced_int = add(1, 2);           // int
    auto deduced_double = multiply(1.0, 2.0); // double
    auto deduced_vector = create_vector();   // std::vector<int>
    auto deduced_lambda = [](int x) { return x * 2; }; // lambda type
    
    std::cout << "Deduced types work seamlessly:" << std::endl;
    std::cout << "  Integer result: " << deduced_int << std::endl;
    std::cout << "  Double result: " << deduced_double << std::endl;
    std::cout << "  Vector size: " << deduced_vector.size() << std::endl;
    std::cout << "  Lambda result: " << deduced_lambda(5) << std::endl;
    
    // 13. Error examples (commented out)
    std::cout << "\n13. Common Pitfalls (These would cause errors):" << std::endl;
    std::cout << "// auto bad_conditional(bool b) {" << std::endl;
    std::cout << "//     if (b) return 1;      // int" << std::endl;
    std::cout << "//     else return 1.0;     // double - ERROR!" << std::endl;
    std::cout << "// }" << std::endl;
    std::cout << std::endl;
    std::cout << "// auto bad_recursive(int n) {" << std::endl;
    std::cout << "//     if (n <= 1) return 1;" << std::endl;
    std::cout << "//     return n * bad_recursive(n-1); // ERROR without forward decl!" << std::endl;
    std::cout << "// }" << std::endl;
    
    std::cout << "\n=== AUTO RETURN TYPE BENEFITS ===" << std::endl;
    std::cout << "✅ Cleaner code - no need to specify complex return types" << std::endl;
    std::cout << "✅ Template-friendly - works with any type combination" << std::endl;
    std::cout << "✅ Maintenance - changes to implementation don't require return type updates" << std::endl;
    std::cout << "✅ Generic programming - enables more flexible template code" << std::endl;
    std::cout << "✅ Less typing - especially useful with complex STL types" << std::endl;
    std::cout << "⚠️  All return paths must deduce to the same type" << std::endl;
    std::cout << "⚠️  Recursive functions need forward declaration or trailing return type" << std::endl;
    std::cout << "⚠️  Makes function signatures less explicit (can be good or bad)" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++14 -Wall -Wextra -o auto_return_demo auto_return_demo.cpp
./auto_return_demo

C++14 Auto Return Type Features:
1. Function return type deduction from return statement
2. Works with templates for generic programming
3. Handles complex STL types automatically
4. Supports references and pointers
5. Works with member functions and lambdas

Key Rules:
- All return paths must deduce to the same type
- Recursive functions need forward declaration
- Template instantiation determines actual return type
- Works with references (&) and const qualifiers

Benefits:
- Reduces boilerplate code for complex return types
- Makes template functions more flexible
- Easier maintenance when implementation changes
- Perfect for generic programming patterns

Best Practices:
- Use when return type is obvious from context
- Be careful with conditional returns (ensure same type)
- Consider explicit return types for public APIs
- Great for internal/private functions and lambdas
*/
