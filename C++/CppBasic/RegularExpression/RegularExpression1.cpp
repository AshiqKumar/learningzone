#include<iostream>
#include<regex>
#include<string>
using namespace std;

int main()
{
	string input;
	regex integer("[[:digit:]]"); //A single digit
	cout << "enter any single digit number, 'q' to quit" << endl;
	while (true)
	{
		cin >> input;
		if (!cin) break;
		if (input == "q")
			break;
		if (regex_match(input, integer))
			cout << "integer" << endl;
		else
			cout << "invalid input" << endl;
	}
}