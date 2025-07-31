// Traditional Headers - Implementation File
#include "calculator.h"
#include <stdexcept>
#include <cmath>

// Static member initialization
int Calculator::instance_count_ = 0;

Calculator::Calculator() {
    ++instance_count_;
    std::cout << "Calculator #" << instance_count_ << " created" << std::endl;
}

Calculator::~Calculator() {
    --instance_count_;
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

// Internal helper function - exposed through header but shouldn't be
void internal_helper_function() {
    std::cout << "This is an internal function that's accidentally exposed!" << std::endl;
}

// Utility namespace implementations
namespace CalculatorUtils {
    double calculate_compound_interest(double principal, double rate, int time) {
        return principal * std::pow((1 + rate / 100), time) - principal;
    }
    
    double calculate_simple_interest(double principal, double rate, int time) {
        return (principal * rate * time) / 100;
    }
}
