#include<iostream>
#include<thread>
#include<mutex>
#include<string>

using namespace std;

/*
* A resource that is bound to be accesses by multiples thread's must be
* bound to-gether along with its mutex. And we have to ensure that this resource
* never gets accessed outside the bound of the mutex.
*/

class TaskRunner {
private:
    std::mutex mtx; // Mutex to protect shared resources

public:
    void task1() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Task 1 is running\n";
    }

    void task2() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Task 2 is running\n";
    }

    void run() {
        std::thread th1(&TaskRunner::task1, this);
        std::thread th2(&TaskRunner::task2, this);

        th1.join();
        th2.join();

        std::cout << "Both threads finished.\n";
    }
};

int main() {
    TaskRunner runner;
    runner.run();
    return 0;
}
