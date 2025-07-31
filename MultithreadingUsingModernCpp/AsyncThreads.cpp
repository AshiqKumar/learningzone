
/*
🧵 std::async vs std::thread

Feature           std::thread         std::async
----------------------------------------------------------
Manual join       ✅ Required         ❌ Not needed if .get() is used
Return values     ❌ Harder to manage ✅ Easy via std::future
Exception safety  ❌ Manual handling  ✅ Exceptions propagate via future
Thread creation   ✅ Always creates   ⚠️ May defer execution
				  thread
*/
#include<iostream>
#include<thread>
#include<future>
using namespace std;

void fun1() { cout << "Welcome "; }
void fun2() { cout << "To "; }
void fun3() { cout << "C++ "; }
void fun4() { cout << "Multithreading "; }

int main()
{
	cout << "inside main thread" << endl;
	/*thread th1(fun1);
	thread th2(fun2);
	thread th3(fun3);
	thread th4(fun4);
	th1.join();
	th2.join();
	th3.join();
	th4.join();*/

	//spawn threads with 'async'
	async(launch::async, fun1);
	async(launch::async, fun2);
	async(launch::async, fun3);
	async(launch::async, fun4);
}

/* Output:
inside main thread
Welcome To C++ Multithreading

Note: ⚠️ Important Note
Since you're not storing the futures, the main thread may exit before the async tasks complete, leading to undefined behavior.
✅ Recommended Fix
Store the futures and call .get() to ensure all tasks complete:
auto f1 = async(launch::async, fun1);
auto f2 = async(launch::async, fun2);
auto f3 = async(launch::async, fun3);
auto f4 = async(launch::async, fun4);

f1.get();
f2.get();
f3.get();
f4.get();

*/