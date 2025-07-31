// C++23 if consteval - Compile-Time vs Runtime Detection
// Compile: g++ -std=c++23 -o consteval_demo consteval_demo.cpp
// Run: ./consteval_demo

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <type_traits>
#include <cassert>
#include <chrono>

// 1. Basic if consteval usage
constexpr int factorial(int n) {
    if consteval {
        // This branch is taken during constant evaluation
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    } else {
        // This branch is taken during runtime
        int result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }
}

// 2. Different algorithms for compile-time vs runtime
constexpr bool is_prime(int n) {
    if (n < 2) return false;
    
    if consteval {
        // Simple trial division for compile-time (easier to constant-evaluate)
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    } else {
        // Optimized runtime version with early exits
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
}

// 3. String processing with different approaches
constexpr std::string_view process_string(std::string_view input) {
    if consteval {
        // Compile-time: simple operations only
        return input.substr(0, input.find_first_of(" \t\n"));
    } else {
        // Runtime: can use more complex operations
        // Note: returning string_view from constexpr function requires care
        return input.substr(0, input.find_first_of(" \t\n"));
    }
}

// 4. Memory allocation detection
constexpr int process_data(bool use_dynamic = false) {
    if consteval {
        // Compile-time: cannot use dynamic allocation
        std::array<int, 10> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int sum = 0;
        for (int val : data) {
            sum += val;
        }
        return sum;
    } else {
        // Runtime: can use dynamic allocation if requested
        if (use_dynamic) {
            std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            int sum = 0;
            for (int val : data) {
                sum += val;
            }
            return sum;
        } else {
            // Use stack allocation at runtime too
            std::array<int, 10> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            int sum = 0;
            for (int val : data) {
                sum += val;
            }
            return sum;
        }
    }
}

// 5. Debug vs release behavior
constexpr int debug_function(int x) {
    if consteval {
        // Always include bounds checking at compile-time
        if (x < 0 || x > 1000) {
            // In real code, this might throw or return error
            return -1;
        }
        return x * x;
    } else {
        // Runtime: might skip checks in release builds
        #ifdef NDEBUG
            // Release build: skip checks for performance
            return x * x;
        #else
            // Debug build: include checks
            if (x < 0 || x > 1000) {
                std::cerr << "Warning: value out of range: " << x << std::endl;
                return -1;
            }
            return x * x;
        #endif
    }
}

// 6. Error handling differences
constexpr int safe_divide(int a, int b) {
    if consteval {
        // Compile-time: must handle errors without exceptions
        return (b == 0) ? 0 : a / b;
    } else {
        // Runtime: can use exceptions or other error handling
        if (b == 0) {
            std::cerr << "Division by zero!" << std::endl;
            return 0;
        }
        return a / b;
    }
}

// 7. Template specialization based on consteval
template<typename T>
constexpr T compute_value(T input) {
    if consteval {
        // Compile-time: use simple operations
        return input * 2 + 1;
    } else {
        // Runtime: can use more complex operations
        if constexpr (std::is_floating_point_v<T>) {
            return input * 2.0 + 1.0;
        } else {
            return input * 2 + 1;
        }
    }
}

// 8. Consteval constructor with if consteval
class SmartValue {
private:
    int value;
    bool is_constant;
    
public:
    constexpr SmartValue(int v) : value(v) {
        if consteval {
            is_constant = true;
        } else {
            is_constant = false;
        }
    }
    
    constexpr int get_value() const { return value; }
    constexpr bool is_compile_time() const { return is_constant; }
    
    constexpr void print() const {
        if consteval {
            // Cannot use std::cout at compile-time
            // This would be a compile error if called in constant evaluation
        } else {
            std::cout << "SmartValue: " << value 
                      << " (compile-time: " << is_constant << ")" << std::endl;
        }
    }
};

// 9. Configuration based on evaluation context
constexpr int get_buffer_size() {
    if consteval {
        // Compile-time: use smaller buffer for faster compilation
        return 64;
    } else {
        // Runtime: use larger buffer for better performance
        return 1024;
    }
}

template<int Size = get_buffer_size()>
class Buffer {
private:
    std::array<char, Size> data;
    
public:
    constexpr Buffer() : data{} {}
    
    constexpr size_t size() const { return Size; }
    
    constexpr char& operator[](size_t index) { return data[index]; }
    constexpr const char& operator[](size_t index) const { return data[index]; }
};

// 10. Optimization hints using consteval
constexpr int optimized_calculation(int n) {
    if consteval {
        // Compile-time: use simple but guaranteed-to-work approach
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += i * i;
        }
        return result;
    } else {
        // Runtime: use mathematical formula for better performance
        // Sum of squares: n(n-1)(2n-1)/6
        return (n * (n - 1) * (2 * n - 1)) / 6;
    }
}

// 11. Feature detection using consteval
constexpr bool has_fast_math() {
    if consteval {
        // Compile-time: assume no special math features
        return false;
    } else {
        // Runtime: can check CPU features
        #ifdef __FMA__
            return true;
        #else
            return false;
        #endif
    }
}

// 12. Logging system with consteval
constexpr void log_message(const char* message) {
    if consteval {
        // Compile-time: cannot log to console, but could store for later
        // This is mainly for demonstration
        (void)message;
    } else {
        // Runtime: actual logging
        std::cout << "[LOG] " << message << std::endl;
    }
}

// 13. Performance measurement
template<typename Func>
constexpr auto measure_performance(Func&& func) {
    if consteval {
        // Compile-time: cannot measure actual time
        func();
        return 0;  // Placeholder
    } else {
        // Runtime: actual timing
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
}

int main() {
    std::cout << "=== C++23 IF CONSTEVAL DEMO ===" << std::endl;
    
    // 1. Basic factorial demonstration
    std::cout << "\n1. Factorial with Different Algorithms:" << std::endl;
    
    // Compile-time evaluation
    constexpr int fact_compile = factorial(5);  // Uses recursive version
    std::cout << "Compile-time factorial(5): " << fact_compile << std::endl;
    
    // Runtime evaluation
    int n = 5;
    int fact_runtime = factorial(n);  // Uses iterative version
    std::cout << "Runtime factorial(5): " << fact_runtime << std::endl;
    
    // 2. Prime number checking
    std::cout << "\n2. Prime Number Checking:" << std::endl;
    
    constexpr bool prime_17 = is_prime(17);  // Compile-time
    std::cout << "17 is prime (compile-time): " << prime_17 << std::endl;
    
    int num = 17;
    bool prime_runtime = is_prime(num);  // Runtime
    std::cout << "17 is prime (runtime): " << prime_runtime << std::endl;
    
    // Test with larger numbers
    std::cout << "Testing prime checking with larger numbers:" << std::endl;
    std::vector<int> test_numbers = {97, 98, 99, 101, 103};
    
    for (int test_num : test_numbers) {
        bool is_prime_result = is_prime(test_num);
        std::cout << test_num << " is " << (is_prime_result ? "prime" : "not prime") << std::endl;
    }
    
    // 3. String processing
    std::cout << "\n3. String Processing:" << std::endl;
    
    constexpr auto processed_compile = process_string("Hello World");
    std::cout << "Compile-time processed: '" << processed_compile << "'" << std::endl;
    
    std::string input = "Hello World";
    auto processed_runtime = process_string(input);
    std::cout << "Runtime processed: '" << processed_runtime << "'" << std::endl;
    
    // 4. Data processing with different memory strategies
    std::cout << "\n4. Data Processing:" << std::endl;
    
    constexpr int sum_compile = process_data();
    std::cout << "Compile-time sum: " << sum_compile << std::endl;
    
    int sum_runtime_static = process_data(false);
    int sum_runtime_dynamic = process_data(true);
    std::cout << "Runtime sum (static): " << sum_runtime_static << std::endl;
    std::cout << "Runtime sum (dynamic): " << sum_runtime_dynamic << std::endl;
    
    // 5. Debug function demonstration
    std::cout << "\n5. Debug Function:" << std::endl;
    
    constexpr int debug_result_compile = debug_function(10);
    std::cout << "Debug function (compile-time): " << debug_result_compile << std::endl;
    
    int value = 10;
    int debug_result_runtime = debug_function(value);
    std::cout << "Debug function (runtime): " << debug_result_runtime << std::endl;
    
    // Test with out-of-range values
    int bad_value = -5;
    int debug_bad = debug_function(bad_value);
    std::cout << "Debug function with bad value: " << debug_bad << std::endl;
    
    // 6. Safe division
    std::cout << "\n6. Safe Division:" << std::endl;
    
    constexpr int div_result = safe_divide(10, 2);
    std::cout << "Safe divide (compile-time): " << div_result << std::endl;
    
    int a = 10, b = 0;
    int div_zero = safe_divide(a, b);
    std::cout << "Safe divide by zero: " << div_zero << std::endl;
    
    // 7. Template computation
    std::cout << "\n7. Template Computation:" << std::endl;
    
    constexpr int int_result = compute_value(5);
    constexpr double double_result = compute_value(5.0);
    
    std::cout << "Compute int (compile-time): " << int_result << std::endl;
    std::cout << "Compute double (compile-time): " << double_result << std::endl;
    
    int runtime_int = 5;
    double runtime_double = 5.0;
    int int_runtime = compute_value(runtime_int);
    double double_runtime = compute_value(runtime_double);
    
    std::cout << "Compute int (runtime): " << int_runtime << std::endl;
    std::cout << "Compute double (runtime): " << double_runtime << std::endl;
    
    // 8. SmartValue demonstration
    std::cout << "\n8. SmartValue Class:" << std::endl;
    
    constexpr SmartValue sv_compile(42);
    std::cout << "SmartValue compile-time - value: " << sv_compile.get_value() 
              << ", is_constant: " << sv_compile.is_compile_time() << std::endl;
    
    int runtime_val = 42;
    SmartValue sv_runtime(runtime_val);
    std::cout << "SmartValue runtime - value: " << sv_runtime.get_value() 
              << ", is_constant: " << sv_runtime.is_compile_time() << std::endl;
    
    sv_runtime.print();  // Only works at runtime
    
    // 9. Buffer with configurable size
    std::cout << "\n9. Configurable Buffer:" << std::endl;
    
    Buffer<> default_buffer;  // Uses get_buffer_size()
    Buffer<256> explicit_buffer;
    
    std::cout << "Default buffer size: " << default_buffer.size() << std::endl;
    std::cout << "Explicit buffer size: " << explicit_buffer.size() << std::endl;
    
    // 10. Optimized calculation
    std::cout << "\n10. Optimized Calculation:" << std::endl;
    
    constexpr int opt_compile = optimized_calculation(10);
    std::cout << "Optimized calculation (compile-time): " << opt_compile << std::endl;
    
    int n_runtime = 10;
    int opt_runtime = optimized_calculation(n_runtime);
    std::cout << "Optimized calculation (runtime): " << opt_runtime << std::endl;
    
    // Performance comparison
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        volatile int result = optimized_calculation(100);
        (void)result;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Runtime optimization (1M calls): " << duration.count() << " microseconds" << std::endl;
    
    // 11. Feature detection
    std::cout << "\n11. Feature Detection:" << std::endl;
    
    constexpr bool has_fast_compile = has_fast_math();
    std::cout << "Has fast math (compile-time): " << has_fast_compile << std::endl;
    
    bool has_fast_runtime = has_fast_math();
    std::cout << "Has fast math (runtime): " << has_fast_runtime << std::endl;
    
    // 12. Logging system
    std::cout << "\n12. Logging System:" << std::endl;
    
    log_message("This is a runtime log message");
    
    // Compile-time call would not produce output
    constexpr auto compile_log = []() { log_message("Compile-time message"); return 0; }();
    (void)compile_log;
    
    // 13. Performance measurement
    std::cout << "\n13. Performance Measurement:" << std::endl;
    
    auto lambda = []() {
        volatile int sum = 0;
        for (int i = 0; i < 1000; ++i) {
            sum += i;
        }
    };
    
    // Compile-time "measurement"
    constexpr auto compile_time = measure_performance([](){});
    std::cout << "Compile-time measurement result: " << compile_time << std::endl;
    
    // Runtime measurement
    auto runtime_time = measure_performance(lambda);
    std::cout << "Runtime measurement: " << runtime_time << " microseconds" << std::endl;
    
    // 14. Conditional compilation based on consteval
    std::cout << "\n14. Conditional Compilation:" << std::endl;
    
    auto conditional_func = [](int x) constexpr {
        if consteval {
            // Compile-time version - simple and safe
            return x > 0 ? x : 0;
        } else {
            // Runtime version - can be more sophisticated
            return std::max(x, 0);
        }
    };
    
    constexpr int cond_compile = conditional_func(-5);
    int cond_runtime = conditional_func(-5);
    
    std::cout << "Conditional function (compile-time): " << cond_compile << std::endl;
    std::cout << "Conditional function (runtime): " << cond_runtime << std::endl;
    
    // 15. Practical example: Configuration system
    std::cout << "\n15. Configuration System Example:" << std::endl;
    
    auto get_config_value = [](const char* key) constexpr -> int {
        if consteval {
            // Compile-time: use preprocessor or constexpr values
            if (std::string_view(key) == "buffer_size") return 1024;
            if (std::string_view(key) == "max_connections") return 100;
            return 0;  // Default
        } else {
            // Runtime: could read from file, environment, etc.
            std::string_view k(key);
            if (k == "buffer_size") return 2048;  // Runtime might have different values
            if (k == "max_connections") return 200;
            return 0;
        }
    };
    
    constexpr int compile_buffer_size = get_config_value("buffer_size");
    int runtime_buffer_size = get_config_value("buffer_size");
    
    std::cout << "Buffer size (compile-time): " << compile_buffer_size << std::endl;
    std::cout << "Buffer size (runtime): " << runtime_buffer_size << std::endl;
    
    std::cout << "\n=== IF CONSTEVAL BENEFITS ===" << std::endl;
    std::cout << "✅ Choose different algorithms for compile-time vs runtime" << std::endl;
    std::cout << "✅ Optimize for compilation speed vs execution speed" << std::endl;
    std::cout << "✅ Handle constraints of constant evaluation" << std::endl;
    std::cout << "✅ Enable different error handling strategies" << std::endl;
    std::cout << "✅ Better debugging and logging control" << std::endl;
    std::cout << "✅ Allows conditional feature usage" << std::endl;
    std::cout << "✅ More flexible than separate constexpr/non-constexpr functions" << std::endl;
    std::cout << "⚠️  Requires C++23 compiler support" << std::endl;
    std::cout << "⚠️  Can make code more complex to understand" << std::endl;
    std::cout << "⚠️  Need to ensure both branches are valid" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++23 -Wall -Wextra -o consteval_demo consteval_demo.cpp
./consteval_demo

C++23 if consteval Key Features:
1. Detect whether code is being evaluated at compile-time or runtime
2. Choose different algorithms based on evaluation context
3. Handle limitations of constant evaluation gracefully
4. Optimize for compilation speed vs execution performance

Basic Usage:
constexpr int func(int n) {
    if consteval {
        // This runs during constant evaluation (compile-time)
        return simple_algorithm(n);
    } else {
        // This runs at runtime
        return optimized_algorithm(n);
    }
}

Use Cases:
- Different algorithms for compile-time vs runtime
- Handle dynamic memory restrictions at compile-time
- Conditional debugging/logging
- Feature detection and capability branching
- Performance vs compilation speed tradeoffs

Benefits over Traditional Approaches:
- Single function instead of separate constexpr/non-constexpr versions
- More flexible than constexpr if and requires clauses
- Better control over constant evaluation constraints
- Enables hybrid compile-time/runtime optimizations

Comparison with if constexpr:
- if constexpr: Compile-time branching based on conditions
- if consteval: Runtime detection of evaluation context
- if consteval branches based on HOW code is called, not template parameters

Common Patterns:
1. Algorithm Selection:
   - Simple/reliable for compile-time
   - Optimized/complex for runtime

2. Resource Management:
   - Stack-only at compile-time
   - Dynamic allocation at runtime

3. Error Handling:
   - Return codes at compile-time
   - Exceptions at runtime

4. Feature Detection:
   - Conservative at compile-time
   - Full capability at runtime

Best Practices:
- Keep compile-time branches simple and reliable
- Use runtime branches for optimizations
- Test both branches thoroughly
- Document the different behaviors
- Consider maintenance complexity
*/
