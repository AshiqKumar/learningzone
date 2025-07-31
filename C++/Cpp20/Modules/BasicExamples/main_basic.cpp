// C++20 Modules - Basic Examples Consumer
// This file demonstrates importing and using modules

import hello;          // Import our hello module
import math_utils;     // Import our math_utils module
import <iostream>;     // Import standard library modules
import <string>;
import <vector>;

int main() {
    std::cout << "=== C++20 Modules Basic Examples Demo ===" << std::endl << std::endl;
    
    // ==================== HELLO MODULE DEMONSTRATION ====================
    std::cout << "1. HELLO MODULE DEMONSTRATION:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Use exported function
    say_hello("C++ Developer");
    
    // Use exported class
    Greeter greeter;
    greeter.greet("Alice");
    greeter.greet("Bob");
    
    // Change greeting and use again
    greeter.set_greeting("Welcome");
    greeter.greet("Charlie");
    
    // Demonstrate privacy
    demonstrate_privacy();
    
    // NOTE: The following would cause a compilation error because
    // internal_helper() is not exported from the hello module:
    // internal_helper();  // ERROR! Function not exported
    
    std::cout << std::endl;
    
    // ==================== MATH UTILS MODULE DEMONSTRATION ====================
    std::cout << "2. MATH UTILS MODULE DEMONSTRATION:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Use exported constants
    std::cout << "Mathematical constants:" << std::endl;
    std::cout << "  PI = " << PI << std::endl;
    std::cout << "  E = " << E << std::endl << std::endl;
    
    // Use exported functions
    double a = 15.5, b = 4.2;
    std::cout << "Basic operations with " << a << " and " << b << ":" << std::endl;
    std::cout << "  Add: " << add(a, b) << std::endl;
    std::cout << "  Multiply: " << multiply(a, b) << std::endl;
    std::cout << "  Divide: " << divide(a, b) << std::endl << std::endl;
    
    // Advanced mathematical functions
    double radius = 5.0;
    std::cout << "Circle calculations (radius = " << radius << "):" << std::endl;
    std::cout << "  Area: " << calculate_circle_area(radius) << std::endl;
    std::cout << "  Circumference: " << calculate_circle_circumference(radius) << std::endl << std::endl;
    
    // Power function
    double base = 2.0, exponent = 8.0;
    std::cout << base << " to the power of " << exponent << " = " << power(base, exponent) << std::endl << std::endl;
    
    // ==================== TEMPLATE FUNCTIONS DEMONSTRATION ====================
    std::cout << "3. TEMPLATE FUNCTIONS DEMONSTRATION:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Template functions with different types
    std::cout << "Template functions work with different types:" << std::endl;
    
    // With integers
    int int1 = 42, int2 = 17;
    std::cout << "  max_value(" << int1 << ", " << int2 << ") = " << max_value(int1, int2) << std::endl;
    std::cout << "  min_value(" << int1 << ", " << int2 << ") = " << min_value(int1, int2) << std::endl;
    std::cout << "  abs_value(-25) = " << abs_value(-25) << std::endl;
    
    // With doubles
    double d1 = 3.14, d2 = 2.71;
    std::cout << "  max_value(" << d1 << ", " << d2 << ") = " << max_value(d1, d2) << std::endl;
    std::cout << "  square(" << d1 << ") = " << square(d1) << std::endl;
    
    // With strings (lexicographic comparison)
    std::string str1 = "apple", str2 = "banana";
    std::cout << "  max_value(\"" << str1 << "\", \"" << str2 << "\") = \"" << max_value(str1, str2) << "\"" << std::endl << std::endl;
    
    // ==================== CALCULATOR CLASS DEMONSTRATION ====================
    std::cout << "4. CALCULATOR CLASS DEMONSTRATION:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    {
        // Create calculators to demonstrate static members
        Calculator calc1;
        Calculator calc2;
        
        std::cout << "Current calculator count: " << Calculator::get_calculator_count() << std::endl << std::endl;
        
        // Use calculator operations
        std::cout << "Calculator operations:" << std::endl;
        calc1.add(10.0, 5.0);
        calc1.multiply(3.0, 4.0);
        calc1.divide(20.0, 4.0);
        calc1.subtract(15.0, 7.0);
        
        std::cout << "Memory value: " << calc1.get_memory() << std::endl;
        
        // Memory operations
        calc1.set_memory(100.0);
        std::cout << "Memory after setting to 100: " << calc1.get_memory() << std::endl;
        calc1.clear_memory();
        std::cout << "Memory after clearing: " << calc1.get_memory() << std::endl << std::endl;
        
        // Precision comparison
        double val1 = 0.1 + 0.2;
        double val2 = 0.3;
        std::cout << "Precision comparison:" << std::endl;
        std::cout << "  " << val1 << " == " << val2 << " ? " << (val1 == val2 ? "true" : "false") << std::endl;
        std::cout << "  Using compare_with_precision: " << (compare_with_precision(val1, val2) ? "true" : "false") << std::endl;
        
    } // Calculators destroyed here
    
    std::cout << "Calculator count after destruction: " << Calculator::get_calculator_count() << std::endl << std::endl;
    
    // ==================== TEMPLATE CLASS DEMONSTRATION ====================
    std::cout << "5. TEMPLATE CLASS DEMONSTRATION:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Integer math operations
    MathOperations<int> intMath(5);
    int result = intMath.add(3).multiply(2).power(2).get();
    std::cout << "Integer operations: ((5 + 3) * 2) ^ 2 = " << result << std::endl;
    
    // Double math operations  
    MathOperations<double> doubleMath(2.5);
    double dresult = doubleMath.add(1.5).multiply(2.0).power(1.5).get();
    std::cout << "Double operations: ((2.5 + 1.5) * 2.0) ^ 1.5 = " << dresult << std::endl << std::endl;
    
    // ==================== MODULES BENEFITS DEMONSTRATION ====================
    std::cout << "6. MODULES BENEFITS:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    std::cout << "✅ Fast compilation: No preprocessor text processing" << std::endl;
    std::cout << "✅ Strong encapsulation: Private functions truly private" << std::endl;
    std::cout << "✅ No header guards needed: Modules prevent redefinition" << std::endl;
    std::cout << "✅ Order independence: Import order doesn't matter" << std::endl;
    std::cout << "✅ Template support: Templates work seamlessly" << std::endl;
    std::cout << "✅ Binary interfaces: Faster incremental builds" << std::endl;
    std::cout << "✅ Namespace compatibility: Works with existing code" << std::endl << std::endl;
    
    // ==================== COMPILATION INFORMATION ====================
    std::cout << "7. COMPILATION NOTES:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "To compile this example:" << std::endl;
    std::cout << "1. Compile modules first:" << std::endl;
    std::cout << "   g++ -std=c++20 -fmodules-ts -c hello_world.cppm" << std::endl;
    std::cout << "   g++ -std=c++20 -fmodules-ts -c math_utils.cppm" << std::endl;
    std::cout << "2. Compile main program:" << std::endl;
    std::cout << "   g++ -std=c++20 -fmodules-ts main_basic.cpp hello_world.o math_utils.o -o basic_demo" << std::endl;
    std::cout << "3. Run:" << std::endl;
    std::cout << "   ./basic_demo" << std::endl << std::endl;
    
    std::cout << "🎉 C++20 Modules demonstration completed successfully!" << std::endl;
    
    return 0;
}

/*
KEY CONCEPTS DEMONSTRATED IN THIS MAIN FILE:

1. MODULE IMPORTING:
   - import hello;          // Import custom module
   - import math_utils;     // Import another custom module  
   - import <iostream>;     // Import standard library module

2. SEAMLESS USAGE:
   - Exported functions and classes work exactly like traditional headers
   - Template functions and classes work without any special syntax
   - Constants and static members work correctly

3. COMPILATION SAFETY:
   - Cannot access non-exported items (would cause compile error)
   - Type safety maintained across module boundaries
   - Template instantiation works correctly

4. PERFORMANCE BENEFITS:
   - Faster compilation due to binary module interfaces
   - No repeated preprocessing of headers
   - Better dependency management

5. COMPATIBILITY:
   - Works alongside traditional headers
   - Can gradually migrate existing code
   - Standard library modules work seamlessly

This example shows that modules provide all the benefits of headers
with better performance, encapsulation, and safety!
*/
