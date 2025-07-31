#include<iostream>
using namespace std;

void Fun1(int x)
{
	cout << "Fun1(int x) called" << endl;
}

void Fun2(double x)
{
	cout << "Fun2(double x) called" << endl;
}

int main()
{
	auto f1 = Fun1;
	auto &f2 = Fun2;
	(*f1)(100);  //derefence and then call, as it is a pointer
	f2(45.12); //direct call using the alias name, as it is reference type
}