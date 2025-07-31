#!/bin/bash

# Build script for Advanced C++20 Modules Examples
echo "Building Advanced C++20 Modules Example..."

# Check if we're on Windows (Git Bash) or Unix
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo "Windows detected - using MSVC with advanced C++20 features..."
    
    # MSVC with modules and concepts
    echo "Step 1: Compiling advanced module interface..."
    cl /EHsc /std:c++20 /experimental:module AdvancedExamples/data_processor.cppm /c
    
    if [ $? -ne 0 ]; then
        echo "❌ Advanced module interface compilation failed!"
        echo "Make sure you have Visual Studio 2019 16.8+ or Visual Studio 2022"
        exit 1
    fi
    
    echo "Step 2: Building advanced demo executable..."
    cl /EHsc /std:c++20 data_processor.obj AdvancedExamples/demo_advanced.cpp /Fe:advanced_demo.exe
    
    if [ $? -eq 0 ]; then
        echo "✅ Advanced C++20 modules example built successfully!"
        echo "Run with: advanced_demo.exe"
    else
        echo "❌ Advanced demo build failed!"
        exit 1
    fi
    
elif command -v g++ &> /dev/null; then
    echo "Linux/macOS detected - checking GCC version for advanced features..."
    
    # Check GCC version for concepts and modules support
    GCC_VERSION=$(g++ -dumpversion | cut -d. -f1)
    if [ "$GCC_VERSION" -lt 11 ]; then
        echo "❌ GCC 11+ required for C++20 concepts and modules (found GCC $GCC_VERSION)"
        echo "Please install GCC 11 or newer"
        exit 1
    fi
    
    echo "GCC $GCC_VERSION detected - building with advanced C++20 features..."
    
    # GCC with concepts and modules
    echo "Step 1: Compiling advanced module interface..."
    g++ -std=c++20 -fmodules-ts -fconcepts -Wall -Wextra -c AdvancedExamples/data_processor.cppm
    
    if [ $? -ne 0 ]; then
        echo "❌ Advanced module interface compilation failed!"
        echo "Note: C++20 concepts and modules support in GCC is still evolving"
        echo "Try using -fconcepts-ts flag if -fconcepts doesn't work"
        exit 1
    fi
    
    echo "Step 2: Building advanced demo executable..."
    g++ -std=c++20 -fmodules-ts -fconcepts -Wall -Wextra -o advanced_demo AdvancedExamples/demo_advanced.cpp
    
    if [ $? -eq 0 ]; then
        echo "✅ Advanced C++20 modules example built successfully!"
        echo "Run with: ./advanced_demo"
    else
        echo "❌ Advanced demo build failed!"
        exit 1
    fi
    
elif command -v clang++ &> /dev/null; then
    echo "Using Clang - checking version for advanced C++20 features..."
    
    # Check Clang version for concepts and modules support
    CLANG_VERSION=$(clang++ --version | grep -oP 'clang version \K[0-9]+' | head -1)
    if [ "$CLANG_VERSION" -lt 15 ]; then
        echo "❌ Clang 15+ recommended for full C++20 support (found Clang $CLANG_VERSION)"
        echo "Some features may not work with older versions"
    fi
    
    echo "Clang $CLANG_VERSION detected - building with advanced C++20 features..."
    
    # Clang with concepts and modules
    echo "Step 1: Precompiling advanced module interface..."
    clang++ -std=c++20 --precompile AdvancedExamples/data_processor.cppm -o data_processor.pcm
    
    if [ $? -ne 0 ]; then
        echo "❌ Advanced module precompilation failed!"
        echo "Make sure you have Clang 15+ with full C++20 support"
        exit 1
    fi
    
    echo "Step 2: Building advanced demo executable..."
    clang++ -std=c++20 -fprebuilt-module-path=. -Wall -Wextra -o advanced_demo AdvancedExamples/demo_advanced.cpp
    
    if [ $? -eq 0 ]; then
        echo "✅ Advanced C++20 modules example built successfully!"
        echo "Run with: ./advanced_demo"
    else
        echo "❌ Advanced demo build failed!"
        exit 1
    fi
    
else
    echo "❌ No suitable C++ compiler found!"
    echo "Please install:"
    echo "  - GCC 11+ for Linux/macOS (with experimental modules support)"
    echo "  - Clang 15+ for Linux/macOS (recommended for best C++20 support)"
    echo "  - Visual Studio 2019 16.8+ or Visual Studio 2022 for Windows"
    exit 1
fi

echo ""
echo "🚀 Advanced C++20 Modules Features Demonstrated:"
echo "  ✨ C++20 Concepts (Numeric, Comparable, Printable)"
echo "  ✨ Complex template metaprogramming"
echo "  ✨ Perfect forwarding and universal references"
echo "  ✨ SFINAE with requires clauses"
echo "  ✨ Fluent interfaces (method chaining)"
echo "  ✨ Lambda expressions and functional programming"
echo "  ✨ Auto type deduction and decltype"
echo "  ✨ Template constraints and specializations"
echo "  ✨ Modern STL algorithms integration"
echo "  ✨ Clean module interfaces for complex templates"
echo "  ✨ C++20 std::format and localization"
echo "  ✨ Custom formatters for user-defined types"

echo ""
echo "📋 Example Operations Available:"
echo "  • Statistical analysis (sum, mean, min, max)"
echo "  • Functional operations (filter, transform, fold)"
echo "  • Data manipulation (sort, reverse, unique)"
echo "  • Partitioning and grouping"
echo "  • Sequence generation"
echo "  • Advanced algorithms (merge, count_if)"
echo "  • Type-safe operations with concepts"
echo "  • std::format with custom types"
echo "  • Locale-aware number and currency formatting"
echo "  • Multilingual message support"
echo "  • Performance comparisons"

echo ""
echo "⚠️  Advanced Features Note:"
echo "  • C++20 Concepts: Full support in GCC 10+, Clang 10+, MSVC 2019+"
echo "  • Modules: Varying support levels across compilers"
echo "  • Template constraints: Best support in latest compiler versions"
echo "  • Some features may require specific compiler flags"
