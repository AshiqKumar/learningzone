#include "StudentView.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

// Console colors (ANSI escape codes)
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Display methods
void StudentView::displayWelcomeMessage() const {
    clearScreen();
    printHeader("Student Management System");
    std::cout << CYAN << "Welcome to the Student Management System!" << RESET << std::endl;
    std::cout << "This system demonstrates the MVC (Model-View-Controller) pattern." << std::endl;
    printSeparator();
}

void StudentView::displayMenu() const {
    std::cout << std::endl;
    printHeader("Main Menu");
    std::cout << "1. " << GREEN << "Add Student" << RESET << std::endl;
    std::cout << "2. " << BLUE << "View All Students" << RESET << std::endl;
    std::cout << "3. " << YELLOW << "Find Student by ID" << RESET << std::endl;
    std::cout << "4. " << CYAN << "Search Students by Name" << RESET << std::endl;
    std::cout << "5. " << MAGENTA << "Update Student" << RESET << std::endl;
    std::cout << "6. " << RED << "Remove Student" << RESET << std::endl;
    std::cout << "7. " << WHITE << "Show Statistics" << RESET << std::endl;
    std::cout << "8. " << RED << BOLD << "Clear All Students" << RESET << std::endl;
    std::cout << "0. " << RED << "Exit" << RESET << std::endl;
    printSeparator();
}

void StudentView::displayAllStudents(const std::vector<Student>& students) const {
    if (students.empty()) {
        printInfo("No students found in the system.");
        return;
    }

    printHeader("All Students");
    printStudentTable(students);
}

void StudentView::displayStudent(const Student& student) const {
    printHeader("Student Details");
    std::cout << std::left << std::setw(15) << "ID:" << student.getId() << std::endl;
    std::cout << std::left << std::setw(15) << "Name:" << student.getName() << std::endl;
    std::cout << std::left << std::setw(15) << "Email:" << student.getEmail() << std::endl;
    std::cout << std::left << std::setw(15) << "Age:" << student.getAge() << std::endl;
    std::cout << std::left << std::setw(15) << "GPA:" << std::fixed << std::setprecision(2) << student.getGpa() << std::endl;
}

void StudentView::displayStudentCount(size_t count) const {
    std::cout << CYAN << "Total Students: " << count << RESET << std::endl;
}

void StudentView::displayAverageGpa(double avgGpa) const {
    std::cout << YELLOW << "Average GPA: " << std::fixed << std::setprecision(2) << avgGpa << RESET << std::endl;
}

void StudentView::displayTopStudent(const Student* student) const {
    if (student) {
        std::cout << GREEN << "Top Student (Highest GPA): " << RESET << std::endl;
        std::cout << "  " << student->getName() << " (ID: " << student->getId() 
                  << ", GPA: " << std::fixed << std::setprecision(2) << student->getGpa() << ")" << std::endl;
    } else {
        printInfo("No students available.");
    }
}

void StudentView::displaySearchResults(const std::vector<Student>& students, const std::string& searchTerm) const {
    if (students.empty()) {
        printInfo("No students found matching: '" + searchTerm + "'");
        return;
    }

    printHeader("Search Results for: '" + searchTerm + "'");
    printStudentTable(students);
}

void StudentView::displayGoodbye() const {
    clearScreen();
    printHeader("Goodbye!");
    std::cout << CYAN << "Thank you for using the Student Management System!" << RESET << std::endl;
    std::cout << "This MVC pattern demonstration is now complete." << std::endl;
}

// Input methods
int StudentView::getUserChoice() const {
    return getIntInput("Enter your choice: ");
}

std::string StudentView::getStringInput(const std::string& prompt) const {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int StudentView::getIntInput(const std::string& prompt) const {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printError("Invalid input. Please enter a valid number.");
        }
    }
}

double StudentView::getDoubleInput(const std::string& prompt) const {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printError("Invalid input. Please enter a valid number.");
        }
    }
}

StudentView::StudentInput StudentView::getNewStudentData() const {
    printHeader("Add New Student");
    StudentInput input;
    
    input.name = getStringInput("Enter student name: ");
    input.email = getStringInput("Enter student email: ");
    input.age = getIntInput("Enter student age: ");
    input.gpa = getDoubleInput("Enter student GPA (0.0-4.0): ");
    
    return input;
}

StudentView::StudentInput StudentView::getUpdatedStudentData(const Student& currentStudent) const {
    printHeader("Update Student Information");
    std::cout << "Current student data:" << std::endl;
    displayStudent(currentStudent);
    std::cout << std::endl << "Enter new information (or press Enter to keep current values):" << std::endl;
    
    StudentInput input;
    
    std::string tempInput = getStringInput("Name [" + currentStudent.getName() + "]: ");
    input.name = tempInput.empty() ? currentStudent.getName() : tempInput;
    
    tempInput = getStringInput("Email [" + currentStudent.getEmail() + "]: ");
    input.email = tempInput.empty() ? currentStudent.getEmail() : tempInput;
    
    std::cout << "Age [" << currentStudent.getAge() << "]: ";
    std::string ageStr;
    std::getline(std::cin, ageStr);
    input.age = ageStr.empty() ? currentStudent.getAge() : std::stoi(ageStr);
    
    std::cout << "GPA [" << std::fixed << std::setprecision(2) << currentStudent.getGpa() << "]: ";
    std::string gpaStr;
    std::getline(std::cin, gpaStr);
    input.gpa = gpaStr.empty() ? currentStudent.getGpa() : std::stod(gpaStr);
    
    return input;
}

int StudentView::getStudentIdInput() const {
    return getIntInput("Enter student ID: ");
}

// Feedback methods
void StudentView::showOperationSuccess(const std::string& operation) const {
    printSuccess(operation + " completed successfully!");
}

void StudentView::showOperationFailure(const std::string& operation, const std::string& reason) const {
    std::string message = operation + " failed!";
    if (!reason.empty()) {
        message += " Reason: " + reason;
    }
    printError(message);
}

void StudentView::showValidationError(const std::string& field, const std::string& requirement) const {
    printError("Validation error in " + field + ": " + requirement);
}

// Observer pattern implementation
void StudentView::onStudentAdded(const Student& student) {
    std::cout << GREEN << "✓ Student added: " << student.getName() 
              << " (ID: " << student.getId() << ")" << RESET << std::endl;
}

void StudentView::onStudentUpdated(const Student& student) {
    std::cout << YELLOW << "✓ Student updated: " << student.getName() 
              << " (ID: " << student.getId() << ")" << RESET << std::endl;
}

void StudentView::onStudentRemoved(int studentId) {
    std::cout << RED << "✓ Student removed (ID: " << studentId << ")" << RESET << std::endl;
}

void StudentView::onModelCleared() {
    std::cout << RED << "✓ All students have been cleared from the system." << RESET << std::endl;
}

// Helper methods
void StudentView::printHeader(const std::string& title) const {
    std::cout << std::endl << BOLD << BLUE << "=== " << title << " ===" << RESET << std::endl;
}

void StudentView::printSeparator() const {
    std::cout << std::string(50, '-') << std::endl;
}

void StudentView::printStudentTable(const std::vector<Student>& students) const {
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(25) << "Email" 
              << std::setw(5) << "Age" 
              << std::setw(6) << "GPA" << std::endl;
    std::cout << std::string(61, '-') << std::endl;
    
    for (const auto& student : students) {
        std::cout << std::left << std::setw(5) << student.getId()
                  << std::setw(20) << student.getName()
                  << std::setw(25) << student.getEmail()
                  << std::setw(5) << student.getAge()
                  << std::setw(6) << std::fixed << std::setprecision(2) << student.getGpa() << std::endl;
    }
}

void StudentView::printError(const std::string& message) const {
    std::cout << RED << "❌ Error: " << message << RESET << std::endl;
}

void StudentView::printSuccess(const std::string& message) const {
    std::cout << GREEN << "✅ " << message << RESET << std::endl;
}

void StudentView::printInfo(const std::string& message) const {
    std::cout << CYAN << "ℹ️  " << message << RESET << std::endl;
}

void StudentView::clearScreen() const {
    // Cross-platform clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void StudentView::waitForUserInput() const {
    std::cout << std::endl << "Press Enter to continue...";
    std::cin.ignore();
}
