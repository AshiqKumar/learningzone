# Factory Method Design Pattern in C++

## Overview

The **Factory Method Design Pattern** is a creational design pattern that defines an interface for creating objects, but lets subclasses decide which class to instantiate. It allows a class to defer instantiation to subclasses, providing a way to create objects without specifying their exact classes. This pattern is particularly useful when the exact type of object to be created is determined at runtime.

## Key Concepts

- **Creator**: Abstract base class that declares the factory method
- **Concrete Creator**: Subclass that implements the factory method to create specific products
- **Product**: Abstract interface for objects the factory method creates
- **Concrete Product**: Specific implementation of the Product interface
- **Factory Method**: Virtual method that creates and returns Product objects

## Problem Solved

Without the Factory Method pattern:
- **Hard-coded object creation** scattered throughout the codebase
- **Tight coupling** between client code and specific product classes
- **Difficulty adding new product types** without modifying existing code
- **Violation of Open/Closed Principle** when extending functionality
- **Complex conditional logic** for object creation

## Solution Structure

```
                     ┌─────────────────┐
                     │     Client      │
                     └─────────────────┘
                              │
                              ▼
                     ┌─────────────────┐
                     │     Creator     │
                     │ + factoryMethod()│ ◄─── Factory Method
                     │ + operation()   │
                     └─────────────────┘
                              △
                    ┌─────────┴─────────┐
           ┌────────▼────────┐ ┌────────▼────────┐
           │ ConcreteCreatorA│ │ ConcreteCreatorB│
           │ + factoryMethod()│ │ + factoryMethod()│
           └─────────────────┘ └─────────────────┘
                    │                    │
                    │creates             │creates
                    ▼                    ▼
            ┌─────────────┐      ┌─────────────┐
            │  ProductA   │      │  ProductB   │
            └─────────────┘      └─────────────┘
                    △                    △
                    └──────────┬─────────┘
                              │
                     ┌────────▼────────┐
                     │    Product      │
                     │   (Abstract)    │
                     └─────────────────┘
```

## Code Analysis

### Product Interface
```cpp
class Shape {
public:
    virtual void Draw() = 0;
    static Shape* Create(string type);
};
```
**Purpose**: Defines the interface that all concrete shapes must implement.

### Concrete Products
```cpp
class Circle : public Shape {
public:
    void Draw() { cout << "I am circle" << endl; }
    friend class Shape;
};

class Square : public Shape {
public:
    void Draw() { cout << "I am square" << endl; }
    friend class Shape;
};
```
**Purpose**: Concrete implementations of the Shape interface.

### Factory Method Implementation
```cpp
Shape* Shape::Create(string type) {
    if (type == "circle") return new Circle();
    if (type == "square") return new Square();
    return NULL;
}
```
**Purpose**: Static factory method that creates specific shape objects based on type parameter.

### Client Usage
```cpp
Shape* obj1 = Shape::Create("circle");
Shape* obj2 = Shape::Create("square");
obj1->Draw();
obj2->Draw();
```
**Purpose**: Client code uses the factory method without knowing the specific classes.

## Advantages

### ✅ **Eliminates Tight Coupling**
- Client code doesn't depend on concrete classes
- Easy to change product implementations
- Reduced dependencies between components

### ✅ **Open/Closed Principle**
- Open for extension (new products)
- Closed for modification (existing code)
- Add new products without changing existing factory

### ✅ **Single Responsibility**
- Factory handles only object creation
- Products handle only their specific behavior
- Clear separation of concerns

### ✅ **Polymorphism Support**
- Work with products through common interface
- Runtime product selection
- Consistent behavior across different products

## Disadvantages

### ❌ **Code Complexity**
- Additional classes and inheritance hierarchy
- Can be overkill for simple scenarios
- More code to maintain

### ❌ **Runtime Overhead**
- Virtual function calls
- Dynamic allocation overhead
- Indirection through factory methods

### ❌ **Memory Management**
- Manual memory management with raw pointers
- Potential memory leaks
- No automatic cleanup

## Modern C++ Implementation

Here's an improved version addressing the original code's limitations:

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>
#include <stdexcept>

// Forward declarations
class Shape;

// Modern Product Interface
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual std::string getType() const = 0;
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void scale(double factor) = 0;
    
    // Modern factory method with smart pointers
    static std::unique_ptr<Shape> create(const std::string& type);
    
    // Advanced factory with parameters
    template<typename T, typename... Args>
    static std::unique_ptr<Shape> create(Args&&... args);
};

// Concrete Products with enhanced functionality
class Circle : public Shape {
private:
    double radius_;
    
public:
    explicit Circle(double radius = 1.0) : radius_(radius) {
        if (radius <= 0) {
            throw std::invalid_argument("Circle radius must be positive");
        }
    }
    
    void draw() const override {
        std::cout << "Drawing Circle with radius: " << radius_ << std::endl;
    }
    
    std::string getType() const override {
        return "Circle";
    }
    
    double getArea() const override {
        return 3.14159 * radius_ * radius_;
    }
    
    double getPerimeter() const override {
        return 2 * 3.14159 * radius_;
    }
    
    void scale(double factor) override {
        if (factor <= 0) {
            throw std::invalid_argument("Scale factor must be positive");
        }
        radius_ *= factor;
    }
    
    double getRadius() const { return radius_; }
    void setRadius(double radius) {
        if (radius <= 0) {
            throw std::invalid_argument("Circle radius must be positive");
        }
        radius_ = radius;
    }
};

class Rectangle : public Shape {
private:
    double width_, height_;
    
public:
    Rectangle(double width = 1.0, double height = 1.0) 
        : width_(width), height_(height) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Rectangle dimensions must be positive");
        }
    }
    
    void draw() const override {
        std::cout << "Drawing Rectangle: " << width_ << " x " << height_ << std::endl;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
    
    double getArea() const override {
        return width_ * height_;
    }
    
    double getPerimeter() const override {
        return 2 * (width_ + height_);
    }
    
    void scale(double factor) override {
        if (factor <= 0) {
            throw std::invalid_argument("Scale factor must be positive");
        }
        width_ *= factor;
        height_ *= factor;
    }
    
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
    void setDimensions(double width, double height) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Rectangle dimensions must be positive");
        }
        width_ = width;
        height_ = height;
    }
};

class Triangle : public Shape {
private:
    double base_, height_;
    
public:
    Triangle(double base = 1.0, double height = 1.0) 
        : base_(base), height_(height) {
        if (base <= 0 || height <= 0) {
            throw std::invalid_argument("Triangle dimensions must be positive");
        }
    }
    
    void draw() const override {
        std::cout << "Drawing Triangle: base=" << base_ << ", height=" << height_ << std::endl;
    }
    
    std::string getType() const override {
        return "Triangle";
    }
    
    double getArea() const override {
        return 0.5 * base_ * height_;
    }
    
    double getPerimeter() const override {
        // Simplified calculation for isosceles triangle
        double side = std::sqrt((base_/2) * (base_/2) + height_ * height_);
        return base_ + 2 * side;
    }
    
    void scale(double factor) override {
        if (factor <= 0) {
            throw std::invalid_argument("Scale factor must be positive");
        }
        base_ *= factor;
        height_ *= factor;
    }
    
    double getBase() const { return base_; }
    double getHeight() const { return height_; }
    void setDimensions(double base, double height) {
        if (base <= 0 || height <= 0) {
            throw std::invalid_argument("Triangle dimensions must be positive");
        }
        base_ = base;
        height_ = height;
    }
};

// Registry-based Factory
class ShapeRegistry {
private:
    std::map<std::string, std::function<std::unique_ptr<Shape>()>> creators_;
    
public:
    template<typename T>
    void registerCreator(const std::string& name) {
        creators_[name] = []() { return std::make_unique<T>(); };
    }
    
    template<typename T, typename... Args>
    void registerCreatorWithArgs(const std::string& name, Args... defaultArgs) {
        creators_[name] = [defaultArgs...]() { 
            return std::make_unique<T>(defaultArgs...); 
        };
    }
    
    std::unique_ptr<Shape> create(const std::string& name) const {
        auto it = creators_.find(name);
        if (it != creators_.end()) {
            return it->second();
        }
        throw std::runtime_error("Unknown shape type: " + name);
    }
    
    std::vector<std::string> getAvailableTypes() const {
        std::vector<std::string> types;
        for (const auto& pair : creators_) {
            types.push_back(pair.first);
        }
        return types;
    }
    
    bool isTypeRegistered(const std::string& name) const {
        return creators_.find(name) != creators_.end();
    }
};

// Singleton Registry Instance
class ShapeFactory {
private:
    static ShapeRegistry& getRegistry() {
        static ShapeRegistry registry;
        static bool initialized = false;
        
        if (!initialized) {
            registry.registerCreator<Circle>("circle");
            registry.registerCreator<Rectangle>("rectangle");
            registry.registerCreator<Triangle>("triangle");
            
            // Register with default parameters
            registry.registerCreatorWithArgs<Circle>("unit_circle", 1.0);
            registry.registerCreatorWithArgs<Rectangle>("unit_square", 1.0, 1.0);
            registry.registerCreatorWithArgs<Triangle>("unit_triangle", 1.0, 1.0);
            
            initialized = true;
        }
        
        return registry;
    }
    
public:
    static std::unique_ptr<Shape> create(const std::string& type) {
        return getRegistry().create(type);
    }
    
    template<typename T>
    static void registerType(const std::string& name) {
        getRegistry().registerCreator<T>(name);
    }
    
    static std::vector<std::string> getAvailableTypes() {
        return getRegistry().getAvailableTypes();
    }
    
    static bool isTypeSupported(const std::string& type) {
        return getRegistry().isTypeRegistered(type);
    }
};

// Implementation of static factory method
std::unique_ptr<Shape> Shape::create(const std::string& type) {
    return ShapeFactory::create(type);
}

// Template factory method implementation
template<typename T, typename... Args>
std::unique_ptr<Shape> Shape::create(Args&&... args) {
    static_assert(std::is_base_of_v<Shape, T>, "T must be derived from Shape");
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// Advanced: Parameterized Factory
class ParameterizedShapeFactory {
public:
    static std::unique_ptr<Shape> createCircle(double radius) {
        return std::make_unique<Circle>(radius);
    }
    
    static std::unique_ptr<Shape> createRectangle(double width, double height) {
        return std::make_unique<Rectangle>(width, height);
    }
    
    static std::unique_ptr<Shape> createTriangle(double base, double height) {
        return std::make_unique<Triangle>(base, height);
    }
    
    static std::unique_ptr<Shape> createFromString(const std::string& specification) {
        // Parse specification like "circle:5.0" or "rectangle:3.0,4.0"
        size_t colonPos = specification.find(':');
        if (colonPos == std::string::npos) {
            throw std::invalid_argument("Invalid specification format");
        }
        
        std::string type = specification.substr(0, colonPos);
        std::string params = specification.substr(colonPos + 1);
        
        if (type == "circle") {
            double radius = std::stod(params);
            return createCircle(radius);
        } else if (type == "rectangle") {
            size_t commaPos = params.find(',');
            if (commaPos == std::string::npos) {
                throw std::invalid_argument("Rectangle requires width,height");
            }
            double width = std::stod(params.substr(0, commaPos));
            double height = std::stod(params.substr(commaPos + 1));
            return createRectangle(width, height);
        } else if (type == "triangle") {
            size_t commaPos = params.find(',');
            if (commaPos == std::string::npos) {
                throw std::invalid_argument("Triangle requires base,height");
            }
            double base = std::stod(params.substr(0, commaPos));
            double height = std::stod(params.substr(commaPos + 1));
            return createTriangle(base, height);
        } else {
            throw std::invalid_argument("Unknown shape type: " + type);
        }
    }
};

// Configuration-based Factory
class ConfigurableShapeFactory {
private:
    std::map<std::string, std::map<std::string, double>> defaultParams_;
    
public:
    void setDefaultParameters(const std::string& type, 
                            const std::map<std::string, double>& params) {
        defaultParams_[type] = params;
    }
    
    std::unique_ptr<Shape> create(const std::string& type) {
        auto it = defaultParams_.find(type);
        if (it == defaultParams_.end()) {
            return ShapeFactory::create(type);
        }
        
        const auto& params = it->second;
        
        if (type == "circle") {
            double radius = params.count("radius") ? params.at("radius") : 1.0;
            return std::make_unique<Circle>(radius);
        } else if (type == "rectangle") {
            double width = params.count("width") ? params.at("width") : 1.0;
            double height = params.count("height") ? params.at("height") : 1.0;
            return std::make_unique<Rectangle>(width, height);
        } else if (type == "triangle") {
            double base = params.count("base") ? params.at("base") : 1.0;
            double height = params.count("height") ? params.at("height") : 1.0;
            return std::make_unique<Triangle>(base, height);
        }
        
        return ShapeFactory::create(type);
    }
};

// Drawing Canvas - Client class
class Canvas {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;
    
public:
    void addShape(std::unique_ptr<Shape> shape) {
        shapes_.push_back(std::move(shape));
    }
    
    void drawAll() const {
        std::cout << "\n=== Drawing Canvas ===" << std::endl;
        for (size_t i = 0; i < shapes_.size(); ++i) {
            std::cout << "Shape " << i + 1 << ": ";
            shapes_[i]->draw();
            std::cout << "  Type: " << shapes_[i]->getType()
                      << ", Area: " << shapes_[i]->getArea()
                      << ", Perimeter: " << shapes_[i]->getPerimeter() << std::endl;
        }
        std::cout << "Total shapes: " << shapes_.size() << std::endl;
    }
    
    void scaleAll(double factor) {
        std::cout << "\nScaling all shapes by factor: " << factor << std::endl;
        for (auto& shape : shapes_) {
            shape->scale(factor);
        }
    }
    
    double getTotalArea() const {
        double total = 0.0;
        for (const auto& shape : shapes_) {
            total += shape->getArea();
        }
        return total;
    }
    
    size_t getShapeCount() const {
        return shapes_.size();
    }
    
    void clear() {
        shapes_.clear();
    }
    
    std::vector<std::unique_ptr<Shape>> removeShapesByType(const std::string& type) {
        std::vector<std::unique_ptr<Shape>> removed;
        auto it = std::remove_if(shapes_.begin(), shapes_.end(),
            [&type, &removed](std::unique_ptr<Shape>& shape) {
                if (shape->getType() == type) {
                    removed.push_back(std::move(shape));
                    return true;
                }
                return false;
            });
        shapes_.erase(it, shapes_.end());
        return removed;
    }
};
```

## Usage Examples

### Basic Factory Usage
```cpp
int main() {
    try {
        std::cout << "=== Basic Factory Method Usage ===" << std::endl;
        
        // Method 1: Using static factory method
        auto circle = Shape::create("circle");
        auto rectangle = Shape::create("rectangle");
        auto triangle = Shape::create("triangle");
        
        circle->draw();
        rectangle->draw();
        triangle->draw();
        
        // Method 2: Template factory method with parameters
        auto customCircle = Shape::create<Circle>(5.0);
        auto customRect = Shape::create<Rectangle>(3.0, 4.0);
        auto customTri = Shape::create<Triangle>(6.0, 8.0);
        
        std::cout << "\nCustom shapes:" << std::endl;
        customCircle->draw();
        customRect->draw();
        customTri->draw();
        
        // Method 3: Parameterized factory
        auto paramCircle = ParameterizedShapeFactory::createCircle(2.5);
        auto paramRect = ParameterizedShapeFactory::createRectangle(4.0, 6.0);
        
        std::cout << "\nParameterized factory:" << std::endl;
        paramCircle->draw();
        paramRect->draw();
        
        // Method 4: String-based factory
        auto stringCircle = ParameterizedShapeFactory::createFromString("circle:7.5");
        auto stringRect = ParameterizedShapeFactory::createFromString("rectangle:2.0,3.0");
        
        std::cout << "\nString-based factory:" << std::endl;
        stringCircle->draw();
        stringRect->draw();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
```

### Advanced Usage with Canvas
```cpp
void demonstrateCanvasUsage() {
    Canvas canvas;
    
    // Add shapes using different factory methods
    canvas.addShape(Shape::create("circle"));
    canvas.addShape(ParameterizedShapeFactory::createRectangle(5.0, 3.0));
    canvas.addShape(Shape::create<Triangle>(4.0, 6.0));
    canvas.addShape(ParameterizedShapeFactory::createFromString("circle:2.0"));
    
    canvas.drawAll();
    
    std::cout << "\nTotal area: " << canvas.getTotalArea() << std::endl;
    
    // Scale all shapes
    canvas.scaleAll(1.5);
    canvas.drawAll();
    
    std::cout << "\nTotal area after scaling: " << canvas.getTotalArea() << std::endl;
}
```

### Configuration-Based Factory
```cpp
void demonstrateConfigurableFactory() {
    ConfigurableShapeFactory factory;
    
    // Set default parameters
    factory.setDefaultParameters("circle", {{"radius", 10.0}});
    factory.setDefaultParameters("rectangle", {{"width", 8.0}, {"height", 6.0}});
    factory.setDefaultParameters("triangle", {{"base", 12.0}, {"height", 9.0}});
    
    std::cout << "\n=== Configurable Factory ===" << std::endl;
    
    auto circle = factory.create("circle");
    auto rectangle = factory.create("rectangle");
    auto triangle = factory.create("triangle");
    
    circle->draw();
    rectangle->draw();
    triangle->draw();
}
```

### Registry Usage
```cpp
void demonstrateRegistry() {
    std::cout << "\n=== Registry-based Factory ===" << std::endl;
    
    // Show available types
    auto types = ShapeFactory::getAvailableTypes();
    std::cout << "Available shape types: ";
    for (const auto& type : types) {
        std::cout << type << " ";
    }
    std::cout << std::endl;
    
    // Create shapes
    for (const auto& type : types) {
        if (ShapeFactory::isTypeSupported(type)) {
            auto shape = ShapeFactory::create(type);
            shape->draw();
        }
    }
}
```

## Real-World Applications

### 1. **Document Processing System**
```cpp
// Document factory for different file formats
class Document {
public:
    virtual ~Document() = default;
    virtual void open(const std::string& filename) = 0;
    virtual void save(const std::string& filename) = 0;
    virtual std::string getContent() const = 0;
    virtual void setContent(const std::string& content) = 0;
    virtual std::string getFormat() const = 0;
    
    static std::unique_ptr<Document> create(const std::string& format);
};

class PDFDocument : public Document {
private:
    std::string content_;
    
public:
    void open(const std::string& filename) override {
        std::cout << "Opening PDF: " << filename << std::endl;
        // PDF-specific opening logic
    }
    
    void save(const std::string& filename) override {
        std::cout << "Saving as PDF: " << filename << std::endl;
        // PDF-specific saving logic
    }
    
    std::string getContent() const override { return content_; }
    void setContent(const std::string& content) override { content_ = content; }
    std::string getFormat() const override { return "PDF"; }
};

class WordDocument : public Document {
private:
    std::string content_;
    
public:
    void open(const std::string& filename) override {
        std::cout << "Opening Word document: " << filename << std::endl;
        // Word-specific opening logic
    }
    
    void save(const std::string& filename) override {
        std::cout << "Saving as Word document: " << filename << std::endl;
        // Word-specific saving logic
    }
    
    std::string getContent() const override { return content_; }
    void setContent(const std::string& content) override { content_ = content; }
    std::string getFormat() const override { return "DOCX"; }
};

class TextDocument : public Document {
private:
    std::string content_;
    
public:
    void open(const std::string& filename) override {
        std::cout << "Opening text file: " << filename << std::endl;
        // Text file opening logic
    }
    
    void save(const std::string& filename) override {
        std::cout << "Saving as text file: " << filename << std::endl;
        // Text file saving logic
    }
    
    std::string getContent() const override { return content_; }
    void setContent(const std::string& content) override { content_ = content; }
    std::string getFormat() const override { return "TXT"; }
};

// Document factory implementation
std::unique_ptr<Document> Document::create(const std::string& format) {
    if (format == "pdf") return std::make_unique<PDFDocument>();
    if (format == "docx") return std::make_unique<WordDocument>();
    if (format == "txt") return std::make_unique<TextDocument>();
    throw std::runtime_error("Unsupported document format: " + format);
}

// Document processor using factory
class DocumentProcessor {
public:
    void processDocument(const std::string& inputFile, const std::string& outputFormat) {
        // Determine input format from file extension
        std::string inputFormat = getFileExtension(inputFile);
        
        auto inputDoc = Document::create(inputFormat);
        inputDoc->open(inputFile);
        
        auto outputDoc = Document::create(outputFormat);
        outputDoc->setContent(inputDoc->getContent());
        
        std::string outputFile = changeFileExtension(inputFile, outputFormat);
        outputDoc->save(outputFile);
    }
    
private:
    std::string getFileExtension(const std::string& filename) {
        size_t lastDot = filename.find_last_of('.');
        if (lastDot != std::string::npos) {
            return filename.substr(lastDot + 1);
        }
        return "txt"; // Default
    }
    
    std::string changeFileExtension(const std::string& filename, const std::string& newExt) {
        size_t lastDot = filename.find_last_of('.');
        if (lastDot != std::string::npos) {
            return filename.substr(0, lastDot + 1) + newExt;
        }
        return filename + "." + newExt;
    }
};
```

### 2. **Game Character Factory**
```cpp
// Game character factory
class GameCharacter {
public:
    virtual ~GameCharacter() = default;
    virtual void attack() = 0;
    virtual void defend() = 0;
    virtual void move() = 0;
    virtual int getHealth() const = 0;
    virtual int getAttackPower() const = 0;
    virtual std::string getClass() const = 0;
    
    static std::unique_ptr<GameCharacter> create(const std::string& characterClass);
};

class Warrior : public GameCharacter {
private:
    int health_ = 100;
    int attackPower_ = 20;
    
public:
    void attack() override {
        std::cout << "Warrior swings sword! Damage: " << attackPower_ << std::endl;
    }
    
    void defend() override {
        std::cout << "Warrior raises shield!" << std::endl;
    }
    
    void move() override {
        std::cout << "Warrior marches forward" << std::endl;
    }
    
    int getHealth() const override { return health_; }
    int getAttackPower() const override { return attackPower_; }
    std::string getClass() const override { return "Warrior"; }
};

class Mage : public GameCharacter {
private:
    int health_ = 80;
    int attackPower_ = 30;
    
public:
    void attack() override {
        std::cout << "Mage casts fireball! Damage: " << attackPower_ << std::endl;
    }
    
    void defend() override {
        std::cout << "Mage casts magic shield!" << std::endl;
    }
    
    void move() override {
        std::cout << "Mage teleports" << std::endl;
    }
    
    int getHealth() const override { return health_; }
    int getAttackPower() const override { return attackPower_; }
    std::string getClass() const override { return "Mage"; }
};

class Archer : public GameCharacter {
private:
    int health_ = 90;
    int attackPower_ = 25;
    
public:
    void attack() override {
        std::cout << "Archer shoots arrow! Damage: " << attackPower_ << std::endl;
    }
    
    void defend() override {
        std::cout << "Archer dodges!" << std::endl;
    }
    
    void move() override {
        std::cout << "Archer moves stealthily" << std::endl;
    }
    
    int getHealth() const override { return health_; }
    int getAttackPower() const override { return attackPower_; }
    std::string getClass() const override { return "Archer"; }
};

std::unique_ptr<GameCharacter> GameCharacter::create(const std::string& characterClass) {
    if (characterClass == "warrior") return std::make_unique<Warrior>();
    if (characterClass == "mage") return std::make_unique<Mage>();
    if (characterClass == "archer") return std::make_unique<Archer>();
    throw std::runtime_error("Unknown character class: " + characterClass);
}

// Game using character factory
class Game {
private:
    std::vector<std::unique_ptr<GameCharacter>> players_;
    
public:
    void createPlayer(const std::string& characterClass) {
        auto character = GameCharacter::create(characterClass);
        std::cout << "Created " << character->getClass() 
                  << " (Health: " << character->getHealth() 
                  << ", Attack: " << character->getAttackPower() << ")" << std::endl;
        players_.push_back(std::move(character));
    }
    
    void simulateBattle() {
        if (players_.size() < 2) {
            std::cout << "Need at least 2 players for battle!" << std::endl;
            return;
        }
        
        std::cout << "\n=== Battle Simulation ===" << std::endl;
        for (auto& player : players_) {
            player->attack();
            player->defend();
            player->move();
            std::cout << "---" << std::endl;
        }
    }
};
```

### 3. **Network Protocol Factory**
```cpp
// Network protocol factory
class NetworkProtocol {
public:
    virtual ~NetworkProtocol() = default;
    virtual void connect(const std::string& address, int port) = 0;
    virtual void send(const std::string& data) = 0;
    virtual std::string receive() = 0;
    virtual void disconnect() = 0;
    virtual std::string getProtocolName() const = 0;
    
    static std::unique_ptr<NetworkProtocol> create(const std::string& protocol);
};

class TCPProtocol : public NetworkProtocol {
private:
    bool connected_ = false;
    std::string address_;
    int port_;
    
public:
    void connect(const std::string& address, int port) override {
        address_ = address;
        port_ = port;
        connected_ = true;
        std::cout << "TCP connected to " << address << ":" << port << std::endl;
    }
    
    void send(const std::string& data) override {
        if (!connected_) throw std::runtime_error("Not connected");
        std::cout << "TCP sending: " << data << std::endl;
    }
    
    std::string receive() override {
        if (!connected_) throw std::runtime_error("Not connected");
        std::cout << "TCP receiving data..." << std::endl;
        return "TCP_DATA";
    }
    
    void disconnect() override {
        if (connected_) {
            std::cout << "TCP disconnected" << std::endl;
            connected_ = false;
        }
    }
    
    std::string getProtocolName() const override { return "TCP"; }
};

class UDPProtocol : public NetworkProtocol {
private:
    std::string address_;
    int port_;
    
public:
    void connect(const std::string& address, int port) override {
        address_ = address;
        port_ = port;
        std::cout << "UDP configured for " << address << ":" << port << std::endl;
    }
    
    void send(const std::string& data) override {
        std::cout << "UDP sending datagram: " << data << std::endl;
    }
    
    std::string receive() override {
        std::cout << "UDP receiving datagram..." << std::endl;
        return "UDP_DATA";
    }
    
    void disconnect() override {
        std::cout << "UDP connection closed" << std::endl;
    }
    
    std::string getProtocolName() const override { return "UDP"; }
};

class HTTPProtocol : public NetworkProtocol {
private:
    bool connected_ = false;
    std::string baseUrl_;
    
public:
    void connect(const std::string& address, int port) override {
        baseUrl_ = "http://" + address + ":" + std::to_string(port);
        connected_ = true;
        std::cout << "HTTP client configured for " << baseUrl_ << std::endl;
    }
    
    void send(const std::string& data) override {
        if (!connected_) throw std::runtime_error("Not connected");
        std::cout << "HTTP POST: " << data << " to " << baseUrl_ << std::endl;
    }
    
    std::string receive() override {
        if (!connected_) throw std::runtime_error("Not connected");
        std::cout << "HTTP GET from " << baseUrl_ << std::endl;
        return "HTTP_RESPONSE";
    }
    
    void disconnect() override {
        if (connected_) {
            std::cout << "HTTP connection closed" << std::endl;
            connected_ = false;
        }
    }
    
    std::string getProtocolName() const override { return "HTTP"; }
};

std::unique_ptr<NetworkProtocol> NetworkProtocol::create(const std::string& protocol) {
    if (protocol == "tcp") return std::make_unique<TCPProtocol>();
    if (protocol == "udp") return std::make_unique<UDPProtocol>();
    if (protocol == "http") return std::make_unique<HTTPProtocol>();
    throw std::runtime_error("Unsupported protocol: " + protocol);
}

// Network client using protocol factory
class NetworkClient {
private:
    std::unique_ptr<NetworkProtocol> protocol_;
    
public:
    void setProtocol(const std::string& protocolName) {
        protocol_ = NetworkProtocol::create(protocolName);
        std::cout << "Protocol set to: " << protocol_->getProtocolName() << std::endl;
    }
    
    void communicate(const std::string& address, int port, const std::string& message) {
        if (!protocol_) {
            throw std::runtime_error("No protocol set");
        }
        
        protocol_->connect(address, port);
        protocol_->send(message);
        std::string response = protocol_->receive();
        std::cout << "Received: " << response << std::endl;
        protocol_->disconnect();
    }
};
```

## Advanced Factory Method Patterns

### 1. **Lazy Factory Method**
```cpp
template<typename T>
class LazyFactory {
private:
    mutable std::unique_ptr<T> instance_;
    std::function<std::unique_ptr<T>()> creator_;
    
public:
    explicit LazyFactory(std::function<std::unique_ptr<T>()> creator)
        : creator_(creator) {}
    
    T& get() const {
        if (!instance_) {
            instance_ = creator_();
        }
        return *instance_;
    }
    
    void reset() {
        instance_.reset();
    }
    
    bool isInitialized() const {
        return instance_ != nullptr;
    }
};

// Usage
LazyFactory<Circle> lazyCircle([]() { return std::make_unique<Circle>(5.0); });
// Circle is created only when first accessed
Circle& circle = lazyCircle.get();
```

### 2. **Caching Factory Method**
```cpp
template<typename T>
class CachingFactory {
private:
    mutable std::map<std::string, std::weak_ptr<T>> cache_;
    std::function<std::shared_ptr<T>(const std::string&)> creator_;
    
public:
    explicit CachingFactory(std::function<std::shared_ptr<T>(const std::string&)> creator)
        : creator_(creator) {}
    
    std::shared_ptr<T> get(const std::string& key) const {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            if (auto existing = it->second.lock()) {
                return existing;
            } else {
                cache_.erase(it); // Remove expired weak_ptr
            }
        }
        
        auto newInstance = creator_(key);
        cache_[key] = newInstance;
        return newInstance;
    }
    
    void clearCache() {
        cache_.clear();
    }
    
    size_t getCacheSize() const {
        // Clean up expired entries
        auto it = cache_.begin();
        while (it != cache_.end()) {
            if (it->second.expired()) {
                it = cache_.erase(it);
            } else {
                ++it;
            }
        }
        return cache_.size();
    }
};

// Usage
CachingFactory<Shape> shapeCache([](const std::string& type) {
    return std::shared_ptr<Shape>(Shape::create(type));
});

auto shape1 = shapeCache.get("circle");
auto shape2 = shapeCache.get("circle"); // Returns cached instance
```

### 3. **Asynchronous Factory Method**
```cpp
#include <future>
#include <thread>

template<typename T>
class AsyncFactory {
public:
    template<typename... Args>
    static std::future<std::unique_ptr<T>> createAsync(Args&&... args) {
        return std::async(std::launch::async, [args...]() {
            // Simulate expensive creation process
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return std::make_unique<T>(args...);
        });
    }
    
    template<typename... Args>
    static std::vector<std::future<std::unique_ptr<T>>> createMultipleAsync(
        size_t count, Args&&... args) {
        std::vector<std::future<std::unique_ptr<T>>> futures;
        
        for (size_t i = 0; i < count; ++i) {
            futures.push_back(createAsync(args...));
        }
        
        return futures;
    }
};

// Usage
auto futureCircle = AsyncFactory<Circle>::createAsync(5.0);
auto futureShapes = AsyncFactory<Rectangle>::createMultipleAsync(3, 4.0, 6.0);

// Get results when ready
auto circle = futureCircle.get();

std::vector<std::unique_ptr<Rectangle>> rectangles;
for (auto& future : futureShapes) {
    rectangles.push_back(future.get());
}
```

## Performance Considerations

### Memory Usage Optimization
```cpp
// Object pool for expensive objects
template<typename T>
class FactoryPool {
private:
    std::queue<std::unique_ptr<T>> pool_;
    std::function<std::unique_ptr<T>()> factory_;
    std::mutex mutex_;
    size_t maxSize_;
    
public:
    explicit FactoryPool(std::function<std::unique_ptr<T>()> factory, size_t maxSize = 100)
        : factory_(factory), maxSize_(maxSize) {}
    
    std::unique_ptr<T> acquire() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pool_.empty()) {
            return factory_();
        } else {
            auto obj = std::move(pool_.front());
            pool_.pop();
            return obj;
        }
    }
    
    void release(std::unique_ptr<T> obj) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pool_.size() < maxSize_) {
            pool_.push(std::move(obj));
        }
        // If pool is full, object is automatically destroyed
    }
    
    size_t getPoolSize() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return pool_.size();
    }
};

// Custom deleter for automatic return to pool
template<typename T>
class PoolDeleter {
private:
    FactoryPool<T>* pool_;
    
public:
    explicit PoolDeleter(FactoryPool<T>* pool) : pool_(pool) {}
    
    void operator()(T* ptr) {
        if (pool_ && ptr) {
            pool_->release(std::unique_ptr<T>(ptr));
        }
    }
};

// Factory with automatic pooling
template<typename T>
class PooledFactory {
private:
    FactoryPool<T> pool_;
    
public:
    explicit PooledFactory(std::function<std::unique_ptr<T>()> factory)
        : pool_(factory) {}
    
    std::unique_ptr<T, PoolDeleter<T>> create() {
        auto obj = pool_.acquire();
        return std::unique_ptr<T, PoolDeleter<T>>(
            obj.release(), PoolDeleter<T>(&pool_));
    }
};
```

### Performance Benchmarking
```cpp
#include <chrono>

void benchmarkFactoryMethods() {
    const int iterations = 100000;
    
    // Direct construction
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto circle = std::make_unique<Circle>(1.0);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto directTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Factory method
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto circle = Shape::create("circle");
    }
    end = std::chrono::high_resolution_clock::now();
    auto factoryTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Template factory
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto circle = Shape::create<Circle>(1.0);
    }
    end = std::chrono::high_resolution_clock::now();
    auto templateTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Pooled factory
    PooledFactory<Circle> pooledFactory([]() { return std::make_unique<Circle>(1.0); });
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto circle = pooledFactory.create();
    }
    end = std::chrono::high_resolution_clock::now();
    auto pooledTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Performance Benchmark Results:" << std::endl;
    std::cout << "Direct construction: " << directTime.count() << " μs" << std::endl;
    std::cout << "Factory method: " << factoryTime.count() << " μs" << std::endl;
    std::cout << "Template factory: " << templateTime.count() << " μs" << std::endl;
    std::cout << "Pooled factory: " << pooledTime.count() << " μs" << std::endl;
}
```

## Testing Factory Method Pattern

```cpp
#include <gtest/gtest.h>

class FactoryMethodTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code
    }
};

TEST_F(FactoryMethodTest, BasicFactoryCreatesCorrectShapes) {
    auto circle = Shape::create("circle");
    auto rectangle = Shape::create("rectangle");
    auto triangle = Shape::create("triangle");
    
    EXPECT_EQ("Circle", circle->getType());
    EXPECT_EQ("Rectangle", rectangle->getType());
    EXPECT_EQ("Triangle", triangle->getType());
}

TEST_F(FactoryMethodTest, TemplateFactoryWorksWithParameters) {
    auto circle = Shape::create<Circle>(5.0);
    auto rectangle = Shape::create<Rectangle>(3.0, 4.0);
    
    EXPECT_DOUBLE_EQ(5.0, dynamic_cast<Circle*>(circle.get())->getRadius());
    EXPECT_DOUBLE_EQ(3.0, dynamic_cast<Rectangle*>(rectangle.get())->getWidth());
    EXPECT_DOUBLE_EQ(4.0, dynamic_cast<Rectangle*>(rectangle.get())->getHeight());
}

TEST_F(FactoryMethodTest, ParameterizedFactoryWorksWithStrings) {
    auto circle = ParameterizedShapeFactory::createFromString("circle:7.5");
    auto rectangle = ParameterizedShapeFactory::createFromString("rectangle:2.0,3.0");
    
    EXPECT_EQ("Circle", circle->getType());
    EXPECT_EQ("Rectangle", rectangle->getType());
    EXPECT_DOUBLE_EQ(7.5, dynamic_cast<Circle*>(circle.get())->getRadius());
}

TEST_F(FactoryMethodTest, FactoryThrowsForInvalidTypes) {
    EXPECT_THROW(Shape::create("invalid"), std::runtime_error);
    EXPECT_THROW(ParameterizedShapeFactory::createFromString("invalid:1.0"), 
                 std::invalid_argument);
}

TEST_F(FactoryMethodTest, ShapeCalculationsAreCorrect) {
    auto circle = Shape::create<Circle>(2.0);
    auto rectangle = Shape::create<Rectangle>(3.0, 4.0);
    
    EXPECT_NEAR(12.566, circle->getArea(), 0.01);  // π * 2²
    EXPECT_NEAR(12.566, circle->getPerimeter(), 0.01);  // 2π * 2
    EXPECT_DOUBLE_EQ(12.0, rectangle->getArea());  // 3 * 4
    EXPECT_DOUBLE_EQ(14.0, rectangle->getPerimeter());  // 2 * (3 + 4)
}

TEST_F(FactoryMethodTest, ShapeScalingWorks) {
    auto circle = Shape::create<Circle>(2.0);
    double originalArea = circle->getArea();
    
    circle->scale(2.0);
    
    EXPECT_NEAR(4.0 * originalArea, circle->getArea(), 0.01);
}

TEST_F(FactoryMethodTest, CanvasOperationsWork) {
    Canvas canvas;
    
    canvas.addShape(Shape::create<Circle>(1.0));
    canvas.addShape(Shape::create<Rectangle>(2.0, 3.0));
    
    EXPECT_EQ(2, canvas.getShapeCount());
    EXPECT_NEAR(9.14159, canvas.getTotalArea(), 0.01);  // π + 6
    
    canvas.scaleAll(2.0);
    EXPECT_NEAR(36.566, canvas.getTotalArea(), 0.01);  // 4π + 24
}

TEST_F(FactoryMethodTest, RegistryWorks) {
    auto types = ShapeFactory::getAvailableTypes();
    
    EXPECT_TRUE(std::find(types.begin(), types.end(), "circle") != types.end());
    EXPECT_TRUE(std::find(types.begin(), types.end(), "rectangle") != types.end());
    EXPECT_TRUE(std::find(types.begin(), types.end(), "triangle") != types.end());
    
    EXPECT_TRUE(ShapeFactory::isTypeSupported("circle"));
    EXPECT_FALSE(ShapeFactory::isTypeSupported("invalid"));
}
```

## Common Pitfalls and Solutions

### 1. **Memory Leaks with Raw Pointers**
```cpp
// ❌ Problematic - potential memory leaks
class BadShape {
public:
    static Shape* create(const std::string& type) {
        if (type == "circle") return new Circle();  // Raw pointer!
        return nullptr;
    }
};

// Client code
Shape* shape = BadShape::create("circle");
// If exception occurs, shape is leaked!

// ✅ Better - use smart pointers
class GoodShape {
public:
    static std::unique_ptr<Shape> create(const std::string& type) {
        if (type == "circle") return std::make_unique<Circle>();
        return nullptr;
    }
};

// Client code
auto shape = GoodShape::create("circle");
// Automatic cleanup even with exceptions
```

### 2. **Missing Error Handling**
```cpp
// ❌ Problematic - silent failures
Shape* BadFactory::create(const std::string& type) {
    if (type == "circle") return new Circle();
    return nullptr;  // Silent failure
}

// ✅ Better - explicit error handling
std::unique_ptr<Shape> GoodFactory::create(const std::string& type) {
    if (type == "circle") return std::make_unique<Circle>();
    throw std::runtime_error("Unknown shape type: " + type);
}
```

### 3. **Thread Safety Issues**
```cpp
// ❌ Problematic - not thread-safe
class UnsafeRegistry {
private:
    static std::map<std::string, std::function<std::unique_ptr<Shape>()>> creators_;
    
public:
    static void registerCreator(const std::string& name, 
                               std::function<std::unique_ptr<Shape>()> creator) {
        creators_[name] = creator;  // Race condition!
    }
};

// ✅ Better - thread-safe
class SafeRegistry {
private:
    static std::map<std::string, std::function<std::unique_ptr<Shape>()>> creators_;
    static std::mutex mutex_;
    
public:
    static void registerCreator(const std::string& name, 
                               std::function<std::unique_ptr<Shape>()> creator) {
        std::lock_guard<std::mutex> lock(mutex_);
        creators_[name] = creator;
    }
};
```

### 4. **Parameter Validation**
```cpp
// ❌ Problematic - no validation
class BadCircle : public Shape {
public:
    explicit BadCircle(double radius) : radius_(radius) {}
    // No validation - could create invalid circle
    
private:
    double radius_;
};

// ✅ Better - proper validation
class GoodCircle : public Shape {
public:
    explicit GoodCircle(double radius) : radius_(radius) {
        if (radius <= 0) {
            throw std::invalid_argument("Circle radius must be positive");
        }
    }
    
private:
    double radius_;
};
```

## Best Practices

### 1. **Use Smart Pointers**
- Always return `std::unique_ptr` or `std::shared_ptr`
- Avoid raw pointer ownership
- Enable RAII and automatic cleanup

### 2. **Validate Parameters**
- Check input parameters in constructors
- Throw meaningful exceptions for invalid input
- Document parameter requirements

### 3. **Thread Safety**
- Use proper synchronization for registry operations
- Consider thread-local storage for performance
- Use atomic operations where appropriate

### 4. **Error Handling**
- Throw exceptions for invalid types
- Provide meaningful error messages
- Use custom exception types when appropriate

### 5. **Performance Optimization**
- Consider object pooling for expensive objects
- Use template specialization for compile-time optimization
- Cache frequently created objects

### 6. **Design for Extensibility**
- Use registry pattern for dynamic type registration
- Support plugin architectures
- Keep factory interfaces minimal

## Comparison with Other Creational Patterns

| Pattern | Purpose | Key Difference |
|---------|---------|----------------|
| **Factory Method** | Create single objects | Single product creation method |
| **Abstract Factory** | Create families of objects | Multiple related products |
| **Builder** | Construct complex objects | Step-by-step construction |
| **Singleton** | Ensure single instance | Instance management |
| **Prototype** | Clone existing objects | Object copying |

## When to Use Factory Method

### ✅ **Use When:**
- Object creation logic is complex
- Product types are determined at runtime
- You want to decouple object creation from usage
- New product types need to be added frequently
- Object creation involves validation or initialization

### ❌ **Don't Use When:**
- Object creation is simple and straightforward
- Product types are fixed and rarely change
- Performance is critical and factory overhead is significant
- Only one or two product types exist

## Conclusion

The Factory Method pattern is essential for:
- **Decoupling object creation** from client code
- **Runtime type selection** based on parameters
- **Easy extensibility** for new product types
- **Centralized creation logic** and validation
- **Polymorphic object creation** through common interfaces

Key benefits:
- **Flexibility** in object creation and configuration
- **Maintainability** through centralized creation logic
- **Testability** through dependency injection
- **Extensibility** for new product types

The pattern is particularly valuable in systems requiring dynamic object creation, plugin architectures, and scenarios where the exact types of objects to be created are determined at runtime based on configuration or user input.
