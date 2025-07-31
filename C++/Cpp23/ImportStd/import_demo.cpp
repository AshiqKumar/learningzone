// C++23 import std - Standard Library Modules
// Compile: g++ -std=c++23 -fmodules-ts -o import_demo import_demo.cpp
// Alternative: clang++ -std=c++23 -stdlib=libc++ -fmodules -o import_demo import_demo.cpp
// Run: ./import_demo

// C++23 allows importing the entire standard library as a module
// This is a major improvement over traditional #include directives

// Traditional approach (still works):
// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>
// #include <ranges>

// Modern C++23 approach - import std:
import std;

// Note: If import std; is not supported, fallback to traditional includes
#ifndef __cpp_modules
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <map>
#include <set>
#include <chrono>
#include <format>
#include <expected>
#include <mdspan>
#include <print>
#include <numeric>
#include <random>
#include <thread>
#include <future>
#include <memory>
#include <typeinfo>
#include <span>
#endif

// 1. Demonstrate basic usage after import std
void demonstrate_basic_std_usage() {
    std::println("1. Basic Standard Library Usage after 'import std':");
    
    // All std components are available without individual includes
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::string message = "Hello, C++23 Modules!";
    
    std::println("Vector: {}", numbers);
    std::println("String: {}", message);
    
    // Algorithms
    auto even_count = std::ranges::count_if(numbers, [](int n) { return n % 2 == 0; });
    std::println("Even numbers count: {}", even_count);
    
    // Ranges
    auto squares = numbers 
        | std::views::transform([](int n) { return n * n; })
        | std::views::take(5);
    
    std::println("First 5 squares: {}", squares);
}

// 2. Advanced STL features available through import std
void demonstrate_advanced_features() {
    std::println("\n2. Advanced STL Features:");
    
    // Containers
    std::map<std::string, int> scores = {
        {"Alice", 95}, {"Bob", 87}, {"Charlie", 92}
    };
    
    std::set<int> unique_numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    
    std::println("Scores: {}", scores);
    std::println("Unique numbers: {}", unique_numbers);
    
    // Smart pointers
    auto ptr = std::make_unique<std::string>("Smart pointer content");
    auto shared = std::make_shared<std::vector<int>>(std::initializer_list<int>{1, 2, 3, 4, 5});
    
    std::println("Unique pointer: {}", *ptr);
    std::println("Shared pointer: {}", *shared);
    
    // Optional and variant
    std::optional<int> maybe_value = 42;
    std::variant<int, std::string, double> value_variant = std::string("Hello");
    
    if (maybe_value) {
        std::println("Optional value: {}", *maybe_value);
    }
    
    std::visit([](const auto& v) {
        std::println("Variant holds: {}", v);
    }, value_variant);
}

// 3. Chrono and time utilities
void demonstrate_chrono_features() {
    std::println("\n3. Chrono and Time Utilities:");
    
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::milliseconds(1500);
    
    std::println("Current time: {}", now);
    std::println("Duration: {}", duration);
    
    // Timing operations
    auto start = std::chrono::high_resolution_clock::now();
    
    // Simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::println("Elapsed time: {} microseconds", elapsed.count());
}

// 4. Numeric algorithms and random numbers
void demonstrate_numeric_features() {
    std::println("\n4. Numeric and Random Features:");
    
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Numeric algorithms
    int sum = std::accumulate(data.begin(), data.end(), 0);
    auto product = std::accumulate(data.begin(), data.end(), 1, std::multiplies<int>());
    
    std::println("Sum: {}", sum);
    std::println("Product: {}", product);
    
    // Partial sums
    std::vector<int> partial_sums(data.size());
    std::partial_sum(data.begin(), data.end(), partial_sums.begin());
    std::println("Partial sums: {}", partial_sums);
    
    // Random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    std::vector<int> random_numbers;
    for (int i = 0; i < 10; ++i) {
        random_numbers.push_back(dis(gen));
    }
    
    std::println("Random numbers: {}", random_numbers);
    
    // Statistical operations
    std::ranges::sort(random_numbers);
    double mean = std::accumulate(random_numbers.begin(), random_numbers.end(), 0.0) / random_numbers.size();
    
    std::println("Sorted: {}", random_numbers);
    std::println("Mean: {:.2f}", mean);
}

// 5. String and formatting utilities
void demonstrate_string_features() {
    std::println("\n5. String and Formatting Features:");
    
    std::string text = "  Hello, World!  ";
    
    // String views for efficient string operations
    std::string_view view = text;
    std::println("Original: '{}'", text);
    std::println("String view: '{}'", view);
    
    // Find operations
    size_t pos = text.find("World");
    if (pos != std::string::npos) {
        std::println("'World' found at position: {}", pos);
    }
    
    // String formatting (C++20/23 features)
    int age = 25;
    std::string name = "Alice";
    auto formatted = std::format("Name: {}, Age: {}", name, age);
    std::println("Formatted string: {}", formatted);
    
    // String manipulation
    std::string upper_text = text;
    std::ranges::transform(upper_text, upper_text.begin(), 
                          [](char c) { return std::toupper(c); });
    std::println("Uppercase: '{}'", upper_text);
}

// 6. Memory management features
void demonstrate_memory_features() {
    std::println("\n6. Memory Management Features:");
    
    // Span for safe array access
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    std::span<int> span_view = arr;
    
    std::println("Array through span: {}", span_view);
    
    // First few elements
    auto first_three = span_view.first(3);
    std::println("First three: {}", first_three);
    
    // Memory allocation
    auto buffer = std::make_unique<int[]>(10);
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i * i;
    }
    
    std::span<int> buffer_span(buffer.get(), 10);
    std::println("Buffer: {}", buffer_span);
    
    // Memory utilities
    std::println("Size of int: {} bytes", sizeof(int));
    std::println("Alignment of int: {} bytes", alignof(int));
    
    // Type information
    std::println("Type of buffer: {}", typeid(buffer).name());
}

// 7. Concurrent programming features
void demonstrate_concurrent_features() {
    std::println("\n7. Concurrent Programming Features:");
    
    // Future and async
    auto future_result = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return 42;
    });
    
    std::println("Computing asynchronously...");
    int result = future_result.get();
    std::println("Async result: {}", result);
    
    // Thread-safe operations
    std::atomic<int> counter(0);
    
    auto increment_task = [&counter]() {
        for (int i = 0; i < 1000; ++i) {
            counter.fetch_add(1);
        }
    };
    
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(increment_task);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::println("Atomic counter final value: {}", counter.load());
}

// 8. C++23 specific features available through import std
void demonstrate_cpp23_features() {
    std::println("\n8. C++23 Specific Features:");
    
    // std::expected for error handling
    auto divide = [](double a, double b) -> std::expected<double, std::string> {
        if (b == 0.0) {
            return std::unexpected("Division by zero");
        }
        return a / b;
    };
    
    auto result1 = divide(10.0, 2.0);
    auto result2 = divide(10.0, 0.0);
    
    if (result1) {
        std::println("Division result: {}", *result1);
    }
    
    if (!result2) {
        std::println("Division error: {}", result2.error());
    }
    
    // Multidimensional array support
    std::vector<int> matrix_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::mdspan<int, std::dextents<size_t, 2>> matrix(matrix_data.data(), 3, 4);
    
    std::println("Matrix element [1,2]: {}", matrix[1, 2]);
    
    // Print utilities (C++23)
    std::println("Using std::println from imported std module!");
}

// 9. Performance comparison: import vs include
void demonstrate_performance_characteristics() {
    std::println("\n9. Performance Characteristics:");
    
    // Compile-time benefits of modules:
    std::println("Module import benefits:");
    std::println("✅ Faster compilation (modules are pre-compiled)");
    std::println("✅ Better dependency tracking");
    std::println("✅ Reduced preprocessor overhead");
    std::println("✅ Isolation from macro pollution");
    std::println("✅ Better incremental builds");
    
    // Runtime performance is identical
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> data(100000);
    std::iota(data.begin(), data.end(), 1);
    
    auto sum = std::accumulate(data.begin(), data.end(), 0LL);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::println("Runtime performance test:");
    std::println("Sum of 100,000 integers: {}", sum);
    std::println("Time taken: {} microseconds", duration.count());
    std::println("(Performance identical to #include version)");
}

// 10. Module best practices and migration
void demonstrate_best_practices() {
    std::println("\n10. Best Practices and Migration:");
    
    std::println("Migration from #include to import std:");
    std::println("");
    std::println("Before (C++20 and earlier):");
    std::println("  #include <iostream>");
    std::println("  #include <vector>");
    std::println("  #include <algorithm>");
    std::println("");
    std::println("After (C++23):");
    std::println("  import std;");
    std::println("");
    
    std::println("Best practices:");
    std::println("✅ Use 'import std;' instead of multiple includes");
    std::println("✅ Can mix with traditional includes during transition");
    std::println("✅ Use specific module imports for better control:");
    std::println("   - import std.core; (basic utilities)");
    std::println("   - import std.threading; (threading utilities)");
    std::println("   - import std.memory; (memory management)");
    std::println("✅ Prefer modules for new projects");
    std::println("⚠️  Ensure compiler support before migration");
    std::println("⚠️  May require build system updates");
    
    std::println("\nCompiler support status:");
    std::println("- GCC 14+: Experimental support");
    std::println("- Clang 17+: Partial support");
    std::println("- MSVC 2022 17.5+: Good support");
}

// 11. Integration with user-defined modules
namespace my_module {
    class Calculator {
    public:
        template<typename T>
        static T add(T a, T b) {
            return a + b;
        }
        
        template<typename T>
        static T multiply(T a, T b) {
            return a * b;
        }
        
        static void demonstrate() {
            std::println("Custom module working with imported std:");
            
            auto result1 = add(10, 20);
            auto result2 = multiply(3.14, 2.0);
            
            std::println("Addition: {}", result1);
            std::println("Multiplication: {:.2f}", result2);
            
            // Using std algorithms with our custom types
            std::vector<int> numbers = {1, 2, 3, 4, 5};
            std::ranges::transform(numbers, numbers.begin(), 
                                  [](int n) { return multiply(n, n); });
            
            std::println("Squared numbers: {}", numbers);
        }
    };
}

void demonstrate_module_integration() {
    std::println("\n11. Integration with User-Defined Modules:");
    my_module::Calculator::demonstrate();
}

int main() {
    std::println("=== C++23 IMPORT STD DEMO ===");
    
    try {
        demonstrate_basic_std_usage();
        demonstrate_advanced_features();
        demonstrate_chrono_features();
        demonstrate_numeric_features();
        demonstrate_string_features();
        demonstrate_memory_features();
        demonstrate_concurrent_features();
        demonstrate_cpp23_features();
        demonstrate_performance_characteristics();
        demonstrate_best_practices();
        demonstrate_module_integration();
        
    } catch (const std::exception& e) {
        std::println("Exception caught: {}", e.what());
        return 1;
    }
    
    std::println("\n=== IMPORT STD BENEFITS ===");
    std::println("✅ Faster compilation times (pre-compiled modules)");
    std::println("✅ Better dependency management");
    std::println("✅ Reduced preprocessor overhead");
    std::println("✅ Protection from macro pollution");
    std::println("✅ Cleaner code (single import line)");
    std::println("✅ Better incremental build performance");
    std::println("✅ Improved IDE support and IntelliSense");
    std::println("✅ Forward compatibility with module ecosystem");
    std::println("⚠️  Requires modern compiler with C++23 support");
    std::println("⚠️  May need build system modifications");
    std::println("⚠️  Learning curve for module system concepts");
    std::println("⚠️  Potential compatibility issues with older code");
    
    std::println("\n=== COMPILER REQUIREMENTS ===");
    std::println("GCC: Use -std=c++23 -fmodules-ts");
    std::println("Clang: Use -std=c++23 -fmodules -stdlib=libc++");
    std::println("MSVC: Use /std:c++23 with VS 2022 17.5+");
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

GCC (if supported):
g++ -std=c++23 -fmodules-ts -Wall -Wextra -o import_demo import_demo.cpp
./import_demo

Clang (if supported):
clang++ -std=c++23 -stdlib=libc++ -fmodules -Wall -Wextra -o import_demo import_demo.cpp
./import_demo

MSVC (if supported):
cl /std:c++23 /EHsc import_demo.cpp
import_demo.exe

Fallback compilation (traditional includes):
g++ -std=c++23 -Wall -Wextra -o import_demo import_demo.cpp
./import_demo

C++23 import std Key Features:
1. Single import statement replaces multiple #include directives
2. Faster compilation through pre-compiled modules
3. Better dependency tracking and management
4. Protection from macro pollution
5. Improved incremental build performance

Basic Usage:
import std;  // Replaces all standard library includes

// Now all std components are available:
std::vector<int> v;
std::string s;
std::println("Hello, {}!", name);

Benefits over #include:

Compilation Speed:
- Modules are parsed once and reused
- No repeated header parsing
- Faster incremental builds
- Reduced template instantiation overhead

Code Quality:
- No macro pollution between translation units
- Better symbol visibility control
- Cleaner dependency graph
- Enhanced IDE support

Maintenance:
- Single import line instead of dozens of includes
- Automatic dependency tracking
- Better error messages
- Future-proof for standard library evolution

Compatibility:
- Can coexist with traditional #include
- Gradual migration possible
- Works with existing C++ code
- Binary compatibility maintained

Advanced Usage:
import std.core;      // Core utilities only
import std.io;        // I/O operations only
import std.threading; // Threading utilities only

Migration Strategy:
1. Ensure C++23 compiler support
2. Replace common includes with import std;
3. Test compilation and runtime behavior
4. Update build system if necessary
5. Gradually migrate entire codebase

Common Issues and Solutions:
- Compiler support: Use feature detection macros
- Build systems: Update CMake/Make files for modules
- Legacy code: Use compatibility headers
- Third-party libraries: May still require traditional includes

Best Practices:
- Use import std; for new projects
- Migrate incrementally for existing projects
- Keep build system updated for module support
- Use specific module imports when appropriate
- Test thoroughly during migration
- Document module usage for team members

Future Outlook:
- Standard library modules are the future
- Better tooling support coming
- Performance improvements continue
- Ecosystem adoption growing
- Essential for modern C++ development
*/
