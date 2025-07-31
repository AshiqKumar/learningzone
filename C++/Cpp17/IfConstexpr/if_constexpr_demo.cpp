// C++17 if constexpr - Compile-time Conditional Compilation
// Compile: g++ -std=c++17 -o if_constexpr_demo if_constexpr_demo.cpp
// Run: ./if_constexpr_demo

#include <iostream>
#include <type_traits>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <optional>

// 1. Basic if constexpr example
template<typename T>
void print_type_info(const T& value) {
    std::cout << "Value: " << value << std::endl;
    
    if constexpr (std::is_integral_v<T>) {
        std::cout << "  -> This is an integral type" << std::endl;
        std::cout << "  -> Size: " << sizeof(T) << " bytes" << std::endl;
        std::cout << "  -> Max value: " << std::numeric_limits<T>::max() << std::endl;
    }
    else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "  -> This is a floating-point type" << std::endl;
        std::cout << "  -> Precision: " << std::numeric_limits<T>::digits10 << " decimal digits" << std::endl;
        std::cout << "  -> Max value: " << std::numeric_limits<T>::max() << std::endl;
    }
    else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "  -> This is a string" << std::endl;
        std::cout << "  -> Length: " << value.length() << " characters" << std::endl;
        std::cout << "  -> Empty: " << (value.empty() ? "Yes" : "No") << std::endl;
    }
    else {
        std::cout << "  -> This is some other type" << std::endl;
        std::cout << "  -> Size: " << sizeof(T) << " bytes" << std::endl;
    }
    std::cout << std::endl;
}

// 2. Generic container size function
template<typename Container>
auto get_size_info(const Container& container) {
    if constexpr (std::is_same_v<Container, std::string>) {
        return container.length();
    }
    else if constexpr (requires { container.size(); }) {
        return container.size();
    }
    else {
        return sizeof(container);
    }
}

// 3. Arithmetic operations with type checking
template<typename T>
T safe_arithmetic(T a, T b, char operation) {
    if constexpr (std::is_arithmetic_v<T>) {
        switch (operation) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': 
                if constexpr (std::is_floating_point_v<T>) {
                    return a / b;  // Direct division for floating point
                } else {
                    return (b != 0) ? a / b : 0;  // Safe division for integers
                }
            default:
                std::cout << "Unknown operation: " << operation << std::endl;
                return T{};
        }
    } else {
        static_assert(std::is_arithmetic_v<T>, "Type must be arithmetic");
        return T{};  // Never reached, but needed for compilation
    }
}

// 4. Generic print function for different container types
template<typename T>
void print_container(const T& container) {
    if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "String: \"" << container << "\"" << std::endl;
    }
    else if constexpr (requires { container.begin(); container.end(); }) {
        std::cout << "Container contents: ";
        for (const auto& element : container) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    else if constexpr (std::is_array_v<T>) {
        std::cout << "Array contents: ";
        for (const auto& element : container) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Single value: " << container << std::endl;
    }
}

// 5. Advanced: recursive template with if constexpr
template<typename T>
constexpr T factorial(T n) {
    if constexpr (std::is_integral_v<T>) {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    } else {
        static_assert(std::is_integral_v<T>, "Factorial requires integral type");
        return T{};
    }
}

// 6. Type-specific serialization
template<typename T>
std::string serialize(const T& value) {
    if constexpr (std::is_arithmetic_v<T>) {
        return std::to_string(value);
    }
    else if constexpr (std::is_same_v<T, std::string>) {
        return "\"" + value + "\"";
    }
    else if constexpr (std::is_same_v<T, const char*>) {
        return "\"" + std::string(value) + "\"";
    }
    else if constexpr (requires { value.begin(); value.end(); }) {
        std::string result = "[";
        bool first = true;
        for (const auto& element : value) {
            if (!first) result += ", ";
            result += serialize(element);
            first = false;
        }
        result += "]";
        return result;
    }
    else {
        return "unknown_type";
    }
}

// 7. Smart pointer handling
template<typename T>
void handle_pointer(const T& ptr) {
    if constexpr (std::is_pointer_v<T>) {
        std::cout << "Raw pointer: ";
        if (ptr) {
            std::cout << *ptr << std::endl;
        } else {
            std::cout << "null" << std::endl;
        }
    }
    else if constexpr (requires { ptr.get(); }) {  // Smart pointer check
        std::cout << "Smart pointer: ";
        if (ptr) {
            std::cout << *ptr << std::endl;
        } else {
            std::cout << "null" << std::endl;
        }
    }
    else {
        std::cout << "Not a pointer: " << ptr << std::endl;
    }
}

// 8. Optional handling
template<typename T>
void handle_optional_like(const T& value) {
    if constexpr (requires { value.has_value(); value.value(); }) {
        std::cout << "Optional-like type: ";
        if (value.has_value()) {
            std::cout << value.value() << std::endl;
        } else {
            std::cout << "empty" << std::endl;
        }
    } else {
        std::cout << "Regular value: " << value << std::endl;
    }
}

// 9. Comparison with C++11/14 approach
template<typename T>
void old_style_type_handling(const T& value) {
    std::cout << "\n=== C++11/14 Style (SFINAE) ===" << std::endl;
    
    // This would require multiple function overloads or SFINAE
    old_style_print_integral(value);
    old_style_print_floating(value);
    old_style_print_other(value);
}

// SFINAE versions (C++11/14 approach)
template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
old_style_print_integral(const T& value) {
    std::cout << "Integral (SFINAE): " << value << std::endl;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
old_style_print_floating(const T& value) {
    std::cout << "Floating (SFINAE): " << value << std::endl;
}

template<typename T>
typename std::enable_if<!std::is_arithmetic<T>::value, void>::type
old_style_print_other(const T& value) {
    std::cout << "Other (SFINAE): " << value << std::endl;
}

// 10. Complex template with multiple conditions
template<typename Container, typename Value>
auto find_and_process(Container& container, const Value& value) {
    if constexpr (std::is_same_v<Container, std::vector<Value>>) {
        std::cout << "Processing std::vector" << std::endl;
        auto it = std::find(container.begin(), container.end(), value);
        if (it != container.end()) {
            *it = value * 2;  // Double the value
            return true;
        }
    }
    else if constexpr (std::is_same_v<Container, std::set<Value>>) {
        std::cout << "Processing std::set" << std::endl;
        auto it = container.find(value);
        if (it != container.end()) {
            container.erase(it);
            container.insert(value * 2);
            return true;
        }
    }
    else if constexpr (requires { container.find(value); }) {
        std::cout << "Processing associative container" << std::endl;
        auto it = container.find(value);
        return it != container.end();
    }
    else {
        std::cout << "Unsupported container type" << std::endl;
        return false;
    }
    return false;
}

int main() {
    std::cout << "=== C++17 IF CONSTEXPR DEMO ===" << std::endl;
    
    // 1. Basic type-specific behavior
    std::cout << "\n1. Type-Specific Behavior:" << std::endl;
    
    print_type_info(42);
    print_type_info(3.14159);
    print_type_info(std::string("Hello, World!"));
    print_type_info('A');
    
    // 2. Container size handling
    std::cout << "\n2. Generic Container Size:" << std::endl;
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::string str = "Hello";
    std::map<int, std::string> map_container = {{1, "one"}, {2, "two"}};
    int single_value = 42;
    
    std::cout << "Vector size: " << get_size_info(vec) << std::endl;
    std::cout << "String length: " << get_size_info(str) << std::endl;
    std::cout << "Map size: " << get_size_info(map_container) << std::endl;
    std::cout << "Single value size: " << get_size_info(single_value) << std::endl;
    
    // 3. Arithmetic operations with type safety
    std::cout << "\n3. Safe Arithmetic Operations:" << std::endl;
    
    std::cout << "Integer arithmetic:" << std::endl;
    std::cout << "10 + 5 = " << safe_arithmetic(10, 5, '+') << std::endl;
    std::cout << "10 / 3 = " << safe_arithmetic(10, 3, '/') << std::endl;
    std::cout << "10 / 0 = " << safe_arithmetic(10, 0, '/') << std::endl;
    
    std::cout << "Floating-point arithmetic:" << std::endl;
    std::cout << "10.0 + 5.5 = " << safe_arithmetic(10.0, 5.5, '+') << std::endl;
    std::cout << "10.0 / 3.0 = " << safe_arithmetic(10.0, 3.0, '/') << std::endl;
    std::cout << "10.0 / 0.0 = " << safe_arithmetic(10.0, 0.0, '/') << std::endl;
    
    // 4. Generic container printing
    std::cout << "\n4. Generic Container Printing:" << std::endl;
    
    print_container(vec);
    print_container(str);
    print_container(42);
    
    std::set<std::string> string_set = {"apple", "banana", "cherry"};
    print_container(string_set);
    
    int arr[] = {10, 20, 30, 40, 50};
    print_container(arr);
    
    // 5. Compile-time factorial
    std::cout << "\n5. Compile-time Factorial:" << std::endl;
    
    constexpr int fact5 = factorial(5);
    constexpr long fact10 = factorial(10L);
    
    std::cout << "5! = " << fact5 << std::endl;
    std::cout << "10! = " << fact10 << std::endl;
    
    // This would cause a compile-time error:
    // constexpr double bad_fact = factorial(5.0);
    
    // 6. Type-specific serialization
    std::cout << "\n6. Type-Specific Serialization:" << std::endl;
    
    std::cout << "Serialize int: " << serialize(42) << std::endl;
    std::cout << "Serialize double: " << serialize(3.14159) << std::endl;
    std::cout << "Serialize string: " << serialize(std::string("hello")) << std::endl;
    std::cout << "Serialize const char*: " << serialize("world") << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Serialize vector: " << serialize(numbers) << std::endl;
    
    std::vector<std::string> words = {"foo", "bar", "baz"};
    std::cout << "Serialize string vector: " << serialize(words) << std::endl;
    
    // 7. Smart pointer handling
    std::cout << "\n7. Pointer Type Handling:" << std::endl;
    
    int value = 100;
    int* raw_ptr = &value;
    int* null_ptr = nullptr;
    auto unique_ptr = std::make_unique<int>(200);
    auto shared_ptr = std::make_shared<int>(300);
    std::unique_ptr<int> null_unique;
    
    handle_pointer(raw_ptr);
    handle_pointer(null_ptr);
    handle_pointer(unique_ptr);
    handle_pointer(shared_ptr);
    handle_pointer(null_unique);
    handle_pointer(42);  // Not a pointer
    
    // 8. Optional handling
    std::cout << "\n8. Optional-like Type Handling:" << std::endl;
    
    std::optional<int> opt_with_value = 42;
    std::optional<int> opt_empty;
    int regular_int = 123;
    
    handle_optional_like(opt_with_value);
    handle_optional_like(opt_empty);
    handle_optional_like(regular_int);
    
    // 9. Complex container processing
    std::cout << "\n9. Complex Container Processing:" << std::endl;
    
    std::vector<int> test_vector = {1, 2, 3, 4, 5};
    std::set<int> test_set = {10, 20, 30, 40, 50};
    std::map<int, std::string> test_map = {{1, "one"}, {2, "two"}, {3, "three"}};
    
    std::cout << "Before processing:" << std::endl;
    print_container(test_vector);
    print_container(test_set);
    
    bool result1 = find_and_process(test_vector, 3);
    bool result2 = find_and_process(test_set, 30);
    bool result3 = find_and_process(test_map, 2);
    
    std::cout << "After processing:" << std::endl;
    print_container(test_vector);
    print_container(test_set);
    
    std::cout << "Results: " << std::boolalpha 
              << result1 << ", " << result2 << ", " << result3 << std::endl;
    
    // 10. Performance comparison
    std::cout << "\n10. Comparison with Traditional Approaches:" << std::endl;
    
    std::cout << "=== C++17 if constexpr Style ===" << std::endl;
    print_type_info(42);
    
    // Show the old style approach for comparison
    old_style_type_handling(42);
    old_style_type_handling(3.14);
    old_style_type_handling(std::string("test"));
    
    // 11. Nested if constexpr
    std::cout << "\n11. Nested Conditional Compilation:" << std::endl;
    
    auto process_numeric = [](auto value) {
        if constexpr (std::is_arithmetic_v<decltype(value)>) {
            std::cout << "Numeric value: " << value << std::endl;
            
            if constexpr (std::is_integral_v<decltype(value)>) {
                if constexpr (std::is_signed_v<decltype(value)>) {
                    std::cout << "  -> Signed integer" << std::endl;
                } else {
                    std::cout << "  -> Unsigned integer" << std::endl;
                }
            } else {
                std::cout << "  -> Floating-point number" << std::endl;
            }
            
            if constexpr (sizeof(value) >= 8) {
                std::cout << "  -> Large type (≥8 bytes)" << std::endl;
            } else {
                std::cout << "  -> Small type (<8 bytes)" << std::endl;
            }
        } else {
            std::cout << "Non-numeric value: " << value << std::endl;
        }
    };
    
    process_numeric(42);
    process_numeric(-17);
    process_numeric(3.14159);
    process_numeric(std::string("not numeric"));
    process_numeric(static_cast<unsigned long long>(1000000ULL));
    
    std::cout << "\n=== IF CONSTEXPR BENEFITS ===" << std::endl;
    std::cout << "✅ Cleaner code than SFINAE - no complex template specializations" << std::endl;
    std::cout << "✅ Compile-time branching - unused branches completely eliminated" << std::endl;
    std::cout << "✅ Better error messages - clearer compilation failures" << std::endl;
    std::cout << "✅ Single function template instead of multiple overloads" << std::endl;
    std::cout << "✅ Works with any compile-time constant expressions" << std::endl;
    std::cout << "✅ Nested conditionals support complex logic" << std::endl;
    std::cout << "✅ Perfect for generic programming and template metaprogramming" << std::endl;
    std::cout << "✅ Zero runtime overhead - all decisions made at compile time" << std::endl;
    std::cout << "⚠️  Requires C++17 compiler support" << std::endl;
    std::cout << "⚠️  Only works with compile-time constant expressions" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++17 -Wall -Wextra -o if_constexpr_demo if_constexpr_demo.cpp
./if_constexpr_demo

C++17 if constexpr Key Features:
1. Compile-time conditional compilation within template functions
2. Discards branches that don't compile for specific instantiations
3. Cleaner alternative to SFINAE and template specialization
4. Works with any compile-time constant boolean expression

Syntax:
if constexpr (condition) {
    // Code only compiled if condition is true
} else if constexpr (other_condition) {
    // Alternative branch
} else {
    // Default branch
}

Benefits over C++11/14 SFINAE:
- Single function instead of multiple template specializations
- Cleaner, more readable code
- Better compiler error messages
- Easier to maintain and understand
- Natural conditional logic flow

Common Use Cases:
- Type trait based branching
- Generic algorithm customization
- Template metaprogramming
- Container-agnostic functions
- Type-safe generic operations

Performance:
- Zero runtime overhead
- Unused branches completely eliminated from binary
- Compile-time decision making
- No virtual dispatch or runtime checks

Best Practices:
- Use for compile-time constant conditions only
- Prefer over complex SFINAE patterns
- Combine with type traits for powerful generic code
- Keep conditions simple and readable
- Document template requirements clearly
*/
