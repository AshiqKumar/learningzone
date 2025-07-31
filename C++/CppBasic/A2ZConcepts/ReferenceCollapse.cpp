#include<iostream>
using namespace std;

template<typename T> T&& _forward(typename remove_reference<T>::type &t)
{
	cout << __FUNCSIG__ << endl;
	return static_cast<T&&>(t);
}

template<typename T>void MyFun(T &&x)
{
	cout << __FUNCSIG__ << endl;
}

template<typename T> void wrapper(T &&x)
{
	cout << __FUNCSIG__ << endl;
	MyFun(_forward<T>(x));
} 

int main()
{
	wrapper(100);
	int a = 200;
	wrapper(a);
}