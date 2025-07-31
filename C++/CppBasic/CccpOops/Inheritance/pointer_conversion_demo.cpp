// pointer_conversion_demo.cpp - Demonstrates pointer conversions in inheritance
// Compile: g++ -std=c++17 -Wall -Wextra pointer_conversion_demo.cpp -o pointer_conversion

#include <iostream>
#include <memory>
#include <vector>
#include <typeinfo>

// Base class hierarchy for demonstration
class Animal {
protected:
    std::string name;
    
public:
    Animal(const std::string& n) : name(n) {}
    virtual ~Animal() = default;  // Virtual destructor - IMPORTANT!
    
    virtual void makeSound() const {
        std::cout << name << " makes a generic animal sound\n";
    }
    
    virtual void move() const {
        std::cout << name << " moves around\n";
    }
    
    const std::string& getName() const { return name; }
    
    // Virtual function to identify type
    virtual std::string getType() const { return "Animal"; }
};

class Mammal : public Animal {
protected:
    bool hasFur;
    
public:
    Mammal(const std::string& n, bool fur = true) : Animal(n), hasFur(fur) {}
    
    virtual void giveBirth() const {
        std::cout << name << " gives birth to live young\n";
    }
    
    std::string getType() const override { return "Mammal"; }
    
    bool getHasFur() const { return hasFur; }
};

class Dog : public Mammal {
private:
    std::string breed;
    
public:
    Dog(const std::string& n, const std::string& b) : Mammal(n, true), breed(b) {}
    
    void makeSound() const override {
        std::cout << name << " (a " << breed << ") barks: Woof! Woof!\n";
    }
    
    void move() const override {
        std::cout << name << " runs around wagging tail\n";
    }
    
    // Dog-specific method
    void fetch() const {
        std::cout << name << " fetches the ball!\n";
    }
    
    std::string getType() const override { return "Dog"; }
    std::string getBreed() const { return breed; }
};

class Cat : public Mammal {
private:
    bool isIndoor;
    
public:
    Cat(const std::string& n, bool indoor = true) : Mammal(n, true), isIndoor(indoor) {}
    
    void makeSound() const override {
        std::cout << name << " meows: Meow! Meow!\n";
    }
    
    void move() const override {
        std::cout << name << " prowls silently\n";
    }
    
    // Cat-specific method
    void climb() const {
        std::cout << name << " climbs up the tree\n";
    }
    
    std::string getType() const override { return "Cat"; }
    bool getIsIndoor() const { return isIndoor; }
};

class Bird : public Animal {
private:
    bool canFly;
    
public:
    Bird(const std::string& n, bool fly = true) : Animal(n), canFly(fly) {}
    
    void makeSound() const override {
        std::cout << name << " chirps: Tweet! Tweet!\n";
    }
    
    void move() const override {
        if (canFly) {
            std::cout << name << " flies through the air\n";
        } else {
            std::cout << name << " walks on the ground\n";
        }
    }
    
    // Bird-specific method
    void fly() const {
        if (canFly) {
            std::cout << name << " soars high in the sky\n";
        } else {
            std::cout << name << " cannot fly\n";
        }
    }
    
    std::string getType() const override { return "Bird"; }
    bool getCanFly() const { return canFly; }
};

// Utility function to print object information
void printObjectInfo(const Animal* ptr) {
    std::cout << "Object Info: " << ptr->getName() 
              << " (" << ptr->getType() << ")\n";
}

// Function demonstrating polymorphism with base pointers
void demonstratePolymorphism(const std::vector<Animal*>& animals) {
    std::cout << "\n=== POLYMORPHISM DEMONSTRATION ===" << std::endl;
    
    for (const auto& animal : animals) {
        std::cout << "\n--- Processing " << animal->getName() << " ---" << std::endl;
        printObjectInfo(animal);
        animal->makeSound();
        animal->move();
    }
}

// Safe upcasting examples
void demonstrateUpcasting() {
    std::cout << "\n=== UPCASTING (DERIVED → BASE) - ALWAYS SAFE ===" << std::endl;
    
    // Create derived objects
    Dog* dogPtr = new Dog("Buddy", "Golden Retriever");
    Cat* catPtr = new Cat("Whiskers", true);
    Bird* birdPtr = new Bird("Tweety", true);
    
    std::cout << "\n1. Direct derived object access:" << std::endl;
    dogPtr->makeSound();
    dogPtr->fetch();  // Dog-specific method
    
    std::cout << "\n2. Implicit upcasting to base class:" << std::endl;
    
    // ✅ SAFE: Implicit conversion from derived to base
    Animal* animalPtr1 = dogPtr;     // Dog* → Animal*
    Animal* animalPtr2 = catPtr;     // Cat* → Animal*
    Animal* animalPtr3 = birdPtr;    // Bird* → Animal*
    
    // Still calls derived class methods due to virtual functions
    animalPtr1->makeSound();  // Calls Dog::makeSound()
    animalPtr2->makeSound();  // Calls Cat::makeSound()
    animalPtr3->makeSound();  // Calls Bird::makeSound()
    
    std::cout << "\n3. Upcasting to intermediate base (Mammal):" << std::endl;
    
    // ✅ SAFE: Dog → Mammal → Animal
    Mammal* mammalPtr1 = dogPtr;     // Dog* → Mammal*
    Mammal* mammalPtr2 = catPtr;     // Cat* → Mammal*
    
    mammalPtr1->giveBirth();  // Mammal method available
    mammalPtr2->giveBirth();  // Mammal method available
    
    // ✅ SAFE: Further upcasting Mammal → Animal
    Animal* animalPtr4 = mammalPtr1;  // Mammal* → Animal*
    Animal* animalPtr5 = mammalPtr2;  // Mammal* → Animal*
    
    animalPtr4->makeSound();
    animalPtr5->makeSound();
    
    // Cleanup
    delete dogPtr;
    delete catPtr;
    delete birdPtr;
}

// Downcasting examples (with safety checks)
void demonstrateDowncasting() {
    std::cout << "\n=== DOWNCASTING (BASE → DERIVED) - REQUIRES CARE ===" << std::endl;
    
    // Create objects through base pointers (upcasting)
    Animal* animals[] = {
        new Dog("Rex", "German Shepherd"),
        new Cat("Fluffy", false),
        new Bird("Eagle", true),
        new Animal("Generic")  // Pure Animal object
    };
    
    std::cout << "\n1. Safe downcasting with dynamic_cast:" << std::endl;
    
    for (int i = 0; i < 4; ++i) {
        Animal* animal = animals[i];
        std::cout << "\n--- Processing " << animal->getName() << " ---" << std::endl;
        
        // ✅ SAFE: Try to downcast to Dog
        Dog* dogPtr = dynamic_cast<Dog*>(animal);
        if (dogPtr) {
            std::cout << "✅ Successfully cast to Dog: " << dogPtr->getBreed() << std::endl;
            dogPtr->fetch();
        } else {
            std::cout << "❌ Not a Dog object" << std::endl;
        }
        
        // ✅ SAFE: Try to downcast to Cat
        Cat* catPtr = dynamic_cast<Cat*>(animal);
        if (catPtr) {
            std::cout << "✅ Successfully cast to Cat: " 
                      << (catPtr->getIsIndoor() ? "Indoor" : "Outdoor") << std::endl;
            catPtr->climb();
        } else {
            std::cout << "❌ Not a Cat object" << std::endl;
        }
        
        // ✅ SAFE: Try to downcast to Bird
        Bird* birdPtr = dynamic_cast<Bird*>(animal);
        if (birdPtr) {
            std::cout << "✅ Successfully cast to Bird: " 
                      << (birdPtr->getCanFly() ? "Can fly" : "Cannot fly") << std::endl;
            birdPtr->fly();
        } else {
            std::cout << "❌ Not a Bird object" << std::endl;
        }
        
        // ✅ SAFE: Try to downcast to Mammal
        Mammal* mammalPtr = dynamic_cast<Mammal*>(animal);
        if (mammalPtr) {
            std::cout << "✅ Successfully cast to Mammal" << std::endl;
            mammalPtr->giveBirth();
        } else {
            std::cout << "❌ Not a Mammal object" << std::endl;
        }
    }
    
    std::cout << "\n2. Dangerous downcasting with static_cast (NOT RECOMMENDED):" << std::endl;
    std::cout << "⚠️  static_cast doesn't check if cast is valid!" << std::endl;
    
    Animal* genericAnimal = new Animal("Generic");
    
    // ⚠️ DANGEROUS: static_cast doesn't verify the cast
    Dog* forcedDog = static_cast<Dog*>(genericAnimal);
    std::cout << "static_cast succeeded (but object is not actually a Dog!)" << std::endl;
    
    // ❌ UNDEFINED BEHAVIOR: Calling Dog methods on non-Dog object
    // forcedDog->fetch();  // DON'T DO THIS - undefined behavior!
    // forcedDog->getBreed(); // DON'T DO THIS - undefined behavior!
    
    std::cout << "⚠️  Calling Dog methods would cause undefined behavior!" << std::endl;
    
    // Cleanup
    for (auto animal : animals) {
        delete animal;
    }
    delete genericAnimal;
}

// Smart pointer examples
void demonstrateSmartPointers() {
    std::cout << "\n=== SMART POINTERS WITH INHERITANCE ===" << std::endl;
    
    // ✅ SAFE: Upcasting with smart pointers
    std::unique_ptr<Dog> dogPtr = std::make_unique<Dog>("Smart Buddy", "Labrador");
    std::unique_ptr<Animal> animalPtr = std::move(dogPtr);  // Upcasting
    
    std::cout << "Smart pointer upcasting:" << std::endl;
    animalPtr->makeSound();
    
    // ✅ SAFE: Polymorphic container
    std::vector<std::unique_ptr<Animal>> animalPtrs;
    animalPtrs.push_back(std::make_unique<Dog>("Smart Rex", "Bulldog"));
    animalPtrs.push_back(std::make_unique<Cat>("Smart Whiskers", true));
    animalPtrs.push_back(std::make_unique<Bird>("Smart Tweety", true));
    
    std::cout << "\nPolymorphic container with smart pointers:" << std::endl;
    for (const auto& animal : animalPtrs) {
        animal->makeSound();
    }
    
    // Smart pointers automatically handle cleanup!
}

// Function that accepts base class pointer (demonstrates polymorphism)
void processAnimal(Animal* animal) {
    if (!animal) return;
    
    std::cout << "\n--- Processing Animal ---" << std::endl;
    std::cout << "Type: " << animal->getType() << std::endl;
    std::cout << "Name: " << animal->getName() << std::endl;
    animal->makeSound();
    animal->move();
    
    // Try to access derived class specific features
    if (Dog* dog = dynamic_cast<Dog*>(animal)) {
        std::cout << "Breed: " << dog->getBreed() << std::endl;
        dog->fetch();
    } else if (Cat* cat = dynamic_cast<Cat*>(animal)) {
        std::cout << "Indoor: " << (cat->getIsIndoor() ? "Yes" : "No") << std::endl;
        cat->climb();
    } else if (Bird* bird = dynamic_cast<Bird*>(animal)) {
        std::cout << "Can fly: " << (bird->getCanFly() ? "Yes" : "No") << std::endl;
        bird->fly();
    }
}

int main() {
    std::cout << "=== POINTER CONVERSION IN INHERITANCE ===" << std::endl;
    std::cout << "Demonstrates safe upcasting and careful downcasting" << std::endl;
    
    demonstrateUpcasting();
    demonstrateDowncasting();
    demonstrateSmartPointers();
    
    std::cout << "\n=== POLYMORPHISM IN ACTION ===" << std::endl;
    
    // Create a mixed collection through base pointers
    std::vector<Animal*> zoo = {
        new Dog("Rover", "Beagle"),
        new Cat("Mittens", true),
        new Bird("Parrot", true),
        new Dog("Max", "Poodle")
    };
    
    demonstratePolymorphism(zoo);
    
    std::cout << "\n=== PROCESSING INDIVIDUAL ANIMALS ===" << std::endl;
    for (auto animal : zoo) {
        processAnimal(animal);
    }
    
    // Cleanup
    for (auto animal : zoo) {
        delete animal;
    }
    
    std::cout << "\n=== KEY TAKEAWAYS ===" << std::endl;
    std::cout << "✅ Upcasting (Derived → Base) is ALWAYS SAFE and implicit" << std::endl;
    std::cout << "✅ Enables polymorphism and code reusability" << std::endl;
    std::cout << "✅ Virtual functions work correctly through base pointers" << std::endl;
    std::cout << "⚠️  Downcasting (Base → Derived) requires dynamic_cast for safety" << std::endl;
    std::cout << "⚠️  Always check dynamic_cast result before using" << std::endl;
    std::cout << "❌ Avoid static_cast for downcasting (unsafe)" << std::endl;
    std::cout << "💡 Use smart pointers for automatic memory management" << std::endl;
    std::cout << "💡 Virtual destructors ensure proper cleanup" << std::endl;
    
    return 0;
}

/*
Expected Output Highlights:

=== UPCASTING (DERIVED → BASE) - ALWAYS SAFE ===
Buddy (a Golden Retriever) barks: Woof! Woof!
Buddy fetches the ball!
Buddy (a Golden Retriever) barks: Woof! Woof!
Whiskers meows: Meow! Meow!
Tweety chirps: Tweet! Tweet!

=== DOWNCASTING (BASE → DERIVED) - REQUIRES CARE ===
✅ Successfully cast to Dog: German Shepherd
Rex fetches the ball!
❌ Not a Dog object
✅ Successfully cast to Cat: Outdoor
Fluffy climbs up the tree

Key Learning Points:
1. Upcasting is safe and implicit
2. Downcasting requires dynamic_cast
3. Virtual functions enable polymorphism
4. Smart pointers work seamlessly with inheritance
5. Always use virtual destructors in base classes
*/
