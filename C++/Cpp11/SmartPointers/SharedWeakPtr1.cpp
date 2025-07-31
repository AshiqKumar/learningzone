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
	shared_ptr<Dummy> ptr1(new Dummy());
	shared_ptr<Dummy> ptr2(ptr1);
	cout << "objects shared" << ptr1.use_count() << endl;
	weak_ptr<Dummy> wk1 = ptr1;
	cout << "objects shared after weak reference" << wk1.use_count() << endl;
	auto ptr3 = wk1.lock();
	ptr1->print();
	ptr2->print();
	ptr3->print();
	cout << "shared count, after acquiring lock:" << ptr1.use_count() << endl;
	cout << "weak count after providing lock:" << wk1.use_count() << endl;
	return 0;
}

