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

class CB
{
private:
	Dummy * p;
public:
	CB() :p(new(nothrow) Dummy) {}
	~CB() { delete p; }
	void print() { p->print(); }
};

int main()
{
	unique_ptr<CB> ptr1(new CB);
	ptr1->print();
	return 0;
}