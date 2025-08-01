
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

class Wheel
{
    public:
        int size;
};

class Engine
{
    public:
        int horsepower;
};

class Body
{
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

class Builder
{
    public:
        virtual Wheel* getWheel() = 0;
        virtual Engine* getEngine() = 0;
        virtual Body* getBody() = 0;
};


class JeepBuilder : public Builder
{
    public:
        Wheel* getWheel()
        {
            Wheel* wheel = new Wheel();
            wheel->size = 22;
            return wheel;
        }    
        Engine* getEngine()
        {
            Engine* engine = new Engine();
            engine->horsepower = 400;
            return engine;
        }
        Body* getBody()
        {
            Body* body = new Body();
            body->shape = "SUV";
            return body;
        }
};

class NissanBuilder : public Builder 
{
    public:
        Wheel* getWheel()
        {
            Wheel* wheel = new Wheel();
            wheel->size = 16;
            return wheel;
        }

        Engine* getEngine()
        {
            Engine* engine = new Engine();
            engine->horsepower = 85;
            return engine;
        }
        Body* getBody()
        {
            Body* body = new Body();
            body->shape = "hatchback";
            return body;
        }
};

class Director 
{
    Builder* builder;
    public:
        void setBuilder(Builder* newBuilder)
        {
            builder = newBuilder;
        }

        Car* getCar()
        {
            Car* car = new Car();

            car->body = builder->getBody();

            car->engine = builder->getEngine();

            car->wheels[0] = builder->getWheel();
            car->wheels[1] = builder->getWheel();
            car->wheels[2] = builder->getWheel();
            car->wheels[3] = builder->getWheel();

            return car;
        }
};

int main()
{
    Car* car;
    Director director;
    JeepBuilder jeepBuilder;
    NissanBuilder nissanBuilder;

    cout<<"Jeep"<<endl;
    director.setBuilder(&jeepBuilder);
    car = director.getCar();
    car->specifications();

    cout<<endl;

    cout<<"Nissan"<<endl;
    director.setBuilder(&nissanBuilder);
    car = director.getCar();
    car->specifications();
    return 0;
}
//Usage: The client chooses a builder and asks the director to construct the car. The same construction process creates different car types.