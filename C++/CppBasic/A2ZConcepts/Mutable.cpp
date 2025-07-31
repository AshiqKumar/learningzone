/*
The `mutable` keyword allows a member variable of a class to be modified even if the object is declared as `const`.
*/

#include <iostream>

class TestMutable {
public:
    TestMutable() : valueOne(3), valueTwo (4){}

    mutable int valueOne;
    int valueTwo;
};

int main() {
  const  TestMutable test;
    std::cout << "Initial values: " << test.valueOne << ", " << test.valueTwo << std::endl;
    // Modifying mutable member
    test.valueOne = 10;
    // Note: This is allowed because valueOne is declared as mutable and the object is declared as const.
    std::cout << "After modifying valueOne: " << test.valueOne << ", " << test.valueTwo << std::endl;

    // Attempting to modify non-mutable member
    // test.valueTwo = 20; // Uncommenting this line will cause a compilation error

   /* &ptr: Prints the address of the pointer variable itself (where ptr is stored in memory).
      ptr: Prints the address stored in the pointer (i.e., the address of x).
      *ptr: Prints the value pointed to by the pointer (i.e., the value of x, which is 10).*/
    int *ptr = const_cast<int*>(&test.valueTwo);
    *ptr = 20; // This is allowed, but it's generally not recommended to use
    std::cout << "Address of ptr: " << &ptr << "  ptr: " << ptr <<" ptrValues: "<<*ptr<< std::endl;
    // Modifying valueTwo using const_cast
    std::cout << "After modifying valueTwo using const_cast: " << test.valueOne << ", " << test.valueTwo << std::endl;

    return 0;
}