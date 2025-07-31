#include "StudentModel.h"
#include <algorithm>
#include <numeric>

StudentModel::StudentModel() : nextId(1) {}

// Observer pattern implementation
void StudentModel::addObserver(ModelObserver* observer) {
    if (observer) {
        observers.push_back(observer);
    }
}

void StudentModel::removeObserver(ModelObserver* observer) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),
        observers.end()
    );
}

void StudentModel::notifyStudentAdded(const Student& student) {
    for (auto observer : observers) {
        observer->onStudentAdded(student);
    }
}

void StudentModel::notifyStudentUpdated(const Student& student) {
    for (auto observer : observers) {
        observer->onStudentUpdated(student);
    }
}

void StudentModel::notifyStudentRemoved(int studentId) {
    for (auto observer : observers) {
        observer->onStudentRemoved(studentId);
    }
}

void StudentModel::notifyModelCleared() {
    for (auto observer : observers) {
        observer->onModelCleared();
    }
}

// Student management methods
bool StudentModel::addStudent(const std::string& name, const std::string& email, int age, double gpa) {
    Student newStudent(nextId, name, email, age, gpa);
    
    if (!isValidStudent(newStudent)) {
        return false;
    }
    
    students.push_back(newStudent);
    nextId++;
    
    notifyStudentAdded(newStudent);
    return true;
}

bool StudentModel::updateStudent(int id, const std::string& name, const std::string& email, int age, double gpa) {
    int index = findStudentIndex(id);
    if (index == -1) {
        return false;
    }
    
    Student updatedStudent(id, name, email, age, gpa);
    if (!isValidStudent(updatedStudent)) {
        return false;
    }
    
    students[index] = updatedStudent;
    notifyStudentUpdated(updatedStudent);
    return true;
}

bool StudentModel::removeStudent(int id) {
    int index = findStudentIndex(id);
    if (index == -1) {
        return false;
    }
    
    students.erase(students.begin() + index);
    notifyStudentRemoved(id);
    return true;
}

void StudentModel::clearAllStudents() {
    students.clear();
    nextId = 1;
    notifyModelCleared();
}

// Query methods
Student* StudentModel::findStudent(int id) {
    int index = findStudentIndex(id);
    return (index != -1) ? &students[index] : nullptr;
}

const Student* StudentModel::findStudent(int id) const {
    int index = findStudentIndex(id);
    return (index != -1) ? &students[index] : nullptr;
}

std::vector<Student> StudentModel::findStudentsByName(const std::string& name) const {
    std::vector<Student> result;
    for (const auto& student : students) {
        if (student.getName().find(name) != std::string::npos) {
            result.push_back(student);
        }
    }
    return result;
}

std::vector<Student> StudentModel::getStudentsWithGpaAbove(double minGpa) const {
    std::vector<Student> result;
    std::copy_if(students.begin(), students.end(), std::back_inserter(result),
                 [minGpa](const Student& s) { return s.getGpa() >= minGpa; });
    return result;
}

std::vector<Student> StudentModel::getAllStudents() const {
    return students;
}

// Statistics methods
size_t StudentModel::getStudentCount() const {
    return students.size();
}

double StudentModel::getAverageGpa() const {
    if (students.empty()) {
        return 0.0;
    }
    
    double sum = std::accumulate(students.begin(), students.end(), 0.0,
                                [](double acc, const Student& s) {
                                    return acc + s.getGpa();
                                });
    return sum / students.size();
}

Student* StudentModel::getTopStudent() const {
    if (students.empty()) {
        return nullptr;
    }
    
    auto maxIt = std::max_element(students.begin(), students.end(),
                                  [](const Student& a, const Student& b) {
                                      return a.getGpa() < b.getGpa();
                                  });
    
    return const_cast<Student*>(&(*maxIt));
}

// Helper methods
int StudentModel::findStudentIndex(int id) const {
    auto it = std::find_if(students.begin(), students.end(),
                          [id](const Student& s) { return s.getId() == id; });
    return (it != students.end()) ? std::distance(students.begin(), it) : -1;
}

bool StudentModel::isValidStudent(const Student& student) const {
    return student.isValid();
}

bool StudentModel::studentExists(int id) const {
    return findStudentIndex(id) != -1;
}
