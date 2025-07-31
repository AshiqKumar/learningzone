// C++14 Extended constexpr - Relaxed Constraints
// Compile: g++ -std=c++14 -o extended_constexpr_demo extended_constexpr_demo.cpp
// Run: ./extended_constexpr_demo

#include <iostream>
#include <array>
#include <string>
#include <cassert>

// C++11 constexpr was very limited - only single return statement
// C++14 relaxes many constraints

// 1. Multiple statements and local variables (C++14)
constexpr int factorial_cpp14(int n) {
    if (n <= 1) return 1;
    
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Compare with C++11 style (single expression)
constexpr int factorial_cpp11(int n) {
    return (n <= 1) ? 1 : n * factorial_cpp11(n - 1);
}

// 2. Loops and conditional statements
constexpr int fibonacci(int n) {
    if (n <= 1) return n;
    
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

constexpr int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 3. Mutable local variables and assignments
constexpr int sum_of_squares(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i * i;  // Multiple assignments allowed
    }
    return sum;
}

constexpr bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// 4. constexpr member functions with mutations (of local state)
class Counter {
private:
    int value;
    
public:
    constexpr Counter() : value(0) {}
    constexpr Counter(int v) : value(v) {}
    
    // C++14: constexpr member functions can modify local variables
    constexpr int increment_and_get(int times) {
        int result = value;
        for (int i = 0; i < times; ++i) {
            result++;
        }
        return result;
    }
    
    constexpr int get_value() const { return value; }
    
    // Note: Still cannot modify member variables in constexpr
    // This would NOT compile:
    // constexpr void increment() { value++; }  // Error in C++14
};

// 5. constexpr constructors with complex logic
class Point {
private:
    double x, y;
    
public:
    constexpr Point() : x(0), y(0) {}
    
    constexpr Point(double x_val, double y_val) : x(x_val), y(y_val) {
        // C++14: Can have statements in constexpr constructors
        // (but still cannot modify members after initialization)
    }
    
    constexpr double distance_from_origin() const {
        return sqrt_approximation(x * x + y * y);
    }
    
    constexpr double get_x() const { return x; }
    constexpr double get_y() const { return y; }
    
private:
    // Newton's method for square root approximation
    constexpr double sqrt_approximation(double n, double guess = 1.0, int iterations = 10) const {
        if (iterations == 0) return guess;
        
        double next_guess = (guess + n / guess) / 2.0;
        double diff = next_guess - guess;
        if (diff < 0) diff = -diff;  // abs
        
        if (diff < 0.0001) return next_guess;
        
        return sqrt_approximation(n, next_guess, iterations - 1);
    }
};

// 6. Complex compile-time calculations
constexpr int power(int base, int exp) {
    if (exp == 0) return 1;
    
    int result = 1;
    int current_base = base;
    
    while (exp > 0) {
        if (exp & 1) {  // If exp is odd
            result *= current_base;
        }
        current_base *= current_base;
        exp >>= 1;  // Divide by 2
    }
    
    return result;
}

// 7. constexpr with arrays and more complex data
constexpr int sum_array(const int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

template<int N>
constexpr std::array<int, N> generate_squares() {
    std::array<int, N> result{};  // Initialize all to 0
    
    for (int i = 0; i < N; ++i) {
        result[i] = i * i;
    }
    
    return result;
}

// 8. Compile-time string processing
constexpr int string_length(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

constexpr bool strings_equal(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return false;
        ++i;
    }
    return s1[i] == s2[i];  // Both should be '\0'
}

// 9. constexpr with switch statements
constexpr int days_in_month(int month, bool is_leap_year = false) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return is_leap_year ? 29 : 28;
        default:
            return 0;  // Invalid month
    }
}

constexpr bool is_leap_year(int year) {
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    if (year % 400 != 0) return false;
    return true;
}

// 10. Compile-time error checking
constexpr int safe_divide(int a, int b) {
    if (b == 0) {
        // In C++14, we can throw in constexpr functions
        // But the expression must not actually throw when evaluated at compile time
        throw "Division by zero";
    }
    return a / b;
}

int main() {
    std::cout << "=== C++14 EXTENDED CONSTEXPR DEMO ===" << std::endl;
    
    // 1. Factorial calculations - compile time
    std::cout << "\n1. Factorial Calculations:" << std::endl;
    
    constexpr int fact5_cpp14 = factorial_cpp14(5);
    constexpr int fact5_cpp11 = factorial_cpp11(5);
    constexpr int fact10 = factorial_cpp14(10);
    
    std::cout << "5! (C++14 style) = " << fact5_cpp14 << std::endl;
    std::cout << "5! (C++11 style) = " << fact5_cpp11 << std::endl;
    std::cout << "10! = " << fact10 << std::endl;
    
    // 2. Fibonacci and GCD
    std::cout << "\n2. Fibonacci and GCD:" << std::endl;
    
    constexpr int fib10 = fibonacci(10);
    constexpr int fib15 = fibonacci(15);
    constexpr int gcd_result = gcd(48, 18);
    
    std::cout << "Fibonacci(10) = " << fib10 << std::endl;
    std::cout << "Fibonacci(15) = " << fib15 << std::endl;
    std::cout << "GCD(48, 18) = " << gcd_result << std::endl;
    
    // 3. Mathematical calculations
    std::cout << "\n3. Mathematical Calculations:" << std::endl;
    
    constexpr int sum_squares_5 = sum_of_squares(5);  // 1² + 2² + 3² + 4² + 5² = 55
    constexpr bool prime_17 = is_prime(17);
    constexpr bool prime_18 = is_prime(18);
    constexpr int power_result = power(2, 10);  // 2^10 = 1024
    
    std::cout << "Sum of squares 1-5 = " << sum_squares_5 << std::endl;
    std::cout << "Is 17 prime? " << std::boolalpha << prime_17 << std::endl;
    std::cout << "Is 18 prime? " << prime_18 << std::endl;
    std::cout << "2^10 = " << power_result << std::endl;
    
    // 4. Counter class demonstration
    std::cout << "\n4. Counter Class:" << std::endl;
    
    constexpr Counter counter(5);
    constexpr int counter_result = counter.increment_and_get(3);  // 5 + 3 = 8
    
    std::cout << "Counter starting at 5, increment by 3: " << counter_result << std::endl;
    std::cout << "Original counter value: " << counter.get_value() << std::endl;
    
    // 5. Point class with distance calculation
    std::cout << "\n5. Point Class:" << std::endl;
    
    constexpr Point origin;
    constexpr Point p1(3.0, 4.0);
    constexpr double distance = p1.distance_from_origin();  // Should be ~5.0
    
    std::cout << "Point (3, 4) distance from origin ≈ " << distance << std::endl;
    
    // 6. Array operations
    std::cout << "\n6. Array Operations:" << std::endl;
    
    constexpr int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr int array_sum = sum_array(numbers, 10);  // Should be 55
    
    std::cout << "Sum of array [1..10] = " << array_sum << std::endl;
    
    // Generate array at compile time
    constexpr auto squares = generate_squares<6>();
    std::cout << "Squares array [0..5]: ";
    for (int i = 0; i < 6; ++i) {
        std::cout << squares[i] << " ";
    }
    std::cout << std::endl;
    
    // 7. String processing
    std::cout << "\n7. String Processing:" << std::endl;
    
    constexpr const char* message = "Hello, World!";
    constexpr int msg_length = string_length(message);
    constexpr bool strings_match = strings_equal("test", "test");
    constexpr bool strings_differ = strings_equal("test", "best");
    
    std::cout << "Length of \"" << message << "\" = " << msg_length << std::endl;
    std::cout << "\"test\" == \"test\"? " << std::boolalpha << strings_match << std::endl;
    std::cout << "\"test\" == \"best\"? " << strings_differ << std::endl;
    
    // 8. Date calculations
    std::cout << "\n8. Date Calculations:" << std::endl;
    
    constexpr int days_jan = days_in_month(1);
    constexpr int days_feb_normal = days_in_month(2, false);
    constexpr int days_feb_leap = days_in_month(2, true);
    constexpr bool is_2024_leap = is_leap_year(2024);
    constexpr bool is_2023_leap = is_leap_year(2023);
    
    std::cout << "Days in January: " << days_jan << std::endl;
    std::cout << "Days in February (normal year): " << days_feb_normal << std::endl;
    std::cout << "Days in February (leap year): " << days_feb_leap << std::endl;
    std::cout << "Is 2024 a leap year? " << std::boolalpha << is_2024_leap << std::endl;
    std::cout << "Is 2023 a leap year? " << is_2023_leap << std::endl;
    
    // 9. Division (compile-time safe)
    std::cout << "\n9. Safe Division:" << std::endl;
    
    constexpr int division_result = safe_divide(100, 5);  // OK at compile time
    std::cout << "100 / 5 = " << division_result << std::endl;
    
    // This would cause a compile error:
    // constexpr int bad_division = safe_divide(100, 0);  // Compile error!
    
    // But runtime division by zero would throw
    std::cout << "Runtime division by zero would throw an exception" << std::endl;
    
    // 10. Performance comparison
    std::cout << "\n10. Performance Comparison:" << std::endl;
    
    // All these calculations happen at compile time!
    constexpr int large_factorial = factorial_cpp14(12);  // Computed at compile time
    constexpr int large_fibonacci = fibonacci(30);        // Computed at compile time
    constexpr int large_power = power(3, 15);            // Computed at compile time
    
    std::cout << "12! = " << large_factorial << " (computed at compile time)" << std::endl;
    std::cout << "Fibonacci(30) = " << large_fibonacci << " (computed at compile time)" << std::endl;
    std::cout << "3^15 = " << large_power << " (computed at compile time)" << std::endl;
    
    // Runtime version for comparison
    auto start = std::chrono::high_resolution_clock::now();
    int runtime_factorial = factorial_cpp14(12);  // Computed at runtime
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Runtime 12! = " << runtime_factorial << " (took " << duration.count() << " nanoseconds)" << std::endl;
    
    // 11. Compile-time assertions
    std::cout << "\n11. Compile-time Assertions:" << std::endl;
    
    static_assert(factorial_cpp14(5) == 120, "5! should be 120");
    static_assert(fibonacci(10) == 55, "Fibonacci(10) should be 55");
    static_assert(is_prime(17), "17 should be prime");
    static_assert(!is_prime(18), "18 should not be prime");
    static_assert(power(2, 8) == 256, "2^8 should be 256");
    static_assert(gcd(48, 18) == 6, "GCD(48, 18) should be 6");
    
    std::cout << "All compile-time assertions passed!" << std::endl;
    
    std::cout << "\n=== C++14 CONSTEXPR IMPROVEMENTS SUMMARY ===" << std::endl;
    std::cout << "✅ Multiple statements and declarations in constexpr functions" << std::endl;
    std::cout << "✅ Local variables and assignments" << std::endl;
    std::cout << "✅ Loops (for, while) and conditional statements" << std::endl;
    std::cout << "✅ Switch statements" << std::endl;
    std::cout << "✅ Complex algorithms at compile time" << std::endl;
    std::cout << "✅ Better member function support" << std::endl;
    std::cout << "✅ Exception specifications (though not thrown at compile time)" << std::endl;
    std::cout << "⚠️  Still cannot modify global state" << std::endl;
    std::cout << "⚠️  Still cannot modify class members in constexpr member functions" << std::endl;
    std::cout << "⚠️  Dynamic memory allocation still not allowed" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++14 -Wall -Wextra -o extended_constexpr_demo extended_constexpr_demo.cpp
./extended_constexpr_demo

C++14 Extended constexpr Improvements:

C++11 constexpr limitations:
- Only single return statement
- No local variables
- No loops or conditionals
- Very restrictive

C++14 constexpr relaxations:
- Multiple statements allowed
- Local variables and assignments
- Loops (for, while, do-while)
- Conditional statements (if-else, switch)
- More complex algorithms

Still prohibited in C++14:
- Modifying global state
- Dynamic memory allocation
- Virtual function calls
- Exception handling (throw allowed but not caught)

Benefits:
- Write natural imperative code that runs at compile time
- Better performance - computations moved from runtime to compile time
- Compile-time error detection
- More complex compile-time calculations possible

Use Cases:
- Mathematical computations
- String processing
- Array initialization
- Configuration calculations
- Template metaprogramming simplification
*/
