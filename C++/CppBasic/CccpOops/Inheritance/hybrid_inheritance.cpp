/**
 * @file hybrid_inheritance.cpp
 * @brief Demonstration of Hybrid Inheritance in C++
 * 
 * Hybrid inheritance is a combination of two or more types of inheritance.
 * It typically involves hierarchical + multiple inheritance, often leading
 * to complex structures and the diamond problem.
 * 
 * Compile: g++ -std=c++17 -Wall -Wextra hybrid_inheritance.cpp -o hybrid_inheritance
 * Run: ./hybrid_inheritance
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>

// ===== ACADEMIC SYSTEM HYBRID INHERITANCE =====

/**
 * Base class - Person
 */
class Person {
protected:
    std::string name;
    int age;
    std::string address;
    std::string phoneNumber;

public:
    Person(const std::string& n, int a, const std::string& addr = "", const std::string& phone = "")
        : name(n), age(a), address(addr), phoneNumber(phone) {
        std::cout << "Person constructor: " << name << std::endl;
    }
    
    virtual ~Person() {
        std::cout << "Person destructor: " << name << std::endl;
    }
    
    virtual void introduce() const {
        std::cout << "Hi, I'm " << name << ", " << age << " years old" << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << "Person: " << name << ", Age: " << age << std::endl;
        if (!address.empty()) std::cout << "  Address: " << address << std::endl;
        if (!phoneNumber.empty()) std::cout << "  Phone: " << phoneNumber << std::endl;
    }
    
    // Getters
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getAddress() const { return address; }
    std::string getPhoneNumber() const { return phoneNumber; }
};

/**
 * Derived class 1 - Student (from Person)
 * This creates a hierarchical inheritance branch
 */
class Student : virtual public Person {  // Virtual inheritance to solve diamond problem
protected:
    std::string studentId;
    std::string major;
    double gpa;
    std::vector<std::string> courses;

public:
    Student(const std::string& n, int a, const std::string& id, const std::string& maj, double g = 0.0)
        : Person(n, a), studentId(id), major(maj), gpa(g) {
        std::cout << "Student constructor: " << name << " (" << studentId << ")" << std::endl;
    }
    
    virtual ~Student() {
        std::cout << "Student destructor: " << name << std::endl;
    }
    
    virtual void study() const {
        std::cout << name << " is studying " << major << std::endl;
    }
    
    virtual void attendClass(const std::string& courseName) {
        if (std::find(courses.begin(), courses.end(), courseName) == courses.end()) {
            courses.push_back(courseName);
        }
        std::cout << name << " attended " << courseName << " class" << std::endl;
    }
    
    virtual void takeExam(const std::string& subject) const {
        std::cout << name << " is taking " << subject << " exam" << std::endl;
    }
    
    void updateGPA(double newGpa) {
        gpa = newGpa;
        std::cout << name << "'s GPA updated to " << gpa << std::endl;
    }
    
    void displayInfo() const override {
        Person::displayInfo();
        std::cout << "  Student ID: " << studentId << std::endl;
        std::cout << "  Major: " << major << std::endl;
        std::cout << "  GPA: " << gpa << std::endl;
        std::cout << "  Courses: " << courses.size() << std::endl;
    }
    
    // Getters
    std::string getStudentId() const { return studentId; }
    std::string getMajor() const { return major; }
    double getGPA() const { return gpa; }
    const std::vector<std::string>& getCourses() const { return courses; }
};

/**
 * Derived class 2 - Employee (from Person)
 * This creates another hierarchical inheritance branch
 */
class Employee : virtual public Person {  // Virtual inheritance
protected:
    std::string employeeId;
    std::string department;
    double salary;
    std::string position;

public:
    Employee(const std::string& n, int a, const std::string& id, const std::string& dept, 
             double sal, const std::string& pos)
        : Person(n, a), employeeId(id), department(dept), salary(sal), position(pos) {
        std::cout << "Employee constructor: " << name << " (" << employeeId << ")" << std::endl;
    }
    
    virtual ~Employee() {
        std::cout << "Employee destructor: " << name << std::endl;
    }
    
    virtual void work() const {
        std::cout << name << " is working as " << position << " in " << department << std::endl;
    }
    
    virtual void attendMeeting() const {
        std::cout << name << " is attending a department meeting" << std::endl;
    }
    
    virtual double calculateSalary() const {
        return salary;
    }
    
    void promote(const std::string& newPosition, double salaryIncrease) {
        position = newPosition;
        salary += salaryIncrease;
        std::cout << name << " promoted to " << position << " with salary $" << salary << std::endl;
    }
    
    void displayInfo() const override {
        Person::displayInfo();
        std::cout << "  Employee ID: " << employeeId << std::endl;
        std::cout << "  Department: " << department << std::endl;
        std::cout << "  Position: " << position << std::endl;
        std::cout << "  Salary: $" << salary << std::endl;
    }
    
    // Getters
    std::string getEmployeeId() const { return employeeId; }
    std::string getDepartment() const { return department; }
    std::string getPosition() const { return position; }
    double getSalary() const { return salary; }
};

/**
 * Multiple inheritance - TeachingAssistant inherits from both Student and Employee
 * This creates the hybrid inheritance pattern
 */
class TeachingAssistant : public Student, public Employee {
private:
    std::vector<std::string> coursesTeaching;
    int hoursPerWeek;
    double hourlyRate;

public:
    TeachingAssistant(const std::string& n, int a, const std::string& studId, const std::string& maj,
                     const std::string& empId, const std::string& dept, double sal, int hours, double rate)
        : Person(n, a), Student(n, a, studId, maj), Employee(n, a, empId, dept, sal, "Teaching Assistant"),
          hoursPerWeek(hours), hourlyRate(rate) {
        std::cout << "TeachingAssistant constructor: " << name << " (Hybrid role)" << std::endl;
    }
    
    ~TeachingAssistant() override {
        std::cout << "TeachingAssistant destructor: " << name << std::endl;
    }
    
    // Override methods from both base classes
    void work() const override {
        std::cout << name << " is working as Teaching Assistant - teaching and studying" << std::endl;
    }
    
    double calculateSalary() const override {
        return Employee::calculateSalary() + (hoursPerWeek * hourlyRate * 4); // Monthly calculation
    }
    
    // TA-specific methods
    void teachCourse(const std::string& courseName) {
        if (std::find(coursesTeaching.begin(), coursesTeaching.end(), courseName) == coursesTeaching.end()) {
            coursesTeaching.push_back(courseName);
        }
        std::cout << name << " is teaching " << courseName << std::endl;
    }
    
    void gradeAssignments(const std::string& courseName) const {
        std::cout << name << " is grading assignments for " << courseName << std::endl;
    }
    
    void holdOfficeHours() const {
        std::cout << name << " is holding office hours for student consultation" << std::endl;
    }
    
    void assistProfessor(const std::string& task) const {
        std::cout << name << " is assisting professor with " << task << std::endl;
    }
    
    // Combined activities
    void dailyRoutine() const {
        std::cout << name << "'s daily routine:" << std::endl;
        study();        // Student activity
        work();         // Employee activity
        teachCourse("Introduction to Programming");  // TA activity
        attendClass("Advanced Algorithms");         // Student activity
        holdOfficeHours();  // TA activity
    }
    
    void displayInfo() const override {
        std::cout << "=== Teaching Assistant Information ===" << std::endl;
        Person::displayInfo();
        std::cout << "Student Details:" << std::endl;
        std::cout << "  Student ID: " << studentId << std::endl;
        std::cout << "  Major: " << major << std::endl;
        std::cout << "  GPA: " << gpa << std::endl;
        std::cout << "Employee Details:" << std::endl;
        std::cout << "  Employee ID: " << employeeId << std::endl;
        std::cout << "  Department: " << department << std::endl;
        std::cout << "  Position: " << position << std::endl;
        std::cout << "TA Details:" << std::endl;
        std::cout << "  Hours/Week: " << hoursPerWeek << std::endl;
        std::cout << "  Hourly Rate: $" << hourlyRate << std::endl;
        std::cout << "  Total Salary: $" << calculateSalary() << std::endl;
        std::cout << "  Courses Teaching: " << coursesTeaching.size() << std::endl;
    }
    
    const std::vector<std::string>& getCoursesTeaching() const { return coursesTeaching; }
    int getHoursPerWeek() const { return hoursPerWeek; }
};

// ===== VEHICLE SYSTEM HYBRID INHERITANCE =====

/**
 * Base class - Vehicle
 */
class Vehicle {
protected:
    std::string brand;
    std::string model;
    int year;
    double price;

public:
    Vehicle(const std::string& b, const std::string& m, int y, double p)
        : brand(b), model(m), year(y), price(p) {
        std::cout << "Vehicle constructor: " << brand << " " << model << std::endl;
    }
    
    virtual ~Vehicle() {
        std::cout << "Vehicle destructor: " << brand << " " << model << std::endl;
    }
    
    virtual void start() const {
        std::cout << brand << " " << model << " is starting" << std::endl;
    }
    
    virtual void stop() const {
        std::cout << brand << " " << model << " has stopped" << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << year << " " << brand << " " << model << " - $" << price << std::endl;
    }
    
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
};

/**
 * Hierarchical inheritance - different vehicle types
 */
class LandVehicle : virtual public Vehicle {
protected:
    int numberOfWheels;
    std::string fuelType;

public:
    LandVehicle(const std::string& b, const std::string& m, int y, double p, int wheels, const std::string& fuel)
        : Vehicle(b, m, y, p), numberOfWheels(wheels), fuelType(fuel) {
        std::cout << "LandVehicle constructor: " << numberOfWheels << " wheels" << std::endl;
    }
    
    virtual ~LandVehicle() {
        std::cout << "LandVehicle destructor" << std::endl;
    }
    
    virtual void drive() const {
        std::cout << brand << " " << model << " is driving on " << numberOfWheels << " wheels" << std::endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "  Wheels: " << numberOfWheels << ", Fuel: " << fuelType << std::endl;
    }
    
    int getNumberOfWheels() const { return numberOfWheels; }
    std::string getFuelType() const { return fuelType; }
};

class WaterVehicle : virtual public Vehicle {
protected:
    std::string propulsion;
    double displacement;

public:
    WaterVehicle(const std::string& b, const std::string& m, int y, double p, 
                 const std::string& prop, double disp)
        : Vehicle(b, m, y, p), propulsion(prop), displacement(disp) {
        std::cout << "WaterVehicle constructor: " << propulsion << " propulsion" << std::endl;
    }
    
    virtual ~WaterVehicle() {
        std::cout << "WaterVehicle destructor" << std::endl;
    }
    
    virtual void sail() const {
        std::cout << brand << " " << model << " is sailing using " << propulsion << std::endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "  Propulsion: " << propulsion << ", Displacement: " << displacement << " tons" << std::endl;
    }
    
    std::string getPropulsion() const { return propulsion; }
    double getDisplacement() const { return displacement; }
};

/**
 * Multiple inheritance - AmphibiousVehicle inherits from both LandVehicle and WaterVehicle
 * This demonstrates hybrid inheritance with diamond problem resolution
 */
class AmphibiousVehicle : public LandVehicle, public WaterVehicle {
private:
    std::string currentMode;
    bool isSealed;

public:
    AmphibiousVehicle(const std::string& b, const std::string& m, int y, double p,
                     int wheels, const std::string& fuel, const std::string& prop, double disp)
        : Vehicle(b, m, y, p), LandVehicle(b, m, y, p, wheels, fuel), 
          WaterVehicle(b, m, y, p, prop, disp), currentMode("land"), isSealed(true) {
        std::cout << "AmphibiousVehicle constructor: Hybrid land/water vehicle" << std::endl;
    }
    
    ~AmphibiousVehicle() override {
        std::cout << "AmphibiousVehicle destructor" << std::endl;
    }
    
    void switchToLandMode() {
        currentMode = "land";
        std::cout << brand << " " << model << " switched to land mode" << std::endl;
    }
    
    void switchToWaterMode() {
        if (isSealed) {
            currentMode = "water";
            std::cout << brand << " " << model << " switched to water mode" << std::endl;
        } else {
            std::cout << "Cannot switch to water mode - vehicle not sealed!" << std::endl;
        }
    }
    
    void move() const {
        if (currentMode == "land") {
            drive();
        } else {
            sail();
        }
    }
    
    void emergencyLanding() {
        if (currentMode == "water") {
            std::cout << "Emergency! Switching to land mode immediately" << std::endl;
            currentMode = "land";
        }
    }
    
    void sealCheck() {
        isSealed = true;  // Simulate seal check
        std::cout << "Seal integrity checked - vehicle ready for water mode" << std::endl;
    }
    
    void displayInfo() const override {
        std::cout << "=== Amphibious Vehicle Information ===" << std::endl;
        Vehicle::displayInfo();
        std::cout << "Land capabilities:" << std::endl;
        std::cout << "  Wheels: " << numberOfWheels << ", Fuel: " << fuelType << std::endl;
        std::cout << "Water capabilities:" << std::endl;
        std::cout << "  Propulsion: " << propulsion << ", Displacement: " << displacement << " tons" << std::endl;
        std::cout << "Current mode: " << currentMode << std::endl;
        std::cout << "Sealed: " << (isSealed ? "Yes" : "No") << std::endl;
    }
    
    std::string getCurrentMode() const { return currentMode; }
    bool getIsSealed() const { return isSealed; }
};

// ===== DEMONSTRATION FUNCTIONS =====

void demonstrateAcademicHybridInheritance() {
    std::cout << "\n=== ACADEMIC HYBRID INHERITANCE DEMO ===" << std::endl;
    
    std::cout << "\n1. Creating individuals with different roles:" << std::endl;
    Student student("Alice Johnson", 20, "STU001", "Computer Science", 3.8);
    Employee professor("Dr. Bob Smith", 45, "EMP001", "Computer Science", 75000, "Professor");
    
    std::cout << "\n2. Creating Teaching Assistant (Multiple Inheritance):" << std::endl;
    TeachingAssistant ta("Charlie Brown", 24, "STU002", "Computer Science", 
                        "EMP002", "Computer Science", 2000, 20, 15.0);
    
    std::cout << "\n3. Individual activities:" << std::endl;
    student.study();
    student.attendClass("Data Structures");
    student.takeExam("Algorithms");
    
    professor.work();
    professor.attendMeeting();
    
    std::cout << "\n4. Teaching Assistant activities (demonstrating hybrid nature):" << std::endl;
    ta.dailyRoutine();
    
    std::cout << "\n5. TA-specific tasks:" << std::endl;
    ta.teachCourse("Programming 101");
    ta.gradeAssignments("Programming 101");
    ta.assistProfessor("research project");
    ta.holdOfficeHours();
    
    std::cout << "\n6. Information display:" << std::endl;
    student.displayInfo();
    std::cout << "---" << std::endl;
    professor.displayInfo();
    std::cout << "---" << std::endl;
    ta.displayInfo();
    
    std::cout << "\n7. Polymorphic behavior:" << std::endl;
    std::vector<Person*> people = {&student, &professor, &ta};
    
    for (auto person : people) {
        person->introduce();
    }
    
    // Demonstrate access to specific interfaces
    std::cout << "\n8. Interface demonstration:" << std::endl;
    Student* taAsStudent = &ta;
    Employee* taAsEmployee = &ta;
    
    std::cout << "TA as Student:" << std::endl;
    taAsStudent->study();
    taAsStudent->takeExam("Advanced Topics");
    
    std::cout << "TA as Employee:" << std::endl;
    taAsEmployee->work();
    taAsEmployee->attendMeeting();
}

void demonstrateVehicleHybridInheritance() {
    std::cout << "\n=== VEHICLE HYBRID INHERITANCE DEMO ===" << std::endl;
    
    std::cout << "\n1. Creating different vehicle types:" << std::endl;
    LandVehicle car("Toyota", "Camry", 2023, 25000, 4, "Gasoline");
    WaterVehicle boat("Sea Ray", "Sundancer", 2023, 150000, "Inboard Motor", 5.2);
    
    std::cout << "\n2. Creating Amphibious Vehicle (Multiple Inheritance):" << std::endl;
    AmphibiousVehicle amphi("DUKW", "Duck", 1943, 75000, 6, "Gasoline", "Propeller", 2.5);
    
    std::cout << "\n3. Individual vehicle operations:" << std::endl;
    car.start();
    car.drive();
    car.stop();
    
    boat.start();
    boat.sail();
    boat.stop();
    
    std::cout << "\n4. Amphibious vehicle operations:" << std::endl;
    amphi.start();
    amphi.sealCheck();
    
    std::cout << "Land operations:" << std::endl;
    amphi.switchToLandMode();
    amphi.move();
    
    std::cout << "Transition to water:" << std::endl;
    amphi.switchToWaterMode();
    amphi.move();
    
    std::cout << "Emergency scenario:" << std::endl;
    amphi.emergencyLanding();
    amphi.move();
    
    std::cout << "\n5. Vehicle information:" << std::endl;
    car.displayInfo();
    std::cout << "---" << std::endl;
    boat.displayInfo();
    std::cout << "---" << std::endl;
    amphi.displayInfo();
    
    std::cout << "\n6. Polymorphic behavior:" << std::endl;
    std::vector<Vehicle*> vehicles = {&car, &boat, &amphi};
    
    for (auto vehicle : vehicles) {
        vehicle->start();
        vehicle->displayInfo();
        vehicle->stop();
        std::cout << "---" << std::endl;
    }
}

void demonstrateHybridInheritanceComplexity() {
    std::cout << "\n=== HYBRID INHERITANCE COMPLEXITY ANALYSIS ===" << std::endl;
    
    std::cout << "\n1. Memory layout analysis:" << std::endl;
    std::cout << "sizeof(Person): " << sizeof(Person) << " bytes" << std::endl;
    std::cout << "sizeof(Student): " << sizeof(Student) << " bytes" << std::endl;
    std::cout << "sizeof(Employee): " << sizeof(Employee) << " bytes" << std::endl;
    std::cout << "sizeof(TeachingAssistant): " << sizeof(TeachingAssistant) << " bytes" << std::endl;
    
    std::cout << "\nsizeof(Vehicle): " << sizeof(Vehicle) << " bytes" << std::endl;
    std::cout << "sizeof(LandVehicle): " << sizeof(LandVehicle) << " bytes" << std::endl;
    std::cout << "sizeof(WaterVehicle): " << sizeof(WaterVehicle) << " bytes" << std::endl;
    std::cout << "sizeof(AmphibiousVehicle): " << sizeof(AmphibiousVehicle) << " bytes" << std::endl;
    
    std::cout << "\n2. Inheritance structure:" << std::endl;
    std::cout << "Academic System:" << std::endl;
    std::cout << "       Person" << std::endl;
    std::cout << "      /      \\" << std::endl;
    std::cout << "  Student   Employee" << std::endl;
    std::cout << "      \\      /" << std::endl;
    std::cout << "   TeachingAssistant" << std::endl;
    std::cout << "   (Multiple Inheritance)" << std::endl;
    
    std::cout << "\nVehicle System:" << std::endl;
    std::cout << "       Vehicle" << std::endl;
    std::cout << "      /       \\" << std::endl;
    std::cout << " LandVehicle  WaterVehicle" << std::endl;
    std::cout << "      \\       /" << std::endl;
    std::cout << "  AmphibiousVehicle" << std::endl;
    std::cout << "  (Multiple Inheritance)" << std::endl;
    
    std::cout << "\n3. Virtual inheritance benefits:" << std::endl;
    std::cout << "• Solves diamond problem" << std::endl;
    std::cout << "• Single instance of base class" << std::endl;
    std::cout << "• Avoids ambiguity in member access" << std::endl;
    std::cout << "• Enables proper polymorphic behavior" << std::endl;
    
    std::cout << "\n4. Complexity considerations:" << std::endl;
    std::cout << "• Constructor calling order is complex" << std::endl;
    std::cout << "• Virtual inheritance has runtime overhead" << std::endl;
    std::cout << "• Method resolution can be ambiguous" << std::endl;
    std::cout << "• Debugging can be challenging" << std::endl;
}

int main() {
    std::cout << "=== HYBRID INHERITANCE DEMONSTRATION ===" << std::endl;
    
    try {
        demonstrateAcademicHybridInheritance();
        demonstrateVehicleHybridInheritance();
        demonstrateHybridInheritanceComplexity();
        
        std::cout << "\n=== HYBRID INHERITANCE SUMMARY ===" << std::endl;
        std::cout << "\nKey Concepts Demonstrated:" << std::endl;
        std::cout << "✅ Combination of multiple inheritance types" << std::endl;
        std::cout << "✅ Diamond problem and virtual inheritance solution" << std::endl;
        std::cout << "✅ Complex object with multiple roles/capabilities" << std::endl;
        std::cout << "✅ Constructor/destructor order in hybrid inheritance" << std::endl;
        std::cout << "✅ Polymorphic behavior at different inheritance levels" << std::endl;
        std::cout << "✅ Method overriding and ambiguity resolution" << std::endl;
        
        std::cout << "\nTypes of Hybrid Inheritance:" << std::endl;
        std::cout << "• Hierarchical + Multiple (most common)" << std::endl;
        std::cout << "• Multilevel + Multiple" << std::endl;
        std::cout << "• Hierarchical + Multilevel + Multiple" << std::endl;
        
        std::cout << "\nBenefits:" << std::endl;
        std::cout << "• Models complex real-world relationships" << std::endl;
        std::cout << "• Enables objects with multiple capabilities" << std::endl;
        std::cout << "• Flexible design for complex systems" << std::endl;
        std::cout << "• Code reuse from multiple inheritance paths" << std::endl;
        
        std::cout << "\nChallenges:" << std::endl;
        std::cout << "• Increased complexity and cognitive overhead" << std::endl;
        std::cout << "• Diamond problem requires virtual inheritance" << std::endl;
        std::cout << "• Complex constructor/destructor calling order" << std::endl;
        std::cout << "• Potential for ambiguous method resolution" << std::endl;
        std::cout << "• Debugging and maintenance difficulties" << std::endl;
        
        std::cout << "\nBest Practices:" << std::endl;
        std::cout << "• Use virtual inheritance to solve diamond problem" << std::endl;
        std::cout << "• Keep inheritance hierarchies as simple as possible" << std::endl;
        std::cout << "• Document inheritance relationships clearly" << std::endl;
        std::cout << "• Consider composition as alternative to complex inheritance" << std::endl;
        std::cout << "• Use interface segregation principle" << std::endl;
        std::cout << "• Test thoroughly for all inheritance paths" << std::endl;
        
        std::cout << "\nAlternatives to Consider:" << std::endl;
        std::cout << "• Composition over inheritance" << std::endl;
        std::cout << "• Strategy pattern for behaviors" << std::endl;
        std::cout << "• Mixin classes through templates" << std::endl;
        std::cout << "• Interface-based design" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

/*
Hybrid Inheritance Summary:

Definition:
Combination of two or more types of inheritance in a single program.
Most common: Hierarchical + Multiple inheritance.

Structure Example:
       A
      / \
     B   C
      \ /
       D    (D inherits from both B and C, which inherit from A)

Key Features:
1. Combines multiple inheritance patterns
2. Often involves diamond problem
3. Requires virtual inheritance for proper resolution
4. Creates complex object hierarchies
5. Enables multiple roles/capabilities in single object

Diamond Problem:
- Multiple inheritance paths to same base class
- Creates duplicate base class instances
- Causes ambiguity in member access
- Solved with virtual inheritance

Virtual Inheritance:
- Ensures single instance of base class
- Resolves diamond problem ambiguity
- Adds runtime overhead
- Changes constructor calling order

Constructor Order (with virtual inheritance):
1. Virtual base classes (in order of first appearance)
2. Non-virtual base classes (left to right)
3. Derived class

Common Patterns:
1. Role-based objects (Student-Employee)
2. Multi-capability devices (Amphibious vehicles)
3. Cross-cutting concerns (Logging, Serialization)
4. Complex domain models

Benefits:
- Models complex real-world relationships
- Enables rich object behavior
- Code reuse from multiple sources
- Flexible system design

Drawbacks:
- High complexity
- Difficult debugging
- Performance overhead
- Maintenance challenges
- Cognitive overhead

When to Use:
- Complex domain models
- Objects with truly multiple roles
- When composition is insufficient
- Rich behavior requirements

When to Avoid:
- Simple domain models
- Performance-critical code
- When composition would suffice
- Maintenance is primary concern

Best Practices:
- Use virtual inheritance for diamond resolution
- Keep hierarchies shallow
- Document relationships clearly
- Test all inheritance paths
- Consider composition alternatives
*/
