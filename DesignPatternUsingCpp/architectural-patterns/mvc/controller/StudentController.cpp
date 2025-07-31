#include "StudentController.h"
#include <iostream>
#include <algorithm>
#include <cctype>

StudentController::StudentController() : isRunning(false) {
    // Initialize Model and View
    model = std::make_unique<StudentModel>();
    view = std::make_unique<StudentView>();
    
    // Register view as observer of model
    model->addObserver(view.get());
    
    // Add some sample data for demonstration
    model->addStudent("Alice Johnson", "alice.johnson@email.com", 20, 3.85);
    model->addStudent("Bob Smith", "bob.smith@email.com", 22, 3.42);
    model->addStudent("Charlie Brown", "charlie.brown@email.com", 19, 3.91);
}

void StudentController::run() {
    isRunning = true;
    view->displayWelcomeMessage();
    
    while (isRunning) {
        view->displayMenu();
        int choice = view->getUserChoice();
        
        switch (choice) {
            case 1: handleAddStudent(); break;
            case 2: handleViewAllStudents(); break;
            case 3: handleFindStudentById(); break;
            case 4: handleSearchStudentsByName(); break;
            case 5: handleUpdateStudent(); break;
            case 6: handleRemoveStudent(); break;
            case 7: handleShowStatistics(); break;
            case 8: handleClearAllStudents(); break;
            case 0: handleExit(); break;
            default:
                view->showOperationFailure("Invalid choice", "Please select a number from 0-8");
                break;
        }
        
        if (isRunning) {
            view->waitForUserInput();
        }
    }
}

void StudentController::stop() {
    isRunning = false;
}

bool StudentController::isApplicationRunning() const {
    return isRunning;
}

// Menu action handlers
void StudentController::handleAddStudent() {
    auto input = view->getNewStudentData();
    
    if (!validateStudentInput(input)) {
        showValidationErrors(input);
        return;
    }
    
    bool success = model->addStudent(input.name, input.email, input.age, input.gpa);
    
    if (success) {
        view->showOperationSuccess("Add student");
    } else {
        view->showOperationFailure("Add student", "Student data validation failed");
    }
}

void StudentController::handleViewAllStudents() {
    auto students = model->getAllStudents();
    view->displayAllStudents(students);
}

void StudentController::handleFindStudentById() {
    int id = view->getStudentIdInput();
    const Student* student = model->findStudent(id);
    
    if (student) {
        view->displayStudent(*student);
    } else {
        view->showOperationFailure("Find student", "Student with ID " + std::to_string(id) + " not found");
    }
}

void StudentController::handleSearchStudentsByName() {
    std::string searchTerm = view->getStringInput("Enter name to search: ");
    
    if (searchTerm.empty()) {
        view->showOperationFailure("Search", "Search term cannot be empty");
        return;
    }
    
    auto students = model->findStudentsByName(searchTerm);
    view->displaySearchResults(students, searchTerm);
}

void StudentController::handleUpdateStudent() {
    int id = view->getStudentIdInput();
    const Student* existingStudent = model->findStudent(id);
    
    if (!existingStudent) {
        view->showOperationFailure("Update student", "Student with ID " + std::to_string(id) + " not found");
        return;
    }
    
    auto input = view->getUpdatedStudentData(*existingStudent);
    
    if (!validateStudentInput(input)) {
        showValidationErrors(input);
        return;
    }
    
    bool success = model->updateStudent(id, input.name, input.email, input.age, input.gpa);
    
    if (success) {
        view->showOperationSuccess("Update student");
    } else {
        view->showOperationFailure("Update student", "Student data validation failed");
    }
}

void StudentController::handleRemoveStudent() {
    int id = view->getStudentIdInput();
    
    if (!model->studentExists(id)) {
        view->showOperationFailure("Remove student", "Student with ID " + std::to_string(id) + " not found");
        return;
    }
    
    bool success = model->removeStudent(id);
    
    if (success) {
        view->showOperationSuccess("Remove student");
    } else {
        view->showOperationFailure("Remove student", "Failed to remove student");
    }
}

void StudentController::handleShowStatistics() {
    size_t count = model->getStudentCount();
    double avgGpa = model->getAverageGpa();
    const Student* topStudent = model->getTopStudent();
    
    std::cout << std::endl << "=== Student Statistics ===" << std::endl;
    view->displayStudentCount(count);
    
    if (count > 0) {
        view->displayAverageGpa(avgGpa);
        view->displayTopStudent(topStudent);
        
        // Additional statistics
        auto highPerformers = model->getStudentsWithGpaAbove(3.5);
        std::cout << "High Performers (GPA ≥ 3.5): " << highPerformers.size() << std::endl;
    }
}

void StudentController::handleClearAllStudents() {
    std::string confirmation = view->getStringInput("Are you sure you want to clear all students? (yes/no): ");
    
    // Convert to lowercase for comparison
    std::transform(confirmation.begin(), confirmation.end(), confirmation.begin(), ::tolower);
    
    if (confirmation == "yes" || confirmation == "y") {
        model->clearAllStudents();
        view->showOperationSuccess("Clear all students");
    } else {
        std::cout << "Operation cancelled." << std::endl;
    }
}

void StudentController::handleExit() {
    view->displayGoodbye();
    stop();
}

// Input validation helpers
bool StudentController::validateStudentInput(const StudentView::StudentInput& input) {
    return !input.name.empty() &&
           !input.email.empty() &&
           input.email.find('@') != std::string::npos &&  // Basic email validation
           input.age > 0 && input.age < 120 &&
           input.gpa >= 0.0 && input.gpa <= 4.0;
}

void StudentController::showValidationErrors(const StudentView::StudentInput& input) {
    if (input.name.empty()) {
        view->showValidationError("Name", "Name cannot be empty");
    }
    
    if (input.email.empty()) {
        view->showValidationError("Email", "Email cannot be empty");
    } else if (input.email.find('@') == std::string::npos) {
        view->showValidationError("Email", "Email must contain '@' symbol");
    }
    
    if (input.age <= 0 || input.age >= 120) {
        view->showValidationError("Age", "Age must be between 1 and 119");
    }
    
    if (input.gpa < 0.0 || input.gpa > 4.0) {
        view->showValidationError("GPA", "GPA must be between 0.0 and 4.0");
    }
}
