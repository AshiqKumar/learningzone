#include<iostream>
using namespace std;

//C++14, a variable template
template<typename T> constexpr T pi = T(3.1415926535897932385);

//C++14, a variable template in use
template<typename T> T circular_area(T r) 
{
	return pi<T> * r * r;
}

int main()
{
	auto darea = circular_area(5.5);//uses pi<double>
	auto farea = circular_area(5.5f);//uses pi<float>
	cout << "darea =" << darea << endl;
	cout << "farea =" << farea << endl;
}