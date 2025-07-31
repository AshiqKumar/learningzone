#include<iostream>
using namespace std;

template<typename...TAIL> class Dummy
{
public:

};
template<typename HEAD, typename ... TAIL> class Dummy<HEAD, TAIL...> : Dummy<TAIL...>
{
private:
	HEAD data;
public:

	Dummy(HEAD h, TAIL... args) :Dummy<TAIL... >(args...), data(h)
	{
		cout << "No. of elements left further ..." << sizeof...(args) << endl;
		cout << "data " << h << endl;
	}

};


//***************************
int main()
{
	Dummy<int, float, double> obj1(10,12.34f, 56.12);
	//Dummy<int, float, int, char> obj1(10, 12.34f, 56, 'c');
}