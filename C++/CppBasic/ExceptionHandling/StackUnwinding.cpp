#include <iostream>
using namespace std;

class Demo {
    string name;
public:
    Demo(const string& n) : name(n) {
        cout << "Constructor: " << name << endl;
    }
    ~Demo() {
        cout << "Destructor: " << name << endl;
    }
};

void func() {
    Demo d2("Local in func");
    throw runtime_error("Exception thrown in func()");
}

int main() {
    try {
        Demo d1("Local in main");
        func();
    } catch (const exception& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    return 0;
}