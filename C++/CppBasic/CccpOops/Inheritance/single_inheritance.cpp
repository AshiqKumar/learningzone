/**
 * @file single_inheritance.cpp
 * @brief Demonstration of Single Inheritance in C++
 * 
 * Single inheritance is the simplest form where one derived class
 * inherits from exactly one base class.
 * 
 * Compile: g++ -std=c++17 -Wall -Wextra single_inheritance.cpp -o single_inheritance
 * Run: ./single_inheritance
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>

// ===== BASIC SINGLE INHERITANCE =====

/**
 * Base class representing a generic Animal
 */
class Animal {
protected:
    std::string name;
    int age;
    double weight;

public:
    // Constructor
    Animal(const std::string& n, int a, double w) 
        : name(n), age(a), weight(w) {
        std::cout << "Animal constructor: " << name << std::endl;
    }
    
    // Virtual destructor (important for proper cleanup)
    virtual ~Animal() {
        std::cout << "Animal destructor: " << name << std::endl;
    }
    
    // Virtual functions for polymorphism
    virtual void makeSound() const {
        std::cout << name << " makes a generic animal sound" << std::endl;
    }
    
    virtual void move() const {
        std::cout << name << " moves around" << std::endl;
    }
    
    // Non-virtual functions
    void eat() const {
        std::cout << name << " is eating" << std::endl;
    }
    
    void sleep() const {
        std::cout << name << " is sleeping" << std::endl;
    }
    
    // Getters
    std::string getName() const { return name; }
    int getAge() const { return age; }
    double getWeight() const { return weight; }
    
    // Display information
    virtual void displayInfo() const {
        std::cout << "Animal: " << name 
                  << ", Age: " << age 
                  << ", Weight: " << weight << "kg" << std::endl;
    }
};

/**
 * Derived class Dog inheriting from Animal
 */
class Dog : public Animal {
private:
    std::string breed;
    bool isTrained;

public:
    // Constructor - calls base class constructor
    Dog(const std::string& n, int a, double w, const std::string& b, bool trained = false)
        : Animal(n, a, w), breed(b), isTrained(trained) {
        std::cout << "Dog constructor: " << name << " (" << breed << ")" << std::endl;
    }
    
    // Destructor
    ~Dog() override {
        std::cout << "Dog destructor: " << name << std::endl;
    }
    
    // Override virtual functions
    void makeSound() const override {
        std::cout << name << " barks: Woof! Woof!" << std::endl;
    }
    
    void move() const override {
        std::cout << name << " runs on four legs" << std::endl;
    }
    
    void displayInfo() const override {
        Animal::displayInfo();  // Call base class method
        std::cout << "Breed: " << breed 
                  << ", Trained: " << (isTrained ? "Yes" : "No") << std::endl;
    }
    
    // Dog-specific methods
    void wagTail() const {
        std::cout << name << " wags tail happily" << std::endl;
    }
    
    void fetch() const {
        if (isTrained) {
            std::cout << name << " fetches the ball" << std::endl;
        } else {
            std::cout << name << " doesn't know how to fetch yet" << std::endl;
        }
    }
    
    void train() {
        isTrained = true;
        std::cout << name << " has been trained!" << std::endl;
    }
    
    // Getters for Dog-specific attributes
    std::string getBreed() const { return breed; }
    bool getIsTrained() const { return isTrained; }
};

/**
 * Another derived class Cat inheriting from Animal
 */
class Cat : public Animal {
private:
    bool isIndoor;
    int livesLeft;

public:
    Cat(const std::string& n, int a, double w, bool indoor = true)
        : Animal(n, a, w), isIndoor(indoor), livesLeft(9) {
        std::cout << "Cat constructor: " << name << std::endl;
    }
    
    ~Cat() override {
        std::cout << "Cat destructor: " << name << std::endl;
    }
    
    void makeSound() const override {
        std::cout << name << " meows: Meow! Meow!" << std::endl;
    }
    
    void move() const override {
        std::cout << name << " moves gracefully and silently" << std::endl;
    }
    
    void displayInfo() const override {
        Animal::displayInfo();
        std::cout << "Indoor: " << (isIndoor ? "Yes" : "No") 
                  << ", Lives left: " << livesLeft << std::endl;
    }
    
    // Cat-specific methods
    void purr() const {
        std::cout << name << " purrs contentedly" << std::endl;
    }
    
    void climb() const {
        std::cout << name << " climbs up high" << std::endl;
    }
    
    void useLitterBox() const {
        if (isIndoor) {
            std::cout << name << " uses the litter box" << std::endl;
        } else {
            std::cout << name << " goes outside" << std::endl;
        }
    }
    
    void loseLife() {
        if (livesLeft > 0) {
            livesLeft--;
            std::cout << name << " lost a life! Lives left: " << livesLeft << std::endl;
        }
    }
    
    bool getIsIndoor() const { return isIndoor; }
    int getLivesLeft() const { return livesLeft; }
};

// ===== ADVANCED SINGLE INHERITANCE =====

/**
 * Base class for vehicles
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
        std::cout << "Vehicle created: " << brand << " " << model << std::endl;
    }
    
    virtual ~Vehicle() {
        std::cout << "Vehicle destroyed: " << brand << " " << model << std::endl;
    }
    
    virtual void start() const {
        std::cout << brand << " " << model << " is starting..." << std::endl;
    }
    
    virtual void stop() const {
        std::cout << brand << " " << model << " has stopped" << std::endl;
    }
    
    virtual double calculateInsurance() const {
        return price * 0.05;  // 5% of price
    }
    
    virtual void displaySpecs() const {
        std::cout << year << " " << brand << " " << model 
                  << " - $" << price << std::endl;
    }
    
    // Getters
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
};

/**
 * Derived class Car
 */
class Car : public Vehicle {
private:
    int doors;
    std::string fuelType;
    double fuelEfficiency;  // miles per gallon

public:
    Car(const std::string& b, const std::string& m, int y, double p,
        int d, const std::string& fuel, double efficiency)
        : Vehicle(b, m, y, p), doors(d), fuelType(fuel), fuelEfficiency(efficiency) {
        std::cout << "Car specifics added: " << doors << " doors, " 
                  << fuelType << " engine" << std::endl;
    }
    
    ~Car() override {
        std::cout << "Car destroyed: " << brand << " " << model << std::endl;
    }
    
    void start() const override {
        std::cout << "Turning key in " << brand << " " << model << "..." << std::endl;
        std::cout << fuelType << " engine started!" << std::endl;
    }
    
    void stop() const override {
        std::cout << brand << " " << model << " engine turned off" << std::endl;
    }
    
    double calculateInsurance() const override {
        double baseInsurance = Vehicle::calculateInsurance();
        // Sports cars cost more to insure
        if (doors == 2) {
            baseInsurance *= 1.5;
        }
        return baseInsurance;
    }
    
    void displaySpecs() const override {
        Vehicle::displaySpecs();
        std::cout << "  Doors: " << doors << std::endl;
        std::cout << "  Fuel Type: " << fuelType << std::endl;
        std::cout << "  Efficiency: " << fuelEfficiency << " MPG" << std::endl;
        std::cout << "  Insurance: $" << calculateInsurance() << "/year" << std::endl;
    }
    
    // Car-specific methods
    void honk() const {
        std::cout << brand << " " << model << " honks: BEEP BEEP!" << std::endl;
    }
    
    void openTrunk() const {
        std::cout << "Opening trunk of " << brand << " " << model << std::endl;
    }
    
    double calculateFuelCost(double miles, double pricePerGallon) const {
        return (miles / fuelEfficiency) * pricePerGallon;
    }
    
    int getDoors() const { return doors; }
    std::string getFuelType() const { return fuelType; }
    double getFuelEfficiency() const { return fuelEfficiency; }
};

// ===== DEMONSTRATION FUNCTIONS =====

void demonstrateBasicInheritance() {
    std::cout << "\n=== BASIC SINGLE INHERITANCE DEMO ===" << std::endl;
    
    // Create objects
    std::cout << "\n1. Creating Animals:" << std::endl;
    Dog buddy("Buddy", 3, 25.5, "Golden Retriever");
    Cat whiskers("Whiskers", 2, 4.2, true);
    
    std::cout << "\n2. Basic Animal Behaviors:" << std::endl;
    buddy.eat();
    whiskers.sleep();
    
    std::cout << "\n3. Polymorphic Behavior:" << std::endl;
    buddy.makeSound();
    whiskers.makeSound();
    buddy.move();
    whiskers.move();
    
    std::cout << "\n4. Dog-specific Behaviors:" << std::endl;
    buddy.wagTail();
    buddy.fetch();  // Not trained yet
    buddy.train();
    buddy.fetch();  // Now trained
    
    std::cout << "\n5. Cat-specific Behaviors:" << std::endl;
    whiskers.purr();
    whiskers.climb();
    whiskers.useLitterBox();
    whiskers.loseLife();
    
    std::cout << "\n6. Display Information:" << std::endl;
    buddy.displayInfo();
    whiskers.displayInfo();
}

void demonstratePolymorphism() {
    std::cout << "\n=== POLYMORPHISM DEMO ===" << std::endl;
    
    // Using base class pointers for polymorphism
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("Rex", 5, 30.0, "German Shepherd", true));
    animals.push_back(std::make_unique<Cat>("Mittens", 1, 3.5, false));
    animals.push_back(std::make_unique<Dog>("Spot", 2, 15.0, "Beagle"));
    
    std::cout << "\nPolymorphic calls:" << std::endl;
    for (const auto& animal : animals) {
        animal->displayInfo();
        animal->makeSound();
        animal->move();
        std::cout << "---" << std::endl;
    }
    
    // Note: animals are automatically destroyed when vector goes out of scope
    // Virtual destructors ensure proper cleanup
}

void demonstrateVehicleInheritance() {
    std::cout << "\n=== VEHICLE INHERITANCE DEMO ===" << std::endl;
    
    std::cout << "\n1. Creating Vehicles:" << std::endl;
    Car sedan("Toyota", "Camry", 2023, 25000, 4, "Gasoline", 32.0);
    Car sportscar("Porsche", "911", 2023, 120000, 2, "Gasoline", 20.0);
    
    std::cout << "\n2. Vehicle Operations:" << std::endl;
    sedan.start();
    sedan.honk();
    sedan.stop();
    
    std::cout << std::endl;
    sportscar.start();
    sportscar.openTrunk();
    sportscar.stop();
    
    std::cout << "\n3. Vehicle Specifications:" << std::endl;
    sedan.displaySpecs();
    std::cout << std::endl;
    sportscar.displaySpecs();
    
    std::cout << "\n4. Fuel Cost Calculation:" << std::endl;
    double tripMiles = 300;
    double gasPrice = 3.50;
    
    std::cout << "Trip: " << tripMiles << " miles at $" << gasPrice << "/gallon" << std::endl;
    std::cout << "Sedan fuel cost: $" << sedan.calculateFuelCost(tripMiles, gasPrice) << std::endl;
    std::cout << "Sports car fuel cost: $" << sportscar.calculateFuelCost(tripMiles, gasPrice) << std::endl;
}

void demonstrateConstructorDestructorOrder() {
    std::cout << "\n=== CONSTRUCTOR/DESTRUCTOR ORDER DEMO ===" << std::endl;
    
    std::cout << "\nCreating objects (note constructor order):" << std::endl;
    {
        Dog temp("Temporary", 1, 10.0, "Mutt");
        std::cout << "Object created in scope" << std::endl;
    }  // Destructor called here (note order)
    
    std::cout << "\nScope ended (note destructor order)" << std::endl;
}

void demonstrateAccessSpecifiers() {
    std::cout << "\n=== ACCESS SPECIFIERS DEMO ===" << std::endl;
    
    Dog demo("Demo", 4, 20.0, "Mixed");
    
    // Public members - accessible
    std::cout << "Public access:" << std::endl;
    std::cout << "Name: " << demo.getName() << std::endl;
    std::cout << "Age: " << demo.getAge() << std::endl;
    
    // Protected members - not directly accessible, but inherited
    // demo.name;  // Error: protected member
    
    // Private members - not accessible
    // demo.breed;  // Error: private member
    std::cout << "Breed (via getter): " << demo.getBreed() << std::endl;
    
    std::cout << "\nNote: Protected members are accessible within derived class" << std::endl;
    std::cout << "Private members require getters/setters for access" << std::endl;
}

int main() {
    std::cout << "=== SINGLE INHERITANCE DEMONSTRATION ===" << std::endl;
    
    try {
        demonstrateBasicInheritance();
        demonstratePolymorphism();
        demonstrateVehicleInheritance();
        demonstrateConstructorDestructorOrder();
        demonstrateAccessSpecifiers();
        
        std::cout << "\n=== SINGLE INHERITANCE SUMMARY ===" << std::endl;
        std::cout << "\nKey Concepts Demonstrated:" << std::endl;
        std::cout << "✅ Basic inheritance syntax (class Derived : public Base)" << std::endl;
        std::cout << "✅ Constructor/destructor chaining" << std::endl;
        std::cout << "✅ Virtual functions and polymorphism" << std::endl;
        std::cout << "✅ Function overriding with 'override' keyword" << std::endl;
        std::cout << "✅ Access specifiers (public, protected, private)" << std::endl;
        std::cout << "✅ Virtual destructors for proper cleanup" << std::endl;
        std::cout << "✅ Base class method calling" << std::endl;
        std::cout << "✅ Polymorphic containers with smart pointers" << std::endl;
        
        std::cout << "\nBest Practices Shown:" << std::endl;
        std::cout << "• Use virtual destructors in base classes" << std::endl;
        std::cout << "• Use 'override' keyword for clarity and safety" << std::endl;
        std::cout << "• Prefer smart pointers for polymorphic containers" << std::endl;
        std::cout << "• Keep protected members minimal" << std::endl;
        std::cout << "• Use initialization lists in constructors" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

/*
Single Inheritance Summary:

Syntax:
class Derived : access_specifier Base {
    // Derived class members
};

Key Features:
1. Code Reusability - Inherit existing functionality
2. Polymorphism - Virtual functions enable runtime binding
3. Extensibility - Add new features to existing classes
4. Hierarchy - Create logical class relationships

Access Specifiers:
- public: Most common, maintains "is-a" relationship
- protected: Rarely used, more restrictive access
- private: Creates "implemented-in-terms-of" relationship

Constructor/Destructor Order:
- Construction: Base first, then Derived
- Destruction: Derived first, then Base
- Virtual destructors ensure proper cleanup

Virtual Functions:
- Enable polymorphism
- Resolved at runtime
- Use 'virtual' in base, 'override' in derived
- Pure virtual makes class abstract

Memory Layout:
- Base class members first
- Derived class members after
- Virtual table pointer if virtual functions exist

Performance:
- Minimal overhead for non-virtual functions
- Small cost for virtual function calls
- Memory efficient compared to composition
*/
