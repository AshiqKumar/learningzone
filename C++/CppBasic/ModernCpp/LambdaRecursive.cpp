#include<iostream>
#include <functional>
using namespace std;

function<int(int)> factorial = [&factorial](int n)
{
return n <= 1 ? 1 : n * factorial(n - 1);
};

int main()
{  
   int x = factorial(4); 
   cout <<"x =" << x << endl;
   return 0;
}