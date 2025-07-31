// The Factory Method Design Pattern is a creational pattern that defines an interface for creating objects,
// but lets subclasses decide which class to instantiate. It allows a class to defer instantiation to subclasses.
// This pattern is useful when you want to create objects that belong to a common interface or base class,
// but the exact type of object to be created is determined at runtime.
// The Factory Method Pattern is often used in conjunction with the Abstract Factory Pattern, which provides a way to create families of related or dependent objects.
#include <iostream>
#include <string>

using namespace std;

class Shape 
{
    public:
       virtual void Draw() = 0;
       static Shape* Create(string type);
};

class Circle : public Shape 
{
    public:
       void Draw() { cout << "I am circle" << endl; }
       friend class Shape;
};

class Square : public Shape 
{
    public:
       void Draw() { cout << "I am square" << endl; }
       friend class Shape;
};

Shape* Shape::Create(string type) 
{
    if ( type == "circle" ) return new Circle();
    if ( type == "square" ) return new Square();
    return NULL;
}

int main()
{
   Shape* obj1 = Shape::Create("circle");
   Shape* obj2 = Shape::Create("square");
   obj1->Draw();
   obj2->Draw();
}