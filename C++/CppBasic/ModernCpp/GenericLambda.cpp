#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

auto myLambda = [](const auto &x)
{
	return x*2;
};
int main()
{
	cout << "Using myLambda:"<< myLambda(14) <<endl;
	
}