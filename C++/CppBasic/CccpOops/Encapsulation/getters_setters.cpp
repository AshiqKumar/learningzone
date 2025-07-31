// getters_setters.cpp - Demonstrates getter and setter methods in C++
// Compile: g++ -std=c++17 -Wall -Wextra getters_setters.cpp -o getters_setters

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

// 1. Person Class - Basic Getters and Setters
class Person {
private:
    std::string firstName;
    std::string lastName;
    int age;
    std::string email;
    
public:
    // Constructor
    Person(const std::string& fName, const std::string& lName, 
           int personAge, const std::string& emailAddress)
        : firstName(fName), lastName(lName), age(personAge), email(emailAddress) {
        
        // Validate during construction
        setAge(personAge);
        setEmail(emailAddress);
    }
    
    // Getters (Accessors) - const methods
    std::string getFirstName() const {
        return firstName;
    }
    
    std::string getLastName() const {
        return lastName;
    }
    
    int getAge() const {
        return age;
    }
    
    std::string getEmail() const {
        return email;
    }
    
    // Computed getter - full name
    std::string getFullName() const {
        return firstName + " " + lastName;
    }
    
    // Computed getter - adult status
    bool isAdult() const {
        return age >= 18;
    }
    
    // Setters (Mutators) - with validation
    void setFirstName(const std::string& fName) {
        if (!fName.empty() && fName.length() <= 50) {
            firstName = fName;
        } else {
            throw std::invalid_argument("First name must be 1-50 characters");
        }
    }
    
    void setLastName(const std::string& lName) {
        if (!lName.empty() && lName.length() <= 50) {
            lastName = lName;
        } else {
            throw std::invalid_argument("Last name must be 1-50 characters");
        }
    }
    
    void setAge(int newAge) {
        if (newAge >= 0 && newAge <= 150) {
            age = newAge;
        } else {
            throw std::invalid_argument("Age must be between 0 and 150");
        }
    }
    
    void setEmail(const std::string& newEmail) {
        // Simple email validation
        if (newEmail.find('@') != std::string::npos && 
            newEmail.find('.') != std::string::npos) {
            email = newEmail;
        } else {
            throw std::invalid_argument("Invalid email format");
        }
    }
    
    void displayInfo() const {
        std::cout << "Person: " << getFullName() << std::endl;
        std::cout << "  Age: " << age << " (" << (isAdult() ? "Adult" : "Minor") << ")" << std::endl;
        std::cout << "  Email: " << email << std::endl;
    }
};

// 2. Temperature Class - Multiple Representations
class Temperature {
private:
    double celsius;
    
public:
    // Constructors for different scales
    Temperature(double temp = 0.0) : celsius(temp) {}
    
    static Temperature fromFahrenheit(double fahrenheit) {
        return Temperature((fahrenheit - 32.0) * 5.0 / 9.0);
    }
    
    static Temperature fromKelvin(double kelvin) {
        return Temperature(kelvin - 273.15);
    }
    
    // Getters for different temperature scales
    double getCelsius() const {
        return celsius;
    }
    
    double getFahrenheit() const {
        return celsius * 9.0 / 5.0 + 32.0;
    }
    
    double getKelvin() const {
        return celsius + 273.15;
    }
    
    // Setters for different temperature scales
    void setCelsius(double temp) {
        if (temp >= -273.15) {  // Absolute zero check
            celsius = temp;
        } else {
            throw std::invalid_argument("Temperature cannot be below absolute zero");
        }
    }
    
    void setFahrenheit(double fahrenheit) {
        setCelsius((fahrenheit - 32.0) * 5.0 / 9.0);
    }
    
    void setKelvin(double kelvin) {
        setCelsius(kelvin - 273.15);
    }
    
    // Status getters
    bool isFreezing() const {
        return celsius <= 0.0;
    }
    
    bool isBoiling() const {
        return celsius >= 100.0;
    }
    
    std::string getPhase() const {
        if (celsius < 0.0) return "Ice";
        else if (celsius < 100.0) return "Liquid";
        else return "Steam";
    }
    
    void displayInfo() const {
        std::cout << "Temperature Information:" << std::endl;
        std::cout << "  Celsius: " << getCelsius() << "°C" << std::endl;
        std::cout << "  Fahrenheit: " << getFahrenheit() << "°F" << std::endl;
        std::cout << "  Kelvin: " << getKelvin() << "K" << std::endl;
        std::cout << "  Phase: " << getPhase() << std::endl;
    }
};

// 3. Book Class - Complex Object with Nested Data
class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    int publicationYear;
    double price;
    int pageCount;
    bool isAvailable;
    std::vector<std::string> categories;
    
public:
    Book(const std::string& bookTitle, const std::string& bookAuthor,
         const std::string& bookIsbn, int year, double bookPrice, int pages)
        : title(bookTitle), author(bookAuthor), isbn(bookIsbn),
          publicationYear(year), price(bookPrice), pageCount(pages), isAvailable(true) {}
    
    // Basic getters
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getIsbn() const { return isbn; }
    int getPublicationYear() const { return publicationYear; }
    double getPrice() const { return price; }
    int getPageCount() const { return pageCount; }
    bool getIsAvailable() const { return isAvailable; }
    
    // Categories getter - returns copy to prevent external modification
    std::vector<std::string> getCategories() const {
        return categories;
    }
    
    // Computed getters
    int getAge() const {
        return 2024 - publicationYear;  // Assuming current year is 2024
    }
    
    double getPricePerPage() const {
        return pageCount > 0 ? price / pageCount : 0.0;
    }
    
    bool isClassic() const {
        return getAge() >= 50;
    }
    
    // Basic setters with validation
    void setTitle(const std::string& newTitle) {
        if (!newTitle.empty()) {
            title = newTitle;
        } else {
            throw std::invalid_argument("Title cannot be empty");
        }
    }
    
    void setAuthor(const std::string& newAuthor) {
        if (!newAuthor.empty()) {
            author = newAuthor;
        } else {
            throw std::invalid_argument("Author cannot be empty");
        }
    }
    
    void setPrice(double newPrice) {
        if (newPrice >= 0.0) {
            price = newPrice;
        } else {
            throw std::invalid_argument("Price cannot be negative");
        }
    }
    
    void setAvailability(bool available) {
        isAvailable = available;
    }
    
    // Collection manipulation methods
    void addCategory(const std::string& category) {
        if (std::find(categories.begin(), categories.end(), category) == categories.end()) {
            categories.push_back(category);
        }
    }
    
    void removeCategory(const std::string& category) {
        categories.erase(
            std::remove(categories.begin(), categories.end(), category),
            categories.end()
        );
    }
    
    bool hasCategory(const std::string& category) const {
        return std::find(categories.begin(), categories.end(), category) != categories.end();
    }
    
    size_t getCategoryCount() const {
        return categories.size();
    }
    
    void clearCategories() {
        categories.clear();
    }
    
    void displayInfo() const {
        std::cout << "Book Information:" << std::endl;
        std::cout << "  Title: " << title << std::endl;
        std::cout << "  Author: " << author << std::endl;
        std::cout << "  ISBN: " << isbn << std::endl;
        std::cout << "  Year: " << publicationYear << " (Age: " << getAge() << " years)" << std::endl;
        std::cout << "  Price: $" << price << " (" << getPricePerPage() << " per page)" << std::endl;
        std::cout << "  Pages: " << pageCount << std::endl;
        std::cout << "  Available: " << (isAvailable ? "Yes" : "No") << std::endl;
        std::cout << "  Classic: " << (isClassic() ? "Yes" : "No") << std::endl;
        
        if (!categories.empty()) {
            std::cout << "  Categories: ";
            for (size_t i = 0; i < categories.size(); ++i) {
                std::cout << categories[i];
                if (i < categories.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
};

// 4. Property Pattern Implementation
template<typename T>
class Property {
private:
    T value;
    std::function<bool(const T&)> validator;
    std::function<void(const T&)> onChange;
    
public:
    Property(const T& initialValue = T{}) : value(initialValue) {}
    
    // Set validator function
    void setValidator(std::function<bool(const T&)> validatorFunc) {
        validator = validatorFunc;
    }
    
    // Set onChange callback
    void setOnChange(std::function<void(const T&)> onChangeFunc) {
        onChange = onChangeFunc;
    }
    
    // Assignment operator (setter)
    Property& operator=(const T& newValue) {
        if (validator && !validator(newValue)) {
            throw std::invalid_argument("Value failed validation");
        }
        
        T oldValue = value;
        value = newValue;
        
        if (onChange && oldValue != value) {
            onChange(value);
        }
        
        return *this;
    }
    
    // Conversion operator (getter)
    operator const T&() const {
        return value;
    }
    
    // Explicit getter
    const T& get() const {
        return value;
    }
};

// 5. SmartPerson Class using Property Pattern
class SmartPerson {
private:
    Property<std::string> name;
    Property<int> age;
    Property<std::string> email;
    
public:
    SmartPerson(const std::string& personName, int personAge, const std::string& personEmail) {
        // Set up validators
        name.setValidator([](const std::string& n) { 
            return !n.empty() && n.length() <= 50; 
        });
        
        age.setValidator([](int a) { 
            return a >= 0 && a <= 150; 
        });
        
        email.setValidator([](const std::string& e) {
            return e.find('@') != std::string::npos && e.find('.') != std::string::npos;
        });
        
        // Set up change notifications
        name.setOnChange([](const std::string& newName) {
            std::cout << "Name changed to: " << newName << std::endl;
        });
        
        age.setOnChange([](int newAge) {
            std::cout << "Age changed to: " << newAge << std::endl;
        });
        
        email.setOnChange([](const std::string& newEmail) {
            std::cout << "Email changed to: " << newEmail << std::endl;
        });
        
        // Initialize values
        name = personName;
        age = personAge;
        email = personEmail;
    }
    
    // Property accessors
    Property<std::string>& getName() { return name; }
    const Property<std::string>& getName() const { return name; }
    
    Property<int>& getAge() { return age; }
    const Property<int>& getAge() const { return age; }
    
    Property<std::string>& getEmail() { return email; }
    const Property<std::string>& getEmail() const { return email; }
    
    void displayInfo() const {
        std::cout << "Smart Person: " << name.get() << std::endl;
        std::cout << "  Age: " << age.get() << std::endl;
        std::cout << "  Email: " << email.get() << std::endl;
    }
};

// Demonstration functions
void demonstrateBasicGettersSetters() {
    std::cout << "\n=== BASIC GETTERS AND SETTERS ===" << std::endl;
    
    try {
        Person person("John", "Doe", 25, "john.doe@email.com");
        person.displayInfo();
        
        std::cout << "\nModifying person data:" << std::endl;
        person.setAge(30);
        person.setEmail("john.doe@newemail.com");
        person.displayInfo();
        
        std::cout << "\nTesting validation:" << std::endl;
        try {
            person.setAge(-5);  // Should throw exception
        } catch (const std::exception& e) {
            std::cout << "Age validation error: " << e.what() << std::endl;
        }
        
        try {
            person.setEmail("invalid-email");  // Should throw exception
        } catch (const std::exception& e) {
            std::cout << "Email validation error: " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void demonstrateTemperatureGettersSetters() {
    std::cout << "\n=== TEMPERATURE GETTERS AND SETTERS ===" << std::endl;
    
    Temperature temp1(25.0);  // 25°C
    temp1.displayInfo();
    
    std::cout << "\nCreating temperature from Fahrenheit:" << std::endl;
    Temperature temp2 = Temperature::fromFahrenheit(98.6);  // Body temperature
    temp2.displayInfo();
    
    std::cout << "\nModifying temperature:" << std::endl;
    temp1.setFahrenheit(212.0);  // Boiling point
    temp1.displayInfo();
    
    std::cout << "\nTesting absolute zero validation:" << std::endl;
    try {
        temp1.setCelsius(-300.0);  // Below absolute zero
    } catch (const std::exception& e) {
        std::cout << "Temperature validation error: " << e.what() << std::endl;
    }
}

void demonstrateBookGettersSetters() {
    std::cout << "\n=== BOOK GETTERS AND SETTERS ===" << std::endl;
    
    Book book("The Great Gatsby", "F. Scott Fitzgerald", "978-0-7432-7356-5", 1925, 12.99, 180);
    
    // Add categories
    book.addCategory("Fiction");
    book.addCategory("Classic Literature");
    book.addCategory("American Literature");
    
    book.displayInfo();
    
    std::cout << "\nModifying book properties:" << std::endl;
    book.setPrice(15.99);
    book.setAvailability(false);
    book.addCategory("Romance");
    
    std::cout << "\nChecking categories:" << std::endl;
    std::cout << "Has Fiction category: " << (book.hasCategory("Fiction") ? "Yes" : "No") << std::endl;
    std::cout << "Has Horror category: " << (book.hasCategory("Horror") ? "Yes" : "No") << std::endl;
    std::cout << "Total categories: " << book.getCategoryCount() << std::endl;
    
    book.displayInfo();
    
    std::cout << "\nRemoving a category:" << std::endl;
    book.removeCategory("Romance");
    book.displayInfo();
}

void demonstratePropertyPattern() {
    std::cout << "\n=== PROPERTY PATTERN ===" << std::endl;
    
    try {
        SmartPerson person("Alice Smith", 28, "alice@example.com");
        person.displayInfo();
        
        std::cout << "\nModifying properties:" << std::endl;
        person.getName() = "Alice Johnson";  // Uses property setter
        person.getAge() = 29;
        person.getEmail() = "alice.johnson@example.com";
        
        std::cout << "\nAccessing properties:" << std::endl;
        std::cout << "Name: " << person.getName().get() << std::endl;
        std::cout << "Age: " << static_cast<int>(person.getAge()) << std::endl;
        
        std::cout << "\nTesting property validation:" << std::endl;
        try {
            person.getAge() = -10;  // Should trigger validation
        } catch (const std::exception& e) {
            std::cout << "Property validation error: " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void demonstrateGetterSetterBestPractices() {
    std::cout << "\n=== GETTER/SETTER BEST PRACTICES ===" << std::endl;
    
    std::cout << "1. Const Correctness:" << std::endl;
    std::cout << "   - Getters should be const methods" << std::endl;
    std::cout << "   - Prevents modification of object state during read access" << std::endl;
    
    std::cout << "\n2. Validation in Setters:" << std::endl;
    std::cout << "   - Always validate input data" << std::endl;
    std::cout << "   - Throw meaningful exceptions for invalid data" << std::endl;
    
    std::cout << "\n3. Return Types:" << std::endl;
    std::cout << "   - Return by value for primitive types" << std::endl;
    std::cout << "   - Return by const reference for complex types" << std::endl;
    std::cout << "   - Avoid returning non-const references to private members" << std::endl;
    
    std::cout << "\n4. Computed Properties:" << std::endl;
    std::cout << "   - Calculate derived values in getters" << std::endl;
    std::cout << "   - Keep computation lightweight" << std::endl;
    
    std::cout << "\n5. Naming Conventions:" << std::endl;
    std::cout << "   - Use get/set prefixes consistently" << std::endl;
    std::cout << "   - Use meaningful, descriptive names" << std::endl;
}

int main() {
    std::cout << "=== ENCAPSULATION: GETTERS AND SETTERS ===" << std::endl;
    std::cout << "Getter and setter methods provide controlled access to private data" << std::endl;
    std::cout << "while enabling validation, computation, and maintaining encapsulation." << std::endl;
    
    demonstrateBasicGettersSetters();
    demonstrateTemperatureGettersSetters();
    demonstrateBookGettersSetters();
    demonstratePropertyPattern();
    demonstrateGetterSetterBestPractices();
    
    std::cout << "\n=== KEY CONCEPTS ===" << std::endl;
    std::cout << "1. Getters provide read access to private data" << std::endl;
    std::cout << "2. Setters provide write access with validation" << std::endl;
    std::cout << "3. Const getters guarantee no object modification" << std::endl;
    std::cout << "4. Computed getters derive values from existing data" << std::endl;
    std::cout << "5. Property pattern combines getter/setter functionality" << std::endl;
    std::cout << "6. Validation in setters ensures data integrity" << std::endl;
    
    return 0;
}

/* Expected Output:
=== ENCAPSULATION: GETTERS AND SETTERS ===
Getter and setter methods provide controlled access to private data
while enabling validation, computation, and maintaining encapsulation.

=== BASIC GETTERS AND SETTERS ===
Person: John Doe
  Age: 25 (Adult)
  Email: john.doe@email.com

Modifying person data:
Person: John Doe
  Age: 30 (Adult)
  Email: john.doe@newemail.com

Testing validation:
Age validation error: Age must be between 0 and 150
Email validation error: Invalid email format

=== TEMPERATURE GETTERS AND SETTERS ===
Temperature Information:
  Celsius: 25°C
  Fahrenheit: 77°F
  Kelvin: 298.15K
  Phase: Liquid

Creating temperature from Fahrenheit:
Temperature Information:
  Celsius: 37°C
  Fahrenheit: 98.6°F
  Kelvin: 310.15K
  Phase: Liquid

Modifying temperature:
Temperature Information:
  Celsius: 100°C
  Fahrenheit: 212°F
  Kelvin: 373.15K
  Phase: Steam

Testing absolute zero validation:
Temperature validation error: Temperature cannot be below absolute zero

=== BOOK GETTERS AND SETTERS ===
Book Information:
  Title: The Great Gatsby
  Author: F. Scott Fitzgerald
  ISBN: 978-0-7432-7356-5
  Year: 1925 (Age: 99 years)
  Price: $12.99 (0.0721611 per page)
  Pages: 180
  Available: Yes
  Classic: Yes
  Categories: Fiction, Classic Literature, American Literature

Modifying book properties:

Checking categories:
Has Fiction category: Yes
Has Horror category: No
Total categories: 4

Book Information:
  Title: The Great Gatsby
  Author: F. Scott Fitzgerald
  ISBN: 978-0-7432-7356-5
  Year: 1925 (Age: 99 years)
  Price: $15.99 (0.0888333 per page)
  Pages: 180
  Available: No
  Classic: Yes
  Categories: Fiction, Classic Literature, American Literature, Romance

Removing a category:
Book Information:
  Title: The Great Gatsby
  Author: F. Scott Fitzgerald
  ISBN: 978-0-7432-7356-5
  Year: 1925 (Age: 99 years)
  Price: $15.99 (0.0888333 per page)
  Pages: 180
  Available: No
  Classic: Yes
  Categories: Fiction, Classic Literature, American Literature

=== PROPERTY PATTERN ===
Name changed to: Alice Smith
Age changed to: 28
Email changed to: alice@example.com
Smart Person: Alice Smith
  Age: 28
  Email: alice@example.com

Modifying properties:
Name changed to: Alice Johnson
Age changed to: 29
Email changed to: alice.johnson@example.com

Accessing properties:
Name: Alice Johnson
Age: 29

Testing property validation:
Property validation error: Value failed validation

=== GETTER/SETTER BEST PRACTICES ===
1. Const Correctness:
   - Getters should be const methods
   - Prevents modification of object state during read access

2. Validation in Setters:
   - Always validate input data
   - Throw meaningful exceptions for invalid data

3. Return Types:
   - Return by value for primitive types
   - Return by const reference for complex types
   - Avoid returning non-const references to private members

4. Computed Properties:
   - Calculate derived values in getters
   - Keep computation lightweight

5. Naming Conventions:
   - Use get/set prefixes consistently
   - Use meaningful, descriptive names

=== KEY CONCEPTS ===
1. Getters provide read access to private data
2. Setters provide write access with validation
3. Const getters guarantee no object modification
4. Computed getters derive values from existing data
5. Property pattern combines getter/setter functionality
6. Validation in setters ensures data integrity
*/
