#include<iostream>
#include<type_traits>
using namespace std;

template<typename T> void Add(const T a, const T b)
{
	static_assert(tr1::is_pod<T>::value, "Input parameters must be POD types");
	T c;
	//c = a + b;
	//cout << "sum is " << c << endl;
}
class Dummy
{
public:
	Dummy(){}
};
int main()
{
	Add(10, 20);
	Dummy obj1, obj2;
	Add(obj1,obj2);
}