// function_templates.cpp - Simple Function Template Examples
// Compile: g++ -std=c++17 -Wall -Wextra function_templates.cpp -o function_templates

#include <iostream>
#include <string>
#include <vector>

// 1. Basic Function Template
template<typename T>
T add(T a, T b) {
    return a + b;
}

// 2. Function Template with Multiple Parameters
template<typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

// 3. Function Template with Non-Type Parameter
template<typename T, int N>
T power(T base) {
    T result = 1;
    for (int i = 0; i < N; ++i) {
        result *= base;
    }
    return result;
}

// 4. Function Template for Finding Maximum
template<typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

// 5. Function Template for Arrays
template<typename T, size_t N>
void printArray(T (&arr)[N]) {
    std::cout << "Array contents: ";
    for (size_t i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// 6. Function Template for Vectors
template<typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "Vector contents: ";
    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// 7. Function Template with Default Parameter
template<typename T = int>
T square(T value) {
    return value * value;
}

// 8. Function Template for Swapping
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 9. Specialized Function Template for Strings
template<>
std::string add<std::string>(std::string a, std::string b) {
    return a + " " + b;  // Add space between strings
}

int main() {
    std::cout << "=== FUNCTION TEMPLATES EXAMPLES ===" << std::endl;
    
    // 1. Basic function template usage
    std::cout << "\n1. Basic Addition Template:" << std::endl;
    std::cout << "add(5, 3) = " << add(5, 3) << std::endl;           // int
    std::cout << "add(2.5, 1.5) = " << add(2.5, 1.5) << std::endl;   // double
    std::cout << "add('A', 1) = " << add('A', 1) << std::endl;        // char (promotes to int)
    
    // Using specialized version for strings
    std::string str1 = "Hello";
    std::string str2 = "World";
    std::cout << "add(\"Hello\", \"World\") = " << add(str1, str2) << std::endl;
    
    // 2. Multiple template parameters
    std::cout << "\n2. Multiple Template Parameters:" << std::endl;
    std::cout << "multiply(5, 2.5) = " << multiply(5, 2.5) << std::endl;      // int * double
    std::cout << "multiply(3.5, 4) = " << multiply(3.5, 4) << std::endl;      // double * int
    
    // 3. Non-type template parameters
    std::cout << "\n3. Non-Type Template Parameters:" << std::endl;
    std::cout << "power<int, 3>(2) = " << power<int, 3>(2) << std::endl;      // 2^3
    std::cout << "power<double, 4>(1.5) = " << power<double, 4>(1.5) << std::endl; // 1.5^4
    
    // 4. Finding maximum
    std::cout << "\n4. Finding Maximum:" << std::endl;
    std::cout << "findMax(10, 20) = " << findMax(10, 20) << std::endl;
    std::cout << "findMax(3.14, 2.71) = " << findMax(3.14, 2.71) << std::endl;
    std::cout << "findMax('X', 'A') = " << findMax('X', 'A') << std::endl;
    
    // 5. Array template
    std::cout << "\n5. Array Template:" << std::endl;
    int intArray[] = {1, 2, 3, 4, 5};
    double doubleArray[] = {1.1, 2.2, 3.3};
    char charArray[] = {'A', 'B', 'C', 'D'};
    
    printArray(intArray);
    printArray(doubleArray);
    printArray(charArray);
    
    // 6. Vector template
    std::cout << "\n6. Vector Template:" << std::endl;
    std::vector<int> intVec = {10, 20, 30, 40};
    std::vector<std::string> stringVec = {"Hello", "World", "C++", "Templates"};
    
    printVector(intVec);
    printVector(stringVec);
    
    // 7. Default template parameter
    std::cout << "\n7. Default Template Parameter:" << std::endl;
    std::cout << "square(5) = " << square(5) << std::endl;           // Uses default int
    std::cout << "square<double>(2.5) = " << square<double>(2.5) << std::endl; // Explicit double
    
    // 8. Swap template
    std::cout << "\n8. Swap Template:" << std::endl;
    int x = 100, y = 200;
    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
    swap(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    
    std::string s1 = "First", s2 = "Second";
    std::cout << "Before swap: s1 = " << s1 << ", s2 = " << s2 << std::endl;
    swap(s1, s2);
    std::cout << "After swap: s1 = " << s1 << ", s2 = " << s2 << std::endl;
    
    // 9. Explicit template instantiation
    std::cout << "\n9. Explicit Template Instantiation:" << std::endl;
    std::cout << "add<float>(1.5f, 2.5f) = " << add<float>(1.5f, 2.5f) << std::endl;
    std::cout << "findMax<long>(1000L, 2000L) = " << findMax<long>(1000L, 2000L) << std::endl;
    
    std::cout << "\n=== FUNCTION TEMPLATE BENEFITS ===" << std::endl;
    std::cout << "✅ Code reusability - write once, use with multiple types" << std::endl;
    std::cout << "✅ Type safety - compile-time type checking" << std::endl;
    std::cout << "✅ Performance - no runtime overhead" << std::endl;
    std::cout << "✅ Automatic type deduction in most cases" << std::endl;
    std::cout << "✅ Compile-time polymorphism" << std::endl;
    
    std::cout << "\n=== KEY CONCEPTS ===" << std::endl;
    std::cout << "• Template instantiation happens at compile-time" << std::endl;
    std::cout << "• Each type used creates a separate function instance" << std::endl;
    std::cout << "• Type deduction works from function arguments" << std::endl;
    std::cout << "• Can be specialized for specific types" << std::endl;
    std::cout << "• Can have multiple template parameters" << std::endl;
    std::cout << "• Non-type parameters are also supported" << std::endl;
    
    return 0;
}

/*
Function Template Key Points:

1. Syntax:
   template<typename T>
   T functionName(T parameter) { ... }

2. Type Deduction:
   - Compiler deduces type from arguments
   - Can be explicitly specified: func<int>(...)

3. Instantiation:
   - Happens at compile-time
   - Separate function created for each type used

4. Specialization:
   - Can provide specific implementation for certain types
   - template<> ReturnType func<SpecificType>(...) { ... }

5. Multiple Parameters:
   - template<typename T, typename U>
   - template<typename T, int N>

6. Best Practices:
   - Use meaningful template parameter names
   - Provide clear documentation
   - Consider constraints for template parameters
   - Use auto return type when appropriate
*/
