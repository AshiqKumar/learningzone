/**
 * @file extern_vars.cpp
 * @brief External variable definitions for extern_demo.cpp
 * 
 * This file contains the actual definitions of external variables
 * and functions declared in extern_demo.cpp
 */

#include <iostream>
#include <string>

// External variable definitions
int extern_global_int = 12345;
double extern_global_double = 98.76;
std::string extern_global_string = "External String from extern_vars.cpp";

// External array definition
int extern_array[5] = {10, 20, 30, 40, 50};

// External function definitions
void extern_function() {
    std::cout << "extern_function() called from extern_vars.cpp" << std::endl;
    std::cout << "Accessing extern_global_int: " << extern_global_int << std::endl;
}

void modify_extern_vars() {
    extern_global_int *= 2;
    extern_global_double += 1.5;
    extern_global_string += " [Modified]";
    
    std::cout << "External variables modified in extern_vars.cpp" << std::endl;
}

// External class definition
class ExternClass {
private:
    static int instance_count;
    int id;
    
public:
    ExternClass() : id(++instance_count) {
        std::cout << "ExternClass instance " << id << " created" << std::endl;
    }
    
    int getId() const { return id; }
    static int getInstanceCount() { return instance_count; }
    
    ~ExternClass() {
        std::cout << "ExternClass instance " << id << " destroyed" << std::endl;
    }
};

// Static member definition
int ExternClass::instance_count = 0;

// Function returning ExternClass instance
ExternClass createExternClassInstance() {
    std::cout << "Creating ExternClass instance in extern_vars.cpp" << std::endl;
    return ExternClass();
}

// Template function definition
template<typename T>
T extern_template_function(T a, T b) {
    std::cout << "extern_template_function called with type: " << typeid(T).name() << std::endl;
    return a + b;
}

// Explicit template instantiations
template int extern_template_function<int>(int, int);
template double extern_template_function<double>(double, double);

// Namespace with external linkage
namespace ExternNamespace {
    int namespace_var = 777;
    
    void namespace_function() {
        std::cout << "ExternNamespace::namespace_function() called" << std::endl;
        std::cout << "namespace_var = " << namespace_var << std::endl;
    }
}

// Const external variables
const int extern_const_int = 2024;
const char* const extern_const_string = "Constant External String";

// External linkage for C functions (if needed)
extern "C" {
    int c_style_function(int x, int y) {
        return x * y + 100;
    }
    
    int c_global_var = 999;
}

/*
Note: This file provides the actual definitions for all the external
declarations made in extern_demo.cpp. When both files are compiled
and linked together, the extern declarations in extern_demo.cpp will
resolve to these definitions.

Compilation:
g++ -c extern_vars.cpp -o extern_vars.o
g++ -c extern_demo.cpp -o extern_demo.o  
g++ extern_vars.o extern_demo.o -o extern_demo

Or simply:
g++ extern_vars.cpp extern_demo.cpp -o extern_demo
*/
