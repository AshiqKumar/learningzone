//std::promise and std::future are used to safely pass data from one thread to another.
//The thread sets a value in the promise; the main thread waits for and retrieves it using the future.
//This is a common pattern for thread synchronization and communication in modern C++.
//std::promise and std::future is part of the version of c++11 and later
#include<iostream>
#include<thread>
#include<string>
#include<future>
using namespace std;

void MyFun(promise<string> &prm)
{
	string str("MyFun:Hello from future");
	prm.set_value(str);
}

int main()
{
	promise<string> pm;
	future<string> ft = pm.get_future();
	
	
	thread th(MyFun, ref(pm));
	cout << "Inside main...." << endl;

	string str = ft.get();
	cout << str << endl;

	th.join();
}