# Makefile for Encapsulation Examples
# Compile: make all
# Run all: make run-all
# Clean: make clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Source files
SOURCES = basic_encapsulation.cpp \
          getters_setters.cpp \
          const_correctness.cpp \
          friend_functions.cpp \
          validation_encapsulation.cpp \
          pimpl_idiom.cpp \
          property_pattern.cpp \
          encapsulation_inheritance.cpp \
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
basic_encapsulation: basic_encapsulation.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

getters_setters: getters_setters.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

const_correctness: const_correctness.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

friend_functions: friend_functions.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

validation_encapsulation: validation_encapsulation.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

pimpl_idiom: pimpl_idiom.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

property_pattern: property_pattern.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

encapsulation_inheritance: encapsulation_inheritance.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

comprehensive_demo: comprehensive_demo.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Run all examples
run-all: $(EXECUTABLES)
	@echo "=== Running Basic Encapsulation Example ==="
	./basic_encapsulation
	@echo ""
	@echo "=== Running Getters and Setters Example ==="
	./getters_setters
	@echo ""
	@echo "=== Running Const Correctness Example ==="
	./const_correctness
	@echo ""
	@echo "=== Running Friend Functions Example ==="
	./friend_functions
	@echo ""
	@echo "=== Running Validation Encapsulation Example ==="
	./validation_encapsulation
	@echo ""
	@echo "=== Running Pimpl Idiom Example ==="
	./pimpl_idiom
	@echo ""
	@echo "=== Running Property Pattern Example ==="
	./property_pattern
	@echo ""
	@echo "=== Running Encapsulation Inheritance Example ==="
	./encapsulation_inheritance
	@echo ""
	@echo "=== Running Comprehensive Demo ==="
	./comprehensive_demo

# Run individual examples
run-basic-encapsulation: basic_encapsulation
	./basic_encapsulation

run-getters-setters: getters_setters
	./getters_setters

run-const-correctness: const_correctness
	./const_correctness

run-friend-functions: friend_functions
	./friend_functions

run-validation-encapsulation: validation_encapsulation
	./validation_encapsulation

run-pimpl-idiom: pimpl_idiom
	./pimpl_idiom

run-property-pattern: property_pattern
	./property_pattern

run-encapsulation-inheritance: encapsulation_inheritance
	./encapsulation_inheritance

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
	@echo "  all                           - Build all examples"
	@echo "  run-all                      - Build and run all examples"
	@echo "  run-<example>                - Build and run specific example"
	@echo "  debug                        - Build with debug information"
	@echo "  check                        - Check compilation without running"
	@echo "  clean                        - Remove all build artifacts"
	@echo "  test                         - Run all examples as tests"
	@echo "  help                         - Show this help message"
	@echo ""
	@echo "Individual examples:"
	@echo "  basic_encapsulation          - Basic data hiding and access control"
	@echo "  getters_setters              - Accessor and mutator methods"
	@echo "  const_correctness            - Const methods and immutability"
	@echo "  friend_functions             - Friend functions and classes"
	@echo "  validation_encapsulation     - Input validation and data integrity"
	@echo "  pimpl_idiom                  - Pointer to Implementation pattern"
	@echo "  property_pattern             - Property-like access mechanisms"
	@echo "  encapsulation_inheritance    - Encapsulation in inheritance"
	@echo "  comprehensive_demo           - All concepts integrated"

# Phony targets (don't correspond to files)
.PHONY: all run-all clean debug check install test help \
        run-basic-encapsulation run-getters-setters \
        run-const-correctness run-friend-functions \
        run-validation-encapsulation run-pimpl-idiom \
        run-property-pattern run-encapsulation-inheritance \
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

# Code metrics
metrics:
	@echo "Code metrics:"
	@for file in $(SOURCES); do \
		echo "$$file:"; \
		echo "  Lines: $$(wc -l < $$file)"; \
		echo "  Characters: $$(wc -c < $$file)"; \
		echo "  Words: $$(wc -w < $$file)"; \
	done

.PHONY: analyze memcheck format docs perf-test size-analysis metrics
