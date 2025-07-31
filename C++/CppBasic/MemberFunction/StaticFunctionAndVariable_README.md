# Static Member Functions and Static Variables in C++

## What is a Static Member Variable?
A static member variable is a class variable that is shared by all objects of the class. It is declared with the `static` keyword inside the class definition. Only one copy of the static variable exists, regardless of how many objects are created.

**Syntax:**
```cpp
class MyClass {
    static int count;
};
```

**Definition (outside the class):**
```cpp
int MyClass::count = 0;
```

### Key Points
- Shared among all instances of the class.
- Exists even if no objects are created.
- Lifetime: From program start to end (static storage duration).
- Can be accessed using the class name (e.g., `MyClass::count`).

---

## What is a Static Member Function?
A static member function is a function that can be called on the class itself, not on a specific object. It is declared with the `static` keyword inside the class definition.

**Syntax:**
```cpp
class MyClass {
public:
    static void showCount();
};
```

### Key Points
- Can only access static member variables or other static member functions.
- Cannot access `this` pointer or non-static members.
- Can be called using the class name (e.g., `MyClass::showCount()`).

---

## Why Use Static Member Variables and Functions?
- **Shared Data:** When you need a variable or function that is common to all objects (e.g., a counter for the number of objects created).
- **Utility Functions:** For helper functions that do not depend on object state.
- **Memory Efficiency:** Only one copy of the static variable exists, saving memory.
- **Encapsulation:** Keeps related data/functions within the class scope.

---

## Storage Class and Lifetime
- **Storage Class:** Static member variables have static storage duration (allocated once, exist for the lifetime of the program).
- **Scope:** Class scope, but accessible outside the class using the scope resolution operator (`::`).
- **Initialization:** Must be defined and optionally initialized outside the class.

---

## Example
```cpp
#include <iostream>

class Counter {
    static int count;
public:
    Counter() { ++count; }
    static int getCount() { return count; }
};

int Counter::count = 0;

int main() {
    Counter a, b, c;
    std::cout << "Number of objects: " << Counter::getCount() << std::endl;
    return 0;
}
```

---

## Summary Table
| Feature                | Static Variable         | Static Function           |
|------------------------|------------------------|--------------------------|
| Shared among objects   | Yes                    | Yes                      |
| Access to this pointer | No                     | No                       |
| Access to non-static   | No                     | No                       |
| Lifetime               | Entire program         | Entire program           |
| Access syntax          | ClassName::var         | ClassName::func()        |

---

**Static members are essential for shared data and utility functions in C++ class design.**
