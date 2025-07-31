#include<iostream>
using namespace std;

//An array of reference types were not supported earlier, now it is supported in C++11

void Fun(const int(&ref1)[10])
{
	for (auto i = 0; i < 10; i++)
	{
		cout << ref1[i] << ",";
	}
}
int main()
{
	const int a[10] = { 10,20,30,40,50,60,70,80,90,100 };
	Fun(a);
	//BUT ALLOWED HERE
	auto &ref = a;   // now 'ref' is an array of reference types
	
	for (auto i = 0; i < 10; i++)
	{
		cout << ref[i] << ",";
	}
	cout << endl;
}