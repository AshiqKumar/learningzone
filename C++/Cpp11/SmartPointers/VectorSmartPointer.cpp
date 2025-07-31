#include<iostream>
#include<vector>
#include<memory>
using namespace std;

class Dummy
{
private:
	int a = 0, b = 0;
public:
	Dummy() = default;
	Dummy(int x, int y) :a(x), b(y) { cout << "Two arg. constructor" << endl; }
	void print() const { cout << "a = " << a << ",b=" << b << endl; }
	~Dummy() { cout << "Dummy destructor" << endl; }
};

int main()
{
	vector<unique_ptr<Dummy>> v1;
	for (auto &x : { 1,2,3,4,5 })
	{
		auto i = make_unique<Dummy>(x, x + 10);
		v1.push_back(move(i));

		//v1.push_back(make_unique<Dummy>(x, x + 10));
	}
	/*auto itr = v1.begin();
	while (itr != v1.end())
	{
		auto p = itr->get();
		p->print();
		itr++;
	}*/
	for (auto &itr : v1)
	{
		itr->print();
	}
}