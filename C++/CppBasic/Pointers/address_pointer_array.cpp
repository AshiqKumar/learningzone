/*C++ Program to display address of elements of an array using both array and pointers*/

#include <iostream>
using namespace std;

int main()
 {
    float a[5];
    float *ptr;
    
	cout << "Displaying address using arrays: "<<endl;
	for (int i = 0; i < 5; ++i) 
		{
        	cout << "&a[" << i << "] = " << &a[i] <<endl;
    		}

 	ptr = a;   // ptr = &a[0]
        cout<<"\nDisplaying address using pointers: "<< endl;
    	for (int i = 0; i < 5; ++i) 
		{
        	cout << "ptr + " << i << " = "<<ptr+i <<endl;
  	        }

	cout<<"Displaying address using pointers notation: "<< endl;
	for (int i = 0; i < 5; ++i) 
		{
        	cout <<"a+" <<i<< " = "<< a+i <<endl;
		}
       return 0;
}
