#include<iostream>
#include<map>
#include<string>
using namespace std;
//Example on 'owner_less' predicate function
int main()
{
	shared_ptr<int> s1 = make_shared<int>(10);
	shared_ptr<int> s2 = make_shared<int>(20);
	shared_ptr<int> s3 = make_shared<int>(30);
	shared_ptr<int> s4 = make_shared<int>(40);
	auto s5 = s3;  //sharing

	//map<weak_ptr<int>, string> mc;
	map<weak_ptr<int>, string, owner_less<weak_ptr<int>>> mc;
	mc[s1] = "first";
	mc[s2] = "second";
	mc[s4] = "Fourth";
	mc[s3] = "Third";
	
	mc[s5] = "Fifth";

	cout << "Total elements inside the container " << mc.size() << endl;
	for (auto &x : mc)
	{
		auto s = (x.first).lock();
		cout << *s  << ":" << x.second << endl;
	}

	return 0;
}