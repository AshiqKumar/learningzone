#include<iostream>
using namespace std;

template<typename T1, typename T2, typename T3> 
auto call(auto(*fp)(T2)->T1, T3 &&x) ->T1
{
	T1 x1;
	T2 y{};
	x1 = (*fp)(x);
	return x1;
}

int fun(float x)
{
	cout << __FUNCSIG__ << endl;
	return 100;
}

int main()
{
	call<int, float, int>(&fun, 100);
}