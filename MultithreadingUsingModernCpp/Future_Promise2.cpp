//Event handling (or event synchronization) is important in multithreaded programming to coordinate actions between threads. 
// It allows one thread to wait for a specific condition or "event" to occur in another thread before proceeding.
//Event handling for threads is needed to synchronize actions, avoid race conditions, and ensure threads proceed only when certain conditions are met.
//In C++, this is often done using std::future, std::promise, std::condition_variable, or similar mechanisms.


#include<iostream>
#include<thread>
#include<future>
using namespace std;
//Like Thread class objects, Even the future and promise class objects are
//move only types.
int factorial(future<int>& f)
{
	int res=1;
	
	int N = f.get();
	for(int i=1;i<=N;i++)
	{
		res *- i;
	}
	return res;
}

int main()
{
   int x;
   //create a future object channel to send a value from parent thread to 
   //to the child thread, 
   promise<int> p;
   future<int> f = p.get_future();
   
   future<int> fu = async(launch::async, factorial, ref(f));
   
   //do someother parent thread business....
   //also take a nap if necessary
   this_thread::sleep_for(chrono::milliseconds(20));
   //And now it is decided to pass the required parameter to child thread
   p.set_value(4);
   
   
   x = fu.get();
   cout <<"Factorial value recieved from child thread is "<< x << endl;
}

/************************************************************* *
 * Why is event handling needed for threads?
 * 
 * Event handling is crucial in multithreaded programming to ensure that threads can communicate and synchronize their actions effectively. 
 * It helps to:
 * 1. **Coordinate Actions**: Threads may need to wait for certain conditions or events in other threads before proceeding with their execution.
 * 2. ** Avoiding busy-waiting: Without event handling, a thread might repeatedly check (poll) for a condition, wasting CPU cycles.
         Safe communication: It ensures data is ready and valid before another thread accesses it, preventing race conditions and undefined behavior.
 * 3. **Resource Management**: Threads can signal when they have completed tasks or when resources are available, allowing other threads to proceed.
 * 4. **Error Handling**: It allows threads to handle errors or exceptions in a controlled manner, ensuring that the program can recover or terminate gracefully.
 * 5.Safe communication: It ensures data is ready and valid before another thread accesses it, preventing race conditions and undefined behavior.
 * In C++, event handling is often implemented using mechanisms like `std::future`, `std::promise`, `std::condition_variable`, and other synchronization primitives.
 **************************************************************/