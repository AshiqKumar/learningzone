#include<iostream>
using namespace std;
#include<iostream>
using namespace std;

class Dummy
{
public:
	Dummy(){ cout << __FUNCSIG__ << endl; }
	Dummy(const Dummy &x){ cout << __FUNCSIG__ << endl; }
	~Dummy(){ cout << __FUNCSIG__ << endl; }
};


//const Dummy f1()
//{
//	cout << __FUNCSIG__ << endl;
//	Dummy obj1;
//	return obj1;
//}
//
// Dummy f2()
//{
//	cout << __FUNCSIG__ << endl;
//	Dummy obj1;
//	return obj1;
//}
 /*Dummy& f3()
 {
	 cout << __FUNCSIG__ << endl;
	 Dummy obj1;
	 return obj1;
 }*/
 /*void fun(Dummy &x)
 {
	 cout << __FUNCSIG__ << endl;
 }
 void fun(Dummy &&x)
 {
	 cout << __FUNCSIG__ << endl;
 }
 void fun(const Dummy &x)
 {
	 cout << __FUNCSIG__ << endl;
 }
 void pf(Dummy x)
 {
	 cout << __FUNCSIG__ << endl;
 }*/
 void fun(int &&x)
 {
	 cout << __FUNCSIG__ << endl;
 }
 void fun(const int &x)
 {
	 cout << __FUNCSIG__ << endl;
 }
 const int g()
 {
	 return 100;
 }
 int main()
 {
	 //Dummy obj(f1());
	 //fun(f1());
	 //fun(100);
	 fun(g());
	 int a=10;
	 
	 fun(a);
	 //const Dummy obj1;
	 //fun(obj1);
	 
 }