#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>

std::shared_mutex rw_mutex;
int shared_data = 0;

// Reader function: multiple threads can read at the same time
void reader(int id) {
    std::shared_lock lock(rw_mutex); // shared (reader) lock
    std::cout << "Reader " << id << " reads: " << shared_data << std::endl;
}

// Writer function: only one thread can write at a time
void writer(int id) {
    std::unique_lock lock(rw_mutex); // exclusive (writer) lock
    ++shared_data;
    std::cout << "Writer " << id << " writes: " << shared_data << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    // Start some readers (concurrent reads)
    for (int i = 0; i < 3; ++i)
        threads.emplace_back(reader, i);

    // Start a writer (exclusive write)
    threads.emplace_back(writer, 1);

    // More readers (concurrent reads after write)
    for (int i = 3; i < 6; ++i)
        threads.emplace_back(reader, i);

    // Wait for all threads to finish
    // Ensures the main() function waits for all threads to finish before exiting.
    // Prevents premature termination of the program.
    for (auto& t : threads) t.join();

    return 0;
}

/*
Reader 0 reads: 0
Reader 1 reads: 0
Reader 2 reads: 0
Writer 1 writes: 1
Reader 3 reads: 1
Reader 4 reads: 1
Reader 5 reads: 1
*/