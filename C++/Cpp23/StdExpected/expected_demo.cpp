// C++23 std::expected - Error Handling Without Exceptions
// Compile: g++ -std=c++23 -o expected_demo expected_demo.cpp
// Run: ./expected_demo

#include <iostream>
#include <expected>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <system_error>

// 1. Basic error types
enum class MathError {
    DIVISION_BY_ZERO,
    NEGATIVE_SQRT,
    INVALID_INPUT,
    OVERFLOW
};

enum class FileError {
    NOT_FOUND,
    PERMISSION_DENIED,
    INVALID_FORMAT,
    IO_ERROR
};

enum class ParseError {
    EMPTY_STRING,
    INVALID_CHARACTER,
    OUT_OF_RANGE,
    MALFORMED_DATA
};

// Error message helpers
std::string to_string(MathError error) {
    switch (error) {
        case MathError::DIVISION_BY_ZERO: return "Division by zero";
        case MathError::NEGATIVE_SQRT: return "Square root of negative number";
        case MathError::INVALID_INPUT: return "Invalid mathematical input";
        case MathError::OVERFLOW: return "Mathematical overflow";
        default: return "Unknown math error";
    }
}

std::string to_string(FileError error) {
    switch (error) {
        case FileError::NOT_FOUND: return "File not found";
        case FileError::PERMISSION_DENIED: return "Permission denied";
        case FileError::INVALID_FORMAT: return "Invalid file format";
        case FileError::IO_ERROR: return "I/O error";
        default: return "Unknown file error";
    }
}

std::string to_string(ParseError error) {
    switch (error) {
        case ParseError::EMPTY_STRING: return "Empty string";
        case ParseError::INVALID_CHARACTER: return "Invalid character";
        case ParseError::OUT_OF_RANGE: return "Value out of range";
        case ParseError::MALFORMED_DATA: return "Malformed data";
        default: return "Unknown parse error";
    }
}

// 2. Basic mathematical operations with expected
std::expected<double, MathError> safe_divide(double a, double b) {
    if (b == 0.0) {
        return std::unexpected(MathError::DIVISION_BY_ZERO);
    }
    return a / b;
}

std::expected<double, MathError> safe_sqrt(double x) {
    if (x < 0.0) {
        return std::unexpected(MathError::NEGATIVE_SQRT);
    }
    return std::sqrt(x);
}

std::expected<double, MathError> quadratic_formula(double a, double b, double c) {
    if (a == 0.0) {
        return std::unexpected(MathError::INVALID_INPUT);
    }
    
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return std::unexpected(MathError::NEGATIVE_SQRT);
    }
    
    // Return the positive root
    return (-b + std::sqrt(discriminant)) / (2 * a);
}

// 3. String parsing functions
std::expected<int, ParseError> parse_int(const std::string& str) {
    if (str.empty()) {
        return std::unexpected(ParseError::EMPTY_STRING);
    }
    
    try {
        size_t pos;
        int result = std::stoi(str, &pos);
        
        if (pos != str.length()) {
            return std::unexpected(ParseError::INVALID_CHARACTER);
        }
        
        return result;
    } catch (const std::invalid_argument&) {
        return std::unexpected(ParseError::INVALID_CHARACTER);
    } catch (const std::out_of_range&) {
        return std::unexpected(ParseError::OUT_OF_RANGE);
    }
}

std::expected<double, ParseError> parse_double(const std::string& str) {
    if (str.empty()) {
        return std::unexpected(ParseError::EMPTY_STRING);
    }
    
    try {
        size_t pos;
        double result = std::stod(str, &pos);
        
        if (pos != str.length()) {
            return std::unexpected(ParseError::INVALID_CHARACTER);
        }
        
        return result;
    } catch (const std::invalid_argument&) {
        return std::unexpected(ParseError::INVALID_CHARACTER);
    } catch (const std::out_of_range&) {
        return std::unexpected(ParseError::OUT_OF_RANGE);
    }
}

std::expected<std::vector<int>, ParseError> parse_csv_integers(const std::string& csv) {
    if (csv.empty()) {
        return std::unexpected(ParseError::EMPTY_STRING);
    }
    
    std::vector<int> result;
    std::stringstream ss(csv);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        // Trim whitespace
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        
        auto parsed = parse_int(token);
        if (!parsed) {
            return std::unexpected(parsed.error());
        }
        result.push_back(*parsed);
    }
    
    return result;
}

// 4. File operations with expected
std::expected<std::string, FileError> read_file(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        return std::unexpected(FileError::NOT_FOUND);
    }
    
    std::ostringstream buffer;
    buffer << file.rdbuf();
    
    if (file.bad()) {
        return std::unexpected(FileError::IO_ERROR);
    }
    
    return buffer.str();
}

std::expected<void, FileError> write_file(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        return std::unexpected(FileError::PERMISSION_DENIED);
    }
    
    file << content;
    
    if (file.bad()) {
        return std::unexpected(FileError::IO_ERROR);
    }
    
    return {};  // Success - void expected
}

// 5. Configuration parser using expected
class ConfigParser {
public:
    std::expected<std::map<std::string, std::string>, ParseError> 
    parse_config(const std::string& content) {
        std::map<std::string, std::string> config;
        std::stringstream ss(content);
        std::string line;
        
        while (std::getline(ss, line)) {
            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') {
                continue;
            }
            
            auto eq_pos = line.find('=');
            if (eq_pos == std::string::npos) {
                return std::unexpected(ParseError::MALFORMED_DATA);
            }
            
            std::string key = line.substr(0, eq_pos);
            std::string value = line.substr(eq_pos + 1);
            
            // Trim whitespace
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            
            if (key.empty()) {
                return std::unexpected(ParseError::MALFORMED_DATA);
            }
            
            config[key] = value;
        }
        
        return config;
    }
};

// 6. Chain of operations with expected
std::expected<double, std::string> process_mathematical_string(const std::string& input) {
    // Parse the string as a double
    auto parsed = parse_double(input);
    if (!parsed) {
        return std::unexpected("Parse error: " + to_string(parsed.error()));
    }
    
    // Take square root
    auto sqrt_result = safe_sqrt(*parsed);
    if (!sqrt_result) {
        return std::unexpected("Math error: " + to_string(sqrt_result.error()));
    }
    
    // Multiply by 2
    return *sqrt_result * 2.0;
}

// 7. Monadic operations (C++23 feature)
void demonstrate_monadic_operations() {
    std::cout << "\n7. Monadic Operations:" << std::endl;
    
    auto pipeline = [](const std::string& input) {
        return parse_double(input)
            .and_then([](double d) -> std::expected<double, ParseError> {
                if (d < 0) return std::unexpected(ParseError::OUT_OF_RANGE);
                return d * 2.0;
            })
            .and_then([](double d) -> std::expected<double, ParseError> {
                if (d > 1000) return std::unexpected(ParseError::OUT_OF_RANGE);
                return std::sqrt(d);
            })
            .transform([](double d) { return d + 1.0; })
            .or_else([](ParseError error) -> std::expected<double, ParseError> {
                std::cout << "Error in pipeline: " << to_string(error) << std::endl;
                return 0.0;  // Default value
            });
    };
    
    std::vector<std::string> test_inputs = {"100", "-5", "2000", "abc", "25"};
    
    for (const auto& input : test_inputs) {
        auto result = pipeline(input);
        if (result) {
            std::cout << "Input '" << input << "' -> Result: " << *result << std::endl;
        } else {
            std::cout << "Input '" << input << "' -> Error: " << to_string(result.error()) << std::endl;
        }
    }
}

// 8. Generic error handling with expected
template<typename T, typename E>
void print_expected(const std::expected<T, E>& exp, const std::string& name) {
    if (exp) {
        if constexpr (std::is_void_v<T>) {
            std::cout << name << ": Success" << std::endl;
        } else {
            std::cout << name << ": Success - " << *exp << std::endl;
        }
    } else {
        std::cout << name << ": Error - ";
        if constexpr (requires { to_string(exp.error()); }) {
            std::cout << to_string(exp.error()) << std::endl;
        } else {
            std::cout << "Error occurred" << std::endl;
        }
    }
}

// 9. Comparison with optional and exception handling
class TraditionalCalculator {
public:
    static std::optional<double> divide_optional(double a, double b) {
        if (b == 0.0) return std::nullopt;
        return a / b;
    }
    
    static double divide_exception(double a, double b) {
        if (b == 0.0) {
            throw std::runtime_error("Division by zero");
        }
        return a / b;
    }
    
    static std::expected<double, MathError> divide_expected(double a, double b) {
        if (b == 0.0) {
            return std::unexpected(MathError::DIVISION_BY_ZERO);
        }
        return a / b;
    }
};

// 10. Performance comparison
void performance_comparison() {
    std::cout << "\n10. Performance Comparison:" << std::endl;
    
    const int iterations = 1000000;
    std::vector<std::pair<double, double>> test_data;
    
    // Prepare test data (mix of valid and invalid operations)
    for (int i = 0; i < iterations; ++i) {
        double a = static_cast<double>(i);
        double b = (i % 7 == 0) ? 0.0 : static_cast<double>(i % 100 + 1);
        test_data.emplace_back(a, b);
    }
    
    // Test with expected
    auto start = std::chrono::high_resolution_clock::now();
    volatile double sum_expected = 0.0;
    
    for (const auto& [a, b] : test_data) {
        auto result = TraditionalCalculator::divide_expected(a, b);
        if (result) {
            sum_expected += *result;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto expected_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test with optional
    start = std::chrono::high_resolution_clock::now();
    volatile double sum_optional = 0.0;
    
    for (const auto& [a, b] : test_data) {
        auto result = TraditionalCalculator::divide_optional(a, b);
        if (result) {
            sum_optional += *result;
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto optional_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Test with exceptions (separate to avoid affecting other tests)
    start = std::chrono::high_resolution_clock::now();
    volatile double sum_exception = 0.0;
    
    for (const auto& [a, b] : test_data) {
        try {
            double result = TraditionalCalculator::divide_exception(a, b);
            sum_exception += result;
        } catch (const std::runtime_error&) {
            // Handle error
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto exception_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Performance (" << iterations << " operations):" << std::endl;
    std::cout << "std::expected: " << expected_time.count() << " microseconds" << std::endl;
    std::cout << "std::optional: " << optional_time.count() << " microseconds" << std::endl;
    std::cout << "Exceptions: " << exception_time.count() << " microseconds" << std::endl;
    
    std::cout << "Sums (for verification): " << sum_expected << ", " 
              << sum_optional << ", " << sum_exception << std::endl;
}

int main() {
    std::cout << "=== C++23 STD::EXPECTED DEMO ===" << std::endl;
    
    // 1. Basic usage
    std::cout << "\n1. Basic std::expected Usage:" << std::endl;
    
    auto result1 = safe_divide(10.0, 2.0);
    auto result2 = safe_divide(10.0, 0.0);
    
    print_expected(result1, "10.0 / 2.0");
    print_expected(result2, "10.0 / 0.0");
    
    // 2. Mathematical operations
    std::cout << "\n2. Mathematical Operations:" << std::endl;
    
    auto sqrt_result1 = safe_sqrt(16.0);
    auto sqrt_result2 = safe_sqrt(-4.0);
    
    print_expected(sqrt_result1, "sqrt(16.0)");
    print_expected(sqrt_result2, "sqrt(-4.0)");
    
    auto quad_result = quadratic_formula(1, -5, 6);  // x^2 - 5x + 6 = 0
    print_expected(quad_result, "Quadratic formula");
    
    // 3. String parsing
    std::cout << "\n3. String Parsing:" << std::endl;
    
    std::vector<std::string> test_strings = {"42", "3.14", "hello", "123abc", "", "999999999999999999999"};
    
    for (const auto& str : test_strings) {
        auto int_result = parse_int(str);
        auto double_result = parse_double(str);
        
        std::cout << "String '" << str << "':" << std::endl;
        print_expected(int_result, "  As int");
        print_expected(double_result, "  As double");
    }
    
    // 4. CSV parsing
    std::cout << "\n4. CSV Parsing:" << std::endl;
    
    std::vector<std::string> csv_tests = {
        "1,2,3,4,5",
        "10, 20, 30",
        "1,2,abc,4",
        "",
        "100,200,999999999999999999999"
    };
    
    for (const auto& csv : csv_tests) {
        auto result = parse_csv_integers(csv);
        
        if (result) {
            std::cout << "CSV '" << csv << "' -> [";
            for (size_t i = 0; i < result->size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << (*result)[i];
            }
            std::cout << "]" << std::endl;
        } else {
            std::cout << "CSV '" << csv << "' -> Error: " << to_string(result.error()) << std::endl;
        }
    }
    
    // 5. File operations (simulated)
    std::cout << "\n5. File Operations:" << std::endl;
    
    // Create a temporary file for testing
    std::string test_content = "Hello, World!\nThis is a test file.\n";
    auto write_result = write_file("test_expected.txt", test_content);
    print_expected(write_result, "Write file");
    
    if (write_result) {
        auto read_result = read_file("test_expected.txt");
        if (read_result) {
            std::cout << "Read file content:\n" << *read_result << std::endl;
        } else {
            print_expected(read_result, "Read file");
        }
    }
    
    // Try to read non-existent file
    auto missing_file = read_file("nonexistent.txt");
    print_expected(missing_file, "Read missing file");
    
    // 6. Configuration parsing
    std::cout << "\n6. Configuration Parsing:" << std::endl;
    
    std::string config_content = R"(
# Database configuration
host = localhost
port = 5432
database = myapp

# Logging settings
log_level = debug
log_file = /var/log/app.log

# Invalid line below
invalid_line_without_equals
)";
    
    ConfigParser parser;
    auto config_result = parser.parse_config(config_content);
    
    if (config_result) {
        std::cout << "Configuration parsed successfully:" << std::endl;
        for (const auto& [key, value] : *config_result) {
            std::cout << "  " << key << " = " << value << std::endl;
        }
    } else {
        print_expected(config_result, "Parse configuration");
    }
    
    // 7. Chained operations
    std::cout << "\n7. Chained Operations:" << std::endl;
    
    std::vector<std::string> math_inputs = {"16", "25", "-4", "abc"};
    
    for (const auto& input : math_inputs) {
        auto result = process_mathematical_string(input);
        if (result) {
            std::cout << "Process '" << input << "' -> " << *result << std::endl;
        } else {
            std::cout << "Process '" << input << "' -> " << result.error() << std::endl;
        }
    }
    
    // 8. Monadic operations
    demonstrate_monadic_operations();
    
    // 9. Value extraction and error handling
    std::cout << "\n9. Value Extraction Methods:" << std::endl;
    
    auto good_result = safe_divide(10.0, 2.0);
    auto bad_result = safe_divide(10.0, 0.0);
    
    // Using value() - throws if error
    try {
        std::cout << "Good result value(): " << good_result.value() << std::endl;
    } catch (const std::bad_expected_access<MathError>& e) {
        std::cout << "Exception: " << to_string(e.error()) << std::endl;
    }
    
    // Using value_or() - provides default
    std::cout << "Bad result value_or(-1): " << bad_result.value_or(-1.0) << std::endl;
    
    // Using error()
    if (!bad_result) {
        std::cout << "Bad result error: " << to_string(bad_result.error()) << std::endl;
    }
    
    // 10. Performance comparison
    performance_comparison();
    
    // 11. Best practices demonstration
    std::cout << "\n11. Best Practices:" << std::endl;
    
    // Use meaningful error types
    auto meaningful_error = [](bool condition) -> std::expected<std::string, MathError> {
        if (condition) {
            return "Success!";
        } else {
            return std::unexpected(MathError::INVALID_INPUT);
        }
    };
    
    auto result_good = meaningful_error(true);
    auto result_bad = meaningful_error(false);
    
    print_expected(result_good, "Meaningful success");
    print_expected(result_bad, "Meaningful error");
    
    // Chain operations safely
    auto safe_chain = [](double x) -> std::expected<double, MathError> {
        return safe_sqrt(x)
            .and_then([](double result) { return safe_divide(result, 2.0); })
            .transform([](double result) { return result * 3.14159; });
    };
    
    auto chain_result1 = safe_chain(16.0);  // Should work
    auto chain_result2 = safe_chain(-4.0);  // Should fail at sqrt
    
    print_expected(chain_result1, "Safe chain (16.0)");
    print_expected(chain_result2, "Safe chain (-4.0)");
    
    std::cout << "\n=== STD::EXPECTED BENEFITS ===" << std::endl;
    std::cout << "✅ Type-safe error handling without exceptions" << std::endl;
    std::cout << "✅ Composable with monadic operations (and_then, or_else, transform)" << std::endl;
    std::cout << "✅ Better performance than exceptions for error handling" << std::endl;
    std::cout << "✅ Self-documenting - function signature shows possible errors" << std::endl;
    std::cout << "✅ Forced error handling - compiler ensures you check for errors" << std::endl;
    std::cout << "✅ No hidden control flow like exceptions" << std::endl;
    std::cout << "✅ Works well with functional programming patterns" << std::endl;
    std::cout << "✅ Zero-cost abstraction when successful" << std::endl;
    std::cout << "⚠️  Larger binary size than raw return values" << std::endl;
    std::cout << "⚠️  Can make code more verbose than exception handling" << std::endl;
    std::cout << "⚠️  Requires C++23 support" << std::endl;
    std::cout << "⚠️  Learning curve for monadic operations" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++23 -Wall -Wextra -o expected_demo expected_demo.cpp
./expected_demo

C++23 std::expected Key Features:
1. Type-safe error handling without exceptions
2. Monadic operations for composing error-prone operations
3. Explicit error types in function signatures
4. Performance benefits over exception-based error handling

Basic Usage:
std::expected<T, E> result = function_that_might_fail();
if (result) {
    // Success case
    T value = *result;
    // or: T value = result.value();
} else {
    // Error case
    E error = result.error();
}

Creating Expected Values:
return value;                        // Success
return std::unexpected(error);       // Error

Monadic Operations:
result.and_then(func)    // Chain operations, short-circuit on error
      .or_else(handler)  // Handle errors
      .transform(mapper) // Transform success value

Access Methods:
- result.has_value() / bool(result)  - Check if successful
- *result / result.value()           - Get value (throws if error)
- result.value_or(default)           - Get value or default
- result.error()                     - Get error (only if has error)

Benefits over Exceptions:
- No hidden control flow
- Better performance (no stack unwinding)
- Explicit error types in signatures
- Composable error handling
- Zero-cost when successful

Benefits over Optional:
- Rich error information instead of just "no value"
- Multiple error types supported
- Better debugging information
- Self-documenting error conditions

Use Cases:
- File I/O operations
- Network operations
- Parsing and validation
- Mathematical operations
- System calls
- Any operation that can fail in predictable ways

Best Practices:
- Use meaningful error enum types
- Chain operations with monadic functions
- Provide good error messages
- Consider performance vs exceptions
- Document expected error conditions
- Use value_or() for simple defaults
*/
