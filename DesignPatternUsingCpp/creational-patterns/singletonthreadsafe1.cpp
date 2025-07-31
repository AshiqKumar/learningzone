
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

class Singleton
{
private:
    int data;
    
    // Private constructor prevents direct instantiation
    Singleton() : data(0) {
        std::cout << "Singleton instance created!" << std::endl;
    }
    
    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static Singleton& getInstance()
    {
        static Singleton instance; // Thread-safe since C++11
        return instance;
    }
    
    void setData(int val) { data = val; }
    int getData() const { return data; }
};

int main()
{
    Singleton& s1 = Singleton::getInstance();
    s1.setData(42);
    
    Singleton& s2 = Singleton::getInstance();
    
    if (&s1 == &s2) {
        std::cout << "Both references point to the same instance." << std::endl;
        std::cout << "Data from s2: " << s2.getData() << std::endl;
    } else {
        std::cout << "Different instances!" << std::endl;
    }
    
    // These would cause compile errors:
    // Singleton s3;           // Error: constructor is private
    // Singleton s4(s1);       // Error: copy constructor is deleted
    // Singleton s5 = s1;      // Error: assignment operator is deleted
    
    return 0;
}