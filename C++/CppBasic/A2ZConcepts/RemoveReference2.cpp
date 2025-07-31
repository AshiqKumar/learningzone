#include<iostream>
#include<string>
using namespace std;

class Dummy
{
	
public:
	void operator =(const string& s)
	{
		cout << "operator =(const string&) called" << endl;
	}
	void operator =(string&& s)
	{
		cout << "operator =(string&&) called" << endl;
	}
};

int main()
{
	const string s1 = "Ganesh";
	Dummy obj1;
	//obj1 = s1;
	obj1 = (remove_reference_t<string>&&) s1;
	string s2 = "Ganesh";
	//obj1 = move(s2);
	//obj1 = (remove_reference_t<string>&&) s2;
}
