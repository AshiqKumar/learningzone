#include <memory>
#include <iostream>
using namespace std;

int main()
{
	shared_ptr<int> p1(new int(42));
	weak_ptr<int> wp(p1);
	p1.reset(); // The initial shared_ptr is reset, deleting the managed object
	try 
	{
		shared_ptr<int> p2(wp);   // The parameter 'wp' weak_ptr refers to an already deleted object
	}
	catch (const bad_weak_ptr& e) 
	{
		cout << e.what() << '\n';
	}
}