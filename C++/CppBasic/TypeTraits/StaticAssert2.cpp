#include<iostream>
#include<type_traits>
using namespace std;

template<typename T> class Dummy
{
	static_assert(tr1::has_virtual_destructor<T>::value, "Class Dummy does not have virtual destructor");
public:
	Dummy(){ }
	~Dummy(){}
};

template<typename T> class CB
{
	static_assert(tr1::is_class<T>::value, "Must instantiate class types only");
public:
	CB(){ }
	~CB(){ };
};

class CC
{
public:
	CC(){}
};

int main()
{
	//Dummy<int> obj1;
	//CB<int> obj2;
	//CB<CC> obj3;
	
}