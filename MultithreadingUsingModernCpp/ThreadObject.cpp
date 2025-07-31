#include<iostream>
#include<thread>
using namespace std;

class Dummy
{
private:
	int a;
	static int b;
public:
	Dummy(int x = 0) :a(x) { b = b + 1; }
	~Dummy() { cout << "Dummy destructor" << endl; }
	static void count() { cout << "Dummy-count, total objects " << b << endl; }
	void operator()()
	{
		cout << "Dummy-Function operator, a=" << a << endl;
	}
};
int Dummy::b;
int main()
{
	Dummy obj1;
	//A thread that would spawn a static member function of a class
	thread th1(&Dummy::count);
	th1.join();
	cout << "---------------" << endl;
	//A thread that would spawn a FUNCTOR member function
	thread th2(obj1);
	th2.join();
	cout << "---------------" << endl;
}