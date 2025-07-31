#include <iostream>
using namespace std;

// Function that returns a reference
int& getRef(int& x) {
    return x;
}

// Function using decltype(auto)
decltype(auto) getAuto(int& x) {
    return getRef(x); // preserves reference
}

int main() {
    int a = 10;
    decltype(auto) b = a;        // b is int
    decltype(auto) c = (a);      // c is int& (because (a) is an lvalue expression)
    decltype(auto) d = getAuto(a); // d is int&

    b = 20;
    c = 30;
    d = 40;

    cout << "a: " << a << endl; // a will be 40
    cout << "b: " << b << endl; // b will be 20
    cout << "c: " << c << endl; // c will be 40 (refers to a)
    cout << "d: " << d << endl; // d will be 40 (refers to a)
    return 0;
}