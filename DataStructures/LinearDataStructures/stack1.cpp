// This file demonstrates the use of the C++ Standard Library stack container.
// It includes basic operations such as push, pop, and top, along with checks for emptiness and size of the stack.
// The stack is used to store integers in this example.

#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> myStack;

    // Push elements onto the stack
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    cout << "Top element: " << myStack.top() << endl; // 30

    // Pop the top element
    myStack.pop();

    cout << "Top after pop: " << myStack.top() << endl; // 20

    // Check if stack is empty
    if (myStack.empty()) {
        cout << "Stack is empty." << endl;
    } else {
        cout << "Stack is not empty." << endl;
    }

    // Size of the stack
    cout << "Stack size: " << myStack.size() << endl;

    return 0;
}
