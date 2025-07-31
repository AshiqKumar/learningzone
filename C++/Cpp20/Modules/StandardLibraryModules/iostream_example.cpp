// C++20 Standard Library Modules - iostream Example
// Demonstrates using standard library modules instead of traditional headers

// Traditional approach (old way):
// #include <iostream>
// #include <iomanip>
// #include <sstream>

// Modern approach (C++20 modules):
import <iostream>;    // Import iostream as a module
import <iomanip>;     // Import iomanip as a module  
import <sstream>;     // Import sstream as a module
import <string>;      // Import string as a module
import <vector>;      // Import vector as a module

int main() {
    std::cout << "=== C++20 Standard Library Modules - iostream Example ===" << std::endl << std::endl;
    
    // ==================== BASIC OUTPUT OPERATIONS ====================
    std::cout << "1. BASIC OUTPUT OPERATIONS:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    std::cout << "Hello, C++20 Modules!" << std::endl;
    std::cout << "Integer: " << 42 << std::endl;
    std::cout << "Float: " << 3.14159 << std::endl;
    std::cout << "Boolean: " << std::boolalpha << true << std::endl;
    std::cout << std::endl;
    
    // ==================== FORMATTED OUTPUT ====================
    std::cout << "2. FORMATTED OUTPUT:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    double pi = 3.141592653589793;
    std::cout << "Pi with default precision: " << pi << std::endl;
    std::cout << "Pi with 2 decimal places: " << std::fixed << std::setprecision(2) << pi << std::endl;
    std::cout << "Pi with 6 decimal places: " << std::fixed << std::setprecision(6) << pi << std::endl;
    std::cout << "Pi in scientific notation: " << std::scientific << pi << std::endl;
    
    // Reset formatting
    std::cout << std::resetiosflags(std::ios::floatfield) << std::setprecision(6);
    std::cout << std::endl;
    
    // ==================== INPUT OPERATIONS ====================
    std::cout << "3. INPUT OPERATIONS:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    std::cout << "Enter your name: ";
    std::string name;
    std::getline(std::cin, name);
    
    std::cout << "Enter your age: ";
    int age;
    std::cin >> age;
    std::cin.ignore(); // Clear the input buffer
    
    std::cout << "Hello, " << name << "! You are " << age << " years old." << std::endl;
    std::cout << std::endl;
    
    // ==================== STRING STREAMS ====================
    std::cout << "4. STRING STREAMS:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Output string stream
    std::ostringstream oss;
    oss << "Name: " << name << ", Age: " << age;
    std::string userInfo = oss.str();
    std::cout << "Formatted string: " << userInfo << std::endl;
    
    // Input string stream
    std::string data = "42 3.14 Hello";
    std::istringstream iss(data);
    
    int number;
    double decimal;
    std::string word;
    
    iss >> number >> decimal >> word;
    std::cout << "Parsed from string:" << std::endl;
    std::cout << "  Integer: " << number << std::endl;
    std::cout << "  Double: " << decimal << std::endl;
    std::cout << "  String: " << word << std::endl;
    std::cout << std::endl;
    
    // ==================== ADVANCED FORMATTING ====================
    std::cout << "5. ADVANCED FORMATTING:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Width and alignment
    std::cout << std::left << std::setw(15) << "Left aligned" << "|" << std::endl;
    std::cout << std::right << std::setw(15) << "Right aligned" << "|" << std::endl;
    std::cout << std::setfill('*') << std::setw(15) << "Filled" << "|" << std::endl;
    std::cout << std::setfill(' '); // Reset fill character
    
    // Number formatting
    int hex_number = 255;
    std::cout << "Decimal: " << std::dec << hex_number << std::endl;
    std::cout << "Hexadecimal: " << std::hex << hex_number << std::endl;
    std::cout << "Octal: " << std::oct << hex_number << std::endl;
    std::cout << std::dec; // Reset to decimal
    std::cout << std::endl;
    
    // ==================== MODULE BENEFITS ====================
    std::cout << "6. MODULE BENEFITS:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    std::cout << "🚀 Benefits of using 'import <iostream>;' vs '#include <iostream>':" << std::endl << std::endl;
    
    std::cout << "✅ FASTER COMPILATION:" << std::endl;
    std::cout << "   • No text preprocessing - binary module interface" << std::endl;
    std::cout << "   • Recompilation only when module changes" << std::endl;
    std::cout << "   • Shared binary interface across translation units" << std::endl << std::endl;
    
    std::cout << "🔒 BETTER ISOLATION:" << std::endl;
    std::cout << "   • No macro pollution from headers" << std::endl;
    std::cout << "   • Private implementation details truly hidden" << std::endl;
    std::cout << "   • Cleaner namespace management" << std::endl << std::endl;
    
    std::cout << "📦 CLEANER DEPENDENCIES:" << std::endl;
    std::cout << "   • Import order doesn't matter" << std::endl;
    std::cout << "   • No circular dependency issues" << std::endl;
    std::cout << "   • Clear module boundaries" << std::endl << std::endl;
    
    std::cout << "⚡ PERFORMANCE:" << std::endl;
    std::cout << "   • Reduced memory usage during compilation" << std::endl;
    std::cout << "   • Faster linking phase" << std::endl;
    std::cout << "   • Better optimization opportunities" << std::endl << std::endl;
    
    // ==================== COMPARISON TABLE ====================
    std::cout << "7. COMPARISON: HEADERS vs MODULES:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    std::cout << "┌────────────────────┬─────────────────┬──────────────────┐" << std::endl;
    std::cout << "│      Feature       │     Headers     │     Modules      │" << std::endl;
    std::cout << "├────────────────────┼─────────────────┼──────────────────┤" << std::endl;
    std::cout << "│ Compilation Speed  │ ❌ Slow (reparse)│ ✅ Fast (binary) │" << std::endl;
    std::cout << "│ Macro Pollution    │ ❌ Yes (global)  │ ✅ No (isolated) │" << std::endl;
    std::cout << "│ Include Order      │ ❌ Matters       │ ✅ Independent   │" << std::endl;
    std::cout << "│ Preprocessing      │ ❌ Text-based    │ ✅ Binary        │" << std::endl;
    std::cout << "│ Memory Usage       │ ❌ High          │ ✅ Low           │" << std::endl;
    std::cout << "│ Build Parallelism  │ ❌ Limited       │ ✅ Better        │" << std::endl;
    std::cout << "└────────────────────┴─────────────────┴──────────────────┘" << std::endl;
    std::cout << std::endl;
    
    // ==================== PRACTICAL EXAMPLE ====================
    std::cout << "8. PRACTICAL EXAMPLE:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    // Create a simple table
    std::vector<std::pair<std::string, int>> products = {
        {"Laptop", 999},
        {"Mouse", 25},
        {"Keyboard", 75},
        {"Monitor", 299}
    };
    
    std::cout << "Product Inventory:" << std::endl;
    std::cout << "┌────────────┬───────────┐" << std::endl;
    std::cout << "│  Product   │   Price   │" << std::endl;
    std::cout << "├────────────┼───────────┤" << std::endl;
    
    for (const auto& [product, price] : products) {
        std::cout << "│ " << std::left << std::setw(10) << product 
                  << " │ $" << std::right << std::setw(8) << price << " │" << std::endl;
    }
    
    std::cout << "└────────────┴───────────┘" << std::endl;
    std::cout << std::endl;
    
    // ==================== COMPILATION NOTES ====================
    std::cout << "9. COMPILATION INFORMATION:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    std::cout << "To compile this standard library modules example:" << std::endl << std::endl;
    
    std::cout << "GCC (11+):" << std::endl;
    std::cout << "  g++ -std=c++20 -fmodules-ts iostream_example.cpp -o iostream_demo" << std::endl << std::endl;
    
    std::cout << "Clang (14+):" << std::endl;
    std::cout << "  clang++ -std=c++20 -fmodules iostream_example.cpp -o iostream_demo" << std::endl << std::endl;
    
    std::cout << "MSVC (2019+):" << std::endl;
    std::cout << "  cl /std:c++20 /experimental:module iostream_example.cpp" << std::endl << std::endl;
    
    std::cout << "🎉 Standard library modules demonstration completed!" << std::endl;
    
    return 0;
}

/*
KEY CONCEPTS DEMONSTRATED:

1. STANDARD LIBRARY MODULE IMPORTS:
   - import <iostream>; instead of #include <iostream>
   - Faster compilation through binary interfaces
   - Same functionality, better performance

2. SEAMLESS USAGE:
   - All iostream functions work exactly the same
   - std::cout, std::cin, manipulators work identically
   - No code changes needed, just import instead of include

3. PERFORMANCE BENEFITS:
   - No preprocessor text processing overhead
   - Binary module interfaces shared across files
   - Faster incremental builds

4. COMPATIBILITY:
   - Can mix module imports with traditional includes
   - Gradual migration path from headers to modules
   - All standard library features available

5. FUTURE-READY CODE:
   - Using modern C++20 features
   - Better tooling support
   - Cleaner dependency management

This example shows how easy it is to start using C++20 modules
with the standard library while getting immediate benefits!
*/
