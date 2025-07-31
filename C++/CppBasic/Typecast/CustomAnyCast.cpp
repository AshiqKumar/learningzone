#include<iostream>
using namespace std;

class AnyCast
{
private:
public:
	 template<typename T1, typename T2> static T1* any_cast(T2 *p)
	{
		if (typeid(T1) == typeid(T2))
		{
			cout << "cast successfull" << endl;
			return p;
		}
		else
		{
			cout << "bad cast" << endl;
			return nullptr;
		}
	}
};
class Dummy
{
public:
	void fun() { cout << "Dummy fun called" << endl; }
};
class CB
{
public:
	void fun() { cout << "CB fun called" << endl; }
};
//****** consumer code ******
int main()
{
	Dummy obj1;
	CB obj2;
	if (Dummy *q1 = AnyCast::any_cast<Dummy>(&obj1))
	{
		q1->fun();
	}
	else
	{
		cout << "Type not Dummy, casting failed" << endl;
	}
}