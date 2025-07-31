// The Singleton pattern ensures that only one instance of a class exists throughout the program and provides a global point of access to it.
/*
✅ Result: Only one instance is created and reused — as long as no two threads call getInstance() at the same time.
singleton.cpp implementation, multiple instances can be created in a multithreaded environment.
why?
The getInstance() method checks if (!instance) and then creates a new instance.
If two threads call getInstance() at the same time, both could see instance == nullptr and both could create a new Singleton, resulting in more
than one instance.
How to Fix?
🔍Use a thread-safe approach, such as a local static variable (C++11 and later) or a mutex.
*/
#include <iostream>
using namespace std;

class Singleton {
private:
    // since it is a static member, it is shared across all instances
    // The instance is private to prevent direct instantiation
    // and to ensure that it can only be accessed through the getInstance method.
    // This is a lazy initialization, meaning the instance is created only when it is needed. 
    static Singleton* instance; 
    int data;

    // Private constructor
    Singleton() : data(0) {}

    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton* getInstance() {
        if (!instance)  // Check if instance exists
            instance = new Singleton; //Create ONLY if it doesn't exist

        return instance;  // // ALWAYS return the instance (whether newly created or existing)
    }

    void setData(int val) { data = val; }
    int getData() const { return data; }
};

// Initialize static member
Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* s1 = Singleton::getInstance();
    s1->setData(42);

    Singleton* s2 = Singleton::getInstance();
    cout << "Data from s2: " << s2->getData() << endl; // Output: 42

    // Singleton s; // Error: The constructor is private, so you cannot create an object directly
    /* The copy constructor and assignment operator are deleted, so you cannot copy or assign:
       Singleton s3(*s1); 
       Singleton s4 = *s1; */

    return 0;
}

/*
Note:  Result: Only one instance is created and reused — as long as no two threads call getInstance() at the same time.

⚠️ What Happens in a Multithreaded Environment?
If two threads call getInstance() simultaneously, both might see instance == nullptr and both might create a new Singleton. This leads to:

Multiple instances being created.
Violation of the Singleton pattern.
This is called a race condition.
*/