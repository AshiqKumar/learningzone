# CRTP (Curiously Recurring Template Pattern) Singleton in C++

## What is CRTP?

**CRTP (Curiously Recurring Template Pattern)** is a C++ idiom where a class derives from a template instantiation of itself. In the context of Singleton pattern, CRTP provides a elegant, reusable, and type-safe way to implement singletons.

## CRTP Singleton Structure

```cpp
template<typename Derived>
class Singleton {
protected:
    Singleton() = default;
    ~Singleton() = default;
    
public:
    static Derived& getInstance() {
        static Derived instance;  // Thread-safe since C++11
        return instance;
    }
    
    // Prevent copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

class MyClass : public Singleton<MyClass> {
    friend class Singleton<MyClass>;  // Allow base class access
    
private:
    MyClass() {}  // Private constructor
    
public:
    void doSomething() { /* implementation */ }
};
```

## Key Benefits of CRTP Singleton

### 1. **Type Safety**
- Each derived class gets its own unique singleton instance
- No risk of mixing different singleton types
- Compile-time enforcement

### 2. **Code Reusability**
- Single template base class serves all singletons
- No code duplication for singleton logic
- Consistent interface across all singleton classes

### 3. **Performance**
- **No virtual function overhead** - all calls resolved at compile-time
- **Static polymorphism** instead of dynamic polymorphism
- Maximum performance with type safety

### 4. **Thread Safety**
- Uses C++11 static local variable initialization
- Guaranteed thread-safe without explicit synchronization
- No race conditions on instance creation

### 5. **Inheritance Prevention**
- Private constructors prevent direct inheritance
- Friend relationship controls access precisely
- Eliminates common singleton breaking patterns

## How CRTP Works

The "curiosity" in CRTP comes from the recursive template relationship:

```cpp
// The base class is templated on the derived class
template<typename Derived>
class Singleton {
    static Derived& getInstance() {
        static Derived instance;  // Creates instance of derived type
        return instance;
    }
};

// The derived class inherits from instantiation of itself
class Logger : public Singleton<Logger> {  // Logger inherits from Singleton<Logger>
    // ...
};
```

### Step-by-step execution:
1. `Logger` inherits from `Singleton<Logger>`
2. When `Logger::getInstance()` is called, it instantiates `Singleton<Logger>::getInstance()`
3. Inside the base template, `Derived` is `Logger`
4. `static Derived instance` becomes `static Logger instance`
5. Returns reference to the `Logger` instance

## Comparison with Traditional Singleton

| Aspect | **Traditional Singleton** | **CRTP Singleton** |
|--------|---------------------------|-------------------|
| **Code Duplication** | Each singleton implements its own logic | Single base template, no duplication |
| **Type Safety** | Manual implementation, error-prone | Automatic type safety |
| **Performance** | Same performance | Same performance, no virtual overhead |
| **Reusability** | Copy-paste pattern | Inherit from template |
| **Maintainability** | Hard to maintain multiple singletons | Consistent, easy to maintain |
| **Thread Safety** | Manual synchronization needed | Automatic with C++11 |

## When to Use CRTP Singleton

### ✅ **Good Use Cases:**
- Multiple different singleton classes in your application
- Need maximum performance (no virtual calls)
- Want consistent singleton interface
- Type safety is critical
- C++11 or later environment

### ❌ **Avoid When:**
- Only need one singleton class (traditional approach simpler)
- Working with legacy C++ (pre-C++11)
- Template complexity is unwanted
- Need runtime polymorphism with singletons

## Common Pitfalls and Solutions

### 1. **Forgetting Friend Declaration**
```cpp
class MyClass : public Singleton<MyClass> {
    // FORGOT: friend class Singleton<MyClass>;
private:
    MyClass() {}  // Compiler error: base class can't access private constructor
};
```

**Solution:** Always add friend declaration for base class access.

### 2. **Template Instantiation Issues**
```cpp
// DON'T do this - creates different template instances
class A : public Singleton<A> {};
class B : public Singleton<A> {};  // Wrong! Both use Singleton<A>
```

**Solution:** Each class should inherit from `Singleton<ClassName>`.

### 3. **Initialization Order Problems**
```cpp
// If singletons depend on each other during construction
class Logger : public Singleton<Logger> {
    Logger() {
        Config::getInstance().log();  // Potential order issue
    }
};
```

**Solution:** Avoid inter-singleton dependencies during construction.

## Best Practices

1. **Always use friend declaration** for base class access
2. **Keep constructors private** in derived classes
3. **Avoid dependencies** between singletons during construction
4. **Use descriptive names** for singleton classes
5. **Document singleton behavior** in your classes
6. **Consider alternatives** before using any singleton pattern

## Example Usage Patterns

```cpp
// Logger singleton
Logger::getInstance().info("Application started");

// Configuration singleton  
ConfigManager::getInstance().setConfig("debug", "true");

// Cache singleton
CacheManager::getInstance().put("user:123", userData);

// Each call is type-safe and resolved at compile-time
```

## Conclusion

CRTP Singleton pattern provides a modern, efficient, and safe way to implement multiple singleton classes in C++. It combines the benefits of templates, static polymorphism, and C++11 thread safety to create a robust singleton implementation that scales well across large applications.

The pattern is particularly valuable when you need multiple different singleton types and want to maintain consistency, performance, and type safety across your codebase.
