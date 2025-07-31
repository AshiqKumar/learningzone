// SFINAE lets you write templates that are only enabled for certain types or expressions,
// enabling powerful compile-time checks and overload selection in C++. (Metaprogramming concept)
// SFINAE (Substitution Failure Is Not An Error) is a C++ template metaprogramming technique that allows you to conditionally enable or 
// disable template instantiations based on the properties of types.
//decltype is a C++ keyword that deduces the type of an expression at compile time.
#include <type_traits>
#include <iostream>

template<typename T>
auto test(int) -> decltype(std::declval<T>().foo(), std::true_type{})  // trailing return type.(features of C++11.)
{
    return std::true_type{};
}

template<typename T>
std::false_type test(...) 
{
    return std::false_type{};
}

struct A { void foo() {} };
struct B {};

int main() {
    std::cout << decltype(test<A>(0))::value << std::endl; // prints 1 (A has foo)
    std::cout << decltype(test<B>(0))::value << std::endl; // prints 0 (B doesn't have foo)
}