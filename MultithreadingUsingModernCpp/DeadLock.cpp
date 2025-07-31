
//code demonstrates a classic deadlock:
//Two threads each hold one mutex and wait for the other, so both are stuck forever. A deadlock occurs when two or more threads wait 
// indefinitely for each other to release resources.

//How to avoid deadlock
//Always lock multiple mutexes in the same order in all threads/functions.
//Or use std::lock() to lock both mutexes at once.
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

class Dummy
{
private:
	//...
	mutex m1, m2;
public:
	void fun1(int x)
	{
		lock_guard<mutex> guard1(m1);
		lock_guard<mutex> guard2(m2);
		cout << "Dummy-fun1 called " << x << endl;
	}
	void fun2(int x)
	{
		lock_guard<mutex> guard2(m2);
		lock_guard<mutex> guard1(m1);
		cout << "Dummy-fun2 called " << x << endl;
	}
};

void process(Dummy& ob)
{
	for (int i = 100; i <= 2000; i++)
	{
		ob.fun1(i);
	}
}
int main()
{
	Dummy obj1;
	thread th1(process, ref(obj1));
	for (int i = 1; i <= 999; i++)
	{
		obj1.fun2(i);
	}
	th1.join();
}

/*
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
//Alternate approach is to make use of 'lock' function, which has dead-lock avoidance algorithm and
//also facilitates locking multiples mutex's.
class Dummy
{
private:
	//...
	mutex m1, m2;
public:
	void fun1(int x)
	{
		lock(m1, m2);
		lock_guard<mutex> guard1(m1, adopt_lock);
		lock_guard<mutex> guard2(m2, adopt_lock);
		cout << "Dummy-fun1 called " << x << endl;
	}
	void fun2(int x)
	{
		lock(m1, m2);
		lock_guard<mutex> guard2(m2, adopt_lock);
		lock_guard<mutex> guard1(m1, adopt_lock);
		cout << "Dummy-fun2 called " << x << endl;
	}
};

void process(Dummy& ob)
{
	for (int i = 100; i <= 2000; i++)
	{
		ob.fun1(i);
	}
}
int main()
{
	Dummy obj1;
	thread th1(process, ref(obj1));
	for (int i = 1; i <= 999; i++)
	{
		obj1.fun2(i);
	}
	th1.join();
}
*/