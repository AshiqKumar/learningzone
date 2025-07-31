#include<iostream>
#include<memory>
using namespace std;
class Dummy
{
private:
	//shared_ptr<Dummy> p1;
	weak_ptr<Dummy> p1;
public:
	Dummy() { cout << "Dummy constructor called" << endl; }
	~Dummy() { cout << "Dummy destructor called" << endl; }
	void print() { cout << "Dummy-print called:" << this << endl; }
	void Set(shared_ptr<Dummy> x) { p1 = x; }
};

int main()
{
	shared_ptr<Dummy> ptr1 = make_shared<Dummy>();
	shared_ptr<Dummy> ptr2 = make_shared<Dummy>();

	ptr1->Set(ptr2);
	ptr2->Set(ptr1);
}