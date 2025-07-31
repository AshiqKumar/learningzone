#include <iostream>
#include <mutex>
using namespace std;

class Singleton {
    static Singleton* instance;
    static once_flag flag;
    Singleton() { cout << "Singleton created\n"; }
public:
    static Singleton* getInstance() {
        call_once(flag, []() {
            instance = new Singleton();
        });
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
once_flag Singleton::flag;

int main() {
    Singleton* s1 = Singleton::getInstance()
    Singleton* s2 = Singleton::getInstance();
    // Output: "Singleton created" (printed only once)
}

/*
How it works:

call_once(flag, ...) ensures the lambda (which creates the singleton) runs only once, no matter how many threads call getInstance().
This prevents multiple creations of the singleton instance, making it thread-safe.
Summary:
std::call_once and std::once_flag are the standard way to implement a thread-safe singleton in modern C++.
*/

/*
Yes, std::call_once can be used without a lambda function.
You can use std::call_once with any callable—lambda, function pointer, or functor. Lambdas are just a convenient option.

#include <iostream>
#include <mutex>
using namespace std;

class Singleton {
    static Singleton* instance;
    static once_flag flag;
    Singleton() { cout << "Singleton created\n"; }
    static void createInstance() {
        instance = new Singleton();
    }
public:
    static Singleton* getInstance() {
        call_once(flag, createInstance); // No lambda, just a function pointer
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;
once_flag Singleton::flag;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
}
*/