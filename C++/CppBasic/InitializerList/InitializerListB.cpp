/*****************************************************************************
This code demonstrates how to use std::initializer_list as a member variable in a class and how to initialize 
it using a constructor initializer list.
initializer_list<int> arr;
Declares a member variable arr that can hold a list of integers.

Constructor:
Dummy(const initializer_list<int> &x) : arr(x)

The constructor takes an initializer list and uses the member initializer list (: arr(x)) to initialize the member 
variable arr with the values from x.
Prints a message to indicate the constructor was called.

************************************************************************** */
#include<iostream>
#include<initializer_list>
using namespace std;

class Dummy
{
private:
	initializer_list<int> arr;
public:
	Dummy(const initializer_list<int> &x):arr(x)
	{
		cout << "initializer list constructor" << endl;
	}

	void print()
	{
		for (auto &val : arr)
		{
			cout << val << ",";
		}
		cout << endl;
	}
};

int main()
{
	Dummy obj1{ 10,20,30,40,50,60,70,80 };
	obj1.print();
}