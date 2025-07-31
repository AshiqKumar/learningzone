#include<iostream>
#include<functional>
using namespace std;

class Dummy
{
private:
	int max, min;
public:
	Dummy(int x = 0, int y = 0) :max(x), min(y) { }
	auto getdata()   ->function<int(void)>
	{
		return  [this](){ return max-min; };   //[this] convention only for non-static mem.
		//return  [=](){ return max-min; };
	}
};

int main()
{
	Dummy obj1(10,20);
	auto lm = obj1.getdata();
	cout << lm() << endl;
}