// The Prototype Design Pattern is a creational pattern that allows you to create new objects by copying (cloning) existing objects, 
// rather than creating them from scratch. This is useful when object creation is costly or complex.
// The Prototype Pattern is often used when you want to create a new object that is similar to an existing object, but with some modifications.
// It allows you to create new objects without knowing their concrete classes, as long as they implement a common interface.
// The Prototype Pattern is useful when you need to create a large number of similar objects, or when you want to avoid the overhead of creating new objects from scratch.

#include <iostream>
#include <string>
using namespace std;

// Default Classes
class Device
{
public:
    virtual void send(string data) = 0; 
    virtual int setSpeed(int value) = 0;
    virtual int getSpeed() = 0;
};

class Wifi : public Device
{
public:
    int speed;
    Wifi()
    {
        speed = 100;
    }
    int setSpeed(int value)
    {
        speed = value;
    }
    int getSpeed()
    {
        return speed;
    }
    void send(string data)
    {
        cout<<"Sent By Wifi: "<<data<<" Speed: "<<speed<<endl;
    }
};

class Bluetooth : public Device
{
public:
    int speed;
    Bluetooth(){
        speed = 8;
    }
    int setSpeed(int value)
    {
        speed = value;
    }
    int getSpeed()
    {
        return speed;
    }
    void send(string data)
    {
        cout<<"Sent By Bluetooth: "<<data<<" Speed: "<<speed<<endl;
    }
};

// Prototype Started
// Problem: Clone the old object
// Solution: Clone function

class Prototype
{
public:
    virtual Device* clone(Device *oldOneObject) = 0;
};

class BluetoothPrototype : public Prototype
{
public:
    Device* clone(Device* oldOneObject)
    {
        Device* newOneObject = new Bluetooth;
        newOneObject->setSpeed(oldOneObject->getSpeed());
        return newOneObject;
    }
};


// Main Usage
int main()
{
    Device* bluetoothObject = new Bluetooth;
    bluetoothObject->setSpeed(20);
    bluetoothObject->send("First Object");

    Prototype* prototypeObject = new BluetoothPrototype;
    Device* clonedBluetoothObject = prototypeObject->clone(bluetoothObject);
    clonedBluetoothObject->send("Cloned Object creatd");

    cout<<"If speed is same in two objects, it means clone worked successfully"<<endl;
}

// The Prototype Pattern lets you clone objects, avoiding the need to know their exact class or how to build them from scratch.
// It is useful for creating copies of objects with the same state.
// In this example, a Bluetooth object is cloned using the BluetoothPrototype, copying its speed to the new object.