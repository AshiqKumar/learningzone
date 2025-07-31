#include<iostream>
#include<functional>
#include<memory>
using namespace std;
class Dummy
{
public:
	Dummy() { cout << "Dummy default constructor" << endl; }
	void print() { cout << "Dummy print called" << endl; }
	~Dummy() { cout << "Dummy destructor" << endl; }
};


int main()
{
	unique_ptr<Dummy> obj(new Dummy);
	/*    NOT ALLOWED BY VALUE
	auto lm = [=]()
	{
	cout << "inside lambda" << endl;
	obj->print();
	};
	*/
	/*  ALLOWED BY REFERENCE
	auto lm = [&]() 
				{
					cout << "inside lambda" << endl; 
					obj->print();
				};
	lm();
	*/
	
	/*
	// IN C++14, NOW ALLOWED WITH THE HELP OF MOVE AS WELL, WHERE 'x' IS AN ARBITRARY ENTITY
	auto lm = [x=move(obj)]()
	{
		cout << "inside lambda" << endl;
		x->print();
	};
	lm();
	*/
	
	// IN C++14, NOW ALLOWED WITH THE HELP OF MOVE AS WELL, WHERE 'x' IS AN ARBITRARY ENTITY
	[x = move(obj)]()
	{
		cout << "inside lambda" << endl;
		x->print();
	}();
}