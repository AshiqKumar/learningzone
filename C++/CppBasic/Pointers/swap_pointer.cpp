#include <iostream>
using namespace std;

int main() 
{
    void swap(int*, int*);      // Function prototype

    int a = 1, b = 2;
    cout << "Before swaping" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    swap(&a, &b);

    cout << "\nAfter swaping" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    return 0;
}

void swap(int* n1, int* n2) 
{
    int temp;
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
