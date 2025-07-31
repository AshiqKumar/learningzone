// ModernSmartPointers.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<memory>
using namespace std;
class Dummy
{
public:
	Dummy() { cout << "Dummy constructor called" << endl; }
	~Dummy() { cout << "Dummy destructor called" << endl; }
	void print() { cout << "Dummy-print called:" << this << endl; }
};


int main()
{
	shared_ptr<Dummy> ptr1 = make_shared<Dummy>();
	ptr1.reset();
	if (ptr1)
		cout << "shared_count :" << ptr1.use_count() << endl;
	else
		cout << "sharing no object - count :" << ptr1.use_count() << endl;
	return 0;
}

