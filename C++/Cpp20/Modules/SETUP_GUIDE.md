# 🔧 GCC 11+ Setup Guide for VS Code on Windows

## 📋 **What You Need for C++20 Modules**

To run the C++20 formatting and modules examples, you need a modern compiler that supports:
- ✅ C++20 standard
- ✅ `std::format` library
- ✅ Modules (experimental)
- ✅ Concepts

## 🚀 **Installation Options**

### **Option 1: MSYS2 (Recommended for GCC)**

1. **Download and Install MSYS2:**
   - Visit: https://www.msys2.org/
   - Download the installer and run it
   - Follow the installation wizard

2. **Install GCC 13+ and Tools:**
   ```bash
   # Open MSYS2 terminal and run:
   pacman -Syu                          # Update package database
   pacman -S mingw-w64-x86_64-gcc       # Install GCC 13+
   pacman -S mingw-w64-x86_64-gdb       # Install debugger
   pacman -S mingw-w64-x86_64-make      # Install make
   pacman -S mingw-w64-x86_64-cmake     # Install CMake
   ```

3. **Add to Windows PATH:**
   - Add `C:\msys64\mingw64\bin` to your system PATH
   - Restart VS Code after updating PATH

4. **Verify Installation:**
   ```bash
   gcc --version    # Should show GCC 13.x or higher
   ```

### **Option 2: Visual Studio 2022 (Easiest)**

1. **Install VS 2022 Community (Free):**
   ```powershell
   winget install Microsoft.VisualStudio.2022.Community
   ```
   
2. **Select Workloads During Installation:**
   - ✅ Desktop development with C++
   - ✅ MSVC v143 compiler toolset
   - ✅ Windows 10/11 SDK (latest version)
   - ✅ CMake tools for Visual Studio

3. **VS Code will automatically detect MSVC**

### **Option 3: WinLibs (Alternative)**

1. **Download WinLibs:**
   - Visit: https://winlibs.com/
   - Download GCC 13+ release
   - Extract to `C:\mingw64\`

2. **Add to PATH:**
   - Add `C:\mingw64\bin` to system PATH

## 🛠️ **VS Code Configuration**

I've already created the necessary VS Code configuration files:

- 📄 `.vscode/c_cpp_properties.json` - IntelliSense configuration
- 📄 `.vscode/tasks.json` - Build tasks for different examples
- 📄 `.vscode/launch.json` - Debug configurations
- 📄 `.vscode/settings.json` - VS Code settings for C++20

## 🎯 **How to Use**

### **Step 1: Install a Modern Compiler**
Choose one of the options above and install it.

### **Step 2: Update Paths (if needed)**
If you installed to a different location, update the paths in:
- `.vscode/c_cpp_properties.json` (line 12: compilerPath)
- `.vscode/launch.json` (miDebuggerPath entries)

### **Step 3: Build and Run**

**Using VS Code Tasks (Ctrl+Shift+P → "Tasks: Run Task"):**

1. **"Build Traditional Headers"** - Works with any compiler
2. **"Build C++20 Modules (GCC)"** - Requires GCC 11+
3. **"Build C++20 Formatting (GCC)"** - Requires GCC 13+ for std::format

**Or using Terminal:**
```bash
# For traditional headers (works with your current GCC 6.3)
cd ComparisonExamples/traditional_headers
g++ -std=c++17 -o traditional_demo main_traditional.cpp calculator.cpp
./traditional_demo

# For C++20 modules (requires GCC 11+)
cd AdvancedExamples
g++ -std=c++20 -fmodules-ts -fconcepts data_processor.cppm demo_advanced.cpp -o advanced_demo
./advanced_demo

# For C++20 formatting (requires GCC 13+)
g++ -std=c++20 -fmodules-ts formatting_localization.cppm demo_formatting.cpp -o formatting_demo
./formatting_demo
```

## 🔍 **Verify Your Setup**

Run this command to check your compiler:

```bash
gcc --version
g++ -std=c++20 -dM -E - < /dev/null | grep __cplusplus
```

Expected output for C++20 support:
- GCC version: 11.0 or higher
- `__cplusplus` value: 202002L or higher

## ⚠️ **Troubleshooting**

**Problem: "cl command not found"**
- Solution: Install Visual Studio 2022 or use GCC

**Problem: "C++20 features not working"**
- Solution: Ensure GCC 11+ is installed and in PATH

**Problem: "std::format not found"**
- Solution: Need GCC 13+ or MSVC 2019 16.10+

**Problem: "Module compilation failed"**
- Solution: Modules are experimental, try different compiler flags

## 🎉 **Success Indicators**

You'll know everything is working when:
- ✅ IntelliSense recognizes C++20 syntax
- ✅ `import` statements don't show errors
- ✅ `std::format` is available
- ✅ Concepts work without errors
- ✅ Build tasks complete successfully

## 📚 **Next Steps**

Once you have a modern compiler:

1. **Start with Traditional Headers:** Always works as a baseline
2. **Try Basic Modules:** Simple module examples
3. **Advanced Features:** Concepts, std::format, complex templates
4. **Compare Performance:** See the benefits of modules

Happy coding with modern C++20! 🚀
