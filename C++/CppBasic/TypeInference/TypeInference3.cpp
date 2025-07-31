#include<iostream>
#include<vector>
using namespace std;
// 'auto' keyword only infers the data-type & not the other
// extended qualifiers 'const', 'volatile' & 'static'.
// The above qualifiers has to be manually added by the programmer
int main()
{
	const vector<int> v1;    // v1 is const vector<int> kind
	cout << "data type of v1 is " << typeid(v1).name() << endl;

	//auto a = v1;  // but 'a' is vector<int> kind
	const auto a = v1;  // now 'a' is const vector<int> kind
	cout << "data type of a is " << typeid(a).name() << endl;
	auto itr1 = v1.begin();
	auto itr2 = a.begin();
	//v1.insert(itr1, 100);  // cannot insert as its read-only
	a.insert(itr2,100);  // can insert as its read-write
	//----------------------------------

	auto &b = v1;   // 'b' is treated as "const vector<int>"
	auto itr3 = b.begin();
	//b.insert(itr3, 300);  
}