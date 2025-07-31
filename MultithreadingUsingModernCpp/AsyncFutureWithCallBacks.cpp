
/*This demonstrates:
Default policy
Explicit async policy
Deferred policy
Lambda as callable
Functor as callable
Each future will print the sum of its arguments.*/

#include <future>
#include <iostream>
using namespace std;

// Regular function
int add(int a, int b) {
    return a + b;
}

// Functor (function object)
struct Adder {
    int operator()(int x, int y) const { return x + y; }
};

int main() {
    // 1. Default policy (implementation chooses)
    std::future<int> fut1 = std::async(add, 2, 3);

    // 2. Always run in a new thread
    std::future<int> fut2 = std::async(std::launch::async, add, 4, 5);

    // 3. Deferred execution (runs in same thread when .get() or .wait() is called)
    std::future<int> fut3 = std::async(std::launch::deferred, add, 6, 7);

    // 4. With a lambda
    std::future<int> fut4 = std::async([](int x, int y) { return x + y; }, 8, 9);

    // 5. With a function object (functor)
    Adder adder;
    std::future<int> fut5 = std::async(adder, 10, 11);

    // Get and print results
    std::cout << "fut1: " << fut1.get() << std::endl;
    std::cout << "fut2: " << fut2.get() << std::endl;
    std::cout << "fut3: " << fut3.get() << std::endl;
    std::cout << "fut4: " << fut4.get() << std::endl;
    std::cout << "fut5: " << fut5.get() << std::endl;

    return 0;
}

/*
//std::async is a powerful feature in C++11 and later that allows you to run a function asynchronously, 
// meaning it can run in the background while your main thread continues executing. 
// It returns a std::future object that can be used to retrieve the result of the asynchronous operation once it's complete.
//Summary:
//std::async is used to run functions asynchronously and get their results via std::future, enabling easy parallelism in C++11 and later.

*/