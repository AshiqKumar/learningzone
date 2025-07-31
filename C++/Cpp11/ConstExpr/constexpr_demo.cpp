// C++11 constexpr - Compile-Time Constants and Functions
// Compile: g++ -std=c++11 -o constexpr_demo constexpr_demo.cpp
// Run: ./constexpr_demo

#include <iostream>
#include <array>
#include <string>
#include <cassert>
#include <bitset>

// 1. constexpr variables - computed at compile time
constexpr int BUFFER_SIZE = 1024;
constexpr double PI = 3.14159265359;
constexpr const char* GREETING = "Hello, constexpr!";

// 2. constexpr functions - can be evaluated at compile time
constexpr int square(int x) {
    return x * x;
}

constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr bool is_even(int x) {
    return (x % 2) == 0;
}

// More complex constexpr function
constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

// constexpr function with conditions
constexpr int absolute(int x) {
    return (x < 0) ? -x : x;
}

// constexpr function for array size calculation
constexpr size_t string_length(const char* str) {
    return (*str == '\0') ? 0 : 1 + string_length(str + 1);
}

// 3. constexpr class/struct
struct Point {
    int x, y;
    
    // constexpr constructor
    constexpr Point(int x_val, int y_val) : x(x_val), y(y_val) {}
    
    // constexpr member functions
    constexpr int get_x() const { return x; }
    constexpr int get_y() const { return y; }
    constexpr int distance_squared() const { return x * x + y * y; }
};

// constexpr with more complex class
class Rectangle {
private:
    int width_, height_;
    
public:
    constexpr Rectangle(int w, int h) : width_(w), height_(h) {}
    
    constexpr int area() const { return width_ * height_; }
    constexpr int perimeter() const { return 2 * (width_ + height_); }
    constexpr bool is_square() const { return width_ == height_; }
    
    constexpr int get_width() const { return width_; }
    constexpr int get_height() const { return height_; }
};

// 4. Template with constexpr
template<int N>
struct PowersOfTwo {
    static constexpr int value = 2 * PowersOfTwo<N-1>::value;
};

template<>
struct PowersOfTwo<0> {
    static constexpr int value = 1;
};

// constexpr template function
template<typename T>
constexpr T max_value(T a, T b) {
    return (a > b) ? a : b;
}

// 5. Array size calculation using constexpr
template<size_t N>
class StaticArray {
private:
    int data_[N];
    
public:
    constexpr StaticArray() : data_{} {}  // Zero initialization
    
    constexpr size_t size() const { return N; }
    
    int& operator[](size_t index) { return data_[index]; }
    const int& operator[](size_t index) const { return data_[index]; }
};

// 6. constexpr for compile-time string processing
constexpr bool starts_with(const char* str, const char* prefix) {
    return (*prefix == '\0') ? true :
           (*str == '\0') ? false :
           (*str == *prefix) ? starts_with(str + 1, prefix + 1) : false;
}

constexpr int count_chars(const char* str, char target) {
    return (*str == '\0') ? 0 :
           (*str == target) ? 1 + count_chars(str + 1, target) :
           count_chars(str + 1, target);
}

// 7. Mathematical constants and functions
namespace math_constants {
    constexpr double E = 2.71828182845904523536;
    constexpr double GOLDEN_RATIO = 1.61803398874989484820;
    constexpr double SQRT_2 = 1.41421356237309504880;
    
    constexpr double deg_to_rad(double degrees) {
        return degrees * PI / 180.0;
    }
    
    constexpr double rad_to_deg(double radians) {
        return radians * 180.0 / PI;
    }
}

// 8. Compile-time hash function (simplified)
constexpr size_t simple_hash(const char* str) {
    size_t hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + static_cast<size_t>(*str++);
    }
    return hash;
}

// 9. constexpr for bit manipulation
constexpr bool is_power_of_two(unsigned int x) {
    return x != 0 && (x & (x - 1)) == 0;
}

constexpr int count_set_bits(unsigned int x) {
    return (x == 0) ? 0 : (x & 1) + count_set_bits(x >> 1);
}

constexpr unsigned int reverse_bits(unsigned int x, int bits = 32) {
    return (bits == 0) ? 0 : ((x & 1) << (bits - 1)) | reverse_bits(x >> 1, bits - 1);
}

int main() {
    std::cout << "=== C++11 CONSTEXPR DEMO ===" << std::endl;
    
    // 1. Basic constexpr variables
    std::cout << "\n1. constexpr Variables:" << std::endl;
    std::cout << "BUFFER_SIZE: " << BUFFER_SIZE << std::endl;
    std::cout << "PI: " << PI << std::endl;
    std::cout << "GREETING: " << GREETING << std::endl;
    
    // These values are computed at compile time!
    std::array<int, BUFFER_SIZE> buffer;  // Size known at compile time
    std::cout << "Buffer size: " << buffer.size() << std::endl;
    
    // 2. constexpr functions
    std::cout << "\n2. constexpr Functions:" << std::endl;
    
    // These are computed at compile time when possible
    constexpr int sq5 = square(5);
    constexpr int fact5 = factorial(5);
    constexpr bool even10 = is_even(10);
    constexpr int fib8 = fibonacci(8);
    
    std::cout << "square(5): " << sq5 << std::endl;
    std::cout << "factorial(5): " << fact5 << std::endl;
    std::cout << "is_even(10): " << even10 << std::endl;
    std::cout << "fibonacci(8): " << fib8 << std::endl;
    
    // Runtime usage (still works!)
    int runtime_val = 7;
    std::cout << "square(runtime_val): " << square(runtime_val) << std::endl;
    
    // 3. constexpr with arrays
    std::cout << "\n3. constexpr with Array Sizes:" << std::endl;
    
    constexpr size_t msg_len = string_length("Hello World");
    std::array<char, msg_len + 1> message_buffer;
    
    std::cout << "Compile-time string length: " << msg_len << std::endl;
    std::cout << "Message buffer size: " << message_buffer.size() << std::endl;
    
    // 4. constexpr classes
    std::cout << "\n4. constexpr Classes:" << std::endl;
    
    constexpr Point origin(0, 0);
    constexpr Point p1(3, 4);
    constexpr int dist_sq = p1.distance_squared();
    
    std::cout << "Point p1(" << p1.get_x() << ", " << p1.get_y() << ")" << std::endl;
    std::cout << "Distance squared from origin: " << dist_sq << std::endl;
    
    constexpr Rectangle rect(5, 3);
    constexpr int area = rect.area();
    constexpr int perimeter = rect.perimeter();
    constexpr bool is_square = rect.is_square();
    
    std::cout << "Rectangle " << rect.get_width() << "x" << rect.get_height() << std::endl;
    std::cout << "Area: " << area << ", Perimeter: " << perimeter << std::endl;
    std::cout << "Is square: " << (is_square ? "Yes" : "No") << std::endl;
    
    // 5. Template constexpr
    std::cout << "\n5. Template constexpr:" << std::endl;
    
    constexpr int power8 = PowersOfTwo<8>::value;
    constexpr int power10 = PowersOfTwo<10>::value;
    
    std::cout << "2^8 = " << power8 << std::endl;
    std::cout << "2^10 = " << power10 << std::endl;
    
    constexpr int max_ab = max_value(15, 23);
    constexpr double max_cd = max_value(3.14, 2.71);
    
    std::cout << "max(15, 23): " << max_ab << std::endl;
    std::cout << "max(3.14, 2.71): " << max_cd << std::endl;
    
    // 6. Compile-time string processing
    std::cout << "\n6. Compile-time String Processing:" << std::endl;
    
    constexpr const char* test_str = "Hello World";
    constexpr bool starts_hello = starts_with(test_str, "Hello");
    constexpr bool starts_world = starts_with(test_str, "World");
    constexpr int l_count = count_chars(test_str, 'l');
    
    std::cout << "String: \"" << test_str << "\"" << std::endl;
    std::cout << "Starts with 'Hello': " << (starts_hello ? "Yes" : "No") << std::endl;
    std::cout << "Starts with 'World': " << (starts_world ? "Yes" : "No") << std::endl;
    std::cout << "Count of 'l': " << l_count << std::endl;
    
    // 7. Mathematical constants
    std::cout << "\n7. Mathematical Constants:" << std::endl;
    
    constexpr double rad_90 = math_constants::deg_to_rad(90.0);
    constexpr double deg_pi = math_constants::rad_to_deg(PI);
    
    std::cout << "90 degrees in radians: " << rad_90 << std::endl;
    std::cout << "π radians in degrees: " << deg_pi << std::endl;
    std::cout << "Golden ratio: " << math_constants::GOLDEN_RATIO << std::endl;
    std::cout << "√2: " << math_constants::SQRT_2 << std::endl;
    
    // 8. Compile-time hashing
    std::cout << "\n8. Compile-time Hashing:" << std::endl;
    
    constexpr size_t hash1 = simple_hash("Hello");
    constexpr size_t hash2 = simple_hash("World");
    constexpr size_t hash3 = simple_hash("Hello");  // Same as hash1
    
    std::cout << "hash('Hello'): " << hash1 << std::endl;
    std::cout << "hash('World'): " << hash2 << std::endl;
    std::cout << "hash('Hello') again: " << hash3 << std::endl;
    std::cout << "Hashes equal: " << (hash1 == hash3 ? "Yes" : "No") << std::endl;
    
    // 9. Bit manipulation
    std::cout << "\n9. Compile-time Bit Manipulation:" << std::endl;
    
    constexpr bool pow2_8 = is_power_of_two(8);
    constexpr bool pow2_7 = is_power_of_two(7);
    constexpr int bits_42 = count_set_bits(42);  // 42 = 101010 in binary
    constexpr unsigned int reversed = reverse_bits(0b11000000, 8);  // Reverse 8 bits
    
    std::cout << "8 is power of 2: " << (pow2_8 ? "Yes" : "No") << std::endl;
    std::cout << "7 is power of 2: " << (pow2_7 ? "Yes" : "No") << std::endl;
    std::cout << "Set bits in 42: " << bits_42 << std::endl;
    std::cout << "Reverse bits of 11000000: " << std::bitset<8>(reversed) << std::endl;
    
    // 10. Static arrays with constexpr sizes
    std::cout << "\n10. Static Arrays with constexpr:" << std::endl;
    
    constexpr size_t ARRAY_SIZE = square(5);  // 25, computed at compile time
    StaticArray<ARRAY_SIZE> static_array;
    
    std::cout << "Static array size: " << static_array.size() << std::endl;
    
    // Fill with some data
    for (size_t i = 0; i < static_array.size() && i < 10; ++i) {
        static_array[i] = static_cast<int>(i * i);
    }
    
    std::cout << "First 10 elements: ";
    for (size_t i = 0; i < 10; ++i) {
        std::cout << static_array[i] << " ";
    }
    std::cout << std::endl;
    
    // 11. constexpr vs const demonstration
    std::cout << "\n11. constexpr vs const:" << std::endl;
    
    const int const_val = square(5);        // Computed at runtime
    constexpr int constexpr_val = square(5); // Computed at compile time
    
    std::cout << "const value: " << const_val << std::endl;
    std::cout << "constexpr value: " << constexpr_val << std::endl;
    
    // Only constexpr can be used in constant expressions
    std::array<int, constexpr_val> constexpr_array;  // OK
    // std::array<int, const_val> const_array;      // Error in C++11!
    
    std::cout << "constexpr array size: " << constexpr_array.size() << std::endl;
    
    // 12. Compile-time vs runtime behavior
    std::cout << "\n12. Compile-time vs Runtime Behavior:" << std::endl;
    
    // Compile-time evaluation
    constexpr int compile_time_result = factorial(6);
    std::cout << "Compile-time factorial(6): " << compile_time_result << std::endl;
    
    // Runtime evaluation
    int n = 6;
    int runtime_result = factorial(n);
    std::cout << "Runtime factorial(6): " << runtime_result << std::endl;
    
    std::cout << "\n=== CONSTEXPR BENEFITS ===" << std::endl;
    std::cout << "✅ Compile-time computation for better performance" << std::endl;
    std::cout << "✅ Can be used in constant expressions" << std::endl;
    std::cout << "✅ Template-friendly (template parameters)" << std::endl;
    std::cout << "✅ Array size specification at compile time" << std::endl;
    std::cout << "✅ Type safety and early error detection" << std::endl;
    std::cout << "✅ Can still be called at runtime when needed" << std::endl;
    std::cout << "⚠️  Function must be evaluable at compile time" << std::endl;
    std::cout << "⚠️  Limited to simple operations in C++11" << std::endl;
    std::cout << "⚠️  All paths must be deterministic" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -o constexpr_demo constexpr_demo.cpp
./constexpr_demo

constexpr Key Features:
1. Variables: Values computed at compile time
2. Functions: Can be evaluated at compile time
3. Constructors: Enable compile-time object creation
4. Member functions: Compile-time method calls
5. Template integration: Perfect for template parameters

Benefits:
- Performance: No runtime computation cost
- Safety: Compile-time error detection
- Flexibility: Can still be used at runtime
- Template compatibility: Works with template parameters
- Array sizes: Enable compile-time array sizing

C++11 Limitations:
- Single return statement (relaxed in C++14)
- No loops or local variables (added in C++14)
- Limited standard library support

Best Practices:
- Use for mathematical constants and simple calculations
- Combine with templates for generic programming
- Prefer over #define for type safety
- Use for array sizes instead of magic numbers
*/
