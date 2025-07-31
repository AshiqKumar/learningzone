#include<iostream>
using namespace std;

int main()
{
	//C++ 14 now supports binary literals
	auto num1 = 0B0100'0001;
	
	cout << "[100'0001] in decimal =" << num1 << endl;
	cout << "[100'0001] in char =" << (char) num1 << endl;
}