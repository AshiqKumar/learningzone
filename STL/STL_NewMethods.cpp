#include<iostream>
#include<vector>
using namespace std;

int main()
{
	vector<int> v1{ 10,20,30,40,50,60 };
	vector<int> v2{ 10,20,30,40,50,60 };
	auto itr1 = v1.begin();
	while (itr1 != v1.end())
	{
		*itr1 = *itr1 + 10;
		itr1++;
	}
	for (auto x : v1)
	{
		cout << x << ",";
	}
	cout << endl;
	cout << "---------------------" << endl;
	auto itr2 = v2.cbegin();
	while (itr2 != v2.cend())
	{
		*itr2 = *itr2 + 10;    //ERROR
		itr2++;
	}
	for (auto x : v2)
	{
		cout << x << ",";
	}
	cout << endl;
}