// C++11 static_assert - Compile-Time Assertions
// Compile: g++ -std=c++11 -o static_assert_demo static_assert_demo.cpp
// Run: ./static_assert_demo

#include <iostream>
#include <type_traits>
#include <limits>
#include <cstdint>

// 1. Basic static_assert usage
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
static_assert(sizeof(char) == 1, "char must be exactly 1 byte");
static_assert(sizeof(void*) >= sizeof(int), "pointer must be at least as large as int");

// 2. Template with static_assert
template<typename T>
class SafeArray {
private:
    static_assert(std::is_arithmetic<T>::value, "SafeArray only supports arithmetic types");
    static_assert(!std::is_same<T, bool>::value, "SafeArray does not support bool type");
    
    T* data_;
    size_t size_;
    
public:
    SafeArray(size_t size) : size_(size) {
        static_assert(sizeof(T) > 0, "Type T must have non-zero size");
        data_ = new T[size_];
    }
    
    ~SafeArray() { delete[] data_; }
    
    T& operator[](size_t index) {
        // Runtime check (static_assert is compile-time only)
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }
    
    size_t size() const { return size_; }
};

// 3. Constexpr function with static_assert
constexpr int factorial(int n) {
    static_assert(true, "This static_assert always passes");  // Just for demo
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// 4. Class template with multiple static_asserts
template<typename T, size_t N>
class FixedBuffer {
    static_assert(N > 0, "Buffer size must be greater than zero");
    static_assert(N <= 1024, "Buffer size too large (max 1024)");
    static_assert(std::is_pod<T>::value, "Type must be POD (Plain Old Data)");
    static_assert(sizeof(T) * N <= 4096, "Total buffer size exceeds 4KB limit");
    
private:
    T data_[N];
    
public:
    constexpr size_t size() const { return N; }
    constexpr size_t byte_size() const { return N * sizeof(T); }
    
    T& at(size_t index) {
        if (index >= N) throw std::out_of_range("Index out of bounds");
        return data_[index];
    }
    
    const T& at(size_t index) const {
        if (index >= N) throw std::out_of_range("Index out of bounds");
        return data_[index];
    }
    
    T* begin() { return data_; }
    T* end() { return data_ + N; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + N; }
};

// 5. Platform-specific static_asserts
#if defined(__LP64__) || defined(_WIN64)
    static_assert(sizeof(void*) == 8, "Expected 64-bit pointers");
#else
    static_assert(sizeof(void*) == 4, "Expected 32-bit pointers");
#endif

// Endianness check (simplified)
static_assert(std::numeric_limits<unsigned char>::digits == 8, 
              "CHAR_BIT must be 8 for this code");

// 6. Type trait static_asserts
template<typename T>
class NumericVector {
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
    static_assert(std::is_signed<T>::value, "T must be a signed type");
    static_assert(!std::is_floating_point<T>::value, "T must not be floating point");
    
    // This means T must be a signed integer type
    
private:
    T* data_;
    size_t size_;
    size_t capacity_;
    
public:
    NumericVector() : data_(nullptr), size_(0), capacity_(0) {}
    
    ~NumericVector() { delete[] data_; }
    
    void push_back(T value) {
        if (size_ >= capacity_) {
            capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
            T* new_data = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
        }
        data_[size_++] = value;
    }
    
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
    
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
};

// 7. Function template with static_assert
template<typename From, typename To>
To safe_cast(From value) {
    static_assert(std::is_arithmetic<From>::value, "From type must be arithmetic");
    static_assert(std::is_arithmetic<To>::value, "To type must be arithmetic");
    static_assert(sizeof(To) >= sizeof(From), "Target type must be at least as large as source type");
    
    return static_cast<To>(value);
}

// 8. Specialized static_asserts for different scenarios
namespace compile_time_checks {
    // Mathematical constants verification
    static_assert(3.14 < 3.15, "Pi approximation check");
    static_assert(2 + 2 == 4, "Basic arithmetic check");
    
    // Size assumptions
    static_assert(sizeof(short) <= sizeof(int), "short must not be larger than int");
    static_assert(sizeof(int) <= sizeof(long), "int must not be larger than long");
    static_assert(sizeof(float) <= sizeof(double), "float must not be larger than double");
    
    // Character encoding assumptions
    static_assert('A' < 'Z', "Alphabetic ordering assumption");
    static_assert('0' < '9', "Numeric character ordering assumption");
    
    // Bit manipulation assumptions
    constexpr unsigned int test_bits = 0xFFFFFFFF;
    static_assert(test_bits != 0, "Unsigned int must support at least 32 bits");
}

// 9. Configuration validation
namespace config {
    constexpr int MAX_USERS = 1000;
    constexpr int MAX_CONNECTIONS = 100;
    constexpr int BUFFER_SIZE = 4096;
    
    // Validate configuration at compile time
    static_assert(MAX_USERS > 0, "MAX_USERS must be positive");
    static_assert(MAX_CONNECTIONS <= MAX_USERS, "Cannot have more connections than users");
    static_assert(BUFFER_SIZE >= 1024, "BUFFER_SIZE too small (minimum 1024)");
    static_assert((BUFFER_SIZE & (BUFFER_SIZE - 1)) == 0, "BUFFER_SIZE must be power of 2");
}

// 10. Version compatibility checks
#if __cplusplus >= 201103L
    static_assert(__cplusplus >= 201103L, "C++11 or later required");
#endif

// 11. Memory alignment checks
template<typename T>
struct AlignedType {
    static_assert(sizeof(T) % alignof(T) == 0, "Size must be multiple of alignment");
    static_assert(alignof(T) <= 64, "Alignment too large (max 64 bytes)");
    
    alignas(T) char storage[sizeof(T)];
    
    T* get() { return reinterpret_cast<T*>(storage); }
    const T* get() const { return reinterpret_cast<const T*>(storage); }
};

int main() {
    std::cout << "=== C++11 STATIC_ASSERT DEMO ===" << std::endl;
    
    // 1. Basic platform information
    std::cout << "\n1. Platform Information (verified by static_assert):" << std::endl;
    std::cout << "sizeof(char): " << sizeof(char) << " bytes" << std::endl;
    std::cout << "sizeof(int): " << sizeof(int) << " bytes" << std::endl;
    std::cout << "sizeof(void*): " << sizeof(void*) << " bytes" << std::endl;
    std::cout << "sizeof(long): " << sizeof(long) << " bytes" << std::endl;
    
    // 2. Template class with static_assert (arithmetic types)
    std::cout << "\n2. SafeArray with Arithmetic Types:" << std::endl;
    
    SafeArray<int> int_array(5);
    SafeArray<double> double_array(3);
    // SafeArray<std::string> string_array(2);  // Compile error: not arithmetic!
    // SafeArray<bool> bool_array(4);           // Compile error: bool not supported!
    
    int_array[0] = 42;
    int_array[1] = 100;
    double_array[0] = 3.14159;
    
    std::cout << "int_array[0]: " << int_array[0] << std::endl;
    std::cout << "int_array[1]: " << int_array[1] << std::endl;
    std::cout << "double_array[0]: " << double_array[0] << std::endl;
    
    // 3. FixedBuffer with compile-time size checks
    std::cout << "\n3. FixedBuffer with Static Assertions:" << std::endl;
    
    FixedBuffer<int, 10> buffer1;  // OK: size 10, int is POD
    FixedBuffer<char, 100> buffer2; // OK: size 100, char is POD
    // FixedBuffer<int, 0> buffer3;    // Compile error: size must be > 0
    // FixedBuffer<int, 2000> buffer4; // Compile error: size too large
    
    std::cout << "buffer1 size: " << buffer1.size() << ", byte size: " << buffer1.byte_size() << std::endl;
    std::cout << "buffer2 size: " << buffer2.size() << ", byte size: " << buffer2.byte_size() << std::endl;
    
    // Fill and display buffer
    for (size_t i = 0; i < buffer1.size(); ++i) {
        buffer1.at(i) = static_cast<int>(i * i);
    }
    
    std::cout << "buffer1 contents: ";
    for (size_t i = 0; i < buffer1.size(); ++i) {
        std::cout << buffer1.at(i) << " ";
    }
    std::cout << std::endl;
    
    // 4. NumericVector (signed integer types only)
    std::cout << "\n4. NumericVector (Signed Integer Types Only):" << std::endl;
    
    NumericVector<int> signed_ints;
    NumericVector<long> signed_longs;
    // NumericVector<unsigned int> unsigned_ints;  // Compile error: not signed!
    // NumericVector<double> doubles;              // Compile error: floating point!
    
    signed_ints.push_back(-5);
    signed_ints.push_back(10);
    signed_ints.push_back(-15);
    
    std::cout << "signed_ints contents: ";
    for (size_t i = 0; i < signed_ints.size(); ++i) {
        std::cout << signed_ints[i] << " ";
    }
    std::cout << std::endl;
    
    // 5. Safe casting with static_assert
    std::cout << "\n5. Safe Casting with Static Assertions:" << std::endl;
    
    short s = 100;
    int i = safe_cast<short, int>(s);        // OK: int >= short
    long l = safe_cast<int, long>(i);        // OK: long >= int
    // short s2 = safe_cast<int, short>(i);   // Compile error: short < int
    
    std::cout << "short to int: " << s << " -> " << i << std::endl;
    std::cout << "int to long: " << i << " -> " << l << std::endl;
    
    // 6. Configuration validation results
    std::cout << "\n6. Configuration Validation (compile-time):" << std::endl;
    std::cout << "MAX_USERS: " << config::MAX_USERS << std::endl;
    std::cout << "MAX_CONNECTIONS: " << config::MAX_CONNECTIONS << std::endl;
    std::cout << "BUFFER_SIZE: " << config::BUFFER_SIZE << std::endl;
    std::cout << "All configuration values validated at compile time!" << std::endl;
    
    // 7. Type trait demonstrations
    std::cout << "\n7. Type Trait Demonstrations:" << std::endl;
    
    std::cout << "std::is_arithmetic<int>: " << std::is_arithmetic<int>::value << std::endl;
    std::cout << "std::is_signed<int>: " << std::is_signed<int>::value << std::endl;
    std::cout << "std::is_floating_point<double>: " << std::is_floating_point<double>::value << std::endl;
    std::cout << "std::is_pod<int>: " << std::is_pod<int>::value << std::endl;
    
    // 8. Alignment information
    std::cout << "\n8. Alignment Information:" << std::endl;
    
    AlignedType<int> aligned_int;
    AlignedType<double> aligned_double;
    
    std::cout << "alignof(int): " << alignof(int) << std::endl;
    std::cout << "alignof(double): " << alignof(double) << std::endl;
    std::cout << "sizeof(AlignedType<int>): " << sizeof(AlignedType<int>) << std::endl;
    std::cout << "sizeof(AlignedType<double>): " << sizeof(AlignedType<double>) << std::endl;
    
    // 9. Compile-time factorial with static_assert
    std::cout << "\n9. Compile-time Factorial:" << std::endl;
    
    constexpr int fact5 = factorial(5);
    constexpr int fact6 = factorial(6);
    
    std::cout << "factorial(5): " << fact5 << std::endl;
    std::cout << "factorial(6): " << fact6 << std::endl;
    
    // 10. Demonstrating different static_assert scenarios
    std::cout << "\n10. Static Assert Scenarios:" << std::endl;
    
    // These are checked at compile time, not runtime
    std::cout << "✅ All basic type size assertions passed" << std::endl;
    std::cout << "✅ All platform-specific assertions passed" << std::endl;
    std::cout << "✅ All template parameter validations passed" << std::endl;
    std::cout << "✅ All configuration validations passed" << std::endl;
    std::cout << "✅ All mathematical constant checks passed" << std::endl;
    
    // 11. Limits and boundaries
    std::cout << "\n11. Numeric Limits Verification:" << std::endl;
    
    std::cout << "int min: " << std::numeric_limits<int>::min() << std::endl;
    std::cout << "int max: " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "double epsilon: " << std::numeric_limits<double>::epsilon() << std::endl;
    
    // 12. Examples that would cause compile errors (commented out)
    std::cout << "\n12. Examples That Would Cause Compile Errors:" << std::endl;
    std::cout << "// static_assert(sizeof(int) > sizeof(long), \"This would fail\");" << std::endl;
    std::cout << "// static_assert(false, \"This would always fail\");" << std::endl;
    std::cout << "// SafeArray<std::string> - would fail (not arithmetic)" << std::endl;
    std::cout << "// FixedBuffer<int, 0> - would fail (size must be > 0)" << std::endl;
    std::cout << "// NumericVector<unsigned int> - would fail (must be signed)" << std::endl;
    
    std::cout << "\n=== STATIC_ASSERT BENEFITS ===" << std::endl;
    std::cout << "✅ Compile-time error detection" << std::endl;
    std::cout << "✅ Self-documenting code (assertions as documentation)" << std::endl;
    std::cout << "✅ Template parameter validation" << std::endl;
    std::cout << "✅ Platform and configuration verification" << std::endl;
    std::cout << "✅ Zero runtime cost" << std::endl;
    std::cout << "✅ Clear error messages with custom text" << std::endl;
    std::cout << "⚠️  Only works with compile-time constant expressions" << std::endl;
    std::cout << "⚠️  Cannot replace runtime assertions for dynamic conditions" << std::endl;
    std::cout << "⚠️  Failure stops compilation (which is usually what you want)" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -o static_assert_demo static_assert_demo.cpp
./static_assert_demo

static_assert Key Features:
1. Compile-time evaluation: Checked during compilation, not runtime
2. Custom error messages: Provide meaningful error descriptions
3. Template parameter validation: Ensure template arguments meet requirements
4. Configuration verification: Validate constants and settings
5. Platform assumptions: Check platform-specific requirements

Syntax:
static_assert(constant_expression, "error message");

Common Use Cases:
- Template parameter validation
- Platform requirement verification
- Configuration constant validation
- Type trait checking
- Size and alignment requirements
- Mathematical constant verification

Benefits:
- Zero runtime cost (compile-time only)
- Early error detection (at compile time)
- Self-documenting code
- Template safety
- Platform portability checks

Best Practices:
- Use meaningful error messages
- Check template parameters early
- Validate configuration constants
- Combine with type traits for type checking
- Use in template specializations for constraints
*/
