#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

/*
	- Algorithms : 'all_of', 'any_of' & 'none_of'
	These functions check if the supplied unary predicate function
	returns true for all, any or no element in a range.
*/
int main()
{
	//Lambda that returns 'true' if the number is a positive value 
	auto Positive = [](const int num) {return num > 0; };

	//Lambda that returns 'true' if the number is a zero
	auto Zero = [](const int num) {return num == 0; };

	//Lambda that returns 'true' if the input string is a empty string 
	auto Empty = [](const string &x) {return x.empty(); };
	//-------------------------------------------------------------
	int num1[] = { 10,20,30,40,50 };
	int num2[] = { 10,20,0,40,50 };
	int num3[] = { 10,20,30,-40,50 };

	cout << "all_of num1 is positive " << boolalpha << all_of(begin(num1), end(num1), Positive) << endl;
	cout << "all_of num2 is positive " << boolalpha << all_of(begin(num2), end(num2), Positive) << endl;
	cout << "all_of num3 is positive " << boolalpha << all_of(begin(num3), end(num3), Positive) << endl;
	cout << "------------------------" << endl;
	cout << "any_of num1 is zero " << boolalpha << any_of(begin(num1), end(num1), Zero) << endl;
	cout << "any_of num2 is zero " << boolalpha << any_of(begin(num2), end(num2), Zero) << endl;
	cout << "any_of num3 is zero " << boolalpha << any_of(begin(num3), end(num3), Zero) << endl;
	
	string data1[] = { "first","second", "third" };
	string data2[] = { "apple","","orange" };
	string data3[] = { "","","" };
	cout << "------------------------" << endl;
	cout << "all_of data1 is empty " << boolalpha << all_of(begin(data1), end(data1), Empty) << endl;
	cout << "all_of data2 is empty " << boolalpha << all_of(begin(data2), end(data2), Empty) << endl;
	cout << "all_of data3 is empty " << boolalpha << all_of(begin(data3), end(data3), Empty) << endl;
	cout << "------------------------" << endl;
	cout << "any_of data1 is empty " << boolalpha << any_of(begin(data1), end(data1), Empty) << endl;
	cout << "any_of data2 is empty " << boolalpha << any_of(begin(data2), end(data2), Empty) << endl;
	cout << "any_of data3 is empty " << boolalpha << any_of(begin(data3), end(data3), Empty) << endl;
	cout << "------------------------" << endl;
	cout << "none_of data1 is empty " << boolalpha << none_of(begin(data1), end(data1), Empty) << endl;
	cout << "none_of data2 is empty " << boolalpha << none_of(begin(data2), end(data2), Empty) << endl;
	cout << "none_of data3 is empty " << boolalpha << none_of(begin(data3), end(data3), Empty) << endl;
}