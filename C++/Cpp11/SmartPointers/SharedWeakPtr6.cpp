#include<iostream>
#include<map>
#include<string>
using namespace std;

int main()
{
	shared_ptr<int> s1 = make_shared<int>(10);
	shared_ptr<int> s2 = make_shared<int>(20);
	shared_ptr<int> s3 = make_shared<int>(30);
	shared_ptr<int> s4 = make_shared<int>(40);
	auto s5 = s3;  //sharing

	map<shared_ptr<int>, string> mc;
	mc[s1] = "first";
	mc[s2] = "second";
	mc[s3] = "Third";
	mc[s4] = "Fourth";
	mc[s5] = "Fifth";
	for (auto &x : mc)
	{
		cout << *x.first << ":" << x.second << endl;
	}

	cout << "===================" << endl;
	//shared_ptr<int> s6 = make_shared<int>(20);

	/*
	auto pr = make_pair(s6, "NewString");
	mc.insert(pr);
	for (auto &x : mc)
	{
		cout << *x.first << ":" << x.second << endl;
	}*/
	return 0;
}