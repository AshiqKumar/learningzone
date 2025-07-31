#include<iostream>
using namespace std;
//Generalized return type in C++ 14 now also works for normal functions other
//than lambdas
/*   C++ 11
auto fun1() -> double
{
	auto a = 10.32;
	cout << "fun1 called" << endl;
	return a;
}
*/
//-----C++ 14 style, deduces the return type without trailing return type syntax -----
auto fun1()
{
	auto a = 10.32;
	cout << "fun1 called" << endl;
	return a;
}
//----Also with multiple return statements in a function block, ensure all
//return types are same
auto fun2()
{
	cout << "fun2 called" << endl;
	int x = 1;
	if (x == 1)
		return 100;
	else
		return 200;
}
int main()
{
	cout << fun1() << endl;
	cout << fun2() << endl;
}