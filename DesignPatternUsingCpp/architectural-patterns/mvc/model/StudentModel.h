#pragma once
#include "Student.h"
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

/**
 * @brief Observer interface for Model notifications
 */
class ModelObserver {
public:
    virtual void onStudentAdded(const Student& student) = 0;
    virtual void onStudentUpdated(const Student& student) = 0;
    virtual void onStudentRemoved(int studentId) = 0;
    virtual void onModelCleared() = 0;
    virtual ~ModelObserver() = default;
};

/**
 * @brief StudentModel class - manages student data and business logic
 * 
 * This class represents the Model in MVC architecture.
 * It handles all student-related operations and notifies observers of changes.
 */
class StudentModel {
private:
    std::vector<Student> students;
    std::vector<ModelObserver*> observers;
    int nextId;

    // Helper methods
    int findStudentIndex(int id) const;
    void notifyStudentAdded(const Student& student);
    void notifyStudentUpdated(const Student& student);
    void notifyStudentRemoved(int studentId);
    void notifyModelCleared();

public:
    StudentModel();
    ~StudentModel() = default;

    // Observer pattern methods
    void addObserver(ModelObserver* observer);
    void removeObserver(ModelObserver* observer);

    // Student management methods
    bool addStudent(const std::string& name, const std::string& email, int age, double gpa);
    bool updateStudent(int id, const std::string& name, const std::string& email, int age, double gpa);
    bool removeStudent(int id);
    void clearAllStudents();

    // Query methods
    Student* findStudent(int id);
    const Student* findStudent(int id) const;
    std::vector<Student> findStudentsByName(const std::string& name) const;
    std::vector<Student> getStudentsWithGpaAbove(double minGpa) const;
    std::vector<Student> getAllStudents() const;
    
    // Statistics methods
    size_t getStudentCount() const;
    double getAverageGpa() const;
    Student* getTopStudent() const;  // Student with highest GPA
    
    // Validation
    bool isValidStudent(const Student& student) const;
    bool studentExists(int id) const;
};
