# Makefile for Runtime Polymorphism Examples
# Compile: make all
# Run all: make run-all
# Clean: make clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Source files
SOURCES = virtual_functions.cpp \
          pure_virtual_abstract.cpp \
          virtual_destructors.cpp \
          function_overriding.cpp \
          dynamic_binding.cpp \
          type_identification.cpp \
          polymorphic_containers.cpp \
          interface_design.cpp \
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
virtual_functions: virtual_functions.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

pure_virtual_abstract: pure_virtual_abstract.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

virtual_destructors: virtual_destructors.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

function_overriding: function_overriding.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

dynamic_binding: dynamic_binding.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

type_identification: type_identification.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

polymorphic_containers: polymorphic_containers.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

interface_design: interface_design.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

comprehensive_demo: comprehensive_demo.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Run all examples
run-all: $(EXECUTABLES)
	@echo "=== Running Virtual Functions Example ==="
	./virtual_functions
	@echo ""
	@echo "=== Running Pure Virtual & Abstract Classes Example ==="
	./pure_virtual_abstract
	@echo ""
	@echo "=== Running Virtual Destructors Example ==="
	./virtual_destructors
	@echo ""
	@echo "=== Running Function Overriding Example ==="
	./function_overriding
	@echo ""
	@echo "=== Running Dynamic Binding Example ==="
	./dynamic_binding
	@echo ""
	@echo "=== Running Type Identification Example ==="
	./type_identification
	@echo ""
	@echo "=== Running Polymorphic Containers Example ==="
	./polymorphic_containers
	@echo ""
	@echo "=== Running Interface Design Example ==="
	./interface_design
	@echo ""
	@echo "=== Running Comprehensive Demo ==="
	./comprehensive_demo

# Run individual examples
run-virtual-functions: virtual_functions
	./virtual_functions

run-pure-virtual-abstract: pure_virtual_abstract
	./pure_virtual_abstract

run-virtual-destructors: virtual_destructors
	./virtual_destructors

run-function-overriding: function_overriding
	./function_overriding

run-dynamic-binding: dynamic_binding
	./dynamic_binding

run-type-identification: type_identification
	./type_identification

run-polymorphic-containers: polymorphic_containers
	./polymorphic_containers

run-interface-design: interface_design
	./interface_design

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
	@echo "  all                      - Build all examples"
	@echo "  run-all                 - Build and run all examples"
	@echo "  run-<example>           - Build and run specific example"
	@echo "  debug                   - Build with debug information"
	@echo "  check                   - Check compilation without running"
	@echo "  clean                   - Remove all build artifacts"
	@echo "  test                    - Run all examples as tests"
	@echo "  help                    - Show this help message"
	@echo ""
	@echo "Individual examples:"
	@echo "  virtual_functions       - Basic virtual function concepts"
	@echo "  pure_virtual_abstract   - Abstract classes and pure virtual functions"
	@echo "  virtual_destructors     - Proper cleanup in inheritance hierarchies"
	@echo "  function_overriding     - Function overriding techniques"
	@echo "  dynamic_binding         - Runtime binding demonstrations"
	@echo "  type_identification     - RTTI and type checking"
	@echo "  polymorphic_containers  - Using polymorphism with containers"
	@echo "  interface_design        - Designing interfaces with pure virtual functions"
	@echo "  comprehensive_demo      - All concepts integrated"

# Phony targets (don't correspond to files)
.PHONY: all run-all clean debug check install test help \
        run-virtual-functions run-pure-virtual-abstract \
        run-virtual-destructors run-function-overriding \
        run-dynamic-binding run-type-identification \
        run-polymorphic-containers run-interface-design \
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

# Performance testing
perf-test: $(EXECUTABLES)
	@echo "Running performance tests..."
	@for exe in $(EXECUTABLES); do \
		echo "Testing $$exe..."; \
		time ./$$exe > /dev/null; \
	done

# Size analysis
size-analysis: $(EXECUTABLES)
	@echo "Executable sizes:"
	@ls -lh $(EXECUTABLES) | awk '{print $$9 ": " $$5}'

.PHONY: analyze memcheck format docs perf-test size-analysis
