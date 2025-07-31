# Friend Function in C++

## What is a Friend Function?
A friend function is a function that is not a member of a class but has access to its private and protected members. It is declared inside the class with the `friend` keyword.

**Syntax:**
```cpp
class MyClass {
    friend void show(const MyClass& obj);
    // ...
};
```

## Why Do We Need Friend Functions?
- **Access Private Data:** Sometimes, you need to allow a non-member function or another class to access the private/protected data of a class.
- **Operator Overloading:** Friend functions are often used to overload operators that need access to private members of two different classes (e.g., `operator+`).
- **Inter-Class Communication:** When two or more classes need to share private data for certain operations.
- **Non-Member Utility:** When a function logically should not be a member but still needs access to internals (e.g., for debugging or serialization).

## Key Points
- Declared inside the class, defined outside.
- Not called with the object (no `this` pointer).
- Can access all members (private, protected, public).
- Friendship is not inherited or transitive.

---

## Example
```cpp
#include <iostream>
class Box {
    double width;
public:
    Box(double w) : width(w) {}
    friend void printWidth(const Box& b);
};

void printWidth(const Box& b) {
    std::cout << "Width: " << b.width << std::endl;
}

int main() {
    Box b(10.5);
    printWidth(b);
    return 0;
}
```

---

**Friend functions are useful for controlled access to class internals without breaking encapsulation.**
