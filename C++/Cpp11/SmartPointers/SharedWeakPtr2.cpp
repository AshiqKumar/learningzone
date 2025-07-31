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
	weak_ptr<Dummy> wk1(ptr1);
	
	//ptr1.reset();  //destroy the resource to the handle 'ptr1'
	//Now acquire a 'lock' from the weak_ptr
	if (!wk1.expired())
	{
		auto ptr2 = wk1.lock();
		cout << "Successfully accquired a lock on 'wk1':" << endl;
	}
	else
	{
		cout << "Failed to accquire a lock on 'wk1':" << endl;
	}
	
	return 0;
}

