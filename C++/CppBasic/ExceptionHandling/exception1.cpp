#include<iostream>
using namespace std;
int main()
{
	double num1,num2,result;
	cout<<"input two number"<<endl;
	try
	{
	 cout<<"1st no:";
       	 cin>>num1;
	 cout<<"2nd no";
	 cin>>num2;
	 if(num2==0)
	 throw;
	 result=num1/num2;
	 cout<<"\n"<<num1<<"/"<<num2<<"="<<result<<"\n";
	}
	
	catch(...)
	{  }
}
