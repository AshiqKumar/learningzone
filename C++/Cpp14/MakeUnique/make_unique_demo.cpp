// C++14 std::make_unique - Smart Pointer Factory Function
// Compile: g++ -std=c++14 -o make_unique_demo make_unique_demo.cpp
// Run: ./make_unique_demo

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <array>

// Custom classes for demonstration
class Person {
private:
    std::string name;
    int age;
    
public:
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Person constructor: " << name << " (" << age << ")" << std::endl;
    }
    
    ~Person() {
        std::cout << "Person destructor: " << name << std::endl;
    }
    
    void introduce() const {
        std::cout << "Hi, I'm " << name << ", " << age << " years old." << std::endl;
    }
    
    const std::string& getName() const { return name; }
    int getAge() const { return age; }
};

class Employee : public Person {
private:
    std::string department;
    double salary;
    
public:
    Employee(const std::string& name, int age, const std::string& dept, double sal)
        : Person(name, age), department(dept), salary(sal) {
        std::cout << "Employee constructor: " << getName() << " in " << department << std::endl;
    }
    
    ~Employee() {
        std::cout << "Employee destructor: " << getName() << std::endl;
    }
    
    void work() const {
        std::cout << getName() << " is working in " << department 
                  << " (salary: $" << salary << ")" << std::endl;
    }
};

// Template class for demonstration
template<typename T>
class Container {
private:
    std::vector<T> data;
    std::string name;
    
public:
    Container(const std::string& n) : name(n) {
        std::cout << "Container<" << typeid(T).name() << "> constructor: " << name << std::endl;
    }
    
    ~Container() {
        std::cout << "Container destructor: " << name << std::endl;
    }
    
    void add(const T& item) {
        data.push_back(item);
    }
    
    void display() const {
        std::cout << "Container " << name << " contains " << data.size() << " items:" << std::endl;
        for (const auto& item : data) {
            std::cout << "  " << item << std::endl;
        }
    }
};

// Function that takes unique_ptr by value
void processPersonByValue(std::unique_ptr<Person> person) {
    std::cout << "Processing person by value:" << std::endl;
    person->introduce();
    // person is automatically destroyed when function exits
}

// Function that takes unique_ptr by reference
void processPersonByReference(const std::unique_ptr<Person>& person) {
    std::cout << "Processing person by reference:" << std::endl;
    person->introduce();
    // person ownership remains with caller
}

int main() {
    std::cout << "=== C++14 STD::MAKE_UNIQUE DEMO ===" << std::endl;
    
    // 1. Basic make_unique usage
    std::cout << "\n1. Basic make_unique Usage:" << std::endl;
    
    // Create unique_ptr using make_unique (C++14)
    auto person1 = std::make_unique<Person>("Alice", 30);
    auto person2 = std::make_unique<Person>("Bob", 25);
    
    person1->introduce();
    person2->introduce();
    
    // 2. Advantages over raw new
    std::cout << "\n2. Advantages over raw new:" << std::endl;
    
    // C++11 way (less safe)
    std::unique_ptr<Person> person_old(new Person("Charlie", 35));
    
    // C++14 way (safer, exception-safe)
    auto person_new = std::make_unique<Person>("Diana", 28);
    
    std::cout << "Both created successfully, but make_unique is safer!" << std::endl;
    person_old->introduce();
    person_new->introduce();
    
    // 3. Exception safety demonstration
    std::cout << "\n3. Exception Safety:" << std::endl;
    
    // This could be problematic if an exception occurs between allocations:
    // some_function(std::unique_ptr<Person>(new Person("X", 1)), 
    //               std::unique_ptr<Person>(new Person("Y", 2)));
    
    // This is always safe:
    auto safe_person1 = std::make_unique<Person>("Safe1", 40);
    auto safe_person2 = std::make_unique<Person>("Safe2", 42);
    
    std::cout << "Exception-safe creation completed!" << std::endl;
    
    // 4. make_unique with different constructors
    std::cout << "\n4. make_unique with Different Constructors:" << std::endl;
    
    // Multi-parameter constructor
    auto employee = std::make_unique<Employee>("John", 30, "Engineering", 75000.0);
    employee->introduce();
    employee->work();
    
    // Template class with make_unique
    auto int_container = std::make_unique<Container<int>>("Numbers");
    int_container->add(1);
    int_container->add(2);
    int_container->add(3);
    int_container->display();
    
    auto string_container = std::make_unique<Container<std::string>>("Words");
    string_container->add("Hello");
    string_container->add("World");
    string_container->display();
    
    // 5. Arrays with make_unique
    std::cout << "\n5. Arrays with make_unique:" << std::endl;
    
    // Create array of 5 integers, all initialized to 0
    auto int_array = std::make_unique<int[]>(5);
    
    // Initialize array elements
    for (int i = 0; i < 5; ++i) {
        int_array[i] = i * i;
    }
    
    std::cout << "Array contents: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << int_array[i] << " ";
    }
    std::cout << std::endl;
    
    // Array of objects
    auto person_array = std::make_unique<Person[]>(3);
    // Note: This would require a default constructor for Person
    // We'll use a different approach:
    
    std::vector<std::unique_ptr<Person>> person_vector;
    person_vector.push_back(std::make_unique<Person>("Vector1", 20));
    person_vector.push_back(std::make_unique<Person>("Vector2", 21));
    person_vector.push_back(std::make_unique<Person>("Vector3", 22));
    
    std::cout << "Person vector contents:" << std::endl;
    for (const auto& person : person_vector) {
        person->introduce();
    }
    
    // 6. Perfect forwarding with make_unique
    std::cout << "\n6. Perfect Forwarding:" << std::endl;
    
    // make_unique perfectly forwards arguments to constructor
    std::string name = "Forwarded";
    int age = 33;
    
    // Arguments are perfectly forwarded
    auto forwarded_person = std::make_unique<Person>(name, age);
    auto rvalue_person = std::make_unique<Person>(std::string("RValue"), 44);
    
    forwarded_person->introduce();
    rvalue_person->introduce();
    
    // 7. Polymorphism with make_unique
    std::cout << "\n7. Polymorphism with unique_ptr:" << std::endl;
    
    std::vector<std::unique_ptr<Person>> people;
    
    // Base class pointers to derived objects
    people.push_back(std::make_unique<Person>("Base Person", 50));
    people.push_back(std::make_unique<Employee>("Employee Person", 45, "IT", 80000));
    
    std::cout << "Polymorphic behavior:" << std::endl;
    for (const auto& person : people) {
        person->introduce();
        
        // Dynamic cast to check if it's an Employee
        if (auto emp = dynamic_cast<Employee*>(person.get())) {
            emp->work();
        }
    }
    
    // 8. Moving unique_ptr
    std::cout << "\n8. Moving unique_ptr:" << std::endl;
    
    auto movable_person = std::make_unique<Person>("Movable", 27);
    std::cout << "Before move - person exists: " << (movable_person != nullptr) << std::endl;
    
    // Move ownership to function
    std::cout << "Moving to function..." << std::endl;
    processPersonByValue(std::move(movable_person));
    
    std::cout << "After move - person exists: " << (movable_person != nullptr) << std::endl;
    
    // 9. Passing by reference (no ownership transfer)
    std::cout << "\n9. Passing by Reference:" << std::endl;
    
    auto reference_person = std::make_unique<Person>("Reference", 29);
    std::cout << "Before reference call - person exists: " << (reference_person != nullptr) << std::endl;
    
    processPersonByReference(reference_person);
    
    std::cout << "After reference call - person exists: " << (reference_person != nullptr) << std::endl;
    reference_person->introduce();
    
    // 10. Factory pattern with make_unique
    std::cout << "\n10. Factory Pattern:" << std::endl;
    
    auto create_person = [](const std::string& type, const std::string& name, int age) -> std::unique_ptr<Person> {
        if (type == "person") {
            return std::make_unique<Person>(name, age);
        } else if (type == "employee") {
            return std::make_unique<Employee>(name, age, "General", 50000);
        }
        return nullptr;
    };
    
    auto factory_person = create_person("person", "Factory Person", 35);
    auto factory_employee = create_person("employee", "Factory Employee", 32);
    
    if (factory_person) factory_person->introduce();
    if (factory_employee) {
        factory_employee->introduce();
        static_cast<Employee*>(factory_employee.get())->work();
    }
    
    // 11. Custom deleters (though make_unique uses default delete)
    std::cout << "\n11. Memory Management Benefits:" << std::endl;
    
    {
        std::cout << "Creating scoped unique_ptrs..." << std::endl;
        auto scoped_person1 = std::make_unique<Person>("Scoped1", 60);
        auto scoped_person2 = std::make_unique<Person>("Scoped2", 61);
        
        scoped_person1->introduce();
        scoped_person2->introduce();
        
        std::cout << "Leaving scope - automatic cleanup will occur..." << std::endl;
    } // Destructors called automatically here
    
    std::cout << "Scope exited - memory automatically cleaned up!" << std::endl;
    
    // 12. Performance considerations
    std::cout << "\n12. Performance Considerations:" << std::endl;
    
    // make_unique performs single allocation (usually)
    auto start = std::chrono::high_resolution_clock::now();
    
    constexpr int COUNT = 10000;
    std::vector<std::unique_ptr<Person>> performance_test;
    performance_test.reserve(COUNT);
    
    for (int i = 0; i < COUNT; ++i) {
        performance_test.push_back(std::make_unique<Person>("Test" + std::to_string(i), i));
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Created " << COUNT << " unique_ptrs in " << duration.count() << " microseconds" << std::endl;
    std::cout << "Average: " << (duration.count() / static_cast<double>(COUNT)) << " microseconds per object" << std::endl;
    
    // 13. Comparison with shared_ptr
    std::cout << "\n13. Comparison with shared_ptr:" << std::endl;
    
    // unique_ptr - exclusive ownership, no reference counting
    auto unique_person = std::make_unique<Person>("Unique Owner", 25);
    std::cout << "unique_ptr size: " << sizeof(unique_person) << " bytes" << std::endl;
    
    // shared_ptr - shared ownership, reference counting
    auto shared_person = std::make_shared<Person>("Shared Owner", 26);
    std::cout << "shared_ptr size: " << sizeof(shared_person) << " bytes" << std::endl;
    std::cout << "shared_ptr use count: " << shared_person.use_count() << std::endl;
    
    std::cout << "\n=== MAKE_UNIQUE BENEFITS SUMMARY ===" << std::endl;
    std::cout << "✅ Exception safety - no memory leaks if constructor throws" << std::endl;
    std::cout << "✅ Less typing - auto type deduction" << std::endl;
    std::cout << "✅ Cannot accidentally use raw pointer" << std::endl;
    std::cout << "✅ Perfect forwarding of constructor arguments" << std::endl;
    std::cout << "✅ Consistent with make_shared style" << std::endl;
    std::cout << "✅ Single allocation (no control block like shared_ptr)" << std::endl;
    std::cout << "✅ Zero overhead - same as manual unique_ptr construction" << std::endl;
    std::cout << "⚠️  Added in C++14 (not available in C++11)" << std::endl;
    std::cout << "⚠️  Cannot be used with custom deleters (use unique_ptr constructor)" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++14 -Wall -Wextra -o make_unique_demo make_unique_demo.cpp
./make_unique_demo

C++14 std::make_unique:
- Factory function for creating std::unique_ptr objects
- Safer alternative to using 'new' directly
- Exception-safe construction
- Perfect forwarding of arguments

Key Features:
1. Exception Safety: If constructor throws, no memory leak occurs
2. Type Deduction: Auto deduction eliminates typing unique_ptr<Type>
3. Perfect Forwarding: Arguments passed exactly as provided
4. Consistent API: Similar to std::make_shared

Syntax:
auto ptr = std::make_unique<Type>(args...);        // Single object
auto arr = std::make_unique<Type[]>(size);         // Array

Benefits over raw new:
- Exception safe: make_unique guarantees no leaks
- More concise: auto type deduction
- Harder to misuse: no raw pointer exposure
- Consistent: matches make_shared pattern

Performance:
- Same runtime performance as manual construction
- Single allocation (no control block overhead)
- Perfect forwarding avoids unnecessary copies

Use Cases:
- Factory functions
- RAII resource management
- Polymorphic object creation
- Exception-safe code
- Modern C++ best practices
*/
