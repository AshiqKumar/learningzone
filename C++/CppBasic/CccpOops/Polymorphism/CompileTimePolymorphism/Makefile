# Makefile for Compile-Time Polymorphism Examples
# Compile: make all
# Run all: make run-all
# Clean: make clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Source files
SOURCES = function_overloading.cpp \
          operator_overloading.cpp \
          template_functions.cpp \
          template_classes.cpp \
          template_specialization.cpp \
          sfinae_concepts.cpp \
          constexpr_programming.cpp \
          auto_deduction.cpp \
          comprehensive_demo.cpp

# Object files (derived from source files)
OBJECTS = $(SOURCES:.cpp=.o)

# Executable files (derived from source files)
EXECUTABLES = $(SOURCES:.cpp=)

# Default target
all: $(EXECUTABLES)

# Rule to build executables from source files
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Rule to build object files (if needed)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Individual targets
function_overloading: function_overloading.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

operator_overloading: operator_overloading.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

template_functions: template_functions.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

template_classes: template_classes.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

template_specialization: template_specialization.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

sfinae_concepts: sfinae_concepts.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

constexpr_programming: constexpr_programming.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

auto_deduction: auto_deduction.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

comprehensive_demo: comprehensive_demo.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Run all examples
run-all: $(EXECUTABLES)
	@echo "=== Running Function Overloading Example ==="
	./function_overloading
	@echo ""
	@echo "=== Running Operator Overloading Example ==="
	./operator_overloading
	@echo ""
	@echo "=== Running Template Functions Example ==="
	./template_functions
	@echo ""
	@echo "=== Running Template Classes Example ==="
	./template_classes
	@echo ""
	@echo "=== Running Template Specialization Example ==="
	./template_specialization
	@echo ""
	@echo "=== Running SFINAE Concepts Example ==="
	./sfinae_concepts
	@echo ""
	@echo "=== Running Constexpr Programming Example ==="
	./constexpr_programming
	@echo ""
	@echo "=== Running Auto Deduction Example ==="
	./auto_deduction
	@echo ""
	@echo "=== Running Comprehensive Demo ==="
	./comprehensive_demo

# Run individual examples
run-function-overloading: function_overloading
	./function_overloading

run-operator-overloading: operator_overloading
	./operator_overloading

run-template-functions: template_functions
	./template_functions

run-template-classes: template_classes
	./template_classes

run-template-specialization: template_specialization
	./template_specialization

run-sfinae-concepts: sfinae_concepts
	./sfinae_concepts

run-constexpr-programming: constexpr_programming
	./constexpr_programming

run-auto-deduction: auto_deduction
	./auto_deduction

run-comprehensive-demo: comprehensive_demo
	./comprehensive_demo

# Debug builds
debug: CXXFLAGS += -g -DDEBUG
debug: $(EXECUTABLES)

# Check for compilation errors without running
check: $(EXECUTABLES)
	@echo "All examples compiled successfully!"

# Clean build artifacts
clean:
	rm -f $(EXECUTABLES) $(OBJECTS) *.exe *.out
	@echo "Cleaned all build artifacts"

# Install target (copy to system directory)
install: $(EXECUTABLES)
	@echo "Install target not implemented. Examples are ready to run locally."

# Test target
test: run-all
	@echo "All tests completed!"

# Help target
help:
	@echo "Available targets:"
	@echo "  all                    - Build all examples"
	@echo "  run-all               - Build and run all examples"
	@echo "  run-<example>         - Build and run specific example"
	@echo "  debug                 - Build with debug information"
	@echo "  check                 - Check compilation without running"
	@echo "  clean                 - Remove all build artifacts"
	@echo "  test                  - Run all examples as tests"
	@echo "  help                  - Show this help message"
	@echo ""
	@echo "Individual examples:"
	@echo "  function_overloading  - Function overloading concepts"
	@echo "  operator_overloading  - Operator overloading examples"
	@echo "  template_functions    - Template function demonstrations"
	@echo "  template_classes      - Template class examples"
	@echo "  template_specialization - Template specialization techniques"
	@echo "  sfinae_concepts       - SFINAE and type traits"
	@echo "  constexpr_programming - Compile-time computation"
	@echo "  auto_deduction        - Automatic type deduction"
	@echo "  comprehensive_demo    - All concepts combined"

# Phony targets (don't correspond to files)
.PHONY: all run-all clean debug check install test help \
        run-function-overloading run-operator-overloading \
        run-template-functions run-template-classes \
        run-template-specialization run-sfinae-concepts \
        run-constexpr-programming run-auto-deduction \
        run-comprehensive-demo

# Advanced features
# Static analysis with cppcheck (if available)
analyze:
	@if command -v cppcheck >/dev/null 2>&1; then \
		echo "Running static analysis..."; \
		cppcheck --enable=all --std=c++17 $(SOURCES); \
	else \
		echo "cppcheck not available, skipping static analysis"; \
	fi

# Memory check with valgrind (if available, Linux/Mac)
memcheck: $(EXECUTABLES)
	@if command -v valgrind >/dev/null 2>&1; then \
		for exe in $(EXECUTABLES); do \
			echo "Memory checking $$exe..."; \
			valgrind --leak-check=full ./$$exe; \
		done; \
	else \
		echo "valgrind not available, skipping memory check"; \
	fi

# Format code with clang-format (if available)
format:
	@if command -v clang-format >/dev/null 2>&1; then \
		echo "Formatting source files..."; \
		clang-format -i $(SOURCES); \
		echo "Code formatted successfully"; \
	else \
		echo "clang-format not available, skipping formatting"; \
	fi

# Generate documentation with doxygen (if available)
docs:
	@if command -v doxygen >/dev/null 2>&1; then \
		echo "Generating documentation..."; \
		doxygen; \
	else \
		echo "doxygen not available, skipping documentation generation"; \
	fi

.PHONY: analyze memcheck format docs
