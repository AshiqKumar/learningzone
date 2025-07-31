/*
The State design pattern is a behavioral design pattern that allows an object to change its behavior dynamically based on its internal state. Instead of using multiple conditional statements (if-else or switch), this pattern encapsulates state-specific behavior into separate classes.
Key Components:
- Context – Maintains a reference to the current state and delegates behavior to it.
- State Interface – Defines common methods that all concrete states must implement.
- Concrete States – Implement the state-specific behavior.
How It Works:
- The Context class holds a reference to a State object.
- When the state changes, the Context switches to a different Concrete State.
- Each Concrete State defines behavior specific to that state.
Use Cases:
- Traffic Light System – Changes behavior based on red, yellow, and green states.
- Media Player – Switches between playing, paused, and stopped states.
- Document Workflow – Moves through draft, review, and published states.

Use Cases:
- Traffic Light System – Changes behavior based on red, yellow, and green states.
- Media Player – Switches between playing, paused, and stopped states.
- Document Workflow – Moves through draft, review, and published states

// Example: A simple state pattern implementation that prints "Hello world!" when in a happy mood.😊
*/

#include <iostream>

 //state interface.
class Mood
{
public:
        virtual ~Mood() { }
        virtual void talk()=0;
};


//concrete state.
class Happy : public Mood
{
public:
        void talk() { std::cout << "Hello world!" << std::endl; }
};

//The function hello_world uses the current state (mood) to perform an action (talk()).
void hello_world(Mood & mood)
{
        mood.talk();
}

int main()
{
        Happy mood;
        hello_world(mood);
        return 0;
}

/*
Note: Youu can add more states (e.g., Sad, Angry) by implementing the Mood interface.

Here are some common use cases for the State design pattern:

Traffic Light System:
Each light (Red, Yellow, Green) is a state with its own behavior. The system transitions between these states.

Media Player:
States like Playing, Paused, and Stopped each define different behaviors for play, pause, and stop actions.

Document Workflow:
A document can be in Draft, Review, or Published state, with different allowed actions in each state.

Vending Machine:
States like Idle, HasMoney, Dispensing, and OutOfStock control how the machine reacts to user input.

Network Connection:
States like Connected, Disconnected, and Connecting determine how data is sent or received.

Game Character:
States like Idle, Running, Jumping, or Attacking change the character’s behavior and responses.

Order Processing System:
An order can be in states like New, Paid, Shipped, Delivered, or Cancelled, each with specific transitions and actions.

Summary:
Use the State pattern whenever an object’s behavior depends on its state and it must change its behavior at runtime, 
making your code cleaner and easier to extend.
*/