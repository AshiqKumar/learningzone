#include<iostream>
#include<type_traits>
using namespace std;

template<typename T1> class Dummy
{
	static_assert(tr1::is_pod<T1>::value, "Template argument cannot be a class type");
	
private:
	T1 a, b;
};
class CB
{
public:
	CB(){ }
	~CB(){ }
};

int main()
{
	Dummy<char> obj1;
	//Dummy<CB> obj2;  //error
	
}
