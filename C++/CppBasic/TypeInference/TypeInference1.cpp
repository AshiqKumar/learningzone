#include<iostream>
#include<list>
using namespace std;

int main()
{
	//auto a;
	auto a = 10;
	list<int> ls1;
	//populate the list
	//for (int i = 1; i <= 10; i++)
	for (auto i = 1; i <= 10; i++)
	{
		ls1.push_back(i);
	}
	//traverse the list
	//for (list<int>::iterator itr = ls1.begin(); itr != ls1.end(); itr++)
	for (auto itr = ls1.begin(); itr != ls1.end(); itr++)
	{
		cout << *itr << ",";
	}
	cout << endl;
}