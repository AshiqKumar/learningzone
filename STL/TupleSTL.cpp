
//std::tuple is part of the C++ Standard Library (since C++11) and is defined in the <tuple> header.
//A tuple is a fixed-size collection of heterogeneous values (can store different types together).
//std::tuple can store multiple values of different types.
//Access elements with std::get<index>(tuple).
//Unpack (decompose)with std::tie., i.e decompose a tuple into individual variables in a single statement.
//Useful for returning multiple values from a function.

#include <iostream>
#include <tuple>
#include <string>
using namespace std;

int main() {
    // Create a tuple with different types
    tuple<int, string, double> t(1, "hello", 3.14);

    // Access elements using std::get
    cout << get<0>(t) << endl; // 1
    cout << get<1>(t) << endl; // hello
    cout << get<2>(t) << endl; // 3.14

    // Modify elements
    get<1>(t) = "world";
    cout << get<1>(t) << endl; // world

    // Unpack tuple into variables
    int a;
    string b;
    double c;
    tie(a, b, c) = t;
    cout << a << " " << b << " " << c << endl;

    return 0;
}