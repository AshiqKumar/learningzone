#include <thread>
#include <iostream>
#include <chrono>

void increment(int &count) 
{
    for (int i = 0; i < 5; ++i) 
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10000)); // Simulate work
        count++;
        std::cout << "Count: " << count << std::endl;
    }

}

int main() 
{
    int countThread = 5;

    std::cout << "Starting a thread..." << std::endl;

    // Start the thread and pass countThread by reference

    std::thread t(increment, std::ref(countThread));
    // std::ref is used to pass countThread by reference to the thread function
    // Wait for the thread to finish

    t.join();

    std::cout << "Thread has finished execution." << std::endl;

    return 0;
}
