#include<iostream>
using namespace std;
class Dummy
{
	int a, b, c;
};
template<int N> 
class A
{
public:
	static int size() { return N; }
};

int f1();
double f2();
Dummy& f3();

int main()
{
	A<5> obj;
	cout << obj.size() << endl; // Output: 5
	cout << A<sizeof(f1())>::size() << endl; // don't use cout << A<sizeof(f1())>.size() << endl;
	cout << A<sizeof(f2())>::size() << endl;
	cout << A<sizeof(f3())>::size() << endl;
}