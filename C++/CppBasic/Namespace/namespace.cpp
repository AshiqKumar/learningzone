#include<iostream>
using namespace std;
namespace ABC
{
	int x=20;
	struct st
		{
		 int arr[2];
		 float f;
		}v;
	void display()
		{
		 cout<<"x:"<<x<<endl;
		 cout<<"v:arr[0]"<<endl;
		 }
}
/*
main()
{

	cout<<ABC::x<<endl;
	ABC::display();
}
*/
/*
//................ All Members of ABC  come as globle....................//

using namespace ABC; 
main()
{
	cout<<x<<endl;
	display();
}
*/
//................name sapce inside name space......................//

namespace XYZ
	{
	 double d=90.8;
	}
main()
{
	cout<<"x:"<<ABC::x<<endl;
	ABC::display();
	cout<<"XYZ:"<<XYZ::d<<endl;
}
