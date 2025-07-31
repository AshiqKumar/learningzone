#!/bin/bash

# Build script for Traditional Headers approach
echo "Building Traditional Headers Example..."

# Check if we're on Windows (Git Bash) or Unix
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo "Windows detected - using MSVC..."
    
    # MSVC build
    cl /EHsc /std:c++17 traditional_headers/main_traditional.cpp traditional_headers/calculator.cpp /Fe:traditional_demo.exe
    
    if [ $? -eq 0 ]; then
        echo "✅ Traditional headers example built successfully!"
        echo "Run with: traditional_demo.exe"
    else
        echo "❌ Build failed!"
        exit 1
    fi
    
elif command -v g++ &> /dev/null; then
    echo "Linux/macOS detected - using GCC..."
    
    # GCC build
    g++ -std=c++17 -Wall -Wextra -o traditional_demo traditional_headers/main_traditional.cpp traditional_headers/calculator.cpp
    
    if [ $? -eq 0 ]; then
        echo "✅ Traditional headers example built successfully!"
        echo "Run with: ./traditional_demo"
    else
        echo "❌ Build failed!"
        exit 1
    fi
    
elif command -v clang++ &> /dev/null; then
    echo "Using Clang..."
    
    # Clang build
    clang++ -std=c++17 -Wall -Wextra -o traditional_demo traditional_headers/main_traditional.cpp traditional_headers/calculator.cpp
    
    if [ $? -eq 0 ]; then
        echo "✅ Traditional headers example built successfully!"
        echo "Run with: ./traditional_demo"
    else
        echo "❌ Build failed!"
        exit 1
    fi
    
else
    echo "❌ No suitable C++ compiler found!"
    echo "Please install GCC, Clang, or use MSVC on Windows"
    exit 1
fi

echo ""
echo "🔍 Traditional Headers Demo Features:"
echo "  - Shows macro pollution problems"
echo "  - Demonstrates accidental function exposure"
echo "  - Illustrates header compilation overhead"
echo "  - All template code visible in headers"
