// CPP program to remove duplicate character 
// from character array and print in sorted 
// order 
//@Ashiq Kumar
#include <bits/stdc++.h> 
#include <iostream>
#include <string.h>

using namespace std; 
  
char *removeDuplicate(char str[], int n) 
{ 
    int len = strlen(str);
    int k = 0, i=0; // To store index of result  

    // Start from second character and add  
    // unique ones  
    for (int i=1; i<=len; i++)
    {
        // If different, increment k and add  
        // previous character  
        if (str[i-1] != str[i])
            str[k++] = str[i-1];

        else
            // Keep skipping (removing) characters  
            // while they are same.  
            while (str[i-1] == str[i])
                i++;
    }

    // Add last character and terminator  
    str[k++] = str[i-1];
    str[k] = '\0';

    // If all characters were unique  
     return str;

} 
  
int main()
{
//   char str1[] = "abbsffsshsshllhiqseeeskumabnnbttr";

     char str1[100];
     cout << "Enter a string: ";
     cin >> str1 ;
     int len=strlen(str1);

     char str2[len];
     strcpy(str2,str1);
     cout <<"Actual String::"<<"["<<str2<<"]"<<"Modified String::["<<removeDuplicate(str1,len) <<"]"<< endl;

}
