#include<iostream>
#include<type_traits>
using namespace std;

template<typename... T> void UnPack(T... pack)
{
	static_assert(sizeof...(pack) != 0, "Cannot call with NIL Args!");
    auto vals = {pack...};
	cout << "size of pack" << vals.size() << endl;
	for (auto &x : vals) { cout << x << " "; }
}

int main()
{
	UnPack(10, 20, 30, 40, 50);
	//UnPack();
}