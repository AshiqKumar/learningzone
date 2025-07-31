#include<iostream>
#include<type_traits>
#include<array>
using namespace std;

template<typename... T> auto MakeArray(T... pack)
{
	const auto pack_size = sizeof...(pack);
	static_assert(pack_size != 0, "Cannot call with NIL Args!");
	
	array<int, pack_size> arr = { pack... };
	
	return arr;
}

int main()
{
	auto data1= MakeArray(10, 20, 30, 40, 50);
	cout << "size of array" << data1.size() << endl;
	for (auto &x : data1) { cout << x << " "; }
	//MakeArray();
}