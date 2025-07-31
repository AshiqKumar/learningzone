#include<iostream>
using namespace std;
class Dummy
{
private:
	int a, b;
public:
	Dummy() :a(0), b(0) { cout << "Dummy default constructor" << endl; }
	Dummy(int x) :a(x), b(x) { cout << "Dummy one arg. constructor" << endl; }
	Dummy(int x, int y) :a(x), b(y) { cout << "Dummy two arg. constructor" << endl; }
	Dummy(const Dummy& x) :a(x.a), b(x.b) { cout << "Dummy copy constructor" << endl; }
	~Dummy() { cout << "Dummy destructor" << endl; }
	void print()const { cout << "a =" << a << ",b=" << b << endl; }
};

int main()
{
	//A collection of integers dynamically created and initialized
	int *p1 = new int[5]{ 10,20,30,40,50 };
	Dummy obj1;
	Dummy* p2 = new Dummy[4]{ {}, {10},{20,30},{obj1} };
	
	//prefer the above approach over the following syntax
	Dummy* p3 = new Dummy[4]{ (10),(20,30),(obj1) };
	p3[1].print();

	delete[]p2;
	delete[]p3;
}