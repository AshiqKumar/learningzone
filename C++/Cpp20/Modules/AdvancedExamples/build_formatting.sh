#!/bin/bash

# Build script for C++20 Formatting and Localization Example
echo "Building C++20 Formatting & Localization Example..."

# Check if we're on Windows (Git Bash) or Unix
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    echo "Windows detected - using MSVC with C++20 formatting..."
    
    # MSVC with modules and formatting
    echo "Step 1: Compiling formatting module interface..."
    cl /EHsc /std:c++20 /experimental:module AdvancedExamples/formatting_localization.cppm /c
    
    if [ $? -ne 0 ]; then
        echo "❌ Formatting module interface compilation failed!"
        echo "Make sure you have Visual Studio 2019 16.10+ or Visual Studio 2022"
        echo "Note: std::format requires recent MSVC version"
        exit 1
    fi
    
    echo "Step 2: Building formatting demo executable..."
    cl /EHsc /std:c++20 formatting_localization.obj AdvancedExamples/demo_formatting.cpp /Fe:formatting_demo.exe
    
    if [ $? -eq 0 ]; then
        echo "✅ C++20 Formatting & Localization example built successfully!"
        echo "Run with: formatting_demo.exe"
    else
        echo "❌ Formatting demo build failed!"
        exit 1
    fi
    
elif command -v g++ &> /dev/null; then
    echo "Linux/macOS detected - checking GCC version for std::format..."
    
    # Check GCC version for std::format support
    GCC_VERSION=$(g++ -dumpversion | cut -d. -f1)
    if [ "$GCC_VERSION" -lt 13 ]; then
        echo "⚠️  GCC 13+ recommended for full std::format support (found GCC $GCC_VERSION)"
        echo "Some formatting features may not be available"
        echo "Consider using Clang 14+ or upgrading GCC"
    fi
    
    echo "GCC $GCC_VERSION detected - building with formatting support..."
    
    # GCC with formatting
    echo "Step 1: Compiling formatting module interface..."
    g++ -std=c++20 -fmodules-ts -Wall -Wextra -c AdvancedExamples/formatting_localization.cppm
    
    if [ $? -ne 0 ]; then
        echo "❌ Formatting module interface compilation failed!"
        echo "Note: std::format support in GCC is still evolving"
        echo "You may need to link with -lfmt for format library support"
        exit 1
    fi
    
    echo "Step 2: Building formatting demo executable..."
    g++ -std=c++20 -fmodules-ts -Wall -Wextra -o formatting_demo AdvancedExamples/demo_formatting.cpp
    
    if [ $? -eq 0 ]; then
        echo "✅ C++20 Formatting & Localization example built successfully!"
        echo "Run with: ./formatting_demo"
    else
        echo "❌ Formatting demo build failed!"
        echo "Try installing libfmt-dev and linking with -lfmt if std::format is not available"
        exit 1
    fi
    
elif command -v clang++ &> /dev/null; then
    echo "Using Clang - checking version for std::format support..."
    
    # Check Clang version for std::format support
    CLANG_VERSION=$(clang++ --version | grep -oP 'clang version \K[0-9]+' | head -1)
    if [ "$CLANG_VERSION" -lt 14 ]; then
        echo "⚠️  Clang 14+ recommended for std::format support (found Clang $CLANG_VERSION)"
        echo "Some formatting features may not be available"
    fi
    
    echo "Clang $CLANG_VERSION detected - building with formatting support..."
    
    # Clang with formatting
    echo "Step 1: Precompiling formatting module interface..."
    clang++ -std=c++20 --precompile AdvancedExamples/formatting_localization.cppm -o formatting_localization.pcm
    
    if [ $? -ne 0 ]; then
        echo "❌ Formatting module precompilation failed!"
        echo "Make sure you have Clang 14+ with std::format support"
        exit 1
    fi
    
    echo "Step 2: Building formatting demo executable..."
    clang++ -std=c++20 -fprebuilt-module-path=. -Wall -Wextra -o formatting_demo AdvancedExamples/demo_formatting.cpp
    
    if [ $? -eq 0 ]; then
        echo "✅ C++20 Formatting & Localization example built successfully!"
        echo "Run with: ./formatting_demo"
    else
        echo "❌ Formatting demo build failed!"
        exit 1
    fi
    
else
    echo "❌ No suitable C++ compiler found!"
    echo "Please install:"
    echo "  - GCC 13+ for Linux/macOS (best std::format support)"
    echo "  - Clang 14+ for Linux/macOS (good std::format support)"
    echo "  - Visual Studio 2019 16.10+ or Visual Studio 2022 for Windows"
    exit 1
fi

echo ""
echo "🎨 C++20 Formatting & Localization Features:"
echo "  ✨ std::format - Type-safe string formatting"
echo "  ✨ Custom formatters for user-defined types" 
echo "  ✨ Positional and named arguments"
echo "  ✨ Width, alignment, and fill characters"
echo "  ✨ Number base formatting (binary, octal, hex)"
echo "  ✨ Floating-point precision control"
echo "  ✨ Date/time formatting with chrono"
echo "  ✨ Locale-aware number formatting"
echo "  ✨ Currency formatting for different regions"
echo "  ✨ Multilingual message support"
echo "  ✨ Performance improvements over stringstream"

echo ""
echo "🌐 Localization Capabilities:"
echo "  • Automatic number formatting per locale"
echo "  • Currency symbol and placement"
echo "  • Date/time format customization"
echo "  • UTF-8 and character encoding support"
echo "  • Pluralization handling"
echo "  • Cultural formatting conventions"

echo ""
echo "📊 Real-world Examples Included:"
echo "  • Log message formatting"
echo "  • Configuration display"
echo "  • Error message formatting"
echo "  • Progress bar display"
echo "  • Data validation results"
echo "  • Performance comparisons"

echo ""
echo "⚠️  Compiler Support Notes:"
echo "  • MSVC 2019 16.10+: Full std::format support"
echo "  • GCC 13+: Full std::format support"
echo "  • Clang 14+: Good std::format support (improving)"
echo "  • Some features may require linking with format libraries"
echo "  • Locale support depends on system locale packages"
