# C++ Inheritance

## Overview

**Inheritance** is one of the fundamental principles of Object-Oriented Programming (OOP) that allows a class to inherit properties and methods from another class. It enables code reusability, establishes relationships between classes, and supports polymorphism.

## Types of Inheritance

### 1. **Single Inheritance**
- One derived class inherits from one base class
- Simplest form of inheritance
- Forms a single chain: Base → Derived

### 2. **Multiple Inheritance**
- One derived class inherits from multiple base classes
- Can lead to diamond problem
- Requires careful design

### 3. **Multilevel Inheritance**
- Inheritance in multiple levels
- Chain of inheritance: A → B → C
- Each class inherits from the previous one

### 4. **Hierarchical Inheritance**
- Multiple derived classes inherit from single base class
- Tree-like structure with one root
- Common base functionality shared

### 5. **Hybrid Inheritance**
- Combination of multiple inheritance types
- Most complex form
- May involve virtual inheritance

## Access Specifiers in Inheritance

```cpp
class Base {
public:    // Accessible everywhere
protected: // Accessible in derived classes
private:   // Not accessible in derived classes
};

class Derived : public Base {
    // public inheritance - most common
    // protected inheritance - rare
    // private inheritance - composition-like
};
```

## Inheritance Access Rules

| Base Class Member | Public Inheritance | Protected Inheritance | Private Inheritance |
|-------------------|-------------------|----------------------|-------------------|
| public            | public            | protected            | private           |
| protected         | protected         | protected            | private           |
| private           | Not accessible    | Not accessible       | Not accessible    |

## Key Concepts

### Virtual Functions
- Enable runtime polymorphism
- Resolved at runtime (dynamic binding)
- Use `virtual` keyword

### Pure Virtual Functions
- Abstract functions with no implementation
- Make class abstract
- Syntax: `virtual void func() = 0;`

### Virtual Inheritance
- Solves diamond problem in multiple inheritance
- Ensures single instance of base class
- Use `virtual` keyword in inheritance

### Constructor/Destructor Order
- **Construction**: Base → Derived
- **Destruction**: Derived → Base
- Virtual destructors for proper cleanup

## Design Principles

### Liskov Substitution Principle (LSP)
- Derived class objects should be substitutable for base class objects
- Maintains program correctness

### Interface Segregation
- Prefer small, focused interfaces
- Use pure virtual functions for contracts

### Composition vs Inheritance
- **Inheritance**: "is-a" relationship
- **Composition**: "has-a" relationship
- Prefer composition when possible

## Memory Layout

```
┌─────────────────────────────────────────┐
│                OBJECT LAYOUT            │
├─────────────────────────────────────────┤
│  VTABLE PTR   │ Pointer to virtual table │
├─────────────────────────────────────────┤
│  BASE DATA    │ Base class members       │
├─────────────────────────────────────────┤
│  DERIVED DATA │ Derived class members    │
└─────────────────────────────────────────┘
```

## Files in this Directory

- `README.md` - This overview
- `single_inheritance.cpp` - Single inheritance examples
- `multiple_inheritance.cpp` - Multiple inheritance and diamond problem
- `multilevel_inheritance.cpp` - Chain of inheritance
- `hierarchical_inheritance.cpp` - Multiple classes from one base
- `hybrid_inheritance.cpp` - Complex inheritance combinations
- `virtual_inheritance.cpp` - Virtual inheritance solutions
- `polymorphism_demo.cpp` - Virtual functions and dynamic binding
- `abstract_classes.cpp` - Pure virtual functions and interfaces
- `pointer_conversion_demo.cpp` - Safe upcasting and downcasting examples
- `comprehensive_inheritance.cpp` - All concepts together
- `Makefile` - Build system for all examples

## Quick Compilation

```bash
# Compile individual examples
g++ -std=c++17 -Wall -Wextra single_inheritance.cpp -o single_inheritance
g++ -std=c++17 -Wall -Wextra multiple_inheritance.cpp -o multiple_inheritance

# Or use the provided Makefile
make all
make run-all
```

## Best Practices

### Do's ✅
- Use `virtual` destructors in base classes
- Keep inheritance hierarchies shallow
- Favor composition over inheritance
- Use pure virtual functions for contracts
- Follow Liskov Substitution Principle

### Don'ts ❌
- Avoid deep inheritance chains (>3-4 levels)
- Don't make everything virtual
- Avoid multiple inheritance without virtual inheritance
- Don't inherit for code reuse alone
- Avoid protected data members

## Common Patterns

### Template Method Pattern
```cpp
class Algorithm {
public:
    void execute() {
        step1();
        step2();  // Template method
        step3();
    }
protected:
    virtual void step2() = 0;  // Customization point
private:
    void step1() { /* ... */ }
    void step3() { /* ... */ }
};
```

### Strategy Pattern
```cpp
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void execute() = 0;
};

class Context {
    std::unique_ptr<Strategy> strategy;
public:
    void setStrategy(std::unique_ptr<Strategy> s) {
        strategy = std::move(s);
    }
    void executeStrategy() {
        strategy->execute();
    }
};
```

## Performance Considerations

### Virtual Function Overhead
- Small runtime cost for virtual calls
- Vtable lookup + indirect call
- Modern CPUs handle well

### Memory Layout
- Virtual functions add vtable pointer
- Multiple inheritance can increase size
- Virtual inheritance has additional overhead

### Optimization Tips
- Use `final` keyword to prevent further inheritance
- Use `override` keyword for safety
- Consider devirtualization optimizations

---

*Explore each file to understand different inheritance types and their practical applications!*
