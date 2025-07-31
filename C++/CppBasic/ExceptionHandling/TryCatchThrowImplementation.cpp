//Below program contains single catch statement to handle errors.

#include <iostream>
//#include<conio.h>
using namespace std;
int main()
{
int a=10,b=0,c;
try //try block activates exception handling
{
if(b==0)
throw "Division by zero not possible";//throws exception
c=a/b;
}
catch(const char* ex)//catches exception
{
cout<<ex;
}
//getch();
return 0;
}

