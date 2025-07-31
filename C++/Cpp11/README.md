# C++11 Features - Complete Learning Guide

This folder contains comprehensive, runnable examples of major C++11 features. Each subfolder focuses on a specific C++11 enhancement with detailed explanations, practical examples, and compilation instructions.

## 📁 Folder Structure

```
Cpp11/
├── AutoKeyword/           # auto keyword and type deduction
├── ConstExpr/            # Compile-time constants and functions
├── InitializerList/       # Uniform initialization and initializer lists
├── Lambda/               # Lambda expressions and closures
├── MoveSemantics/        # Move semantics and rvalue references
├── NullptrKeyword/       # Type-safe null pointer
├── RangeBasedFor/        # Range-based for loops
├── ScopedEnums/          # Type-safe enumerations (enum class)
├── SmartPointers/        # Modern memory management
├── StaticAssert/         # Compile-time assertions
├── UnorderedContainers/  # Hash-based STL containers
└── README.md            # This file
```

## 🚀 Quick Start

Each example can be compiled and run independently:

```bash
# Navigate to any subfolder
cd AutoKeyword

# Compile the example
g++ -std=c++11 -Wall -Wextra -o demo auto_keyword_demo.cpp

# Run the example
./demo        # Linux/macOS
demo.exe      # Windows
```

## 📚 C++11 Features Covered

### 1. 🔧 [Auto Keyword](./AutoKeyword/)
**File:** `auto_keyword_demo.cpp`

Automatic type deduction that makes code more maintainable and less verbose.

```cpp
auto x = 42;              // int
auto pi = 3.14159;        // double
auto message = "Hello";   // const char*
```

**Key Benefits:**
- Cleaner code with complex types
- Better maintainability
- Perfect with templates and iterators

### 2. 🎯 [Range-Based For Loops](./RangeBasedFor/)
**File:** `range_based_for_demo.cpp`

Simplified iteration over containers and arrays.

```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5};
for (const auto& num : numbers) {
    std::cout << num << " ";
}
```

**Key Benefits:**
- Cleaner, more readable code
- Less error-prone than traditional loops
- Works with all STL containers

### 3. ⚡ [Lambda Expressions](./Lambda/)
**File:** `lambda_expressions_demo.cpp`

Anonymous functions with capture capabilities for functional programming.

```cpp
auto add = [](int a, int b) { return a + b; };
int result = add(5, 3);  // result = 8

// Capture by reference
int multiplier = 2;
auto multiply = [&multiplier](int x) { return x * multiplier; };
```

**Key Benefits:**
- Inline function definitions
- Powerful capture mechanisms
- Perfect for STL algorithms
- Closures support

### 4. 🧠 [Smart Pointers](./SmartPointers/)
**File:** `smart_pointers_demo.cpp`

Modern RAII-based memory management replacing raw pointers.

```cpp
// Automatic memory management
auto ptr = std::make_unique<int>(42);
auto shared = std::make_shared<int>(100);

// No manual delete needed!
```

**Types Covered:**
- `std::unique_ptr` - Exclusive ownership
- `std::shared_ptr` - Shared ownership  
- `std::weak_ptr` - Non-owning observer

### 5. 🔄 [Move Semantics](./MoveSemantics/)
**File:** `move_semantics_demo.cpp`

Efficient resource transfer using rvalue references and move operations.

```cpp
class Resource {
public:
    Resource(Resource&& other) noexcept {  // Move constructor
        data_ = other.data_;
        other.data_ = nullptr;  // Transfer ownership
    }
};

Resource r1 = std::move(r2);  // Efficient move, not copy
```

**Key Benefits:**
- Eliminates unnecessary copies
- Enables move-only types
- Significant performance improvements

### 6. 🎨 [Initializer Lists](./InitializerList/)
**File:** `initializer_list_demo.cpp`

Uniform initialization syntax for all types and containers.

```cpp
// Containers
std::vector<int> numbers{1, 2, 3, 4, 5};
std::map<string, int> ages{{"Alice", 30}, {"Bob", 25}};

// Custom classes
Point p{3.0, 4.0};
```

**Key Benefits:**
- Consistent initialization syntax
- Prevents narrowing conversions
- Direct aggregate initialization

### 7. 🛡️ [nullptr Keyword](./NullptrKeyword/)
**File:** `nullptr_demo.cpp`

Type-safe null pointer constant replacing NULL and 0.

```cpp
int* ptr = nullptr;        // Clear intent
if (ptr == nullptr) {      // Type-safe comparison
    // Handle null case
}
```

**Key Benefits:**
- Type safety in overload resolution
- Template compatibility
- Clear intent in code

### 8. ⚙️ [constexpr](./ConstExpr/)
**File:** `constexpr_demo.cpp`

Compile-time constants and functions for better performance.

```cpp
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr int result = factorial(5);  // Computed at compile time!
```

**Key Benefits:**
- Compile-time computation
- Template parameter compatibility
- Zero runtime cost
- Type safety

### 9. 🎭 [Scoped Enumerations](./ScopedEnums/)
**File:** `scoped_enums_demo.cpp`

Type-safe enumerations that don't pollute the global namespace.

```cpp
enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

Color c = Color::Red;     // Explicit scope
// if (c == Size::Small)  // Compile error - good!
```

**Key Benefits:**
- Type safety
- Namespace safety
- No implicit conversions
- Forward declaration support

### 10. ✅ [static_assert](./StaticAssert/)
**File:** `static_assert_demo.cpp`

Compile-time assertions for template and configuration validation.

```cpp
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

template<typename T>
class SafeArray {
    static_assert(std::is_arithmetic<T>::value, 
                  "SafeArray only supports arithmetic types");
    // ...
};
```

**Key Benefits:**
- Compile-time error detection
- Template parameter validation
- Zero runtime cost
- Self-documenting code

### 11. 🗂️ [Unordered Containers](./UnorderedContainers/)
**File:** `unordered_containers_demo.cpp`

Hash-based STL containers for O(1) average performance.

```cpp
std::unordered_set<int> fast_set;
std::unordered_map<std::string, int> word_count;

// Custom hash for user-defined types
std::unordered_set<Person, PersonHash> people;
```

**Key Containers:**
- `std::unordered_set` - Hash-based unique elements
- `std::unordered_map` - Hash-based key-value pairs
- `std::multiset` - Ordered duplicates allowed
- `std::multimap` - Ordered multiple key-value pairs

**Key Benefits:**
- O(1) average lookup performance
- Custom hash function support
- Bucket-based organization
- Performance advantages for large datasets

## 🛠️ Compilation Requirements

### Minimum Requirements
- **Compiler:** GCC 4.8+, Clang 3.3+, MSVC 2012+
- **Standard:** C++11 (`-std=c++11`)

### Recommended Setup
- **GCC 6.3+** (your current setup works!)
- **Compiler Flags:** `-Wall -Wextra -O2`

### Example Compilation Commands

```bash
# Basic compilation
g++ -std=c++11 -o demo example.cpp

# With warnings and optimization
g++ -std=c++11 -Wall -Wextra -O2 -o demo example.cpp

# Debug build
g++ -std=c++11 -Wall -Wextra -g -o demo example.cpp
```

## 🎯 Learning Path

### Beginner Level
1. **Auto Keyword** - Start with type deduction
2. **Range-Based For** - Simplify your loops
3. **nullptr** - Improve pointer safety
4. **Scoped Enums** - Type-safe enumerations

### Intermediate Level
5. **Initializer Lists** - Modern initialization
6. **Lambda Expressions** - Functional programming
7. **Smart Pointers** - Memory management
8. **constexpr** - Compile-time computation
9. **Unordered Containers** - Hash-based performance

### Advanced Level
10. **Move Semantics** - Performance optimization
11. **static_assert** - Template validation

## 🧪 Testing Your Knowledge

After studying each feature, try these challenges:

1. **Auto Challenge:** Rewrite old code using auto appropriately
2. **Lambda Challenge:** Replace function objects with lambdas
3. **Move Challenge:** Implement move semantics for a custom class
4. **Smart Pointer Challenge:** Convert raw pointer code to smart pointers
5. **constexpr Challenge:** Create compile-time mathematical functions
6. **Enum Class Challenge:** Replace traditional enums with scoped enums
7. **static_assert Challenge:** Add compile-time validation to templates
8. **Container Challenge:** Convert map/set code to unordered versions for performance
9. **Hash Function Challenge:** Implement custom hash functions for user types

## 🔗 Feature Interactions

Many C++11 features work together:

```cpp
// Auto + Lambda + Range-based for + Smart pointers + constexpr + enum class + unordered containers
enum class ProcessingMode { Sequential, Parallel };

constexpr int BUFFER_SIZE = 1024;

auto word_count = std::make_shared<std::unordered_map<std::string, int>>();
auto numbers = std::make_shared<std::vector<int>>(
    std::initializer_list<int>{1, 2, 3, 4, 5}
);

auto process = [word_count, numbers](int multiplier, ProcessingMode mode) {
    static_assert(BUFFER_SIZE > 0, "Buffer size must be positive");
    
    // Fast O(1) lookups with unordered_map
    (*word_count)["processed"]++;
    
    for (auto& num : *numbers) {
        num *= multiplier;
    }
    
    if (mode == ProcessingMode::Parallel) {
        // Parallel processing logic
    }
};

process(2, ProcessingMode::Sequential);
```

## 📈 Performance Notes

### Move Semantics
- **20-50% faster** for resource-heavy classes
- Essential for containers of large objects

### Range-Based For
- **Same performance** as traditional loops
- Better optimization opportunities

### Lambda vs Function Objects
- **Identical performance** when optimized
- Much cleaner code

### Smart Pointers
- **Minimal overhead** (~1-2% for reference counting)
- **Massive safety benefits** outweigh small cost

## 🔧 Troubleshooting

### Common Compilation Issues

```bash
# If you get "error: 'auto' does not name a type"
# Make sure you're using C++11:
g++ -std=c++11 your_file.cpp

# For lambda capture errors, check capture syntax:
[&]    # Capture all by reference
[=]    # Capture all by value  
[x, &y] # Capture x by value, y by reference
```

### GCC 6.3 Compatibility
All examples are tested with GCC 6.3 and work perfectly! 

## 🚀 Next Steps

After mastering these C++11 features:

1. **C++14:** `auto` return types, generic lambdas
2. **C++17:** `if constexpr`, structured bindings
3. **C++20:** Concepts, modules, coroutines

## 💡 Best Practices Summary

1. **Always use `auto`** for complex types and type deduction
2. **Prefer range-based for loops** over traditional iteration
3. **Use lambdas** instead of small function objects
4. **Always use smart pointers** instead of raw pointers for ownership
5. **Implement move semantics** for resource-managing classes
6. **Use `{}` initialization** everywhere possible
7. **Always use `nullptr`** instead of NULL or 0
8. **Use `constexpr`** for compile-time computations
9. **Prefer `enum class`** over traditional enums
10. **Add `static_assert`** for template parameter validation
11. **Use `unordered_map/set`** for fast lookups when order doesn't matter
12. **Implement custom hash functions** for user-defined types in unordered containers

## 🎉 Happy Learning!

Each example is designed to be:
- ✅ **Self-contained** - Runs independently
- ✅ **Well-commented** - Explains every concept
- ✅ **Practical** - Shows real-world usage
- ✅ **Complete** - Covers edge cases and best practices

Start with any feature that interests you most, and enjoy exploring modern C++!

---

*Created as part of the C++ Learning Playground*  
*Compatible with C++11 and all later standards*
