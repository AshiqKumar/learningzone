# C++23 Features Collection

A comprehensive showcase of C++23 language and library features with practical examples and detailed explanations.

## 📁 Collection Contents

### 🔧 Language Features

#### [1. If Consteval](./IfConsteval/)
**Compile-time vs Runtime Detection**
- `if consteval` branching for compile-time context detection
- Different algorithms for compile-time vs runtime execution
- Performance optimization strategies
- Consteval context propagation

```cpp
if consteval {
    // Compile-time only code
    return compile_time_algorithm(x);
} else {
    // Runtime code
    return runtime_algorithm(x);
}
```

#### [2. Multidimensional Subscript Operator](./MultidimensionalSubscript/)
**Natural Syntax for Multi-dimensional Access**
- `operator[](x, y, z)` syntax support
- Matrix and tensor operations
- Game board representations
- Image processing applications

```cpp
class Matrix {
    auto operator[](size_t row, size_t col) -> double& {
        return data[row * cols + col];
    }
};

Matrix m(3, 3);
m[1, 2] = 42.0;  // Natural 2D access
```

#### [3. Auto Deducing from Braced Initialization](./AutoDeducingFromBracedInit/)
**Enhanced Auto Deduction Rules**
- Improved CTAD (Class Template Argument Deduction)
- Enhanced lambda parameter deduction
- Aggregate initialization improvements
- Performance comparisons with explicit types

```cpp
auto values = {1, 2, 3, 4, 5};  // std::initializer_list<int>
auto lambda = []<typename T>(T&& value) { /* Generic lambda */ };
```

### 📚 Library Features

#### [4. std::expected](./StdExpected/)
**Type-safe Error Handling Without Exceptions**
- Monadic operations (`and_then`, `or_else`, `transform`)
- Error propagation patterns
- Performance benefits over exceptions
- Integration with existing error handling

```cpp
std::expected<double, Error> divide(double a, double b) {
    if (b == 0.0) return std::unexpected(Error::DIVISION_BY_ZERO);
    return a / b;
}

auto result = divide(10, 2)
    .and_then([](double x) { return safe_sqrt(x); })
    .transform([](double x) { return x * 2; });
```

#### [5. std::mdspan](./StdMdspan/)
**Multidimensional Array Views**
- Zero-overhead multidimensional arrays
- Different memory layouts (row/column major)
- Subarray operations with `submdspan`
- Custom memory access patterns

```cpp
std::vector<int> data(12);
std::mdspan<int, std::dextents<size_t, 2>> matrix(data.data(), 3, 4);
int value = matrix[i, j];  // Type-safe 2D access

auto submatrix = std::submdspan(matrix, std::pair{1, 3}, std::pair{1, 4});
```

#### [6. std::print and std::println](./StdPrint/)
**Modern Text Formatting**
- Type-safe formatted output
- Better performance than iostream
- Unicode support
- Custom formatter integration

```cpp
std::print("Value: {}\n", 42);
std::println("Name: {}, Age: {}", name, age);

// Custom formatting
std::println("Point: {:.2f}", my_point);  // Uses custom formatter
```

#### [7. import std](./ImportStd/)
**Standard Library Modules**
- Single import statement for entire standard library
- Faster compilation through pre-compiled modules
- Better dependency management
- Protection from macro pollution

```cpp
import std;  // Replaces dozens of #include statements

// All std components now available
std::vector<int> v;
std::println("Hello, {}!", name);
```

## 🚀 Quick Start

### Prerequisites
- C++23 compatible compiler:
  - GCC 13+ with `-std=c++23`
  - Clang 16+ with `-std=c++23`
  - MSVC 2022 17.6+ with `/std:c++23`

### Building Examples

Each feature directory contains standalone examples:

```bash
# Navigate to any feature directory
cd IfConsteval

# Compile with C++23 support
g++ -std=c++23 -Wall -Wextra -O2 -o demo if_consteval_demo.cpp

# Run the demonstration
./demo
```

### Compilation Commands by Feature

```bash
# If Consteval
g++ -std=c++23 -o if_consteval_demo if_consteval_demo.cpp

# Multidimensional Subscript
g++ -std=c++23 -o multidim_demo multidimensional_subscript_demo.cpp

# Auto Deduction
g++ -std=c++23 -o auto_demo auto_braced_demo.cpp

# std::expected
g++ -std=c++23 -o expected_demo expected_demo.cpp

# std::mdspan
g++ -std=c++23 -o mdspan_demo mdspan_demo.cpp

# std::print
g++ -std=c++23 -o print_demo print_demo.cpp

# import std (if supported)
g++ -std=c++23 -fmodules-ts -o import_demo import_demo.cpp
```

## 🎯 Learning Path

### Beginner Track
1. **Start with [std::print](./StdPrint/)** - Modern output formatting
2. **Explore [std::expected](./StdExpected/)** - Error handling without exceptions
3. **Try [Auto Deduction](./AutoDeducingFromBracedInit/)** - Enhanced type inference

### Intermediate Track
4. **Learn [if consteval](./IfConsteval/)** - Compile-time programming
5. **Master [std::mdspan](./StdMdspan/)** - Multidimensional arrays
6. **Understand [Multidimensional Subscript](./MultidimensionalSubscript/)** - Operator overloading

### Advanced Track
7. **Study [import std](./ImportStd/)** - Module system integration
8. **Combine features** - Build comprehensive applications
9. **Performance optimization** - Benchmark against older approaches

## 🔍 Key C++23 Improvements

### Performance Enhancements
- **Zero-cost abstractions**: `std::mdspan`, `std::expected`
- **Compile-time optimizations**: `if consteval`, enhanced constexpr
- **Module system**: Faster builds with `import std`

### Developer Experience
- **Type safety**: `std::expected`, `std::mdspan` bounds checking
- **Expressiveness**: Multidimensional subscript, enhanced auto
- **Consistency**: Unified formatting with `std::print`

### Modern C++ Patterns
- **Functional programming**: Monadic operations in `std::expected`
- **Generic programming**: Enhanced template deduction
- **Systems programming**: Safe multidimensional array access

## 🛠️ Practical Applications

### Scientific Computing
```cpp
// Matrix operations with std::mdspan
std::mdspan<double, std::dextents<size_t, 2>> matrix(data.data(), rows, cols);
auto result = matrix_multiply(A, B, C);
```

### Error Handling
```cpp
// Chain operations with std::expected
auto pipeline = parse_input()
    .and_then(validate)
    .and_then(process)
    .or_else(handle_error);
```

### Performance-Critical Code
```cpp
// Compile-time vs runtime optimization
if consteval {
    return compile_time_optimized_version();
} else {
    return runtime_version();
}
```

### Modern I/O
```cpp
// Type-safe formatting
std::println("Processing {} items at {:.2f}% completion", count, percentage);
```

## 📊 Performance Characteristics

| Feature | Compile-time Impact | Runtime Performance | Memory Usage |
|---------|-------------------|-------------------|-------------|
| `if consteval` | ➕ Better optimization | ➕ Optimal paths | ➡️ Same |
| `std::expected` | ➡️ Similar to exceptions | ➕ Faster than exceptions | ➖ Slightly higher |
| `std::mdspan` | ➡️ Template heavy | ➕ Zero overhead | ➕ Minimal |
| `std::print` | ➖ Template instantiation | ➕ Faster than iostream | ➡️ Similar |
| `import std` | ➕ Much faster | ➡️ Identical | ➡️ Same |

## 🔄 Migration Guide

### From C++20 to C++23

1. **Replace iostream with std::print**:
   ```cpp
   // Before
   std::cout << "Value: " << value << std::endl;
   
   // After  
   std::println("Value: {}", value);
   ```

2. **Upgrade error handling to std::expected**:
   ```cpp
   // Before
   std::optional<T> maybe_parse(const std::string& input);
   
   // After
   std::expected<T, ParseError> maybe_parse(const std::string& input);
   ```

3. **Use import std for new projects**:
   ```cpp
   // Before
   #include <iostream>
   #include <vector>
   #include <algorithm>
   
   // After
   import std;
   ```

### Compatibility Considerations
- All C++23 features are **additive** - existing code continues to work
- **Gradual adoption** possible - mix old and new approaches
- **Compiler support** varies - check feature availability
- **Build systems** may need updates for modules

## 🧪 Testing and Validation

Each example includes:
- ✅ **Comprehensive demonstrations** of feature capabilities
- ✅ **Performance benchmarks** against traditional approaches
- ✅ **Error handling** and edge case coverage
- ✅ **Best practice examples** and common patterns
- ✅ **Real-world applications** and use cases

## 📈 Compiler Support Status

| Compiler | Version | Support Level | Notes |
|----------|---------|---------------|-------|
| **GCC** | 13+ | ⭐⭐⭐⭐ Good | Most features supported |
| **Clang** | 16+ | ⭐⭐⭐ Fair | Growing support |
| **MSVC** | 2022 17.6+ | ⭐⭐⭐⭐⭐ Excellent | Best C++23 support |

### Feature-Specific Support
- ✅ `std::expected`: Widely supported
- ✅ `std::mdspan`: Good support in recent versions
- ⚠️ `std::print`: Limited support, may need polyfills
- ⚠️ `import std`: Experimental, varies by compiler
- ✅ Language features: Generally well supported

## 🎓 Educational Resources

### Documentation Structure
Each feature directory contains:
- **`README.md`**: Detailed feature documentation
- **`*_demo.cpp`**: Comprehensive working examples
- **Inline comments**: Explaining complex concepts
- **Compilation instructions**: Platform-specific guidance

### Learning Objectives
- Understand **when and why** to use each feature
- Master **best practices** and common patterns
- Learn **performance implications** of different approaches
- Develop **modern C++** programming skills

## 🚀 Future Roadmap

C++23 sets the foundation for:
- **C++26 features**: Reflection, pattern matching, more ranges
- **Module ecosystem**: Third-party library modules
- **Tool improvements**: Better IDE support, static analysis
- **Performance evolution**: Continued optimization opportunities

## 🤝 Contributing

This collection demonstrates:
- **Production-ready** patterns and practices
- **Educational** progression from basic to advanced
- **Practical** real-world applications
- **Comprehensive** coverage of major features

## 📝 Summary

C++23 represents a significant evolution in C++ development:

### Major Themes
1. **Performance**: Zero-cost abstractions with better optimization
2. **Safety**: Type-safe alternatives to unsafe practices  
3. **Expressiveness**: More natural syntax for complex operations
4. **Modularity**: Modern dependency management
5. **Consistency**: Unified approach to common tasks

### Adoption Strategy
- **New projects**: Use C++23 features from the start
- **Existing codebases**: Gradual migration with compatibility layers
- **Performance-critical code**: Leverage compile-time optimizations
- **Team training**: Focus on practical patterns and best practices

C++23 continues C++'s tradition of **zero-cost abstractions** while significantly improving **developer productivity** and **code safety**. This collection provides the foundation for mastering these powerful new capabilities.

---

**Happy Coding with C++23! 🎉**

*Each example is self-contained and thoroughly commented. Start with any feature that interests you most!*
