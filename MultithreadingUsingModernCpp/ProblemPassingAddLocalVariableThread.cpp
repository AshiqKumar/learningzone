// Problem: Passing address of a local variable to a thread
// This can lead to undefined behavior if the local variable goes out of scope
// before the thread accesses it, potentially causing a crash or accessing invalid memory.

#include <iostream>
#include <thread>
#include <chrono>

void unsafe_thread(int* ptr) {
    // Simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Unsafe thread: value = " << *ptr << std::endl; // May crash!
}

void safe_thread(int val) {
    // Simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Safe thread: value = " << val << std::endl;
}

int main() {
    // UNSAFE: Passing address of local variable to thread
    {
        int local = 42;
        std::thread t1(unsafe_thread, &local); // local may go out of scope before t1 runs!
        t1.detach(); // Detaching makes it even more dangerous
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Give time for t1

    // SAFE: Pass by value
    {
        int local = 99;
        std::thread t2(safe_thread, local); // Pass by value (copy)
        t2.join(); // Wait for thread to finish
    }

    std::cout << "Main thread done." << std::endl;
    return 0;
}