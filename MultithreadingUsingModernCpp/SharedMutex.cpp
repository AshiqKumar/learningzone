//(C++17 and later) is a synchronization primitive that allows multiple threads to read shared data at the same time (shared/reader lock), 
// but only one thread to write (exclusive/writer lock) at a time.
/*
How does it work?
Shared lock (lock_shared):
Multiple threads can acquire a shared lock simultaneously.
All can read the data, but none can write.

Exclusive lock (lock):
Only one thread can acquire an exclusive lock.
No other thread (reader or writer) can access the data until the exclusive lock is released.
*/

/*
When should you use std::shared_mutex?
When you have many readers and few writers.
When you want to allow concurrent reads but need to prevent data races during writes.
*/

/*
Summary:
Use std::shared_mutex when you want to allow multiple concurrent readers but only one writer at a time. It improves performance
in read-heavy scenarios by reducing contention compared to a regular mutex.
*/
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>

std::shared_mutex rw_mutex;
int shared_data = 0;

void reader(int id) {
    std::shared_lock lock(rw_mutex); // shared (reader) lock
    std::cout << "Reader " << id << " reads: " << shared_data << std::endl;
}

void writer(int id) {
    std::unique_lock lock(rw_mutex); // exclusive (writer) lock
    ++shared_data;
    std::cout << "Writer " << id << " writes: " << shared_data << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    // Start some readers
    for (int i = 0; i < 3; ++i)
        threads.emplace_back(reader, i);
    // Start a writer
    threads.emplace_back(writer, 1);
    // More readers
    for (int i = 3; i < 6; ++i)
        threads.emplace_back(reader, i);

    for (auto& t : threads) t.join();
    return 0;
}