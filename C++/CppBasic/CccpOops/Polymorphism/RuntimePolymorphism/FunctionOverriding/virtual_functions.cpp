// virtual_functions.cpp - Demonstrates virtual functions in C++
// Compile: g++ -std=c++17 -Wall -Wextra virtual_functions.cpp -o virtual_functions

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// 1. Basic Virtual Functions
class Animal {
protected:
    std::string name;
    
public:
    Animal(const std::string& n) : name(n) {}
    
    // Virtual function - can be overridden
    virtual void makeSound() const {
        std::cout << name << " makes a generic animal sound" << std::endl;
    }
    
    // Virtual function with implementation
    virtual void move() const {
        std::cout << name << " moves around" << std::endl;
    }
    
    // Non-virtual function - cannot be overridden polymorphically
    void breathe() const {
        std::cout << name << " breathes" << std::endl;
    }
    
    // Virtual destructor - important for polymorphism
    virtual ~Animal() {
        std::cout << "Animal " << name << " destructor called" << std::endl;
    }
    
    const std::string& getName() const { return name; }
};

class Dog : public Animal {
public:
    Dog(const std::string& n) : Animal(n) {}
    
    // Override virtual function
    void makeSound() const override {
        std::cout << name << " barks: Woof! Woof!" << std::endl;
    }
    
    void move() const override {
        std::cout << name << " runs on four legs" << std::endl;
    }
    
    // Dog-specific function
    void wagTail() const {
        std::cout << name << " wags tail happily" << std::endl;
    }
    
    ~Dog() override {
        std::cout << "Dog " << name << " destructor called" << std::endl;
    }
};

class Cat : public Animal {
public:
    Cat(const std::string& n) : Animal(n) {}
    
    void makeSound() const override {
        std::cout << name << " meows: Meow! Meow!" << std::endl;
    }
    
    void move() const override {
        std::cout << name << " walks gracefully" << std::endl;
    }
    
    // Cat-specific function
    void purr() const {
        std::cout << name << " purrs contentedly" << std::endl;
    }
    
    ~Cat() override {
        std::cout << "Cat " << name << " destructor called" << std::endl;
    }
};

class Bird : public Animal {
public:
    Bird(const std::string& n) : Animal(n) {}
    
    void makeSound() const override {
        std::cout << name << " chirps: Tweet! Tweet!" << std::endl;
    }
    
    void move() const override {
        std::cout << name << " flies in the sky" << std::endl;
    }
    
    // Bird-specific function
    void fly() const {
        std::cout << name << " spreads wings and soars" << std::endl;
    }
    
    ~Bird() override {
        std::cout << "Bird " << name << " destructor called" << std::endl;
    }
};

// 2. Virtual Functions with Return Type Covariance
class Vehicle {
public:
    virtual Vehicle* clone() const {
        return new Vehicle(*this);
    }
    
    virtual void start() const {
        std::cout << "Vehicle starting..." << std::endl;
    }
    
    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
public:
    // Return type covariance - can return more derived type
    Car* clone() const override {
        return new Car(*this);
    }
    
    void start() const override {
        std::cout << "Car engine starting... Vroom!" << std::endl;
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle* clone() const override {
        return new Motorcycle(*this);
    }
    
    void start() const override {
        std::cout << "Motorcycle engine starting... Roar!" << std::endl;
    }
};

// 3. Virtual Functions in Class Hierarchy
class Shape {
protected:
    std::string color;
    
public:
    Shape(const std::string& c) : color(c) {}
    
    virtual double area() const {
        std::cout << "Generic shape area calculation" << std::endl;
        return 0.0;
    }
    
    virtual double perimeter() const {
        std::cout << "Generic shape perimeter calculation" << std::endl;
        return 0.0;
    }
    
    virtual void draw() const {
        std::cout << "Drawing a " << color << " shape" << std::endl;
    }
    
    virtual std::string getType() const {
        return "Generic Shape";
    }
    
    virtual ~Shape() = default;
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(const std::string& c, double w, double h) 
        : Shape(c), width(w), height(h) {}
    
    double area() const override {
        std::cout << "Calculating rectangle area: ";
        return width * height;
    }
    
    double perimeter() const override {
        std::cout << "Calculating rectangle perimeter: ";
        return 2 * (width + height);
    }
    
    void draw() const override {
        std::cout << "Drawing a " << color << " rectangle (" 
                  << width << "x" << height << ")" << std::endl;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
};

class Circle : public Shape {
private:
    double radius;
    static constexpr double PI = 3.14159265359;
    
public:
    Circle(const std::string& c, double r) : Shape(c), radius(r) {}
    
    double area() const override {
        std::cout << "Calculating circle area: ";
        return PI * radius * radius;
    }
    
    double perimeter() const override {
        std::cout << "Calculating circle circumference: ";
        return 2 * PI * radius;
    }
    
    void draw() const override {
        std::cout << "Drawing a " << color << " circle (radius: " 
                  << radius << ")" << std::endl;
    }
    
    std::string getType() const override {
        return "Circle";
    }
};

class Triangle : public Shape {
private:
    double a, b, c;  // sides
    
public:
    Triangle(const std::string& color, double side_a, double side_b, double side_c) 
        : Shape(color), a(side_a), b(side_b), c(side_c) {}
    
    double area() const override {
        std::cout << "Calculating triangle area (Heron's formula): ";
        double s = (a + b + c) / 2;  // semi-perimeter
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    
    double perimeter() const override {
        std::cout << "Calculating triangle perimeter: ";
        return a + b + c;
    }
    
    void draw() const override {
        std::cout << "Drawing a " << color << " triangle (sides: " 
                  << a << ", " << b << ", " << c << ")" << std::endl;
    }
    
    std::string getType() const override {
        return "Triangle";
    }
};

// 4. Virtual Functions with Default Parameters
class Printer {
public:
    virtual void print(const std::string& text, int copies = 1) const {
        std::cout << "Basic printer: Printing \"" << text 
                  << "\" " << copies << " time(s)" << std::endl;
    }
    
    virtual ~Printer() = default;
};

class LaserPrinter : public Printer {
public:
    void print(const std::string& text, int copies = 1) const override {
        std::cout << "Laser printer: High-quality printing \"" << text 
                  << "\" " << copies << " time(s)" << std::endl;
    }
};

class InkjetPrinter : public Printer {
public:
    void print(const std::string& text, int copies = 1) const override {
        std::cout << "Inkjet printer: Color printing \"" << text 
                  << "\" " << copies << " time(s)" << std::endl;
    }
};

// Utility functions for demonstration
void demonstrateBasicVirtualFunctions() {
    std::cout << "\n=== BASIC VIRTUAL FUNCTIONS ===" << std::endl;
    
    // Polymorphic behavior through base class pointers
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("Buddy"));
    animals.push_back(std::make_unique<Cat>("Whiskers"));
    animals.push_back(std::make_unique<Bird>("Tweety"));
    
    std::cout << "\nDemonstrating polymorphic behavior:" << std::endl;
    for (const auto& animal : animals) {
        animal->makeSound();  // Virtual function call
        animal->move();       // Virtual function call
        animal->breathe();    // Non-virtual function call
        std::cout << "---" << std::endl;
    }
    
    std::cout << "\nDirect object calls (no polymorphism):" << std::endl;
    Dog dog("Rex");
    Cat cat("Felix");
    
    dog.makeSound();
    dog.wagTail();  // Dog-specific method
    
    cat.makeSound();
    cat.purr();     // Cat-specific method
}

void demonstrateReturnTypeCovariance() {
    std::cout << "\n=== RETURN TYPE COVARIANCE ===" << std::endl;
    
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    vehicles.push_back(std::make_unique<Car>());
    vehicles.push_back(std::make_unique<Motorcycle>());
    
    for (const auto& vehicle : vehicles) {
        vehicle->start();
        
        // Clone returns derived type, but we store as base type
        std::unique_ptr<Vehicle> cloned(vehicle->clone());
        cloned->start();
        std::cout << "---" << std::endl;
    }
}

void demonstrateShapeHierarchy() {
    std::cout << "\n=== SHAPE HIERARCHY WITH VIRTUAL FUNCTIONS ===" << std::endl;
    
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>("Red", 5.0, 3.0));
    shapes.push_back(std::make_unique<Circle>("Blue", 4.0));
    shapes.push_back(std::make_unique<Triangle>("Green", 3.0, 4.0, 5.0));
    
    double totalArea = 0.0;
    double totalPerimeter = 0.0;
    
    for (const auto& shape : shapes) {
        std::cout << "\nShape Type: " << shape->getType() << std::endl;
        shape->draw();
        
        double area = shape->area();
        std::cout << area << std::endl;
        
        double perimeter = shape->perimeter();
        std::cout << perimeter << std::endl;
        
        totalArea += area;
        totalPerimeter += perimeter;
        std::cout << "---" << std::endl;
    }
    
    std::cout << "Total Area: " << totalArea << std::endl;
    std::cout << "Total Perimeter: " << totalPerimeter << std::endl;
}

void demonstrateVirtualWithDefaults() {
    std::cout << "\n=== VIRTUAL FUNCTIONS WITH DEFAULT PARAMETERS ===" << std::endl;
    
    std::vector<std::unique_ptr<Printer>> printers;
    printers.push_back(std::make_unique<Printer>());
    printers.push_back(std::make_unique<LaserPrinter>());
    printers.push_back(std::make_unique<InkjetPrinter>());
    
    for (const auto& printer : printers) {
        printer->print("Hello World");      // Using default parameter
        printer->print("Important Doc", 5); // Specifying parameter
        std::cout << "---" << std::endl;
    }
}

void demonstrateStaticVsDynamicBinding() {
    std::cout << "\n=== STATIC VS DYNAMIC BINDING ===" << std::endl;
    
    Dog dog("Static");
    Animal* animalPtr = &dog;
    Animal& animalRef = dog;
    
    std::cout << "Direct call (static binding):" << std::endl;
    dog.makeSound();  // Calls Dog::makeSound (compile-time resolution)
    
    std::cout << "\nPointer call (dynamic binding):" << std::endl;
    animalPtr->makeSound();  // Calls Dog::makeSound (runtime resolution)
    
    std::cout << "\nReference call (dynamic binding):" << std::endl;
    animalRef.makeSound();   // Calls Dog::makeSound (runtime resolution)
    
    std::cout << "\nNon-virtual function call:" << std::endl;
    animalPtr->breathe();    // Calls Animal::breathe (static binding)
}

void demonstrateVTableConcept() {
    std::cout << "\n=== VTABLE CONCEPT DEMONSTRATION ===" << std::endl;
    
    // Show memory layout concept
    std::cout << "Object sizes (including vtable pointer):" << std::endl;
    std::cout << "sizeof(Animal): " << sizeof(Animal) << " bytes" << std::endl;
    std::cout << "sizeof(Dog): " << sizeof(Dog) << " bytes" << std::endl;
    std::cout << "sizeof(Cat): " << sizeof(Cat) << " bytes" << std::endl;
    
    // Show how virtual calls work
    Animal* animals[] = {
        new Dog("VTable Dog"),
        new Cat("VTable Cat"),
        new Bird("VTable Bird")
    };
    
    std::cout << "\nVirtual function calls through base pointer:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "animals[" << i << "]->makeSound(): ";
        animals[i]->makeSound();  // Dynamic dispatch through vtable
    }
    
    // Cleanup
    for (int i = 0; i < 3; ++i) {
        delete animals[i];
    }
}

int main() {
    std::cout << "=== RUNTIME POLYMORPHISM: VIRTUAL FUNCTIONS ===" << std::endl;
    std::cout << "Virtual functions enable polymorphic behavior through" << std::endl;
    std::cout << "dynamic binding and virtual table mechanism." << std::endl;
    
    demonstrateBasicVirtualFunctions();
    demonstrateReturnTypeCovariance();
    demonstrateShapeHierarchy();
    demonstrateVirtualWithDefaults();
    demonstrateStaticVsDynamicBinding();
    demonstrateVTableConcept();
    
    std::cout << "\n=== KEY CONCEPTS ===" << std::endl;
    std::cout << "1. Virtual functions enable polymorphic behavior" << std::endl;
    std::cout << "2. Function resolution happens at runtime (dynamic binding)" << std::endl;
    std::cout << "3. Base class pointers/references can call derived implementations" << std::endl;
    std::cout << "4. Virtual destructor is essential for proper cleanup" << std::endl;
    std::cout << "5. Override keyword provides safety and clarity (C++11)" << std::endl;
    std::cout << "6. Return type covariance allows derived return types" << std::endl;
    std::cout << "7. VTable mechanism provides function dispatch" << std::endl;
    
    return 0;
}

/* Expected Output:
=== RUNTIME POLYMORPHISM: VIRTUAL FUNCTIONS ===
Virtual functions enable polymorphic behavior through
dynamic binding and virtual table mechanism.

=== BASIC VIRTUAL FUNCTIONS ===

Demonstrating polymorphic behavior:
Buddy barks: Woof! Woof!
Buddy runs on four legs
Buddy breathes
---
Whiskers meows: Meow! Meow!
Whiskers walks gracefully
Whiskers breathes
---
Tweety chirps: Tweet! Tweet!
Tweety flies in the sky
Tweety breathes
---

Direct object calls (no polymorphism):
Rex barks: Woof! Woof!
Rex wags tail happily
Felix meows: Meow! Meow!
Felix purrs contentedly

=== RETURN TYPE COVARIANCE ===
Car engine starting... Vroom!
Car engine starting... Vroom!
---
Motorcycle engine starting... Roar!
Motorcycle engine starting... Roar!
---

=== SHAPE HIERARCHY WITH VIRTUAL FUNCTIONS ===

Shape Type: Rectangle
Drawing a Red rectangle (5x3)
Calculating rectangle area: 15
Calculating rectangle perimeter: 16
---

Shape Type: Circle
Drawing a Blue circle (radius: 4)
Calculating circle area: 50.2655
Calculating circle circumference: 25.1327
---

Shape Type: Triangle
Drawing a Green triangle (sides: 3, 4, 5)
Calculating triangle area (Heron's formula): 6
Calculating triangle perimeter: 12
---
Total Area: 71.2655
Total Perimeter: 53.1327

=== VIRTUAL FUNCTIONS WITH DEFAULT PARAMETERS ===
Basic printer: Printing "Hello World" 1 time(s)
Basic printer: Printing "Important Doc" 5 time(s)
---
Laser printer: High-quality printing "Hello World" 1 time(s)
Laser printer: High-quality printing "Important Doc" 5 time(s)
---
Inkjet printer: Color printing "Hello World" 1 time(s)
Inkjet printer: Color printing "Important Doc" 5 time(s)
---

=== STATIC VS DYNAMIC BINDING ===
Direct call (static binding):
Static barks: Woof! Woof!

Pointer call (dynamic binding):
Static barks: Woof! Woof!

Reference call (dynamic binding):
Static barks: Woof! Woof!

Non-virtual function call:
Static breathes

=== VTABLE CONCEPT DEMONSTRATION ===
Object sizes (including vtable pointer):
sizeof(Animal): 40 bytes
sizeof(Dog): 40 bytes
sizeof(Cat): 40 bytes

Virtual function calls through base pointer:
animals[0]->makeSound(): VTable Dog barks: Woof! Woof!
animals[1]->makeSound(): VTable Cat meows: Meow! Meow!
animals[2]->makeSound(): VTable Bird chirps: Tweet! Tweet!
Dog VTable Dog destructor called
Animal VTable Dog destructor called
Cat VTable Cat destructor called
Animal VTable Cat destructor called
Bird VTable Bird destructor called
Animal VTable Bird destructor called

=== KEY CONCEPTS ===
1. Virtual functions enable polymorphic behavior
2. Function resolution happens at runtime (dynamic binding)
3. Base class pointers/references can call derived implementations
4. Virtual destructor is essential for proper cleanup
5. Override keyword provides safety and clarity (C++11)
6. Return type covariance allows derived return types
7. VTable mechanism provides function dispatch
*/
