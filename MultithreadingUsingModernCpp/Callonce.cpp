#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

once_flag Once;
void Business1()
{
	auto lm = []() {cout << "inside lambda" << endl; };
	call_once(Once, lm);
}
int main()
{
	thread th1(Business1);
	th1.join();
	thread th2(Business1);
	th2.join();
}

/*
This code demonstrates the use of std::call_once and std::once_flag to ensure that a particular piece of code (the lambda printing "inside lambda")
is executed only once, even if called from multiple threads.

How it works:
once_flag Once;
Declares a flag used to track if the code has already been executed.

call_once(Once, lm);
Ensures that the lambda lm is executed only the first time call_once is called with Once, regardless of how many threads call it.

In main(), two threads (th1 and th2) both call Business1().
Only one of them will actually execute the lambda; the other will skip it.

Expected Output:
(The message is printed only once, even though both threads call Business1().)

Summary:
std::call_once with std::once_flag is used for thread-safe, one-time initialization (e.g., singleton pattern, initializing shared resources).
*/