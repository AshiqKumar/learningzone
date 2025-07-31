// Traditional Headers - Main Usage File
#include "calculator.h"
#include <vector>
#include <iostream>

int main() {
    std::cout << "=== TRADITIONAL HEADERS DEMO ===" << std::endl;
    
    try {
        // Create calculator instance
        Calculator calc;
        
        // Basic operations
        std::cout << "\n--- Basic Operations ---" << std::endl;
        double result1 = calc.add(10.5, 5.3);
        double result2 = calc.multiply(result1, 2.0);
        double result3 = calc.divide(result2, 3.0);
        
        // Template functions work
        std::cout << "\n--- Template Functions ---" << std::endl;
        double percentage = calc.calculate_percentage(150.0, 20.0);
        std::cout << "20% of 150 = " << percentage << std::endl;
        
        std::vector<int> numbers = {45, 78, 23, 89, 12, 67};
        int max_val = calc.find_max(numbers);
        std::cout << "Max value in vector: " << max_val << std::endl;
        
        // Utility functions
        std::cout << "\n--- Utility Functions ---" << std::endl;
        double angle_rad = degrees_to_radians(90.0);
        std::cout << "90 degrees in radians: " << angle_rad << std::endl;
        
        // Accidentally accessible internal function
        std::cout << "\n--- Problematic Exposure ---" << std::endl;
        internal_helper_function();  // This shouldn't be accessible!
        
        // Macro usage - can cause problems
        std::cout << "\n--- Macro Problems ---" << std::endl;
        std::cout << "PI_CONSTANT: " << PI_CONSTANT << std::endl;
        std::cout << "SQUARE(5): " << SQUARE(5) << std::endl;
        
        // Calculator utilities
        std::cout << "\n--- Calculator Utilities ---" << std::endl;
        double compound = CalculatorUtils::calculate_compound_interest(1000, 5, 2);
        std::cout << "Compound Interest: $" << compound << std::endl;
        
        std::vector<double> values = {1.0, 2.5, 3.7, 4.2, 5.8};
        double mean = CalculatorUtils::calculate_mean(values);
        std::cout << "Mean of values: " << mean << std::endl;
        
        // Show history
        calc.print_history();
        
        std::cout << "\nTotal Calculator instances: " 
                  << Calculator::get_instance_count() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== TRADITIONAL HEADERS PROBLEMS ===" << std::endl;
    std::cout << "1. Macro pollution (PI_CONSTANT, SQUARE)" << std::endl;
    std::cout << "2. Exposed internal functions" << std::endl;
    std::cout << "3. All template code in header" << std::endl;
    std::cout << "4. Long compilation times" << std::endl;
    std::cout << "5. Include order dependencies" << std::endl;
    std::cout << "6. Namespace pollution" << std::endl;
    
    return 0;
}

/*
COMPILE AND RUN:

Windows (MSVC):
    cl /EHsc /std:c++17 main_traditional.cpp calculator.cpp /Fe:traditional_demo.exe
    traditional_demo.exe

Linux/macOS (GCC):
    g++ -std=c++17 -o traditional_demo main_traditional.cpp calculator.cpp
    ./traditional_demo

Linux/macOS (Clang):
    clang++ -std=c++17 -o traditional_demo main_traditional.cpp calculator.cpp
    ./traditional_demo

PROBLEMS DEMONSTRATED:
- internal_helper_function() is accessible (shouldn't be!)
- Macros PI_CONSTANT and SQUARE pollute global namespace
- All template implementations visible in header
- Every file including calculator.h gets ALL dependencies
- Compilation time increases with each include
*/
