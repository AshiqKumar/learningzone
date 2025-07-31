#include<iostream>
#include<functional>
using namespace std;

int main()
{
	//define a recursive lambda
	//auto fib = [&fib](int x)  
	function<int(int)> fib = [&fib](int x)
	{
		return x <= 2 ? 1 : fib(x - 1)+ fib(x - 2);
	};

	cout << fib(20) << endl;
}