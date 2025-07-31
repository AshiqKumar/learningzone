// C++11 Auto Keyword - Automatic Type Deduction
// Compile: g++ -std=c++11 -o auto_demo auto_keyword_demo.cpp
// Run: ./auto_demo

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

int main() {
    std::cout << "=== C++11 AUTO KEYWORD DEMO ===" << std::endl;
    
    // 1. Basic auto usage
    std::cout << "\n1. Basic Auto Usage:" << std::endl;
    auto x = 42;           // int
    auto y = 3.14;         // double
    auto z = 'A';          // char
    auto str = "Hello";    // const char*
    auto flag = true;      // bool
    
    std::cout << "x = " << x << " (int)" << std::endl;
    std::cout << "y = " << y << " (double)" << std::endl;
    std::cout << "z = " << z << " (char)" << std::endl;
    std::cout << "str = " << str << " (const char*)" << std::endl;
    std::cout << "flag = " << std::boolalpha << flag << " (bool)" << std::endl;
    
    // 2. Auto with containers
    std::cout << "\n2. Auto with Containers:" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Before C++11: std::vector<int>::iterator it = numbers.begin();
    auto it = numbers.begin();
    std::cout << "First element: " << *it << std::endl;
    
    // Auto with map
    std::map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};
    
    // Before C++11: std::map<std::string, int>::iterator map_it = ages.begin();
    auto map_it = ages.begin();
    std::cout << "First person: " << map_it->first << " is " << map_it->second << " years old" << std::endl;
    
    // 3. Auto in range-based for loops (C++11)
    std::cout << "\n3. Auto in Range-based For Loops:" << std::endl;
    std::cout << "Numbers: ";
    for (auto num : numbers) {  // auto deduces int
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Ages: ";
    for (auto& pair : ages) {  // auto& deduces std::pair<const std::string, int>&
        std::cout << pair.first << ":" << pair.second << " ";
    }
    std::cout << std::endl;
    
    // 4. Auto with function return types
    std::cout << "\n4. Auto with Function Return Types:" << std::endl;
    
    // Lambda with auto (C++11)
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    
    auto result = add(10, 20);
    std::cout << "10 + 20 = " << result << std::endl;
    
    // Auto with find algorithm
    auto found = std::find(numbers.begin(), numbers.end(), 3);
    if (found != numbers.end()) {
        std::cout << "Found number: " << *found << std::endl;
    }
    
    // 5. Auto with references and pointers
    std::cout << "\n5. Auto with References and Pointers:" << std::endl;
    int original = 100;
    
    auto copy = original;        // int (copy)
    auto& ref = original;        // int& (reference)
    auto* ptr = &original;       // int* (pointer)
    
    std::cout << "Original: " << original << std::endl;
    std::cout << "Copy: " << copy << std::endl;
    std::cout << "Reference: " << ref << std::endl;
    std::cout << "Pointer: " << *ptr << std::endl;
    
    // Modify through reference
    ref = 200;
    std::cout << "After modifying reference:" << std::endl;
    std::cout << "Original: " << original << " (changed!)" << std::endl;
    std::cout << "Copy: " << copy << " (unchanged)" << std::endl;
    
    // 6. Auto with const
    std::cout << "\n6. Auto with Const:" << std::endl;
    const int const_val = 42;
    
    auto auto_val = const_val;        // int (const is dropped)
    const auto const_auto = const_val; // const int
    auto& ref_to_const = const_val;    // const int& (const preserved in reference)
    
    std::cout << "const_val: " << const_val << std::endl;
    std::cout << "auto_val: " << auto_val << std::endl;
    std::cout << "const_auto: " << const_auto << std::endl;
    std::cout << "ref_to_const: " << ref_to_const << std::endl;
    
    // auto_val = 50;        // OK - auto_val is not const
    // const_auto = 50;      // Error - const_auto is const
    // ref_to_const = 50;    // Error - ref_to_const refers to const
    
    // 7. Auto pitfalls and best practices
    std::cout << "\n7. Auto Best Practices:" << std::endl;
    
    // Good: Clear intent
    auto name = std::string("John");  // Explicitly std::string
    std::cout << "Name: " << name << std::endl;
    
    // Careful with braced initializers
    auto list1 = {1, 2, 3};        // std::initializer_list<int>
    // auto list2{1, 2, 3};        // Error in C++11 (OK in C++17)
    auto single = {42};            // std::initializer_list<int> with one element
    
    std::cout << "list1 size: " << list1.size() << std::endl;
    std::cout << "single size: " << single.size() << std::endl;
    
    // 8. Complex type simplification
    std::cout << "\n8. Complex Type Simplification:" << std::endl;
    
    // Complex nested container
    std::map<std::string, std::vector<int>> data = {
        {"group1", {1, 2, 3}},
        {"group2", {4, 5, 6}}
    };
    
    // Before auto: std::map<std::string, std::vector<int>>::iterator complex_it = data.begin();
    auto complex_it = data.begin();
    
    std::cout << "Group: " << complex_it->first << ", Values: ";
    for (auto value : complex_it->second) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\n=== AUTO KEYWORD BENEFITS ===" << std::endl;
    std::cout << "✅ Reduces verbosity and improves readability" << std::endl;
    std::cout << "✅ Automatically adapts to type changes" << std::endl;
    std::cout << "✅ Prevents type mismatches" << std::endl;
    std::cout << "✅ Simplifies complex template types" << std::endl;
    std::cout << "✅ Makes generic programming easier" << std::endl;
    std::cout << "⚠️  Be careful with const and references" << std::endl;
    std::cout << "⚠️  Avoid when type clarity is important" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -o auto_demo auto_keyword_demo.cpp
./auto_demo

Key Points About Auto:
1. Type deduction happens at compile time
2. const is dropped unless explicitly specified
3. References must be explicitly specified with &
4. Great for iterator types and complex templates
5. Use with care - sometimes explicit types are clearer
6. Particularly useful with lambdas and STL algorithms
*/
