/*
The Command pattern provides flexibility, extensibility, and clean separation between 
the request, the invoker, and the action, making code easier to maintain and extend.

This example demonstrates:
- Command interface and concrete commands
- Receiver (Light)
- Invoker (RemoteControl)
- Queuing commands for later execution
*/

#include <iostream>
#include <queue>
using namespace std;

// Command interface
class Command 
{
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

// Receiver
class Light 
{
public:
    void on() { cout << "Light is ON" << endl; }
    void off() { cout << "Light is OFF" << endl; }
};

// Concrete Commands
class LightOnCommand : public Command 
{
    Light* light;
public:
    LightOnCommand(Light* l) : light(l) {}
    void execute() override { light->on(); }
};

class LightOffCommand : public Command 
{
    Light* light;
public:
    LightOffCommand(Light* l) : light(l) {}
    void execute() override { light->off(); }
};

// Invoker
class RemoteControl 
{
    Command* command;
public:
    void setCommand(Command* cmd) { command = cmd; }
    void pressButton() { command->execute(); }
};

int main() 
{
    Light livingRoomLight;
    LightOnCommand lightOn(&livingRoomLight);
    LightOffCommand lightOff(&livingRoomLight);

    // Command queue
    std::queue<Command*> commandQueue;

    // Add commands to the queue
    commandQueue.push(&lightOn);
    commandQueue.push(&lightOff);

    // Process (execute) all commands in the queue
    while (!commandQueue.empty()) {
        Command* cmd = commandQueue.front();
        cmd->execute();
        commandQueue.pop();
    }

    // Example of using the invoker directly
    RemoteControl remote;
    remote.setCommand(&lightOn);
    remote.pressButton(); // Light is ON
    remote.setCommand(&lightOff);
    remote.pressButton(); // Light is OFF

    return 0;
}

/*
In your code, instead of calling execute() on each command immediately, you store command objects in a queue:
std::queue<Command*> commandQueue;
commandQueue.push(&lightOn);
commandQueue.push(&lightOff);
This means you can collect a series of commands (actions to perform) and process them later.
while (!commandQueue.empty()) {
    Command* cmd = commandQueue.front();
    cmd->execute();
    commandQueue.pop();
}
what is the Benefits of this approach?
Ans:- Benefits of this approach include:
      1. Flexibility: You can add, remove, or change commands without modifying the invoker or receiver.
      2. Extensibility: New commands can be added easily without changing existing code.
      3. Decoupling: The invoker (RemoteControl) does not need to know the details of the commands or their receivers.
      4. Queuing: Commands can be queued for later execution, allowing for batch processing or delayed actions.
      5. Reusability: Commands can be reused in different contexts or with different receivers.
      6. Deferred execution: You can execute commands at a later time, which is useful for scenarios like undo/redo functionality.
      7. Order control: Commands are executed in the order they were added, allowing for predictable behavior.
      8. Logging: You can log commands for auditing or replaying actions later.

Q) Why we need the Command pattern ?
Ans:-
* Decouples the sender and receiver: The object that invokes an operation (like RemoteControl) does not need to know the details of the action or the receiver (like Light).
* Supports undo/redo: Commands can be stored and reversed if needed.
* Enables queuing and logging: Commands can be queued, scheduled, or logged for later execution.
* Supports parameterization: You can parameterize objects with operations, delay execution, or support macro commands (multiple commands as one).

Q) When creating a Command design pattern, consider these basic things:
Ans:-
1. Command Interface:
Define a common interface (usually with an execute() method) for all command objects.

2. Concrete Command Classes:
Implement the command interface for each specific action. Each command should know its receiver and call the appropriate action on it.

3. Receiver:
The object that actually performs the action (e.g., Light in your example).

4.Invoker:
The object that asks the command to execute (e.g., RemoteControl). It should not know the details of the action or the receiver.

5. Decoupling:
Ensure the invoker and the receiver are decoupled—invoker interacts only with the command interface.

6. Parameterization:
Commands can be parameterized with data needed for execution.

7. Support for Queuing/Logging/Undo:
If needed, design commands to be storable (for queuing, scheduling, or logging) and possibly reversible (for undo/redo).

8. Memory Management:
If commands are created dynamically, ensure proper cleanup to avoid memory leaks.

Summary:
The Command pattern lets you queue, schedule, or log actions as objects, giving you flexibility to execute them 
whenever and however you want, not just immediately.

*/