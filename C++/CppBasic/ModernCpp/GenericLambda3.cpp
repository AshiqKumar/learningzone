#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

int main()
{
	list<int> ls1{ 10,20,30,40,50,60 };
	list<float> ls2{ 23.21f, 67.56f, 89.32f };

	//A generic lambda to help us traverse either of the containers
	auto lm = [](auto &x)
	{
		cout << x << ",";
	};

	//TRAVERSE THE CONTAINERS
	for_each(ls1.begin(), ls1.end(), lm);
	cout << endl;
	for_each(ls2.begin(), ls2.end(), lm);
	cout << endl;
}