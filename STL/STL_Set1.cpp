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

int main()
{
	set<int> s1;
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
	set<int> s2;
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
	//lets erase value 20 from set s1
	auto itr = s1.find(20);
	if (itr != s1.end())
	{
		s1.erase(itr);
	}
	cout << endl << "----contents of s1 after erasing 20 -----------" << endl;
	for (auto &x : s1)
	{
		cout << x << " ";
	}

	//lets erase a range of values from 10 to 22 from set s2
	auto itr1 = s2.find(10);
	auto itr2 = s2.find(30);
	s2.erase(itr1,itr2);
	cout << endl << "----contents of s2 after erasing a range of values-----" << endl;
	for (auto &x : s2)
	{
		cout << x << " ";
	}
	cout << endl;
}