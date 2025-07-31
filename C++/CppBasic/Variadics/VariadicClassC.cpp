#include<iostream>
#include<vector>
using namespace std;

template<typename... Policies> class PolicyVariadic:public Policies...
{   };

class PolicyOne
{
public:
	void ExecutePolicyOne()
	{
		cout << "Policy One executed" << endl;
	}
};

class PolicyTwo
{
public:
	void ExecutePolicyTwo()
	{
		cout << "Policy Two executed" << endl;
	}
};

class PolicyThree
{
public:
	void ExecutePolicyThree()
	{
		cout << "Policy Three executed" << endl;
	}
};
//***************************
int main()
{
	PolicyVariadic<PolicyOne, PolicyTwo> obj1;
	obj1.ExecutePolicyOne();
	obj1.ExecutePolicyTwo();

	PolicyVariadic<PolicyOne, PolicyTwo, PolicyThree> obj2;
	obj2.ExecutePolicyOne();
	obj2.ExecutePolicyTwo();
	obj2.ExecutePolicyThree();
}