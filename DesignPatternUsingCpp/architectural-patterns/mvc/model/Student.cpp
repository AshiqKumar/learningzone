#include "Student.h"
#include <sstream>
#include <iomanip>

// Default constructor
Student::Student() : id(0), name(""), email(""), age(0), gpa(0.0) {}

// Parameterized constructor
Student::Student(int id, const std::string& name, const std::string& email, int age, double gpa)
    : id(id), name(name), email(email), age(age), gpa(gpa) {}

// Convert student to string representation
std::string Student::toString() const {
    std::ostringstream oss;
    oss << "Student{ID: " << id 
        << ", Name: " << name 
        << ", Email: " << email 
        << ", Age: " << age 
        << ", GPA: " << std::fixed << std::setprecision(2) << gpa << "}";
    return oss.str();
}

// Validate student data
bool Student::isValid() const {
    return id > 0 && 
           !name.empty() && 
           !email.empty() && 
           age > 0 && age < 120 && 
           gpa >= 0.0 && gpa <= 4.0;
}

// Equality operator
bool Student::operator==(const Student& other) const {
    return id == other.id;
}

// Stream output operator
std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << student.toString();
    return os;
}
