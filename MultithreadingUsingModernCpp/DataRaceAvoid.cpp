// DataRaceAvoid3.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Avoiding RACE condition using RAII (RAII stands for Resource Acquisition Is Initialization) technique with lock_guard
// Why use RAII? -->Ensures resources are always released properly. and Prevents resource leaks and makes code exception-safe.
// RAII is a C++ technique that uses object lifetimes to manage resources safely and automatically. In multithreading, 
// it is commonly used with lock_guard to manage mutex locking and unlocking.
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex mu;
int counter = 0;

void increment() {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> guard(mu); // Locks the mutex for this scope
        cout <<"Increment :"<< i << endl;
        ++counter;                   // Safe to modify shared data
    } // Mutex is automatically unlocked here (when guard goes out of scope)
}

int main() {
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << "Final counter value: " << counter << endl;
    return 0;
}