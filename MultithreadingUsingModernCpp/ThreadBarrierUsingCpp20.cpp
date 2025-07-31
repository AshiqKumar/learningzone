/*
Thread Barrier Example :In C++, a barrier is a synchronization mechanism that ensures multiple threads
reach a certain point in execution before any of them proceed.
Note: using a simple loop to join() all threads, which is a form of synchronization but not a true barrier.
✅ Using std::barrier (C++20 and later)
*/
#include <iostream>
#include <thread>
#include <vector>
#include <barrier>

using namespace std;

int main() {
    const int num_threads = 10;

    // Barrier that waits for all threads + main thread
    barrier sync_point(num_threads + 1);

    auto thread_func = [&ync_point {
        cout << "Thread, hello from lambda\n";
        sync_point.arrive_and_wait(); // Wait at the barrier
    };

    vector<thread> v1;
    for (int i = 0; i < num_threads; ++i) {
        v1.emplace_back(thread_func);
    }

    cout << "Thread, from main()\n";
    sync_point.arrive_and_wait(); // Main thread waits too

    for (auto& th : v1) {
        th.join();
    }

    cout << "All threads have synchronized and joined.\n";
    return 0;
}
