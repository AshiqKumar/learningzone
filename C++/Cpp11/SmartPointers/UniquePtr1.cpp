#include<iostream>
#include<memory>
using namespace std;
class Dummy
{
public:
	Dummy() { cout << "Dummy constructor called" << endl; }
	~Dummy() { cout << "Dummy destructor called" << endl; }
	void print() { cout << "Dummy print called" << endl; }
};

void fun1(unique_ptr<Dummy> p)
{
	cout << "inside fun1, ";
	p->print();
}
int main()
{
	//unique_ptr<Dummy> ptr1(new Dummy);
	unique_ptr<Dummy> ptr1 = make_unique<Dummy>();
	cout << "Call to 'print' before transferring ownership ";
	ptr1->print();

	//fun1(ptr1);    //Error, as it is not COPYABLE
	fun1(move(ptr1)); //OK, Being a MOVEABLE type, we are moving the same. 

	cout << "Call to 'print' after transferring ownership ";
	if ((ptr1.get() != nullptr))
		ptr1->print();
	else
		cout << "Cannot call Dummy-print" << endl;

	return 0;
}