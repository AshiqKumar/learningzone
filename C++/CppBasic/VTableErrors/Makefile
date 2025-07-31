# Makefile for VTable Error Examples
# Usage: make all, make run, make clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -O2
DEBUG_FLAGS = -g -O0 -DDEBUG
TARGETS = vtable_demo vtable_error_example

# Default target
all: $(TARGETS)

# Build vtable_demo
vtable_demo: vtable_demo.cpp
	@echo "Compiling vtable_demo..."
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "✓ vtable_demo compiled successfully"

# Build vtable_error_example
vtable_error_example: vtable_error_example.cpp
	@echo "Compiling vtable_error_example..."
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "✓ vtable_error_example compiled successfully"

# Debug builds
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGETS)
	@echo "✓ Debug builds completed"

# Run all examples
run: run-demo run-error-example

run-demo: vtable_demo
	@echo "=== Running vtable_demo ==="
	./vtable_demo
	@echo ""

run-error-example: vtable_error_example
	@echo "=== Running vtable_error_example ==="
	./vtable_error_example
	@echo ""

# Test compilation with different flags
test-compilation:
	@echo "Testing compilation with various flags..."
	@echo "1. Testing with strict warnings..."
	$(CXX) -std=c++17 -Wall -Wextra -Werror -pedantic vtable_demo.cpp -o test_vtable_demo
	@echo "✓ Strict compilation passed"
	
	@echo "2. Testing with sanitizers..."
	$(CXX) -std=c++17 -Wall -Wextra -fsanitize=address vtable_demo.cpp -o test_vtable_demo_asan
	@echo "✓ AddressSanitizer compilation passed"
	
	@echo "3. Testing C++20 compilation..."
	$(CXX) -std=c++20 -Wall -Wextra vtable_demo.cpp -o test_vtable_demo_cpp20
	@echo "✓ C++20 compilation passed"
	
	@rm -f test_vtable_demo test_vtable_demo_asan test_vtable_demo_cpp20
	@echo "✓ All compilation tests passed"

# Analyze object files for vtable symbols
analyze: vtable_demo.o vtable_error_example.o
	@echo "=== Analyzing object files for vtable symbols ==="
	@echo "1. Checking vtable_demo.o:"
	@nm vtable_demo.o | grep -i vtable || echo "No vtable symbols found"
	@echo ""
	@echo "2. Checking vtable_error_example.o:"
	@nm vtable_error_example.o | grep -i vtable || echo "No vtable symbols found"
	@echo ""
	@echo "3. Checking for virtual function symbols:"
	@nm vtable_demo.o | grep -E "_ZTV|virtual" || echo "No virtual function symbols found"

# Create object files for analysis
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Memory leak detection
valgrind: vtable_demo vtable_error_example
	@echo "=== Running memory leak detection ==="
	@echo "1. Checking vtable_demo:"
	valgrind --leak-check=full --show-leak-kinds=all ./vtable_demo
	@echo ""
	@echo "2. Checking vtable_error_example:"
	valgrind --leak-check=full --show-leak-kinds=all ./vtable_error_example

# Performance profiling
profile: vtable_demo
	@echo "=== Performance profiling ==="
	$(CXX) $(CXXFLAGS) -pg vtable_demo.cpp -o vtable_demo_prof
	./vtable_demo_prof
	gprof vtable_demo_prof gmon.out > profiling_report.txt
	@echo "✓ Profiling completed. See profiling_report.txt"

# Static analysis
static-analysis:
	@echo "=== Static Analysis ==="
	@echo "1. Running cppcheck..."
	cppcheck --enable=all --std=c++17 *.cpp || echo "cppcheck not available"
	@echo ""
	@echo "2. Running clang-tidy..."
	clang-tidy *.cpp -- -std=c++17 || echo "clang-tidy not available"

# Documentation generation
docs:
	@echo "=== Generating documentation ==="
	doxygen -g Doxyfile 2>/dev/null || echo "Doxygen config created"
	sed -i 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "VTable Error Solutions"/' Doxyfile 2>/dev/null || true
	sed -i 's/EXTRACT_ALL            = NO/EXTRACT_ALL            = YES/' Doxyfile 2>/dev/null || true
	doxygen Doxyfile 2>/dev/null || echo "Doxygen not available"
	@echo "✓ Documentation generated in html/ directory (if doxygen available)"

# Quick help for debugging vtable errors
help-debug:
	@echo "=== VTable Error Debugging Help ==="
	@echo ""
	@echo "Common vtable errors and solutions:"
	@echo "1. 'undefined reference to vtable for ClassName'"
	@echo "   - Check: All virtual functions are implemented"
	@echo "   - Check: Virtual destructor is implemented"
	@echo "   - Check: .cpp files are being linked"
	@echo ""
	@echo "2. Debugging commands:"
	@echo "   make analyze           - Check object files for vtable symbols"
	@echo "   nm *.o | grep vtable   - List vtable symbols"
	@echo "   objdump -t *.o         - Show all symbols"
	@echo "   ldd executable         - Check dynamic dependencies"
	@echo ""
	@echo "3. Compilation flags for debugging:"
	@echo "   -Wl,--no-undefined     - Show undefined references"
	@echo "   -v                     - Verbose compilation"
	@echo "   -save-temps           - Keep intermediate files"

# Show compilation commands that would cause vtable errors
show-errors:
	@echo "=== Examples of commands that cause vtable errors ==="
	@echo ""
	@echo "This would fail (missing implementation):"
	@echo 'g++ -c -o bad.o - <<EOF'
	@echo 'class Bad { public: virtual ~Bad(); virtual void func(); };'
	@echo 'int main() { Bad b; return 0; }'
	@echo 'EOF'
	@echo ""
	@echo "Error message would be:"
	@echo "undefined reference to \`vtable for Bad'"
	@echo ""
	@echo "Fix by implementing virtual functions:"
	@echo 'g++ -c -o good.o - <<EOF'
	@echo 'class Good { public: virtual ~Good() {} virtual void func() {} };'
	@echo 'int main() { Good g; return 0; }'
	@echo 'EOF'

# Comprehensive test suite
test: test-compilation run
	@echo "=== All tests completed successfully ==="

# Install example files to a specific directory
install: $(TARGETS)
	@mkdir -p ../VTableSolutions
	@cp *.cpp *.h Makefile README.md ../VTableSolutions/ 2>/dev/null || true
	@cp $(TARGETS) ../VTableSolutions/ 2>/dev/null || true
	@echo "✓ Files installed to ../VTableSolutions/"

# Clean up generated files
clean:
	@echo "Cleaning up..."
	@rm -f $(TARGETS) *.o *.exe
	@rm -f test_* *_prof gmon.out profiling_report.txt
	@rm -f Doxyfile
	@rm -rf html/ latex/
	@echo "✓ Cleanup completed"

# Clean everything including documentation
clean-all: clean
	@rm -rf ../VTableSolutions
	@echo "✓ Full cleanup completed"

# Show build information
info:
	@echo "=== Build Information ==="
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Targets: $(TARGETS)"
	@echo "Source files: *.cpp"
	@echo ""
	@echo "Available targets:"
	@echo "  all            - Build all examples"
	@echo "  run            - Run all examples"
	@echo "  debug          - Build with debug flags"
	@echo "  test           - Run comprehensive tests"
	@echo "  analyze        - Analyze for vtable symbols"
	@echo "  help-debug     - Show debugging help"
	@echo "  clean          - Remove generated files"
	@echo "  info           - Show this information"

.PHONY: all run debug test clean clean-all info help-debug show-errors install
.PHONY: run-demo run-error-example test-compilation analyze static-analysis
.PHONY: valgrind profile docs
