#include<iostream>
#include<memory>
using namespace std;
class Dummy
{
public:
	Dummy() { cout << "Dummy constructor called" << endl; }
	~Dummy() { cout << "Dummy destructor called" << endl; }
};

class CB
{
private:
	Dummy * p;
public:
	CB():p(new(nothrow) Dummy) {}
	~CB() { delete p; }
};

void fun1(shared_ptr<CB> ptr)
{
	cout << "inside fun1, use count:" << ptr.use_count() << endl;
}
int main()
{
	//shared_ptr<CB> ptr1(new CB);
	shared_ptr<CB> ptr1 = make_shared<CB>();
	fun1(ptr1);
	return 0;
}