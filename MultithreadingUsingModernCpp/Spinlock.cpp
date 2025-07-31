//A spinlock is a lock that uses busy-waiting instead of blocking, implemented in C++ using std::atomic_flag. 
// It is efficient for short waits but wastes CPU if held for long
#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

class Spinlock {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            // Busy-wait (spin) until the lock is released
        }
    }
    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

Spinlock spin;
int counter = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        spin.lock();
        ++counter;
        spin.unlock();
    }
}

int main() {
    thread t1(increment);
    thread t2(increment);
    t1.join();
    t2.join();
    cout << "Final counter value: " << counter << endl;
    return 0;
}