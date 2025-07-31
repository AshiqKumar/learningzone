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
	/*
	    - Assigning a 'raw pointer' to a multiple shared object's would lead to 
		    dangling pointer issues.
		- Would result in an exception (double delete)
	*/
	Dummy *p = new(nothrow) Dummy;

	shared_ptr<Dummy> ptr1(p);
	shared_ptr<Dummy> ptr2(p);
	//check the use count of both shared_ptr objects
	cout << "ptr1 - use count:" << ptr1.use_count() << endl;
	cout << "ptr2 -use count: " << ptr2.use_count() << endl;
	return 0;
}