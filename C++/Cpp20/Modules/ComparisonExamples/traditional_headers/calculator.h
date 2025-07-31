// Traditional Headers Approach - Calculator Implementation
// This demonstrates the old way of organizing C++ code

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// All these are exposed to anyone including this header
#define PI_CONSTANT 3.14159265359  // Macro pollution
#define SQUARE(x) ((x) * (x))      // Dangerous macro

// Forward declarations
class Calculator;
void internal_helper_function();  // This will be visible even if we don't want it

// Calculator class - everything must be in header for templates
class Calculator {
private:
    std::vector<double> history_;
    static int instance_count_;
    
    // Private implementation must be in header
    void log_operation(const std::string& op, double result) {
        history_.push_back(result);
        std::cout << "[LOG] " << op << " = " << result << std::endl;
    }
    
public:
    Calculator();
    ~Calculator();
    
    // Basic operations
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    
    // Advanced operations
    double power(double base, double exponent);
    double sqrt(double value);
    
    // Template functions must be fully defined in header
    template<typename T>
    T calculate_percentage(T value, T percentage) {
        return value * (percentage / 100.0);
    }
    
    template<typename T>
    T find_max(const std::vector<T>& values) {
        if (values.empty()) {
            throw std::runtime_error("Empty vector");
        }
        T max_val = values[0];
        for (const T& val : values) {
            if (val > max_val) {
                max_val = val;
            }
        }
        return max_val;
    }
    
    // Utility functions
    void clear_history();
    void print_history() const;
    size_t get_history_size() const;
    
    static int get_instance_count();
};

// Global utility functions (will be in every translation unit)
inline double degrees_to_radians(double degrees) {
    return degrees * PI_CONSTANT / 180.0;
}

inline double radians_to_degrees(double radians) {
    return radians * 180.0 / PI_CONSTANT;
}

// This function is declared here but will be "internal" 
// However, it's still visible to all includers
void internal_helper_function();

// More utility functions that might not be needed everywhere
namespace CalculatorUtils {
    double calculate_compound_interest(double principal, double rate, int time);
    double calculate_simple_interest(double principal, double rate, int time);
    
    // Template utility - must be in header
    template<typename T>
    double calculate_mean(const std::vector<T>& values) {
        if (values.empty()) return 0.0;
        T sum = T{};
        for (const T& val : values) {
            sum += val;
        }
        return static_cast<double>(sum) / values.size();
    }
}

#endif // CALCULATOR_H

/*
PROBLEMS WITH TRADITIONAL HEADERS:

1. MACRO POLLUTION:
   - PI_CONSTANT and SQUARE macros are now global
   - Any file including this header gets these macros
   - Can cause naming conflicts and unexpected behavior

2. FORCED VISIBILITY:
   - internal_helper_function() is visible even though it shouldn't be
   - All private implementation details exposed
   - Users can depend on implementation details

3. COMPILATION OVERHEAD:
   - Every .cpp file including this header must:
     • Process all #include dependencies
     • Parse entire header file text
     • Recompile template definitions
   - Slower builds, especially in large projects

4. INCLUDE ORDER DEPENDENCY:
   - Order of includes can matter
   - Circular dependency issues
   - Fragile build system

5. TEMPLATE BLOAT:
   - Template definitions repeated in every translation unit
   - Larger object files
   - Longer link times

6. NAMESPACE POLLUTION:
   - Everything in header goes into every includer's namespace
   - Harder to track dependencies
   - Accidental usage of internal functions

This traditional approach works but has significant drawbacks
that C++20 modules solve elegantly!
*/
