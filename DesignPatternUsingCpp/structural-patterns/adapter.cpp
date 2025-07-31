
// The Adapter Pattern allows incompatible interfaces to work together. 
// It acts as a bridge between two incompatible interfaces by wrapping an existing class with a new interface.
// CAdapter is a subclass of Circle and a private subclass of StandardCircle
// It inherits the draw() method from Circle and the oldDraw() method from StandardCircle
// The constructor of CAdapter initializes the StandardCircle with the radius
// The draw() method calls oldDraw() to perform the drawing operation
// The constructor of CAdapter takes a diameter as an argument and divides it by 2 to get the radius

#include <iostream>
 
using namespace std;
 
class Circle 
{
 public:
    virtual void draw() = 0;
};
 
class StandardCircle 
{
public:
    StandardCircle(double radius) 
    {
        radius_ = radius;
        cout << "StandardCircle:  create. radius = "<< radius_ << endl;
    }
    void oldDraw() 
    {
        cout << "StandardCircle:  oldDraw. " << radius_ << endl;
    }
private:
    double radius_ ;
};
 
class CAdapter : public Circle, private StandardCircle 
{
public:
    CAdapter( double diameter) : StandardCircle(diameter/2) 
    {
        cout << "CAdapter: create. diameter = " << diameter << endl;
    }
    virtual void draw() 
    {
        cout << "CAdapter: draw." << endl;
        oldDraw();
    }
};
 
int main() 
{
    Circle*  c = new CAdapter(14);
    c->draw();
}