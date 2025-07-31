
/*********************************************************************************
- Introduced in C++11.
- Makes code cleaner and safer by ensuring members have default values.
- The constructor can still override these values.

**Summary:**  
In-class initializers provide default values for member variables, improving code safety and readability.
example: 	int a{};
	int b{ 20 };
	float c = 12.34f;
	int sum = a + b;
	double val = compute();
*********************************************************************************/
#include<iostream>
using namespace std;

class Dummy
{
private:
	int a{};
	int b{ 20 };
	float c = 12.34f;
	int sum = a + b;
	double val = compute();
public:
	double compute()
	{
		return c* 45.56;
	}
	void print()
	{
		cout << "a =" << a << endl;
		cout << "b =" << b << endl;
		cout << "c =" << c << endl;
		cout << "sum =" << sum << endl;
		cout << "val =" << val << endl;
	}
};
//------------------
int  main()
{
	Dummy obj1;
	obj1.print();
}