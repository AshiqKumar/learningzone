#include<iostream>
using namespace std;
namespace ABC
{
	int x=20;
	void display()
		{
		 cout<<"in name space of ABC:"<<x<<endl;
		 cout<<x<<endl;
		 }
}

namespace XYZ
{
	 double x=90.8;
	
	void display()
		{
		 cout<<"in namespace of XYZ:"<<endl;
		 cout<<x<<endl;
		 }
}
main()
{
	cout<<"x:"<<ABC::x<<endl;
	XYZ::display();
}
