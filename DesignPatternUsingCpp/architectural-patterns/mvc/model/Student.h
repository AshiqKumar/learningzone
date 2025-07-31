#pragma once
#include <string>
#include <iostream>

/**
 * @brief Student entity class - represents a single student
 * 
 * This is a simple data class that holds student information.
 * It's part of the Model in MVC architecture.
 */
class Student {
private:
    int id;
    std::string name;
    std::string email;
    int age;
    double gpa;

public:
    // Constructors
    Student();
    Student(int id, const std::string& name, const std::string& email, int age, double gpa);
    
    // Getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    int getAge() const { return age; }
    double getGpa() const { return gpa; }
    
    // Setters
    void setId(int id) { this->id = id; }
    void setName(const std::string& name) { this->name = name; }
    void setEmail(const std::string& email) { this->email = email; }
    void setAge(int age) { this->age = age; }
    void setGpa(double gpa) { this->gpa = gpa; }
    
    // Utility methods
    std::string toString() const;
    bool isValid() const;
    
    // Operators
    bool operator==(const Student& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};
