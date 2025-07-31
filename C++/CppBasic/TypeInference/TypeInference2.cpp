#include<iostream>
using namespace std;

//void fun(auto x)  ---  will not compile
void fun(int x)
{
	cout << "fun called, x= " << x << endl;
}
class Dummy
{
private:
	//auto a, b;    -- will not compile
	int a, b;
public:
	void print() const { cout << "a =" << a << ",b=" << b << endl; }
};

int main()
{
	Dummy obj1;
	obj1.print();
	auto a = 200;
	fun(a);
	auto a[10] = { 10,20,30,40,50 };
	//int a[10] = { 10,20,30,40,50 };
}