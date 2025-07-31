//Downward casting (also called downcasting) in C++ refers to converting a pointer or reference of a base class type to a derived class type.
/*
Upcasting (derived → base) is always safe.
Downcasting (base → derived) is only safe if the object is actually of the derived type.
Use dynamic_cast for safe downcasting with polymorphic types (i.e., base class has at least one virtual function).
*/
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { // Make Base polymorphic for dynamic_cast
        cout << "Base show()" << endl;
    }
};

class Derived : public Base {
public:
    void show() override {
        cout << "Derived show()" << endl;
    }
    void derivedOnly() {
        cout << "Derived only function" << endl;
    }
};

int main() {
    Base* basePtr = new Derived(); // Upcasting (safe)
    basePtr->show(); // Calls Derived::show() due to virtual

    // Downcasting using static_cast (unsafe if basePtr is not actually Derived*)
    Derived* d1 = static_cast<Derived*>(basePtr);
    d1->derivedOnly(); // OK, because basePtr actually points to Derived

    // Downcasting using dynamic_cast (safe, checks type at runtime)
    Base* anotherBase = new Base();
    Derived* d2 = dynamic_cast<Derived*>(anotherBase);
    if (d2) {
        d2->derivedOnly();
    } else {
        cout << "dynamic_cast failed: anotherBase is not a Derived*" << endl;
    }

    // dynamic_cast works when the object is actually Derived
    Derived* d3 = dynamic_cast<Derived*>(basePtr);
    if (d3) {
        d3->derivedOnly();
    } else {
        cout << "dynamic_cast failed: basePtr is not a Derived*" << endl;
    }

    delete basePtr;
    delete anotherBase;
    return 0;
}