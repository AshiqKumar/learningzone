// C++11 Lambda Expressions
// Compile: g++ -std=c++11 -o lambda_demo lambda_expressions_demo.cpp
// Run: ./lambda_demo

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

int main() {
    std::cout << "=== C++11 LAMBDA EXPRESSIONS DEMO ===" << std::endl;
    
    // 1. Basic lambda syntax
    std::cout << "\n1. Basic Lambda Syntax:" << std::endl;
    
    // Simple lambda that takes no parameters
    auto simple_lambda = []() {
        std::cout << "Hello from lambda!" << std::endl;
    };
    simple_lambda();
    
    // Lambda with parameters
    auto add = [](int a, int b) -> int {
        return a + b;
    };
    std::cout << "5 + 3 = " << add(5, 3) << std::endl;
    
    // Lambda without explicit return type (auto-deduced)
    auto multiply = [](int x, int y) {
        return x * y;  // return type deduced as int
    };
    std::cout << "4 * 7 = " << multiply(4, 7) << std::endl;
    
    // 2. Capture by value
    std::cout << "\n2. Capture by Value:" << std::endl;
    int x = 10;
    int y = 20;
    
    auto capture_by_value = [x, y]() {
        std::cout << "Captured x = " << x << ", y = " << y << std::endl;
        // x = 100;  // Error! x is const in lambda
    };
    capture_by_value();
    
    // Capture all by value
    auto capture_all_by_value = [=]() {
        std::cout << "All captured by value: x = " << x << ", y = " << y << std::endl;
    };
    capture_all_by_value();
    
    // 3. Capture by reference
    std::cout << "\n3. Capture by Reference:" << std::endl;
    int counter = 0;
    
    auto increment = [&counter]() {
        ++counter;
        std::cout << "Counter is now: " << counter << std::endl;
    };
    
    std::cout << "Initial counter: " << counter << std::endl;
    increment();
    increment();
    std::cout << "Final counter: " << counter << std::endl;
    
    // Capture all by reference
    int a = 100, b = 200;
    auto modify_all = [&]() {
        a += 10;
        b += 20;
    };
    
    std::cout << "Before: a = " << a << ", b = " << b << std::endl;
    modify_all();
    std::cout << "After: a = " << a << ", b = " << b << std::endl;
    
    // 4. Mixed captures
    std::cout << "\n4. Mixed Captures:" << std::endl;
    int val1 = 50, val2 = 60;
    
    auto mixed_capture = [val1, &val2](int param) {
        std::cout << "val1 (by value): " << val1 << std::endl;
        std::cout << "val2 (by reference): " << val2 << std::endl;
        std::cout << "parameter: " << param << std::endl;
        val2 += param;  // Can modify val2 (captured by reference)
        // val1 += param;  // Error! val1 is const
    };
    
    std::cout << "Before mixed capture: val2 = " << val2 << std::endl;
    mixed_capture(15);
    std::cout << "After mixed capture: val2 = " << val2 << std::endl;
    
    // 5. Mutable lambdas
    std::cout << "\n5. Mutable Lambdas:" << std::endl;
    int original = 42;
    
    auto mutable_lambda = [original]() mutable {
        original += 10;  // Now we can modify the captured copy
        std::cout << "Inside lambda: " << original << std::endl;
        return original;
    };
    
    std::cout << "Original value: " << original << std::endl;
    auto result = mutable_lambda();
    std::cout << "Lambda returned: " << result << std::endl;
    std::cout << "Original after lambda: " << original << " (unchanged)" << std::endl;
    
    // 6. Lambdas with STL algorithms
    std::cout << "\n6. Lambdas with STL Algorithms:" << std::endl;
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    std::cout << "Original: ";
    for (auto n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // Sort with lambda
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a < b;  // Ascending order
    });
    
    std::cout << "Sorted ascending: ";
    for (auto n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // Sort descending
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a > b;  // Descending order
    });
    
    std::cout << "Sorted descending: ";
    for (auto n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // Find elements with lambda
    auto it = std::find_if(numbers.begin(), numbers.end(), [](int n) {
        return n > 5;
    });
    
    if (it != numbers.end()) {
        std::cout << "First number > 5: " << *it << std::endl;
    }
    
    // Count elements with lambda
    int count = std::count_if(numbers.begin(), numbers.end(), [](int n) {
        return n % 2 == 0;  // Even numbers
    });
    std::cout << "Even numbers count: " << count << std::endl;
    
    // Transform with lambda
    std::vector<int> squared;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(squared),
                   [](int n) { return n * n; });
    
    std::cout << "Squared: ";
    for (auto n : squared) std::cout << n << " ";
    std::cout << std::endl;
    
    // 7. Lambda with strings
    std::cout << "\n7. Lambdas with Strings:" << std::endl;
    std::vector<std::string> words = {"apple", "banana", "cherry", "date"};
    
    // Sort by length
    std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    });
    
    std::cout << "Sorted by length: ";
    for (const auto& word : words) std::cout << word << " ";
    std::cout << std::endl;
    
    // Find strings containing 'a'
    auto found = std::find_if(words.begin(), words.end(), [](const std::string& s) {
        return s.find('a') != std::string::npos;
    });
    
    if (found != words.end()) {
        std::cout << "First word containing 'a': " << *found << std::endl;
    }
    
    // 8. Storing lambdas in variables
    std::cout << "\n8. Storing Lambdas:" << std::endl;
    
    // Using auto
    auto calculator = [](char op, int a, int b) -> int {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return b != 0 ? a / b : 0;
            default: return 0;
        }
    };
    
    std::cout << "10 + 5 = " << calculator('+', 10, 5) << std::endl;
    std::cout << "10 - 5 = " << calculator('-', 10, 5) << std::endl;
    std::cout << "10 * 5 = " << calculator('*', 10, 5) << std::endl;
    std::cout << "10 / 5 = " << calculator('/', 10, 5) << std::endl;
    
    // Using std::function
    std::function<int(int, int)> func_add = [](int a, int b) { return a + b; };
    std::function<int(int, int)> func_mul = [](int a, int b) { return a * b; };
    
    std::cout << "Using std::function - Add: " << func_add(3, 4) << std::endl;
    std::cout << "Using std::function - Multiply: " << func_mul(3, 4) << std::endl;
    
    // 9. Lambdas as function parameters
    std::cout << "\n9. Lambdas as Function Parameters:" << std::endl;
    
    // Function that takes lambda as parameter
    auto apply_to_vector = [](std::vector<int>& vec, std::function<void(int&)> func) {
        for (auto& element : vec) {
            func(element);
        }
    };
    
    std::vector<int> test_vec = {1, 2, 3, 4, 5};
    std::cout << "Before: ";
    for (auto n : test_vec) std::cout << n << " ";
    std::cout << std::endl;
    
    // Apply doubling lambda
    apply_to_vector(test_vec, [](int& n) { n *= 2; });
    
    std::cout << "After doubling: ";
    for (auto n : test_vec) std::cout << n << " ";
    std::cout << std::endl;
    
    // 10. Recursive lambda (C++11 way)
    std::cout << "\n10. Recursive Lambda:" << std::endl;
    
    std::function<int(int)> factorial = [&factorial](int n) -> int {
        return n <= 1 ? 1 : n * factorial(n - 1);
    };
    
    std::cout << "5! = " << factorial(5) << std::endl;
    std::cout << "6! = " << factorial(6) << std::endl;
    
    std::cout << "\n=== LAMBDA EXPRESSIONS BENEFITS ===" << std::endl;
    std::cout << "✅ Concise anonymous functions" << std::endl;
    std::cout << "✅ Perfect for STL algorithms" << std::endl;
    std::cout << "✅ Capture local variables efficiently" << std::endl;
    std::cout << "✅ No need to define separate functions for simple tasks" << std::endl;
    std::cout << "✅ Can be stored in variables and passed as parameters" << std::endl;
    std::cout << "⚠️  Be careful with capture modes (by value vs by reference)" << std::endl;
    std::cout << "⚠️  Use mutable for modifying captured-by-value variables" << std::endl;
    std::cout << "⚠️  Consider std::function for storing complex lambdas" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -o lambda_demo lambda_expressions_demo.cpp
./lambda_demo

Lambda Syntax:
[capture](parameters) -> return_type { body }

Capture modes:
- [] : Capture nothing
- [=] : Capture all by value
- [&] : Capture all by reference  
- [x] : Capture x by value
- [&x] : Capture x by reference
- [x, &y] : Mixed capture

Key Features:
- Anonymous functions defined inline
- Can capture local variables
- Perfect for STL algorithms
- Can be stored in auto or std::function
- Support recursive calls with std::function
*/
