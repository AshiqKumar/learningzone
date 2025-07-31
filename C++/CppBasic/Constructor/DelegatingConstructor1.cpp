/*
A delegating constructor in C++ is a constructor that calls another constructor of the same class to perform 
part or all of the initialization. This helps avoid code duplication and centralizes initialization logic.
*/

#include<iostream>
using namespace std;
class Dummy
{
private:
	int a, b;
	Dummy(int x, int y) :a(x), b(y) { cout << "Dummy two arg.constructor" << endl; }
public:
	Dummy() :Dummy(10, 20){ cout << "Dummy default constructor" << endl; }

	Dummy(int x) :Dummy(x, x) { cout << "Dummy one arg. constructor" << endl; }
};

int main()
{
	Dummy obj1(300);
}

/*
When you create Dummy obj1(300);, the one-argument constructor is called.
This delegates to Dummy(300, 300), which initializes a and b and prints "Dummy two arg.constructor".
After that, "Dummy one arg. constructor" is printed.

o/p: 
Dummy two arg.constructor
Dummy one arg. constructor
*/