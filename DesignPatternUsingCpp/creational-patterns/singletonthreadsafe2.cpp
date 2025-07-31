/*
Why is this thread-safe?
* Since C++11, the initialization of a local static variable is guaranteed by the C++ standard to be thread-safe.
✅ Result: This means that even if multiple threads call getInstance() at the same time, only one instance of Singleton will ever be created.

How it works:
* The first thread that calls getInstance() will create the Singleton instance.
* Any other threads calling getInstance() at the same time will wait until the initialization is complete.
* All threads will then get a pointer to the same instance.
* Use a local static variable in getInstance() for thread-safe Singleton (C++11+).
* No need for explicit mutex.
*/
#include <iostream>
using namespace std;

class Singleton {
private:
    int data;

    // Private constructor
    Singleton() : data(0) {}

    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // Thread-safe in C++11 and later 
    // The compiler uses mechanisms like mutexes or atomic flags internally to ensure this safety, but you don’t need to manage them manually.
    static Singleton* getInstance() 
    {
        static Singleton instance;
        return &instance;
    }

    void setData(int val) 
    {
        data = val;
    }
    int getData() const
    { 
        return data; 
    }
};

int main() {
    Singleton* s1 = Singleton::getInstance();
    s1->setData(42);

    Singleton* s2 = Singleton::getInstance();
    cout << "Data from s2: " << s2->getData() << endl; // Output: 42

    // The following lines would cause compile errors:
    // Singleton s; // Error: constructor is private
    // Singleton s3(*s1); // Error: copy constructor is deleted
    // Singleton s4 = *s1; // Error: assignment operator is deleted

    return 0;
}