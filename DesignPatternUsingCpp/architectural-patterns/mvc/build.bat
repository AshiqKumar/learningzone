@echo off
REM Build script for Student Management System (Windows)
REM This script compiles the MVC pattern example

echo Building Student Management System (MVC Pattern)...
echo.

REM Create output directory if it doesn't exist
if not exist "bin" mkdir bin

REM Compile all source files
g++ -std=c++17 -Wall -Wextra -O2 -I. ^
    model/Student.cpp ^
    model/StudentModel.cpp ^
    view/StudentView.cpp ^
    controller/StudentController.cpp ^
    main.cpp ^
    -o bin/student_management.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✅ Build successful!
    echo.
    echo To run the application:
    echo   bin\student_management.exe
    echo.
    echo Or use: build.bat run
) else (
    echo.
    echo ❌ Build failed!
    echo Check the error messages above.
)

REM If 'run' parameter is passed, run the application
if "%1"=="run" (
    echo.
    echo Running the application...
    echo.
    bin\student_management.exe
)
