
// The **Builder Design Pattern** is a creational pattern that separates the construction of a complex object from its representation, 
// allowing the same construction process to create different representations.
// It is useful when you need to create an object that requires multiple steps or configurations,
// and you want to avoid a large constructor with many parameters or a telescoping constructor.
// Builder Pattern is useful for constructing complex objects step by step.
// It allows you to use the same construction process for different representations (e.g., Jeep vs. Nissan).
// The pattern improves code readability and flexibility when creating complex objects.

#include <iostream>
#include <string>
using namespace std;
// Add these class definitions
class Wheel {
public:
    int size;
};

class Engine {
public:
    int horsepower;
};

class Body {
public:
    string shape;
};
class Car
{
public:
    Wheel* wheels[4];
    Engine* engine;
    Body* body;

    void specifications(){
        cout<<"Body: "<<body->shape<<endl;
        cout<<"Engine Horsepower: "<<engine->horsepower<<endl;
        cout<<"Tire Size: "<<wheels[0]->size<<endl;
    }
};

class FluentCarBuilder {
    Car* car;
public:
    FluentCarBuilder() { car = new Car(); }
    FluentCarBuilder& setBody(const string& shape) {
        car->body = new Body();
        car->body->shape = shape;
        return *this;
    }
    FluentCarBuilder& setEngine(int horsepower) {
        car->engine = new Engine();
        car->engine->horsepower = horsepower;
        return *this;
    }
    FluentCarBuilder& setWheel(int size) {
        for(int i=0; i<4; ++i) {
            car->wheels[i] = new Wheel();
            car->wheels[i]->size = size;
        }
        return *this;
    }
    Car* build() {
        return car;
    }
};
int main()
{ //Use method chaining in main:
    cout << "Fluent Jeep" << endl;
    FluentCarBuilder fluentJeep;
    Car* jeep = fluentJeep.setBody("SUV")
                          .setEngine(400)
                          .setWheel(22)
                          .build();
    jeep->specifications();

    cout << endl;

    cout << "Fluent Nissan" << endl;
    FluentCarBuilder fluentNissan;
    Car* nissan = fluentNissan.setBody("hatchback")
                              .setEngine(85)
                              .setWheel(16)
                              .build();
    nissan->specifications();

    return 0;
}