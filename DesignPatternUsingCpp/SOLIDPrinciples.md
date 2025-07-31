# SOLID Principles in C++ - Comprehensive Guide with Examples

## Table of Contents
1. [Overview of SOLID Principles](#overview)
2. [Single Responsibility Principle (SRP)](#single-responsibility-principle)
3. [Open/Closed Principle (OCP)](#openclosed-principle)
4. [Liskov Substitution Principle (LSP)](#liskov-substitution-principle)
5. [Interface Segregation Principle (ISP)](#interface-segregation-principle)
6. [Dependency Inversion Principle (DIP)](#dependency-inversion-principle)
7. [SOLID Principles Working Together](#solid-principles-working-together)
8. [Common Violations and How to Fix Them](#common-violations-and-fixes)
9. [Best Practices and Guidelines](#best-practices)

## Overview

The **SOLID** principles are five fundamental design principles in object-oriented programming that help create maintainable, flexible, and robust software. These principles were introduced by Robert C. Martin (Uncle Bob) and form the foundation of clean code architecture.

📖 Structure:
1. Single Responsibility Principle (SRP) - One reason to change
2. Open/Closed Principle (OCP) - Open for extension, closed for modification
3. Liskov Substitution Principle (LSP) - Substitutability of derived classes
4. Interface Segregation Principle (ISP) - Small, focused interfaces
5. Dependency Inversion Principle (DIP) - Depend on abstractions

### Why SOLID Principles Matter:
✅ **Maintainable Code**: Easier to modify and extend  
✅ **Testable Code**: Better isolation and mocking capabilities  
✅ **Flexible Architecture**: Adaptable to changing requirements  
✅ **Reduced Coupling**: Less interdependence between components  
✅ **Higher Cohesion**: Related functionality grouped together  
✅ **Better Code Reusability**: Components can be reused in different contexts  

---

## 1. Single Responsibility Principle (SRP)

### Definition
> **"A class should have only one reason to change."**

Each class should have only one responsibility or job. When a class has multiple responsibilities, changes to one responsibility can affect the others, making the code harder to maintain.

### ❌ **Violation Example:**
```cpp
// BAD: Class with multiple responsibilities
class Employee {
private:
    std::string name_;
    std::string email_;
    double salary_;
    
public:
    Employee(const std::string& name, const std::string& email, double salary)
        : name_(name), email_(email), salary_(salary) {}
    
    // Responsibility 1: Employee data management
    std::string getName() const { return name_; }
    std::string getEmail() const { return email_; }
    double getSalary() const { return salary_; }
    void setSalary(double salary) { salary_ = salary; }
    
    // Responsibility 2: Salary calculation (VIOLATION!)
    double calculateTax() const {
        return salary_ * 0.2; // 20% tax
    }
    
    double calculateBonus() const {
        return salary_ * 0.1; // 10% bonus
    }
    
    // Responsibility 3: Database operations (VIOLATION!)
    void saveToDatabase() const {
        std::cout << "Saving employee " << name_ << " to database..." << std::endl;
        // Database logic here
    }
    
    // Responsibility 4: Report generation (VIOLATION!)
    void generatePayslip() const {
        std::cout << "=== PAYSLIP ===" << std::endl;
        std::cout << "Name: " << name_ << std::endl;
        std::cout << "Salary: $" << salary_ << std::endl;
        std::cout << "Tax: $" << calculateTax() << std::endl;
        std::cout << "Bonus: $" << calculateBonus() << std::endl;
    }
};
```

**Problems with this approach:**
- Changes in tax calculation affect the Employee class
- Database schema changes require Employee class modification
- Report format changes impact Employee class
- Difficult to test individual responsibilities
- High coupling between different concerns

### ✅ **Correct Implementation:**
```cpp
// GOOD: Each class has a single responsibility

// Responsibility 1: Employee data management
class Employee {
private:
    std::string name_;
    std::string email_;
    double salary_;
    
public:
    Employee(const std::string& name, const std::string& email, double salary)
        : name_(name), email_(email), salary_(salary) {}
    
    std::string getName() const { return name_; }
    std::string getEmail() const { return email_; }
    double getSalary() const { return salary_; }
    void setSalary(double salary) { salary_ = salary; }
};

// Responsibility 2: Salary calculations
class SalaryCalculator {
public:
    static double calculateTax(double salary) {
        return salary * 0.2; // 20% tax
    }
    
    static double calculateBonus(double salary) {
        return salary * 0.1; // 10% bonus
    }
    
    static double calculateNetSalary(double salary) {
        return salary - calculateTax(salary) + calculateBonus(salary);
    }
};

// Responsibility 3: Database operations
class EmployeeRepository {
public:
    void save(const Employee& employee) const {
        std::cout << "Saving employee " << employee.getName() << " to database..." << std::endl;
        // Database logic here
    }
    
    Employee findByName(const std::string& name) const {
        // Database query logic here
        return Employee(name, "email@example.com", 50000);
    }
    
    std::vector<Employee> findAll() const {
        // Database query logic here
        return {};
    }
};

// Responsibility 4: Report generation
class PayslipGenerator {
public:
    void generatePayslip(const Employee& employee) const {
        double salary = employee.getSalary();
        std::cout << "=== PAYSLIP ===" << std::endl;
        std::cout << "Name: " << employee.getName() << std::endl;
        std::cout << "Salary: $" << salary << std::endl;
        std::cout << "Tax: $" << SalaryCalculator::calculateTax(salary) << std::endl;
        std::cout << "Bonus: $" << SalaryCalculator::calculateBonus(salary) << std::endl;
        std::cout << "Net Salary: $" << SalaryCalculator::calculateNetSalary(salary) << std::endl;
    }
};

// Usage example
void demonstrateSRP() {
    Employee emp("John Doe", "john@example.com", 50000);
    
    EmployeeRepository repo;
    repo.save(emp);
    
    PayslipGenerator generator;
    generator.generatePayslip(emp);
}
```

**Benefits of this approach:**
- Each class has a single, clear responsibility
- Changes in tax rules only affect SalaryCalculator
- Database changes only affect EmployeeRepository
- Report format changes only affect PayslipGenerator
- Easy to test each component independently
- Better code reusability

---

## 2. Open/Closed Principle (OCP)

### Definition
> **"Software entities should be open for extension, but closed for modification."**

You should be able to extend a class's behavior without modifying its existing code. This is typically achieved through inheritance, composition, and polymorphism.

### ❌ **Violation Example:**
```cpp
// BAD: Modification required for new shapes
class AreaCalculator {
public:
    double calculateArea(const std::vector<std::string>& shapes, 
                        const std::vector<std::map<std::string, double>>& dimensions) {
        double totalArea = 0;
        
        for (size_t i = 0; i < shapes.size(); ++i) {
            const std::string& shape = shapes[i];
            const auto& dims = dimensions[i];
            
            // VIOLATION: Need to modify this method for each new shape
            if (shape == "rectangle") {
                totalArea += dims.at("width") * dims.at("height");
            } else if (shape == "circle") {
                double radius = dims.at("radius");
                totalArea += 3.14159 * radius * radius;
            } else if (shape == "triangle") {
                totalArea += 0.5 * dims.at("base") * dims.at("height");
            }
            // Adding new shapes requires modifying this method!
        }
        
        return totalArea;
    }
};
```

**Problems:**
- Adding new shapes requires modifying existing code
- Risk of breaking existing functionality
- Violates the closed part of OCP

### ✅ **Correct Implementation:**
```cpp
// GOOD: Open for extension, closed for modification

// Abstract base class defines the interface
class Shape {
public:
    virtual ~Shape() = default;
    virtual double calculateArea() const = 0;
    virtual std::string getType() const = 0;
};

// Concrete implementations
class Rectangle : public Shape {
private:
    double width_, height_;
    
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}
    
    double calculateArea() const override {
        return width_ * height_;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
};

class Circle : public Shape {
private:
    double radius_;
    
public:
    explicit Circle(double radius) : radius_(radius) {}
    
    double calculateArea() const override {
        return 3.14159 * radius_ * radius_;
    }
    
    std::string getType() const override {
        return "Circle";
    }
};

class Triangle : public Shape {
private:
    double base_, height_;
    
public:
    Triangle(double base, double height) : base_(base), height_(height) {}
    
    double calculateArea() const override {
        return 0.5 * base_ * height_;
    }
    
    std::string getType() const override {
        return "Triangle";
    }
};

// Calculator that follows OCP
class AreaCalculator {
public:
    double calculateTotalArea(const std::vector<std::unique_ptr<Shape>>& shapes) const {
        double totalArea = 0;
        
        for (const auto& shape : shapes) {
            totalArea += shape->calculateArea();
        }
        
        return totalArea;
    }
    
    void printShapeDetails(const std::vector<std::unique_ptr<Shape>>& shapes) const {
        for (const auto& shape : shapes) {
            std::cout << shape->getType() << ": " << shape->calculateArea() << " sq units" << std::endl;
        }
    }
};

// Adding new shapes WITHOUT modifying existing code
class Pentagon : public Shape {
private:
    double side_;
    
public:
    explicit Pentagon(double side) : side_(side) {}
    
    double calculateArea() const override {
        // Pentagon area formula
        return 0.25 * std::sqrt(25 + 10 * std::sqrt(5)) * side_ * side_;
    }
    
    std::string getType() const override {
        return "Pentagon";
    }
};

// Usage example
void demonstrateOCP() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(5, 4));
    shapes.push_back(std::make_unique<Circle>(3));
    shapes.push_back(std::make_unique<Triangle>(6, 8));
    shapes.push_back(std::make_unique<Pentagon>(4)); // New shape added without modifying AreaCalculator
    
    AreaCalculator calculator;
    std::cout << "Total area: " << calculator.calculateTotalArea(shapes) << std::endl;
    calculator.printShapeDetails(shapes);
}
```

**Benefits:**
- Adding new shapes doesn't require modifying existing code
- Existing functionality remains stable
- Easy to extend with new shape types
- Better maintainability and reduced risk of bugs

---

## 3. Liskov Substitution Principle (LSP)

### Definition
> **"Objects of a superclass should be replaceable with objects of its subclasses without breaking the application."**

Subtypes must be substitutable for their base types. This means derived classes must honor the contracts established by their base classes.

### ❌ **Violation Example:**
```cpp
// BAD: Rectangle-Square inheritance violation
class Rectangle {
protected:
    double width_, height_;
    
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}
    
    virtual void setWidth(double width) { width_ = width; }
    virtual void setHeight(double height) { height_ = height; }
    
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
    
    virtual double getArea() const { return width_ * height_; }
};

// VIOLATION: Square changes the behavior of Rectangle
class Square : public Rectangle {
public:
    explicit Square(double side) : Rectangle(side, side) {}
    
    // LSP Violation: Overrides parent behavior in unexpected way
    void setWidth(double width) override {
        width_ = width;
        height_ = width; // Changes both dimensions!
    }
    
    void setHeight(double height) override {
        width_ = height;  // Changes both dimensions!
        height_ = height;
    }
};

// This function expects Rectangle behavior but breaks with Square
void testRectangle(Rectangle& rect) {
    rect.setWidth(5);
    rect.setHeight(4);
    
    // This assertion fails for Square objects!
    // Expected: 20, but Square gives: 16
    assert(rect.getArea() == 20); // FAILS for Square!
    
    std::cout << "Area: " << rect.getArea() << std::endl;
}
```

**Problems:**
- Square changes the expected behavior of Rectangle
- Client code that works with Rectangle breaks when given a Square
- Violates the contract established by Rectangle

### ✅ **Correct Implementation:**
```cpp
// GOOD: Proper abstraction that follows LSP

// Abstract base class defining common interface
class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual std::string getDescription() const = 0;
};

// Rectangle with its own specific behavior
class Rectangle : public Shape {
private:
    double width_, height_;
    
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}
    
    void setWidth(double width) { width_ = width; }
    void setHeight(double height) { height_ = height; }
    
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
    
    double getArea() const override { return width_ * height_; }
    
    std::string getDescription() const override {
        return "Rectangle(" + std::to_string(width_) + " x " + std::to_string(height_) + ")";
    }
};

// Square with its own specific behavior
class Square : public Shape {
private:
    double side_;
    
public:
    explicit Square(double side) : side_(side) {}
    
    void setSide(double side) { side_ = side; }
    double getSide() const { return side_; }
    
    double getArea() const override { return side_ * side_; }
    
    std::string getDescription() const override {
        return "Square(" + std::to_string(side_) + ")";
    }
};

// Alternative: Using composition instead of inheritance
class GeometricRectangle {
private:
    double width_, height_;
    
public:
    GeometricRectangle(double width, double height) : width_(width), height_(height) {}
    
    void setDimensions(double width, double height) {
        width_ = width;
        height_ = height;
    }
    
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
    double getArea() const { return width_ * height_; }
};

class GeometricSquare {
private:
    double side_;
    
public:
    explicit GeometricSquare(double side) : side_(side) {}
    
    void setSide(double side) { side_ = side; }
    double getSide() const { return side_; }
    double getArea() const { return side_ * side_; }
};

// Function that works correctly with LSP-compliant shapes
void processShapes(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        std::cout << shape->getDescription() << " has area: " << shape->getArea() << std::endl;
    }
}

// Usage example
void demonstrateLSP() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Rectangle>(5, 4));
    shapes.push_back(std::make_unique<Square>(3));
    
    // Both shapes can be used interchangeably without issues
    processShapes(shapes);
}
```

**Key LSP Guidelines:**
- Preconditions cannot be strengthened in subclasses
- Postconditions cannot be weakened in subclasses
- Invariants must be preserved
- Method signatures should remain compatible

---

## 4. Interface Segregation Principle (ISP)

### Definition
> **"Clients should not be forced to depend upon interfaces they do not use."**

Large interfaces should be split into smaller, more specific ones so that clients only need to know about the methods that are relevant to them.

### ❌ **Violation Example:**
```cpp
// BAD: Fat interface that forces unnecessary dependencies
class IMachine {
public:
    virtual ~IMachine() = default;
    
    // Printing functionality
    virtual void print(const std::string& document) = 0;
    
    // Scanning functionality
    virtual void scan() = 0;
    
    // Faxing functionality
    virtual void fax(const std::string& document) = 0;
    
    // Copying functionality
    virtual void copy() = 0;
};

// VIOLATION: Simple printer forced to implement unused methods
class SimplePrinter : public IMachine {
public:
    void print(const std::string& document) override {
        std::cout << "Printing: " << document << std::endl;
    }
    
    // ISP Violation: Forced to implement methods it doesn't need
    void scan() override {
        throw std::runtime_error("Scan not supported!");
    }
    
    void fax(const std::string& document) override {
        throw std::runtime_error("Fax not supported!");
    }
    
    void copy() override {
        throw std::runtime_error("Copy not supported!");
    }
};

// VIOLATION: Scanner forced to implement printing methods
class SimpleScanner : public IMachine {
public:
    void print(const std::string& document) override {
        throw std::runtime_error("Print not supported!");
    }
    
    void scan() override {
        std::cout << "Scanning document..." << std::endl;
    }
    
    void fax(const std::string& document) override {
        throw std::runtime_error("Fax not supported!");
    }
    
    void copy() override {
        throw std::runtime_error("Copy not supported!");
    }
};
```

**Problems:**
- Classes forced to implement methods they don't need
- Unnecessary dependencies on unused functionality
- Runtime exceptions for unsupported operations
- Difficult to maintain and extend

### ✅ **Correct Implementation:**
```cpp
// GOOD: Segregated interfaces

// Separate interfaces for different functionalities
class IPrinter {
public:
    virtual ~IPrinter() = default;
    virtual void print(const std::string& document) = 0;
};

class IScanner {
public:
    virtual ~IScanner() = default;
    virtual void scan() = 0;
};

class IFax {
public:
    virtual ~IFax() = default;
    virtual void fax(const std::string& document) = 0;
};

class ICopier {
public:
    virtual ~ICopier() = default;
    virtual void copy() = 0;
};

// Simple printer only implements what it needs
class SimplePrinter : public IPrinter {
public:
    void print(const std::string& document) override {
        std::cout << "Printing: " << document << std::endl;
    }
};

// Simple scanner only implements what it needs
class SimpleScanner : public IScanner {
public:
    void scan() override {
        std::cout << "Scanning document..." << std::endl;
    }
};

// Multi-function device implements multiple interfaces
class MultiFunctionPrinter : public IPrinter, public IScanner, public IFax, public ICopier {
public:
    void print(const std::string& document) override {
        std::cout << "Multi-function: Printing " << document << std::endl;
    }
    
    void scan() override {
        std::cout << "Multi-function: Scanning document..." << std::endl;
    }
    
    void fax(const std::string& document) override {
        std::cout << "Multi-function: Faxing " << document << std::endl;
    }
    
    void copy() override {
        std::cout << "Multi-function: Copying document..." << std::endl;
    }
};

// Print-scan combo device
class PrintScanDevice : public IPrinter, public IScanner {
public:
    void print(const std::string& document) override {
        std::cout << "Print-Scan device: Printing " << document << std::endl;
    }
    
    void scan() override {
        std::cout << "Print-Scan device: Scanning..." << std::endl;
    }
};

// Client code that only depends on what it needs
class DocumentProcessor {
private:
    IPrinter* printer_;
    IScanner* scanner_;
    
public:
    DocumentProcessor(IPrinter* printer, IScanner* scanner)
        : printer_(printer), scanner_(scanner) {}
    
    void processDocument(const std::string& document) {
        scanner_->scan();
        printer_->print(document);
    }
};

// Usage example
void demonstrateISP() {
    SimplePrinter printer;
    SimpleScanner scanner;
    MultiFunctionPrinter mfp;
    
    // Client only depends on interfaces it needs
    DocumentProcessor processor(&printer, &scanner);
    processor.processDocument("Important document");
    
    // Multi-function device can be used where any interface is needed
    DocumentProcessor processor2(&mfp, &mfp);
    processor2.processDocument("Another document");
}
```

**Benefits:**
- Classes only implement interfaces they actually need
- No forced dependencies on unused functionality
- Better separation of concerns
- Easier to test and mock
- More flexible composition of functionality

---

## 5. Dependency Inversion Principle (DIP)

### Definition
> **"High-level modules should not depend on low-level modules. Both should depend on abstractions. Abstractions should not depend on details. Details should depend on abstractions."**

This principle helps achieve loose coupling by ensuring that high-level policy-setting modules are not dependent on low-level implementation details.

### ❌ **Violation Example:**
```cpp
// BAD: High-level module depends on low-level concrete classes

// Low-level modules (concrete implementations)
class MySQLDatabase {
public:
    void save(const std::string& data) {
        std::cout << "Saving to MySQL: " << data << std::endl;
    }
    
    std::string load(int id) {
        return "Data from MySQL with ID: " + std::to_string(id);
    }
};

class EmailService {
public:
    void sendEmail(const std::string& message, const std::string& recipient) {
        std::cout << "Sending email to " << recipient << ": " << message << std::endl;
    }
};

// VIOLATION: High-level module depends on concrete low-level modules
class UserService {
private:
    MySQLDatabase database_;  // DIP Violation: Depends on concrete class
    EmailService emailService_;  // DIP Violation: Depends on concrete class
    
public:
    void registerUser(const std::string& username, const std::string& email) {
        // High-level business logic
        std::string userData = "User: " + username + ", Email: " + email;
        
        // Directly using concrete implementations
        database_.save(userData);
        emailService_.sendEmail("Welcome!", email);
    }
    
    std::string getUserData(int userId) {
        return database_.load(userId);
    }
};
```

**Problems:**
- UserService is tightly coupled to MySQL and EmailService
- Cannot easily switch to different database or email providers
- Difficult to test in isolation
- Changes in low-level modules can break high-level modules

### ✅ **Correct Implementation:**
```cpp
// GOOD: Dependency Inversion applied

// Abstractions (interfaces)
class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual void save(const std::string& data) = 0;
    virtual std::string load(int id) = 0;
};

class IEmailService {
public:
    virtual ~IEmailService() = default;
    virtual void sendEmail(const std::string& message, const std::string& recipient) = 0;
};

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const std::string& message) = 0;
};

// Low-level modules implementing abstractions
class MySQLDatabase : public IDatabase {
public:
    void save(const std::string& data) override {
        std::cout << "Saving to MySQL: " << data << std::endl;
    }
    
    std::string load(int id) override {
        return "Data from MySQL with ID: " + std::to_string(id);
    }
};

class PostgreSQLDatabase : public IDatabase {
public:
    void save(const std::string& data) override {
        std::cout << "Saving to PostgreSQL: " << data << std::endl;
    }
    
    std::string load(int id) override {
        return "Data from PostgreSQL with ID: " + std::to_string(id);
    }
};

class SMTPEmailService : public IEmailService {
public:
    void sendEmail(const std::string& message, const std::string& recipient) override {
        std::cout << "SMTP: Sending email to " << recipient << ": " << message << std::endl;
    }
};

class SendGridEmailService : public IEmailService {
public:
    void sendEmail(const std::string& message, const std::string& recipient) override {
        std::cout << "SendGrid: Sending email to " << recipient << ": " << message << std::endl;
    }
};

class FileLogger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << "File Log: " << message << std::endl;
    }
};

class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << "Console Log: " << message << std::endl;
    }
};

// High-level module depends only on abstractions
class UserService {
private:
    std::unique_ptr<IDatabase> database_;
    std::unique_ptr<IEmailService> emailService_;
    std::unique_ptr<ILogger> logger_;
    
public:
    // Dependency injection through constructor
    UserService(std::unique_ptr<IDatabase> database,
               std::unique_ptr<IEmailService> emailService,
               std::unique_ptr<ILogger> logger)
        : database_(std::move(database))
        , emailService_(std::move(emailService))
        , logger_(std::move(logger)) {}
    
    void registerUser(const std::string& username, const std::string& email) {
        logger_->log("Registering user: " + username);
        
        // High-level business logic
        std::string userData = "User: " + username + ", Email: " + email;
        
        // Using abstractions, not concrete implementations
        database_->save(userData);
        emailService_->sendEmail("Welcome to our service!", email);
        
        logger_->log("User registration completed for: " + username);
    }
    
    std::string getUserData(int userId) {
        logger_->log("Fetching user data for ID: " + std::to_string(userId));
        return database_->load(userId);
    }
};

// Factory for creating configured UserService
class UserServiceFactory {
public:
    static std::unique_ptr<UserService> createProductionService() {
        return std::make_unique<UserService>(
            std::make_unique<MySQLDatabase>(),
            std::make_unique<SMTPEmailService>(),
            std::make_unique<FileLogger>()
        );
    }
    
    static std::unique_ptr<UserService> createTestService() {
        return std::make_unique<UserService>(
            std::make_unique<PostgreSQLDatabase>(),
            std::make_unique<SendGridEmailService>(),
            std::make_unique<ConsoleLogger>()
        );
    }
};

// Mock implementations for testing
class MockDatabase : public IDatabase {
private:
    std::map<int, std::string> data_;
    int nextId_ = 1;
    
public:
    void save(const std::string& data) override {
        data_[nextId_++] = data;
        std::cout << "Mock: Saved data with ID " << (nextId_ - 1) << std::endl;
    }
    
    std::string load(int id) override {
        auto it = data_.find(id);
        if (it != data_.end()) {
            return it->second;
        }
        return "Mock: No data found for ID " + std::to_string(id);
    }
};

class MockEmailService : public IEmailService {
private:
    std::vector<std::pair<std::string, std::string>> sentEmails_;
    
public:
    void sendEmail(const std::string& message, const std::string& recipient) override {
        sentEmails_.emplace_back(message, recipient);
        std::cout << "Mock: Email queued for " << recipient << std::endl;
    }
    
    size_t getSentEmailCount() const { return sentEmails_.size(); }
    std::vector<std::pair<std::string, std::string>> getSentEmails() const { return sentEmails_; }
};

// Usage example
void demonstrateDIP() {
    // Production configuration
    auto prodService = UserServiceFactory::createProductionService();
    prodService->registerUser("john_doe", "john@example.com");
    
    std::cout << "\n--- Switching to test configuration ---\n" << std::endl;
    
    // Test configuration with different implementations
    auto testService = UserServiceFactory::createTestService();
    testService->registerUser("jane_doe", "jane@example.com");
    
    std::cout << "\n--- Using mock implementations for testing ---\n" << std::endl;
    
    // Test configuration with mocks
    auto mockService = std::make_unique<UserService>(
        std::make_unique<MockDatabase>(),
        std::make_unique<MockEmailService>(),
        std::make_unique<ConsoleLogger>()
    );
    mockService->registerUser("test_user", "test@example.com");
}
```

**Benefits:**
- High-level modules are independent of low-level implementation details
- Easy to swap implementations without changing high-level code
- Better testability through dependency injection and mocking
- Supports different configurations for different environments
- Follows the Hollywood Principle: "Don't call us, we'll call you"

---

## SOLID Principles Working Together

### Complete Example: E-commerce Order Processing System

```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

// DIP: Abstractions for external dependencies
class IPaymentProcessor {
public:
    virtual ~IPaymentProcessor() = default;
    virtual bool processPayment(double amount, const std::string& cardNumber) = 0;
};

class IInventoryService {
public:
    virtual ~IInventoryService() = default;
    virtual bool isInStock(const std::string& productId, int quantity) = 0;
    virtual void reserveItems(const std::string& productId, int quantity) = 0;
};

class INotificationService {
public:
    virtual ~INotificationService() = default;
    virtual void sendOrderConfirmation(const std::string& email, const std::string& orderId) = 0;
};

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const std::string& message) = 0;
};

// SRP: Each class has a single responsibility
class Product {
private:
    std::string id_;
    std::string name_;
    double price_;
    
public:
    Product(const std::string& id, const std::string& name, double price)
        : id_(id), name_(name), price_(price) {}
    
    std::string getId() const { return id_; }
    std::string getName() const { return name_; }
    double getPrice() const { return price_; }
};

class OrderItem {
private:
    Product product_;
    int quantity_;
    
public:
    OrderItem(const Product& product, int quantity)
        : product_(product), quantity_(quantity) {}
    
    Product getProduct() const { return product_; }
    int getQuantity() const { return quantity_; }
    double getTotalPrice() const { return product_.getPrice() * quantity_; }
};

class Customer {
private:
    std::string id_;
    std::string name_;
    std::string email_;
    
public:
    Customer(const std::string& id, const std::string& name, const std::string& email)
        : id_(id), name_(name), email_(email) {}
    
    std::string getId() const { return id_; }
    std::string getName() const { return name_; }
    std::string getEmail() const { return email_; }
};

// SRP: Order only manages order data
class Order {
private:
    std::string id_;
    Customer customer_;
    std::vector<OrderItem> items_;
    double totalAmount_;
    
public:
    Order(const std::string& id, const Customer& customer)
        : id_(id), customer_(customer), totalAmount_(0) {}
    
    void addItem(const OrderItem& item) {
        items_.push_back(item);
        totalAmount_ += item.getTotalPrice();
    }
    
    std::string getId() const { return id_; }
    Customer getCustomer() const { return customer_; }
    std::vector<OrderItem> getItems() const { return items_; }
    double getTotalAmount() const { return totalAmount_; }
};

// ISP: Separate interfaces for different discount strategies
class IDiscountStrategy {
public:
    virtual ~IDiscountStrategy() = default;
    virtual double calculateDiscount(const Order& order) = 0;
    virtual std::string getDescription() = 0;
};

// OCP: New discount strategies can be added without modifying existing code
class NoDiscountStrategy : public IDiscountStrategy {
public:
    double calculateDiscount(const Order& order) override {
        return 0;
    }
    
    std::string getDescription() override {
        return "No discount";
    }
};

class PercentageDiscountStrategy : public IDiscountStrategy {
private:
    double percentage_;
    
public:
    explicit PercentageDiscountStrategy(double percentage) : percentage_(percentage) {}
    
    double calculateDiscount(const Order& order) override {
        return order.getTotalAmount() * (percentage_ / 100.0);
    }
    
    std::string getDescription() override {
        return std::to_string(percentage_) + "% discount";
    }
};

class FixedAmountDiscountStrategy : public IDiscountStrategy {
private:
    double amount_;
    
public:
    explicit FixedAmountDiscountStrategy(double amount) : amount_(amount) {}
    
    double calculateDiscount(const Order& order) override {
        return std::min(amount_, order.getTotalAmount());
    }
    
    std::string getDescription() override {
        return "$" + std::to_string(amount_) + " fixed discount";
    }
};

// SRP: Order processing logic separate from order data
// DIP: Depends on abstractions, not concrete implementations
class OrderProcessor {
private:
    std::unique_ptr<IPaymentProcessor> paymentProcessor_;
    std::unique_ptr<IInventoryService> inventoryService_;
    std::unique_ptr<INotificationService> notificationService_;
    std::unique_ptr<ILogger> logger_;
    std::unique_ptr<IDiscountStrategy> discountStrategy_;
    
public:
    OrderProcessor(std::unique_ptr<IPaymentProcessor> paymentProcessor,
                  std::unique_ptr<IInventoryService> inventoryService,
                  std::unique_ptr<INotificationService> notificationService,
                  std::unique_ptr<ILogger> logger,
                  std::unique_ptr<IDiscountStrategy> discountStrategy)
        : paymentProcessor_(std::move(paymentProcessor))
        , inventoryService_(std::move(inventoryService))
        , notificationService_(std::move(notificationService))
        , logger_(std::move(logger))
        , discountStrategy_(std::move(discountStrategy)) {}
    
    bool processOrder(Order& order, const std::string& cardNumber) {
        logger_->log("Processing order: " + order.getId());
        
        // Check inventory
        for (const auto& item : order.getItems()) {
            if (!inventoryService_->isInStock(item.getProduct().getId(), item.getQuantity())) {
                logger_->log("Item out of stock: " + item.getProduct().getName());
                return false;
            }
        }
        
        // Calculate final amount with discount
        double discount = discountStrategy_->calculateDiscount(order);
        double finalAmount = order.getTotalAmount() - discount;
        
        logger_->log("Discount applied: " + discountStrategy_->getDescription() + 
                    " ($" + std::to_string(discount) + ")");
        
        // Process payment
        if (!paymentProcessor_->processPayment(finalAmount, cardNumber)) {
            logger_->log("Payment failed for order: " + order.getId());
            return false;
        }
        
        // Reserve inventory
        for (const auto& item : order.getItems()) {
            inventoryService_->reserveItems(item.getProduct().getId(), item.getQuantity());
        }
        
        // Send confirmation
        notificationService_->sendOrderConfirmation(order.getCustomer().getEmail(), order.getId());
        
        logger_->log("Order processed successfully: " + order.getId());
        return true;
    }
};

// Concrete implementations
class CreditCardProcessor : public IPaymentProcessor {
public:
    bool processPayment(double amount, const std::string& cardNumber) override {
        std::cout << "Processing $" << amount << " payment with card: " << cardNumber << std::endl;
        return true; // Simulate successful payment
    }
};

class DatabaseInventoryService : public IInventoryService {
public:
    bool isInStock(const std::string& productId, int quantity) override {
        std::cout << "Checking stock for product: " << productId << " (quantity: " << quantity << ")" << std::endl;
        return true; // Simulate items in stock
    }
    
    void reserveItems(const std::string& productId, int quantity) override {
        std::cout << "Reserved " << quantity << " units of product: " << productId << std::endl;
    }
};

class EmailNotificationService : public INotificationService {
public:
    void sendOrderConfirmation(const std::string& email, const std::string& orderId) override {
        std::cout << "Sending order confirmation to " << email << " for order: " << orderId << std::endl;
    }
};

class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << "[LOG] " << message << std::endl;
    }
};

// Usage demonstration
void demonstrateSOLIDPrinciples() {
    // Create products
    Product laptop("P001", "Gaming Laptop", 1500.0);
    Product mouse("P002", "Wireless Mouse", 50.0);
    
    // Create customer
    Customer customer("C001", "John Doe", "john@example.com");
    
    // Create order
    Order order("O001", customer);
    order.addItem(OrderItem(laptop, 1));
    order.addItem(OrderItem(mouse, 2));
    
    // Create order processor with dependencies
    auto processor = std::make_unique<OrderProcessor>(
        std::make_unique<CreditCardProcessor>(),
        std::make_unique<DatabaseInventoryService>(),
        std::make_unique<EmailNotificationService>(),
        std::make_unique<ConsoleLogger>(),
        std::make_unique<PercentageDiscountStrategy>(10.0)
    );
    
    // Process the order
    bool success = processor->processOrder(order, "4532-1234-5678-9012");
    
    if (success) {
        std::cout << "\nOrder processed successfully!" << std::endl;
    } else {
        std::cout << "\nOrder processing failed!" << std::endl;
    }
}
```

---

## Common Violations and How to Fix Them

### 1. God Classes (SRP Violation)
```cpp
// ❌ BAD: God class doing everything
class UserManager {
    void createUser() { /* ... */ }
    void validateEmail() { /* ... */ }
    void sendWelcomeEmail() { /* ... */ }
    void saveToDatabase() { /* ... */ }
    void generateReport() { /* ... */ }
    void auditUserAction() { /* ... */ }
};

// ✅ GOOD: Separate responsibilities
class User { /* User data */ };
class UserValidator { /* Validation logic */ };
class EmailService { /* Email operations */ };
class UserRepository { /* Database operations */ };
class ReportGenerator { /* Reporting logic */ };
class AuditService { /* Auditing logic */ };
```

### 2. Shotgun Surgery (OCP Violation)
```cpp
// ❌ BAD: Adding new shape requires modifying multiple classes
class ShapeProcessor {
    void process(const std::string& shapeType) {
        if (shapeType == "circle") { /* ... */ }
        else if (shapeType == "square") { /* ... */ }
        // Adding triangle requires modifying this method
    }
};

// ✅ GOOD: Use polymorphism
abstract class Shape {
    virtual void process() = 0;
};
class Circle : public Shape { /* ... */ };
class Square : public Shape { /* ... */ };
class Triangle : public Shape { /* ... */ }; // No existing code modified
```

### 3. Refused Bequest (LSP Violation)
```cpp
// ❌ BAD: Derived class refuses to implement base class behavior
class Bird {
    virtual void fly() = 0;
};
class Penguin : public Bird {
    void fly() override {
        throw std::runtime_error("Penguins can't fly!"); // LSP violation
    }
};

// ✅ GOOD: Proper abstraction
class Bird { /* Common bird behavior */ };
class FlyingBird : public Bird {
    virtual void fly() = 0;
};
class Eagle : public FlyingBird { /* ... */ };
class Penguin : public Bird { /* No flying behavior */ };
```

### 4. Fat Interfaces (ISP Violation)
```cpp
// ❌ BAD: Fat interface
class IWorker {
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
};
class Robot : public IWorker {
    void work() override { /* ... */ }
    void eat() override { throw std::runtime_error("Robots don't eat!"); }
    void sleep() override { throw std::runtime_error("Robots don't sleep!"); }
};

// ✅ GOOD: Segregated interfaces
class IWorkable { virtual void work() = 0; };
class IFeedable { virtual void eat() = 0; };
class ISleepable { virtual void sleep() = 0; };
class Robot : public IWorkable { /* Only implements what it needs */ };
class Human : public IWorkable, public IFeedable, public ISleepable { /* ... */ };
```

---

## Best Practices and Guidelines

### 1. **Start with SOLID in Mind**
- Design interfaces before implementations
- Think about responsibilities during class design
- Consider how classes will be extended
- Plan for dependency injection from the beginning

### 2. **Use Modern C++ Features**
```cpp
// Smart pointers for automatic memory management
std::unique_ptr<IService> service = std::make_unique<ConcreteService>();

// Move semantics for better performance
class ServiceManager {
    std::unique_ptr<IService> service_;
public:
    ServiceManager(std::unique_ptr<IService> service) 
        : service_(std::move(service)) {}
};

// Lambda expressions for strategies
auto discountStrategy = [](double amount) { return amount * 0.1; };
```

### 3. **Testing with SOLID**
```cpp
// Dependency injection makes testing easy
class OrderProcessorTest {
    void testOrderProcessing() {
        auto mockPayment = std::make_unique<MockPaymentProcessor>();
        auto mockInventory = std::make_unique<MockInventoryService>();
        
        OrderProcessor processor(std::move(mockPayment), std::move(mockInventory));
        
        // Test with controlled dependencies
        Order order = createTestOrder();
        bool result = processor.processOrder(order, "test-card");
        
        assert(result == true);
    }
};
```

### 4. **Common Patterns That Support SOLID**
- **Strategy Pattern**: Supports OCP and enables algorithm switching
- **Factory Pattern**: Supports DIP by abstracting object creation
- **Observer Pattern**: Supports SRP by separating notification logic
- **Decorator Pattern**: Supports OCP by allowing behavior extension
- **Adapter Pattern**: Supports ISP by providing specific interfaces

### 5. **Code Review Checklist**
- [ ] Does each class have a single, clear responsibility? (SRP)
- [ ] Can new functionality be added without modifying existing code? (OCP)
- [ ] Can derived classes be substituted for base classes? (LSP)
- [ ] Are interfaces focused and specific to client needs? (ISP)
- [ ] Do high-level modules depend on abstractions? (DIP)

---

## Conclusion

The SOLID principles are fundamental guidelines that help create maintainable, flexible, and robust object-oriented software. By following these principles:

✅ **Your code becomes more maintainable** - Changes are localized and predictable  
✅ **Your system becomes more flexible** - Easy to extend and modify  
✅ **Your code becomes more testable** - Dependencies can be easily mocked  
✅ **Your architecture becomes more robust** - Loose coupling and high cohesion  
✅ **Your team becomes more productive** - Clear responsibilities and interfaces  

Remember: SOLID principles are guidelines, not rigid rules. Apply them judiciously based on your specific context and requirements. The goal is to create better software, not to follow principles blindly.

### Further Reading
- "Clean Code" by Robert C. Martin
- "Clean Architecture" by Robert C. Martin
- "Effective C++" by Scott Meyers
- "Modern C++ Design" by Andrei Alexandrescu

---

*Last updated: July 19, 2025*
