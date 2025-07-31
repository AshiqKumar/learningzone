#include<iostream>
#include<functional>
using namespace std;

//undefined behaviour scenario 1

function<int()> f;// a global function object

void fun1()
{
	int *p;
	p = new int{ 10 };
	f = [=]() { return *p; };
	delete p;
	//using the lambda inside fun1 scope is fine
	int x = f();
	cout << x << endl;
}

int main()
{
	//fun1();
	int y{};
	y = f();
	cout << y << endl;
}
