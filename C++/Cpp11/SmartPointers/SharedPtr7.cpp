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
	shared_ptr<Dummy> sp1 = make_shared<Dummy>();
	
	if (sp1.unique())
		cout << "It is unique" << endl;
	else
		cout << "It is not unique" << endl;
	cout << "-------------------" << endl;
	shared_ptr<Dummy> sp2(sp1);
	//weak_ptr<Dummy> sp2(sp1);
	if (sp1.unique())
		cout << "It is unique" << endl;
	else
		cout << "It is not unique" << endl;
}