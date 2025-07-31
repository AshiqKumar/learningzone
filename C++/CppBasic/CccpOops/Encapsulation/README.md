# Encapsulation in C++

## Overview

**Encapsulation** is one of the fundamental principles of Object-Oriented Programming (OOP). It refers to the bundling of data (attributes) and methods (functions) that operate on that data into a single unit (class), while restricting direct access to some of the object's components. This is achieved through access control mechanisms.

## Key Concepts

### What is Encapsulation?
Encapsulation involves two main aspects:
1. **Data Hiding**: Restricting direct access to internal data members
2. **Interface Definition**: Providing controlled access through public methods

### Benefits of Encapsulation
- **Data Protection**: Prevents unauthorized access and modification
- **Modularity**: Code is organized into logical units
- **Maintainability**: Internal implementation can change without affecting external code
- **Validation**: Input validation can be enforced through setter methods
- **Abstraction**: Users interact with simplified interfaces rather than complex internals

## Access Specifiers in C++

### 1. **Private**
- Members are accessible only within the same class
- Default access level for class members
- Provides the strongest encapsulation

### 2. **Protected**
- Members are accessible within the same class and derived classes
- Used in inheritance hierarchies
- Balances encapsulation with inheritance needs

### 3. **Public**
- Members are accessible from anywhere in the program
- Forms the public interface of the class
- Should be minimized to maintain encapsulation

## Encapsulation Techniques

### 1. **Data Hiding**
```cpp
class BankAccount {
private:
    double balance;  // Hidden from external access
    
public:
    void deposit(double amount);    // Controlled access
    double getBalance() const;      // Read-only access
};
```

### 2. **Getter and Setter Methods**
```cpp
class Person {
private:
    std::string name;
    int age;
    
public:
    // Getters (Accessors)
    std::string getName() const { return name; }
    int getAge() const { return age; }
    
    // Setters (Mutators)
    void setName(const std::string& newName) { name = newName; }
    void setAge(int newAge) { 
        if (newAge >= 0) age = newAge; 
    }
};
```

### 3. **Const Correctness**
```cpp
class Rectangle {
private:
    double width, height;
    
public:
    double getArea() const {  // Const method - doesn't modify object
        return width * height;
    }
    
    void setDimensions(double w, double h) {  // Non-const - modifies object
        width = w;
        height = h;
    }
};
```

### 4. **Friend Functions and Classes**
```cpp
class Secret {
private:
    int hiddenValue;
    
    friend class TrustedClass;           // Friend class
    friend void trustedFunction(Secret&); // Friend function
};
```

## Design Patterns Supporting Encapsulation

### 1. **Singleton Pattern**
- Ensures single instance with controlled access
- Encapsulates instance creation logic

### 2. **Factory Pattern**
- Encapsulates object creation process
- Hides complex construction logic

### 3. **Pimpl Idiom (Pointer to Implementation)**
- Separates interface from implementation
- Reduces compilation dependencies

### 4. **Property Pattern**
- Provides property-like access to private members
- Combines getter/setter functionality

## Files in this Directory

- `README.md` - This overview
- `basic_encapsulation.cpp` - Basic data hiding and access control
- `getters_setters.cpp` - Accessor and mutator methods
- `const_correctness.cpp` - Const methods and immutability
- `friend_functions.cpp` - Friend functions and classes
- `validation_encapsulation.cpp` - Input validation and data integrity
- `pimpl_idiom.cpp` - Pointer to Implementation pattern
- `property_pattern.cpp` - Property-like access mechanisms
- `encapsulation_inheritance.cpp` - Encapsulation in inheritance
- `comprehensive_demo.cpp` - All concepts integrated
- `Makefile` - Build system for all examples

## Quick Compilation

```bash
# Compile individual examples
g++ -std=c++17 -Wall -Wextra basic_encapsulation.cpp -o basic_encapsulation
g++ -std=c++17 -Wall -Wextra getters_setters.cpp -o getters_setters

# Or use the provided Makefile
make all
make run-all
```

## Encapsulation vs Other OOP Principles

| Principle       | Purpose                        | Relationship to Encapsulation                                 |
|-----------------|--------------------------------|---------------------------------------------------------------|
| **Inheritance** | Code reuse, IS-A relationships | Uses protected/private members to control access in hierarchies |
| **Polymorphism**| Runtime behavior variation     | Relies on public virtual interfaces, hides implementation details |
| **Abstraction** | Simplifies complex systems     | Achieved via encapsulation by exposing only necessary details   |


## Best Practices

### Do's ✅
- Keep data members private by default
- Provide public methods for controlled access
- Use const methods for read-only operations
- Validate input in setter methods
- Design minimal public interfaces
- Use meaningful names for getter/setter methods
- Consider immutable objects where appropriate

### Don'ts ❌
- Don't expose internal data structures directly
- Avoid public data members (except for POD types)
- Don't return non-const references to private members
- Avoid complex public interfaces
- Don't break encapsulation with friend declarations unnecessarily
- Avoid getter/setter for every private member

## Common Encapsulation Patterns

### 1. **Read-Only Properties**
```cpp
class Circle {
private:
    double radius;
    
public:
    Circle(double r) : radius(r) {}
    double getRadius() const { return radius; }
    double getArea() const { return 3.14159 * radius * radius; }
    // No setter - radius is immutable after construction
};
```

### 2. **Validated Properties**
```cpp
class Temperature {
private:
    double celsius;
    
public:
    void setCelsius(double temp) {
        if (temp >= -273.15) {  // Absolute zero validation
            celsius = temp;
        } else {
            throw std::invalid_argument("Temperature below absolute zero");
        }
    }
    
    double getCelsius() const { return celsius; }
    double getFahrenheit() const { return celsius * 9.0 / 5.0 + 32.0; }
};
```

### 3. **Lazy Evaluation**
```cpp
class ExpensiveCalculation {
private:
    mutable bool calculated;
    mutable double result;
    double input;
    
public:
    ExpensiveCalculation(double in) : calculated(false), input(in) {}
    
    double getResult() const {
        if (!calculated) {
            result = performExpensiveCalculation();
            calculated = true;
        }
        return result;
    }
    
private:
    double performExpensiveCalculation() const {
        // Expensive computation here
        return input * input * input;
    }
};
```

## Advanced Encapsulation Techniques

### 1. **RAII (Resource Acquisition Is Initialization)**
```cpp
class FileHandler {
private:
    FILE* file;
    
public:
    FileHandler(const char* filename) : file(fopen(filename, "r")) {
        if (!file) throw std::runtime_error("Cannot open file");
    }
    
    ~FileHandler() {
        if (file) fclose(file);
    }
    
    // Prevent copying to maintain unique ownership
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;
};
```

### 2. **Immutable Objects**
```cpp
class ImmutablePoint {
private:
    const double x, y;
    
public:
    ImmutablePoint(double x_val, double y_val) : x(x_val), y(y_val) {}
    
    double getX() const { return x; }
    double getY() const { return y; }
    
    // Return new object instead of modifying existing one
    ImmutablePoint translate(double dx, double dy) const {
        return ImmutablePoint(x + dx, y + dy);
    }
};
```

### 3. **Builder Pattern for Complex Objects**
```cpp
class Computer {
private:
    std::string cpu, gpu, ram;
    
    Computer() = default;  // Private constructor
    
public:
    class Builder {
    private:
        Computer computer;
        
    public:
        Builder& setCPU(const std::string& cpu) {
            computer.cpu = cpu;
            return *this;
        }
        
        Builder& setGPU(const std::string& gpu) {
            computer.gpu = gpu;
            return *this;
        }
        
        Builder& setRAM(const std::string& ram) {
            computer.ram = ram;
            return *this;
        }
        
        Computer build() {
            return std::move(computer);
        }
    };
    
    // Getters
    const std::string& getCPU() const { return cpu; }
    const std::string& getGPU() const { return gpu; }
    const std::string& getRAM() const { return ram; }
};
```

## Memory and Performance Considerations

### Access Control Overhead
- **No Runtime Overhead**: Access specifiers are compile-time constructs
- **Inline Functions**: Getter/setter methods are often inlined by compiler
- **Optimization**: Modern compilers optimize away simple accessor methods

### Design Trade-offs
- **Flexibility vs Performance**: Encapsulation may require additional method calls
- **Memory Layout**: Private members are stored like any other members
- **Cache Locality**: Well-designed encapsulation can improve cache performance

## Testing Encapsulated Classes

### Unit Testing Strategies
```cpp
class TestableClass {
private:
    int value;
    
public:
    void setValue(int v) { value = v; }
    int getValue() const { return value; }
    
#ifdef TESTING
    // Expose internals for testing
    int getValueForTesting() const { return value; }
#endif
};
```

### Friend Test Classes
```cpp
class ProductionClass {
private:
    int secretValue;
    
    friend class ProductionClassTest;  // Test class access
    
public:
    void publicMethod();
};
```

## Modern C++ Encapsulation Features

### C++11 Features
- `default` and `delete` keywords for special member functions
- `override` and `final` keywords for virtual functions
- Strong typed enums with controlled scope

### C++14 Features
- Variable templates for compile-time constants
- Generic lambdas with auto parameters

### C++17 Features
- Structured bindings for controlled data access
- `inline` variables for header-only libraries

### C++20 Features
- Concepts for constraining template parameters
- Modules for better encapsulation at translation unit level

## Common Pitfalls

### 1. **Returning References to Private Members**
```cpp
class BadExample {
private:
    std::vector<int> data;
    
public:
    // BAD: Exposes internal data
    std::vector<int>& getData() { return data; }
    
    // GOOD: Returns copy or const reference
    const std::vector<int>& getData() const { return data; }
    std::vector<int> getDataCopy() const { return data; }
};
```

### 2. **Incomplete Encapsulation**
```cpp
class IncompleteEncapsulation {
public:
    int publicData;  // BAD: Direct access to data
    
private:
    int privateData;
    
public:
    void setPrivateData(int value) { privateData = value; }
    int getPrivateData() const { return privateData; }
    
    // Missing validation for publicData
};
```

### 3. **Over-Encapsulation**
```cpp
class OverEncapsulated {
private:
    int x, y;
    
public:
    // Too many getters/setters for simple data
    void setX(int value) { x = value; }
    void setY(int value) { y = value; }
    int getX() const { return x; }
    int getY() const { return y; }
    
    // Consider: struct Point { int x, y; }; for simple data
};
```

---

*Explore each file to understand different encapsulation techniques and their practical applications in creating robust, maintainable C++ code!*
