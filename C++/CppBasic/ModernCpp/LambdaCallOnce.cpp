#include<iostream>
using namespace std;
void term()
{
	cout <<"Cannot call more than once" << endl;
	exit(1);
}

void Add(int x, int y)
{
	cout <<"Add called, sum =" << x+y << endl;
}
void Sub(int x, int y)
{
	cout <<"Sub called, Difference =" << x-y << endl;
}
int main()
{
	set_terminate(term);

	auto Oncelambda = [](auto binary)
		{
		    static bool once=false;
			return [=](auto x, auto y) mutable
			{
				if(once!=true)
				{
					once = true;
					return binary(x,y);
				}
				else
				{
					throw;
				}
			};
		};
	//Implement the lambda
	Oncelambda(Add)(10,20);
	Oncelambda(Sub)(20,30);
}
