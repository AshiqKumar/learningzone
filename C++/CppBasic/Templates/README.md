# C++ Templates

## Overview

**Templates** in C++ provide a way to write generic code that works with different data types. They enable **compile-time polymorphism** and are fundamental to generic programming.

## Types of Templates

### 1. **Function Templates**
- Generic functions that work with multiple data types
- Template parameters are deduced from function arguments
- Instantiated at compile-time for each type used

### 2. **Class Templates**
- Generic classes that can work with different data types
- Template parameters must be explicitly specified
- Enable creation of generic containers and data structures

## Basic Syntax

### Function Template
```cpp
template<typename T>
T add(T a, T b) {
    return a + b;
}
```

### Class Template
```cpp
template<typename T>
class Container {
private:
    T data;
public:
    Container(T value) : data(value) {}
    T getValue() const { return data; }
};
```

## Template Instantiation

```cpp
// Function template usage
int result1 = add(5, 3);        // Instantiates add<int>
double result2 = add(2.5, 1.5); // Instantiates add<double>

// Class template usage
Container<int> intContainer(42);       // Explicit instantiation
Container<string> stringContainer("Hello"); // Different type
```

## Key Benefits

- **Code Reusability**: Write once, use with multiple types
- **Type Safety**: Compile-time type checking
- **Performance**: No runtime overhead
- **Flexibility**: Generic algorithms and data structures

## Files in this Directory

- `README.md` - This overview
- `function_templates.cpp` - Simple function template examples
- `class_templates.cpp` - Simple class template examples

## Quick Compilation

```bash
# Compile examples
g++ -std=c++17 -Wall -Wextra function_templates.cpp -o function_templates
g++ -std=c++17 -Wall -Wextra class_templates.cpp -o class_templates

# Run examples
./function_templates
./class_templates
```

---

*Simple and clear examples to understand C++ template basics!*
