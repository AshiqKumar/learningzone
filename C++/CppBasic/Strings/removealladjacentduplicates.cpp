// C/C++ program to remove all adjacent duplicates from a string 
#include <iostream> 
#include <string.h> 

using namespace std; 

// Recursively removes adjacent duplicates from str and returns 
// new string. las_removed is a pointer to last_removed character 
char* removeUtil(char *str, char *last_removed) 
{ 
	// If length of string is 1 or 0 
	if (str[0] == '\0' || str[1] == '\0') 
		{
		cout<<"1::"<<str<<endl;
		return str; 
		}
        cout<<"1:1::"<<str<<endl;
	// Remove leftmost same characters and recur for remaining 
	// string 
	if (str[0] == str[1]) 
	{ 
		*last_removed = str[0]; 
		cout<<"2:last_removed::"<<last_removed<<endl;
		while (str[1] && str[0] == str[1]) 
		{
			str++; 
			cout<<"4 str++::"<<str<<endl;
		}
		str++;
		cout<<"5:1 str++::"<<str<<endl; 
		return removeUtil(str, last_removed); 
		cout<<"5:2 return::"<<str<<endl;
	} 

	// At this point, the first character is definiotely different 
	// from its adjacent. Ignore first character and recursively 
	// remove characters from remaining string 
	//char* rem_str = removeUtil(str+1, last_removed); 

	cout<<"6 before rem_str ::"<<str<<"  last_removed::" <<last_removed<<endl;
	char* rem_str = removeUtil(str+1, last_removed); 
	cout<<"7 after rem_str ::"<<rem_str<<"  last_removed::" <<last_removed<<endl;

	// Check if the first character of the rem_string matches with 
	// the first character of the original string 
	if (rem_str[0] && rem_str[0] == str[0]) 
	{ 
		*last_removed = str[0]; 
		cout<<"8 before inside if loop rem_str ::"<<rem_str<<endl;
		cout<<"9 inside if loop  last_removed ::"<<last_removed<<endl;
		return (rem_str+1); // Remove first character 
	} 

	// If remaining string becomes empty and last removed character 
	// is same as first character of original string. This is needed 
	// for a string like "acbbcddc" 
	if (rem_str[0] == '\0' && *last_removed == str[0])
	    {
	    cout<<"::  last after rem_str-- rem_str[0] = str[0] ::"<<rem_str<<endl; 
		return rem_str; 
		}
	// If the two first characters of str and rem_str don't match, 
	// append first character of str before the first character of 
	// rem_str. 
	cout<<"10::  last before rem_str--::"<<rem_str<<endl;
	rem_str--; 
	cout<<"11::  last after rem_str-- ::"<<rem_str<<" str::"<<str[0]<<endl;
	rem_str[0] = str[0]; 
	cout<<"12::  last after rem_str-- rem_str[0] = str[0] ::"<<rem_str<<endl;
	return rem_str; 
} 

char *remove(char *str) 
{ 
	char last_removed = '\0'; 
	cout<<"0 str::"<<str<<"  last_removed::" <<last_removed<<endl;
	return removeUtil(str, &last_removed); 
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
