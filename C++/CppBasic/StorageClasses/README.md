# C++ Storage Classes

## Overview

**Storage classes** in C++ define the scope, visibility, and lifetime of variables and functions. They specify where variables are stored in memory and how long they remain accessible.

## Types of Storage Classes

### 1. **auto** (C++11 and later - type deduction)
- **Pre-C++11**: Automatic storage duration (default for local variables)
- **C++11+**: Automatic type deduction

### 2. **register**
- Suggests storing variable in CPU register for faster access
- **Deprecated in C++17**

### 3. **static**
- **Local static**: Persists between function calls
- **Global static**: File scope (internal linkage)

### 4. **extern**
- Declares variable/function defined elsewhere
- Provides external linkage

### 5. **mutable**
- Allows modification of const object members

### 6. **thread_local** (C++11)
- Thread-specific storage duration

## Memory Areas

```
┌─────────────────────────────────────────────────────────────┐
│                    MEMORY LAYOUT                            │
├─────────────────────────────────────────────────────────────┤
│  STACK        │ Local variables, parameters                 │
│               │ (auto, register)                            │
├─────────────────────────────────────────────────────────────┤
│  HEAP         │ Dynamic allocation                          │
│               │ (new, malloc)                               │
├─────────────────────────────────────────────────────────────┤
│  DATA SEGMENT │ Global/static variables                     │
│               │ (static, extern)                            │
├─────────────────────────────────────────────────────────────┤
│  CODE SEGMENT │ Program instructions                        │
└─────────────────────────────────────────────────────────────┘
```

## Files in this Directory

- `README.md` - This overview
- `auto_demo.cpp` - Auto storage class and type deduction
- `static_demo.cpp` - Static storage class examples
- `extern_demo.cpp` - External linkage demonstration
- `extern_vars.cpp` - External variable definitions
- `register_demo.cpp` - Register storage class (deprecated)
- `mutable_demo.cpp` - Mutable keyword examples
- `thread_local_demo.cpp` - Thread-local storage (C++11)
- `comprehensive_demo.cpp` - All storage classes together
- `Makefile` - Build system for all examples

## Quick Compilation

```bash
# Compile individual examples
g++ -std=c++17 -Wall -Wextra auto_demo.cpp -o auto_demo
g++ -std=c++17 -Wall -Wextra static_demo.cpp -o static_demo

# Or use the provided Makefile
make all
make run-all
```

## Key Concepts

### Storage Duration
- **Automatic**: Stack allocation, destroyed when out of scope
- **Static**: Exists for program lifetime
- **Dynamic**: Heap allocation, manual management
- **Thread**: Per-thread storage

### Linkage
- **Internal**: Visible within translation unit only
- **External**: Visible across translation units
- **No linkage**: Local scope only

### Scope
- **Block scope**: Within `{}`
- **Function scope**: Labels only
- **File scope**: Global
- **Class scope**: Within class definition

---

*Explore each file to understand different storage classes in depth!*
