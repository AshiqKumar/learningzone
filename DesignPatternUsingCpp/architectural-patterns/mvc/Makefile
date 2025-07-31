# Makefile for Student Management System (MVC Pattern)
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.

# Directories
MODEL_DIR = model
VIEW_DIR = view
CONTROLLER_DIR = controller

# Source files
MODEL_SOURCES = $(MODEL_DIR)/Student.cpp $(MODEL_DIR)/StudentModel.cpp
VIEW_SOURCES = $(VIEW_DIR)/StudentView.cpp
CONTROLLER_SOURCES = $(CONTROLLER_DIR)/StudentController.cpp
MAIN_SOURCE = main.cpp

# Object files
MODEL_OBJECTS = $(MODEL_SOURCES:.cpp=.o)
VIEW_OBJECTS = $(VIEW_SOURCES:.cpp=.o)
CONTROLLER_OBJECTS = $(CONTROLLER_SOURCES:.cpp=.o)
MAIN_OBJECT = $(MAIN_SOURCE:.cpp=.o)

# All objects
OBJECTS = $(MODEL_OBJECTS) $(VIEW_OBJECTS) $(CONTROLLER_OBJECTS) $(MAIN_OBJECT)

# Target executable
TARGET = student_management

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean completed"

# Rebuild everything
rebuild: clean all

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: all

# Run the application
run: $(TARGET)
	./$(TARGET)

# Create directories if they don't exist
directories:
	mkdir -p $(MODEL_DIR) $(VIEW_DIR) $(CONTROLLER_DIR)

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the application (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  rebuild  - Clean and build"
	@echo "  debug    - Build with debug symbols"
	@echo "  run      - Build and run the application"
	@echo "  help     - Show this help message"

# Phony targets
.PHONY: all clean rebuild debug run directories help

# Dependencies (auto-generated would be better for larger projects)
$(MODEL_DIR)/Student.o: $(MODEL_DIR)/Student.cpp $(MODEL_DIR)/Student.h
$(MODEL_DIR)/StudentModel.o: $(MODEL_DIR)/StudentModel.cpp $(MODEL_DIR)/StudentModel.h $(MODEL_DIR)/Student.h
$(VIEW_DIR)/StudentView.o: $(VIEW_DIR)/StudentView.cpp $(VIEW_DIR)/StudentView.h $(MODEL_DIR)/Student.h $(MODEL_DIR)/StudentModel.h
$(CONTROLLER_DIR)/StudentController.o: $(CONTROLLER_DIR)/StudentController.cpp $(CONTROLLER_DIR)/StudentController.h $(MODEL_DIR)/StudentModel.h $(VIEW_DIR)/StudentView.h
main.o: main.cpp $(CONTROLLER_DIR)/StudentController.h
