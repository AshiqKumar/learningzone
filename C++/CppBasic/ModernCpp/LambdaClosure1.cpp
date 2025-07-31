#include<iostream>

using namespace std;
void error()
{
	cout <<"Range Exceeded" << endl;
	exit(1);
}
int main()
{
	set_terminate(error);
	auto FromTo =[](auto start_val, auto end_val)
		{
			return [=]() mutable
					{
						if(start_val <= end_val)
						{
							return start_val++;
						}
						else
						{
							throw;
						}
					};
		};
	auto Range = FromTo(1,5);
	cout << Range() <<" ";
	cout << Range() <<" ";
	cout << Range()<< " ";
	cout << Range()<< " ";
	cout << Range()<< " ";
	cout << Range()<< " ";
}
