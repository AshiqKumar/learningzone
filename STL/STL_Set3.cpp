#include<iostream>
#include<set>
#include<string>
using namespace std;

class person
{
private:
	int id;
	string name;
	//...
public:
	person(int x = 0, string n = "no_name") :id(x), name(n) {}
	int getid() const { return id; }
	string getname()const { return name; }
	void print()const { cout << "id =" << id << ", name=" << name << endl; }
};

namespace std
{
	template<> class less<person>
	{
	public:
		bool operator()(const person& p1, const person& p2) const
		{
			return p1.getid() < p2.getid();
		}
	};
}

int main()
{
	set<person> s1;     // set<person, less<person>>s1;
	s1.insert(person(100, "ganesh"));
	s1.insert(person(103, "ramesh"));
	s1.insert(person(20, "kumar"));
	s1.insert(person(50, "raju"));
	cout << "contents of set s1" << endl;
	for (auto &x : s1)
	{
		x.print();
	}
	cout << endl;
	//swap the sets
	set<person> s2;
	s2.swap(s1);
	cout << "size of set s1 after swap " << s1.size() << endl;
	cout << "contents of set s2, after swap" << endl;
	for (auto &x : s2)
	{
		x.print();
	}
	cout << endl;
}