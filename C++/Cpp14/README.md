# C++14 Features Collection

This directory contains comprehensive examples of all major C++14 features with detailed explanations and practical demonstrations.

## Directory Structure

### 1. AutoReturnType/
**Function return type deduction**
- `auto_return_demo.cpp` - Complete demonstration of automatic return type deduction
- Features: auto return types, template functions, recursive functions, member functions
- Use cases: Generic programming, template metaprogramming, complex STL operations

### 2. GenericLambdas/
**Generic lambda expressions with auto parameters**
- `generic_lambdas_demo.cpp` - Comprehensive lambda examples with auto parameters
- Features: Auto parameters, STL integration, perfect forwarding, type traits
- Use cases: Functional programming, algorithm customization, generic utilities

### 3. BinaryLiterals/
**Binary literals and digit separators**
- `binary_literals_demo.cpp` - Binary number representation and formatting
- Features: 0b prefix, digit separators ('), bit manipulation, flags
- Use cases: Hardware programming, bit operations, protocol implementations

### 4. MakeUnique/
**std::make_unique smart pointer factory**
- `make_unique_demo.cpp` - Safe unique_ptr creation and exception safety
- Features: Exception-safe construction, perfect forwarding, factory patterns
- Use cases: RAII, resource management, memory safety

### 5. ExtendedConstexpr/
**Relaxed constexpr constraints**
- `extended_constexpr_demo.cpp` - Complex compile-time computations
- Features: Loops, conditionals, local variables, complex algorithms
- Use cases: Compile-time calculations, template metaprogramming, performance optimization

### 6. VariableTemplates/
**Template variables and type traits**
- `variable_templates_demo.cpp` - Template variables and compile-time constants
- Features: Template variables, type traits (_v suffix), mathematical constants
- Use cases: Generic programming, type introspection, compile-time configuration

### 7. AggregateInitialization/
**Enhanced aggregate initialization**
- `aggregate_init_demo.cpp` - Improved initialization for aggregate types
- Features: Brace initialization, nested aggregates, partial initialization
- Use cases: Data structures, configuration objects, POD types

## Key C++14 Improvements

### Language Features
1. **Auto Return Type Deduction**: Functions can deduce return types automatically
2. **Generic Lambdas**: Lambda expressions with `auto` parameters
3. **Extended Constexpr**: Relaxed constraints allowing loops and conditions
4. **Variable Templates**: Template variables for cleaner type traits
5. **Binary Literals**: Direct binary representation with `0b` prefix
6. **Digit Separators**: Use `'` to separate digits for readability

### Library Features
1. **std::make_unique**: Factory function for unique_ptr creation
2. **Enhanced Aggregates**: Better support for aggregate initialization
3. **Type Traits Improvements**: Foundation for `_v` suffix traits
4. **Compile-time Utilities**: Better constexpr support

## Compilation Instructions

All examples require C++14 standard:

```bash
# Individual compilation
g++ -std=c++14 -Wall -Wextra -o demo_name file_name.cpp

# Examples:
g++ -std=c++14 -o auto_demo AutoReturnType/auto_return_demo.cpp
g++ -std=c++14 -o lambda_demo GenericLambdas/generic_lambdas_demo.cpp
g++ -std=c++14 -o binary_demo BinaryLiterals/binary_literals_demo.cpp
```

## Learning Path

### Beginner (Start Here)
1. **BinaryLiterals/** - Learn new literal syntax
2. **MakeUnique/** - Understand smart pointer improvements
3. **AggregateInitialization/** - Master initialization syntax

### Intermediate
1. **AutoReturnType/** - Function return type deduction
2. **GenericLambdas/** - Advanced lambda expressions
3. **ExtendedConstexpr/** - Compile-time programming

### Advanced
1. **VariableTemplates/** - Template metaprogramming
2. **Combined Examples** - Using multiple features together

## Practical Applications

### System Programming
- Binary literals for hardware registers
- Constexpr for compile-time calculations
- make_unique for safe resource management

### Generic Programming
- Auto return types for template functions
- Variable templates for type traits
- Generic lambdas for algorithm customization

### Performance Programming
- Extended constexpr for compile-time computation
- Aggregate initialization for efficient data structures
- Template variables for zero-cost abstractions

## C++14 vs Previous Standards

### vs C++11
- **More Flexible**: Relaxed constexpr, auto return types
- **Cleaner Syntax**: Generic lambdas, variable templates
- **Safer**: make_unique, better aggregate initialization

### vs C++98/03
- **Modern Features**: All the benefits of C++11 plus C++14 improvements
- **Better Performance**: Compile-time programming capabilities
- **Safer Code**: Smart pointers, RAII improvements

## Best Practices

1. **Use make_unique** instead of raw new
2. **Leverage auto** for return types in template contexts
3. **Use binary literals** for bit manipulation code
4. **Apply constexpr** for compile-time calculations
5. **Adopt generic lambdas** for flexible algorithms
6. **Utilize variable templates** for cleaner type traits

## Common Patterns

### Factory Functions
```cpp
auto create_resource() {
    return std::make_unique<Resource>();
}
```

### Generic Algorithms
```cpp
auto generic_transform = [](auto container, auto func) {
    // Transform using generic lambda
};
```

### Compile-time Constants
```cpp
template<typename T>
constexpr bool is_numeric_v = std::is_arithmetic<T>::value;
```

### Bit Manipulation
```cpp
constexpr auto FLAGS = 0b1010'0101'1100'0011;
```

Each directory contains complete, runnable examples with detailed explanations and practical use cases. The code is designed to be educational and demonstrates real-world applications of C++14 features.
