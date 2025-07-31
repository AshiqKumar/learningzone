#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
using namespace std;
/*
	iota - This creates a range of sequentially increasing values, 
	   making use of the pre-increment operator (++i) to create the sequence.
*/
int main()
{
	vector<int> v1{ 10,20,30,40,50,60 };
	cout << "initial contents of the vector " << endl;
	for (auto x : v1)
	{
		cout << x << " ";
	}
	cout << endl;
	//reset the values of the vector 'iota'
	iota(v1.begin(), v1.end(), 100);
	cout << "contents of the vector after re-initialising" << endl;
	for (auto x : v1)
	{
		cout << x << " ";
	}
	cout << endl;
	random_shuffle(v1.begin(), v1.end());
	cout << "contents of the vector after shuffling" << endl;
	for (auto x : v1)
	{
		cout << x << " ";
	}
	cout << endl;
}