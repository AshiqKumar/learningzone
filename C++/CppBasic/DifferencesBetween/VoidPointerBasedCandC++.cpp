//In C, a void pointer can directly be assigned to some other pointer like int *, char *. But in C++, a void pointer must be explicitly typcasted.

#include <stdio.h> 
int main() 
{ 
   void *vptr; 
   int *iptr = vptr; //In C++, it must be replaced with int *iptr=(int *)vptr;  
   return 0; 
}

//This is something we notice when we use malloc(). Return type of malloc() is void *. 
//In C++, we must explicitly typecast return value of malloc() to appropriate type,
// e.g., “int *p = (int *)malloc(sizeof(int))”. In C, typecasting is not necessary. 
