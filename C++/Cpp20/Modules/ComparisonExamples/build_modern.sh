#!/bin/bash

# Build script for C++20 Modules approach
echo "Building C++20 Modules Example..."

# Check if we're on Windows (Git Bash) or Unix
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo "Windows detected - using MSVC with C++20 modules..."
    
    # MSVC with modules (experimental)
    echo "Step 1: Compiling module interface..."
    cl /EHsc /std:c++20 /experimental:module modern_modules/calculator.cppm /c
    
    if [ $? -ne 0 ]; then
        echo "❌ Module interface compilation failed!"
        exit 1
    fi
    
    echo "Step 2: Building final executable..."
    cl /EHsc /std:c++20 modern_modules/calculator_impl.cpp calculator.obj modern_modules/main_modern.cpp /Fe:modern_demo.exe
    
    if [ $? -eq 0 ]; then
        echo "✅ C++20 modules example built successfully!"
        echo "Run with: modern_demo.exe"
    else
        echo "❌ Final build failed!"
        exit 1
    fi
    
elif command -v g++ &> /dev/null; then
    echo "Linux/macOS detected - checking GCC version..."
    
    # Check GCC version for modules support
    GCC_VERSION=$(g++ -dumpversion | cut -d. -f1)
    if [ "$GCC_VERSION" -lt 11 ]; then
        echo "❌ GCC 11+ required for modules support (found GCC $GCC_VERSION)"
        echo "Please install GCC 11 or newer, or try Clang 15+"
        exit 1
    fi
    
    echo "GCC $GCC_VERSION detected - building with modules..."
    
    # GCC modules build (may require special flags)
    echo "Step 1: Compiling module interface..."
    g++ -std=c++20 -fmodules-ts -Wall -Wextra -c modern_modules/calculator.cppm
    
    if [ $? -ne 0 ]; then
        echo "❌ Module interface compilation failed!"
        echo "Note: GCC modules support is still experimental"
        exit 1
    fi
    
    echo "Step 2: Building final executable..."
    g++ -std=c++20 -fmodules-ts -Wall -Wextra -o modern_demo modern_modules/main_modern.cpp modern_modules/calculator_impl.cpp
    
    if [ $? -eq 0 ]; then
        echo "✅ C++20 modules example built successfully!"
        echo "Run with: ./modern_demo"
    else
        echo "❌ Final build failed!"
        exit 1
    fi
    
elif command -v clang++ &> /dev/null; then
    echo "Using Clang - checking version..."
    
    # Check Clang version for modules support
    CLANG_VERSION=$(clang++ --version | grep -oP 'clang version \K[0-9]+' | head -1)
    if [ "$CLANG_VERSION" -lt 15 ]; then
        echo "❌ Clang 15+ required for good modules support (found Clang $CLANG_VERSION)"
        echo "Please install Clang 15 or newer"
        exit 1
    fi
    
    echo "Clang $CLANG_VERSION detected - building with modules..."
    
    # Clang modules build
    echo "Step 1: Precompiling module interface..."
    clang++ -std=c++20 --precompile modern_modules/calculator.cppm -o calculator.pcm
    
    if [ $? -ne 0 ]; then
        echo "❌ Module precompilation failed!"
        exit 1
    fi
    
    echo "Step 2: Building final executable..."
    clang++ -std=c++20 -fprebuilt-module-path=. -Wall -Wextra -o modern_demo modern_modules/main_modern.cpp modern_modules/calculator_impl.cpp
    
    if [ $? -eq 0 ]; then
        echo "✅ C++20 modules example built successfully!"
        echo "Run with: ./modern_demo"
    else
        echo "❌ Final build failed!"
        exit 1
    fi
    
else
    echo "❌ No suitable C++ compiler found!"
    echo "Please install:"
    echo "  - GCC 11+ for Linux/macOS"
    echo "  - Clang 15+ for Linux/macOS" 
    echo "  - Visual Studio 2019+ for Windows"
    exit 1
fi

echo ""
echo "🚀 C++20 Modules Demo Features:"
echo "  - Perfect encapsulation (no internal access)"
echo "  - No macro pollution"
echo "  - Fast compilation after initial build"
echo "  - Clean import syntax"
echo "  - Hidden template implementations"

echo ""
echo "⚠️  Note: C++20 modules support varies by compiler:"
echo "  - MSVC: Good support (experimental flag needed)"
echo "  - Clang 15+: Good support"
echo "  - GCC 11+: Experimental support"
