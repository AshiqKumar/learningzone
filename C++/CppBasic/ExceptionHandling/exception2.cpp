#include<iostream>
using namespace std;
void division(const double a,const double b)throw();
int main()
{
	double operator1,operator2;
	cout<<"division of two no"<<endl;
//.............start an exception.....................
	try
	{
	 cout<<"enter the two no";
	 cin>>operator1;
	 cin>>operator2;
	
	division(operator1,operator2);//pssing two value to function that will analyze them.
	}

catch(const char*str)
	{
	 cout<<"\nBad Operator:"<<str;
	}
        cout<<"\n\n";
}

void division(const double a,const double b)throw()
	{
	 double result;
	 if(b==0) //if exception occure then throw a string to the function caller
	 throw;
	 result;
	 result=a/b;
	 cout<<"\n"<<a<<"/"<<b<<"="<<result;
	}
