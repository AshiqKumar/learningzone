#include<iostream>
#include<thread>
#include<mutex>
using namespace std;


struct Dummy 
{
private:
	mutex mx;
	//recursive_mutex mutex;
	int i;
public:
	Dummy(int x=100):i(x) {}

	void mul(int x) 
	{
		std::lock_guard<mutex> lock(mx);
		i *= x;
		cout << i << endl;
	}

	void div(int x) 
	{
		std::lock_guard<mutex> lock(mx);
		i /= x;
		cout << i << endl;
	}

	void Arithmetic(int x, int y) 
	{
		std::lock_guard<mutex> lock(mx);
		mul(x);
		div(y);
	}
};

int main()
{
	Dummy obj1;
	obj1.Arithmetic(10, 20);
}