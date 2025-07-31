/*
The code demonstrates how to swap two vectors efficiently using move semantics and displays their contents before and after the swap.
Move semantics avoid unnecessary deep copies, making the swap operation fast even for large container
*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;

void displayVector(const vector<string> &v)
{
	if (v.size() != 0)
	{
		for (auto &x : v)
		{
			cout << x << " ";
		}
		cout << endl;
	}
	else
	{
		cout << "vector is empty" << endl;
	}
}

template<typename T> 
void Swap(T &a, T &b)
{
	T temp(move(a));
	a = move(b);
	b = move(temp);
}

int main()
{
	vector<string> v1 = { "one", "two","three", "four", "five" };
	vector<string> v2 = { "six", "seven", "eight", "nine","ten" };

	displayVector(v1);
	displayVector(v2);
	
	/*
	1. v2 = move(v1);
		* The contents of v1 are moved to v2.
		* v2 now has: "one", "two", "three", "four", "five"
		* v1 is now empty.
	2. v1 = move(v2);
		* The contents of v2 are moved back to v1.
		* v1 now has: "one", "two", "three", "four", "five"
		* v2 is now empty.
	*/
	// cout << "after move" << endl;
	// v2 = move(v1);
	// v1 = move(v2);

/* The call swap(v1, v2); uses the standard library’s swap, not your Swap template.
   If you want to use your own, call Swap(v1, v2);. */
	cout << "after swap" << endl;
	swap(v1, v2);
	//Swap(v1, v2);
	displayVector(v1);
	displayVector(v2);
}