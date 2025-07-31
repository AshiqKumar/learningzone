/**
 * @file multiple_inheritance.cpp
 * @brief Demonstration of Multiple Inheritance in C++
 * 
 * Multiple inheritance allows a class to inherit from more than one base class.
 * This powerful feature can lead to complex hierarchies and the famous "diamond problem".
 * 
 * Compile: g++ -std=c++17 -Wall -Wextra multiple_inheritance.cpp -o multiple_inheritance
 * Run: ./multiple_inheritance
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <typeinfo>

// ===== BASIC MULTIPLE INHERITANCE =====

/**
 * First base class - Flyable interface
 */
class Flyable {
protected:
    double maxAltitude;
    double currentAltitude;

public:
    Flyable(double maxAlt = 10000) : maxAltitude(maxAlt), currentAltitude(0) {
        std::cout << "Flyable constructor - max altitude: " << maxAltitude << "ft" << std::endl;
    }
    
    virtual ~Flyable() {
        std::cout << "Flyable destructor" << std::endl;
    }
    
    virtual void takeOff() {
        std::cout << "Taking off..." << std::endl;
        currentAltitude = 100;
    }
    
    virtual void fly() {
        if (currentAltitude > 0) {
            std::cout << "Flying at " << currentAltitude << " feet" << std::endl;
        } else {
            std::cout << "Cannot fly - not airborne" << std::endl;
        }
    }
    
    virtual void land() {
        std::cout << "Landing..." << std::endl;
        currentAltitude = 0;
    }
    
    void setAltitude(double alt) {
        if (alt <= maxAltitude) {
            currentAltitude = alt;
            std::cout << "Altitude set to " << currentAltitude << " feet" << std::endl;
        } else {
            std::cout << "Cannot exceed max altitude of " << maxAltitude << " feet" << std::endl;
        }
    }
    
    double getCurrentAltitude() const { return currentAltitude; }
    double getMaxAltitude() const { return maxAltitude; }
};

/**
 * Second base class - Swimmable interface
 */
class Swimmable {
protected:
    double maxDepth;
    double currentDepth;
    bool isUnderwater;

public:
    Swimmable(double maxD = 100) : maxDepth(maxD), currentDepth(0), isUnderwater(false) {
        std::cout << "Swimmable constructor - max depth: " << maxDepth << "ft" << std::endl;
    }
    
    virtual ~Swimmable() {
        std::cout << "Swimmable destructor" << std::endl;
    }
    
    virtual void dive() {
        std::cout << "Diving underwater..." << std::endl;
        isUnderwater = true;
        currentDepth = 5;
    }
    
    virtual void swim() {
        if (isUnderwater) {
            std::cout << "Swimming at depth " << currentDepth << " feet" << std::endl;
        } else {
            std::cout << "Swimming on the surface" << std::endl;
        }
    }
    
    virtual void surface() {
        std::cout << "Surfacing..." << std::endl;
        isUnderwater = false;
        currentDepth = 0;
    }
    
    void setDepth(double depth) {
        if (depth <= maxDepth) {
            currentDepth = depth;
            isUnderwater = depth > 0;
            std::cout << "Depth set to " << currentDepth << " feet" << std::endl;
        } else {
            std::cout << "Cannot exceed max depth of " << maxDepth << " feet" << std::endl;
        }
    }
    
    double getCurrentDepth() const { return currentDepth; }
    double getMaxDepth() const { return maxDepth; }
    bool getIsUnderwater() const { return isUnderwater; }
};

/**
 * Third base class - basic Animal
 */
class Animal {
protected:
    std::string name;
    std::string species;
    int age;

public:
    Animal(const std::string& n, const std::string& s, int a)
        : name(n), species(s), age(a) {
        std::cout << "Animal constructor: " << name << " (" << species << ")" << std::endl;
    }
    
    virtual ~Animal() {
        std::cout << "Animal destructor: " << name << std::endl;
    }
    
    virtual void makeSound() const = 0;  // Pure virtual
    
    virtual void eat() const {
        std::cout << name << " is eating" << std::endl;
    }
    
    virtual void sleep() const {
        std::cout << name << " is sleeping" << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << "Animal: " << name << " (" << species << "), Age: " << age << std::endl;
    }
    
    std::string getName() const { return name; }
    std::string getSpecies() const { return species; }
    int getAge() const { return age; }
};

/**
 * Multiple inheritance example: Duck inherits from all three classes
 */
class Duck : public Animal, public Flyable, public Swimmable {
private:
    std::string color;
    bool isMigrating;

public:
    Duck(const std::string& n, const std::string& c, int a)
        : Animal(n, "Duck", a), Flyable(5000), Swimmable(20), 
          color(c), isMigrating(false) {
        std::cout << "Duck constructor: " << name << " (" << color << ")" << std::endl;
    }
    
    ~Duck() override {
        std::cout << "Duck destructor: " << name << std::endl;
    }
    
    // Implement pure virtual function from Animal
    void makeSound() const override {
        std::cout << name << " quacks: Quack! Quack!" << std::endl;
    }
    
    // Override Flyable methods
    void takeOff() override {
        std::cout << name << " flaps wings and takes off from water" << std::endl;
        Flyable::takeOff();
    }
    
    void fly() override {
        if (isMigrating) {
            std::cout << name << " is migrating - flying in formation" << std::endl;
        } else {
            Flyable::fly();
        }
    }
    
    void land() override {
        std::cout << name << " lands gracefully on water" << std::endl;
        Flyable::land();
    }
    
    // Override Swimmable methods
    void dive() override {
        std::cout << name << " dives for food" << std::endl;
        Swimmable::dive();
    }
    
    void swim() override {
        std::cout << name << " paddles with webbed feet" << std::endl;
        Swimmable::swim();
    }
    
    // Override Animal methods
    void displayInfo() const override {
        Animal::displayInfo();
        std::cout << "Color: " << color 
                  << ", Flying: " << (getCurrentAltitude() > 0 ? "Yes" : "No")
                  << ", Swimming: " << (getIsUnderwater() ? "Underwater" : "Surface")
                  << ", Migrating: " << (isMigrating ? "Yes" : "No") << std::endl;
    }
    
    // Duck-specific methods
    void startMigration() {
        isMigrating = true;
        std::cout << name << " starts migration journey" << std::endl;
    }
    
    void stopMigration() {
        isMigrating = false;
        std::cout << name << " ends migration journey" << std::endl;
    }
    
    void forage() {
        if (getIsUnderwater()) {
            std::cout << name << " forages underwater for aquatic plants" << std::endl;
        } else {
            std::cout << name << " forages on surface for insects" << std::endl;
        }
    }
    
    std::string getColor() const { return color; }
    bool getIsMigrating() const { return isMigrating; }
};

// ===== DIAMOND PROBLEM DEMONSTRATION =====

/**
 * Base class for diamond problem
 */
class Vehicle {
protected:
    std::string brand;
    int year;

public:
    Vehicle(const std::string& b, int y) : brand(b), year(y) {
        std::cout << "Vehicle constructor: " << brand << std::endl;
    }
    
    virtual ~Vehicle() {
        std::cout << "Vehicle destructor: " << brand << std::endl;
    }
    
    virtual void start() const {
        std::cout << brand << " vehicle starting..." << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << year << " " << brand << std::endl;
    }
    
    std::string getBrand() const { return brand; }
    int getYear() const { return year; }
};

/**
 * First derived class
 */
class LandVehicle : public Vehicle {
protected:
    int wheels;

public:
    LandVehicle(const std::string& b, int y, int w) 
        : Vehicle(b, y), wheels(w) {
        std::cout << "LandVehicle constructor: " << wheels << " wheels" << std::endl;
    }
    
    virtual ~LandVehicle() {
        std::cout << "LandVehicle destructor" << std::endl;
    }
    
    virtual void drive() const {
        std::cout << brand << " drives on " << wheels << " wheels" << std::endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "Wheels: " << wheels << std::endl;
    }
    
    int getWheels() const { return wheels; }
};

/**
 * Second derived class
 */
class WaterVehicle : public Vehicle {
protected:
    std::string propulsion;

public:
    WaterVehicle(const std::string& b, int y, const std::string& prop)
        : Vehicle(b, y), propulsion(prop) {
        std::cout << "WaterVehicle constructor: " << propulsion << " propulsion" << std::endl;
    }
    
    virtual ~WaterVehicle() {
        std::cout << "WaterVehicle destructor" << std::endl;
    }
    
    virtual void sail() const {
        std::cout << brand << " sails using " << propulsion << std::endl;
    }
    
    void displayInfo() const override {
        Vehicle::displayInfo();
        std::cout << "Propulsion: " << propulsion << std::endl;
    }
    
    std::string getPropulsion() const { return propulsion; }
};

/**
 * Diamond problem: AmphibiousVehicle inherits from both LandVehicle and WaterVehicle
 * This creates two copies of Vehicle base class (without virtual inheritance)
 */
class AmphibiousVehicle : public LandVehicle, public WaterVehicle {
private:
    std::string mode;  // "land" or "water"

public:
    AmphibiousVehicle(const std::string& b, int y, int w, const std::string& prop)
        : LandVehicle(b, y, w), WaterVehicle(b, y, prop), mode("land") {
        std::cout << "AmphibiousVehicle constructor" << std::endl;
    }
    
    ~AmphibiousVehicle() override {
        std::cout << "AmphibiousVehicle destructor" << std::endl;
    }
    
    void switchToLand() {
        mode = "land";
        std::cout << "Switched to land mode" << std::endl;
    }
    
    void switchToWater() {
        mode = "water";
        std::cout << "Switched to water mode" << std::endl;
    }
    
    void move() const {
        if (mode == "land") {
            drive();
        } else {
            sail();
        }
    }
    
    // Ambiguity resolution - must specify which base class method to use
    void displayInfo() const {
        std::cout << "Amphibious Vehicle Information:" << std::endl;
        std::cout << "Land mode: ";
        LandVehicle::displayInfo();
        std::cout << "Water mode: ";
        WaterVehicle::displayInfo();
        std::cout << "Current mode: " << mode << std::endl;
    }
    
    // Demonstrate ambiguity
    void demonstrateAmbiguity() const {
        std::cout << "\nDemonstrating diamond problem ambiguity:" << std::endl;
        
        // These would be ambiguous without qualification:
        // getBrand();  // Error: ambiguous
        // getYear();   // Error: ambiguous
        
        // Must specify which base class:
        std::cout << "Land vehicle brand: " << LandVehicle::getBrand() << std::endl;
        std::cout << "Water vehicle brand: " << WaterVehicle::getBrand() << std::endl;
        std::cout << "Land vehicle year: " << LandVehicle::getYear() << std::endl;
        std::cout << "Water vehicle year: " << WaterVehicle::getYear() << std::endl;
        
        // Note: These are actually the same values but from different Vehicle instances!
    }
    
    std::string getMode() const { return mode; }
};

// ===== MIXIN PATTERN DEMONSTRATION =====

/**
 * Mixin for logging functionality
 */
class Loggable {
private:
    static int logLevel;
    std::string loggerName;

public:
    Loggable(const std::string& name) : loggerName(name) {}
    
    virtual ~Loggable() = default;
    
    void logInfo(const std::string& message) const {
        if (logLevel >= 1) {
            std::cout << "[INFO] " << loggerName << ": " << message << std::endl;
        }
    }
    
    void logWarning(const std::string& message) const {
        if (logLevel >= 2) {
            std::cout << "[WARN] " << loggerName << ": " << message << std::endl;
        }
    }
    
    void logError(const std::string& message) const {
        if (logLevel >= 3) {
            std::cout << "[ERROR] " << loggerName << ": " << message << std::endl;
        }
    }
    
    static void setLogLevel(int level) { logLevel = level; }
    static int getLogLevel() { return logLevel; }
};

int Loggable::logLevel = 1;  // Default to INFO level

/**
 * Mixin for serialization
 */
class Serializable {
public:
    virtual ~Serializable() = default;
    
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& data) = 0;
    
    void saveToFile(const std::string& filename) const {
        std::cout << "Saving to file: " << filename << std::endl;
        std::cout << "Data: " << serialize() << std::endl;
    }
    
    void loadFromFile(const std::string& filename) {
        std::cout << "Loading from file: " << filename << std::endl;
        // Simulate loading data
        std::string simulatedData = "name=TestData,value=42";
        deserialize(simulatedData);
    }
};

/**
 * Example class using multiple inheritance with mixins
 */
class SmartDevice : public Loggable, public Serializable {
private:
    std::string deviceName;
    int batteryLevel;
    bool isConnected;

public:
    SmartDevice(const std::string& name, int battery = 100)
        : Loggable("SmartDevice"), deviceName(name), batteryLevel(battery), isConnected(false) {
        logInfo("Device created: " + deviceName);
    }
    
    ~SmartDevice() override {
        logInfo("Device destroyed: " + deviceName);
    }
    
    void connect() {
        if (!isConnected) {
            isConnected = true;
            logInfo("Connected to network");
        } else {
            logWarning("Already connected");
        }
    }
    
    void disconnect() {
        if (isConnected) {
            isConnected = false;
            logInfo("Disconnected from network");
        } else {
            logWarning("Already disconnected");
        }
    }
    
    void useBattery(int amount) {
        batteryLevel -= amount;
        if (batteryLevel < 0) batteryLevel = 0;
        
        if (batteryLevel < 20) {
            logWarning("Low battery: " + std::to_string(batteryLevel) + "%");
        } else {
            logInfo("Battery level: " + std::to_string(batteryLevel) + "%");
        }
        
        if (batteryLevel == 0) {
            logError("Battery depleted - device shutting down");
            isConnected = false;
        }
    }
    
    // Implement Serializable interface
    std::string serialize() const override {
        return "name=" + deviceName + 
               ",battery=" + std::to_string(batteryLevel) +
               ",connected=" + (isConnected ? "true" : "false");
    }
    
    void deserialize(const std::string& data) override {
        logInfo("Deserializing: " + data);
        // Simple parsing simulation
        if (data.find("name=") != std::string::npos) {
            logInfo("Data deserialized successfully");
        }
    }
    
    void displayStatus() const {
        std::cout << "Device: " << deviceName 
                  << ", Battery: " << batteryLevel << "%"
                  << ", Connected: " << (isConnected ? "Yes" : "No") << std::endl;
    }
    
    std::string getDeviceName() const { return deviceName; }
    int getBatteryLevel() const { return batteryLevel; }
    bool getIsConnected() const { return isConnected; }
};

// ===== DEMONSTRATION FUNCTIONS =====

void demonstrateBasicMultipleInheritance() {
    std::cout << "\n=== BASIC MULTIPLE INHERITANCE DEMO ===" << std::endl;
    
    std::cout << "\n1. Creating a Duck (inherits from Animal, Flyable, Swimmable):" << std::endl;
    Duck mallard("Mallard", "Green", 2);
    
    std::cout << "\n2. Animal behaviors:" << std::endl;
    mallard.makeSound();
    mallard.eat();
    
    std::cout << "\n3. Flying behaviors:" << std::endl;
    mallard.takeOff();
    mallard.fly();
    mallard.setAltitude(1000);
    mallard.fly();
    
    std::cout << "\n4. Swimming behaviors:" << std::endl;
    mallard.land();  // Land on water
    mallard.swim();
    mallard.dive();
    mallard.forage();
    mallard.surface();
    
    std::cout << "\n5. Duck-specific behaviors:" << std::endl;
    mallard.startMigration();
    mallard.takeOff();
    mallard.fly();  // Now in migration mode
    mallard.stopMigration();
    
    std::cout << "\n6. Display complete information:" << std::endl;
    mallard.displayInfo();
}

void demonstrateDiamondProblem() {
    std::cout << "\n=== DIAMOND PROBLEM DEMO ===" << std::endl;
    
    std::cout << "\n1. Creating AmphibiousVehicle (demonstrates diamond problem):" << std::endl;
    AmphibiousVehicle amphi("DUKW", 1943, 6, "Propeller");
    
    std::cout << "\n2. Land mode operations:" << std::endl;
    amphi.switchToLand();
    amphi.move();
    
    std::cout << "\n3. Water mode operations:" << std::endl;
    amphi.switchToWater();
    amphi.move();
    
    std::cout << "\n4. Display information:" << std::endl;
    amphi.displayInfo();
    
    std::cout << "\n5. Demonstrating ambiguity resolution:" << std::endl;
    amphi.demonstrateAmbiguity();
    
    std::cout << "\nNote: This amphibious vehicle has TWO Vehicle base class instances!" << std::endl;
    std::cout << "This is the diamond problem - solved with virtual inheritance in next example." << std::endl;
}

void demonstrateMixinPattern() {
    std::cout << "\n=== MIXIN PATTERN DEMO ===" << std::endl;
    
    std::cout << "\n1. Creating SmartDevice with logging and serialization mixins:" << std::endl;
    Loggable::setLogLevel(3);  // Enable all log levels
    SmartDevice phone("iPhone", 85);
    
    std::cout << "\n2. Device operations with logging:" << std::endl;
    phone.connect();
    phone.useBattery(20);
    phone.useBattery(30);
    phone.useBattery(40);  // This should trigger low battery warning
    
    std::cout << "\n3. Serialization operations:" << std::endl;
    phone.saveToFile("device_state.dat");
    phone.loadFromFile("device_state.dat");
    
    std::cout << "\n4. Display device status:" << std::endl;
    phone.displayStatus();
    
    std::cout << "\n5. Different log levels:" << std::endl;
    Loggable::setLogLevel(1);  // Only INFO
    phone.connect();  // Already connected - should show warning but won't due to log level
    
    Loggable::setLogLevel(2);  // INFO and WARN
    phone.connect();  // Now warning will show
}

void demonstrateComplexHierarchy() {
    std::cout << "\n=== COMPLEX MULTIPLE INHERITANCE DEMO ===" << std::endl;
    
    // Create a vector of different objects showing polymorphism
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Duck>("Donald", "White", 5));
    
    std::cout << "\n1. Polymorphic behavior:" << std::endl;
    for (const auto& animal : animals) {
        animal->makeSound();
        animal->displayInfo();
        
        // Try to cast to specific types for extended functionality
        if (auto duck = dynamic_cast<Duck*>(animal.get())) {
            std::cout << "This is a duck - demonstrating flight:" << std::endl;
            duck->takeOff();
            duck->fly();
            duck->land();
        }
    }
    
    std::cout << "\n2. Multiple inheritance size comparison:" << std::endl;
    std::cout << "sizeof(Animal): " << sizeof(Animal) << " bytes" << std::endl;
    std::cout << "sizeof(Flyable): " << sizeof(Flyable) << " bytes" << std::endl;
    std::cout << "sizeof(Swimmable): " << sizeof(Swimmable) << " bytes" << std::endl;
    std::cout << "sizeof(Duck): " << sizeof(Duck) << " bytes" << std::endl;
    std::cout << "Note: Duck size is sum of all base classes plus its own members" << std::endl;
}

int main() {
    std::cout << "=== MULTIPLE INHERITANCE DEMONSTRATION ===" << std::endl;
    
    try {
        demonstrateBasicMultipleInheritance();
        demonstrateDiamondProblem();
        demonstrateMixinPattern();
        demonstrateComplexHierarchy();
        
        std::cout << "\n=== MULTIPLE INHERITANCE SUMMARY ===" << std::endl;
        std::cout << "\nKey Concepts Demonstrated:" << std::endl;
        std::cout << "✅ Multiple inheritance syntax (class D : public B1, public B2)" << std::endl;
        std::cout << "✅ Constructor/destructor order in multiple inheritance" << std::endl;
        std::cout << "✅ Diamond problem and ambiguity resolution" << std::endl;
        std::cout << "✅ Mixin pattern for adding capabilities" << std::endl;
        std::cout << "✅ Scope resolution operator for disambiguation" << std::endl;
        std::cout << "✅ Dynamic casting in complex hierarchies" << std::endl;
        std::cout << "✅ Memory layout implications" << std::endl;
        
        std::cout << "\nDiamond Problem:" << std::endl;
        std::cout << "• Occurs when class inherits from multiple classes with common base" << std::endl;
        std::cout << "• Creates duplicate base class instances" << std::endl;
        std::cout << "• Causes ambiguity in member access" << std::endl;
        std::cout << "• Solution: Virtual inheritance (see virtual_inheritance.cpp)" << std::endl;
        
        std::cout << "\nBest Practices:" << std::endl;
        std::cout << "• Use multiple inheritance sparingly" << std::endl;
        std::cout << "• Prefer composition over multiple inheritance" << std::endl;
        std::cout << "• Use mixins for adding capabilities" << std::endl;
        std::cout << "• Be aware of diamond problem and use virtual inheritance" << std::endl;
        std::cout << "• Use scope resolution for disambiguation" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

/*
Multiple Inheritance Summary:

Syntax:
class Derived : public Base1, public Base2, public Base3 {
    // Multiple base classes
};

Key Features:
1. Inherit from multiple classes simultaneously
2. Combine functionality from different sources
3. Create complex object hierarchies
4. Enable mixin patterns

Constructor/Destructor Order:
- Construction: Base classes in declaration order, then derived
- Destruction: Reverse order of construction

Diamond Problem:
      Base
     /    \
   Base1  Base2
     \    /
    Derived

- Multiple paths to same base class
- Creates duplicate instances
- Causes ambiguity in member access
- Solved with virtual inheritance

Common Use Cases:
1. Mixins - Adding capabilities (Loggable, Serializable)
2. Interfaces - Multiple interface implementation
3. Cross-cutting concerns - Logging, persistence, etc.

Ambiguity Resolution:
- Use scope resolution operator (Base1::member)
- Explicitly qualify member access
- Consider virtual inheritance

Memory Implications:
- Object size is sum of all base classes
- Virtual tables for each base with virtual functions
- Potential memory overhead with virtual inheritance

Alternatives:
1. Composition - "has-a" instead of "is-a"
2. Template-based mixins
3. Policy-based design
4. Dependency injection
*/
