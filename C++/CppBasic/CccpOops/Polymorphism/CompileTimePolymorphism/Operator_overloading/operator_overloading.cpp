// operator_overloading.cpp - Demonstrates operator overloading in C++
// Compile: g++ -std=c++17 -Wall -Wextra operator_overloading.cpp -o operator_overloading

#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

// 1. Basic Arithmetic Operator Overloading
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    
    // Binary arithmetic operators (member functions)
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    // Unary operators
    Complex operator-() const {
        return Complex(-real, -imag);
    }
    
    Complex operator+() const {
        return *this;
    }
    
    // Compound assignment operators
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }
    
    // Increment/Decrement operators
    Complex& operator++() {  // Pre-increment
        ++real;
        return *this;
    }
    
    Complex operator++(int) {  // Post-increment
        Complex temp = *this;
        ++real;
        return temp;
    }
    
    // Comparison operators
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // Assignment operator
    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }
    
    // Subscript operator (for accessing real/imag by index)
    double& operator[](int index) {
        return (index == 0) ? real : imag;
    }
    
    const double& operator[](int index) const {
        return (index == 0) ? real : imag;
    }
    
    // Function call operator
    double operator()() const {
        return sqrt(real * real + imag * imag); // Magnitude
    }
    
    // Type conversion operators
    operator double() const {
        return real; // Convert to real part
    }
    
    operator bool() const {
        return (real != 0.0 || imag != 0.0);
    }
    
    // Friend functions for stream operators
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend std::istream& operator>>(std::istream& is, Complex& c);
    
    // Friend function for symmetric operations
    friend Complex operator*(double scalar, const Complex& c);
    
    void display() const {
        std::cout << real;
        if (imag >= 0) std::cout << " + " << imag << "i";
        else std::cout << " - " << -imag << "i";
    }
};

// Stream operators (must be free functions)
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) os << " + " << c.imag << "i";
    else os << " - " << -c.imag << "i";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c) {
    is >> c.real >> c.imag;
    return is;
}

// Symmetric scalar multiplication
Complex operator*(double scalar, const Complex& c) {
    return Complex(scalar * c.real, scalar * c.imag);
}

// 2. Advanced Container Class with Operator Overloading
template<typename T>
class Vector {
private:
    std::vector<T> data;
    
public:
    // Constructor with initializer list
    Vector(std::initializer_list<T> init) : data(init) {}
    
    Vector() = default;
    
    explicit Vector(size_t size, const T& value = T{}) : data(size, value) {}
    
    // Subscript operators
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
    
    // Addition operator
    Vector operator+(const Vector& other) const {
        Vector result;
        size_t minSize = std::min(data.size(), other.data.size());
        result.data.reserve(minSize);
        
        for (size_t i = 0; i < minSize; ++i) {
            result.data.push_back(data[i] + other.data[i]);
        }
        return result;
    }
    
    // Scalar multiplication
    Vector operator*(const T& scalar) const {
        Vector result;
        result.data.reserve(data.size());
        
        for (const auto& element : data) {
            result.data.push_back(element * scalar);
        }
        return result;
    }
    
    // Compound assignment
    Vector& operator+=(const Vector& other) {
        size_t minSize = std::min(data.size(), other.data.size());
        for (size_t i = 0; i < minSize; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }
    
    // Comparison operators
    bool operator==(const Vector& other) const {
        return data == other.data;
    }
    
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }
    
    // Function call operator for element access with bounds checking
    T& operator()(size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // Size and capacity
    size_t size() const { return data.size(); }
    
    // Iterator support
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
    
    // Stream output
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
        os << "[";
        for (size_t i = 0; i < v.data.size(); ++i) {
            os << v.data[i];
            if (i < v.data.size() - 1) os << ", ";
        }
        os << "]";
        return os;
    }
};

// Free function for symmetric scalar multiplication
template<typename T>
Vector<T> operator*(const T& scalar, const Vector<T>& vec) {
    return vec * scalar;
}

// 3. Smart Pointer Class with Operator Overloading
template<typename T>
class SmartPtr {
private:
    T* ptr;
    
public:
    explicit SmartPtr(T* p = nullptr) : ptr(p) {}
    
    ~SmartPtr() {
        delete ptr;
    }
    
    // Copy constructor and assignment (implementing deep copy)
    SmartPtr(const SmartPtr& other) : ptr(nullptr) {
        if (other.ptr) {
            ptr = new T(*other.ptr);
        }
    }
    
    SmartPtr& operator=(const SmartPtr& other) {
        if (this != &other) {
            delete ptr;
            ptr = nullptr;
            if (other.ptr) {
                ptr = new T(*other.ptr);
            }
        }
        return *this;
    }
    
    // Move constructor and assignment
    SmartPtr(SmartPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    SmartPtr& operator=(SmartPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    // Dereference operators
    T& operator*() const {
        return *ptr;
    }
    
    T* operator->() const {
        return ptr;
    }
    
    // Boolean conversion
    operator bool() const {
        return ptr != nullptr;
    }
    
    // Equality operators
    bool operator==(const SmartPtr& other) const {
        return ptr == other.ptr;
    }
    
    bool operator!=(const SmartPtr& other) const {
        return !(*this == other);
    }
    
    // Get raw pointer
    T* get() const {
        return ptr;
    }
    
    // Release ownership
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    // Reset with new pointer
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

// 4. String Class with Rich Operator Overloading
class String {
private:
    char* data;
    size_t length;
    
    void allocateAndCopy(const char* str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
    
public:
    // Constructors
    String() : data(nullptr), length(0) {
        data = new char[1];
        data[0] = '\0';
    }
    
    String(const char* str) {
        allocateAndCopy(str ? str : "");
    }
    
    String(const String& other) {
        allocateAndCopy(other.data);
    }
    
    // Destructor
    ~String() {
        delete[] data;
    }
    
    // Assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            allocateAndCopy(other.data);
        }
        return *this;
    }
    
    String& operator=(const char* str) {
        delete[] data;
        allocateAndCopy(str ? str : "");
        return *this;
    }
    
    // Concatenation operators
    String operator+(const String& other) const {
        String result;
        delete[] result.data;
        result.length = length + other.length;
        result.data = new char[result.length + 1];
        strcpy(result.data, data);
        strcat(result.data, other.data);
        return result;
    }
    
    String& operator+=(const String& other) {
        *this = *this + other;
        return *this;
    }
    
    // Subscript operator
    char& operator[](size_t index) {
        return data[index];
    }
    
    const char& operator[](size_t index) const {
        return data[index];
    }
    
    // Comparison operators
    bool operator==(const String& other) const {
        return strcmp(data, other.data) == 0;
    }
    
    bool operator!=(const String& other) const {
        return !(*this == other);
    }
    
    bool operator<(const String& other) const {
        return strcmp(data, other.data) < 0;
    }
    
    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data;
        return os;
    }
    
    // Type conversion
    operator const char*() const {
        return data;
    }
    
    size_t size() const { return length; }
    const char* c_str() const { return data; }
};

// Demonstration functions
void demonstrateComplexOperators() {
    std::cout << "\n=== COMPLEX NUMBER OPERATORS ===" << std::endl;
    
    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    
    Complex c3 = c1 + c2;
    std::cout << "c1 + c2 = " << c3 << std::endl;
    
    Complex c4 = c1 * c2;
    std::cout << "c1 * c2 = " << c4 << std::endl;
    
    Complex c5 = -c1;
    std::cout << "-c1 = " << c5 << std::endl;
    
    std::cout << "c1++ = " << c1++ << std::endl;
    std::cout << "c1 after increment = " << c1 << std::endl;
    
    std::cout << "c1[0] (real) = " << c1[0] << std::endl;
    std::cout << "c1[1] (imag) = " << c1[1] << std::endl;
    
    std::cout << "Magnitude of c1: " << c1() << std::endl;
    
    std::cout << "c1 as double: " << static_cast<double>(c1) << std::endl;
    std::cout << "c1 as bool: " << (c1 ? "true" : "false") << std::endl;
    
    Complex c6 = 2.5 * c2;  // Symmetric scalar multiplication
    std::cout << "2.5 * c2 = " << c6 << std::endl;
}

void demonstrateVectorOperators() {
    std::cout << "\n=== VECTOR OPERATORS ===" << std::endl;
    
    Vector<int> v1{1, 2, 3, 4, 5};
    Vector<int> v2{10, 20, 30, 40, 50};
    
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    
    Vector<int> v3 = v1 + v2;
    std::cout << "v1 + v2 = " << v3 << std::endl;
    
    Vector<int> v4 = v1 * 3;
    std::cout << "v1 * 3 = " << v4 << std::endl;
    
    Vector<int> v5 = 2 * v1;
    std::cout << "2 * v1 = " << v5 << std::endl;
    
    v1 += v2;
    std::cout << "v1 after += v2: " << v1 << std::endl;
    
    std::cout << "v1[2] = " << v1[2] << std::endl;
    
    try {
        std::cout << "v1(100) = " << v1(100) << std::endl;  // Will throw
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

void demonstrateSmartPtrOperators() {
    std::cout << "\n=== SMART POINTER OPERATORS ===" << std::endl;
    
    SmartPtr<int> ptr1(new int(42));
    SmartPtr<int> ptr2(new int(84));
    
    std::cout << "*ptr1 = " << *ptr1 << std::endl;
    std::cout << "*ptr2 = " << *ptr2 << std::endl;
    
    *ptr1 = 100;
    std::cout << "After *ptr1 = 100: " << *ptr1 << std::endl;
    
    SmartPtr<int> ptr3 = ptr1;  // Copy constructor
    std::cout << "*ptr3 (copy of ptr1) = " << *ptr3 << std::endl;
    
    if (ptr1) {
        std::cout << "ptr1 is valid" << std::endl;
    }
    
    SmartPtr<int> ptr4(nullptr);
    if (!ptr4) {
        std::cout << "ptr4 is null" << std::endl;
    }
    
    std::cout << "ptr1 == ptr3: " << (ptr1 == ptr3 ? "true" : "false") << std::endl;
}

void demonstrateStringOperators() {
    std::cout << "\n=== STRING OPERATORS ===" << std::endl;
    
    String s1("Hello");
    String s2(" World");
    String s3("!");
    
    std::cout << "s1 = " << s1 << std::endl;
    std::cout << "s2 = " << s2 << std::endl;
    std::cout << "s3 = " << s3 << std::endl;
    
    String s4 = s1 + s2 + s3;
    std::cout << "s1 + s2 + s3 = " << s4 << std::endl;
    
    s1 += s2;
    std::cout << "s1 after += s2: " << s1 << std::endl;
    
    std::cout << "s4[6] = '" << s4[6] << "'" << std::endl;
    
    String s5("Hello");
    std::cout << "s1 == s5: " << (s1 == s5 ? "true" : "false") << std::endl;
    
    String s6("Apple");
    String s7("Banana");
    std::cout << "s6 < s7: " << (s6 < s7 ? "true" : "false") << std::endl;
    
    const char* cstr = s4;  // Implicit conversion
    std::cout << "s4 as C-string: " << cstr << std::endl;
}

int main() {
    std::cout << "=== COMPILE-TIME POLYMORPHISM: OPERATOR OVERLOADING ===" << std::endl;
    std::cout << "Operator overloading allows custom behavior for operators" << std::endl;
    std::cout << "on user-defined types. Resolution happens at compile time." << std::endl;
    
    demonstrateComplexOperators();
    demonstrateVectorOperators();
    demonstrateSmartPtrOperators();
    demonstrateStringOperators();
    
    std::cout << "\n=== KEY CONCEPTS ===" << std::endl;
    std::cout << "1. Member vs Free Function Operators" << std::endl;
    std::cout << "2. Symmetric Operations (e.g., scalar * vector)" << std::endl;
    std::cout << "3. Return Types Matter for Chaining" << std::endl;
    std::cout << "4. Some Operators Cannot Be Overloaded (::, ?:, ., sizeof)" << std::endl;
    std::cout << "5. Assignment Operators Should Return Reference to *this" << std::endl;
    std::cout << "6. Stream Operators Must Be Free Functions" << std::endl;
    
    return 0;
}

/* Expected Output:
=== COMPILE-TIME POLYMORPHISM: OPERATOR OVERLOADING ===
Operator overloading allows custom behavior for operators
on user-defined types. Resolution happens at compile time.

=== COMPLEX NUMBER OPERATORS ===
c1 = 3 + 4i
c2 = 1 + 2i
c1 + c2 = 4 + 6i
c1 * c2 = -5 + 10i
-c1 = -3 - 4i
c1++ = 3 + 4i
c1 after increment = 4 + 4i
c1[0] (real) = 4
c1[1] (imag) = 4
Magnitude of c1: 5.65685
c1 as double: 4
c1 as bool: true
2.5 * c2 = 2.5 + 5i

=== VECTOR OPERATORS ===
v1 = [1, 2, 3, 4, 5]
v2 = [10, 20, 30, 40, 50]
v1 + v2 = [11, 22, 33, 44, 55]
v1 * 3 = [3, 6, 9, 12, 15]
2 * v1 = [2, 4, 6, 8, 10]
v1 after += v2: [11, 22, 33, 44, 55]
v1[2] = 33
Exception: Index out of range

=== SMART POINTER OPERATORS ===
*ptr1 = 42
*ptr2 = 84
After *ptr1 = 100: 100
*ptr3 (copy of ptr1) = 100
ptr1 is valid
ptr4 is null
ptr1 == ptr3: false

=== STRING OPERATORS ===
s1 = Hello
s2 =  World
s3 = !
s1 + s2 + s3 = Hello World!
s1 after += s2: Hello World
s4[6] = 'W'
s1 == s5: false
s6 < s7: true
s4 as C-string: Hello World!

=== KEY CONCEPTS ===
1. Member vs Free Function Operators
2. Symmetric Operations (e.g., scalar * vector)
3. Return Types Matter for Chaining
4. Some Operators Cannot Be Overloaded (::, ?:, ., sizeof)
5. Assignment Operators Should Return Reference to *this
6. Stream Operators Must Be Free Functions
*/
