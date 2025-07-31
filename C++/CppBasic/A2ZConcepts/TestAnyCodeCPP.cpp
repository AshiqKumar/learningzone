#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base constructor called" << std::endl;
    }
    virtual void show() const {
        std::cout << "Base::show()" << std::endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived constructor called" << std::endl;
    }
    void show() const override {
        std::cout << "Derived::show()" << std::endl;
    }
};

int main() {
    Derived d;

    // Using a base class pointer
    Base* ptr = &d;
    ptr->show(); // Calls Derived::show() due to virtual function

    // Using a base class reference
    Base& ref = d;
    ref.show(); // Also calls Derived::show() due to virtual function

    return 0;
}

/*
Base constructor called
Derived constructor called
Derived::show()
Derived::show()
*/ 

/*
The base class constructor gets called first because, in C++, when you create an object of a derived class, the construction process starts with the base class. This ensures that the base part of the object is properly initialized before the derived class adds its own initialization.

Why?

The derived class may depend on the base class being fully constructed.
It guarantees that all inherited members are set up before the derived class uses or modifies them.
Summary:
The base class constructor is always called first to ensure the base part of the object is initialized before the derived part.

*/