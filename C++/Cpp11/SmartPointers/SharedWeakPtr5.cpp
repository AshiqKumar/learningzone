#include<iostream>
#include<memory>
using namespace std;
class Dummy
{
	int a, b;
public:
	Dummy(int x=0, int y=0):a(x),b(y) { cout << "Dummy constructor called" << endl; }
	~Dummy() { cout << "Dummy destructor called" << endl; }
	void print() { cout << "Dummy-print called:" << this << endl; }
	int GetFirst() {	return a;	}
	int GetSecond() { return b; }
};

int main()
{
	shared_ptr<Dummy> sp1 = make_shared<Dummy>(10, 20);

	shared_ptr<int> data1 = make_shared<int>(sp1->GetFirst());
	shared_ptr<int> data2 = make_shared<int>(sp1->GetSecond());
	cout << boolalpha << *data1 << " is less than " <<  *data2 << ":"<< (data1 < data2) << endl;

	cout << boolalpha << *data1 << " is before " << *data2 << ":" << data1.owner_before(data2) << endl;
	cout << boolalpha << *data2 << " is before " << *data1 << ":" << data2.owner_before(data1) << endl;
}