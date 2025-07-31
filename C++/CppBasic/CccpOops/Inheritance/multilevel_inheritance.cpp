/**
 * @file multilevel_inheritance.cpp
 * @brief Demonstration of Multilevel Inheritance in C++
 * 
 * Multilevel inheritance creates a chain of inheritance where each class
 * inherits from the previous one, forming a hierarchy: A → B → C → D
 * 
 * Compile: g++ -std=c++17 -Wall -Wextra multilevel_inheritance.cpp -o multilevel_inheritance
 * Run: ./multilevel_inheritance
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

// ===== LIVING BEINGS HIERARCHY =====

/**
 * Level 1: Base class - LivingBeing
 */
class LivingBeing {
protected:
    std::string scientificName;
    int ageInYears;
    bool isAlive;
    double energyLevel;

public:
    LivingBeing(const std::string& name, int age = 0)
        : scientificName(name), ageInYears(age), isAlive(true), energyLevel(100.0) {
        std::cout << "LivingBeing constructor: " << scientificName << std::endl;
    }
    
    virtual ~LivingBeing() {
        std::cout << "LivingBeing destructor: " << scientificName << std::endl;
    }
    
    virtual void breathe() const {
        std::cout << scientificName << " is breathing" << std::endl;
    }
    
    virtual void grow() {
        ageInYears++;
        std::cout << scientificName << " grew older, now " << ageInYears << " years old" << std::endl;
    }
    
    virtual void consumeEnergy(double amount) {
        energyLevel -= amount;
        if (energyLevel < 0) energyLevel = 0;
        if (energyLevel == 0) {
            isAlive = false;
            std::cout << scientificName << " has no energy left" << std::endl;
        }
    }
    
    virtual void displayInfo() const {
        std::cout << "Living Being: " << scientificName 
                  << ", Age: " << ageInYears 
                  << ", Energy: " << std::fixed << std::setprecision(1) << energyLevel << "%"
                  << ", Alive: " << (isAlive ? "Yes" : "No") << std::endl;
    }
    
    // Getters
    std::string getScientificName() const { return scientificName; }
    int getAge() const { return ageInYears; }
    bool getIsAlive() const { return isAlive; }
    double getEnergyLevel() const { return energyLevel; }
};

/**
 * Level 2: Animal inherits from LivingBeing
 */
class Animal : public LivingBeing {
protected:
    std::string habitat;
    std::string diet;
    bool canMove;
    double size;  // in meters

public:
    Animal(const std::string& name, const std::string& hab, const std::string& d, 
           double s, int age = 0)
        : LivingBeing(name, age), habitat(hab), diet(d), canMove(true), size(s) {
        std::cout << "Animal constructor: " << scientificName << " in " << habitat << std::endl;
    }
    
    ~Animal() override {
        std::cout << "Animal destructor: " << scientificName << std::endl;
    }
    
    virtual void eat() {
        energyLevel += 20;
        if (energyLevel > 100) energyLevel = 100;
        std::cout << scientificName << " eats (" << diet << "), energy restored" << std::endl;
    }
    
    virtual void move() {
        if (canMove && isAlive) {
            consumeEnergy(5);
            std::cout << scientificName << " moves around in " << habitat << std::endl;
        } else {
            std::cout << scientificName << " cannot move" << std::endl;
        }
    }
    
    virtual void sleep() {
        energyLevel += 10;
        if (energyLevel > 100) energyLevel = 100;
        std::cout << scientificName << " sleeps and recovers energy" << std::endl;
    }
    
    virtual void makeSound() const = 0;  // Pure virtual - specific to each animal
    
    void displayInfo() const override {
        LivingBeing::displayInfo();
        std::cout << "  Habitat: " << habitat 
                  << ", Diet: " << diet 
                  << ", Size: " << size << "m" << std::endl;
    }
    
    // Getters
    std::string getHabitat() const { return habitat; }
    std::string getDiet() const { return diet; }
    double getSize() const { return size; }
};

/**
 * Level 3: Mammal inherits from Animal
 */
class Mammal : public Animal {
protected:
    std::string furType;
    double bodyTemperature;
    bool isWarmBlooded;
    int numberOfOffspring;

public:
    Mammal(const std::string& name, const std::string& hab, const std::string& d,
           double s, const std::string& fur, int age = 0)
        : Animal(name, hab, d, s, age), furType(fur), bodyTemperature(37.0),
          isWarmBlooded(true), numberOfOffspring(0) {
        std::cout << "Mammal constructor: " << scientificName << " with " << furType << " fur" << std::endl;
    }
    
    ~Mammal() override {
        std::cout << "Mammal destructor: " << scientificName << std::endl;
    }
    
    virtual void regulateTemperature() {
        if (bodyTemperature < 36.0) {
            bodyTemperature = 37.0;
            consumeEnergy(8);
            std::cout << scientificName << " regulates body temperature" << std::endl;
        }
    }
    
    virtual void giveBirth(int offspring = 1) {
        numberOfOffspring += offspring;
        consumeEnergy(30);
        std::cout << scientificName << " gives birth to " << offspring 
                  << " offspring. Total offspring: " << numberOfOffspring << std::endl;
    }
    
    virtual void nurseYoung() {
        if (numberOfOffspring > 0) {
            consumeEnergy(15);
            std::cout << scientificName << " nurses young with milk" << std::endl;
        } else {
            std::cout << scientificName << " has no young to nurse" << std::endl;
        }
    }
    
    virtual void shedFur() {
        std::cout << scientificName << " sheds " << furType << " fur seasonally" << std::endl;
    }
    
    void displayInfo() const override {
        Animal::displayInfo();
        std::cout << "  Fur: " << furType 
                  << ", Body Temp: " << std::fixed << std::setprecision(1) << bodyTemperature << "°C"
                  << ", Offspring: " << numberOfOffspring << std::endl;
    }
    
    // Getters
    std::string getFurType() const { return furType; }
    double getBodyTemperature() const { return bodyTemperature; }
    int getNumberOfOffspring() const { return numberOfOffspring; }
};

/**
 * Level 4: Dog inherits from Mammal
 */
class Dog : public Mammal {
private:
    std::string breed;
    std::string ownerName;
    bool isTrained;
    std::vector<std::string> tricks;

public:
    Dog(const std::string& name, const std::string& b, const std::string& owner, int age = 1)
        : Mammal(name + " " + b, "Domestic", "Omnivore", 0.6, "Short", age),
          breed(b), ownerName(owner), isTrained(false) {
        std::cout << "Dog constructor: " << breed << " named " << name << ", owned by " << ownerName << std::endl;
    }
    
    ~Dog() override {
        std::cout << "Dog destructor: " << breed << std::endl;
    }
    
    void makeSound() const override {
        std::cout << scientificName << " barks: Woof! Woof!" << std::endl;
    }
    
    void eat() override {
        Mammal::eat();  // Call parent method
        std::cout << "Dog eats dog food from bowl" << std::endl;
    }
    
    void move() override {
        if (canMove && isAlive) {
            consumeEnergy(3);  // Dogs are efficient movers
            std::cout << scientificName << " runs and plays happily" << std::endl;
        }
    }
    
    // Dog-specific behaviors
    void wagTail() const {
        std::cout << scientificName << " wags tail enthusiastically" << std::endl;
    }
    
    void fetch() const {
        if (isTrained) {
            std::cout << scientificName << " fetches the ball for " << ownerName << std::endl;
        } else {
            std::cout << scientificName << " doesn't understand fetch command" << std::endl;
        }
    }
    
    void learnTrick(const std::string& trick) {
        tricks.push_back(trick);
        isTrained = true;
        consumeEnergy(10);
        std::cout << scientificName << " learned new trick: " << trick << std::endl;
    }
    
    void performTricks() const {
        if (tricks.empty()) {
            std::cout << scientificName << " doesn't know any tricks yet" << std::endl;
        } else {
            std::cout << scientificName << " performs tricks: ";
            for (size_t i = 0; i < tricks.size(); ++i) {
                std::cout << tricks[i];
                if (i < tricks.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
    
    void guardHouse() const {
        std::cout << scientificName << " guards " << ownerName << "'s house" << std::endl;
    }
    
    void playWith(const Dog& other) const {
        std::cout << scientificName << " plays with " << other.getBreed() << std::endl;
    }
    
    void displayInfo() const override {
        Mammal::displayInfo();
        std::cout << "  Breed: " << breed 
                  << ", Owner: " << ownerName 
                  << ", Trained: " << (isTrained ? "Yes" : "No")
                  << ", Tricks: " << tricks.size() << std::endl;
    }
    
    // Getters
    std::string getBreed() const { return breed; }
    std::string getOwnerName() const { return ownerName; }
    bool getIsTrained() const { return isTrained; }
    const std::vector<std::string>& getTricks() const { return tricks; }
};

// ===== TECHNOLOGY HIERARCHY =====

/**
 * Level 1: Base class - Device
 */
class Device {
protected:
    std::string deviceId;
    std::string manufacturer;
    int yearManufactured;
    bool isPoweredOn;
    double powerConsumption;  // watts

public:
    Device(const std::string& id, const std::string& mfg, int year, double power)
        : deviceId(id), manufacturer(mfg), yearManufactured(year), 
          isPoweredOn(false), powerConsumption(power) {
        std::cout << "Device constructor: " << deviceId << " by " << manufacturer << std::endl;
    }
    
    virtual ~Device() {
        std::cout << "Device destructor: " << deviceId << std::endl;
    }
    
    virtual void powerOn() {
        isPoweredOn = true;
        std::cout << deviceId << " powered on (consuming " << powerConsumption << "W)" << std::endl;
    }
    
    virtual void powerOff() {
        isPoweredOn = false;
        std::cout << deviceId << " powered off" << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << "Device: " << deviceId 
                  << " (" << manufacturer << ", " << yearManufactured << ")"
                  << ", Status: " << (isPoweredOn ? "ON" : "OFF")
                  << ", Power: " << powerConsumption << "W" << std::endl;
    }
    
    // Getters
    std::string getDeviceId() const { return deviceId; }
    std::string getManufacturer() const { return manufacturer; }
    bool getIsPoweredOn() const { return isPoweredOn; }
};

/**
 * Level 2: Computer inherits from Device
 */
class Computer : public Device {
protected:
    std::string operatingSystem;
    int ramSize;  // GB
    int storageSize;  // GB
    double cpuSpeed;  // GHz

public:
    Computer(const std::string& id, const std::string& mfg, int year, 
             const std::string& os, int ram, int storage, double cpu)
        : Device(id, mfg, year, 150.0), operatingSystem(os), 
          ramSize(ram), storageSize(storage), cpuSpeed(cpu) {
        std::cout << "Computer constructor: " << deviceId << " with " << operatingSystem << std::endl;
    }
    
    ~Computer() override {
        std::cout << "Computer destructor: " << deviceId << std::endl;
    }
    
    virtual void boot() {
        if (isPoweredOn) {
            std::cout << deviceId << " booting " << operatingSystem << "..." << std::endl;
        } else {
            std::cout << "Cannot boot - device is powered off" << std::endl;
        }
    }
    
    virtual void shutdown() {
        if (isPoweredOn) {
            std::cout << deviceId << " shutting down " << operatingSystem << std::endl;
            powerOff();
        }
    }
    
    virtual void installSoftware(const std::string& software) {
        if (isPoweredOn) {
            std::cout << "Installing " << software << " on " << deviceId << std::endl;
        } else {
            std::cout << "Cannot install software - computer is off" << std::endl;
        }
    }
    
    void displayInfo() const override {
        Device::displayInfo();
        std::cout << "  OS: " << operatingSystem 
                  << ", RAM: " << ramSize << "GB"
                  << ", Storage: " << storageSize << "GB"
                  << ", CPU: " << cpuSpeed << "GHz" << std::endl;
    }
    
    // Getters
    std::string getOperatingSystem() const { return operatingSystem; }
    int getRamSize() const { return ramSize; }
};

/**
 * Level 3: Laptop inherits from Computer
 */
class Laptop : public Computer {
protected:
    double screenSize;  // inches
    int batteryLife;    // hours
    double weight;      // kg
    bool hasWebcam;

public:
    Laptop(const std::string& id, const std::string& mfg, int year,
           const std::string& os, int ram, int storage, double cpu,
           double screen, int battery, double w)
        : Computer(id, mfg, year, os, ram, storage, cpu),
          screenSize(screen), batteryLife(battery), weight(w), hasWebcam(true) {
        std::cout << "Laptop constructor: " << deviceId << " (" << screenSize << "\" screen)" << std::endl;
    }
    
    ~Laptop() override {
        std::cout << "Laptop destructor: " << deviceId << std::endl;
    }
    
    void openLid() {
        std::cout << "Opening " << deviceId << " lid" << std::endl;
        powerOn();
    }
    
    void closeLid() {
        std::cout << "Closing " << deviceId << " lid (sleep mode)" << std::endl;
    }
    
    void connectToWifi(const std::string& network) {
        if (isPoweredOn) {
            std::cout << deviceId << " connecting to WiFi network: " << network << std::endl;
        } else {
            std::cout << "Cannot connect to WiFi - laptop is off" << std::endl;
        }
    }
    
    void startVideoCall() {
        if (isPoweredOn && hasWebcam) {
            std::cout << deviceId << " starting video call using webcam" << std::endl;
        } else {
            std::cout << "Cannot start video call - laptop off or no webcam" << std::endl;
        }
    }
    
    void displayInfo() const override {
        Computer::displayInfo();
        std::cout << "  Screen: " << screenSize << "\""
                  << ", Battery: " << batteryLife << "h"
                  << ", Weight: " << weight << "kg"
                  << ", Webcam: " << (hasWebcam ? "Yes" : "No") << std::endl;
    }
    
    double getScreenSize() const { return screenSize; }
    int getBatteryLife() const { return batteryLife; }
};

/**
 * Level 4: GamingLaptop inherits from Laptop
 */
class GamingLaptop : public Laptop {
private:
    std::string graphicsCard;
    int refreshRate;  // Hz
    bool hasRGBKeyboard;
    std::vector<std::string> installedGames;

public:
    GamingLaptop(const std::string& id, const std::string& mfg, int year,
                 const std::string& os, int ram, int storage, double cpu,
                 double screen, int battery, double w, const std::string& gpu, int refresh)
        : Laptop(id, mfg, year, os, ram, storage, cpu, screen, battery, w),
          graphicsCard(gpu), refreshRate(refresh), hasRGBKeyboard(true) {
        std::cout << "GamingLaptop constructor: " << deviceId << " with " << graphicsCard << std::endl;
        powerConsumption = 200.0;  // Gaming laptops consume more power
    }
    
    ~GamingLaptop() override {
        std::cout << "GamingLaptop destructor: " << deviceId << std::endl;
    }
    
    void installGame(const std::string& game) {
        if (isPoweredOn) {
            installedGames.push_back(game);
            std::cout << "Installing game: " << game << " on " << deviceId << std::endl;
        } else {
            std::cout << "Cannot install game - laptop is off" << std::endl;
        }
    }
    
    void playGame(const std::string& game) {
        if (!isPoweredOn) {
            std::cout << "Cannot play game - laptop is off" << std::endl;
            return;
        }
        
        bool gameFound = false;
        for (const auto& installedGame : installedGames) {
            if (installedGame == game) {
                gameFound = true;
                break;
            }
        }
        
        if (gameFound) {
            std::cout << "Playing " << game << " on " << deviceId 
                      << " at " << refreshRate << "Hz with " << graphicsCard << std::endl;
        } else {
            std::cout << game << " is not installed on " << deviceId << std::endl;
        }
    }
    
    void enableRGBLighting() {
        if (hasRGBKeyboard) {
            std::cout << deviceId << " RGB keyboard lighting enabled - rainbow mode!" << std::endl;
        }
    }
    
    void overclockGPU() {
        std::cout << "Overclocking " << graphicsCard << " for better performance" << std::endl;
        powerConsumption += 50;  // Overclocking increases power consumption
    }
    
    void streamGameplay(const std::string& platform) {
        if (isPoweredOn) {
            std::cout << deviceId << " streaming gameplay to " << platform << std::endl;
        } else {
            std::cout << "Cannot stream - laptop is off" << std::endl;
        }
    }
    
    void displayInfo() const override {
        Laptop::displayInfo();
        std::cout << "  GPU: " << graphicsCard 
                  << ", Refresh Rate: " << refreshRate << "Hz"
                  << ", RGB Keyboard: " << (hasRGBKeyboard ? "Yes" : "No")
                  << ", Games: " << installedGames.size() << std::endl;
    }
    
    std::string getGraphicsCard() const { return graphicsCard; }
    const std::vector<std::string>& getInstalledGames() const { return installedGames; }
};

// ===== DEMONSTRATION FUNCTIONS =====

void demonstrateBiologicalHierarchy() {
    std::cout << "\n=== BIOLOGICAL MULTILEVEL INHERITANCE DEMO ===" << std::endl;
    
    std::cout << "\n1. Creating a Dog (4 levels of inheritance):" << std::endl;
    Dog buddy("Buddy", "Golden Retriever", "Alice", 3);
    
    std::cout << "\n2. Level 1 - LivingBeing behaviors:" << std::endl;
    buddy.breathe();
    buddy.grow();
    
    std::cout << "\n3. Level 2 - Animal behaviors:" << std::endl;
    buddy.makeSound();
    buddy.eat();
    buddy.move();
    buddy.sleep();
    
    std::cout << "\n4. Level 3 - Mammal behaviors:" << std::endl;
    buddy.regulateTemperature();
    buddy.shedFur();
    buddy.giveBirth(3);
    buddy.nurseYoung();
    
    std::cout << "\n5. Level 4 - Dog behaviors:" << std::endl;
    buddy.wagTail();
    buddy.fetch();  // Not trained yet
    buddy.learnTrick("sit");
    buddy.learnTrick("roll over");
    buddy.learnTrick("play dead");
    buddy.performTricks();
    buddy.fetch();  // Now trained
    buddy.guardHouse();
    
    std::cout << "\n6. Complete information display:" << std::endl;
    buddy.displayInfo();
    
    std::cout << "\n7. Energy management demonstration:" << std::endl;
    std::cout << "Initial energy: " << buddy.getEnergyLevel() << "%" << std::endl;
    buddy.move();
    buddy.move();
    buddy.learnTrick("shake hands");
    std::cout << "After activities: " << buddy.getEnergyLevel() << "%" << std::endl;
    buddy.eat();
    buddy.sleep();
    std::cout << "After rest: " << buddy.getEnergyLevel() << "%" << std::endl;
}

void demonstrateTechnologyHierarchy() {
    std::cout << "\n=== TECHNOLOGY MULTILEVEL INHERITANCE DEMO ===" << std::endl;
    
    std::cout << "\n1. Creating a Gaming Laptop (4 levels of inheritance):" << std::endl;
    GamingLaptop gaming("ASUS-ROG-001", "ASUS", 2023, "Windows 11", 32, 1000, 3.2, 
                       17.3, 8, 2.5, "RTX 4080", 240);
    
    std::cout << "\n2. Level 1 - Device behaviors:" << std::endl;
    gaming.powerOn();
    
    std::cout << "\n3. Level 2 - Computer behaviors:" << std::endl;
    gaming.boot();
    gaming.installSoftware("Steam");
    gaming.installSoftware("Discord");
    
    std::cout << "\n4. Level 3 - Laptop behaviors:" << std::endl;
    gaming.connectToWifi("GamersNetwork");
    gaming.startVideoCall();
    
    std::cout << "\n5. Level 4 - Gaming Laptop behaviors:" << std::endl;
    gaming.enableRGBLighting();
    gaming.installGame("Cyberpunk 2077");
    gaming.installGame("Call of Duty");
    gaming.installGame("Minecraft");
    gaming.playGame("Cyberpunk 2077");
    gaming.overclockGPU();
    gaming.streamGameplay("Twitch");
    
    std::cout << "\n6. Complete information display:" << std::endl;
    gaming.displayInfo();
    
    std::cout << "\n7. Laptop lifecycle:" << std::endl;
    gaming.closeLid();
    gaming.openLid();  // Powers back on
    gaming.playGame("Minecraft");
    gaming.shutdown();
}

void demonstratePolymorphismInMultilevel() {
    std::cout << "\n=== POLYMORPHISM IN MULTILEVEL INHERITANCE ===" << std::endl;
    
    // Create polymorphic containers at different levels
    std::cout << "\n1. Polymorphic behavior at LivingBeing level:" << std::endl;
    std::vector<std::unique_ptr<LivingBeing>> livingBeings;
    livingBeings.push_back(std::make_unique<Dog>("Rex", "German Shepherd", "Bob", 5));
    
    for (const auto& being : livingBeings) {
        being->breathe();
        being->displayInfo();
    }
    
    std::cout << "\n2. Polymorphic behavior at Animal level:" << std::endl;
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("Max", "Labrador", "Carol", 2));
    
    for (const auto& animal : animals) {
        animal->makeSound();
        animal->eat();
        animal->move();
    }
    
    std::cout << "\n3. Polymorphic behavior at Device level:" << std::endl;
    std::vector<std::unique_ptr<Device>> devices;
    devices.push_back(std::make_unique<GamingLaptop>("MSI-001", "MSI", 2023, "Windows 11", 
                                                     16, 512, 2.8, 15.6, 6, 2.2, "RTX 4060", 144));
    
    for (const auto& device : devices) {
        device->powerOn();
        device->displayInfo();
        device->powerOff();
    }
}

void demonstrateInheritanceChain() {
    std::cout << "\n=== INHERITANCE CHAIN ANALYSIS ===" << std::endl;
    
    Dog testDog("Test", "Test Breed", "Test Owner", 1);
    
    std::cout << "\nInheritance chain for Dog:" << std::endl;
    std::cout << "Level 1: LivingBeing (base class)" << std::endl;
    std::cout << "Level 2: Animal (inherits from LivingBeing)" << std::endl;
    std::cout << "Level 3: Mammal (inherits from Animal)" << std::endl;
    std::cout << "Level 4: Dog (inherits from Mammal)" << std::endl;
    
    std::cout << "\nSize analysis:" << std::endl;
    std::cout << "sizeof(LivingBeing): " << sizeof(LivingBeing) << " bytes" << std::endl;
    std::cout << "sizeof(Animal): " << sizeof(Animal) << " bytes" << std::endl;
    std::cout << "sizeof(Mammal): " << sizeof(Mammal) << " bytes" << std::endl;
    std::cout << "sizeof(Dog): " << sizeof(Dog) << " bytes" << std::endl;
    
    std::cout << "\nNote: Each level adds its own data members to the total size" << std::endl;
    
    std::cout << "\nAccess to inherited methods:" << std::endl;
    std::cout << "Dog can call:" << std::endl;
    std::cout << "- LivingBeing methods: breathe(), grow(), consumeEnergy()" << std::endl;
    std::cout << "- Animal methods: eat(), move(), sleep()" << std::endl;
    std::cout << "- Mammal methods: regulateTemperature(), giveBirth()" << std::endl;
    std::cout << "- Dog methods: wagTail(), fetch(), learnTrick()" << std::endl;
}

int main() {
    std::cout << "=== MULTILEVEL INHERITANCE DEMONSTRATION ===" << std::endl;
    
    try {
        demonstrateBiologicalHierarchy();
        demonstrateTechnologyHierarchy();
        demonstratePolymorphismInMultilevel();
        demonstrateInheritanceChain();
        
        std::cout << "\n=== MULTILEVEL INHERITANCE SUMMARY ===" << std::endl;
        std::cout << "\nKey Concepts Demonstrated:" << std::endl;
        std::cout << "✅ Chain of inheritance (A → B → C → D)" << std::endl;
        std::cout << "✅ Constructor/destructor order in chains" << std::endl;
        std::cout << "✅ Method overriding at multiple levels" << std::endl;
        std::cout << "✅ Access to inherited functionality" << std::endl;
        std::cout << "✅ Polymorphism at different hierarchy levels" << std::endl;
        std::cout << "✅ Cumulative data member inheritance" << std::endl;
        std::cout << "✅ Virtual function behavior in chains" << std::endl;
        
        std::cout << "\nBenefits of Multilevel Inheritance:" << std::endl;
        std::cout << "• Logical organization of related classes" << std::endl;
        std::cout << "• Progressive specialization" << std::endl;
        std::cout << "• Code reuse at multiple levels" << std::endl;
        std::cout << "• Natural modeling of real-world hierarchies" << std::endl;
        
        std::cout << "\nBest Practices:" << std::endl;
        std::cout << "• Keep inheritance chains shallow (3-4 levels max)" << std::endl;
        std::cout << "• Use virtual destructors in base classes" << std::endl;
        std::cout << "• Document inheritance relationships clearly" << std::endl;
        std::cout << "• Consider composition for deep hierarchies" << std::endl;
        std::cout << "• Use pure virtual functions for contracts" << std::endl;
        
        std::cout << "\nPotential Issues:" << std::endl;
        std::cout << "• Deep hierarchies can be hard to understand" << std::endl;
        std::cout << "• Changes in base classes affect all derived classes" << std::endl;
        std::cout << "• Increased coupling between levels" << std::endl;
        std::cout << "• Performance overhead with deep virtual calls" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

/*
Multilevel Inheritance Summary:

Structure:
class A { };           // Level 1 (Base)
class B : public A { }; // Level 2 (inherits from A)
class C : public B { }; // Level 3 (inherits from B, indirectly from A)
class D : public C { }; // Level 4 (inherits from C, B, and A)

Key Features:
1. Linear inheritance chain
2. Each level builds upon the previous
3. Progressive specialization
4. Cumulative functionality

Constructor/Destructor Order:
Construction: A → B → C → D (base to derived)
Destruction: D → C → B → A (derived to base)

Memory Layout:
┌─────────────────┐
│ A's members     │
├─────────────────┤
│ B's members     │
├─────────────────┤
│ C's members     │
├─────────────────┤
│ D's members     │
└─────────────────┘

Access Rules:
- Each level can access public/protected members of all parent levels
- Private members are only accessible within their own class
- Virtual functions enable polymorphism at any level

Common Use Cases:
1. Biological taxonomies (Kingdom → Phylum → Class → Species)
2. Technology hierarchies (Device → Computer → Laptop → Gaming Laptop)
3. GUI frameworks (Widget → Control → Button → ImageButton)
4. Vehicle classifications (Vehicle → LandVehicle → Car → SportsCar)

Benefits:
- Natural modeling of real-world hierarchies
- Progressive refinement of functionality
- Code reuse across multiple levels
- Polymorphic behavior at different abstraction levels

Drawbacks:
- Can become complex with deep hierarchies
- Tight coupling between levels
- Changes propagate through entire chain
- Performance impact with deep virtual calls

Best Practices:
- Limit depth to 3-4 levels maximum
- Use composition for complex relationships
- Document inheritance relationships
- Keep base classes stable
- Use virtual destructors
*/
