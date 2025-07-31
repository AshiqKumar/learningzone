#include<iostream>
#include<type_traits>
using namespace std;

int main()
{
	int x = 100;
	//int&& p = (remove_reference_t<int>&&) x;
	int&& p = move(x);
	cout << "data type of p is " << typeid(p).name() << endl;
	cout << x << endl;
	cout << p << endl;
}

/*
Q) if x got moved it should be empty, but how 100 is still out put int&& p = move(x);

Ans :- 
 This is a common point of confusion in C++.

When you write:
int x = 100;
int&& p = std::move(x);
and then print x and p, you see: 100 100 as output

Why?
std::move(x) does not move the value; it just casts x to an rvalue reference (int&&).
The actual "move" (i.e., transferring or emptying resources) only happens if you use x in a context where a move operation is defined 
(like moving from a std::string or std::vector).
For built-in types like int, there is no move semantics—copying and moving are the same, and the value is simply copied.

x is not emptied or changed; both x and p still have the value 100.
Only user-defined types with move constructors/assignments can have their resources "moved from" (and possibly left empty or in a valid but unspecified state).
*/