#include<iostream>
#include<set>
using namespace std;

/*
About Set:
(i) Stores the values in sorted order. ( ascending to descending)
(ii) Stores only unique values, duplicate value if added are ignored.
(iii) Elements can only be inserted or deleted but cannot be modified.
(iv) We can erase more than 1 element by giving start iterator and end iterator position.
(v) Traversal using iterators.
(vi) Sets are implemented as Binary Search Tree.
*/

namespace c_std
{
	template<typename T> class less
	{
	public:
		bool operator()(const int& x, const int& y) const
		{
			return x > y;
		}
	};
}
int main()
{
	set<int, std::less<int>> s1;
	//populate some integers into the set
	s1.insert(20);
	s1.insert(30);
	s1.insert(10);
	s1.insert(5);
	s1.insert(22);
	cout << "contents of the set s1 " << endl;
	for (auto &x : s1)
	{
		cout << x << " ";
	}
	cout << endl << "---------------" << endl;
	set<int, c_std::less<int>> s2;
	s2.insert(20);
	s2.insert(30);
	s2.insert(10);
	s2.insert(5);
	s2.insert(22);
	cout << "contents of the set s2 " << endl;
	for (auto &x : s2)
	{
		cout << x << " ";
	}
	cout << endl;
}