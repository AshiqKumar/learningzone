#include<iostream>
#include<memory>
#include<vector>
#include<algorithm>
using namespace std;

class Dummy
{
	int a;
public:
	Dummy(int x = 0) :a(x) { cout << "Dummy constructor" << endl; }
	~Dummy() { cout << "Dummy destructor" << endl; }
	void print() { cout << "Dummy-print:" << a << endl; }
};


int main()
{
	vector<Dummy *> vect_ptr1;  //A vector of pointers
	//TRADITIONAL APPROACH
	vect_ptr1.push_back(new Dummy(10));
	vect_ptr1.push_back(new Dummy(20));
	vect_ptr1.push_back(new Dummy(30));
	vect_ptr1.push_back(new Dummy(40));
	vect_ptr1.push_back(new Dummy(50));

	vector<Dummy*>::iterator itr = vect_ptr1.begin();
	while (itr != vect_ptr1.end())
	{
		(*itr)->print();
		itr++;
	}
	//Now care should be taken to clean the HEAP 'int' instances
	itr = vect_ptr1.begin();
	while (itr != vect_ptr1.end())
	{
		delete *itr;
		itr++;
	}


	//***************MODERN APPROACH**************************
	//A vector of pointers
	vector<Dummy *> vect_ptr2{ new Dummy(10), new Dummy(20), new Dummy(30), new Dummy(40), new Dummy(50) };
	for (auto &x : vect_ptr2)
	{
		x->print();
	}
	for_each(vect_ptr2.begin(), vect_ptr2.end(),default_delete<Dummy>());
	return 0;
}
