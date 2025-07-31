#!/bin/bash

# C++20 Modules Basic Examples Compilation Script
# This script demonstrates how to compile C++20 modules with different compilers

echo "=== C++20 Modules Basic Examples Compilation ==="
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Clean previous builds
print_status "Cleaning previous builds..."
rm -f *.o *.pcm basic_demo hello math_utils
echo ""

# Check for compiler availability
check_compiler() {
    if command -v $1 &> /dev/null; then
        print_success "$1 is available"
        return 0
    else
        print_warning "$1 is not available"
        return 1
    fi
}

echo "Checking compiler availability:"
GCC_AVAILABLE=false
CLANG_AVAILABLE=false

if check_compiler "g++"; then
    GCC_VERSION=$(g++ --version | head -n1)
    print_status "GCC Version: $GCC_VERSION"
    GCC_AVAILABLE=true
fi

if check_compiler "clang++"; then
    CLANG_VERSION=$(clang++ --version | head -n1)
    print_status "Clang Version: $CLANG_VERSION"
    CLANG_AVAILABLE=true
fi

echo ""

# GCC Compilation
if $GCC_AVAILABLE; then
    echo "=== Compiling with GCC ==="
    print_status "Using GCC with -fmodules-ts flag"
    
    # Step 1: Compile module interface units
    print_status "Step 1: Compiling hello module..."
    if g++ -std=c++20 -fmodules-ts -c hello_world.cppm -o hello.o; then
        print_success "hello module compiled successfully"
    else
        print_error "Failed to compile hello module"
        exit 1
    fi
    
    print_status "Step 2: Compiling math_utils module..."
    if g++ -std=c++20 -fmodules-ts -c math_utils.cppm -o math_utils.o; then
        print_success "math_utils module compiled successfully"
    else
        print_error "Failed to compile math_utils module"
        exit 1
    fi
    
    # Step 2: Compile main program and link
    print_status "Step 3: Compiling main program and linking..."
    if g++ -std=c++20 -fmodules-ts main_basic.cpp hello.o math_utils.o -o basic_demo_gcc; then
        print_success "Program compiled and linked successfully"
        print_success "Executable created: basic_demo_gcc"
    else
        print_error "Failed to compile main program"
        exit 1
    fi
    
    echo ""
fi

# Clang Compilation (if available)
if $CLANG_AVAILABLE; then
    echo "=== Compiling with Clang ==="
    print_warning "Note: Clang modules syntax may vary by version"
    print_status "Using Clang with -fmodules flag"
    
    # Clang uses a different approach - precompiled modules
    print_status "Step 1: Precompiling hello module..."
    if clang++ -std=c++20 -fmodules --precompile hello_world.cppm -o hello.pcm; then
        print_success "hello module precompiled successfully"
    else
        print_warning "Clang module compilation may not be supported in this version"
        print_status "Trying alternative Clang syntax..."
        # Alternative: try compiling as regular C++ with module support
        if clang++ -std=c++20 -c hello_world.cppm -o hello_clang.o; then
            print_success "hello module compiled with alternative method"
        else
            print_error "Failed to compile hello module with Clang"
        fi
    fi
    
    echo ""
fi

# MSVC Compilation (Windows only)
if command -v cl &> /dev/null; then
    echo "=== MSVC Compilation Instructions ==="
    print_status "For MSVC (Windows), use these commands:"
    echo "cl /std:c++20 /experimental:module /c hello_world.cppm"
    echo "cl /std:c++20 /experimental:module /c math_utils.cppm"
    echo "cl /std:c++20 /experimental:module main_basic.cpp hello_world.obj math_utils.obj"
    echo ""
fi

# Test the executable
if [ -f "basic_demo_gcc" ]; then
    echo "=== Testing the Executable ==="
    print_status "Running basic_demo_gcc..."
    echo ""
    if ./basic_demo_gcc; then
        echo ""
        print_success "Program executed successfully!"
    else
        print_error "Program execution failed"
        exit 1
    fi
fi

echo ""
echo "=== Compilation Summary ==="
if [ -f "basic_demo_gcc" ]; then
    print_success "✅ GCC compilation successful"
    print_status "   Executable: basic_demo_gcc"
    print_status "   Size: $(du -h basic_demo_gcc | cut -f1)"
fi

if [ -f "hello.pcm" ]; then
    print_success "✅ Clang precompiled modules created"
fi

echo ""
print_status "Generated files:"
ls -la *.o *.pcm basic_demo* 2>/dev/null || echo "No output files found"

echo ""
print_status "To run the demo:"
echo "  ./basic_demo_gcc"

echo ""
print_status "To clean up:"
echo "  rm -f *.o *.pcm basic_demo*"

echo ""
print_success "🎉 Compilation script completed!"

# Additional helpful information
echo ""
echo "=== Module Compilation Notes ==="
print_status "📝 Key Points:"
echo "   • Modules must be compiled before importing code"
echo "   • .cppm files are module interface units"
echo "   • .cpp files can be module implementation units"
echo "   • Template definitions should be in interface units"
echo "   • Module names don't need to match file names"

echo ""
print_status "🔧 Compiler Flags Explained:"
echo "   GCC: -fmodules-ts (experimental modules support)"
echo "   Clang: -fmodules (modules support)"
echo "   MSVC: /experimental:module (experimental modules)"

echo ""
print_status "📚 Further Learning:"
echo "   • Try modifying the modules and recompiling"
echo "   • Experiment with different export patterns"
echo "   • Check advanced examples in ../AdvancedExamples/"
