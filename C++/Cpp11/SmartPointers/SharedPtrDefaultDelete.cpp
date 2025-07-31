#include<iostream>
#include<memory>
using namespace std;
class Dummy
{
public:
	Dummy() { cout << "Dummy constructor called" << endl; }
	~Dummy() { cout << "Dummy destructor called" << endl; }
	void print() { cout << "Dummy print called :" << this << endl; }
};


int main()
{ 
	//std::shared_ptr<int> shared_good(new int[10], std::default_delete<int[]>());
	//create an array of instances on the heap
	shared_ptr<Dummy> p( new Dummy[5], default_delete<Dummy[]>());

	auto x = p.get();
	[=](int size) mutable
	{
		int i = 0;
		do
		{
			x[i].print();
			i++;
		} while (i < size);
	}(5);
	return 0;
}