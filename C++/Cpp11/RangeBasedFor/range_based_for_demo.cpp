// C++11 Range-based For Loops
// Compile: g++ -std=c++11 -o range_for_demo range_based_for_demo.cpp
// Run: ./range_for_demo

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <string>
#include <list>

int main() {
    std::cout << "=== C++11 RANGE-BASED FOR LOOPS DEMO ===" << std::endl;
    
    // 1. Basic range-based for loop
    std::cout << "\n1. Basic Range-based For Loop:" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Traditional for loop
    std::cout << "Traditional for loop: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
    
    // Range-based for loop (C++11)
    std::cout << "Range-based for loop: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 2. Auto with range-based for
    std::cout << "\n2. Auto with Range-based For:" << std::endl;
    std::cout << "Using auto: ";
    for (auto num : numbers) {  // auto deduces int
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 3. References in range-based for
    std::cout << "\n3. References in Range-based For:" << std::endl;
    std::vector<int> mutable_numbers = {10, 20, 30, 40, 50};
    
    std::cout << "Before modification: ";
    for (auto num : mutable_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Modify using references
    for (auto& num : mutable_numbers) {  // Reference allows modification
        num *= 2;
    }
    
    std::cout << "After modification (doubled): ";
    for (auto num : mutable_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 4. Const references for read-only access
    std::cout << "\n4. Const References (Efficient Read-only):" << std::endl;
    std::vector<std::string> words = {"Hello", "World", "C++11", "Rocks"};
    
    std::cout << "Words (const ref): ";
    for (const auto& word : words) {  // const& avoids copying strings
        std::cout << word << " ";
    }
    std::cout << std::endl;
    
    // 5. Range-based for with different containers
    std::cout << "\n5. Different Container Types:" << std::endl;
    
    // Array
    int arr[] = {1, 2, 3, 4, 5};
    std::cout << "Array: ";
    for (auto elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // std::array (C++11)
    std::array<int, 4> std_arr = {6, 7, 8, 9};
    std::cout << "std::array: ";
    for (auto elem : std_arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // std::list
    std::list<char> char_list = {'A', 'B', 'C', 'D'};
    std::cout << "std::list: ";
    for (auto ch : char_list) {
        std::cout << ch << " ";
    }
    std::cout << std::endl;
    
    // 6. Range-based for with associative containers
    std::cout << "\n6. Associative Containers:" << std::endl;
    
    // std::map
    std::map<std::string, int> ages = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };
    
    std::cout << "std::map (key-value pairs):" << std::endl;
    for (const auto& pair : ages) {  // pair is std::pair<const std::string, int>
        std::cout << "  " << pair.first << " is " << pair.second << " years old" << std::endl;
    }
    
    // std::set
    std::set<int> unique_numbers = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "std::set (sorted, unique): ";
    for (auto num : unique_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 7. String iteration
    std::cout << "\n7. String Iteration:" << std::endl;
    std::string message = "Hello";
    
    std::cout << "Characters in '" << message << "': ";
    for (auto ch : message) {
        std::cout << ch << " ";
    }
    std::cout << std::endl;
    
    // Modify string characters
    std::string mutable_str = "hello";
    for (auto& ch : mutable_str) {
        ch = std::toupper(ch);
    }
    std::cout << "Uppercase: " << mutable_str << std::endl;
    
    // 8. Nested containers
    std::cout << "\n8. Nested Containers:" << std::endl;
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    std::cout << "Matrix:" << std::endl;
    for (const auto& row : matrix) {
        std::cout << "  ";
        for (auto elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    
    // 9. Range-based for with initializer lists
    std::cout << "\n9. Initializer Lists:" << std::endl;
    std::cout << "Direct iteration: ";
    for (auto num : {1, 2, 3, 4, 5}) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 10. Performance comparison
    std::cout << "\n10. Performance Considerations:" << std::endl;
    
    // Large objects - use const reference to avoid copying
    std::vector<std::string> large_strings = {
        "This is a long string that we don't want to copy",
        "Another long string for demonstration",
        "Yet another string to show the concept"
    };
    
    std::cout << "Large strings (const ref - efficient):" << std::endl;
    for (const auto& str : large_strings) {  // No copying!
        std::cout << "  Length: " << str.length() << " - " << str.substr(0, 20) << "..." << std::endl;
    }
    
    // 11. When NOT to use range-based for
    std::cout << "\n11. When Traditional Loops are Better:" << std::endl;
    
    // When you need the index
    std::vector<int> indexed_data = {10, 20, 30, 40, 50};
    std::cout << "With indices (traditional for loop):" << std::endl;
    for (size_t i = 0; i < indexed_data.size(); ++i) {
        std::cout << "  Index " << i << ": " << indexed_data[i] << std::endl;
    }
    
    // When you need to skip elements
    std::cout << "Every second element:" << std::endl;
    for (size_t i = 0; i < indexed_data.size(); i += 2) {
        std::cout << "  " << indexed_data[i] << std::endl;
    }
    
    // When you need reverse iteration (use reverse iterators)
    std::cout << "Reverse iteration (traditional approach):" << std::endl;
    for (auto it = indexed_data.rbegin(); it != indexed_data.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\n=== RANGE-BASED FOR LOOP BENEFITS ===" << std::endl;
    std::cout << "✅ Cleaner, more readable code" << std::endl;
    std::cout << "✅ Less error-prone (no index management)" << std::endl;
    std::cout << "✅ Works with any container that has begin()/end()" << std::endl;
    std::cout << "✅ Perfect with auto keyword" << std::endl;
    std::cout << "✅ Efficient with const& for large objects" << std::endl;
    std::cout << "⚠️  Use traditional loops when you need indices" << std::endl;
    std::cout << "⚠️  Use const& for large objects to avoid copying" << std::endl;
    std::cout << "⚠️  Use & when you need to modify elements" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -o range_for_demo range_based_for_demo.cpp
./range_for_demo

Range-based For Loop Syntax:
- for (declaration : expression) statement
- declaration: auto, type, auto&, const auto&, etc.
- expression: any container with begin()/end() methods
- Works with: arrays, std::vector, std::array, std::map, std::set, std::string, etc.

Performance Tips:
- Use const auto& for read-only access to avoid copying
- Use auto& when you need to modify elements
- Use auto for simple types (int, char, etc.)
*/
