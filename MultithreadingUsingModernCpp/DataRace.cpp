// Problem: Race condition between two threads
#include<iostream>
#include<thread>
using namespace std;

int counter = 0; // Shared variable, so race condition can occur

void Increment()
{
	for (int i = 1; i<100; i++)
	{
		cout <<"Increment :"<< i << endl;
        ++counter;
	}
}
int main()
{
	thread th1(Increment);
	thread th2(Increment);
	th1.join();
	th2.join();
}
/*
The race condition in your code is on std::cout, not on your own variables.
To avoid jumbled output, protect std::cout with a mutex.

Q)To make your program demonstrate a race condition on your own variables (not just on std::cout),
 you need to have both threads modify a shared variable without synchronization.

#include <iostream>
#include <thread>
using namespace std;

int counter = 0; // Shared variable

void Increment()
{
    for (int i = 0; i < 10000; i++)
    {
        counter++; // Race condition: both threads modify 'counter'
    }
}

int main()
{
    thread th1(Increment);
    thread th2(Increment);
    th1.join();
    th2.join();

    cout << "Final counter value: " << counter << endl;
    // Expected: 20000, but due to race condition, it will likely be less
}
*/