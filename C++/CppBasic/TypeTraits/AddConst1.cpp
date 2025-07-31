#include<iostream>
#include<type_traits>
using namespace std;

class Dummy
{
public:
	void fun() { cout << "Dummy fun() called" << endl; }
	void fun() const { cout << "Dummy fun() const called" << endl; }
	void fun() volatile { cout << "Dummy fun() volatile called" << endl; }
	void fun() const volatile { cout << "Dummy fun() const volatile called" << endl; }
};

int main()
{
	Dummy obj1;
	add_const<Dummy>::type obj2;
	add_volatile<Dummy>::type obj3;
	add_cv<Dummy>::type obj4;
	obj1.fun();
	obj2.fun();
	obj3.fun();
	obj4.fun();
	return 0;
}