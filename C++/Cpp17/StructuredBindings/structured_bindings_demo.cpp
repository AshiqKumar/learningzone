// C++17 Structured Bindings - Multiple Variable Declaration
// Compile: g++ -std=c++17 -o structured_bindings_demo structured_bindings_demo.cpp
// Run: ./structured_bindings_demo

#include <iostream>
#include <tuple>
#include <map>
#include <unordered_map>
#include <vector>
#include <array>
#include <string>
#include <utility>
#include <set>

// Custom struct for demonstration
struct Person {
    std::string name;
    int age;
    double salary;
};

// Custom class with public members
class Point3D {
public:
    double x, y, z;
    
    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

// Function returning multiple values via tuple
std::tuple<std::string, int, bool> get_user_info() {
    return std::make_tuple("Alice Johnson", 28, true);
}

// Function returning pair
std::pair<int, std::string> get_error_info() {
    return {404, "Not Found"};
}

// Function returning array
std::array<int, 3> get_coordinates() {
    return {10, 20, 30};
}

int main() {
    std::cout << "=== C++17 STRUCTURED BINDINGS DEMO ===" << std::endl;
    
    // 1. Basic structured bindings with std::pair
    std::cout << "\n1. Basic Pair Decomposition:" << std::endl;
    
    std::pair<int, std::string> p1 = {42, "Answer"};
    
    // C++11/14 way
    int old_number = p1.first;
    std::string old_text = p1.second;
    std::cout << "C++14 way: " << old_number << ", " << old_text << std::endl;
    
    // C++17 structured bindings
    auto [number, text] = p1;
    std::cout << "C++17 way: " << number << ", " << text << std::endl;
    
    // With explicit type
    const auto [const_num, const_text] = p1;
    std::cout << "Const binding: " << const_num << ", " << const_text << std::endl;
    
    // 2. Tuple decomposition
    std::cout << "\n2. Tuple Decomposition:" << std::endl;
    
    std::tuple<std::string, int, double, bool> person_tuple = 
        std::make_tuple("John Doe", 35, 75000.50, false);
    
    // C++11/14 way
    std::string old_name = std::get<0>(person_tuple);
    int old_age = std::get<1>(person_tuple);
    std::cout << "C++14 tuple access: " << old_name << ", " << old_age << std::endl;
    
    // C++17 structured bindings
    auto [name, age, salary, is_manager] = person_tuple;
    std::cout << "C++17 tuple binding: " << name << ", " << age 
              << ", $" << salary << ", manager: " << std::boolalpha << is_manager << std::endl;
    
    // 3. Function return value decomposition
    std::cout << "\n3. Function Return Decomposition:" << std::endl;
    
    auto [user_name, user_age, is_active] = get_user_info();
    std::cout << "User info: " << user_name << ", age " << user_age 
              << ", active: " << is_active << std::endl;
    
    auto [error_code, error_message] = get_error_info();
    std::cout << "Error: " << error_code << " - " << error_message << std::endl;
    
    // 4. Array decomposition
    std::cout << "\n4. Array Decomposition:" << std::endl;
    
    // C-style array
    int coords[3] = {100, 200, 300};
    auto [x1, y1, z1] = coords;
    std::cout << "C-array coordinates: (" << x1 << ", " << y1 << ", " << z1 << ")" << std::endl;
    
    // std::array
    std::array<int, 3> std_coords = {400, 500, 600};
    auto [x2, y2, z2] = std_coords;
    std::cout << "std::array coordinates: (" << x2 << ", " << y2 << ", " << z2 << ")" << std::endl;
    
    // Function returning array
    auto [fx, fy, fz] = get_coordinates();
    std::cout << "Function array: (" << fx << ", " << fy << ", " << fz << ")" << std::endl;
    
    // 5. Struct/Class member decomposition
    std::cout << "\n5. Struct/Class Member Decomposition:" << std::endl;
    
    Person person{"Bob Smith", 42, 85000.0};
    auto [p_name, p_age, p_salary] = person;
    std::cout << "Person: " << p_name << ", " << p_age << " years old, $" << p_salary << std::endl;
    
    Point3D point(1.5, 2.5, 3.5);
    auto [px, py, pz] = point;
    std::cout << "Point3D: (" << px << ", " << py << ", " << pz << ")" << std::endl;
    
    // 6. Map iteration with structured bindings
    std::cout << "\n6. Map Iteration:" << std::endl;
    
    std::map<std::string, int> word_count = {
        {"hello", 5}, {"world", 3}, {"C++", 10}, {"structured", 2}, {"bindings", 1}
    };
    
    std::cout << "Word frequencies:" << std::endl;
    for (const auto& [word, count] : word_count) {
        std::cout << "  " << word << ": " << count << std::endl;
    }
    
    // Modifying map values
    std::cout << "\nUpdating map values:" << std::endl;
    for (auto& [word, count] : word_count) {
        if (word == "C++") {
            count += 5;  // Increase C++ count
        }
    }
    
    std::cout << "Updated C++ count: " << word_count["C++"] << std::endl;
    
    // 7. Unordered map with structured bindings
    std::cout << "\n7. Unordered Map Operations:" << std::endl;
    
    std::unordered_map<int, std::string> id_to_name = {
        {1001, "Alice"}, {1002, "Bob"}, {1003, "Charlie"}, {1004, "Diana"}
    };
    
    std::cout << "Employee directory:" << std::endl;
    for (const auto& [id, name] : id_to_name) {
        std::cout << "  ID " << id << ": " << name << std::endl;
    }
    
    // Insert operation with structured binding result
    auto [iterator, success] = id_to_name.insert({1005, "Eve"});
    std::cout << "Insert result: " << (success ? "Success" : "Failed") << std::endl;
    if (success) {
        const auto& [new_id, new_name] = *iterator;
        std::cout << "Inserted: ID " << new_id << " -> " << new_name << std::endl;
    }
    
    // 8. Multiple assignment pattern
    std::cout << "\n8. Multiple Assignment Patterns:" << std::endl;
    
    // Swap using structured bindings
    int a = 10, b = 20;
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    
    std::tie(a, b) = std::make_pair(b, a);  // Traditional way
    std::cout << "After tie swap: a = " << a << ", b = " << b << std::endl;
    
    // Using structured bindings for assignment
    auto [new_a, new_b] = std::make_pair(100, 200);
    std::cout << "New values: a = " << new_a << ", b = " << new_b << std::endl;
    
    // 9. Nested structured bindings
    std::cout << "\n9. Nested Structures:" << std::endl;
    
    std::pair<std::pair<int, int>, std::string> nested_pair = {{5, 10}, "coordinates"};
    
    // Decompose outer pair
    auto [inner_pair, description] = nested_pair;
    std::cout << "Description: " << description << std::endl;
    
    // Decompose inner pair
    auto [inner_x, inner_y] = inner_pair;
    std::cout << "Inner coordinates: (" << inner_x << ", " << inner_y << ")" << std::endl;
    
    // Can't do nested decomposition in one step (C++17 limitation)
    // This would be invalid: auto [[inner_x2, inner_y2], desc2] = nested_pair;
    
    // 10. Reference bindings
    std::cout << "\n10. Reference Bindings:" << std::endl;
    
    std::pair<int, std::string> mutable_pair = {123, "mutable"};
    
    // Bind by reference to modify original
    auto& [ref_num, ref_str] = mutable_pair;
    ref_num = 456;
    ref_str = "modified";
    
    std::cout << "Original pair after modification: " << mutable_pair.first 
              << ", " << mutable_pair.second << std::endl;
    
    // Const reference binding
    const auto& [const_ref_num, const_ref_str] = mutable_pair;
    std::cout << "Const reference: " << const_ref_num << ", " << const_ref_str << std::endl;
    
    // 11. Structured bindings with algorithms
    std::cout << "\n11. Structured Bindings with Algorithms:" << std::endl;
    
    std::vector<std::pair<std::string, double>> products = {
        {"Laptop", 1299.99}, {"Phone", 899.99}, {"Tablet", 499.99}, {"Watch", 299.99}
    };
    
    // Find most expensive product
    auto max_product = *std::max_element(products.begin(), products.end(),
        [](const auto& a, const auto& b) {
            const auto& [name_a, price_a] = a;
            const auto& [name_b, price_b] = b;
            return price_a < price_b;
        });
    
    auto [max_name, max_price] = max_product;
    std::cout << "Most expensive: " << max_name << " at $" << max_price << std::endl;
    
    // Count products over $500
    int expensive_count = std::count_if(products.begin(), products.end(),
        [](const auto& product) {
            const auto& [name, price] = product;
            return price > 500.0;
        });
    
    std::cout << "Products over $500: " << expensive_count << std::endl;
    
    // 12. Multiple return values pattern
    std::cout << "\n12. Multiple Return Values Pattern:" << std::endl;
    
    auto divide_with_remainder = [](int dividend, int divisor) {
        return std::make_tuple(dividend / divisor, dividend % divisor);
    };
    
    auto [quotient, remainder] = divide_with_remainder(17, 5);
    std::cout << "17 ÷ 5 = " << quotient << " remainder " << remainder << std::endl;
    
    // Statistical calculations
    auto calculate_stats = [](const std::vector<double>& data) {
        double sum = 0;
        for (double val : data) sum += val;
        double mean = sum / data.size();
        
        double variance = 0;
        for (double val : data) {
            variance += (val - mean) * (val - mean);
        }
        variance /= data.size();
        
        return std::make_tuple(mean, variance, sum);
    };
    
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto [mean, variance, total] = calculate_stats(data);
    std::cout << "Statistics - Mean: " << mean << ", Variance: " << variance 
              << ", Sum: " << total << std::endl;
    
    // 13. Error handling pattern
    std::cout << "\n13. Error Handling Pattern:" << std::endl;
    
    auto safe_divide = [](double a, double b) -> std::pair<double, bool> {
        if (b == 0.0) {
            return {0.0, false};  // error case
        }
        return {a / b, true};     // success case
    };
    
    auto [result1, success1] = safe_divide(10.0, 2.0);
    if (success1) {
        std::cout << "10.0 / 2.0 = " << result1 << std::endl;
    } else {
        std::cout << "Division failed" << std::endl;
    }
    
    auto [result2, success2] = safe_divide(10.0, 0.0);
    if (success2) {
        std::cout << "10.0 / 0.0 = " << result2 << std::endl;
    } else {
        std::cout << "Division by zero detected!" << std::endl;
    }
    
    // 14. Complex data structure decomposition
    std::cout << "\n14. Complex Data Structures:" << std::endl;
    
    using StudentRecord = std::tuple<std::string, int, std::vector<double>, std::pair<std::string, std::string>>;
    
    StudentRecord student = std::make_tuple(
        "Jane Doe",
        20,
        std::vector<double>{85.5, 92.0, 78.5, 94.0},
        std::make_pair("Computer Science", "University of Tech")
    );
    
    auto [student_name, student_age, grades, school_info] = student;
    auto [major, university] = school_info;
    
    std::cout << "Student: " << student_name << ", Age: " << student_age << std::endl;
    std::cout << "Major: " << major << " at " << university << std::endl;
    std::cout << "Grades: ";
    for (double grade : grades) {
        std::cout << grade << " ";
    }
    std::cout << std::endl;
    
    // 15. Performance and best practices
    std::cout << "\n15. Performance Considerations:" << std::endl;
    
    // Structured bindings create copies by default
    std::pair<std::string, std::vector<int>> large_data = {
        "Large Dataset", std::vector<int>(1000, 42)
    };
    
    // This creates copies
    auto [name_copy, data_copy] = large_data;
    std::cout << "Copy binding - Data size: " << data_copy.size() << std::endl;
    
    // This uses references (more efficient)
    const auto& [name_ref, data_ref] = large_data;
    std::cout << "Reference binding - Data size: " << data_ref.size() << std::endl;
    
    // Move semantics with structured bindings
    auto create_large_pair = []() {
        return std::make_pair(std::string("Moved"), std::vector<int>(500, 1));
    };
    
    auto [moved_name, moved_data] = create_large_pair();  // Move occurs
    std::cout << "Moved data size: " << moved_data.size() << std::endl;
    
    std::cout << "\n=== STRUCTURED BINDINGS BENEFITS ===" << std::endl;
    std::cout << "✅ Cleaner, more readable code for multiple value handling" << std::endl;
    std::cout << "✅ Eliminates need for std::get<N> or .first/.second" << std::endl;
    std::cout << "✅ Self-documenting variable names instead of generic accessors" << std::endl;
    std::cout << "✅ Works with pairs, tuples, arrays, and custom types" << std::endl;
    std::cout << "✅ Perfect for range-based for loops with maps" << std::endl;
    std::cout << "✅ Enables elegant multiple return value patterns" << std::endl;
    std::cout << "✅ Supports reference bindings for efficiency" << std::endl;
    std::cout << "✅ Compile-time decomposition - no runtime overhead" << std::endl;
    std::cout << "⚠️  Creates copies by default - use references when needed" << std::endl;
    std::cout << "⚠️  Cannot nest decomposition in single statement" << std::endl;
    std::cout << "⚠️  Requires C++17 compiler support" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++17 -Wall -Wextra -o structured_bindings_demo structured_bindings_demo.cpp
./structured_bindings_demo

C++17 Structured Bindings Key Features:
1. Multiple variable declaration: auto [a, b, c] = tuple_or_array;
2. Works with pairs, tuples, arrays, and custom types
3. Reference bindings: auto& [a, b] = pair; or const auto& [a, b] = pair;
4. Perfect for map iteration and multiple return values

Supported Types:
- std::pair and std::tuple
- C-style arrays and std::array
- Custom structs/classes with public members
- Any type with get<N>() support

Common Patterns:
- Map iteration: for (const auto& [key, value] : map)
- Function multiple returns: auto [result, error] = function();
- Tuple decomposition: auto [a, b, c] = std::make_tuple(...);
- Error handling: auto [value, success] = safe_operation();

Benefits:
- More readable than std::get<N>() or .first/.second
- Self-documenting variable names
- Eliminates temporary variables
- Clean multiple return value handling
- Works seamlessly with algorithms and STL containers

Best Practices:
- Use const auto& for large objects to avoid copies
- Prefer structured bindings over manual decomposition
- Use meaningful variable names
- Consider move semantics for temporary objects
*/
