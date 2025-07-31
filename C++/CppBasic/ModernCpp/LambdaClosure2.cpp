#include<iostream>
using namespace std;

int main()
{
	auto Plus=[](auto x)
		{
		   return [=](auto y)
				   {
			   	   	   return x+y;
				   };
		};

	cout <<Plus(10)(20) << endl;
}
