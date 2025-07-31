# Makefile for C++ Inheritance Examples
# Usage: make all, make clean, make run-all

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Source files
SOURCES = single_inheritance.cpp multiple_inheritance.cpp multilevel_inheritance.cpp \
          hierarchical_inheritance.cpp hybrid_inheritance.cpp

# Executables
EXECUTABLES = single_inheritance multiple_inheritance multilevel_inheritance \
              hierarchical_inheritance hybrid_inheritance

.PHONY: all clean run-all help

# Default target
all: $(EXECUTABLES)

# Individual targets
single_inheritance: single_inheritance.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

multiple_inheritance: multiple_inheritance.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

multilevel_inheritance: multilevel_inheritance.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

hierarchical_inheritance: hierarchical_inheritance.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

hybrid_inheritance: hybrid_inheritance.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Run all examples
run-all: all
	@echo "=== Running Single Inheritance Demo ==="
	./single_inheritance
	@echo
	@echo "=== Running Multiple Inheritance Demo ==="
	./multiple_inheritance
	@echo
	@echo "=== Running Multilevel Inheritance Demo ==="
	./multilevel_inheritance
	@echo
	@echo "=== Running Hierarchical Inheritance Demo ==="
	./hierarchical_inheritance
	@echo
	@echo "=== Running Hybrid Inheritance Demo ==="
	./hybrid_inheritance

# Quick test with single inheritance
run-quick: single_inheritance
	@echo "=== Running Single Inheritance Demo ==="
	./single_inheritance

# Run specific inheritance type
run-single: single_inheritance
	./single_inheritance

run-multiple: multiple_inheritance
	./multiple_inheritance

run-multilevel: multilevel_inheritance
	./multilevel_inheritance

run-hierarchical: hierarchical_inheritance
	./hierarchical_inheritance

run-hybrid: hybrid_inheritance
	./hybrid_inheritance

# Clean up executables
clean:
	rm -f $(EXECUTABLES)
	rm -f *.exe

# Help target
help:
	@echo "Available targets:"
	@echo "  all           - Build all inheritance examples"
	@echo "  run-all       - Build and run all examples"
	@echo "  run-quick     - Build and run single inheritance only"
	@echo "  clean         - Remove all executables"
	@echo "  help          - Show this help message"
	@echo
	@echo "Individual targets:"
	@echo "  single_inheritance      - Single inheritance example"
	@echo "  multiple_inheritance    - Multiple inheritance example"
	@echo "  multilevel_inheritance  - Multilevel inheritance example"
	@echo "  hierarchical_inheritance - Hierarchical inheritance example"
	@echo "  hybrid_inheritance      - Hybrid inheritance example"
	@echo
	@echo "Run specific examples:"
	@echo "  run-single       - Run single inheritance demo"
	@echo "  run-multiple     - Run multiple inheritance demo"
	@echo "  run-multilevel   - Run multilevel inheritance demo"
	@echo "  run-hierarchical - Run hierarchical inheritance demo"
	@echo "  run-hybrid       - Run hybrid inheritance demo"
