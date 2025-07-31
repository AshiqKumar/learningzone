// basic_encapsulation.cpp - Demonstrates basic encapsulation concepts in C++
// Compile: g++ -std=c++17 -Wall -Wextra basic_encapsulation.cpp -o basic_encapsulation

#include <iostream>
#include <string>
#include <vector>

// 1. Basic Class with Private Data Members
class Student {
private:
    // Private data members - hidden from external access
    std::string name;
    int age;
    double gpa;
    std::string studentId;
    
public:
    // Constructor - public interface for object creation
    Student(const std::string& studentName, int studentAge, 
            const std::string& id, double initialGpa = 0.0) 
        : name(studentName), age(studentAge), gpa(initialGpa), studentId(id) {
        std::cout << "Student " << name << " created with ID: " << studentId << std::endl;
    }
    
    // Public methods to access private data (Controlled Access)
    std::string getName() const {
        return name;
    }
    
    int getAge() const {
        return age;
    }
    
    double getGPA() const {
        return gpa;
    }
    
    std::string getStudentId() const {
        return studentId;
    }
    
    // Public methods to modify private data with validation
    void setAge(int newAge) {
        if (newAge >= 0 && newAge <= 150) {
            age = newAge;
            std::cout << "Age updated to: " << age << std::endl;
        } else {
            std::cout << "Invalid age! Age must be between 0 and 150." << std::endl;
        }
    }
    
    void setGPA(double newGpa) {
        if (newGpa >= 0.0 && newGpa <= 4.0) {
            gpa = newGpa;
            std::cout << "GPA updated to: " << gpa << std::endl;
        } else {
            std::cout << "Invalid GPA! GPA must be between 0.0 and 4.0." << std::endl;
        }
    }
    
    // Public method that uses private data
    void displayInfo() const {
        std::cout << "Student Information:" << std::endl;
        std::cout << "  Name: " << name << std::endl;
        std::cout << "  Age: " << age << std::endl;
        std::cout << "  Student ID: " << studentId << std::endl;
        std::cout << "  GPA: " << gpa << std::endl;
        std::cout << "  Status: " << getAcademicStatus() << std::endl;
    }
    
    // Public method that provides abstraction
    std::string getAcademicStatus() const {
        if (gpa >= 3.5) return "Excellent";
        else if (gpa >= 3.0) return "Good";
        else if (gpa >= 2.0) return "Average";
        else return "Needs Improvement";
    }
};

// 2. Bank Account Class - Strong Encapsulation Example
class BankAccount {
private:
    std::string accountNumber;
    std::string ownerName;
    double balance;
    std::string accountType;
    static int nextAccountId;  // Static private member
    
    // Private helper method
    bool isValidTransaction(double amount) const {
        return amount > 0 && amount <= 10000; // Max transaction limit
    }
    
    // Private method to generate account number
    std::string generateAccountNumber() {
        return "ACC" + std::to_string(++nextAccountId);
    }
    
public:
    // Constructor
    BankAccount(const std::string& owner, const std::string& type = "Savings", 
                double initialDeposit = 0.0) 
        : ownerName(owner), balance(0.0), accountType(type) {
        
        accountNumber = generateAccountNumber();
        
        if (initialDeposit > 0) {
            deposit(initialDeposit);
        }
        
        std::cout << "Bank account created for " << ownerName 
                  << " with account number: " << accountNumber << std::endl;
    }
    
    // Read-only access to account information
    std::string getAccountNumber() const {
        return accountNumber;
    }
    
    std::string getOwnerName() const {
        return ownerName;
    }
    
    double getBalance() const {
        return balance;
    }
    
    std::string getAccountType() const {
        return accountType;
    }
    
    // Controlled operations on balance
    bool deposit(double amount) {
        if (!isValidTransaction(amount)) {
            std::cout << "Invalid deposit amount: " << amount << std::endl;
            return false;
        }
        
        balance += amount;
        std::cout << "Deposited $" << amount 
                  << ". New balance: $" << balance << std::endl;
        return true;
    }
    
    bool withdraw(double amount) {
        if (!isValidTransaction(amount)) {
            std::cout << "Invalid withdrawal amount: " << amount << std::endl;
            return false;
        }
        
        if (amount > balance) {
            std::cout << "Insufficient funds! Current balance: $" << balance << std::endl;
            return false;
        }
        
        balance -= amount;
        std::cout << "Withdrew $" << amount 
                  << ". New balance: $" << balance << std::endl;
        return true;
    }
    
    // Transfer method using encapsulated operations
    bool transferTo(BankAccount& targetAccount, double amount) {
        std::cout << "Initiating transfer of $" << amount 
                  << " from " << accountNumber 
                  << " to " << targetAccount.getAccountNumber() << std::endl;
        
        if (withdraw(amount)) {
            if (targetAccount.deposit(amount)) {
                std::cout << "Transfer successful!" << std::endl;
                return true;
            } else {
                // Rollback - deposit back to source account
                deposit(amount);
                std::cout << "Transfer failed - deposit to target failed" << std::endl;
                return false;
            }
        }
        
        std::cout << "Transfer failed - withdrawal from source failed" << std::endl;
        return false;
    }
    
    void displayAccountInfo() const {
        std::cout << "Account Information:" << std::endl;
        std::cout << "  Account Number: " << accountNumber << std::endl;
        std::cout << "  Owner: " << ownerName << std::endl;
        std::cout << "  Type: " << accountType << std::endl;
        std::cout << "  Balance: $" << balance << std::endl;
    }
};

// Initialize static member
int BankAccount::nextAccountId = 1000;

// 3. Rectangle Class - Geometric Encapsulation
class Rectangle {
private:
    double width;
    double height;
    
    // Private validation method
    bool isValidDimension(double dimension) const {
        return dimension > 0;
    }
    
public:
    // Constructor with validation
    Rectangle(double w = 1.0, double h = 1.0) {
        setWidth(w);
        setHeight(h);
    }
    
    // Getters
    double getWidth() const {
        return width;
    }
    
    double getHeight() const {
        return height;
    }
    
    // Setters with validation
    void setWidth(double w) {
        if (isValidDimension(w)) {
            width = w;
        } else {
            std::cout << "Invalid width: " << w << ". Setting to default (1.0)" << std::endl;
            width = 1.0;
        }
    }
    
    void setHeight(double h) {
        if (isValidDimension(h)) {
            height = h;
        } else {
            std::cout << "Invalid height: " << h << ". Setting to default (1.0)" << std::endl;
            height = 1.0;
        }
    }
    
    // Computed properties (read-only)
    double getArea() const {
        return width * height;
    }
    
    double getPerimeter() const {
        return 2 * (width + height);
    }
    
    // Method to scale rectangle
    void scale(double factor) {
        if (factor > 0) {
            width *= factor;
            height *= factor;
            std::cout << "Rectangle scaled by factor " << factor << std::endl;
        } else {
            std::cout << "Invalid scale factor: " << factor << std::endl;
        }
    }
    
    void displayInfo() const {
        std::cout << "Rectangle Information:" << std::endl;
        std::cout << "  Width: " << width << std::endl;
        std::cout << "  Height: " << height << std::endl;
        std::cout << "  Area: " << getArea() << std::endl;
        std::cout << "  Perimeter: " << getPerimeter() << std::endl;
    }
};

// 4. Counter Class - Simple Encapsulation with Static Data
class Counter {
private:
    int count;
    std::string name;
    static int totalCounters;  // Tracks number of counter instances
    
public:
    // Constructor
    Counter(const std::string& counterName = "Unnamed") 
        : count(0), name(counterName) {
        totalCounters++;
        std::cout << "Counter '" << name << "' created. Total counters: " 
                  << totalCounters << std::endl;
    }
    
    // Destructor
    ~Counter() {
        totalCounters--;
        std::cout << "Counter '" << name << "' destroyed. Remaining counters: " 
                  << totalCounters << std::endl;
    }
    
    // Copy constructor
    Counter(const Counter& other) : count(other.count), name(other.name + "_copy") {
        totalCounters++;
        std::cout << "Counter '" << name << "' copied from '" << other.name 
                  << "'. Total counters: " << totalCounters << std::endl;
    }
    
    // Getters
    int getCount() const {
        return count;
    }
    
    std::string getName() const {
        return name;
    }
    
    static int getTotalCounters() {
        return totalCounters;
    }
    
    // Counter operations
    void increment() {
        count++;
        std::cout << "Counter '" << name << "' incremented to: " << count << std::endl;
    }
    
    void decrement() {
        if (count > 0) {
            count--;
            std::cout << "Counter '" << name << "' decremented to: " << count << std::endl;
        } else {
            std::cout << "Counter '" << name << "' cannot go below zero!" << std::endl;
        }
    }
    
    void reset() {
        count = 0;
        std::cout << "Counter '" << name << "' reset to zero" << std::endl;
    }
    
    void displayInfo() const {
        std::cout << "Counter '" << name << "' current value: " << count << std::endl;
    }
};

// Initialize static member
int Counter::totalCounters = 0;

// Demonstration functions
void demonstrateStudentEncapsulation() {
    std::cout << "\n=== STUDENT ENCAPSULATION DEMO ===" << std::endl;
    
    Student student1("Alice Johnson", 20, "STU001", 3.8);
    student1.displayInfo();
    
    std::cout << "\nAttempting to modify student data:" << std::endl;
    student1.setAge(21);
    student1.setGPA(3.9);
    
    std::cout << "\nTrying invalid data:" << std::endl;
    student1.setAge(-5);      // Invalid age
    student1.setGPA(5.0);     // Invalid GPA
    
    std::cout << "\nFinal student information:" << std::endl;
    student1.displayInfo();
    
    // Cannot access private members directly:
    // student1.name = "Hacker";  // Compilation error!
    // student1.gpa = 4.0;        // Compilation error!
}

void demonstrateBankAccountEncapsulation() {
    std::cout << "\n=== BANK ACCOUNT ENCAPSULATION DEMO ===" << std::endl;
    
    BankAccount account1("John Doe", "Checking", 1000.0);
    BankAccount account2("Jane Smith", "Savings", 500.0);
    
    std::cout << "\nInitial account states:" << std::endl;
    account1.displayAccountInfo();
    std::cout << std::endl;
    account2.displayAccountInfo();
    
    std::cout << "\nPerforming transactions:" << std::endl;
    account1.withdraw(200.0);
    account2.deposit(150.0);
    
    std::cout << "\nAttempting invalid operations:" << std::endl;
    account1.withdraw(2000.0);    // Insufficient funds
    account1.deposit(-100.0);     // Invalid amount
    
    std::cout << "\nTransfer operation:" << std::endl;
    account1.transferTo(account2, 300.0);
    
    std::cout << "\nFinal account states:" << std::endl;
    account1.displayAccountInfo();
    std::cout << std::endl;
    account2.displayAccountInfo();
    
    // Cannot access private members:
    // account1.balance = 1000000;  // Compilation error!
    // account1.accountNumber = "HACK123";  // Compilation error!
}

void demonstrateRectangleEncapsulation() {
    std::cout << "\n=== RECTANGLE ENCAPSULATION DEMO ===" << std::endl;
    
    Rectangle rect1(5.0, 3.0);
    rect1.displayInfo();
    
    std::cout << "\nModifying rectangle:" << std::endl;
    rect1.setWidth(7.0);
    rect1.setHeight(4.0);
    rect1.displayInfo();
    
    std::cout << "\nTrying invalid dimensions:" << std::endl;
    rect1.setWidth(-2.0);    // Invalid width
    rect1.setHeight(0.0);    // Invalid height
    
    std::cout << "\nScaling rectangle:" << std::endl;
    rect1.scale(1.5);
    rect1.displayInfo();
    
    rect1.scale(-1.0);       // Invalid scale factor
    
    // Cannot access private members:
    // rect1.width = -5.0;     // Compilation error!
    // rect1.height = 0.0;     // Compilation error!
}

void demonstrateCounterEncapsulation() {
    std::cout << "\n=== COUNTER ENCAPSULATION DEMO ===" << std::endl;
    
    Counter counter1("Main Counter");
    Counter counter2("Secondary Counter");
    
    std::cout << "\nCounter operations:" << std::endl;
    counter1.increment();
    counter1.increment();
    counter1.increment();
    
    counter2.increment();
    counter2.increment();
    
    counter1.displayInfo();
    counter2.displayInfo();
    
    std::cout << "\nDecrementing and testing boundaries:" << std::endl;
    counter1.decrement();
    counter2.decrement();
    counter2.decrement();
    counter2.decrement();    // Should not go below zero
    
    std::cout << "\nCreating copy and resetting:" << std::endl;
    Counter counter3 = counter1;  // Copy constructor
    counter3.displayInfo();
    
    counter1.reset();
    counter1.displayInfo();
    
    std::cout << "\nTotal counters created: " << Counter::getTotalCounters() << std::endl;
}

void demonstrateEncapsulationBenefits() {
    std::cout << "\n=== ENCAPSULATION BENEFITS DEMONSTRATION ===" << std::endl;
    
    std::cout << "1. Data Protection:" << std::endl;
    std::cout << "   - Private members cannot be accessed directly" << std::endl;
    std::cout << "   - All access goes through controlled public interface" << std::endl;
    
    std::cout << "\n2. Validation and Integrity:" << std::endl;
    std::cout << "   - Setter methods can validate input data" << std::endl;
    std::cout << "   - Invalid data is rejected with appropriate messages" << std::endl;
    
    std::cout << "\n3. Abstraction:" << std::endl;
    std::cout << "   - Users don't need to know internal implementation" << std::endl;
    std::cout << "   - Complex operations are simplified through methods" << std::endl;
    
    std::cout << "\n4. Maintainability:" << std::endl;
    std::cout << "   - Internal implementation can change without affecting external code" << std::endl;
    std::cout << "   - Public interface remains stable" << std::endl;
    
    std::cout << "\n5. Modularity:" << std::endl;
    std::cout << "   - Related data and methods are bundled together" << std::endl;
    std::cout << "   - Clear separation of concerns" << std::endl;
}

int main() {
    std::cout << "=== ENCAPSULATION IN C++: BASIC CONCEPTS ===" << std::endl;
    std::cout << "Encapsulation bundles data and methods while controlling access" << std::endl;
    std::cout << "through private, protected, and public access specifiers." << std::endl;
    
    demonstrateStudentEncapsulation();
    demonstrateBankAccountEncapsulation();
    demonstrateRectangleEncapsulation();
    demonstrateCounterEncapsulation();
    demonstrateEncapsulationBenefits();
    
    std::cout << "\n=== KEY TAKEAWAYS ===" << std::endl;
    std::cout << "1. Private members hide internal implementation details" << std::endl;
    std::cout << "2. Public methods provide controlled access to data" << std::endl;
    std::cout << "3. Validation in setters ensures data integrity" << std::endl;
    std::cout << "4. Const methods guarantee they won't modify object state" << std::endl;
    std::cout << "5. Encapsulation enables safe, maintainable code design" << std::endl;
    
    return 0;
}

/* Expected Output:
=== ENCAPSULATION IN C++: BASIC CONCEPTS ===
Encapsulation bundles data and methods while controlling access
through private, protected, and public access specifiers.

=== STUDENT ENCAPSULATION DEMO ===
Student Alice Johnson created with ID: STU001
Student Information:
  Name: Alice Johnson
  Age: 20
  Student ID: STU001
  GPA: 3.8
  Status: Excellent

Attempting to modify student data:
Age updated to: 21
GPA updated to: 3.9

Trying invalid data:
Invalid age! Age must be between 0 and 150.
Invalid GPA! GPA must be between 0.0 and 4.0.

Final student information:
Student Information:
  Name: Alice Johnson
  Age: 21
  Student ID: STU001
  GPA: 3.9
  Status: Excellent

=== BANK ACCOUNT ENCAPSULATION DEMO ===
Deposited $1000. New balance: $1000
Bank account created for John Doe with account number: ACC1001
Deposited $500. New balance: $500
Bank account created for Jane Smith with account number: ACC1002

Initial account states:
Account Information:
  Account Number: ACC1001
  Owner: John Doe
  Type: Checking
  Balance: $1000

Account Information:
  Account Number: ACC1002
  Owner: Jane Smith
  Type: Savings
  Balance: $500

Performing transactions:
Withdrew $200. New balance: $800
Deposited $150. New balance: $650

Attempting invalid operations:
Insufficient funds! Current balance: $800
Invalid deposit amount: -100

Transfer operation:
Initiating transfer of $300 from ACC1001 to ACC1002
Withdrew $300. New balance: $500
Deposited $300. New balance: $950
Transfer successful!

Final account states:
Account Information:
  Account Number: ACC1001
  Owner: John Doe
  Type: Checking
  Balance: $500

Account Information:
  Account Number: ACC1002
  Owner: Jane Smith
  Type: Savings
  Balance: $950

=== RECTANGLE ENCAPSULATION DEMO ===
Rectangle Information:
  Width: 5
  Height: 3
  Area: 15
  Perimeter: 16

Modifying rectangle:
Rectangle Information:
  Width: 7
  Height: 4
  Area: 28
  Perimeter: 22

Trying invalid dimensions:
Invalid width: -2. Setting to default (1.0)
Invalid height: 0. Setting to default (1.0)

Scaling rectangle:
Rectangle scaled by factor 1.5
Rectangle Information:
  Width: 1.5
  Height: 1.5
  Area: 2.25
  Perimeter: 6

Invalid scale factor: -1

=== COUNTER ENCAPSULATION DEMO ===
Counter 'Main Counter' created. Total counters: 1
Counter 'Secondary Counter' created. Total counters: 2

Counter operations:
Counter 'Main Counter' incremented to: 1
Counter 'Main Counter' incremented to: 2
Counter 'Main Counter' incremented to: 3
Counter 'Secondary Counter' incremented to: 1
Counter 'Secondary Counter' incremented to: 2
Counter 'Main Counter' current value: 3
Counter 'Secondary Counter' current value: 2

Decrementing and testing boundaries:
Counter 'Main Counter' decremented to: 2
Counter 'Secondary Counter' decremented to: 1
Counter 'Secondary Counter' decremented to: 0
Counter 'Secondary Counter' cannot go below zero!

Creating copy and resetting:
Counter 'Main Counter_copy' copied from 'Main Counter'. Total counters: 3
Counter 'Main Counter_copy' current value: 2
Counter 'Main Counter' reset to zero
Counter 'Main Counter' current value: 0

Total counters created: 3

=== ENCAPSULATION BENEFITS DEMONSTRATION ===
1. Data Protection:
   - Private members cannot be accessed directly
   - All access goes through controlled public interface

2. Validation and Integrity:
   - Setter methods can validate input data
   - Invalid data is rejected with appropriate messages

3. Abstraction:
   - Users don't need to know internal implementation
   - Complex operations are simplified through methods

4. Maintainability:
   - Internal implementation can change without affecting external code
   - Public interface remains stable

5. Modularity:
   - Related data and methods are bundled together
   - Clear separation of concerns

=== KEY TAKEAWAYS ===
1. Private members hide internal implementation details
2. Public methods provide controlled access to data
3. Validation in setters ensures data integrity
4. Const methods guarantee they won't modify object state
5. Encapsulation enables safe, maintainable code design
*/
