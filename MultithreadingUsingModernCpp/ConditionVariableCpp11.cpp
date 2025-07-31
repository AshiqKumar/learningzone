// simple example of using a condition variable with C++11 multithreading:
/*
🧠 Why Use condition_variable?
    • To pause a thread until a specific condition is met.
    • Avoids busy waiting (e.g., checking in a loop).
    • Ensures safe and efficient thread synchronization.

🧠 Why Use std::lock_guard?
    • Thread Safety: Prevents multiple threads from accessing shared data at the same time.
    • Automatic Unlocking: You don’t need to manually call mtx.unlock().
    • Exception Safety: Even if an exception is thrown, the mutex is released properly.

🧠 How to Use std::lock_guard with condition_variable?
    std::lock_guard<std::mutex> lock(mtx); is a C++ RAII-style (Resource Acquisition Is Initialization)
    way to safely lock a mutex. Here's what it does and why it's important:

    🔐 Purpose
        • It locks the mutex mtx when the lock_guard is created.
        • It automatically unlocks the mutex when the lock_guard goes out of scope (e.g., at the end of a function or block).
        • This ensures exception-safe and clean mutex handling.

    Manual locking is error-prone. std::lock_guard is safer and cleaner.
        mtx.lock();
        // do something
        mtx.unlock();  // You must remember to unlock, even on exceptions!

Note:
    🔐 std::lock_guard<std::mutex>
        • Simple and lightweight
        • Automatically locks the mutex on construction and unlocks on destruction
        • No manual control over locking/unlocking
        • Best for basic, scoped locking

    🔧 std::unique_lock<std::mutex>
        • More flexible than lock_guard
        • Can lock and unlock manually
        • Can be moved between functions or scopes
        • Supports deferred locking, timed locking, and condition variables

        ✅  Manual locking with std::unique_lock:
            std::unique_lock<std::mutex> lock(mtx); // Locks immediately
            lock.unlock(); // Manually unlock
            lock.lock();   // Lock again if needed

        ✅ With condition variable:
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [] { return ready; }); // Required by condition_variable

🧠 Summary Table
Feature                  std::lock_guard      std::unique_lock
Auto lock/unlock         ✅ Yes               ✅ Yes
Manual lock/unlock       ❌ No                ✅ Yes
Moveable                 ❌ No                ✅ Yes
Condition variable use   ❌ Not supported     ✅ Required
Overhead                 🔹 Lower             🔸 Slightly higher
Use case                 Simple locking      Complex locking logic
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() {
    std::unique_lock<std::mutex> lock(mtx);
    // Wait until main() sends data
    cv.wait(lock, []{ return ready; });
    std::cout << "Worker thread proceeding after notification!" << std::endl;
}

int main() {
    std::thread t(worker);

    // Simulate some work in main
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one(); // Notify the worker thread

    t.join();
    return 0;
}