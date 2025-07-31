/*
The Observer pattern is a behavioral design pattern that defines a one-to-many dependency between objects. 
When one object (the subject) changes state, all its dependents (observers) are notified and updated automatically.
This is particularly useful in embedded systems where you might have multiple components that need to react to changes in state or events.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Observer interface
class Observer 
{
public:
    virtual void update(const string& message) = 0;
    virtual ~Observer() {}
};

// Subject class
class Subject 
{
    vector<Observer*> observers;
    string message;
public:
    void attach(Observer* obs) {
        observers.push_back(obs);
    }
    void detach(Observer* obs) {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }
    void setMessage(const string& msg) {
        message = msg;
        notify();
    }
    void notify() {
        for (auto obs : observers) {
            obs->update(message);
        }
    }
};

// Concrete Observer
class ConcreteObserver : public Observer {
    string name;
public:
    ConcreteObserver(const string& n) : name(n) {}
    void update(const string& message) override {
        cout << name << " received: " << message << endl;
    }
};

int main() {
    Subject subject;
    ConcreteObserver obs1("Observer1");
    ConcreteObserver obs2("Observer2");
    ConcreteObserver obs3("Observer3");

    subject.attach(&obs1);
    subject.attach(&obs2);

    subject.setMessage("Hello, Observers!");

    // Dynamically add another observer
    subject.attach(&obs3);
    subject.setMessage("Observer3 joined!");

    // Dynamically remove an observer
    subject.detach(&obs2);
    subject.setMessage("Observer2 left!");

    return 0;
}

/*
Here’s how your Observer pattern code works:

1. Observer Interface:

* Observer is an abstract class with a pure virtual function update().
* Any class inheriting from Observer must implement update().

2. Concrete Observer:

* ConcreteObserver implements the update() method.
* When notified, it prints the message with its name.

3. Subject:

* Maintains a list of Observer* (the observers).
* attach() adds observers to the list.
* setMessage() sets a new message and calls notify().
* notify() calls update() on all attached observers, passing the new message.

4. main():

* Creates a Subject and two ConcreteObserver objects.
* Attaches both observers to the subject.
* When setMessage() is called, both observers are notified and print the message.

output
Observer1 received: Hello, Observers!
Observer2 received: Hello, Observers!
Observer1 received: Another update!
Observer2 received: Another update!
*/

/*
The Observer pattern is needed when you want to:
* Loose coupling: The subject does not need to know the concrete details of its observers.
* Automatic notification: All observers are updated automatically when the subject changes.
* Dynamic relationships: Observers can be added or removed at runtime.
* Event-driven systems: Ideal for implementing publish/subscribe or event-listener mechanisms.

1. Event-driven programming
* Embedded systems often react to hardware events (button presses, sensor changes, interrupts).
* The Observer pattern allows you to register multiple handlers (observers) for these events, 
  so when an event occurs, all relevant parts of the system are notified automatically.

2.  Loose coupling 
* Hardware drivers (subjects) don’t need to know about the application logic (observers).
* This makes the code modular, maintainable, and easier to update or extend.

3.  Dynamic behavior
* In embedded systems, you might need to change the behavior of your application at runtime.
* For example, a sensor driver can notify multiple modules (logging, display, communication) when new data is available.

4. Reusability and scalability
* You can reuse the same subject code with different observers in different projects.
* Adding new features (like logging or alarms) is easy—just add a new observer.
* Example in Embedded Context: 
    Subject: GPIO button driver
    Observers: LED controller, logger, communication module
    When the button is pressed, the driver notifies all observers, which can then react (toggle LED, log event, send message).
*/