#include<iostream>
#include<memory>
#include<functional>
using namespace std;
class Dummy
{
public:
	Dummy() { cout << "Dummy constructor called" << endl; }
	~Dummy() { cout << "Dummy destructor called" << endl; }
	void print() { cout << "Dummy print called :" << this << endl; }
};

void print(size_t size, Dummy *p)
{
	for (size_t i = 0; i < size; i++)
	{
		p->print();
		p++;
	}
}
int main()
{
	//create an array of instances on the heap
	//Also provide a custom deleter to delete the array of instances.
	unique_ptr<Dummy,function<void(Dummy*)>> p{ new Dummy[5], [](Dummy *x) {delete[]x; }};
	print(5, p.get());
	
	return 0;
}