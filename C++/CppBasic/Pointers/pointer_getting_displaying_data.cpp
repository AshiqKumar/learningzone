/*c++ Program to insert and display data entered by using pointer notation.*/

#include <iostream>
using namespace std;

int main() 
{
    float a[5];
    
// Inserting data using pointer notation
     cout << "Enter 5 numbers: ";
         for (int i = 0; i < 5; ++i) 
        	{
		 cin >> *(a+i) ;
		 cin >> a[i] ;
                }
// Displaying data using pointer notation
	cout << "Displaying data: " << endl;
           for (int i = 0; i < 5; ++i) 
		{
                  cout << *(a+i) << endl ;
                  cout << a[i] << endl ;
                }

         return 0;
}
