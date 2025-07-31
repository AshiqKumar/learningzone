# Prototype Design Pattern in C++

## Overview

The **Prototype Design Pattern** is a creational design pattern that allows you to create new objects by copying (cloning) existing objects, rather than creating them from scratch. This pattern is particularly useful when object creation is costly or complex.

## Key Concepts

- **Cloning**: Create new objects by copying existing ones
- **Prototype Interface**: Common interface for cloneable objects
- **Concrete Prototypes**: Actual implementations that can be cloned
- **Cost Efficiency**: Avoid expensive object creation operations

## When to Use Prototype Pattern

✅ **Object creation is expensive** (database connections, file operations, network calls)  
✅ **Need multiple similar objects** with slight variations  
✅ **Avoid subclassing** object creators  
✅ **Runtime object configuration** is needed  
✅ **Complex object initialization** that should be reused  

## Problem Solved

Without the Prototype pattern, creating similar objects requires:
- Knowing the exact class of the object
- Going through expensive initialization processes repeatedly
- Tight coupling between client code and concrete classes

## Solution Structure

```
┌─────────────────┐    ┌──────────────────┐
│    Client       │───▶│   Prototype      │
└─────────────────┘    │  (Interface)     │
                       │ + clone()        │
                       └──────────────────┘
                                △
                                │
                   ┌────────────┴────────────┐
                   │                         │
        ┌──────────▼──────────┐   ┌─────────▼────────┐
        │ ConcretePrototype1  │   │ ConcretePrototype2│
        │ + clone()           │   │ + clone()         │
        └─────────────────────┘   └──────────────────┘
```

## Code Example Analysis

### Base Device Interface
```cpp
class Device {
public:
    virtual void send(string data) = 0; 
    virtual int setSpeed(int value) = 0;
    virtual int getSpeed() = 0;
};
```

### Concrete Device Implementations
```cpp
class Bluetooth : public Device {
public:
    int speed;
    Bluetooth() { speed = 8; }
    
    int setSpeed(int value) { speed = value; }
    int getSpeed() { return speed; }
    
    void send(string data) {
        cout << "Sent By Bluetooth: " << data << " Speed: " << speed << endl;
    }
};
```

### Prototype Interface
```cpp
class Prototype {
public:
    virtual Device* clone(Device *oldOneObject) = 0;
};
```

### Concrete Prototype Implementation
```cpp
class BluetoothPrototype : public Prototype {
public:
    Device* clone(Device* oldOneObject) {
        Device* newOneObject = new Bluetooth;
        newOneObject->setSpeed(oldOneObject->getSpeed());
        return newOneObject;
    }
};
```

## Advantages

### ✅ **Performance Benefits**
- Avoid expensive object creation
- Reuse complex initialization logic
- Faster than creating from scratch

### ✅ **Flexibility**
- Create objects without knowing their exact type
- Runtime object configuration
- Easy to add new prototype types

### ✅ **Reduced Coupling**
- Client doesn't need to know concrete classes
- Eliminates need for complex factory hierarchies

### ✅ **Memory Efficiency**
- Share common data between clones
- Reduce initialization overhead

## Disadvantages

### ❌ **Complexity**
- Implementing clone() can be complex
- Deep vs shallow copy considerations
- Circular reference handling

### ❌ **Memory Management**
- Manual memory management with raw pointers
- Risk of memory leaks
- Ownership responsibilities unclear

## Improved Implementation

Here's a modern C++ approach with better memory management:

```cpp
#include <memory>
#include <iostream>
#include <string>

// Modern Device interface with smart pointers
class Device {
public:
    virtual ~Device() = default;
    virtual void send(const std::string& data) = 0;
    virtual void setSpeed(int value) = 0;
    virtual int getSpeed() const = 0;
    virtual std::unique_ptr<Device> clone() const = 0;  // Self-cloning
};

class Bluetooth : public Device {
private:
    int speed;
    
public:
    Bluetooth(int initialSpeed = 8) : speed(initialSpeed) {}
    
    void send(const std::string& data) override {
        std::cout << "Sent By Bluetooth: " << data 
                  << " Speed: " << speed << std::endl;
    }
    
    void setSpeed(int value) override { speed = value; }
    int getSpeed() const override { return speed; }
    
    std::unique_ptr<Device> clone() const override {
        return std::make_unique<Bluetooth>(speed);
    }
};

class Wifi : public Device {
private:
    int speed;
    
public:
    Wifi(int initialSpeed = 100) : speed(initialSpeed) {}
    
    void send(const std::string& data) override {
        std::cout << "Sent By Wifi: " << data 
                  << " Speed: " << speed << std::endl;
    }
    
    void setSpeed(int value) override { speed = value; }
    int getSpeed() const override { return speed; }
    
    std::unique_ptr<Device> clone() const override {
        return std::make_unique<Wifi>(speed);
    }
};

// Usage example
int main() {
    // Create original object
    auto originalBluetooth = std::make_unique<Bluetooth>();
    originalBluetooth->setSpeed(20);
    originalBluetooth->send("Original Object");
    
    // Clone the object
    auto clonedBluetooth = originalBluetooth->clone();
    clonedBluetooth->send("Cloned Object");
    
    std::cout << "Original speed: " << originalBluetooth->getSpeed() << std::endl;
    std::cout << "Cloned speed: " << clonedBluetooth->getSpeed() << std::endl;
    
    return 0;
}
```

## Deep vs Shallow Copy

### Shallow Copy
- Copies only the immediate members
- Shared resources between original and clone
- Faster but can cause issues with shared data

### Deep Copy
- Copies all data recursively
- Independent objects
- Slower but safer

```cpp
class ComplexDevice : public Device {
private:
    std::vector<std::string> configuration;
    std::unique_ptr<NetworkAdapter> adapter;
    
public:
    std::unique_ptr<Device> clone() const override {
        auto cloned = std::make_unique<ComplexDevice>();
        
        // Deep copy of vector
        cloned->configuration = this->configuration;
        
        // Deep copy of adapter
        if (this->adapter) {
            cloned->adapter = this->adapter->clone();
        }
        
        return cloned;
    }
};
```

## Common Pitfalls and Solutions

### 1. **Memory Leaks**
```cpp
// ❌ Problematic
Device* clone = prototype->clone(original);
// Forgot to delete!

// ✅ Better
std::unique_ptr<Device> clone = original->clone();
// Automatic cleanup
```

### 2. **Incomplete Cloning**
```cpp
// ❌ Shallow copy issues
class BadDevice : public Device {
    int* data;
public:
    Device* clone() const {
        auto cloned = new BadDevice();
        cloned->data = this->data;  // Shared pointer!
        return cloned;
    }
};

// ✅ Proper deep copy
class GoodDevice : public Device {
    std::unique_ptr<int> data;
public:
    std::unique_ptr<Device> clone() const override {
        auto cloned = std::make_unique<GoodDevice>();
        if (data) {
            cloned->data = std::make_unique<int>(*data);
        }
        return cloned;
    }
};
```

### 3. **Virtual Constructor Idiom**
```cpp
class Device {
public:
    virtual ~Device() = default;
    virtual std::unique_ptr<Device> clone() const = 0;
    
    // Template method for type-safe cloning
    template<typename T>
    std::unique_ptr<T> clone_as() const {
        auto cloned = clone();
        return std::unique_ptr<T>(dynamic_cast<T*>(cloned.release()));
    }
};
```

## Real-World Use Cases

### 1. **Game Objects**
```cpp
class GameObject {
    Vector3 position;
    Mesh* mesh;
    Material* material;
public:
    virtual std::unique_ptr<GameObject> clone() const = 0;
};

class Enemy : public GameObject {
public:
    std::unique_ptr<GameObject> clone() const override {
        // Clone enemy with same mesh/material but different position
        auto cloned = std::make_unique<Enemy>();
        cloned->mesh = this->mesh;  // Shared resource
        cloned->material = this->material;  // Shared resource
        cloned->position = this->position;  // Could be modified after cloning
        return cloned;
    }
};
```

### 2. **Document Templates**
```cpp
class Document {
    std::string template_content;
    std::map<std::string, std::string> placeholders;
public:
    virtual std::unique_ptr<Document> clone() const = 0;
    virtual void fillPlaceholder(const std::string& key, const std::string& value) = 0;
};
```

### 3. **Database Connection Pools**
```cpp
class DatabaseConnection {
    std::string connectionString;
    ConnectionSettings settings;
public:
    std::unique_ptr<DatabaseConnection> clone() const {
        auto cloned = std::make_unique<DatabaseConnection>();
        cloned->connectionString = this->connectionString;
        cloned->settings = this->settings;
        // New connection with same settings
        cloned->connect();
        return cloned;
    }
};
```

## Best Practices

### 1. **Use Smart Pointers**
- Prefer `std::unique_ptr` for ownership
- Use `std::shared_ptr` for shared resources
- Avoid raw pointers for memory management

### 2. **Implement Copy Constructor and Assignment**
```cpp
class Device {
public:
    // Copy constructor
    Device(const Device& other) = default;
    
    // Copy assignment
    Device& operator=(const Device& other) = default;
    
    // Move constructor
    Device(Device&& other) noexcept = default;
    
    // Move assignment
    Device& operator=(Device&& other) noexcept = default;
    
    // Virtual destructor
    virtual ~Device() = default;
    
    // Clone method
    virtual std::unique_ptr<Device> clone() const = 0;
};
```

### 3. **Consider Copy-and-Swap Idiom**
```cpp
class Device {
    std::string name;
    std::vector<int> data;
    
public:
    Device& operator=(Device other) {  // Pass by value
        swap(*this, other);
        return *this;
    }
    
    friend void swap(Device& first, Device& second) noexcept {
        using std::swap;
        swap(first.name, second.name);
        swap(first.data, second.data);
    }
};
```

### 4. **Thread Safety Considerations**
```cpp
class ThreadSafeDevice : public Device {
    mutable std::mutex mutex_;
    
public:
    std::unique_ptr<Device> clone() const override {
        std::lock_guard<std::mutex> lock(mutex_);
        // Safe cloning under lock
        return std::make_unique<ThreadSafeDevice>(*this);
    }
};
```

## Performance Considerations

### Benchmarking Clone vs New
```cpp
#include <chrono>

void benchmarkCreation() {
    const int iterations = 100000;
    
    // Benchmark new creation
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto device = std::make_unique<ComplexDevice>("config.xml");
        // ComplexDevice constructor reads file, parses XML, etc.
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto newTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Benchmark cloning
    auto prototype = std::make_unique<ComplexDevice>("config.xml");
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto device = prototype->clone();
    }
    end = std::chrono::high_resolution_clock::now();
    auto cloneTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "New creation: " << newTime.count() << "ms" << std::endl;
    std::cout << "Cloning: " << cloneTime.count() << "ms" << std::endl;
}
```

## Comparison with Other Patterns

| Pattern | Purpose | When to Use |
|---------|---------|-------------|
| **Prototype** | Clone existing objects | Expensive object creation |
| **Factory Method** | Create objects via inheritance | Need different creators |
| **Abstract Factory** | Create families of objects | Related object groups |
| **Builder** | Construct complex objects step by step | Complex construction process |
| **Singleton** | Ensure single instance | Global access point needed |

## Conclusion

The Prototype pattern is powerful for:
- **Performance optimization** when object creation is expensive
- **Flexibility** in object creation without tight coupling
- **Runtime configuration** of object types

However, be careful with:
- **Deep vs shallow copying** decisions
- **Memory management** (prefer smart pointers)
- **Thread safety** in multi-threaded environments

The pattern works best when combined with modern C++ features like smart pointers, RAII, and move semantics for robust and efficient implementations.

## Testing the Pattern

```cpp
#include <gtest/gtest.h>

class PrototypeTest : public ::testing::Test {
protected:
    void SetUp() override {
        original = std::make_unique<Bluetooth>(25);
    }
    
    std::unique_ptr<Device> original;
};

TEST_F(PrototypeTest, ClonePreservesState) {
    auto cloned = original->clone();
    
    EXPECT_EQ(original->getSpeed(), cloned->getSpeed());
    EXPECT_NE(original.get(), cloned.get());  // Different objects
}

TEST_F(PrototypeTest, CloneIndependence) {
    auto cloned = original->clone();
    
    original->setSpeed(50);
    
    EXPECT_EQ(50, original->getSpeed());
    EXPECT_EQ(25, cloned->getSpeed());  // Clone unchanged
}
```

This comprehensive documentation covers all aspects of the Prototype pattern, from basic concepts to advanced implementations and best practices.
