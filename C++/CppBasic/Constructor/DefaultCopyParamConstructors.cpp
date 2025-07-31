#include <iostream>
using namespace std;

class Point {
    int x, y;
public:
    // Default constructor
    Point():x(0), y(0) {
        cout << "Default constructor called" << endl;
    }

    // Copy constructor
    Point(const Point& p) {
        x = p.x;
        y = p.y;
        cout << "Copy constructor called" << endl;
    }
    // Parameterized constructor
    Point(int a, int b) : x(a), y(b) {
        cout << "Parameterized constructor called" << endl;
    }
    void display() {
        cout << "x = " << x << ", y = " << y << endl;
    }
};

int main() {
    Point p; // Calls default constructor
    p.display();
    Point p1(10, 20); // // Calls parameterized constructor
    p1.display();
    Point p2 = p1; // Copy constructor is called
    p2.display();
    Point p3;
    p3 = p1; // Copy assignment operator is called
    p3.display();
    Point p5(p1); // Copy constructor is called, Demonstrating passing by value
    p5.display();
    return 0;
}