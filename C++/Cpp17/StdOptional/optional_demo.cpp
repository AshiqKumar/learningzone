// C++17 std::optional - Type-Safe Nullable Values
// Compile: g++ -std=c++17 -o optional_demo optional_demo.cpp
// Run: ./optional_demo

#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

// 1. Functions returning optional values
std::optional<int> safe_divide(int numerator, int denominator) {
    if (denominator == 0) {
        return std::nullopt;  // Return empty optional
    }
    return numerator / denominator;
}

std::optional<std::string> find_user_name(int user_id) {
    static std::map<int, std::string> users = {
        {1, "Alice"}, {2, "Bob"}, {3, "Charlie"}, {4, "Diana"}
    };
    
    auto it = users.find(user_id);
    if (it != users.end()) {
        return it->second;
    }
    return std::nullopt;
}

// 2. File operations with optional
std::optional<std::string> read_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return std::nullopt;
    }
    
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// 3. Parsing with optional
std::optional<int> parse_int(const std::string& str) {
    try {
        size_t pos;
        int result = std::stoi(str, &pos);
        // Check if entire string was consumed
        if (pos == str.length()) {
            return result;
        }
    } catch (const std::exception&) {
        // Parsing failed
    }
    return std::nullopt;
}

std::optional<double> parse_double(const std::string& str) {
    try {
        size_t pos;
        double result = std::stod(str, &pos);
        if (pos == str.length()) {
            return result;
        }
    } catch (const std::exception&) {
        // Parsing failed
    }
    return std::nullopt;
}

// 4. Search operations
template<typename Container, typename T>
std::optional<size_t> find_index(const Container& container, const T& value) {
    auto it = std::find(container.begin(), container.end(), value);
    if (it != container.end()) {
        return std::distance(container.begin(), it);
    }
    return std::nullopt;
}

// 5. Configuration with defaults
class Configuration {
private:
    std::map<std::string, std::string> settings;
    
public:
    void set(const std::string& key, const std::string& value) {
        settings[key] = value;
    }
    
    std::optional<std::string> get_string(const std::string& key) const {
        auto it = settings.find(key);
        if (it != settings.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    std::optional<int> get_int(const std::string& key) const {
        auto str_value = get_string(key);
        if (str_value) {
            return parse_int(*str_value);
        }
        return std::nullopt;
    }
    
    std::optional<bool> get_bool(const std::string& key) const {
        auto str_value = get_string(key);
        if (str_value) {
            if (*str_value == "true" || *str_value == "1") return true;
            if (*str_value == "false" || *str_value == "0") return false;
        }
        return std::nullopt;
    }
    
    // Get with default value
    template<typename T>
    T get_or_default(const std::string& key, const T& default_value) const {
        if constexpr (std::is_same_v<T, std::string>) {
            return get_string(key).value_or(default_value);
        } else if constexpr (std::is_same_v<T, int>) {
            return get_int(key).value_or(default_value);
        } else if constexpr (std::is_same_v<T, bool>) {
            return get_bool(key).value_or(default_value);
        }
    }
};

// 6. Chain of optional operations
std::optional<std::string> process_user_data(int user_id) {
    auto name = find_user_name(user_id);
    if (!name) {
        return std::nullopt;
    }
    
    // Process the name (convert to uppercase)
    std::string processed = *name;
    std::transform(processed.begin(), processed.end(), processed.begin(), ::toupper);
    
    return processed;
}

// 7. Optional with custom types
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

std::optional<Point> find_intersection(Point p1, Point p2, Point p3, Point p4) {
    // Simplified line intersection (assuming lines are not parallel)
    double denom = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
    
    if (std::abs(denom) < 1e-10) {  // Lines are parallel
        return std::nullopt;
    }
    
    double t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / denom;
    
    return Point{p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y)};
}

// 8. Comparison with traditional approaches
// Traditional approach using pointers
std::string* find_user_name_ptr(int user_id) {
    static std::map<int, std::string> users = {
        {1, "Alice"}, {2, "Bob"}, {3, "Charlie"}, {4, "Diana"}
    };
    
    auto it = users.find(user_id);
    if (it != users.end()) {
        return &(it->second);
    }
    return nullptr;
}

// Traditional approach using bool + reference
bool find_user_name_ref(int user_id, std::string& result) {
    static std::map<int, std::string> users = {
        {1, "Alice"}, {2, "Bob"}, {3, "Charlie"}, {4, "Diana"}
    };
    
    auto it = users.find(user_id);
    if (it != users.end()) {
        result = it->second;
        return true;
    }
    return false;
}

int main() {
    std::cout << "=== C++17 STD::OPTIONAL DEMO ===" << std::endl;
    
    // 1. Basic optional usage
    std::cout << "\n1. Basic Optional Usage:" << std::endl;
    
    // Creating optionals
    std::optional<int> opt1 = 42;
    std::optional<int> opt2;  // Empty optional
    std::optional<int> opt3 = std::nullopt;  // Explicitly empty
    
    std::cout << "opt1 has value: " << opt1.has_value() << ", value: " << opt1.value() << std::endl;
    std::cout << "opt2 has value: " << opt2.has_value() << std::endl;
    std::cout << "opt3 has value: " << opt3.has_value() << std::endl;
    
    // Safe access
    if (opt1) {
        std::cout << "opt1 value (operator bool): " << *opt1 << std::endl;
    }
    
    // value_or for default values
    std::cout << "opt2 value or default: " << opt2.value_or(-1) << std::endl;
    
    // 2. Safe division example
    std::cout << "\n2. Safe Division:" << std::endl;
    
    auto result1 = safe_divide(10, 2);
    auto result2 = safe_divide(10, 0);
    
    if (result1) {
        std::cout << "10 / 2 = " << *result1 << std::endl;
    }
    
    if (result2) {
        std::cout << "10 / 0 = " << *result2 << std::endl;
    } else {
        std::cout << "Division by zero detected!" << std::endl;
    }
    
    // Using value_or
    std::cout << "10 / 2 with default: " << result1.value_or(0) << std::endl;
    std::cout << "10 / 0 with default: " << result2.value_or(0) << std::endl;
    
    // 3. User lookup
    std::cout << "\n3. User Lookup:" << std::endl;
    
    for (int id = 1; id <= 5; ++id) {
        auto name = find_user_name(id);
        if (name) {
            std::cout << "User " << id << ": " << *name << std::endl;
        } else {
            std::cout << "User " << id << ": not found" << std::endl;
        }
    }
    
    // 4. String parsing
    std::cout << "\n4. String Parsing:" << std::endl;
    
    std::vector<std::string> test_strings = {"42", "3.14", "hello", "123abc", "", "999"};
    
    for (const auto& str : test_strings) {
        auto int_val = parse_int(str);
        auto double_val = parse_double(str);
        
        std::cout << "\"" << str << "\" -> ";
        std::cout << "int: " << (int_val ? std::to_string(*int_val) : "invalid") << ", ";
        std::cout << "double: " << (double_val ? std::to_string(*double_val) : "invalid") << std::endl;
    }
    
    // 5. Container search
    std::cout << "\n5. Container Search:" << std::endl;
    
    std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    auto index1 = find_index(words, std::string("cherry"));
    auto index2 = find_index(words, std::string("grape"));
    
    if (index1) {
        std::cout << "Found 'cherry' at index: " << *index1 << std::endl;
    }
    
    if (!index2) {
        std::cout << "'grape' not found in container" << std::endl;
    }
    
    // 6. Configuration system
    std::cout << "\n6. Configuration System:" << std::endl;
    
    Configuration config;
    config.set("debug", "true");
    config.set("port", "8080");
    config.set("name", "MyApp");
    config.set("timeout", "30");
    
    // Accessing configuration values
    auto debug = config.get_bool("debug");
    auto port = config.get_int("port");
    auto name = config.get_string("name");
    auto missing = config.get_string("missing_key");
    
    std::cout << "Debug mode: " << (debug ? (*debug ? "enabled" : "disabled") : "not set") << std::endl;
    std::cout << "Port: " << (port ? std::to_string(*port) : "not set") << std::endl;
    std::cout << "Name: " << (name ? *name : "not set") << std::endl;
    std::cout << "Missing key: " << (missing ? *missing : "not found") << std::endl;
    
    // Using defaults
    std::cout << "Default values:" << std::endl;
    std::cout << "Debug (default false): " << config.get_or_default("debug", false) << std::endl;
    std::cout << "Max connections (default 100): " << config.get_or_default("max_connections", 100) << std::endl;
    std::cout << "App name (default 'Unknown'): " << config.get_or_default("name", std::string("Unknown")) << std::endl;
    
    // 7. Chaining optional operations
    std::cout << "\n7. Chaining Operations:" << std::endl;
    
    for (int id = 1; id <= 5; ++id) {
        auto processed = process_user_data(id);
        if (processed) {
            std::cout << "Processed user " << id << ": " << *processed << std::endl;
        } else {
            std::cout << "Could not process user " << id << std::endl;
        }
    }
    
    // 8. Optional with custom types
    std::cout << "\n8. Optional with Custom Types:" << std::endl;
    
    // Line intersection example
    Point p1{0, 0}, p2{2, 2};  // Line 1: y = x
    Point p3{0, 2}, p4{2, 0};  // Line 2: y = -x + 2
    Point p5{1, 1}, p6{3, 3};  // Line 3: parallel to line 1
    
    auto intersection1 = find_intersection(p1, p2, p3, p4);
    auto intersection2 = find_intersection(p1, p2, p5, p6);  // Parallel lines
    
    if (intersection1) {
        std::cout << "Intersection found at: (" << intersection1->x << ", " << intersection1->y << ")" << std::endl;
    }
    
    if (!intersection2) {
        std::cout << "Lines are parallel - no intersection" << std::endl;
    }
    
    // 9. Optional assignment and modification
    std::cout << "\n9. Optional Assignment and Modification:" << std::endl;
    
    std::optional<std::string> opt_str;
    std::cout << "Initially empty: " << !opt_str.has_value() << std::endl;
    
    opt_str = "Hello";
    std::cout << "After assignment: " << *opt_str << std::endl;
    
    opt_str.emplace("World");  // Construct in place
    std::cout << "After emplace: " << *opt_str << std::endl;
    
    opt_str.reset();  // Clear the optional
    std::cout << "After reset: " << !opt_str.has_value() << std::endl;
    
    // 10. Performance comparison with traditional approaches
    std::cout << "\n10. Performance Comparison:" << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // std::optional approach
    for (int i = 0; i < 1000000; ++i) {
        auto result = find_user_name(1);
        if (result) {
            volatile auto len = result->length();
            (void)len;  // Suppress unused warning
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_optional = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Pointer approach
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 1000000; ++i) {
        auto* result = find_user_name_ptr(1);
        if (result) {
            volatile auto len = result->length();
            (void)len;
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto duration_pointer = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Bool + reference approach
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 1000000; ++i) {
        std::string result;
        if (find_user_name_ref(1, result)) {
            volatile auto len = result.length();
            (void)len;
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto duration_bool_ref = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Performance (1M lookups):" << std::endl;
    std::cout << "std::optional: " << duration_optional.count() << " microseconds" << std::endl;
    std::cout << "Pointer: " << duration_pointer.count() << " microseconds" << std::endl;
    std::cout << "Bool + ref: " << duration_bool_ref.count() << " microseconds" << std::endl;
    
    // 11. Exception safety
    std::cout << "\n11. Exception Safety:" << std::endl;
    
    std::optional<int> safe_opt = 42;
    std::optional<int> empty_opt;
    
    // Safe access - no exceptions
    std::cout << "Safe access with operator*: " << *safe_opt << std::endl;
    
    // Exception throwing access
    try {
        std::cout << "Trying to access empty optional with value()..." << std::endl;
        auto value = empty_opt.value();  // Throws std::bad_optional_access
        std::cout << "Value: " << value << std::endl;
    } catch (const std::bad_optional_access& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    // 12. Monadic operations (C++23 preview)
    std::cout << "\n12. Functional-Style Operations:" << std::endl;
    
    // Manual implementation of monadic-style operations
    auto transform_if_present = [](auto opt, auto func) {
        using ReturnType = std::optional<decltype(func(*opt))>;
        return opt ? ReturnType{func(*opt)} : std::nullopt;
    };
    
    auto and_then = [](auto opt, auto func) {
        return opt ? func(*opt) : decltype(func(*opt)){};
    };
    
    std::optional<int> num = 42;
    
    auto doubled = transform_if_present(num, [](int x) { return x * 2; });
    auto as_string = transform_if_present(doubled, [](int x) { return std::to_string(x); });
    
    if (as_string) {
        std::cout << "Transformed value: " << *as_string << std::endl;
    }
    
    // Chain with and_then
    auto chained = and_then(num, [](int x) {
        return x > 0 ? std::optional<int>{x * 2} : std::nullopt;
    });
    
    if (chained) {
        std::cout << "Chained result: " << *chained << std::endl;
    }
    
    std::cout << "\n=== STD::OPTIONAL BENEFITS ===" << std::endl;
    std::cout << "✅ Type-safe nullable values - no null pointer dereference" << std::endl;
    std::cout << "✅ Self-documenting code - function signature shows optional return" << std::endl;
    std::cout << "✅ Exception safety - choose between throwing and non-throwing access" << std::endl;
    std::cout << "✅ Composable - works well with algorithms and functional programming" << std::endl;
    std::cout << "✅ Memory efficient - no heap allocation for value types" << std::endl;
    std::cout << "✅ Explicit null handling - compiler enforces checking" << std::endl;
    std::cout << "✅ Better than magic values (-1, empty string, etc.)" << std::endl;
    std::cout << "⚠️  Small overhead compared to raw values (bool flag storage)" << std::endl;
    std::cout << "⚠️  Not suitable for very performance-critical inner loops" << std::endl;
    std::cout << "⚠️  Can be overused - not every function needs optional return" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++17 -Wall -Wextra -o optional_demo optional_demo.cpp
./optional_demo

C++17 std::optional Key Features:
1. Type-safe nullable values without pointers
2. Explicit handling of "no value" scenarios  
3. Composable and functional programming friendly
4. Exception-safe access methods

Basic Usage:
std::optional<int> opt = 42;          // Has value
std::optional<int> empty;             // No value
std::optional<int> null = std::nullopt; // Explicitly no value

Access Methods:
- opt.has_value() / bool(opt)  - Check if has value
- *opt / opt.value()           - Access value (value() throws if empty)
- opt.value_or(default)        - Get value or default
- opt.emplace(args...)         - Construct value in-place
- opt.reset()                  - Clear the optional

Common Patterns:
- Function return types for operations that may fail
- Configuration systems with optional settings
- Search operations that may not find results
- Parsing operations that may fail
- File I/O that may fail

Benefits over Traditional Approaches:
- Safer than raw pointers (no null dereference)
- Cleaner than bool + reference parameters
- Self-documenting (signature shows optional nature)
- Exception safe (choose throwing vs non-throwing)
- Composable with algorithms and functional style

Performance:
- Small overhead (typically 1 byte for flag + value)
- No heap allocation
- Comparable to pointer-based approaches
- Compiler optimizations often eliminate overhead

Best Practices:
- Use for operations that may legitimately fail
- Prefer value_or() for simple defaults
- Check has_value() or use operator bool before dereferencing
- Consider exception handling needs (value() vs operator*)
- Don't overuse - not every function needs optional
*/
