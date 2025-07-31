#include<iostream>
#include<future>
using namespace std;
/*
- The future itself is a structure pointing to a result that will be
   computed in the future.
- A 'async' function spawns a thread without the use of 'thread class' and
   return's an instance of type 'future'
*/
int main()
{
	auto lm = []()
	{
		cout << "I am a lambda " << endl;
	};

	auto ft = async(lm);       // (or)  auto ft = async(launch::async, lm);
	//ANY OTHER BUSINESS THAT THE PARENT THREAD WISHES HERE
	//..
	//..
	ft.get();  //Will block till 'async' call returns
	//A call to 'get' on a 'future' can called only once.

	if (ft.valid())
	{
		ft.get();
	}
	else
	{
		cout << "cannot call 'get' for the second time" << endl;
	}
}