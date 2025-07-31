/** 
 * Initializer List Example in C++
 * This code demonstrates how to use initializer lists to initialize an array in a class.
- **Constructor:**  Dummy(const initializer_list<int> &x)
- Accepts an `initializer_list<int>`, so you can initialize `Dummy` with a list of integers.
- If the list size is 5 or less, it copies the values into `arr`.
- If more than 5 values are provided, it prints an error message.
**Key Concepts Demonstrated**
- **Initializer List Constructor:** Allows easy and flexible initialization of objects with a list of values.
- **Range-based for loop:** Used to copy values and print the array.
- **Error Handling:** Checks for excess parameters.

This code shows how to use `std::initializer_list` to allow class objects to be initialized with a list of values using curly braces, 
making initialization simple and expressive.
 */
#include<iostream>
#include<initializer_list>
using namespace std;

class Dummy
{
private:
	int arr[5];
public:
	Dummy(const initializer_list<int> &x) 
	{
		int i = 0;
		if (x.size() <= 5)
		{
			for (auto &val : x)
			{
				arr[i] = val;
				++i;
			}
		}
		else
			cout << "Excess parameters, initialization failed" << endl;
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
	Dummy obj1{ 10,20,30,40,50 };
	obj1.print();
}