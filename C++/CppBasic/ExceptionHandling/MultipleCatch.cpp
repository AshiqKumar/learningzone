//Code for program contains multiple catch statements to handle exception.
#include <iostream>
using namespace std;
int main()
{
	int x[3]={-1,2,};
	for(int i=0;i<2;i++)
	{
	int ex=x[i];
		try 
		{
		if (ex > 0)
		throw ex;
		else
		throw 'ex';
		} 
		catch (const int ex) 
		{
		cout <<"Integer exception"<<endl;
		} 
		catch (const char ex) 
		{
		cout <<"Character exception"<<endl;
		}
	}
}
