#include <iostream>
#include <cstring>

class MyString {
    char* data;
public:
    // Constructor
    MyString(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // Shallow copy constructor
    // MyString(const MyString& other) : data(other.data) {}

    // Deep copy constructor
    MyString(const MyString& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // Destructor
    ~MyString() {
        delete[] data;
    }

    void set(const char* str) {
        strcpy(data, str);
    }

    void print() const {
        std::cout << data << std::endl;
    }
};

int main() {
    MyString s1("Hello");
    MyString s2 = s1; // Deep copy

    s2.set("World");

    std::cout << "s1: "; s1.print(); // Output: Hello
    std::cout << "s2: "; s2.print(); // Output: World

    return 0;
}