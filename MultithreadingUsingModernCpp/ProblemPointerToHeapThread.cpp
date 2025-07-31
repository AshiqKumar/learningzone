//Certainly! Here’s an example that demonstrates the problem when you pass a pointer to heap memory to a thread, 
// but the memory is deleted (freed) before the thread accesses it.
// This is dangerous and leads to undefined behavior!
#include <iostream>
#include <thread>
#include <chrono>

void thread_func(int* ptr) {
    // Simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // This may crash or print garbage if memory was deleted!
    std::cout << "Thread: value = " << *ptr << std::endl;
}

int main() {
    int* heap_val = new int(123);

    std::thread t(thread_func, heap_val);

    // BAD: Delete the memory before the thread uses it!
    delete heap_val;

    t.join(); // Thread may access deleted memory here

    std::cout << "Main thread done." << std::endl;
    return 0;
}