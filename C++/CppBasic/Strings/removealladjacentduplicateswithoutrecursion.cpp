#include <iostream>
#include <string.h>

using namespace std;


char *remove(char *s)
{
   int i,j,k,l;
   for(i=0;s[i];i++)
	{
	 if(s[i]==s[i+1])
	   {
		for(j=i;s[j];j++)
		s[j]=s[j+1];
		i--;
	   }
	}
    return (s);

}

int main()
{
//     char str1[] = "abbsffsshsshllhiqseeeskumabnnbttr";

      char str1[100];
     cout << "Enter a string: ";
     cin >> str1 ;
     int len=strlen(str1);

     char str2[len];
     strcpy(str2,str1);
     cout <<"Actual String::"<<"["<<str2<<"]"<<"Modified String::["<<remove(str1) <<"]"<< endl;

}
