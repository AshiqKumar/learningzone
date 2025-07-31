#include<iostream>
#include<string>

using namespace std;

template<typename... Policy> class PolicyVariadic :public Policy...
{
public:
	//A constructor as a variadic function template
	template<typename... Args> PolicyVariadic(const Args... arg):Policy(arg)...
	{

	}
};

//-----------------POLICY CLASSES ---------------

class PolicyOne
{
private:
	string s1;
public:
	PolicyOne(const char* s) :s1(s) {}
	void ExecutePolicyOne()
	{
		cout << "Executed..." << s1 << endl;
	}
};

class PolicyTwo
{
private:
	string s1;
public:
	PolicyTwo(const char* s) :s1(s) {}
	void ExecutePolicyTwo()
	{
		cout << "Executed..." << s1 << endl;
	}
};

class PolicyThree
{
private:
	int s1;
public:
	PolicyThree(const int s) :s1(s) {}
	void ExecutePolicyThree()
	{
		cout << "Executed Policy Three with value " << s1 << endl;
	}
};
//------------- consumer ------------
int main()
{
	PolicyVariadic<PolicyOne, PolicyTwo> obj1("Policy One", "Policy Two");
	obj1.ExecutePolicyOne();
	obj1.ExecutePolicyTwo();
	cout << "===================" << endl;
	PolicyVariadic<PolicyOne, PolicyTwo, PolicyThree> obj2("Policy One", "Policy Two", 200);
	obj2.ExecutePolicyOne();
	obj2.ExecutePolicyTwo();
	obj2.ExecutePolicyThree();
}