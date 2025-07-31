// Modern C++20 Modules - Implementation File
module calculator;

// Private constants - NOT exported, completely internal
constexpr double PI_INTERNAL = 3.14159265359;
constexpr double EULER_INTERNAL = 2.71828182846;

// Static member initialization
int Calculator::instance_count_ = 0;

// Private helper function - truly private, not visible to users
namespace {
    void internal_helper_function() {
        std::cout << "This is truly internal - users can't access it!" << std::endl;
    }
    
    // More internal utilities
    double square_internal(double x) {
        return x * x;
    }
}

Calculator::Calculator() {
    ++instance_count_;
    std::cout << "Calculator #" << instance_count_ << " created" << std::endl;
}

Calculator::~Calculator() {
    --instance_count_;
}

void Calculator::log_operation(const std::string& op, double result) {
    history_.push_back(result);
    std::cout << "[LOG] " << op << " = " << result << std::endl;
    
    // Can use internal helper - but users can't!
    if (history_.size() % 10 == 0) {
        internal_helper_function();
    }
}

double Calculator::add(double a, double b) {
    double result = a + b;
    log_operation("ADD", result);
    return result;
}

double Calculator::subtract(double a, double b) {
    double result = a - b;
    log_operation("SUB", result);
    return result;
}

double Calculator::multiply(double a, double b) {
    double result = a * b;
    log_operation("MUL", result);
    return result;
}

double Calculator::divide(double a, double b) {
    if (b == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    double result = a / b;
    log_operation("DIV", result);
    return result;
}

double Calculator::power(double base, double exponent) {
    double result = std::pow(base, exponent);
    log_operation("POW", result);
    return result;
}

double Calculator::sqrt(double value) {
    if (value < 0.0) {
        throw std::runtime_error("Cannot take square root of negative number");
    }
    double result = std::sqrt(value);
    log_operation("SQRT", result);
    return result;
}

void Calculator::clear_history() {
    history_.clear();
    std::cout << "History cleared" << std::endl;
}

void Calculator::print_history() const {
    std::cout << "=== CALCULATION HISTORY ===" << std::endl;
    for (size_t i = 0; i < history_.size(); ++i) {
        std::cout << "  " << (i + 1) << ": " << history_[i] << std::endl;
    }
    std::cout << "===========================================" << std::endl;
}

size_t Calculator::get_history_size() const {
    return history_.size();
}

int Calculator::get_instance_count() {
    return instance_count_;
}

// Exported utility functions
double degrees_to_radians(double degrees) {
    return degrees * PI_INTERNAL / 180.0;  // Uses internal constant
}

double radians_to_degrees(double radians) {
    return radians * 180.0 / PI_INTERNAL;  // Users can't see PI_INTERNAL
}

// Utility namespace implementations
namespace CalculatorUtils {
    double calculate_compound_interest(double principal, double rate, int time) {
        // Can use internal helper functions
        double base = 1 + rate / 100;
        return principal * std::pow(base, time) - principal;
    }
    
    double calculate_simple_interest(double principal, double rate, int time) {
        return (principal * rate * time) / 100;
    }
}
