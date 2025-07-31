# Runtime Polymorphism in C++

## Overview

**Runtime polymorphism** (also known as **dynamic polymorphism**) is resolved during program execution. The actual function or method to be called is determined at runtime based on the type of the object, not the type of the pointer or reference. This is achieved through virtual functions and dynamic binding.

## Types of Runtime Polymorphism

### 1. **Virtual Functions**
- Functions that can be overridden in derived classes
- Resolved at runtime using vtable (virtual table)
- Enable polymorphic behavior through base class pointers/references

### 2. **Pure Virtual Functions**
- Virtual functions with no implementation in base class
- Make the base class abstract
- Must be implemented in derived classes

### 3. **Abstract Classes**
- Classes containing one or more pure virtual functions
- Cannot be instantiated directly
- Define interface contracts for derived classes

### 4. **Virtual Destructors**
- Ensure proper cleanup in inheritance hierarchies
- Critical for polymorphic base classes
- Prevent resource leaks

### 5. **Function Overriding**
- Redefining virtual functions in derived classes
- Uses `override` keyword for safety (C++11)
- Maintains same signature as base class

### 6. **Dynamic Binding**
- Function call resolution at runtime
- Based on actual object type, not pointer/reference type
- Implemented through vtable mechanism

### 7. **Type Identification**
- `typeid` operator for runtime type information
- `dynamic_cast` for safe downcasting
- RTTI (Run-Time Type Information)

## Key Concepts

### Virtual Table (VTable)
```cpp
// Each class with virtual functions has a vtable
class Base {
public:
    virtual void func() { /* implementation */ }
};

class Derived : public Base {
public:
    void func() override { /* overridden implementation */ }
};

// Runtime resolution:
Base* ptr = new Derived();
ptr->func(); // Calls Derived::func() via vtable lookup
```

### Memory Layout
- **VTable Pointer**: Each object contains pointer to class's vtable
- **VTable**: Array of function pointers for virtual functions
- **Runtime Overhead**: Small memory cost, function call indirection

### Dynamic Dispatch
```cpp
std::vector<std::unique_ptr<Animal>> animals;
animals.push_back(std::make_unique<Dog>());
animals.push_back(std::make_unique<Cat>());

for (auto& animal : animals) {
    animal->makeSound(); // Resolved at runtime based on actual type
}
```

## Comparison: Runtime vs Compile-Time Polymorphism

| Aspect | Runtime | Compile-Time |
|--------|---------|-------------|
| Resolution | Execution time | Compilation time |
| Performance | Small overhead | Zero overhead |
| Flexibility | High (dynamic) | Limited (static) |
| Memory Usage | VTable overhead | No extra memory |
| Type Safety | Runtime checks | Compile-time checks |
| Extensibility | Easy to extend | Requires recompilation |

## Files in this Directory

- `README.md` - This overview
- `virtual_functions.cpp` - Basic virtual function concepts
- `pure_virtual_abstract.cpp` - Abstract classes and pure virtual functions
- `virtual_destructors.cpp` - Proper cleanup in inheritance
- `function_overriding.cpp` - Function overriding techniques
- `dynamic_binding.cpp` - Runtime binding demonstrations
- `type_identification.cpp` - RTTI and type checking
- `polymorphic_containers.cpp` - Using polymorphism with containers
- `interface_design.cpp` - Designing interfaces with pure virtual functions
- `comprehensive_demo.cpp` - All concepts integrated
- `Makefile` - Build system for all examples

## Quick Compilation

```bash
# Compile individual examples
g++ -std=c++17 -Wall -Wextra virtual_functions.cpp -o virtual_functions
g++ -std=c++17 -Wall -Wextra dynamic_binding.cpp -o dynamic_binding

# Or use the provided Makefile
make all
make run-all
```

## Advanced Features

### Virtual Function Table Structure
```cpp
class Base {
    int data;
    virtual void func1();
    virtual void func2();
    // VTable: [&Base::func1, &Base::func2]
};

class Derived : public Base {
    virtual void func1() override;
    virtual void func3();
    // VTable: [&Derived::func1, &Base::func2, &Derived::func3]
};
```

### Multiple Inheritance and Virtual Functions
```cpp
class Interface1 {
public:
    virtual void method1() = 0;
    virtual ~Interface1() = default;
};

class Interface2 {
public:
    virtual void method2() = 0;
    virtual ~Interface2() = default;
};

class Implementation : public Interface1, public Interface2 {
public:
    void method1() override { /* implementation */ }
    void method2() override { /* implementation */ }
};
```

### CRTP vs Virtual Functions
```cpp
// CRTP (Compile-time)
template<typename Derived>
class CRTPBase {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

// Virtual Functions (Runtime)
class VirtualBase {
public:
    virtual void interface() = 0;
    virtual ~VirtualBase() = default;
};
```

## Performance Considerations

### Runtime Overhead
- **Virtual Function Call**: 1 extra indirection through vtable
- **VTable Pointer**: ~8 bytes per object (64-bit systems)
- **VTable Storage**: One table per class with virtual functions
- **Cache Impact**: Potential cache misses during virtual calls

### Optimization Techniques
- **Devirtualization**: Compiler optimization when type is known
- **Final Classes**: `final` keyword prevents further inheritance
- **Profile-Guided Optimization**: Better virtual call prediction
- **Template Specialization**: Avoid virtuals when possible

## Best Practices

### Do's ✅
- Use virtual destructors in polymorphic base classes
- Declare pure virtual functions for interface contracts
- Use `override` keyword for safety and clarity
- Prefer smart pointers for polymorphic objects
- Design interfaces with minimal virtual functions

### Don'ts ❌
- Don't call virtual functions in constructors/destructors
- Avoid deep inheritance hierarchies
- Don't mix virtual and non-virtual functions carelessly
- Avoid virtual functions in performance-critical inner loops
- Don't forget virtual destructors in base classes

## Memory Layout

### Object Layout with Virtual Functions
```
[VTable Pointer] -> [Class VTable]
[Member Data 1 ]    [Virtual Func 1 Ptr]
[Member Data 2 ]    [Virtual Func 2 Ptr]
[Member Data 3 ]    [Virtual Func 3 Ptr]
```

### Inheritance and VTables
```cpp
class Base {
    virtual void f1();
    virtual void f2();
}; // VTable: [f1, f2]

class Derived : public Base {
    void f1() override;
    virtual void f3();
}; // VTable: [Derived::f1, Base::f2, f3]
```

## Modern C++ Features

### C++11 Features
- `override` keyword for explicit overriding
- `final` keyword to prevent inheritance/overriding
- `nullptr` instead of NULL for pointer initialization
- Smart pointers for automatic memory management

### C++14 Features
- `std::make_unique` for unique pointer creation
- Generic lambdas with auto parameters
- Variable templates

### C++17 Features
- Structured bindings
- `if constexpr` for conditional compilation
- Fold expressions

### C++20 Features
- Concepts for constraining templates
- Modules for better compilation
- Coroutines for asynchronous programming

## Design Patterns Using Runtime Polymorphism

### Strategy Pattern
```cpp
class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0;
    virtual ~SortStrategy() = default;
};

class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        // Quick sort implementation
    }
};
```

### Observer Pattern
```cpp
class Observer {
public:
    virtual void update(const Event& event) = 0;
    virtual ~Observer() = default;
};

class Subject {
    std::vector<Observer*> observers;
public:
    virtual void notify(const Event& event) {
        for (auto* observer : observers) {
            observer->update(event);
        }
    }
};
```

### Factory Pattern
```cpp
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() = default;
};

class Factory {
public:
    virtual std::unique_ptr<Product> createProduct() = 0;
    virtual ~Factory() = default;
};
```

## Common Pitfalls

### Virtual Function in Constructor
```cpp
class Base {
public:
    Base() {
        init(); // Calls Base::init, not derived version!
    }
    virtual void init() { /* base initialization */ }
};
```

### Slicing Problem
```cpp
void processAnimal(Animal animal) { // Pass by value!
    animal.makeSound(); // Always calls Animal::makeSound
}

// Correct:
void processAnimal(const Animal& animal) { // Pass by reference
    animal.makeSound(); // Calls correct derived version
}
```

### Missing Virtual Destructor
```cpp
class Base {
public:
    ~Base() { /* cleanup */ } // Should be virtual!
};

Base* ptr = new Derived();
delete ptr; // Undefined behavior - Derived destructor not called
```

---

*Explore each file to understand different runtime polymorphism techniques and their practical applications in object-oriented design!*
