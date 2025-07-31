// C++23 std::print and std::println - Modern Text Formatting
// Compile: g++ -std=c++23 -o print_demo print_demo.cpp
// Run: ./print_demo

#include <iostream>
#include <print>
#include <format>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <complex>
#include <fstream>
#include <ranges>
#include <algorithm>

// 1. Basic std::print and std::println usage
void demonstrate_basic_usage() {
    std::println("1. Basic std::print and std::println Usage:");
    
    // Simple text output
    std::print("Hello, World!\n");
    std::println("Hello, World with newline!");
    
    // Basic formatting
    std::print("Number: {}\n", 42);
    std::println("Number: {}", 42);
    
    // Multiple arguments
    std::print("Name: {}, Age: {}, Height: {:.1f}m\n", "Alice", 30, 1.75);
    std::println("Name: {}, Age: {}, Height: {:.1f}m", "Alice", 30, 1.75);
    
    // Positional arguments
    std::print("Today is {1}/{0}/{2}\n", 15, 12, 2023);
    std::println("Today is {1}/{0}/{2}", 15, 12, 2023);
}

// 2. Advanced formatting with std::print
void demonstrate_advanced_formatting() {
    std::println("\n2. Advanced Formatting:");
    
    // Width and alignment
    std::println("Left aligned:    '{:<10}'", "text");
    std::println("Right aligned:   '{:>10}'", "text");
    std::println("Center aligned:  '{:^10}'", "text");
    std::println("Fill character:  '{:*^10}'", "text");
    
    // Number formatting
    int value = 42;
    std::println("Decimal:         {:d}", value);
    std::println("Binary:          {:b}", value);
    std::println("Octal:           {:o}", value);
    std::println("Hexadecimal:     {:x}", value);
    std::println("HEX (uppercase): {:X}", value);
    
    // Float formatting
    double pi = 3.14159265359;
    std::println("Fixed:           {:.3f}", pi);
    std::println("Scientific:      {:.3e}", pi);
    std::println("General:         {:.3g}", pi);
    std::println("Auto:            {:.3}", pi);
    std::println("Percentage:      {:.2%}", 0.85);
    
    // Width with numbers
    std::println("Padded:          '{:08d}'", 42);
    std::println("Signed:          '{:+d}'", 42);
    std::println("Space for +ve:   '{: d}'", 42);
    std::println("Space for +ve:   '{: d}'", -42);
}

// 3. String and character formatting
void demonstrate_string_formatting() {
    std::println("\n3. String and Character Formatting:");
    
    std::string text = "Hello, World!";
    
    // Basic string formatting
    std::println("String:          '{}'", text);
    std::println("Width (left):    '{:<20}'", text);
    std::println("Width (right):   '{:>20}'", text);
    std::println("Width (center):  '{:^20}'", text);
    std::println("With fill:       '{:=^20}'", text);
    
    // Substring
    std::println("First 5 chars:   '{:.5}'", text);
    
    // Character formatting
    char ch = 'A';
    std::println("Character:       '{}'", ch);
    std::println("As integer:      '{:d}'", ch);
    std::println("As hex:          '{:x}'", ch);
    
    // String literals and wide strings
    std::println("String literal:  '{}'", "C++ is awesome!");
    
    // Unicode support
    std::println("Unicode:         '{}'", "🚀 C++23 🎉");
    std::println("Greek:           '{}'", "αβγδε");
    std::println("Japanese:        '{}'", "こんにちは");
}

// 4. Container formatting
void demonstrate_container_formatting() {
    std::println("\n4. Container Formatting:");
    
    // Vector
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::println("Vector:          {}", numbers);
    
    // Array
    std::array<double, 4> values = {1.1, 2.2, 3.3, 4.4};
    std::println("Array:           {:.1f}", values);
    
    // Map
    std::map<std::string, int> scores = {
        {"Alice", 95}, {"Bob", 87}, {"Charlie", 92}
    };
    std::println("Map:             {}", scores);
    
    // Ranges (C++23 feature integration)
    auto even_numbers = numbers | std::views::filter([](int n) { return n % 2 == 0; });
    std::println("Even numbers:    {}", even_numbers);
    
    // Custom container formatting
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::println("2D Vector:       {}", matrix);
}

// 5. Date and time formatting
void demonstrate_datetime_formatting() {
    std::println("\n5. Date and Time Formatting:");
    
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    // Basic time formatting
    std::println("Current time:    {}", now);
    
    // Duration formatting
    auto duration = std::chrono::milliseconds(1500);
    std::println("Duration:        {}", duration);
    
    auto hours = std::chrono::hours(2);
    auto minutes = std::chrono::minutes(30);
    std::println("Time span:       {} and {}", hours, minutes);
    
    // High resolution timing
    auto start = std::chrono::high_resolution_clock::now();
    // Simulate some work
    volatile int sum = 0;
    for (int i = 0; i < 1000; ++i) {
        sum += i;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    
    std::println("Elapsed time:    {}", elapsed);
    std::println("In microseconds: {}", 
                std::chrono::duration_cast<std::chrono::microseconds>(elapsed));
}

// 6. Complex types and custom formatting
struct Point {
    double x, y;
    
    Point(double x_val, double y_val) : x(x_val), y(y_val) {}
};

// Custom formatter for Point
template <>
struct std::formatter<Point> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }
    
    auto format(const Point& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "Point({:.2f}, {:.2f})", p.x, p.y);
    }
};

struct Color {
    uint8_t r, g, b, a;
    
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}
};

// Custom formatter with format specification
template <>
struct std::formatter<Color> {
    char presentation = 'n';  // 'n' for name, 'h' for hex, 'r' for rgb
    
    constexpr auto parse(std::format_parse_context& ctx) {
        auto it = ctx.begin();
        auto end = ctx.end();
        
        if (it != end && (*it == 'n' || *it == 'h' || *it == 'r')) {
            presentation = *it++;
        }
        
        if (it != end && *it != '}') {
            throw std::format_error("Invalid format specification for Color");
        }
        
        return it;
    }
    
    auto format(const Color& c, std::format_context& ctx) const {
        switch (presentation) {
            case 'h':
                return std::format_to(ctx.out(), "#{:02X}{:02X}{:02X}{:02X}", 
                                    c.r, c.g, c.b, c.a);
            case 'r':
                return std::format_to(ctx.out(), "rgba({}, {}, {}, {})", 
                                    c.r, c.g, c.b, c.a);
            default:
                return std::format_to(ctx.out(), "Color(r={}, g={}, b={}, a={})", 
                                    c.r, c.g, c.b, c.a);
        }
    }
};

void demonstrate_custom_formatting() {
    std::println("\n6. Custom Type Formatting:");
    
    // Custom Point formatting
    Point p1(3.14159, 2.71828);
    std::println("Point:           {}", p1);
    
    std::vector<Point> points = {{0.0, 0.0}, {1.0, 1.0}, {2.5, 3.7}};
    std::println("Points:          {}", points);
    
    // Custom Color formatting with different presentations
    Color red(255, 0, 0);
    Color green(0, 255, 0, 128);  // Semi-transparent green
    
    std::println("Color (default): {}", red);
    std::println("Color (hex):     {:h}", red);
    std::println("Color (rgba):    {:r}", red);
    
    std::println("Green (default): {}", green);
    std::println("Green (hex):     {:h}", green);
    std::println("Green (rgba):    {:r}", green);
    
    // Complex numbers
    std::complex<double> c1(3.0, 4.0);
    std::complex<double> c2(-1.5, 2.8);
    std::println("Complex:         {}", c1);
    std::println("Complex:         {}", c2);
    
    // Pair and tuple
    std::pair<std::string, int> pair_val{"Score", 95};
    std::println("Pair:            {}", pair_val);
    
    std::tuple<std::string, int, double> tuple_val{"John", 25, 75.5};
    std::println("Tuple:           {}", tuple_val);
}

// 7. Error handling and edge cases
void demonstrate_error_handling() {
    std::println("\n7. Error Handling and Edge Cases:");
    
    // Null pointer handling
    const char* null_ptr = nullptr;
    std::println("Null pointer:    '{}'", static_cast<void*>(null_ptr));
    
    // Empty containers
    std::vector<int> empty_vec;
    std::println("Empty vector:    {}", empty_vec);
    
    // Special float values
    double infinity = std::numeric_limits<double>::infinity();
    double neg_infinity = -std::numeric_limits<double>::infinity();
    double nan_value = std::numeric_limits<double>::quiet_NaN();
    
    std::println("Infinity:        {}", infinity);
    std::println("Negative inf:    {}", neg_infinity);
    std::println("NaN:             {}", nan_value);
    
    // Large numbers
    long long big_number = 1234567890123456789LL;
    std::println("Big number:      {}", big_number);
    std::println("Formatted:       {:,}", big_number);  // With thousand separators
    
    // Boolean values
    bool true_val = true;
    bool false_val = false;
    std::println("Boolean true:    {}", true_val);
    std::println("Boolean false:   {}", false_val);
    std::println("As text:         {:s}", true_val);
    std::println("As text:         {:s}", false_val);
}

// 8. Performance comparison with traditional methods
void performance_comparison() {
    std::println("\n8. Performance Comparison:");
    
    constexpr int iterations = 100000;
    
    // Prepare data
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "Diana", "Eve"};
    std::vector<int> ages = {25, 30, 35, 28, 32};
    std::vector<double> scores = {95.5, 87.3, 92.1, 89.7, 94.2};
    
    // Traditional iostream approach
    auto start = std::chrono::high_resolution_clock::now();
    
    std::ostringstream oss1;
    for (int i = 0; i < iterations; ++i) {
        for (size_t j = 0; j < names.size(); ++j) {
            oss1 << "Name: " << names[j] << ", Age: " << ages[j] 
                 << ", Score: " << std::fixed << std::setprecision(1) << scores[j] << "\n";
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto iostream_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // std::format approach
    start = std::chrono::high_resolution_clock::now();
    
    std::string result_format;
    for (int i = 0; i < iterations; ++i) {
        for (size_t j = 0; j < names.size(); ++j) {
            result_format += std::format("Name: {}, Age: {}, Score: {:.1f}\n", 
                                       names[j], ages[j], scores[j]);
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto format_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // std::print to string (simulated)
    start = std::chrono::high_resolution_clock::now();
    
    std::ostringstream oss2;
    auto old_buf = std::cout.rdbuf(oss2.rdbuf());  // Redirect stdout
    
    for (int i = 0; i < iterations; ++i) {
        for (size_t j = 0; j < names.size(); ++j) {
            // Note: std::print typically goes to stdout, this is for demonstration
            std::print("Name: {}, Age: {}, Score: {:.1f}\n", names[j], ages[j], scores[j]);
        }
    }
    
    std::cout.rdbuf(old_buf);  // Restore stdout
    end = std::chrono::high_resolution_clock::now();
    auto print_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::println("Performance ({} iterations, {} items each):", iterations, names.size());
    std::println("iostream:        {} microseconds", iostream_time.count());
    std::println("std::format:     {} microseconds", format_time.count());
    std::println("std::print:      {} microseconds", print_time.count());
    
    std::println("std::format vs iostream: {:.2f}x", 
                static_cast<double>(format_time.count()) / iostream_time.count());
    std::println("std::print vs iostream:  {:.2f}x", 
                static_cast<double>(print_time.count()) / iostream_time.count());
}

// 9. File output with std::print
void demonstrate_file_output() {
    std::println("\n9. File Output:");
    
    // Write to file using std::print
    std::ofstream file("print_output.txt");
    
    if (file.is_open()) {
        // Note: std::print to file requires special handling in some implementations
        std::print(file, "Writing to file with std::print\n");
        std::print(file, "Number: {}, String: {}\n", 42, "Hello File");
        std::print(file, "Formatted float: {:.3f}\n", 3.14159);
        
        // Using std::println (automatic newline)
        std::println(file, "Line with automatic newline");
        std::println(file, "Another line: {}", "with formatting");
        
        file.close();
        std::println("Output written to 'print_output.txt'");
    } else {
        std::println("Failed to open file for writing");
    }
    
    // Read back and display
    std::ifstream read_file("print_output.txt");
    if (read_file.is_open()) {
        std::println("File contents:");
        std::string line;
        while (std::getline(read_file, line)) {
            std::println("  {}", line);
        }
        read_file.close();
    }
}

// 10. Locale and internationalization
void demonstrate_locale_support() {
    std::println("\n10. Locale and Internationalization:");
    
    // Number formatting with locale
    double large_number = 1234567.89;
    std::println("Large number:    {}", large_number);
    std::println("With separators: {:L}", large_number);  // Locale-specific formatting
    
    // Different representations
    std::println("Scientific:      {:e}", large_number);
    std::println("Fixed:           {:f}", large_number);
    std::println("General:         {:g}", large_number);
    
    // Currency-like formatting (conceptual)
    std::println("As currency:     ${:.2f}", large_number);
    
    // Date formatting considerations
    auto now = std::chrono::system_clock::now();
    std::println("Timestamp:       {}", now);
    
    // Unicode and special characters
    std::println("Symbols:         {} {} {} {}", "€", "£", "¥", "₹");
    std::println("Math symbols:    {} {} {} {}", "∑", "∏", "∞", "√");
    std::println("Arrows:          {} {} {} {}", "→", "←", "↑", "↓");
}

// 11. Best practices and patterns
void demonstrate_best_practices() {
    std::println("\n11. Best Practices:");
    
    // 1. Prefer std::println over std::print when you want a newline
    std::println("Use std::println for lines ending with newline");
    
    // 2. Use meaningful format specifiers
    double value = 3.14159;
    std::println("Good: {:.2f} (clear precision)", value);
    
    // 3. Consider locale for user-facing output
    int count = 1000000;
    std::println("User-facing: {:L} items", count);
    std::println("Internal:    {} items", count);
    
    // 4. Use named arguments for clarity (conceptual)
    std::string name = "Alice";
    int age = 30;
    double salary = 75000.0;
    
    std::println("Employee: {} is {} years old with salary ${:.2f}", name, age, salary);
    
    // 5. Handle special cases gracefully
    std::vector<int> data;
    if (data.empty()) {
        std::println("No data available");
    } else {
        std::println("Data: {}", data);
    }
    
    // 6. Use appropriate format specifiers for security
    std::string user_input = "potentially unsafe input";
    std::println("Safe: '{}'", user_input);  // Won't interpret format specifiers in input
    
    // 7. Consider performance for high-frequency logging
    std::println("Performance tip: pre-format strings when possible");
    
    // 8. Error message formatting
    int error_code = 404;
    std::string error_msg = "File not found";
    std::println("ERROR {}: {}", error_code, error_msg);
}

int main() {
    std::println("=== C++23 STD::PRINT DEMO ===");
    
    demonstrate_basic_usage();
    demonstrate_advanced_formatting();
    demonstrate_string_formatting();
    demonstrate_container_formatting();
    demonstrate_datetime_formatting();
    demonstrate_custom_formatting();
    demonstrate_error_handling();
    performance_comparison();
    demonstrate_file_output();
    demonstrate_locale_support();
    demonstrate_best_practices();
    
    std::println("\n=== STD::PRINT BENEFITS ===");
    std::println("✅ Type-safe formatting (no printf vulnerabilities)");
    std::println("✅ Better performance than iostream in many cases");
    std::println("✅ Consistent with std::format syntax");
    std::println("✅ Unicode support out of the box");
    std::println("✅ Extensible with custom formatters");
    std::println("✅ Automatic newline handling with std::println");
    std::println("✅ Integration with C++20 ranges and containers");
    std::println("✅ Locale-aware formatting");
    std::println("⚠️  Requires C++23 support");
    std::println("⚠️  May have different performance characteristics than printf");
    std::println("⚠️  Learning curve for advanced formatting");
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++23 -Wall -Wextra -o print_demo print_demo.cpp
./print_demo

C++23 std::print and std::println Key Features:
1. Type-safe formatted output without format string vulnerabilities
2. Better performance than traditional iostream approach
3. Consistent syntax with std::format
4. Built-in Unicode support
5. Extensible with custom formatters

Basic Usage:
std::print("Hello, {}!\n", name);        // Requires explicit newline
std::println("Hello, {}!", name);        // Automatic newline

Advanced Features:
- Width and alignment: {:^10} (center, width 10)
- Number bases: {:b} (binary), {:x} (hex), {:o} (octal)
- Precision: {:.2f} (2 decimal places)
- Sign control: {:+} (always show sign)
- Fill characters: {:*^10} (center with * padding)
- Locale support: {:L} (locale-specific formatting)

Container Formatting:
std::vector<int> v = {1, 2, 3};
std::println("Vector: {}", v);  // Automatic container formatting

Custom Formatters:
- Implement std::formatter<YourType>
- Support format specification parsing
- Integrate seamlessly with std::print

Benefits over printf:
- Type safety (no format string mismatches)
- No buffer overflow vulnerabilities
- Better C++ integration
- Unicode support
- Extensible formatting

Benefits over iostream:
- Often better performance
- More concise syntax
- Better formatting control
- Consistent behavior across platforms
- Less template instantiation overhead

Use Cases:
- Logging and debugging output
- User interface text formatting
- File output with consistent formatting
- Internationalized applications
- Performance-critical formatted output

Best Practices:
- Use std::println for lines ending with newline
- Use meaningful format specifiers
- Consider locale for user-facing output
- Handle empty containers gracefully
- Use custom formatters for complex types
- Prefer over printf for security
- Pre-format strings for high-frequency output
*/
