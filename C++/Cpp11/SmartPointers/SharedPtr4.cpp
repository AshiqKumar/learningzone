#include<iostream>
#include<memory>
using namespace std;
class Dummy
{
public:
	Dummy(int x=0, int y=0) 
	{ 
		cout << "Dummy constructor called" << endl; 
		cout <<"x =" << x <<",y="<< y << endl;
	}
	~Dummy() { cout << "Dummy destructor called" << endl; }
	void print() { cout << "Dummy print called :" << this << endl; }
};


int main()
{
	/*
	- create an array of instances of type 'Dummy' and provide its 
	  handle to a shared_ptr instance
	*/
	shared_ptr<Dummy> ptr1(new Dummy[5]{ {}, {10}, { 10,20 }, { 40 }, { 50,60 } }, [](Dummy *q) {delete[] q; });

	Dummy *q =ptr1.get();
	[=](int size) mutable   //A Once use lambda
	{
		int i = 0;
		do
		{
			q[i].print();
			++i;
		} while (i < size);
	}(5);

	return 0;
}