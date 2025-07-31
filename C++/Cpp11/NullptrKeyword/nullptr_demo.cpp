// C++11 nullptr - Type-Safe Null Pointer
// Compile: g++ -std=c++11 -o nullptr_demo nullptr_demo.cpp
// Run: ./nullptr_demo

#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>

// Function overloads to demonstrate nullptr vs NULL vs 0
void process(int value) {
    std::cout << "process(int): " << value << std::endl;
}

void process(char* ptr) {
    if (ptr) {
        std::cout << "process(char*): " << ptr << std::endl;
    } else {
        std::cout << "process(char*): null pointer" << std::endl;
    }
}

void process(void* ptr) {
    if (ptr) {
        std::cout << "process(void*): valid pointer" << std::endl;
    } else {
        std::cout << "process(void*): null pointer" << std::endl;
    }
}

// Template function to demonstrate nullptr with templates
template<typename T>
void processPointer(T* ptr) {
    if (ptr) {
        std::cout << "processPointer: valid pointer of type " << typeid(T).name() << std::endl;
        std::cout << "Value: " << *ptr << std::endl;
    } else {
        std::cout << "processPointer: null pointer of type " << typeid(T).name() << std::endl;
    }
}

// Class to demonstrate nullptr with member functions
class SafePointerHandler {
private:
    int* data_;
    
public:
    // Constructor
    SafePointerHandler(int* ptr = nullptr) : data_(ptr) {
        if (data_) {
            std::cout << "SafePointerHandler created with value: " << *data_ << std::endl;
        } else {
            std::cout << "SafePointerHandler created with nullptr" << std::endl;
        }
    }
    
    // Check if pointer is valid
    bool isValid() const {
        return data_ != nullptr;  // Clear intent
    }
    
    // Safe access
    int getValue() const {
        if (data_ != nullptr) {
            return *data_;
        }
        throw std::runtime_error("Attempting to access nullptr");
    }
    
    // Reset pointer
    void reset(int* new_ptr = nullptr) {
        data_ = new_ptr;
        std::cout << "Pointer reset to " << (data_ ? "valid value" : "nullptr") << std::endl;
    }
    
    // Comparison with nullptr
    bool operator==(std::nullptr_t) const {
        return data_ == nullptr;
    }
    
    bool operator!=(std::nullptr_t) const {
        return data_ != nullptr;
    }
};

// Function that returns nullable pointer
int* findValue(const std::vector<int>& vec, int target) {
    for (auto& val : vec) {
        if (val == target) {
            return const_cast<int*>(&val);  // In real code, better to return iterator
        }
    }
    return nullptr;  // Clear indication of "not found"
}

// Smart pointer demonstration
std::unique_ptr<int> createOptionalValue(bool create) {
    if (create) {
        return std::make_unique<int>(42);
    }
    return nullptr;  // Return empty unique_ptr
}

int main() {
    std::cout << "=== C++11 NULLPTR DEMO ===" << std::endl;
    
    // 1. Basic nullptr usage
    std::cout << "\n1. Basic nullptr Usage:" << std::endl;
    
    int* ptr1 = nullptr;   // C++11 way
    char* ptr2 = nullptr;
    void* ptr3 = nullptr;
    
    std::cout << "ptr1 == nullptr: " << (ptr1 == nullptr) << std::endl;
    std::cout << "ptr2 == nullptr: " << (ptr2 == nullptr) << std::endl;
    std::cout << "ptr3 == nullptr: " << (ptr3 == nullptr) << std::endl;
    
    // Type safety demonstration
    std::cout << "\n2. Type Safety Comparison:" << std::endl;
    
    // C++98/03 problems with NULL and 0
    #define NULL 0  // Traditional definition
    
    std::cout << "Calling with literal 0:" << std::endl;
    process(0);  // Calls process(int) - ambiguous intent!
    
    std::cout << "\nCalling with NULL:" << std::endl;
    process(NULL);  // Calls process(int) - still ambiguous!
    
    std::cout << "\nCalling with nullptr:" << std::endl;
    process(nullptr);  // Calls process(char*) - clear intent!
    
    // 3. nullptr type properties
    std::cout << "\n3. nullptr Type Properties:" << std::endl;
    
    // nullptr has type std::nullptr_t
    std::nullptr_t null_value = nullptr;
    std::cout << "sizeof(nullptr_t): " << sizeof(std::nullptr_t) << " bytes" << std::endl;
    std::cout << "sizeof(void*): " << sizeof(void*) << " bytes" << std::endl;
    
    // nullptr can be implicitly converted to any pointer type
    int* int_ptr = nullptr;
    double* double_ptr = nullptr;
    char* char_ptr = nullptr;
    
    std::cout << "All pointers set to nullptr successfully" << std::endl;
    
    // nullptr cannot be converted to integral types (unlike NULL)
    // int value = nullptr;  // Compilation error!
    
    // 4. Template usage with nullptr
    std::cout << "\n4. Template Usage with nullptr:" << std::endl;
    
    int value = 100;
    double pi = 3.14159;
    
    processPointer(&value);
    processPointer(&pi);
    processPointer<int>(nullptr);
    processPointer<double>(nullptr);
    
    // 5. Class usage with nullptr
    std::cout << "\n5. Class Usage with nullptr:" << std::endl;
    
    int test_value = 42;
    SafePointerHandler handler1(&test_value);
    SafePointerHandler handler2(nullptr);
    SafePointerHandler handler3;  // Uses default parameter nullptr
    
    std::cout << "handler1.isValid(): " << handler1.isValid() << std::endl;
    std::cout << "handler2.isValid(): " << handler2.isValid() << std::endl;
    std::cout << "handler3.isValid(): " << handler3.isValid() << std::endl;
    
    // Using comparison operators
    std::cout << "handler1 == nullptr: " << (handler1 == nullptr) << std::endl;
    std::cout << "handler2 == nullptr: " << (handler2 == nullptr) << std::endl;
    std::cout << "handler3 != nullptr: " << (handler3 != nullptr) << std::endl;
    
    // 6. Function return values
    std::cout << "\n6. Function Return Values:" << std::endl;
    
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    
    int* found = findValue(numbers, 30);
    if (found != nullptr) {
        std::cout << "Found value: " << *found << std::endl;
    } else {
        std::cout << "Value not found" << std::endl;
    }
    
    int* not_found = findValue(numbers, 99);
    if (not_found != nullptr) {
        std::cout << "Found value: " << *not_found << std::endl;
    } else {
        std::cout << "Value 99 not found (returned nullptr)" << std::endl;
    }
    
    // 7. Smart pointers with nullptr
    std::cout << "\n7. Smart Pointers with nullptr:" << std::endl;
    
    auto smart_ptr1 = createOptionalValue(true);
    auto smart_ptr2 = createOptionalValue(false);
    
    std::cout << "smart_ptr1: " << (smart_ptr1 ? "has value " + std::to_string(*smart_ptr1) : "is nullptr") << std::endl;
    std::cout << "smart_ptr2: " << (smart_ptr2 ? "has value " + std::to_string(*smart_ptr2) : "is nullptr") << std::endl;
    
    // Reset smart pointer to nullptr
    smart_ptr1.reset();  // Equivalent to smart_ptr1 = nullptr;
    std::cout << "After reset, smart_ptr1: " << (smart_ptr1 ? "has value" : "is nullptr") << std::endl;
    
    // Direct assignment to nullptr
    smart_ptr1 = nullptr;
    std::cout << "After nullptr assignment, smart_ptr1: " << (smart_ptr1 ? "has value" : "is nullptr") << std::endl;
    
    // 8. Array pointers with nullptr
    std::cout << "\n8. Array Pointers with nullptr:" << std::endl;
    
    int* array_ptr = new int[5]{1, 2, 3, 4, 5};
    std::cout << "Array pointer created, first element: " << array_ptr[0] << std::endl;
    
    delete[] array_ptr;
    array_ptr = nullptr;  // Good practice: nullify after deletion
    
    if (array_ptr == nullptr) {
        std::cout << "Array pointer safely set to nullptr after deletion" << std::endl;
    }
    
    // 9. nullptr in conditional statements
    std::cout << "\n9. Conditional Statements with nullptr:" << std::endl;
    
    int* conditional_ptr = nullptr;
    
    // Traditional ways to check for null
    if (conditional_ptr == nullptr) {
        std::cout << "Pointer is null (explicit comparison)" << std::endl;
    }
    
    if (!conditional_ptr) {
        std::cout << "Pointer is null (implicit conversion to bool)" << std::endl;
    }
    
    conditional_ptr = &value;
    if (conditional_ptr != nullptr) {
        std::cout << "Pointer is valid, value: " << *conditional_ptr << std::endl;
    }
    
    // 10. Comparison with C-style null checks
    std::cout << "\n10. C-style vs C++11 Null Checks:" << std::endl;
    
    char* c_style_ptr = nullptr;
    
    // C-style (still works but less clear)
    if (c_style_ptr == 0) {
        std::cout << "C-style: pointer is null (using 0)" << std::endl;
    }
    
    // Better C++11 style
    if (c_style_ptr == nullptr) {
        std::cout << "C++11 style: pointer is null (using nullptr)" << std::endl;
    }
    
    // Modern C++ style (implicit conversion)
    if (!c_style_ptr) {
        std::cout << "Modern style: pointer is null (implicit bool conversion)" << std::endl;
    }
    
    // 11. nullptr with function pointers
    std::cout << "\n11. Function Pointers with nullptr:" << std::endl;
    
    void (*func_ptr)() = nullptr;
    
    if (func_ptr == nullptr) {
        std::cout << "Function pointer is null" << std::endl;
    }
    
    // Assign a lambda (C++11 feature)
    func_ptr = []() { std::cout << "Lambda function called!" << std::endl; };
    
    if (func_ptr != nullptr) {
        std::cout << "Function pointer is valid, calling function: ";
        func_ptr();
    }
    
    // 12. Member pointer with nullptr
    std::cout << "\n12. Member Pointers with nullptr:" << std::endl;
    
    class TestClass {
    public:
        int member = 42;
        void method() { std::cout << "Method called!" << std::endl; }
    };
    
    int TestClass::* member_ptr = nullptr;
    void (TestClass::* method_ptr)() = nullptr;
    
    std::cout << "Member pointer is null: " << (member_ptr == nullptr) << std::endl;
    std::cout << "Method pointer is null: " << (method_ptr == nullptr) << std::endl;
    
    // Assign to actual members
    member_ptr = &TestClass::member;
    method_ptr = &TestClass::method;
    
    TestClass obj;
    if (member_ptr != nullptr) {
        std::cout << "Member value through pointer: " << obj.*member_ptr << std::endl;
    }
    
    if (method_ptr != nullptr) {
        std::cout << "Calling method through pointer: ";
        (obj.*method_ptr)();
    }
    
    std::cout << "\n=== NULLPTR BENEFITS ===" << std::endl;
    std::cout << "✅ Type-safe null pointer constant" << std::endl;
    std::cout << "✅ Eliminates ambiguity in overload resolution" << std::endl;
    std::cout << "✅ Works correctly with templates" << std::endl;
    std::cout << "✅ Cannot be accidentally converted to integer types" << std::endl;
    std::cout << "✅ Clear intent in code (null pointer, not zero)" << std::endl;
    std::cout << "✅ Consistent behavior across all pointer types" << std::endl;
    std::cout << "⚠️  Always use nullptr instead of NULL or 0 for pointers" << std::endl;
    std::cout << "⚠️  Set pointers to nullptr after deletion" << std::endl;
    std::cout << "⚠️  Check for nullptr before dereferencing" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -o nullptr_demo nullptr_demo.cpp
./nullptr_demo

nullptr Key Features:
1. Type: std::nullptr_t (special type)
2. Convertible to any pointer type
3. NOT convertible to integral types
4. Eliminates overload resolution ambiguity
5. Template-friendly

Benefits over NULL/0:
- Type safety: Cannot be confused with integer 0
- Template compatibility: Works correctly in template deduction
- Overload resolution: Clear distinction between null pointer and integer
- Intent clarity: Explicitly indicates null pointer, not zero value

Best Practices:
- Always use nullptr for null pointers (never NULL or 0)
- Set pointers to nullptr after deletion
- Compare explicitly with nullptr for clarity
- Use in function default parameters for optional pointers
*/
