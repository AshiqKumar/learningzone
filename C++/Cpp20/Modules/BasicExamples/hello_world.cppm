// C++20 Modules - Hello World Example
// This is the simplest possible module to demonstrate basic concepts

export module hello;  // Declare this file as a module named 'hello'

import <iostream>;     // Import standard library module for iostream
import <string>;       // Import string support

// Export a simple function that can be used by importers
export void say_hello(const std::string& name) {
    std::cout << "Hello, " << name << " from the 'hello' module!" << std::endl;
}

// Export a class demonstration
export class Greeter {
private:
    std::string greeting_;
    
public:
    explicit Greeter(const std::string& greeting = "Hello") 
        : greeting_(greeting) {}
    
    void greet(const std::string& name) const {
        std::cout << greeting_ << ", " << name << "!" << std::endl;
    }
    
    void set_greeting(const std::string& greeting) {
        greeting_ = greeting;
    }
};

// This function is NOT exported - it's internal to the module
// Importers of this module cannot see or use this function
void internal_helper() {
    std::cout << "[Internal] Helper function called" << std::endl;
}

// Export a function that uses the internal helper
export void demonstrate_privacy() {
    std::cout << "Demonstrating module privacy:" << std::endl;
    internal_helper();  // This works because we're inside the module
    std::cout << "The internal_helper() function cannot be called from outside this module" << std::endl;
}

/*
KEY CONCEPTS DEMONSTRATED:

1. MODULE DECLARATION:
   - 'export module hello' declares this file as a module named 'hello'
   - Other files can 'import hello' to use exported items

2. IMPORTING STANDARD LIBRARY:
   - 'import <iostream>' imports standard library modules
   - Faster than #include because it uses pre-compiled binary interfaces

3. EXPORTING ITEMS:
   - 'export' keyword makes functions/classes visible to importers
   - Items without 'export' are private to the module

4. ENCAPSULATION:
   - internal_helper() is not exported, so it's truly private
   - Better encapsulation than traditional headers

5. MODERN C++ FEATURES:
   - Works seamlessly with templates, classes, and modern C++ features
   - No header guards needed!
*/
