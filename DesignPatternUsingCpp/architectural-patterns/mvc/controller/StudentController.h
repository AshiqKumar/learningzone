#pragma once
#include "../model/StudentModel.h"
#include "../view/StudentView.h"
#include <memory>

/**
 * @brief StudentController class - coordinates between Model and View
 * 
 * This class represents the Controller in MVC architecture.
 * It handles user input, invokes appropriate model operations,
 * and updates the view accordingly.
 */
class StudentController {
private:
    std::unique_ptr<StudentModel> model;
    std::unique_ptr<StudentView> view;
    bool isRunning;

    // Menu action handlers
    void handleAddStudent();
    void handleViewAllStudents();
    void handleFindStudentById();
    void handleSearchStudentsByName();
    void handleUpdateStudent();
    void handleRemoveStudent();
    void handleShowStatistics();
    void handleClearAllStudents();
    void handleExit();

    // Input validation helpers
    bool validateStudentInput(const StudentView::StudentInput& input);
    void showValidationErrors(const StudentView::StudentInput& input);

public:
    StudentController();
    ~StudentController() = default;

    // Main application control
    void run();
    void stop();

    // Utility methods
    bool isApplicationRunning() const;
    
    // For testing purposes
    StudentModel* getModel() const { return model.get(); }
    StudentView* getView() const { return view.get(); }
};
