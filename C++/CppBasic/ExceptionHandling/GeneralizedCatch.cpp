//Below program contains generalized catch statement to catch uncaught errors. Catch(…) takes care of all type of exceptions.

#include <iostream>
//#include<conio.h>
using namespace std;
int main()
{
int x[3]={-1,2,};
for(int i=0;i<2;i++)
{
int ex=x[i];
try {
if (ex > 0)
throw x;
else
throw 'ex';
} catch (int ex) {
cout << "Integer exception" <<endl;
} catch (char ex) {
cout << "Character exception"<<endl ;
}catch (...) {
cout << "Special exception"<<endl;;
}
}
//getch();
return 0;
}
