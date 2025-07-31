#include<iostream>
#include<memory>
using namespace std;
class Dummy
{
public:
	Dummy() { cout << "Dummy constructor called" << endl; }
	~Dummy() { cout << "Dummy destructor called" << endl; }
};

void fun1(shared_ptr<Dummy> p)
{
	cout << "inside fun1, shared count:" << p.use_count() << endl;
}

void fun2(shared_ptr<Dummy> p)
{
	cout << "inside fun2, shared count:" << p.use_count() << endl;
}
void fun3(shared_ptr<Dummy> p)
{
	cout << "inside fun3, shared count:" << p.use_count() << endl;
}
int main()
{
	shared_ptr<Dummy> ptr1(new Dummy);
	cout << "Before all 'fun' calls, shared count:" << ptr1.use_count() << endl;
	fun1(ptr1);
	fun2(ptr1);
	fun3(ptr1);
	cout << "After all 'fun' calls, shared count:" << ptr1.use_count() << endl;
	return 0;
}