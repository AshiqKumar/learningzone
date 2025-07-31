
#include <iostream>
//#include <conio.h>
using namespace std;

// working code..
// double division(int a, int b) {
//    if( b == 0 ) {
//       throw "Division by zero condition!";
//    }
//    return (a/b);
// }

// int main () {
//    int x = 50;
//    int y = 0;
//    double z = 0;
 
//    try {
//       z = division(x, y);
//       cout << z << endl;
//    } catch (const char* msg) {
//      cerr << msg << endl;
//    }

//    return 0;
// }

int main()
{
int a=10,b=0,c;
// while(1)
// {
   try //try block activates exception handling
   {
      if(b==0)
      {
      throw "Division by zero not possible";//throws exception
      }
   c=a/b;
   }
      catch(const char* ex)//catches exception
      {
      cout<<ex<<endl;
      }
return 0;
//}
}
