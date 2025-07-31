# Compile-Time Polymorphism in C++

## Overview

**Compile-time polymorphism** (also known as **static polymorphism**) is resolved during compilation. The compiler determines which function or operation to call based on the types and parameters known at compile time. This results in zero runtime overhead and optimal performance.

## Types of Compile-Time Polymorphism

### 1. **Function Overloading**
- Multiple functions with the same name but different parameters
- Resolved based on function signature
- No runtime overhead

### 2. **Operator Overloading**
- Custom behavior for operators (+, -, *, etc.)
- Enables intuitive syntax for user-defined types
- Resolved at compile time

### 3. **Template Functions**
- Generic functions that work with multiple types
- Code generation at compile time
- Type safety with performance

### 4. **Template Classes**
- Generic classes for type-agnostic containers and algorithms
- Specialization for specific types
- Compile-time code generation

### 5. **Template Specialization**
- Custom implementations for specific types
- Partial and full specialization
- Optimization for particular cases

### 6. **SFINAE (Substitution Failure Is Not An Error)**
- Template metaprogramming technique
- Conditional compilation based on type traits
- Enable/disable functions based on type properties

### 7. **Constexpr and Constant Expressions**
- Compile-time computation
- Values and functions evaluated at compile time
- Performance optimization

### 8. **Auto Type Deduction**
- Automatic type inference
- Template argument deduction
- Simplified generic programming

## Key Concepts

### Resolution Time
```cpp
// Compile-time resolution
template<typename T>
T add(T a, T b) { return a + b; }

// Call resolved at compile time:
int result = add(5, 3);        // add<int> generated
double result2 = add(5.5, 3.2); // add<double> generated
```

### Performance Benefits
- **Zero Runtime Overhead**: Function calls resolved at compile time
- **Optimal Code Generation**: Compiler can inline and optimize
- **Type Safety**: Errors caught at compilation
- **Memory Efficiency**: No virtual table overhead

### Type Safety
```cpp
template<typename T>
void processValue(T value) {
    static_assert(std::is_arithmetic_v<T>, "Type must be arithmetic");
    // Compile-time check ensures only numeric types are used
}
```

## Comparison: Compile-Time vs Runtime Polymorphism

| Aspect | Compile-Time | Runtime |
|--------|-------------|---------|
| Resolution | Compilation | Execution |
| Performance | Optimal (no overhead) | Small overhead |
| Flexibility | Static binding | Dynamic binding |
| Type Safety | Compile-time errors | Runtime errors possible |
| Code Size | Larger (code generation) | Smaller |
| Memory Usage | No vtable | Vtable overhead |

## Files in this Directory

- `README.md` - This overview
- `function_overloading.cpp` - Function overloading examples
- `operator_overloading.cpp` - Custom operators for classes
- `template_functions.cpp` - Generic function templates
- `template_classes.cpp` - Generic class templates
- `template_specialization.cpp` - Template specialization techniques
- `sfinae_concepts.cpp` - SFINAE and type traits
- `constexpr_programming.cpp` - Compile-time computation
- `auto_deduction.cpp` - Automatic type deduction
- `comprehensive_demo.cpp` - All concepts together
- `Makefile` - Build system for all examples

## Quick Compilation

```bash
# Compile individual examples
g++ -std=c++17 -Wall -Wextra function_overloading.cpp -o function_overloading
g++ -std=c++17 -Wall -Wextra template_functions.cpp -o template_functions

# Or use the provided Makefile
make all
make run-all
```

## Advanced Features

### Template Metaprogramming
```cpp
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

// Computed at compile time
constexpr int fact5 = Factorial<5>::value; // 120
```

### CRTP (Curiously Recurring Template Pattern)
```cpp
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() { /* specific implementation */ }
};
```

### Variadic Templates
```cpp
template<typename... Args>
void print(Args... args) {
    ((std::cout << args << " "), ...); // C++17 fold expression
}

print(1, "hello", 3.14, 'c'); // Accepts any number of arguments
```

## Best Practices

### Do's ✅
- Use templates for type-agnostic algorithms
- Leverage SFINAE for conditional compilation
- Use constexpr for compile-time computation
- Prefer function overloading for related operations
- Use auto for complex type deduction

### Don'ts ❌
- Don't overuse template specialization
- Avoid complex template metaprogramming when simple solutions exist
- Don't ignore compilation time impact
- Avoid operator overloading for non-intuitive operations
- Don't sacrifice readability for template tricks

## Performance Considerations

### Compilation Time
- Templates increase compilation time
- Instantiation for each type combination
- Consider explicit instantiation for commonly used types

### Code Size
- Template instantiation can increase binary size
- Multiple instantiations of the same template
- Linker optimization helps reduce duplication

### Runtime Performance
- Zero overhead abstraction
- Optimal inlining opportunities
- Better optimization potential than virtual functions

## Modern C++ Features

### C++11 Features
- `auto` keyword for type deduction
- Variadic templates
- `constexpr` functions
- `decltype` for type inference

### C++14 Features
- Variable templates
- Generic lambdas
- Extended constexpr

### C++17 Features
- `if constexpr` for conditional compilation
- Fold expressions for variadic templates
- Template argument deduction for class templates

### C++20 Features
- Concepts for constraining templates
- `consteval` for immediate functions
- Template syntax improvements

---

*Explore each file to understand different compile-time polymorphism techniques and their practical applications!*
