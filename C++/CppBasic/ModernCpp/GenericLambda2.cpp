#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

int main()
{
	list<int> ls1;
	for (int i = 1; i <= 10; i++)
	{
		ls1.push_back(i);
	}

	auto fp = [](auto &x) { cout << x << endl; };


	for_each(ls1.begin(), ls1.end(),  fp);
}