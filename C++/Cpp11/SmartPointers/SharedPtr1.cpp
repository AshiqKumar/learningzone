#include<iostream>
#include<memory>
using namespace std;
class Dummy
{
public:
	Dummy() { cout << "Dummy constructor called" << endl; }
	~Dummy() { cout << "Dummy destructor called" << endl; }
};

void fun3(shared_ptr<Dummy> p)
{
	cout << "inside fun3, shared count:" << p.use_count() << endl;
}

void fun2(shared_ptr<Dummy> p)
{
	cout << "inside fun2, shared count:" << p.use_count() << endl;
	fun3(p);
}

void fun1(shared_ptr<Dummy> p)
{
	cout << "inside fun1, shared count:" << p.use_count() << endl;
	fun2(p);
}



int main()
{
	shared_ptr<Dummy> ptr1(new Dummy);
	cout << "Before fun1 call, shared count:" << ptr1.use_count() << endl;
	fun1(ptr1);
	cout << "After fun1 call, shared count:" << ptr1.use_count() << endl;
	return 0;
}