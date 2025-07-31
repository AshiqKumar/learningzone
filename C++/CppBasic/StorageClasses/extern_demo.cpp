/**
 * @file extern_demo.cpp
 * @brief Demonstration of 'extern' storage class
 * 
 * Compile with extern_vars.cpp:
 * g++ -std=c++17 -Wall -Wextra extern_demo.cpp extern_vars.cpp -o extern_demo
 * Run: ./extern_demo
 */

#include <iostream>
#include <string>

// External variable declarations (defined in extern_vars.cpp)
extern int extern_global_int;
extern double extern_global_double;
extern std::string extern_global_string;
extern int extern_array[5];

// External function declarations (defined in extern_vars.cpp)
extern void extern_function();
extern void modify_extern_vars();

// External class declaration (defined in extern_vars.cpp)
class ExternClass {
private:
    static int instance_count;
    int id;
    
public:
    ExternClass();
    int getId() const;
    static int getInstanceCount();
    ~ExternClass();
};

extern ExternClass createExternClassInstance();

// External template function declaration
template<typename T>
extern T extern_template_function(T a, T b);

// External namespace declaration
namespace ExternNamespace {
    extern int namespace_var;
    extern void namespace_function();
}

// External const declarations
extern const int extern_const_int;
extern const char* const extern_const_string;

// External C linkage declarations
extern "C" {
    extern int c_style_function(int x, int y);
    extern int c_global_var;
}

// Local variables for comparison
int local_global = 100;
static int file_static = 200;

// Function to demonstrate extern vs other storage classes
void demonstrateStorageClasses() {
    auto local_auto = 50;          // Automatic storage
    static int local_static = 75;  // Static storage
    
    std::cout << "\n=== Storage Class Comparison ===" << std::endl;
    std::cout << "Local global: " << local_global << std::endl;
    std::cout << "File static: " << file_static << std::endl;
    std::cout << "Local auto: " << local_auto << std::endl;
    std::cout << "Local static: " << local_static << std::endl;
    std::cout << "External global: " << extern_global_int << std::endl;
    
    // Modify values
    local_global += 10;
    file_static += 10;
    local_auto += 10;
    local_static += 10;
    extern_global_int += 10;  // Modifying external variable
    
    std::cout << "\nAfter modification:" << std::endl;
    std::cout << "Local global: " << local_global << std::endl;
    std::cout << "File static: " << file_static << std::endl;
    std::cout << "Local auto: " << local_auto << std::endl;
    std::cout << "Local static: " << local_static << std::endl;
    std::cout << "External global: " << extern_global_int << std::endl;
}

// Function declarations that will be defined later in this file
extern void forward_declared_function();  // Forward declaration with extern

int main() {
    std::cout << "=== EXTERN STORAGE CLASS DEMO ===" << std::endl;
    
    // 1. Basic external variables
    std::cout << "\n1. External Variables:" << std::endl;
    std::cout << "extern_global_int: " << extern_global_int << std::endl;
    std::cout << "extern_global_double: " << extern_global_double << std::endl;
    std::cout << "extern_global_string: " << extern_global_string << std::endl;
    
    // 2. External arrays
    std::cout << "\n2. External Arrays:" << std::endl;
    std::cout << "extern_array contents: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << extern_array[i] << " ";
    }
    std::cout << std::endl;
    
    // 3. External functions
    std::cout << "\n3. External Functions:" << std::endl;
    extern_function();
    
    // 4. Modifying external variables
    std::cout << "\n4. Modifying External Variables:" << std::endl;
    std::cout << "Before modification:" << std::endl;
    std::cout << "extern_global_int: " << extern_global_int << std::endl;
    std::cout << "extern_global_string: " << extern_global_string << std::endl;
    
    modify_extern_vars();
    
    std::cout << "After modification:" << std::endl;
    std::cout << "extern_global_int: " << extern_global_int << std::endl;
    std::cout << "extern_global_string: " << extern_global_string << std::endl;
    
    // 5. External classes
    std::cout << "\n5. External Classes:" << std::endl;
    std::cout << "Initial instance count: " << ExternClass::getInstanceCount() << std::endl;
    
    {
        ExternClass obj1 = createExternClassInstance();
        ExternClass obj2 = createExternClassInstance();
        
        std::cout << "obj1 ID: " << obj1.getId() << std::endl;
        std::cout << "obj2 ID: " << obj2.getId() << std::endl;
        std::cout << "Current instance count: " << ExternClass::getInstanceCount() << std::endl;
    }  // Objects destroyed here
    
    std::cout << "Final instance count: " << ExternClass::getInstanceCount() << std::endl;
    
    // 6. External template functions
    std::cout << "\n6. External Template Functions:" << std::endl;
    int int_result = extern_template_function(10, 20);
    double double_result = extern_template_function(3.14, 2.86);
    
    std::cout << "Template function (int): " << int_result << std::endl;
    std::cout << "Template function (double): " << double_result << std::endl;
    
    // 7. External namespace
    std::cout << "\n7. External Namespace:" << std::endl;
    ExternNamespace::namespace_function();
    std::cout << "Accessing namespace_var: " << ExternNamespace::namespace_var << std::endl;
    
    // 8. External const variables
    std::cout << "\n8. External Const Variables:" << std::endl;
    std::cout << "extern_const_int: " << extern_const_int << std::endl;
    std::cout << "extern_const_string: " << extern_const_string << std::endl;
    
    // 9. C linkage
    std::cout << "\n9. C Linkage (extern \"C\"):" << std::endl;
    int c_result = c_style_function(5, 6);
    std::cout << "C-style function result: " << c_result << std::endl;
    std::cout << "C global variable: " << c_global_var << std::endl;
    
    // 10. Storage class comparison
    std::cout << "\n10. Storage Class Demonstration:" << std::endl;
    demonstrateStorageClasses();
    demonstrateStorageClasses();  // Call again to see static behavior
    
    // 11. Forward declared function
    std::cout << "\n11. Forward Declared Function:" << std::endl;
    forward_declared_function();
    
    // 12. Extern with different variable types
    std::cout << "\n12. Various External Types:" << std::endl;
    
    // External variable in different scopes
    {
        extern int extern_global_int;  // Re-declaration in local scope
        std::cout << "Local scope extern_global_int: " << extern_global_int << std::endl;
        extern_global_int = 99999;    // Modifies the same global variable
    }
    std::cout << "After local scope modification: " << extern_global_int << std::endl;
    
    // 13. Multiple extern declarations
    std::cout << "\n13. Multiple Extern Declarations:" << std::endl;
    extern int extern_global_int;     // Multiple declarations are OK
    extern int extern_global_int;     // As long as they match
    std::cout << "Multiple declarations of extern_global_int: " << extern_global_int << std::endl;
    
    std::cout << "\n=== EXTERN BENEFITS ===" << std::endl;
    std::cout << "✅ Enables sharing variables across multiple files" << std::endl;
    std::cout << "✅ Provides external linkage for global visibility" << std::endl;
    std::cout << "✅ Allows forward declarations of functions and variables" << std::endl;
    std::cout << "✅ Essential for modular programming" << std::endl;
    std::cout << "✅ Enables C/C++ interoperability with extern \"C\"" << std::endl;
    
    std::cout << "\n=== EXTERN CONSIDERATIONS ===" << std::endl;
    std::cout << "⚠️  Must have exactly one definition (ODR - One Definition Rule)" << std::endl;
    std::cout << "⚠️  Declaration and definition types must match exactly" << std::endl;
    std::cout << "⚠️  Can lead to namespace pollution with many globals" << std::endl;
    std::cout << "⚠️  Initialization order issues with global objects" << std::endl;
    std::cout << "⚠️  Makes code harder to test and debug" << std::endl;
    std::cout << "⚠️  Consider alternatives: namespaces, classes, dependency injection" << std::endl;
    
    return 0;
}

// Definition of forward declared function
void forward_declared_function() {
    std::cout << "forward_declared_function() called" << std::endl;
    std::cout << "This function was declared with extern earlier" << std::endl;
}

/*
Extern Storage Class Summary:

1. Purpose:
   - Provides external linkage
   - Enables sharing variables/functions across translation units
   - Allows forward declarations

2. Variable Declarations:
   - extern int global_var;     // Declaration
   - int global_var = 42;       // Definition (in another file)
   - Only one definition allowed (ODR)

3. Function Declarations:
   - extern void func();        // Declaration
   - void func() { ... }        // Definition (can be in another file)
   - Function declarations are extern by default

4. Key Rules:
   - Declaration tells compiler about existence
   - Definition allocates storage and provides implementation
   - Must have exactly one definition per program
   - Multiple declarations are allowed if they match

5. Common Use Cases:
   - Global configuration variables
   - Shared data structures
   - API function declarations
   - C/C++ interoperability
   - Large codebases with multiple files

6. Alternatives:
   - Namespaces for organization
   - Classes for encapsulation
   - Dependency injection for loose coupling
   - Singleton pattern for single instances
   - Static class members for shared state

7. Best Practices:
   - Use header files for extern declarations
   - Minimize global state
   - Prefer const extern variables
   - Use extern "C" for C compatibility
   - Consider thread safety for global variables
*/
