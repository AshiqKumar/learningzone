/**
 * @file test_mvc.cpp
 * @brief Simple unit tests for MVC components
 * 
 * This file demonstrates how the MVC pattern facilitates testing
 * by allowing each component to be tested independently.
 */

#include "model/Student.h"
#include "model/StudentModel.h"
#include "view/StudentView.h"
#include "controller/StudentController.h"
#include <iostream>
#include <cassert>
#include <vector>

// Simple test framework
class TestRunner {
private:
    int totalTests = 0;
    int passedTests = 0;
    
public:
    void runTest(const std::string& testName, std::function<bool()> testFunc) {
        totalTests++;
        std::cout << "Running " << testName << "... ";
        
        try {
            if (testFunc()) {
                std::cout << "✅ PASSED" << std::endl;
                passedTests++;
            } else {
                std::cout << "❌ FAILED" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "❌ EXCEPTION: " << e.what() << std::endl;
        }
    }
    
    void printSummary() {
        std::cout << std::endl << "=== Test Summary ===" << std::endl;
        std::cout << "Total tests: " << totalTests << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << (totalTests - passedTests) << std::endl;
        std::cout << "Success rate: " << (100.0 * passedTests / totalTests) << "%" << std::endl;
    }
};

// Test Model Layer
bool testStudentCreation() {
    Student student(1, "John Doe", "john@email.com", 20, 3.5);
    return student.getId() == 1 && 
           student.getName() == "John Doe" && 
           student.getEmail() == "john@email.com" &&
           student.getAge() == 20 &&
           student.getGpa() == 3.5;
}

bool testStudentValidation() {
    Student validStudent(1, "John Doe", "john@email.com", 20, 3.5);
    Student invalidStudent(0, "", "", -1, 5.0);
    
    return validStudent.isValid() && !invalidStudent.isValid();
}

bool testStudentModelOperations() {
    StudentModel model;
    
    // Test adding students
    bool added = model.addStudent("Alice", "alice@email.com", 20, 3.8);
    if (!added) return false;
    
    // Test finding students
    const Student* found = model.findStudent(1);
    if (!found || found->getName() != "Alice") return false;
    
    // Test updating students
    bool updated = model.updateStudent(1, "Alice Smith", "alice.smith@email.com", 21, 3.9);
    if (!updated) return false;
    
    found = model.findStudent(1);
    if (!found || found->getName() != "Alice Smith") return false;
    
    // Test statistics
    if (model.getStudentCount() != 1) return false;
    if (model.getAverageGpa() != 3.9) return false;
    
    return true;
}

bool testModelObserverPattern() {
    StudentModel model;
    
    // Simple observer to track notifications
    class TestObserver : public ModelObserver {
    public:
        int addedCount = 0;
        int updatedCount = 0;
        int removedCount = 0;
        int clearedCount = 0;
        
        void onStudentAdded(const Student&) override { addedCount++; }
        void onStudentUpdated(const Student&) override { updatedCount++; }
        void onStudentRemoved(int) override { removedCount++; }
        void onModelCleared() override { clearedCount++; }
    };
    
    TestObserver observer;
    model.addObserver(&observer);
    
    model.addStudent("Test", "test@email.com", 20, 3.0);
    model.updateStudent(1, "Test Updated", "test@email.com", 20, 3.5);
    model.removeStudent(1);
    model.clearAllStudents();
    
    return observer.addedCount == 1 && 
           observer.updatedCount == 1 && 
           observer.removedCount == 1 && 
           observer.clearedCount == 1;
}

// Test search functionality
bool testStudentSearch() {
    StudentModel model;
    model.addStudent("Alice Johnson", "alice@email.com", 20, 3.8);
    model.addStudent("Bob Johnson", "bob@email.com", 22, 3.2);
    model.addStudent("Charlie Smith", "charlie@email.com", 19, 3.9);
    
    // Search by name
    auto results = model.findStudentsByName("Johnson");
    if (results.size() != 2) return false;
    
    // Search by GPA
    auto highPerformers = model.getStudentsWithGpaAbove(3.5);
    if (highPerformers.size() != 2) return false;
    
    return true;
}

// Test Controller (basic functionality)
bool testControllerInitialization() {
    StudentController controller;
    return controller.getModel() != nullptr && 
           controller.getView() != nullptr;
}

int main() {
    std::cout << "=== MVC Pattern Unit Tests ===" << std::endl << std::endl;
    
    TestRunner runner;
    
    // Model layer tests
    runner.runTest("Student Creation", testStudentCreation);
    runner.runTest("Student Validation", testStudentValidation);
    runner.runTest("StudentModel Operations", testStudentModelOperations);
    runner.runTest("Observer Pattern", testModelObserverPattern);
    runner.runTest("Student Search", testStudentSearch);
    
    // Controller tests
    runner.runTest("Controller Initialization", testControllerInitialization);
    
    runner.printSummary();
    
    std::cout << std::endl << "Note: These tests demonstrate how MVC pattern" << std::endl;
    std::cout << "enables easy unit testing of individual components." << std::endl;
    
    return 0;
}

/*
 * Testing Benefits with MVC Pattern:
 * 
 * 1. Model Testing:
 *    - Business logic can be tested independently
 *    - Data operations are isolated from UI
 *    - Observer pattern can be verified
 * 
 * 2. View Testing:
 *    - UI components can be tested with mock data
 *    - Display logic is separate from business logic
 *    - Input validation can be tested independently
 * 
 * 3. Controller Testing:
 *    - Application flow can be tested
 *    - Integration between Model and View can be verified
 *    - User actions can be simulated
 * 
 * 4. Integration Testing:
 *    - Complete workflows can be tested
 *    - Observer notifications can be verified
 *    - End-to-end scenarios can be validated
 */
