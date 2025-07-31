#include <iostream>
#include <string>

class Example {
public:
    std::string name;

    // Constructor using 'this' pointer to distinguish member from parameter
    Example(const std::string& name) {
        this->name = name; // 'this->name' is the member, 'name' is the parameter
    }

    // Member function returning 'this' for method chaining
    Example& setName(const std::string& name) {
        this->name = name;
        return *this; // returns reference to the current object
    }

    // Function to print the name
    void printName() {
        std::cout << "Name: " << this->name << std::endl;
    }

    // Static function (no 'this' pointer)
    static void staticFunction() {
        // std::cout << this->name; // ERROR: 'this' is not available here
        std::cout << "Static function called" << std::endl;
    }
};

int main() {
    Example obj("Initial");
    obj.printName(); // Output: Name: Initial

    obj.setName("Updated").printName(); // Method chaining, Output: Name: Updated

    Example::staticFunction(); // Output: Static function called

    return 0;
}