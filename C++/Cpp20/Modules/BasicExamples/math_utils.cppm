// C++20 Modules - Mathematical Utilities Module
// Demonstrates exporting functions, constants, and template functions

export module math_utils;

import <iostream>;
import <cmath>;
import <type_traits>;

// ==================== EXPORTED CONSTANTS ====================
// Constants are exported and can be used by importers
export constexpr double PI = 3.141592653589793;
export constexpr double E = 2.718281828459045;

// ==================== EXPORTED FUNCTIONS ====================

// Basic mathematical operations
export double add(double a, double b) {
    return a + b;
}

export double multiply(double a, double b) {
    return a * b;
}

export double divide(double a, double b) {
    if (b == 0.0) {
        std::cerr << "Error: Division by zero!" << std::endl;
        return 0.0;
    }
    return a / b;
}

// Advanced mathematical functions
export double calculate_circle_area(double radius) {
    return PI * radius * radius;
}

export double calculate_circle_circumference(double radius) {
    return 2 * PI * radius;
}

export double power(double base, double exponent) {
    return std::pow(base, exponent);
}

// ==================== EXPORTED TEMPLATE FUNCTIONS ====================

// Template function for finding maximum of two values
export template<typename T>
constexpr T max_value(const T& a, const T& b) {
    return (a > b) ? a : b;
}

// Template function for finding minimum of two values  
export template<typename T>
constexpr T min_value(const T& a, const T& b) {
    return (a < b) ? a : b;
}

// Template function for calculating absolute value
export template<typename T>
constexpr T abs_value(const T& value) {
    return (value < T{}) ? -value : value;
}

// Advanced template with SFINAE (works only with arithmetic types)
export template<typename T>
constexpr auto square(const T& value) -> typename std::enable_if_t<std::is_arithmetic_v<T>, T> {
    return value * value;
}

// ==================== EXPORTED CLASSES ====================

// Mathematical calculator class
export class Calculator {
private:
    double memory_;
    static inline int calculation_count_ = 0;  // Static member
    
public:
    Calculator() : memory_(0.0) {
        calculation_count_++;
        std::cout << "Calculator created. Total calculators: " << calculation_count_ << std::endl;
    }
    
    ~Calculator() {
        calculation_count_--;
        std::cout << "Calculator destroyed. Remaining calculators: " << calculation_count_ << std::endl;
    }
    
    // Basic operations
    double add(double a, double b) {
        double result = a + b;
        memory_ = result;
        log_operation("ADD", a, b, result);
        return result;
    }
    
    double subtract(double a, double b) {
        double result = a - b;
        memory_ = result;
        log_operation("SUBTRACT", a, b, result);
        return result;
    }
    
    double multiply(double a, double b) {
        double result = a * b;
        memory_ = result;
        log_operation("MULTIPLY", a, b, result);
        return result;
    }
    
    double divide(double a, double b) {
        if (b == 0.0) {
            std::cerr << "Error: Division by zero!" << std::endl;
            return memory_;  // Return last valid result
        }
        double result = a / b;
        memory_ = result;
        log_operation("DIVIDE", a, b, result);
        return result;
    }
    
    // Memory operations
    double get_memory() const { return memory_; }
    void clear_memory() { memory_ = 0.0; }
    void set_memory(double value) { memory_ = value; }
    
    // Statistics
    static int get_calculator_count() { return calculation_count_; }
    
private:
    void log_operation(const std::string& op, double a, double b, double result) const {
        std::cout << "[CALC] " << a << " " << op << " " << b << " = " << result << std::endl;
    }
};

// ==================== PRIVATE/INTERNAL FUNCTIONS ====================
// These functions are NOT exported - they're internal to the module

namespace {  // Anonymous namespace for truly internal functions
    double internal_precision_multiply(double a, double b) {
        // High-precision multiplication implementation
        return a * b;
    }
    
    bool is_close(double a, double b, double epsilon = 1e-9) {
        return abs_value(a - b) < epsilon;
    }
}

// Internal helper function (not in anonymous namespace, but not exported)
void debug_print(const std::string& message) {
    std::cout << "[DEBUG] " << message << std::endl;
}

// ==================== EXPORTED ADVANCED FEATURES ====================

// Function that uses internal helpers but is exported
export bool compare_with_precision(double a, double b, double epsilon = 1e-9) {
    debug_print("Comparing " + std::to_string(a) + " with " + std::to_string(b));
    return is_close(a, b, epsilon);
}

// Template class for mathematical operations
export template<typename T>
class MathOperations {
private:
    T value_;
    
public:
    explicit MathOperations(const T& initial_value) : value_(initial_value) {}
    
    MathOperations& add(const T& other) {
        value_ = value_ + other;
        return *this;
    }
    
    MathOperations& multiply(const T& other) {
        value_ = value_ * other;
        return *this;
    }
    
    MathOperations& power(const T& exponent) {
        if constexpr (std::is_floating_point_v<T>) {
            value_ = std::pow(value_, exponent);
        } else {
            // Integer power implementation
            T result = T{1};
            for (T i = T{}; i < exponent; ++i) {
                result *= value_;
            }
            value_ = result;
        }
        return *this;
    }
    
    T get() const { return value_; }
    
    void reset(const T& new_value) { value_ = new_value; }
};

/*
KEY CONCEPTS DEMONSTRATED:

1. EXPORTING CONSTANTS:
   - constexpr constants can be exported and used in other modules
   - No need for extern declarations like with headers

2. EXPORTING FUNCTIONS:
   - Regular functions, template functions, and overloaded functions
   - Function templates work seamlessly with modules

3. EXPORTING CLASSES:
   - Complete classes with all their methods
   - Static members work correctly
   - Private members remain truly private

4. TEMPLATE SUPPORT:
   - Function templates and class templates export properly
   - SFINAE and other advanced template techniques work
   - constexpr and consteval functions supported

5. INTERNAL IMPLEMENTATION:
   - Functions without 'export' are private to the module
   - Anonymous namespaces provide additional encapsulation
   - Better than static functions in headers

6. ADVANCED FEATURES:
   - Static class members work correctly across module boundaries
   - Template specialization and SFINAE supported
   - Modern C++ features like auto return types work
*/
