#include <iostream>
#include <vector>
/*
Two threads are created: one counts even numbers, the other counts odd numbers in the vector.
ref() and cref() are used to pass variables by reference and const reference to threads.
Both threads run in parallel and update their respective counts.
The main thread waits for both to finish using join().
*/
#include <thread>
using namespace std;

void count_even(const vector<int>& v, int& even_count) {
    even_count = 0;
    for (int x : v) {
        if (x % 2 == 0) ++even_count;
    }
}

void count_odd(const vector<int>& v, int& odd_count) {
    odd_count = 0;
    for (int x : v) {
        if (x % 2 != 0) ++odd_count;
    }
}

int main() {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int even_count = 0, odd_count = 0;

    thread t1(count_even, cref(v), ref(even_count));
    thread t2(count_odd, cref(v), ref(odd_count));

    t1.join();
    t2.join();

    cout << "Even count: " << even_count << endl;
    cout << "Odd count: " << odd_count << endl;

    return 0;
}

/*

Yes, this program is thread safe.

Why?
Each thread (t1 and t2) only modifies its own variable (even_count or odd_count), and both variables are separate.
Both threads only read from the shared vector v (which is passed as const&), so there are no concurrent writes to v.
There is no shared writable data between the threads.
Summary:
No data races occur.
No need for mutexes in this case.
The program is thread safe as written.
Why use ref and cref?
By default, std::thread copies its arguments.

ref() is used to pass a variable by reference (so changes are visible in the main thread).
cref() is used to pass a variable by const reference (to avoid copying large objects and prevent modification).
*/