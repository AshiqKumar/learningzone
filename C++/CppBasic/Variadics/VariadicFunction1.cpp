#include<iostream>
using namespace std;

template<typename T1, typename... T2> void fun(T1 value, T2...args)
{
	cout << value << ",";
	fun(args...);
}

template<typename T1> void fun(T1 x)
{
	cout << x << endl;
}

void fun() { cout << "empty call" << endl; }

int main()
{
	fun(10, 23, 45.12f, 56.78, 200, 'a');
	fun();
}
