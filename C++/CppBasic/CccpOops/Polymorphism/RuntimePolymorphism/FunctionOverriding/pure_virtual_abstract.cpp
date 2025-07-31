// pure_virtual_abstract.cpp - Demonstrates pure virtual functions and abstract classes
// Compile: g++ -std=c++17 -Wall -Wextra pure_virtual_abstract.cpp -o pure_virtual_abstract

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

// 1. Abstract Base Class with Pure Virtual Functions
class Shape {
protected:
    std::string name;
    
public:
    Shape(const std::string& n) : name(n) {}
    
    // Pure virtual functions - must be implemented by derived classes
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
    
    // Virtual function with implementation (can be overridden)
    virtual std::string getInfo() const {
        return "Shape: " + name;
    }
    
    // Non-virtual function
    const std::string& getName() const {
        return name;
    }
    
    // Virtual destructor is essential for abstract base classes
    virtual ~Shape() {
        std::cout << "Shape " << name << " destroyed" << std::endl;
    }
};

// Concrete derived class
class Circle : public Shape {
private:
    double radius;
    static constexpr double PI = 3.14159265359;
    
public:
    Circle(const std::string& name, double r) : Shape(name), radius(r) {}
    
    // Must implement all pure virtual functions
    double area() const override {
        return PI * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * PI * radius;
    }
    
    void draw() const override {
        std::cout << "Drawing circle '" << name << "' with radius " << radius << std::endl;
    }
    
    std::string getInfo() const override {
        return Shape::getInfo() + " (Circle, radius: " + std::to_string(radius) + ")";
    }
    
    ~Circle() override {
        std::cout << "Circle " << name << " destroyed" << std::endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(const std::string& name, double w, double h) 
        : Shape(name), width(w), height(h) {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        std::cout << "Drawing rectangle '" << name << "' " << width 
                  << "x" << height << std::endl;
    }
    
    std::string getInfo() const override {
        return Shape::getInfo() + " (Rectangle, " + std::to_string(width) 
               + "x" + std::to_string(height) + ")";
    }
    
    ~Rectangle() override {
        std::cout << "Rectangle " << name << " destroyed" << std::endl;
    }
};

class Triangle : public Shape {
private:
    double a, b, c;  // three sides
    
public:
    Triangle(const std::string& name, double side_a, double side_b, double side_c)
        : Shape(name), a(side_a), b(side_b), c(side_c) {}
    
    double area() const override {
        double s = (a + b + c) / 2.0;  // semi-perimeter
        return sqrt(s * (s - a) * (s - b) * (s - c));  // Heron's formula
    }
    
    double perimeter() const override {
        return a + b + c;
    }
    
    void draw() const override {
        std::cout << "Drawing triangle '" << name << "' with sides " 
                  << a << ", " << b << ", " << c << std::endl;
    }
    
    std::string getInfo() const override {
        return Shape::getInfo() + " (Triangle, sides: " + std::to_string(a) 
               + ", " + std::to_string(b) + ", " + std::to_string(c) + ")";
    }
    
    ~Triangle() override {
        std::cout << "Triangle " << name << " destroyed" << std::endl;
    }
};

// 2. Interface Class (all pure virtual functions)
class Drawable {
public:
    virtual void render() const = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual std::pair<double, double> getPosition() const = 0;
    virtual ~Drawable() = default;
};

class Colorable {
public:
    virtual void setColor(const std::string& color) = 0;
    virtual std::string getColor() const = 0;
    virtual ~Colorable() = default;
};

// Multiple interface implementation
class GraphicsObject : public Drawable, public Colorable {
private:
    double x, y;
    std::string color;
    std::string name;
    
public:
    GraphicsObject(const std::string& n, double x_pos = 0, double y_pos = 0, 
                   const std::string& c = "black")
        : x(x_pos), y(y_pos), color(c), name(n) {}
    
    // Implement Drawable interface
    void render() const override {
        std::cout << "Rendering " << color << " " << name 
                  << " at position (" << x << ", " << y << ")" << std::endl;
    }
    
    void setPosition(double new_x, double new_y) override {
        x = new_x;
        y = new_y;
    }
    
    std::pair<double, double> getPosition() const override {
        return {x, y};
    }
    
    // Implement Colorable interface
    void setColor(const std::string& new_color) override {
        color = new_color;
    }
    
    std::string getColor() const override {
        return color;
    }
    
    const std::string& getName() const { return name; }
};

// 3. Abstract Factory Pattern with Pure Virtual Functions
class Animal {
public:
    virtual void makeSound() const = 0;
    virtual void move() const = 0;
    virtual std::string getSpecies() const = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
private:
    std::string name;
    
public:
    Dog(const std::string& n) : name(n) {}
    
    void makeSound() const override {
        std::cout << name << " barks: Woof! Woof!" << std::endl;
    }
    
    void move() const override {
        std::cout << name << " runs on four legs" << std::endl;
    }
    
    std::string getSpecies() const override {
        return "Canis lupus";
    }
};

class Cat : public Animal {
private:
    std::string name;
    
public:
    Cat(const std::string& n) : name(n) {}
    
    void makeSound() const override {
        std::cout << name << " meows: Meow! Meow!" << std::endl;
    }
    
    void move() const override {
        std::cout << name << " walks gracefully" << std::endl;
    }
    
    std::string getSpecies() const override {
        return "Felis catus";
    }
};

// Abstract factory
class AnimalFactory {
public:
    virtual std::unique_ptr<Animal> createAnimal(const std::string& name) const = 0;
    virtual std::string getFactoryType() const = 0;
    virtual ~AnimalFactory() = default;
};

class DogFactory : public AnimalFactory {
public:
    std::unique_ptr<Animal> createAnimal(const std::string& name) const override {
        return std::make_unique<Dog>(name);
    }
    
    std::string getFactoryType() const override {
        return "Dog Factory";
    }
};

class CatFactory : public AnimalFactory {
public:
    std::unique_ptr<Animal> createAnimal(const std::string& name) const override {
        return std::make_unique<Cat>(name);
    }
    
    std::string getFactoryType() const override {
        return "Cat Factory";
    }
};

// 4. Strategy Pattern with Pure Virtual Functions
class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) const = 0;
    virtual std::string getName() const = 0;
    virtual ~SortStrategy() = default;
};

class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) const override {
        std::cout << "Performing Bubble Sort..." << std::endl;
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data.size() - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
    
    std::string getName() const override {
        return "Bubble Sort";
    }
};

class QuickSort : public SortStrategy {
private:
    void quickSort(std::vector<int>& data, int low, int high) const {
        if (low < high) {
            int pivot = partition(data, low, high);
            quickSort(data, low, pivot - 1);
            quickSort(data, pivot + 1, high);
        }
    }
    
    int partition(std::vector<int>& data, int low, int high) const {
        int pivot = data[high];
        int i = low - 1;
        
        for (int j = low; j < high; ++j) {
            if (data[j] < pivot) {
                ++i;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }
    
public:
    void sort(std::vector<int>& data) const override {
        std::cout << "Performing Quick Sort..." << std::endl;
        if (!data.empty()) {
            quickSort(data, 0, static_cast<int>(data.size()) - 1);
        }
    }
    
    std::string getName() const override {
        return "Quick Sort";
    }
};

class Sorter {
private:
    std::unique_ptr<SortStrategy> strategy;
    
public:
    void setStrategy(std::unique_ptr<SortStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }
    
    void performSort(std::vector<int>& data) const {
        if (strategy) {
            std::cout << "Using " << strategy->getName() << std::endl;
            strategy->sort(data);
        } else {
            std::cout << "No sorting strategy set!" << std::endl;
        }
    }
};

// Demonstration functions
void demonstrateAbstractShapes() {
    std::cout << "\n=== ABSTRACT SHAPES WITH PURE VIRTUAL FUNCTIONS ===" << std::endl;
    
    // Cannot instantiate abstract class
    // Shape shape("invalid");  // Compilation error!
    
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>("Circle1", 5.0));
    shapes.push_back(std::make_unique<Rectangle>("Rect1", 4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>("Triangle1", 3.0, 4.0, 5.0));
    
    double totalArea = 0.0;
    double totalPerimeter = 0.0;
    
    for (const auto& shape : shapes) {
        std::cout << "\n" << shape->getInfo() << std::endl;
        shape->draw();
        
        double area = shape->area();
        double perimeter = shape->perimeter();
        
        std::cout << "Area: " << area << std::endl;
        std::cout << "Perimeter: " << perimeter << std::endl;
        
        totalArea += area;
        totalPerimeter += perimeter;
    }
    
    std::cout << "\nTotals:" << std::endl;
    std::cout << "Total Area: " << totalArea << std::endl;
    std::cout << "Total Perimeter: " << totalPerimeter << std::endl;
}

void demonstrateMultipleInterfaces() {
    std::cout << "\n=== MULTIPLE INTERFACE IMPLEMENTATION ===" << std::endl;
    
    std::vector<GraphicsObject> objects;
    objects.emplace_back("Square", 10, 20, "red");
    objects.emplace_back("Circle", 30, 40, "blue");
    objects.emplace_back("Star", 50, 60, "yellow");
    
    for (auto& obj : objects) {
        obj.render();
        
        auto [x, y] = obj.getPosition();
        std::cout << "Current position: (" << x << ", " << y << ")" << std::endl;
        
        obj.setPosition(x + 10, y + 10);
        obj.setColor("green");
        
        std::cout << "After changes: ";
        obj.render();
        std::cout << "---" << std::endl;
    }
}

void demonstrateAbstractFactory() {
    std::cout << "\n=== ABSTRACT FACTORY PATTERN ===" << std::endl;
    
    std::vector<std::unique_ptr<AnimalFactory>> factories;
    factories.push_back(std::make_unique<DogFactory>());
    factories.push_back(std::make_unique<CatFactory>());
    
    std::vector<std::string> names{"Buddy", "Whiskers", "Rex", "Felix"};
    std::vector<std::unique_ptr<Animal>> animals;
    
    for (size_t i = 0; i < names.size(); ++i) {
        const auto& factory = factories[i % factories.size()];
        std::cout << "Using " << factory->getFactoryType() << std::endl;
        
        auto animal = factory->createAnimal(names[i]);
        std::cout << "Created animal of species: " << animal->getSpecies() << std::endl;
        animal->makeSound();
        animal->move();
        
        animals.push_back(std::move(animal));
        std::cout << "---" << std::endl;
    }
    
    std::cout << "All animals performing actions:" << std::endl;
    for (const auto& animal : animals) {
        animal->makeSound();
    }
}

void demonstrateStrategyPattern() {
    std::cout << "\n=== STRATEGY PATTERN WITH PURE VIRTUAL FUNCTIONS ===" << std::endl;
    
    std::vector<int> data1{64, 34, 25, 12, 22, 11, 90};
    std::vector<int> data2 = data1;  // Copy for second test
    
    Sorter sorter;
    
    std::cout << "Original data: ";
    for (int val : data1) std::cout << val << " ";
    std::cout << std::endl;
    
    // Test Bubble Sort
    sorter.setStrategy(std::make_unique<BubbleSort>());
    sorter.performSort(data1);
    
    std::cout << "After Bubble Sort: ";
    for (int val : data1) std::cout << val << " ";
    std::cout << std::endl;
    
    // Test Quick Sort
    std::cout << "\nOriginal data: ";
    for (int val : data2) std::cout << val << " ";
    std::cout << std::endl;
    
    sorter.setStrategy(std::make_unique<QuickSort>());
    sorter.performSort(data2);
    
    std::cout << "After Quick Sort: ";
    for (int val : data2) std::cout << val << " ";
    std::cout << std::endl;
}

void demonstrateAbstractClassProperties() {
    std::cout << "\n=== ABSTRACT CLASS PROPERTIES ===" << std::endl;
    
    std::cout << "1. Cannot instantiate abstract classes directly" << std::endl;
    std::cout << "2. Can have both pure virtual and regular virtual functions" << std::endl;
    std::cout << "3. Can have non-virtual functions and data members" << std::endl;
    std::cout << "4. Derived classes must implement all pure virtual functions" << std::endl;
    std::cout << "5. Virtual destructor is essential for proper cleanup" << std::endl;
    
    // Demonstrate polymorphic destruction
    std::cout << "\nDemonstrating polymorphic destruction:" << std::endl;
    {
        std::unique_ptr<Shape> shape = std::make_unique<Circle>("TempCircle", 2.0);
        // Destructor will be called automatically due to RAII
        // Virtual destructor ensures proper cleanup
    }
    std::cout << "Automatic destruction completed" << std::endl;
}

int main() {
    std::cout << "=== RUNTIME POLYMORPHISM: PURE VIRTUAL FUNCTIONS & ABSTRACT CLASSES ===" << std::endl;
    std::cout << "Pure virtual functions define interface contracts that derived" << std::endl;
    std::cout << "classes must implement, enabling true abstraction and polymorphism." << std::endl;
    
    demonstrateAbstractShapes();
    demonstrateMultipleInterfaces();
    demonstrateAbstractFactory();
    demonstrateStrategyPattern();
    demonstrateAbstractClassProperties();
    
    std::cout << "\n=== KEY CONCEPTS ===" << std::endl;
    std::cout << "1. Pure virtual functions (= 0) create abstract classes" << std::endl;
    std::cout << "2. Abstract classes cannot be instantiated directly" << std::endl;
    std::cout << "3. Derived classes must implement all pure virtual functions" << std::endl;
    std::cout << "4. Abstract classes can have both pure virtual and regular functions" << std::endl;
    std::cout << "5. Interface classes contain only pure virtual functions" << std::endl;
    std::cout << "6. Multiple inheritance enables multiple interface implementation" << std::endl;
    std::cout << "7. Virtual destructors ensure proper polymorphic cleanup" << std::endl;
    
    return 0;
}

/* Expected Output:
=== RUNTIME POLYMORPHISM: PURE VIRTUAL FUNCTIONS & ABSTRACT CLASSES ===
Pure virtual functions define interface contracts that derived
classes must implement, enabling true abstraction and polymorphism.

=== ABSTRACT SHAPES WITH PURE VIRTUAL FUNCTIONS ===

Shape: Circle1 (Circle, radius: 5.000000)
Drawing circle 'Circle1' with radius 5
Area: 78.5398
Perimeter: 31.4159

Shape: Rect1 (Rectangle, 4.000000x6.000000)
Drawing rectangle 'Rect1' 4x6
Area: 24
Perimeter: 20

Shape: Triangle1 (Triangle, sides: 3.000000, 4.000000, 5.000000)
Drawing triangle 'Triangle1' with sides 3, 4, 5
Area: 6
Perimeter: 12

Totals:
Total Area: 108.54
Total Perimeter: 63.4159

=== MULTIPLE INTERFACE IMPLEMENTATION ===
Rendering red Square at position (10, 20)
Current position: (10, 20)
After changes: Rendering green Square at position (20, 30)
---
Rendering blue Circle at position (30, 40)
Current position: (30, 40)
After changes: Rendering green Circle at position (40, 50)
---
Rendering yellow Star at position (50, 60)
Current position: (50, 60)
After changes: Rendering green Star at position (60, 70)
---

=== ABSTRACT FACTORY PATTERN ===
Using Dog Factory
Created animal of species: Canis lupus
Buddy barks: Woof! Woof!
Buddy runs on four legs
---
Using Cat Factory
Created animal of species: Felis catus
Whiskers meows: Meow! Meow!
Whiskers walks gracefully
---
Using Dog Factory
Created animal of species: Canis lupus
Rex barks: Woof! Woof!
Rex runs on four legs
---
Using Cat Factory
Created animal of species: Felis catus
Felix meows: Meow! Meow!
Felix walks gracefully
---
All animals performing actions:
Buddy barks: Woof! Woof!
Whiskers meows: Meow! Meow!
Rex barks: Woof! Woof!
Felix meows: Meow! Meow!

=== STRATEGY PATTERN WITH PURE VIRTUAL FUNCTIONS ===
Original data: 64 34 25 12 22 11 90 
Using Bubble Sort
Performing Bubble Sort...
After Bubble Sort: 11 12 22 25 34 64 90 

Original data: 64 34 25 12 22 11 90 
Using Quick Sort
Performing Quick Sort...
After Quick Sort: 11 12 22 25 34 64 90 

=== ABSTRACT CLASS PROPERTIES ===
1. Cannot instantiate abstract classes directly
2. Can have both pure virtual and regular virtual functions
3. Can have non-virtual functions and data members
4. Derived classes must implement all pure virtual functions
5. Virtual destructor is essential for proper cleanup

Demonstrating polymorphic destruction:
Circle TempCircle destroyed
Shape TempCircle destroyed
Automatic destruction completed
Triangle Triangle1 destroyed
Shape Triangle1 destroyed
Rectangle Rect1 destroyed
Shape Rect1 destroyed
Circle Circle1 destroyed
Shape Circle1 destroyed

=== KEY CONCEPTS ===
1. Pure virtual functions (= 0) create abstract classes
2. Abstract classes cannot be instantiated directly
3. Derived classes must implement all pure virtual functions
4. Abstract classes can have both pure virtual and regular functions
5. Interface classes contain only pure virtual functions
6. Multiple inheritance enables multiple interface implementation
7. Virtual destructors ensure proper polymorphic cleanup
*/
