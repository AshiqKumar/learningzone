// The Abstract Factory Pattern is a creational design pattern that provides an interface for creating families of related or dependent objects without
// specifying their concrete classes.
// It allows you to produce different types of objects using a common interface.
// The Abstract Factory Pattern is useful when you need to create a set of related objects that share a common interface, but you don't want to specify their concrete classes.
// It is often used in conjunction with the Factory Method Pattern, which provides a way to create individual objects.
#include <iostream>
#include <string>
using namespace std;

// Default Classes
class Device
{
public:
	virtual void send(string data) = 0;
};

class Wifi : public Device
{
public:
	void send(string data)
	{
		cout<<"Sent By Wifi: "<<data<<endl;
	}
};

class Bluetooth : public Device
{
public:
	void send(string data)
	{
		cout<<"Sent By Bluetooth: "<<data<<endl;
	}
};

// Abstract Factory Started
// Problem: Multiple if every function for handle the environment
// Solution: Build Abstract Factory and get method

class AbstractFactory
{
public:
	virtual Device* get() = 0;
};

class DeviceAbstractFactory : public AbstractFactory
{
public:
	Device* get()
	{
		if (true) // Conditions
		{
			return new Wifi;
		}
		else
		{
			return new Bluetooth;
		}
	}
};

// Main Usage
int main()
{
	AbstractFactory *abstractFactory = new DeviceAbstractFactory;
	Device* device;
	device = abstractFactory->get();	
	
	device->send("Abstract Factory Design Pattern Worked.");
}
