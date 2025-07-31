#include<iostream>
using namespace std;
//an example illustrating the usage of 'decltype' keyword

int main()
{
	int x = 10;
	float j = 20.34f;
	int &y = x;
	//Let the variable z1 of the type whatever is type 'x'
	decltype(x) z1;
	cout << "data type of z1 is " << typeid(z1).name() << endl;

	decltype(j) z2;
	cout << "data type of z2 is " << typeid(z2).name() << endl;

	decltype(y) z3(x);
	cout << "data type of z3 is " << typeid(z3).name() << endl;

	decltype((x)) z4(y);
	cout << "data type of z4 is " << typeid(z4).name() << endl;
	
	int r = 100;
	decltype((y)) z5(r);
	cout << "data type of z5 is " << typeid(z5).name() << endl;
	cout << "y = " << y << ", and z5 = " << z5 << endl;
	cout << "------------------------" << endl;
}

