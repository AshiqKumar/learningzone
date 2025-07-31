// Modern C++20 Modules Approach - Calculator Module Interface
// This demonstrates the new, clean way of organizing C++ code

export module calculator;

// Import only what we need - no pollution
import <iostream>;
import <string>;
import <vector>;
import <cmath>;
import <stdexcept>;

// ONLY export what should be public
export class Calculator {
private:
    std::vector<double> history_;
    static int instance_count_;
    
    // Private implementation is truly private - not exposed to users
    void log_operation(const std::string& op, double result);
    
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
    
    // Template functions - implementation can be hidden!
    template<typename T>
    T calculate_percentage(T value, T percentage);
    
    template<typename T>
    T find_max(const std::vector<T>& values);
    
    // Utility functions
    void clear_history();
    void print_history() const;
    size_t get_history_size() const;
    
    static int get_instance_count();
};

// SELECTIVELY export utility functions
export double degrees_to_radians(double degrees);
export double radians_to_degrees(double radians);

// Export utility namespace
export namespace CalculatorUtils {
    double calculate_compound_interest(double principal, double rate, int time);
    double calculate_simple_interest(double principal, double rate, int time);
    
    template<typename T>
    double calculate_mean(const std::vector<T>& values);
}

// Template implementations - can be in module implementation section
// Users won't see these implementations!
template<typename T>
T Calculator::calculate_percentage(T value, T percentage) {
    return value * (percentage / 100.0);
}

template<typename T>
T Calculator::find_max(const std::vector<T>& values) {
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

template<typename T>
double CalculatorUtils::calculate_mean(const std::vector<T>& values) {
    if (values.empty()) return 0.0;
    T sum = T{};
    for (const T& val : values) {
        sum += val;
    }
    return static_cast<double>(sum) / values.size();
}

/*
BENEFITS OF C++20 MODULES:

1. CLEAN INTERFACES:
   - Only exported items are visible to users
   - No accidental exposure of internal functions
   - No macro pollution

2. FASTER COMPILATION:
   - Module interfaces compiled once
   - No text-based preprocessing
   - Faster incremental builds

3. BETTER ENCAPSULATION:
   - Private implementation truly private
   - Template implementations can be hidden
   - Clear separation of interface and implementation

4. NO INCLUDE ORDER ISSUES:
   - Modules are order-independent
   - No circular dependency problems
   - Robust build system

5. REDUCED NAMESPACE POLLUTION:
   - Only explicitly exported items visible
   - Internal constants and helpers invisible
   - Cleaner global namespace

This is the future of C++ organization!
*/
