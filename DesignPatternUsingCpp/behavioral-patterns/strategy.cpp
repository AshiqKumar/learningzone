/*

The Strategy design pattern is a behavioral design pattern that allows you to define a family of algorithms, encapsulate each one, 
and make them interchangeable at runtime. This pattern promotes composition over inheritance, enabling dynamic behavior changes without 
modifying the object's code.
Key Components:
- Context – Maintains a reference to a strategy object and delegates execution.
- Strategy Interface – Defines a common interface for all strategies.
- Concrete Strategies – Implement different variations of the algorithm.
Use Cases:
- Sorting algorithms – Easily switch between different sorting techniques.
- Payment processing – Handle multiple payment methods dynamically.
- Compression techniques – Choose between ZIP, RAR, or other formats.
- Navigation systems – Switch between shortest route, fastest route, etc.

*/
#include <iostream>
#include <string>

class Strategy
{
public:
        virtual ~Strategy() { }
        virtual std::string format(const std::string &, const std::string &) const=0;
};

class Formatter : public Strategy
{
public:
        std::string format(const std::string & s1, const std::string & s2) const
        {
                return s1 + " " + s2 + "!";
        }
};

void hello_world(const Strategy & strategy)
{
        std::cout << strategy.format("Hello", "world") << std::endl;
}

int main()
{
        hello_world(Formatter());
        return 0;

}
/*
Why use it?
Promotes composition over inheritance.
Makes it easy to switch algorithms at runtime.
Keeps code flexible, maintainable, and open for extension.

Example use cases:
Sorting algorithms, payment processing, compression techniques, navigation systems, etc.
*/
