/**
 * @file hierarchical_inheritance.cpp
 * @brief Demonstration of Hierarchical Inheritance in C++
 * 
 * Hierarchical inheritance occurs when multiple derived classes inherit
 * from a single base class, creating a tree-like structure.
 * 
 * Compile: g++ -std=c++17 -Wall -Wextra hierarchical_inheritance.cpp -o hierarchical_inheritance
 * Run: ./hierarchical_inheritance
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>

// ===== SHAPE HIERARCHY =====

/**
 * Base class - Shape
 * Common interface for all geometric shapes
 */
class Shape {
protected:
    std::string name;
    std::string color;
    double x, y;  // Position coordinates

public:
    Shape(const std::string& n, const std::string& c, double posX = 0, double posY = 0)
        : name(n), color(c), x(posX), y(posY) {
        std::cout << "Shape constructor: " << name << " (" << color << ")" << std::endl;
    }
    
    virtual ~Shape() {
        std::cout << "Shape destructor: " << name << std::endl;
    }
    
    // Pure virtual functions - must be implemented by derived classes
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    
    // Virtual functions with default implementation
    virtual void draw() const {
        std::cout << "Drawing " << color << " " << name << " at (" << x << ", " << y << ")" << std::endl;
    }
    
    virtual void move(double deltaX, double deltaY) {
        x += deltaX;
        y += deltaY;
        std::cout << name << " moved to (" << x << ", " << y << ")" << std::endl;
    }
    
    virtual void rotate(double angle) {
        std::cout << name << " rotated by " << angle << " degrees" << std::endl;
    }
    
    virtual void scale(double factor) {
        std::cout << name << " scaled by factor " << factor << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << color << " " << name << " at (" << x << ", " << y << ")" << std::endl;
        std::cout << "  Area: " << std::fixed << std::setprecision(2) << calculateArea() << std::endl;
        std::cout << "  Perimeter: " << calculatePerimeter() << std::endl;
    }
    
    // Getters
    std::string getName() const { return name; }
    std::string getColor() const { return color; }
    double getX() const { return x; }
    double getY() const { return y; }
    
    // Setter for color
    void setColor(const std::string& newColor) {
        color = newColor;
        std::cout << name << " color changed to " << color << std::endl;
    }
};

/**
 * Derived class 1 - Circle
 */
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r, const std::string& c = "Red", double x = 0, double y = 0)
        : Shape("Circle", c, x, y), radius(r) {
        std::cout << "Circle constructor: radius = " << radius << std::endl;
    }
    
    ~Circle() override {
        std::cout << "Circle destructor" << std::endl;
    }
    
    double calculateArea() const override {
        return 3.14159 * radius * radius;
    }
    
    double calculatePerimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void draw() const override {
        std::cout << "Drawing circle: center(" << x << ", " << y << "), radius=" << radius << std::endl;
        Shape::draw();  // Call base class method too
    }
    
    void scale(double factor) override {
        radius *= factor;
        std::cout << "Circle scaled: new radius = " << radius << std::endl;
    }
    
    // Circle-specific methods
    void calculateCircumference() const {
        std::cout << "Circumference: " << calculatePerimeter() << std::endl;
    }
    
    bool isPointInside(double px, double py) const {
        double distance = sqrt((px - x) * (px - x) + (py - y) * (py - y));
        return distance <= radius;
    }
    
    void displayInfo() const override {
        Shape::displayInfo();
        std::cout << "  Radius: " << radius << std::endl;
        std::cout << "  Diameter: " << 2 * radius << std::endl;
    }
    
    double getRadius() const { return radius; }
    void setRadius(double r) { radius = r; }
};

/**
 * Derived class 2 - Rectangle
 */
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h, const std::string& c = "Blue", double x = 0, double y = 0)
        : Shape("Rectangle", c, x, y), width(w), height(h) {
        std::cout << "Rectangle constructor: " << width << "x" << height << std::endl;
    }
    
    ~Rectangle() override {
        std::cout << "Rectangle destructor" << std::endl;
    }
    
    double calculateArea() const override {
        return width * height;
    }
    
    double calculatePerimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        std::cout << "Drawing rectangle: corner(" << x << ", " << y 
                  << "), size=" << width << "x" << height << std::endl;
        Shape::draw();
    }
    
    void scale(double factor) override {
        width *= factor;
        height *= factor;
        std::cout << "Rectangle scaled: new size = " << width << "x" << height << std::endl;
    }
    
    // Rectangle-specific methods
    bool isSquare() const {
        return abs(width - height) < 0.001;  // Account for floating point precision
    }
    
    double getDiagonal() const {
        return sqrt(width * width + height * height);
    }
    
    bool isPointInside(double px, double py) const {
        return (px >= x && px <= x + width && py >= y && py <= y + height);
    }
    
    void displayInfo() const override {
        Shape::displayInfo();
        std::cout << "  Dimensions: " << width << "x" << height << std::endl;
        std::cout << "  Diagonal: " << std::fixed << std::setprecision(2) << getDiagonal() << std::endl;
        std::cout << "  Is Square: " << (isSquare() ? "Yes" : "No") << std::endl;
    }
    
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    void setDimensions(double w, double h) { width = w; height = h; }
};

/**
 * Derived class 3 - Triangle
 */
class Triangle : public Shape {
private:
    double side1, side2, side3;

public:
    Triangle(double s1, double s2, double s3, const std::string& c = "Green", double x = 0, double y = 0)
        : Shape("Triangle", c, x, y), side1(s1), side2(s2), side3(s3) {
        if (!isValidTriangle()) {
            throw std::invalid_argument("Invalid triangle: sides don't satisfy triangle inequality");
        }
        std::cout << "Triangle constructor: sides = " << side1 << ", " << side2 << ", " << side3 << std::endl;
    }
    
    ~Triangle() override {
        std::cout << "Triangle destructor" << std::endl;
    }
    
    double calculateArea() const override {
        // Using Heron's formula
        double s = calculatePerimeter() / 2;  // semi-perimeter
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }
    
    double calculatePerimeter() const override {
        return side1 + side2 + side3;
    }
    
    void draw() const override {
        std::cout << "Drawing triangle: vertex(" << x << ", " << y 
                  << "), sides=" << side1 << ", " << side2 << ", " << side3 << std::endl;
        Shape::draw();
    }
    
    void scale(double factor) override {
        side1 *= factor;
        side2 *= factor;
        side3 *= factor;
        std::cout << "Triangle scaled: new sides = " << side1 << ", " << side2 << ", " << side3 << std::endl;
    }
    
    // Triangle-specific methods
    bool isValidTriangle() const {
        return (side1 + side2 > side3) && 
               (side1 + side3 > side2) && 
               (side2 + side3 > side1);
    }
    
    std::string getTriangleType() const {
        if (abs(side1 - side2) < 0.001 && abs(side2 - side3) < 0.001) {
            return "Equilateral";
        } else if (abs(side1 - side2) < 0.001 || abs(side2 - side3) < 0.001 || abs(side1 - side3) < 0.001) {
            return "Isosceles";
        } else {
            return "Scalene";
        }
    }
    
    bool isRightTriangle() const {
        // Check if any combination satisfies Pythagorean theorem
        double a2 = side1 * side1;
        double b2 = side2 * side2;
        double c2 = side3 * side3;
        
        return (abs(a2 + b2 - c2) < 0.001) || 
               (abs(a2 + c2 - b2) < 0.001) || 
               (abs(b2 + c2 - a2) < 0.001);
    }
    
    void displayInfo() const override {
        Shape::displayInfo();
        std::cout << "  Sides: " << side1 << ", " << side2 << ", " << side3 << std::endl;
        std::cout << "  Type: " << getTriangleType() << std::endl;
        std::cout << "  Is Right Triangle: " << (isRightTriangle() ? "Yes" : "No") << std::endl;
    }
    
    double getSide1() const { return side1; }
    double getSide2() const { return side2; }
    double getSide3() const { return side3; }
};

// ===== EMPLOYEE HIERARCHY =====

/**
 * Base class - Employee
 */
class Employee {
protected:
    std::string employeeId;
    std::string name;
    std::string department;
    double baseSalary;
    int yearsOfService;

public:
    Employee(const std::string& id, const std::string& n, const std::string& dept, double salary)
        : employeeId(id), name(n), department(dept), baseSalary(salary), yearsOfService(0) {
        std::cout << "Employee constructor: " << name << " (" << employeeId << ")" << std::endl;
    }
    
    virtual ~Employee() {
        std::cout << "Employee destructor: " << name << std::endl;
    }
    
    // Pure virtual functions
    virtual double calculateSalary() const = 0;
    virtual std::string getRole() const = 0;
    
    // Virtual functions with default implementation
    virtual void work() const {
        std::cout << name << " is working in " << department << " department" << std::endl;
    }
    
    virtual void attendMeeting() const {
        std::cout << name << " is attending a meeting" << std::endl;
    }
    
    virtual void takeBreak() const {
        std::cout << name << " is taking a break" << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << "Employee: " << name << " (" << employeeId << ")" << std::endl;
        std::cout << "  Role: " << getRole() << std::endl;
        std::cout << "  Department: " << department << std::endl;
        std::cout << "  Base Salary: $" << std::fixed << std::setprecision(2) << baseSalary << std::endl;
        std::cout << "  Total Salary: $" << calculateSalary() << std::endl;
        std::cout << "  Years of Service: " << yearsOfService << std::endl;
    }
    
    void promote() {
        baseSalary *= 1.1;  // 10% raise
        std::cout << name << " promoted! New base salary: $" << baseSalary << std::endl;
    }
    
    void incrementService() {
        yearsOfService++;
        std::cout << name << " completed " << yearsOfService << " years of service" << std::endl;
    }
    
    // Getters
    std::string getEmployeeId() const { return employeeId; }
    std::string getName() const { return name; }
    std::string getDepartment() const { return department; }
    double getBaseSalary() const { return baseSalary; }
    int getYearsOfService() const { return yearsOfService; }
};

/**
 * Derived class 1 - Developer
 */
class Developer : public Employee {
private:
    std::string programmingLanguage;
    int projectsCompleted;
    std::vector<std::string> skills;

public:
    Developer(const std::string& id, const std::string& n, const std::string& lang, double salary)
        : Employee(id, n, "Engineering", salary), programmingLanguage(lang), projectsCompleted(0) {
        std::cout << "Developer constructor: specializes in " << programmingLanguage << std::endl;
        skills.push_back(programmingLanguage);
    }
    
    ~Developer() override {
        std::cout << "Developer destructor" << std::endl;
    }
    
    double calculateSalary() const override {
        double bonus = projectsCompleted * 5000;  // $5000 per project
        double skillBonus = skills.size() * 2000; // $2000 per skill
        return baseSalary + bonus + skillBonus;
    }
    
    std::string getRole() const override {
        return "Software Developer";
    }
    
    void work() const override {
        std::cout << name << " is coding in " << programmingLanguage << std::endl;
    }
    
    // Developer-specific methods
    void writeCode() const {
        std::cout << name << " is writing " << programmingLanguage << " code" << std::endl;
    }
    
    void debugCode() const {
        std::cout << name << " is debugging code" << std::endl;
    }
    
    void completeProject() {
        projectsCompleted++;
        std::cout << name << " completed project #" << projectsCompleted << std::endl;
    }
    
    void learnSkill(const std::string& skill) {
        skills.push_back(skill);
        std::cout << name << " learned new skill: " << skill << std::endl;
    }
    
    void codeReview() const {
        std::cout << name << " is conducting code review" << std::endl;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << "  Primary Language: " << programmingLanguage << std::endl;
        std::cout << "  Projects Completed: " << projectsCompleted << std::endl;
        std::cout << "  Skills: ";
        for (size_t i = 0; i < skills.size(); ++i) {
            std::cout << skills[i];
            if (i < skills.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    const std::vector<std::string>& getSkills() const { return skills; }
    int getProjectsCompleted() const { return projectsCompleted; }
};

/**
 * Derived class 2 - Manager
 */
class Manager : public Employee {
private:
    int teamSize;
    std::vector<std::string> teamMembers;
    double bonusPercentage;

public:
    Manager(const std::string& id, const std::string& n, const std::string& dept, double salary, int team)
        : Employee(id, n, dept, salary), teamSize(team), bonusPercentage(15.0) {
        std::cout << "Manager constructor: manages team of " << teamSize << std::endl;
    }
    
    ~Manager() override {
        std::cout << "Manager destructor" << std::endl;
    }
    
    double calculateSalary() const override {
        double bonus = baseSalary * (bonusPercentage / 100.0);
        double teamBonus = teamSize * 1000;  // $1000 per team member
        return baseSalary + bonus + teamBonus;
    }
    
    std::string getRole() const override {
        return "Team Manager";
    }
    
    void work() const override {
        std::cout << name << " is managing the " << department << " team" << std::endl;
    }
    
    // Manager-specific methods
    void holdTeamMeeting() const {
        std::cout << name << " is holding a team meeting with " << teamSize << " members" << std::endl;
    }
    
    void assignTask(const std::string& task, const std::string& member) {
        std::cout << name << " assigned task '" << task << "' to " << member << std::endl;
    }
    
    void addTeamMember(const std::string& member) {
        teamMembers.push_back(member);
        teamSize++;
        std::cout << name << " added " << member << " to team. Team size: " << teamSize << std::endl;
    }
    
    void conductPerformanceReview(const std::string& member) const {
        std::cout << name << " is conducting performance review for " << member << std::endl;
    }
    
    void planProject() const {
        std::cout << name << " is planning new project for the team" << std::endl;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << "  Team Size: " << teamSize << std::endl;
        std::cout << "  Bonus Percentage: " << bonusPercentage << "%" << std::endl;
        if (!teamMembers.empty()) {
            std::cout << "  Team Members: ";
            for (size_t i = 0; i < teamMembers.size(); ++i) {
                std::cout << teamMembers[i];
                if (i < teamMembers.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
    
    int getTeamSize() const { return teamSize; }
    const std::vector<std::string>& getTeamMembers() const { return teamMembers; }
};

/**
 * Derived class 3 - Designer
 */
class Designer : public Employee {
private:
    std::string designTool;
    int designsCompleted;
    std::vector<std::string> designTypes;

public:
    Designer(const std::string& id, const std::string& n, const std::string& tool, double salary)
        : Employee(id, n, "Design", salary), designTool(tool), designsCompleted(0) {
        std::cout << "Designer constructor: uses " << designTool << std::endl;
    }
    
    ~Designer() override {
        std::cout << "Designer destructor" << std::endl;
    }
    
    double calculateSalary() const override {
        double designBonus = designsCompleted * 3000;  // $3000 per design
        double toolBonus = designTypes.size() * 1500;  // $1500 per design type
        return baseSalary + designBonus + toolBonus;
    }
    
    std::string getRole() const override {
        return "UI/UX Designer";
    }
    
    void work() const override {
        std::cout << name << " is creating designs using " << designTool << std::endl;
    }
    
    // Designer-specific methods
    void createDesign(const std::string& type) {
        designsCompleted++;
        if (std::find(designTypes.begin(), designTypes.end(), type) == designTypes.end()) {
            designTypes.push_back(type);
        }
        std::cout << name << " created " << type << " design #" << designsCompleted << std::endl;
    }
    
    void designReview() const {
        std::cout << name << " is reviewing design with stakeholders" << std::endl;
    }
    
    void createPrototype() const {
        std::cout << name << " is creating interactive prototype" << std::endl;
    }
    
    void userTesting() const {
        std::cout << name << " is conducting user testing sessions" << std::endl;
    }
    
    void learnDesignTool(const std::string& tool) {
        designTool = tool;
        std::cout << name << " learned new design tool: " << tool << std::endl;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << "  Primary Tool: " << designTool << std::endl;
        std::cout << "  Designs Completed: " << designsCompleted << std::endl;
        std::cout << "  Design Types: ";
        for (size_t i = 0; i < designTypes.size(); ++i) {
            std::cout << designTypes[i];
            if (i < designTypes.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    const std::vector<std::string>& getDesignTypes() const { return designTypes; }
    int getDesignsCompleted() const { return designsCompleted; }
};

// ===== DEMONSTRATION FUNCTIONS =====

void demonstrateShapeHierarchy() {
    std::cout << "\n=== SHAPE HIERARCHICAL INHERITANCE DEMO ===" << std::endl;
    
    std::cout << "\n1. Creating different shapes (all inherit from Shape):" << std::endl;
    Circle circle(5.0, "Red", 10, 10);
    Rectangle rectangle(8.0, 6.0, "Blue", 20, 15);
    Triangle triangle(3.0, 4.0, 5.0, "Green", 30, 20);
    
    std::cout << "\n2. Polymorphic behavior - all shapes can:" << std::endl;
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(7.0, "Purple", 0, 0));
    shapes.push_back(std::make_unique<Rectangle>(10.0, 4.0, "Orange", 15, 5));
    shapes.push_back(std::make_unique<Triangle>(6.0, 8.0, 10.0, "Yellow", 25, 10));
    
    for (const auto& shape : shapes) {
        shape->draw();
        shape->displayInfo();
        std::cout << "---" << std::endl;
    }
    
    std::cout << "\n3. Shape-specific operations:" << std::endl;
    circle.calculateCircumference();
    std::cout << "Point (12, 12) inside circle: " << (circle.isPointInside(12, 12) ? "Yes" : "No") << std::endl;
    
    std::cout << "Rectangle is square: " << (rectangle.isSquare() ? "Yes" : "No") << std::endl;
    std::cout << "Rectangle diagonal: " << rectangle.getDiagonal() << std::endl;
    
    std::cout << "Triangle type: " << triangle.getTriangleType() << std::endl;
    std::cout << "Is right triangle: " << (triangle.isRightTriangle() ? "Yes" : "No") << std::endl;
    
    std::cout << "\n4. Common operations on all shapes:" << std::endl;
    circle.move(5, 5);
    rectangle.scale(1.5);
    triangle.rotate(45);
    triangle.setColor("Pink");
}

void demonstrateEmployeeHierarchy() {
    std::cout << "\n=== EMPLOYEE HIERARCHICAL INHERITANCE DEMO ===" << std::endl;
    
    std::cout << "\n1. Creating different employees (all inherit from Employee):" << std::endl;
    Developer dev("DEV001", "Alice Johnson", "C++", 80000);
    Manager mgr("MGR001", "Bob Smith", "Engineering", 100000, 5);
    Designer des("DES001", "Carol Brown", "Figma", 75000);
    
    std::cout << "\n2. Employee-specific work activities:" << std::endl;
    dev.writeCode();
    dev.debugCode();
    dev.completeProject();
    dev.learnSkill("Python");
    dev.learnSkill("JavaScript");
    
    mgr.holdTeamMeeting();
    mgr.addTeamMember("Alice Johnson");
    mgr.addTeamMember("David Wilson");
    mgr.assignTask("Implement new feature", "Alice Johnson");
    mgr.planProject();
    
    des.createDesign("Website Layout");
    des.createDesign("Mobile App");
    des.createDesign("Logo");
    des.createPrototype();
    des.userTesting();
    
    std::cout << "\n3. Common employee activities:" << std::endl;
    std::vector<std::unique_ptr<Employee>> employees;
    employees.push_back(std::make_unique<Developer>("DEV002", "Eve Davis", "Java", 85000));
    employees.push_back(std::make_unique<Manager>("MGR002", "Frank Miller", "Marketing", 95000, 8));
    employees.push_back(std::make_unique<Designer>("DES002", "Grace Lee", "Adobe XD", 78000));
    
    for (const auto& emp : employees) {
        emp->work();
        emp->attendMeeting();
        emp->takeBreak();
        std::cout << "---" << std::endl;
    }
    
    std::cout << "\n4. Employee information and promotions:" << std::endl;
    dev.displayInfo();
    dev.promote();
    dev.incrementService();
    std::cout << "After promotion:" << std::endl;
    dev.displayInfo();
    
    std::cout << std::endl;
    mgr.displayInfo();
    
    std::cout << std::endl;
    des.displayInfo();
}

void demonstratePolymorphismInHierarchy() {
    std::cout << "\n=== POLYMORPHISM IN HIERARCHICAL INHERITANCE ===" << std::endl;
    
    std::cout << "\n1. Shape polymorphism - calculating total area:" << std::endl;
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(3.0, "Red"));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0, "Blue"));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0, "Green"));
    shapes.push_back(std::make_unique<Circle>(2.5, "Yellow"));
    
    double totalArea = 0;
    double totalPerimeter = 0;
    
    for (const auto& shape : shapes) {
        totalArea += shape->calculateArea();
        totalPerimeter += shape->calculatePerimeter();
        std::cout << shape->getName() << " - Area: " << shape->calculateArea() 
                  << ", Perimeter: " << shape->calculatePerimeter() << std::endl;
    }
    
    std::cout << "Total area of all shapes: " << std::fixed << std::setprecision(2) << totalArea << std::endl;
    std::cout << "Total perimeter of all shapes: " << totalPerimeter << std::endl;
    
    std::cout << "\n2. Employee polymorphism - calculating payroll:" << std::endl;
    std::vector<std::unique_ptr<Employee>> employees;
    employees.push_back(std::make_unique<Developer>("DEV003", "Henry Brown", "Python", 90000));
    employees.push_back(std::make_unique<Manager>("MGR003", "Ivy Chen", "Sales", 110000, 12));
    employees.push_back(std::make_unique<Designer>("DES003", "Jack Wilson", "Sketch", 80000));
    
    // Simulate some work
    if (auto dev = dynamic_cast<Developer*>(employees[0].get())) {
        dev->completeProject();
        dev->completeProject();
        dev->learnSkill("Machine Learning");
    }
    
    if (auto des = dynamic_cast<Designer*>(employees[2].get())) {
        des->createDesign("Banner");
        des->createDesign("Infographic");
    }
    
    double totalPayroll = 0;
    for (const auto& emp : employees) {
        double salary = emp->calculateSalary();
        totalPayroll += salary;
        std::cout << emp->getName() << " (" << emp->getRole() << ") - Salary: $" 
                  << std::fixed << std::setprecision(2) << salary << std::endl;
    }
    
    std::cout << "Total company payroll: $" << totalPayroll << std::endl;
}

void demonstrateHierarchyCharacteristics() {
    std::cout << "\n=== HIERARCHICAL INHERITANCE CHARACTERISTICS ===" << std::endl;
    
    std::cout << "\n1. Memory layout comparison:" << std::endl;
    std::cout << "sizeof(Shape): " << sizeof(Shape) << " bytes" << std::endl;
    std::cout << "sizeof(Circle): " << sizeof(Circle) << " bytes" << std::endl;
    std::cout << "sizeof(Rectangle): " << sizeof(Rectangle) << " bytes" << std::endl;
    std::cout << "sizeof(Triangle): " << sizeof(Triangle) << " bytes" << std::endl;
    
    std::cout << "\nsizeof(Employee): " << sizeof(Employee) << " bytes" << std::endl;
    std::cout << "sizeof(Developer): " << sizeof(Developer) << " bytes" << std::endl;
    std::cout << "sizeof(Manager): " << sizeof(Manager) << " bytes" << std::endl;
    std::cout << "sizeof(Designer): " << sizeof(Designer) << " bytes" << std::endl;
    
    std::cout << "\n2. Hierarchy structure:" << std::endl;
    std::cout << "Shape Hierarchy:" << std::endl;
    std::cout << "  Shape (base)" << std::endl;
    std::cout << "  ├── Circle" << std::endl;
    std::cout << "  ├── Rectangle" << std::endl;
    std::cout << "  └── Triangle" << std::endl;
    
    std::cout << "\nEmployee Hierarchy:" << std::endl;
    std::cout << "  Employee (base)" << std::endl;
    std::cout << "  ├── Developer" << std::endl;
    std::cout << "  ├── Manager" << std::endl;
    std::cout << "  └── Designer" << std::endl;
    
    std::cout << "\n3. Common interface benefits:" << std::endl;
    std::cout << "• All shapes support: calculateArea(), calculatePerimeter(), draw()" << std::endl;
    std::cout << "• All employees support: calculateSalary(), getRole(), work()" << std::endl;
    std::cout << "• Polymorphic containers can hold any derived type" << std::endl;
    std::cout << "• Code reuse through common base class functionality" << std::endl;
}

int main() {
    std::cout << "=== HIERARCHICAL INHERITANCE DEMONSTRATION ===" << std::endl;
    
    try {
        demonstrateShapeHierarchy();
        demonstrateEmployeeHierarchy();
        demonstratePolymorphismInHierarchy();
        demonstrateHierarchyCharacteristics();
        
        std::cout << "\n=== HIERARCHICAL INHERITANCE SUMMARY ===" << std::endl;
        std::cout << "\nKey Concepts Demonstrated:" << std::endl;
        std::cout << "✅ Multiple classes inheriting from single base class" << std::endl;
        std::cout << "✅ Tree-like inheritance structure" << std::endl;
        std::cout << "✅ Common interface across all derived classes" << std::endl;
        std::cout << "✅ Polymorphic behavior with base class pointers" << std::endl;
        std::cout << "✅ Pure virtual functions for contracts" << std::endl;
        std::cout << "✅ Specialized implementations in derived classes" << std::endl;
        std::cout << "✅ Code reuse through inheritance" << std::endl;
        
        std::cout << "\nBenefits of Hierarchical Inheritance:" << std::endl;
        std::cout << "• Common interface for related classes" << std::endl;
        std::cout << "• Code reuse through base class functionality" << std::endl;
        std::cout << "• Polymorphic containers and algorithms" << std::endl;
        std::cout << "• Easy to add new derived classes" << std::endl;
        std::cout << "• Clear separation of concerns" << std::endl;
        
        std::cout << "\nBest Practices:" << std::endl;
        std::cout << "• Use pure virtual functions for required interface" << std::endl;
        std::cout << "• Provide virtual destructors in base classes" << std::endl;
        std::cout << "• Keep base class interface stable" << std::endl;
        std::cout << "• Use override keyword in derived classes" << std::endl;
        std::cout << "• Consider composition for complex relationships" << std::endl;
        
        std::cout << "\nCommon Use Cases:" << std::endl;
        std::cout << "• GUI components (Widget → Button, TextBox, Label)" << std::endl;
        std::cout << "• Geometric shapes (Shape → Circle, Rectangle, Triangle)" << std::endl;
        std::cout << "• Employee types (Employee → Manager, Developer, Designer)" << std::endl;
        std::cout << "• Vehicle types (Vehicle → Car, Truck, Motorcycle)" << std::endl;
        std::cout << "• File types (File → TextFile, ImageFile, VideoFile)" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

/*
Hierarchical Inheritance Summary:

Structure:
         Base
        /  |  \
   Derived1 Derived2 Derived3
   
Key Features:
1. One base class, multiple derived classes
2. Tree-like structure
3. Common interface across all derived classes
4. Each derived class can specialize base functionality

Benefits:
- Code reuse through common base class
- Polymorphic behavior with containers
- Easy to add new derived classes
- Clear interface contracts with pure virtual functions
- Consistent API across related classes

Memory Layout:
Each derived class contains:
- Base class members
- Virtual table pointer (if virtual functions)
- Derived class specific members

Common Patterns:
1. Abstract base class with pure virtual functions
2. Template Method pattern (base class defines algorithm)
3. Strategy pattern (derived classes implement strategies)
4. Factory pattern (create derived objects polymorphically)

Use Cases:
- GUI frameworks (widgets, controls)
- Graphics systems (shapes, drawing objects)
- Game entities (characters, items, obstacles)
- File system (different file types)
- Network protocols (different message types)

Design Considerations:
- Keep base class interface minimal and stable
- Use pure virtual functions for required behavior
- Provide default implementations where appropriate
- Consider interface segregation for complex hierarchies
- Plan for future extensions

Performance:
- Virtual function call overhead (minimal)
- Memory efficient (shared base class code)
- Good cache locality for similar operations
- Enables compiler optimizations for polymorphic code
*/
