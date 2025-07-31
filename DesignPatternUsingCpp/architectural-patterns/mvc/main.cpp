/**
 * @file main.cpp
 * @brief Main application entry point for Student Management System
 * 
 * This file demonstrates the Model-View-Controller (MVC) architectural pattern
 * in C++. The application manages student records with full CRUD (= Create, Read, Update, Delete) operations.
 * 
 * MVC Components:
 * - Model (StudentModel): Manages data and business logic
 * - View (StudentView): Handles user interface and presentation
 * - Controller (StudentController): Coordinates between Model and View
 * 
 * Design Patterns Used:
 * - MVC Architecture: Separation of concerns
 * - Observer Pattern: Model notifies View of changes
 * - Singleton-like Pattern: Single controller instance
 * 
 * Features:
 * - Add, update, delete students
 * - Search and filter students
 * - Real-time notifications
 * - Input validation
 * - Statistics and reporting
 * 
 *  Here’s why each of these design patterns is needed in your application:

    MVC Architecture:
    Separates the application into Model, View, and Controller. This makes your code modular, easier to maintain, test, and extend.
    Each part has a clear responsibility, reducing complexity and coupling.

    Observer Pattern:
    Allows the View to automatically update when the Model (data) changes. This decouples the data logic from the UI, 
    enabling real-time updates and making the system more flexible and scalable.

    Singleton-like Pattern:
    Ensures only one instance of the Controller exists, which centralizes control and coordination between Model and View. 
    This prevents conflicts, ensures consistent application flow, and avoids resource duplication.

These patterns together make your application robust, maintainable, and scalable.
 * @author Your Name
 * @date 2025
 */

#include "controller/StudentController.h"
#include <iostream>
#include <exception>

int main() {
    try {
        // Create and run the MVC application
        StudentController controller;
        controller.run();
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Application error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
}

/*
 * MVC Pattern Explanation:
 * 
 * 1. MODEL (StudentModel, Student):
 *    - Represents the data and business logic
 *    - Manages student records in memory
 *    - Provides CRUD operations
 *    - Implements observer pattern to notify views
 *    - Independent of user interface concerns
 * 
 * 2. VIEW (StudentView):
 *    - Handles all user interface interactions
 *    - Displays data to the user
 *    - Gathers user input
 *    - Observes model changes for automatic updates
 *    - No direct manipulation of data
 * 
 * 3. CONTROLLER (StudentController):
 *    - Mediates between Model and View
 *    - Handles user actions from View
 *    - Invokes appropriate Model operations
 *    - Controls application flow
 *    - Manages the main application loop
 * 
 * Benefits Demonstrated:
 * - Separation of Concerns: Each component has distinct responsibilities
 * - Modularity: Components can be modified independently
 * - Testability: Each component can be unit tested separately
 * - Reusability: Model can work with different views
 * - Maintainability: Changes are isolated to specific components
 * 
 * Observer Pattern Integration:
 * - StudentView implements ModelObserver interface
 * - StudentModel notifies all registered observers when data changes
 * - Automatic UI updates when model state changes
 * - Loose coupling between Model and View components
 */
