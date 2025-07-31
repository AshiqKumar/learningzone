#include<iostream>
using namespace std;

int main()
{
	int a=10,b=20;

	auto Swap =[](auto &a, auto &b)
		{
		   auto temp = a;
		   a=b;
		   b=temp;
		};


	Swap(a,b);
	cout <<"After swap, a:" << a <<",b:" << b << endl;
	return 0;
}
