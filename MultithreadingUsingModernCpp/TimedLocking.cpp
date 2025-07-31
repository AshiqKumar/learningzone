#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

std::timed_mutex mx;

void work() 
{
	std::chrono::milliseconds timeout(10);

	while (true) 
	{
		if (mx.try_lock_for(timeout)) 
		{
			std::cout << std::this_thread::get_id() << ": do work with the mutex" << std::endl;

			std::chrono::milliseconds sleepDuration(250);
			std::this_thread::sleep_for(sleepDuration);

			mx.unlock();

			std::this_thread::sleep_for(sleepDuration);
		}
		else 
		{
			std::cout << std::this_thread::get_id() << ": do work without mutex" << std::endl;

			std::chrono::milliseconds sleepDuration(100);
			std::this_thread::sleep_for(sleepDuration);
		}
	}
}

int main() 
{
	thread t1(work);
	thread t2(work);

	t1.join();
	t2.join();

	return 0;
}