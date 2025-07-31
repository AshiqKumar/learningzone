// Modern C++20 Modules - Main Usage File
import calculator;  // Clean, simple import!
import <vector>;
import <iostream>;

int main() {
    std::cout << "=== MODERN C++20 MODULES DEMO ===" << std::endl;
    
    try {
        // Create calculator instance
        Calculator calc;
        
        // Basic operations
        std::cout << "\n--- Basic Operations ---" << std::endl;
        double result1 = calc.add(10.5, 5.3);
        double result2 = calc.multiply(result1, 2.0);
        double result3 = calc.divide(result2, 3.0);
        
        // Template functions work seamlessly
        std::cout << "\n--- Template Functions ---" << std::endl;
        double percentage = calc.calculate_percentage(150.0, 20.0);
        std::cout << "20% of 150 = " << percentage << std::endl;
        
        std::vector<int> numbers = {45, 78, 23, 89, 12, 67};
        int max_val = calc.find_max(numbers);
        std::cout << "Max value in vector: " << max_val << std::endl;
        
        // Utility functions - only what was exported
        std::cout << "\n--- Utility Functions ---" << std::endl;
        double angle_rad = degrees_to_radians(90.0);
        std::cout << "90 degrees in radians: " << angle_rad << std::endl;
        
        // Try to access internal function - COMPILATION ERROR!
        std::cout << "\n--- Perfect Encapsulation ---" << std::endl;
        std::cout << "Internal functions are NOT accessible!" << std::endl;
        // internal_helper_function();  // <-- This would cause compilation error!
        // PI_INTERNAL;                 // <-- This would cause compilation error!
        
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
    
    std::cout << "\n=== C++20 MODULES BENEFITS ===" << std::endl;
    std::cout << "✅ No macro pollution" << std::endl;
    std::cout << "✅ Perfect encapsulation" << std::endl;
    std::cout << "✅ Fast compilation" << std::endl;
    std::cout << "✅ No include order issues" << std::endl;
    std::cout << "✅ Clean interfaces" << std::endl;
    std::cout << "✅ Template implementations hidden" << std::endl;
    
    return 0;
}

/*
COMPILE AND RUN (C++20 Modules):

Windows (MSVC):
    cl /EHsc /std:c++20 /experimental:module calculator.cppm /c
    cl /EHsc /std:c++20 calculator_impl.cpp calculator.obj main_modern.cpp /Fe:modern_demo.exe
    modern_demo.exe

Linux/macOS (GCC 11+):
    g++ -std=c++20 -fmodules-ts -c calculator.cppm
    g++ -std=c++20 -fmodules-ts -o modern_demo main_modern.cpp calculator_impl.cpp
    ./modern_demo

Linux/macOS (Clang 15+):
    clang++ -std=c++20 --precompile calculator.cppm -o calculator.pcm
    clang++ -std=c++20 -fprebuilt-module-path=. -o modern_demo main_modern.cpp calculator_impl.cpp
    ./modern_demo

ADVANTAGES DEMONSTRATED:
- ✅ internal_helper_function() is NOT accessible
- ✅ PI_INTERNAL constant is completely hidden
- ✅ No macros polluting the global namespace
- ✅ Template implementations are hidden from users
- ✅ Clean import syntax with no order dependencies
- ✅ Faster compilation (after initial build)
*/
