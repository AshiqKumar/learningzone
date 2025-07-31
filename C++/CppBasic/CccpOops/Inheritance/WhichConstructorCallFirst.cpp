// This code demonstrates the order of constructor calls in inheritance.
// When a derived class object is created, the base class constructor
// is called first, followed by the derived class constructor

#include <iostream>
#include <cstring>
using namespace std;
class person {
protected:
    char name[20];
    int age;
public:
    person() {
        cout << "in default con of class_ person:" << endl;
        strcpy(name, "raj");
        age = 25;
    }
    void display() {
        cout << "name of the person:" << name << endl;
        cout << "age of the person:" << age << endl;
    }
};

class student : protected person {
private:
    char quali[20];
    char grade;
    int tolmark;
public:
    student() {
        cout << "in default con of drived class_student::" << endl;
        strcpy(quali, "b.tech");
        grade = 'A';
        tolmark = 500;
    }

    void display() {
        person::display();
        cout << "quali of the person::" << quali << endl;
        cout << "grade of the person::" << grade << endl;
        cout << "tolmark of the person::" << tolmark << endl;
    }
};

int main() {
    // Creating an object of the derived class 'student'
    // This will automatically call the base class constructor
    student s;
    s.display();
}

/*
O/p:
in default con of class_ person:
in default con of drived class_student::
name of the person:raj
age of the person:25
quali of the person::b.tech
grade of the person::A
tolmark of the person::500
*/