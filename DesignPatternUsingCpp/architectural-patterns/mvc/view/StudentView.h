#pragma once
#include "../model/Student.h"
#include "../model/StudentModel.h"
#include <vector>
#include <string>

/**
 * @brief StudentView class - handles the presentation layer
 * 
 * This class represents the View in MVC architecture.
 * It's responsible for displaying information to the user and
 * gathering user input.
 */
class StudentView : public ModelObserver {
private:
    // Console formatting helpers
    void printHeader(const std::string& title) const;
    void printSeparator() const;
    void printStudentTable(const std::vector<Student>& students) const;
    void printError(const std::string& message) const;
    void printSuccess(const std::string& message) const;
    void printInfo(const std::string& message) const;

public:
    StudentView() = default;
    ~StudentView() = default;

    // Display methods
    void displayWelcomeMessage() const;
    void displayMenu() const;
    void displayAllStudents(const std::vector<Student>& students) const;
    void displayStudent(const Student& student) const;
    void displayStudentCount(size_t count) const;
    void displayAverageGpa(double avgGpa) const;
    void displayTopStudent(const Student* student) const;
    void displaySearchResults(const std::vector<Student>& students, const std::string& searchTerm) const;
    void displayGoodbye() const;

    // Input gathering methods
    int getUserChoice() const;
    std::string getStringInput(const std::string& prompt) const;
    int getIntInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
    
    // Student data input
    struct StudentInput {
        std::string name;
        std::string email;
        int age;
        double gpa;
    };
    StudentInput getNewStudentData() const;
    StudentInput getUpdatedStudentData(const Student& currentStudent) const;
    int getStudentIdInput() const;

    // Feedback methods
    void showOperationSuccess(const std::string& operation) const;
    void showOperationFailure(const std::string& operation, const std::string& reason = "") const;
    void showValidationError(const std::string& field, const std::string& requirement) const;

    // Observer pattern implementation
    void onStudentAdded(const Student& student) override;
    void onStudentUpdated(const Student& student) override;
    void onStudentRemoved(int studentId) override;
    void onModelCleared() override;

    // Utility methods
    void clearScreen() const;
    void waitForUserInput() const;
};
