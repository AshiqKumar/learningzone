// C++11 Smart Pointers - Memory Management Made Safe
// Compile: g++ -std=c++11 -o smart_ptr_demo smart_pointers_demo.cpp
// Run: ./smart_ptr_demo

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Example class for demonstration
class Person {
private:
    std::string name_;
    int age_;
    
public:
    Person(const std::string& name, int age) : name_(name), age_(age) {
        std::cout << "Person(" << name_ << ", " << age_ << ") created" << std::endl;
    }
    
    ~Person() {
        std::cout << "Person(" << name_ << ", " << age_ << ") destroyed" << std::endl;
    }
    
    void introduce() const {
        std::cout << "Hi, I'm " << name_ << " and I'm " << age_ << " years old." << std::endl;
    }
    
    const std::string& getName() const { return name_; }
    int getAge() const { return age_; }
};

// Function that demonstrates unique_ptr parameter passing
void process_person(std::unique_ptr<Person> person) {
    std::cout << "Processing person in function:" << std::endl;
    person->introduce();
    // person is automatically destroyed when function ends
}

// Function that demonstrates shared_ptr sharing
std::shared_ptr<Person> create_shared_person(const std::string& name, int age) {
    return std::make_shared<Person>(name, age);
}

int main() {
    std::cout << "=== C++11 SMART POINTERS DEMO ===" << std::endl;
    
    // 1. unique_ptr - Exclusive ownership
    std::cout << "\n1. unique_ptr - Exclusive Ownership:" << std::endl;
    
    // Create unique_ptr
    std::unique_ptr<Person> unique_person = std::make_unique<Person>("Alice", 25);
    // Note: make_unique is C++14, for C++11 use: std::unique_ptr<Person>(new Person("Alice", 25))
    
    // In C++11, use this syntax instead:
    std::unique_ptr<Person> unique_person_cpp11(new Person("Bob", 30));
    
    unique_person_cpp11->introduce();
    
    // Access through unique_ptr
    std::cout << "Name: " << unique_person_cpp11->getName() << std::endl;
    std::cout << "Age: " << (*unique_person_cpp11).getAge() << std::endl;
    
    // Transfer ownership with std::move
    std::cout << "\nTransferring ownership:" << std::endl;
    std::unique_ptr<Person> another_unique = std::move(unique_person_cpp11);
    
    if (!unique_person_cpp11) {
        std::cout << "Original unique_ptr is now null" << std::endl;
    }
    
    if (another_unique) {
        std::cout << "New unique_ptr owns the object:" << std::endl;
        another_unique->introduce();
    }
    
    // unique_ptr with arrays
    std::cout << "\nunique_ptr with arrays:" << std::endl;
    std::unique_ptr<int[]> unique_array(new int[5]);
    for (int i = 0; i < 5; ++i) {
        unique_array[i] = i * 10;
    }
    
    std::cout << "Array elements: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << unique_array[i] << " ";
    }
    std::cout << std::endl;
    
    // 2. shared_ptr - Shared ownership
    std::cout << "\n2. shared_ptr - Shared Ownership:" << std::endl;
    
    std::shared_ptr<Person> shared_person1 = std::make_shared<Person>("Charlie", 35);
    std::cout << "Reference count: " << shared_person1.use_count() << std::endl;
    
    // Create another shared_ptr pointing to the same object
    std::shared_ptr<Person> shared_person2 = shared_person1;
    std::cout << "Reference count after copying: " << shared_person1.use_count() << std::endl;
    
    {
        std::shared_ptr<Person> shared_person3 = shared_person1;
        std::cout << "Reference count in inner scope: " << shared_person1.use_count() << std::endl;
        shared_person3->introduce();
    }  // shared_person3 goes out of scope
    
    std::cout << "Reference count after inner scope: " << shared_person1.use_count() << std::endl;
    
    // shared_ptr in containers
    std::cout << "\nshared_ptr in containers:" << std::endl;
    std::vector<std::shared_ptr<Person>> people;
    
    auto david = create_shared_person("David", 28);
    auto eve = create_shared_person("Eve", 32);
    
    people.push_back(david);
    people.push_back(eve);
    people.push_back(david);  // Same person shared multiple times
    
    std::cout << "David's reference count: " << david.use_count() << std::endl;
    std::cout << "Eve's reference count: " << eve.use_count() << std::endl;
    
    std::cout << "People in vector:" << std::endl;
    for (const auto& person : people) {
        person->introduce();
    }
    
    // 3. weak_ptr - Breaking circular references
    std::cout << "\n3. weak_ptr - Breaking Circular References:" << std::endl;
    
    class Parent;
    class Child;
    
    class Parent {
    public:
        std::shared_ptr<Child> child;
        std::string name;
        
        Parent(const std::string& n) : name(n) {
            std::cout << "Parent " << name << " created" << std::endl;
        }
        
        ~Parent() {
            std::cout << "Parent " << name << " destroyed" << std::endl;
        }
    };
    
    class Child {
    public:
        std::weak_ptr<Parent> parent;  // weak_ptr to break circular reference
        std::string name;
        
        Child(const std::string& n) : name(n) {
            std::cout << "Child " << name << " created" << std::endl;
        }
        
        ~Child() {
            std::cout << "Child " << name << " destroyed" << std::endl;
        }
        
        void visit_parent() {
            if (auto p = parent.lock()) {  // Convert weak_ptr to shared_ptr
                std::cout << "Child " << name << " visiting parent " << p->name << std::endl;
            } else {
                std::cout << "Parent is no longer available" << std::endl;
            }
        }
    };
    
    {
        auto parent = std::make_shared<Parent>("John");
        auto child = std::make_shared<Child>("Jane");
        
        parent->child = child;
        child->parent = parent;  // weak_ptr assignment
        
        std::cout << "Parent reference count: " << parent.use_count() << std::endl;
        
        child->visit_parent();
    }  // Both parent and child should be destroyed here
    
    // 4. Custom deleters
    std::cout << "\n4. Custom Deleters:" << std::endl;
    
    // Custom deleter for unique_ptr
    auto custom_deleter = [](Person* p) {
        std::cout << "Custom deleter called for " << p->getName() << std::endl;
        delete p;
    };
    
    std::unique_ptr<Person, decltype(custom_deleter)> custom_unique(
        new Person("Frank", 40), custom_deleter);
    
    custom_unique->introduce();
    
    // Custom deleter for shared_ptr
    std::shared_ptr<Person> custom_shared(
        new Person("Grace", 45),
        [](Person* p) {
            std::cout << "Shared custom deleter called for " << p->getName() << std::endl;
            delete p;
        }
    );
    
    custom_shared->introduce();
    
    // 5. Converting between smart pointers
    std::cout << "\n5. Converting Between Smart Pointers:" << std::endl;
    
    // unique_ptr to shared_ptr
    std::unique_ptr<Person> unique_for_conversion(new Person("Henry", 50));
    std::shared_ptr<Person> converted_shared = std::move(unique_for_conversion);
    
    std::cout << "Converted to shared_ptr:" << std::endl;
    converted_shared->introduce();
    std::cout << "Reference count: " << converted_shared.use_count() << std::endl;
    
    // 6. Reset and release
    std::cout << "\n6. Reset and Release Operations:" << std::endl;
    
    std::unique_ptr<Person> resettable_unique(new Person("Ivy", 27));
    resettable_unique->introduce();
    
    // Reset to nullptr
    resettable_unique.reset();
    if (!resettable_unique) {
        std::cout << "unique_ptr is now null after reset" << std::endl;
    }
    
    // Reset with new object
    resettable_unique.reset(new Person("Jack", 33));
    resettable_unique->introduce();
    
    // Release ownership (dangerous - manual management needed)
    Person* raw_ptr = resettable_unique.release();
    if (!resettable_unique) {
        std::cout << "unique_ptr released ownership" << std::endl;
    }
    
    // Now we must manually delete
    std::cout << "Manually managing released pointer:" << std::endl;
    raw_ptr->introduce();
    delete raw_ptr;  // Manual cleanup required
    
    // 7. Performance comparison
    std::cout << "\n7. Performance Considerations:" << std::endl;
    
    std::cout << "Creating objects with different pointer types:" << std::endl;
    
    // Raw pointer (fastest, but dangerous)
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        Person* raw = new Person("Test" + std::to_string(i), 20);
        delete raw;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Raw pointers: Fast but dangerous (manual management)" << std::endl;
    
    // unique_ptr (slight overhead, but safe)
    std::cout << "unique_ptr: Minimal overhead, excellent safety" << std::endl;
    
    // shared_ptr (more overhead due to reference counting)
    std::cout << "shared_ptr: Higher overhead, but enables sharing" << std::endl;
    
    std::cout << "\n=== SMART POINTERS BENEFITS ===" << std::endl;
    std::cout << "✅ Automatic memory management" << std::endl;
    std::cout << "✅ Exception safety" << std::endl;
    std::cout << "✅ Clear ownership semantics" << std::endl;
    std::cout << "✅ Prevents memory leaks" << std::endl;
    std::cout << "✅ Prevents double deletion" << std::endl;
    std::cout << "✅ RAII (Resource Acquisition Is Initialization)" << std::endl;
    
    std::cout << "\n=== USAGE GUIDELINES ===" << std::endl;
    std::cout << "🎯 Use unique_ptr by default (exclusive ownership)" << std::endl;
    std::cout << "🎯 Use shared_ptr when you need shared ownership" << std::endl;
    std::cout << "🎯 Use weak_ptr to break circular references" << std::endl;
    std::cout << "🎯 Prefer make_shared/make_unique when possible" << std::endl;
    std::cout << "⚠️  Avoid mixing smart pointers with raw pointers" << std::endl;
    std::cout << "⚠️  Be careful with circular references" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -o smart_ptr_demo smart_pointers_demo.cpp
./smart_ptr_demo

Smart Pointer Types in C++11:
1. unique_ptr<T> - Exclusive ownership, move-only
2. shared_ptr<T> - Shared ownership with reference counting
3. weak_ptr<T> - Non-owning observer, breaks circular references

Key Benefits:
- Automatic cleanup (RAII)
- Exception safety
- Clear ownership semantics
- Prevents memory leaks and double deletion

Note: make_unique is C++14, so in C++11 use:
std::unique_ptr<T>(new T(...)) instead of std::make_unique<T>(...)
*/
