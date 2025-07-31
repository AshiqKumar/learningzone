/**
 * @file register_demo.cpp
 * @brief Demonstration of 'register' storage class (deprecated in C++17)
 * 
 * Compile: g++ -std=c++14 -Wall -Wextra register_demo.cpp -o register_demo
 * Note: Use C++14 or earlier as 'register' is deprecated in C++17
 * Run: ./register_demo
 */

#include <iostream>
#include <chrono>
#include <vector>
#include <cstring>

// Note: register keyword is deprecated in C++17 and removed in C++20
// This demo shows historical usage and modern alternatives

// Function demonstrating register usage (pre-C++17)
void registerDemo() {
    std::cout << "\n=== Register Storage Class Demo ===" << std::endl;
    
    // Traditional register usage (deprecated)
    // register int counter = 0;        // Hint to store in CPU register
    // register char* ptr = nullptr;    // Register hint for pointer
    
    // Modern equivalent - let compiler optimize
    int counter = 0;           // Compiler will optimize if beneficial
    char* ptr = nullptr;       // Compiler decides optimal storage
    
    std::cout << "Register keyword was used to suggest CPU register storage" << std::endl;
    std::cout << "Modern compilers automatically optimize register usage" << std::endl;
    
    // Example of tight loop where register might have helped historically
    const int iterations = 1000000;
    
    // Without register hint (but compiler optimizes anyway)
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        counter += i;
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Loop completed in " << duration.count() << " microseconds" << std::endl;
    std::cout << "Final counter value: " << counter << std::endl;
}

// Historical context: why register was introduced
void historicalContext() {
    std::cout << "\n=== Historical Context ===" << std::endl;
    
    std::cout << "Original purpose of 'register' keyword:" << std::endl;
    std::cout << "1. Hint to compiler: store variable in CPU register" << std::endl;
    std::cout << "2. Potentially faster access than memory" << std::endl;
    std::cout << "3. Automatic storage duration (like auto)" << std::endl;
    std::cout << "4. Cannot take address of register variable" << std::endl;
    
    std::cout << "\nWhy it became obsolete:" << std::endl;
    std::cout << "1. Modern compilers are better at optimization" << std::endl;
    std::cout << "2. CPU architectures became more complex" << std::endl;
    std::cout << "3. Register allocation is now automatic" << std::endl;
    std::cout << "4. Programmer hints often suboptimal" << std::endl;
}

// Demonstrate compiler optimization without register
void modernOptimization() {
    std::cout << "\n=== Modern Compiler Optimization ===" << std::endl;
    
    const int size = 1000;
    std::vector<int> data(size);
    
    // Initialize data
    for (int i = 0; i < size; ++i) {
        data[i] = i * 2;
    }
    
    // Modern tight loop - compiler optimizes automatically
    int sum = 0;
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < size; ++i) {
        sum += data[i];  // Compiler may use registers optimally
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "Sum calculated: " << sum << std::endl;
    std::cout << "Time taken: " << duration.count() << " nanoseconds" << std::endl;
    std::cout << "Compiler automatically optimized register usage" << std::endl;
}

// Alternative optimization techniques
void modernAlternatives() {
    std::cout << "\n=== Modern Optimization Alternatives ===" << std::endl;
    
    // 1. Compiler optimization flags
    std::cout << "1. Compiler optimization flags:" << std::endl;
    std::cout << "   -O1, -O2, -O3 for GCC/Clang" << std::endl;
    std::cout << "   /O1, /O2, /Ox for MSVC" << std::endl;
    
    // 2. Profile-guided optimization
    std::cout << "\n2. Profile-Guided Optimization (PGO):" << std::endl;
    std::cout << "   Compiler uses runtime data for optimization" << std::endl;
    
    // 3. Inline functions
    std::cout << "\n3. Inline functions for small, frequent calls:" << std::endl;
    
    auto inline_add = [](int a, int b) -> int {
        return a + b;  // Likely inlined by compiler
    };
    
    int result = inline_add(5, 10);
    std::cout << "   Inline result: " << result << std::endl;
    
    // 4. const and constexpr
    std::cout << "\n4. const and constexpr for compile-time optimization:" << std::endl;
    
    constexpr int compile_time_calc(int x) {
        return x * x + 2 * x + 1;  // Evaluated at compile time
    }
    
    constexpr int ct_result = compile_time_calc(10);
    std::cout << "   Compile-time result: " << ct_result << std::endl;
    
    // 5. Loop optimization
    std::cout << "\n5. Loop optimization techniques:" << std::endl;
    
    const int n = 100;
    int array[n];
    
    // Initialize
    for (int i = 0; i < n; ++i) {
        array[i] = i;
    }
    
    // Loop unrolling example (compiler may do this automatically)
    int sum = 0;
    int i = 0;
    for (; i < n - 3; i += 4) {  // Process 4 elements at once
        sum += array[i] + array[i+1] + array[i+2] + array[i+3];
    }
    for (; i < n; ++i) {  // Handle remaining elements
        sum += array[i];
    }
    
    std::cout << "   Optimized loop sum: " << sum << std::endl;
}

// Comparison of storage classes
void storageClassComparison() {
    std::cout << "\n=== Storage Class Comparison ===" << std::endl;
    
    // Automatic (default for local variables)
    int automatic_var = 10;
    
    // Static (persists between calls)
    static int static_var = 20;
    static_var++;
    
    // External (declared elsewhere)
    // extern int external_var;  // Would need definition elsewhere
    
    std::cout << "Automatic variable: " << automatic_var << std::endl;
    std::cout << "Static variable: " << static_var << std::endl;
    
    std::cout << "\nStorage Class Properties:" << std::endl;
    std::cout << "auto:     Local scope, automatic duration, stack storage" << std::endl;
    std::cout << "static:   Local/global scope, static duration, data segment" << std::endl;
    std::cout << "extern:   Global scope, static duration, external linkage" << std::endl;
    std::cout << "register: (deprecated) Hint for register storage" << std::endl;
}

// Performance measurement function
template<typename Func>
void measurePerformance(const std::string& name, Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << name << " took " << duration.count() << " microseconds" << std::endl;
}

int main() {
    std::cout << "=== REGISTER STORAGE CLASS DEMO ===" << std::endl;
    std::cout << "Note: 'register' is deprecated in C++17 and removed in C++20" << std::endl;
    
    // 1. Basic register demonstration
    registerDemo();
    
    // 2. Historical context
    historicalContext();
    
    // 3. Modern optimization
    modernOptimization();
    
    // 4. Alternative optimization techniques
    modernAlternatives();
    
    // 5. Storage class comparison
    storageClassComparison();
    
    // 6. Performance comparison example
    std::cout << "\n=== Performance Comparison ===" << std::endl;
    
    const int iterations = 1000000;
    
    // Test 1: Simple calculation
    measurePerformance("Simple calculation", [&]() {
        volatile int sum = 0;  // volatile prevents optimization
        for (int i = 0; i < iterations; ++i) {
            sum += i;
        }
    });
    
    // Test 2: Function call in loop
    auto simple_add = [](int a, int b) { return a + b; };
    
    measurePerformance("Function call in loop", [&]() {
        volatile int sum = 0;
        for (int i = 0; i < iterations; ++i) {
            sum = simple_add(sum, i);
        }
    });
    
    // Test 3: Inline function
    measurePerformance("Inline function", [&]() {
        volatile int sum = 0;
        for (int i = 0; i < iterations; ++i) {
            sum += i;  // Compiler likely optimizes this
        }
    });
    
    std::cout << "\n=== Register Keyword Legacy ===" << std::endl;
    std::cout << "Historical significance:" << std::endl;
    std::cout << "✅ Introduced when compilers had limited optimization" << std::endl;
    std::cout << "✅ Allowed programmer hints for performance-critical code" << std::endl;
    std::cout << "✅ Part of C heritage carried into early C++" << std::endl;
    
    std::cout << "\nWhy it was deprecated:" << std::endl;
    std::cout << "❌ Modern compilers optimize better than programmer hints" << std::endl;
    std::cout << "❌ CPU architecture complexity makes manual hints ineffective" << std::endl;
    std::cout << "❌ Register allocation algorithms are sophisticated" << std::endl;
    std::cout << "❌ Keyword served no useful purpose in modern C++" << std::endl;
    
    std::cout << "\nModern alternatives:" << std::endl;
    std::cout << "✅ Compiler optimization flags (-O2, -O3)" << std::endl;
    std::cout << "✅ Profile-guided optimization (PGO)" << std::endl;
    std::cout << "✅ Link-time optimization (LTO)" << std::endl;
    std::cout << "✅ constexpr for compile-time evaluation" << std::endl;
    std::cout << "✅ inline for function inlining" << std::endl;
    std::cout << "✅ Algorithm and data structure optimization" << std::endl;
    
    return 0;
}

/*
Register Storage Class Summary:

Historical Purpose:
- Hint to compiler: store variable in CPU register
- Potentially faster access than memory
- Automatic storage duration
- Cannot take address of register variable

Why Deprecated:
1. Compiler optimization improved dramatically
2. Modern CPUs have complex register architectures
3. Automatic register allocation is more effective
4. Programmer hints often counterproductive

Modern Alternatives:
1. Compiler optimization flags
2. Profile-guided optimization
3. Algorithmic improvements
4. Data structure optimization
5. constexpr for compile-time computation
6. inline for function optimization

Timeline:
- C (1972): register introduced
- C++98: register inherited from C
- C++11: register usage discouraged
- C++17: register deprecated
- C++20: register keyword removed (except for compatibility)

Best Practices:
- Don't use register in modern C++
- Trust compiler optimization
- Use appropriate optimization flags
- Focus on algorithmic efficiency
- Measure performance to guide optimization
- Use tools like profilers for optimization guidance

Legacy Code:
- Old code with register will compile but ignore the keyword
- Remove register for cleaner, modern code
- Compiler treats register variables as automatic
*/
