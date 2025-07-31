# Adapter Design Pattern in C++

## Overview

The **Adapter Design Pattern** is a structural design pattern that allows incompatible interfaces to work together. It acts as a bridge between two incompatible interfaces by wrapping an existing class with a new interface. This pattern is particularly useful when you need to integrate legacy code, third-party libraries, or when different parts of a system have incompatible interfaces.

## Key Concepts

- **Target Interface**: The interface that the client expects to use
- **Adaptee**: The existing class with an incompatible interface
- **Adapter**: The class that bridges the gap between Target and Adaptee
- **Client**: The code that uses the Target interface
- **Interface Translation**: Converting method calls from one interface to another

## Problem Solved

Without the Adapter pattern:
- **Incompatible interfaces** prevent code reuse
- **Legacy code integration** becomes difficult
- **Third-party library integration** requires extensive modifications
- **Interface mismatches** force complete rewrites

## Solution Structure

### Object Adapter (Composition)
```
┌─────────────────┐    ┌──────────────────┐
│     Client      │───▶│     Target       │
└─────────────────┘    │   (Interface)    │
                       │ + request()      │
                       └──────────────────┘
                                △
                                │
                       ┌────────┴────────┐
                       │     Adapter     │
                       │ + request()     │───┐
                       └─────────────────┘   │
                                             │
                                             ▼
                                    ┌──────────────────┐
                                    │     Adaptee      │
                                    │ + specificReq()  │
                                    └──────────────────┘
```

### Class Adapter (Inheritance)
```
┌─────────────────┐    ┌──────────────────┐
│     Client      │───▶│     Target       │
└─────────────────┘    │   (Interface)    │
                       │ + request()      │
                       └──────────────────┘
                                △
                                │
                       ┌────────┴────────┐
                       │     Adapter     │───────────┐
                       │ + request()     │           │
                       └─────────────────┘           │
                                △                    │
                                │                    │
                                │              ┌─────▼─────┐
                                └──────────────│  Adaptee  │
                                               │+ specific │
                                               │  Req()    │
                                               └───────────┘
```

## Code Analysis

### Target Interface
```cpp
class Circle {
public:
    virtual void draw() = 0;
};
```
**Purpose**: Defines the interface that the client expects to use.

### Adaptee (Legacy Class)
```cpp
class StandardCircle {
public:
    StandardCircle(double radius) {
        radius_ = radius;
        cout << "StandardCircle: create. radius = " << radius_ << endl;
    }
    
    void oldDraw() {
        cout << "StandardCircle: oldDraw. " << radius_ << endl;
    }
    
private:
    double radius_;
};
```
**Purpose**: Existing class with incompatible interface that needs to be adapted.

### Adapter Implementation
```cpp
class CAdapter : public Circle, private StandardCircle {
public:
    CAdapter(double diameter) : StandardCircle(diameter/2) {
        cout << "CAdapter: create. diameter = " << diameter << endl;
    }
    
    virtual void draw() {
        cout << "CAdapter: draw." << endl;
        oldDraw();  // Delegates to adaptee's method
    }
};
```
**Purpose**: Bridges the gap between Circle interface and StandardCircle implementation.

## Advantages

### ✅ **Code Reuse**
- Reuse existing classes without modification
- Integrate legacy code into new systems
- Leverage third-party libraries with different interfaces

### ✅ **Separation of Concerns**
- Business logic separated from interface adaptation
- Clean architecture with clear responsibilities
- Adapter handles only interface translation

### ✅ **Open/Closed Principle**
- Open for extension (new adapters)
- Closed for modification (existing code unchanged)
- Add new interfaces without touching existing code

### ✅ **Single Responsibility**
- Each adapter has one reason to change
- Clear purpose: interface translation
- Focused responsibility scope

## Disadvantages

### ❌ **Code Complexity**
- Additional layer of indirection
- More classes to maintain
- Can obscure the actual functionality

### ❌ **Performance Overhead**
- Extra method calls through adapter
- Potential object creation overhead
- Additional memory usage

### ❌ **Multiple Inheritance Issues**
- Class adapter uses multiple inheritance
- Can lead to diamond problem
- Platform-specific limitations

## Modern C++ Implementation

Here's an improved, modern C++ version addressing the original code's limitations:

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>

// Target interface - what the client expects
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual std::string getType() const = 0;
    virtual double getArea() const = 0;
};

// Legacy Rectangle class (Adaptee)
class LegacyRectangle {
private:
    double width_, height_;
    
public:
    LegacyRectangle(double w, double h) : width_(w), height_(h) {
        std::cout << "LegacyRectangle created: " << width_ << "x" << height_ << std::endl;
    }
    
    void oldDraw() const {
        std::cout << "Drawing rectangle using legacy method: " 
                  << width_ << "x" << height_ << std::endl;
    }
    
    double calculateArea() const {
        return width_ * height_;
    }
    
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
    
    void setDimensions(double w, double h) {
        width_ = w;
        height_ = h;
    }
};

// Legacy Circle class with different interface
class LegacyCircle {
private:
    double radius_;
    
public:
    explicit LegacyCircle(double radius) : radius_(radius) {
        std::cout << "LegacyCircle created with radius: " << radius_ << std::endl;
    }
    
    void oldDraw() const {
        std::cout << "Drawing circle using legacy method, radius: " << radius_ << std::endl;
    }
    
    double computeArea() const {
        return 3.14159 * radius_ * radius_;
    }
    
    double getRadius() const { return radius_; }
    void setRadius(double radius) { radius_ = radius; }
};

// Object Adapter for Rectangle (using composition)
class RectangleAdapter : public Shape {
private:
    std::unique_ptr<LegacyRectangle> adaptee_;
    
public:
    explicit RectangleAdapter(std::unique_ptr<LegacyRectangle> rectangle) 
        : adaptee_(std::move(rectangle)) {}
    
    // Convenience constructor
    RectangleAdapter(double width, double height) 
        : adaptee_(std::make_unique<LegacyRectangle>(width, height)) {}
    
    void draw() const override {
        std::cout << "[ADAPTER] ";
        adaptee_->oldDraw();
    }
    
    std::string getType() const override {
        return "Rectangle (Adapted)";
    }
    
    double getArea() const override {
        return adaptee_->calculateArea();
    }
    
    // Additional adapter-specific methods
    void resize(double width, double height) {
        adaptee_->setDimensions(width, height);
    }
    
    LegacyRectangle* getLegacyObject() const {
        return adaptee_.get();
    }
};

// Class Adapter for Circle (using inheritance)
class CircleAdapter : public Shape, private LegacyCircle {
public:
    explicit CircleAdapter(double radius) : LegacyCircle(radius) {}
    
    void draw() const override {
        std::cout << "[ADAPTER] ";
        oldDraw();
    }
    
    std::string getType() const override {
        return "Circle (Adapted)";
    }
    
    double getArea() const override {
        return computeArea();
    }
    
    // Adapter-specific method
    void resize(double radius) {
        setRadius(radius);
    }
};

// Advanced: Generic Adapter Template
template<typename Adaptee, typename DrawMethod, typename AreaMethod>
class GenericAdapter : public Shape {
private:
    std::unique_ptr<Adaptee> adaptee_;
    DrawMethod drawMethod_;
    AreaMethod areaMethod_;
    std::string typeName_;
    
public:
    GenericAdapter(std::unique_ptr<Adaptee> adaptee, 
                  DrawMethod drawMethod,
                  AreaMethod areaMethod,
                  const std::string& typeName)
        : adaptee_(std::move(adaptee))
        , drawMethod_(drawMethod)
        , areaMethod_(areaMethod)
        , typeName_(typeName) {}
    
    void draw() const override {
        std::cout << "[GENERIC ADAPTER] ";
        (adaptee_.get()->*drawMethod_)();
    }
    
    std::string getType() const override {
        return typeName_ + " (Generic Adapted)";
    }
    
    double getArea() const override {
        return (adaptee_.get()->*areaMethod_)();
    }
};

// Helper function to create generic adapters
template<typename Adaptee, typename DrawMethod, typename AreaMethod>
auto makeGenericAdapter(std::unique_ptr<Adaptee> adaptee,
                       DrawMethod drawMethod,
                       AreaMethod areaMethod,
                       const std::string& typeName) {
    return std::make_unique<GenericAdapter<Adaptee, DrawMethod, AreaMethod>>(
        std::move(adaptee), drawMethod, areaMethod, typeName);
}

// Function Adapter using std::function
class FunctionAdapter : public Shape {
private:
    std::function<void()> drawFunction_;
    std::function<double()> areaFunction_;
    std::string typeName_;
    
public:
    FunctionAdapter(std::function<void()> drawFunc,
                   std::function<double()> areaFunc,
                   const std::string& typeName)
        : drawFunction_(drawFunc)
        , areaFunction_(areaFunc)
        , typeName_(typeName) {}
    
    void draw() const override {
        std::cout << "[FUNCTION ADAPTER] ";
        drawFunction_();
    }
    
    std::string getType() const override {
        return typeName_ + " (Function Adapted)";
    }
    
    double getArea() const override {
        return areaFunction_();
    }
};

// Client code - Drawing canvas
class Canvas {
private:
    std::vector<std::unique_ptr<Shape>> shapes_;
    
public:
    void addShape(std::unique_ptr<Shape> shape) {
        shapes_.push_back(std::move(shape));
    }
    
    void drawAll() const {
        std::cout << "\n=== Drawing Canvas ===" << std::endl;
        for (const auto& shape : shapes_) {
            std::cout << "Type: " << shape->getType() 
                      << ", Area: " << shape->getArea() << std::endl;
            shape->draw();
            std::cout << "---" << std::endl;
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
};
```

## Usage Examples

### Basic Adapter Usage
```cpp
int main() {
    auto canvas = std::make_unique<Canvas>();
    
    // Object Adapter - Rectangle
    auto rectAdapter = std::make_unique<RectangleAdapter>(5.0, 3.0);
    canvas->addShape(std::move(rectAdapter));
    
    // Class Adapter - Circle
    auto circleAdapter = std::make_unique<CircleAdapter>(2.5);
    canvas->addShape(std::move(circleAdapter));
    
    // Generic Adapter
    auto legacyRect = std::make_unique<LegacyRectangle>(4.0, 6.0);
    auto genericAdapter = makeGenericAdapter(
        std::move(legacyRect),
        &LegacyRectangle::oldDraw,
        &LegacyRectangle::calculateArea,
        "Rectangle"
    );
    canvas->addShape(std::move(genericAdapter));
    
    // Function Adapter with lambda
    auto legacyCircle = std::make_unique<LegacyCircle>(3.0);
    auto functionAdapter = std::make_unique<FunctionAdapter>(
        [&legacyCircle]() { legacyCircle->oldDraw(); },
        [&legacyCircle]() { return legacyCircle->computeArea(); },
        "Circle"
    );
    canvas->addShape(std::move(functionAdapter));
    
    canvas->drawAll();
    std::cout << "\nTotal area: " << canvas->getTotalArea() << std::endl;
    
    return 0;
}
```

### Advanced Usage with Legacy API Integration
```cpp
// Simulating a legacy graphics API
namespace LegacyAPI {
    class GraphicsContext {
    public:
        void setColor(int r, int g, int b) {
            std::cout << "Legacy: Setting color to RGB(" << r << "," << g << "," << b << ")" << std::endl;
        }
        
        void drawLine(int x1, int y1, int x2, int y2) {
            std::cout << "Legacy: Drawing line from (" << x1 << "," << y1 
                      << ") to (" << x2 << "," << y2 << ")" << std::endl;
        }
        
        void fillRect(int x, int y, int width, int height) {
            std::cout << "Legacy: Filling rectangle at (" << x << "," << y 
                      << ") with size " << width << "x" << height << std::endl;
        }
    };
}

// Modern graphics interface
class ModernGraphics {
public:
    virtual ~ModernGraphics() = default;
    virtual void setColor(const std::string& colorName) = 0;
    virtual void drawRectangle(double x, double y, double width, double height) = 0;
    virtual void drawLine(double x1, double y1, double x2, double y2) = 0;
};

// Adapter for legacy graphics API
class LegacyGraphicsAdapter : public ModernGraphics {
private:
    LegacyAPI::GraphicsContext& legacyContext_;
    std::map<std::string, std::tuple<int, int, int>> colorMap_;
    
    void initializeColorMap() {
        colorMap_["red"] = std::make_tuple(255, 0, 0);
        colorMap_["green"] = std::make_tuple(0, 255, 0);
        colorMap_["blue"] = std::make_tuple(0, 0, 255);
        colorMap_["black"] = std::make_tuple(0, 0, 0);
        colorMap_["white"] = std::make_tuple(255, 255, 255);
    }
    
public:
    explicit LegacyGraphicsAdapter(LegacyAPI::GraphicsContext& context)
        : legacyContext_(context) {
        initializeColorMap();
    }
    
    void setColor(const std::string& colorName) override {
        auto it = colorMap_.find(colorName);
        if (it != colorMap_.end()) {
            auto [r, g, b] = it->second;
            legacyContext_.setColor(r, g, b);
        } else {
            std::cout << "Warning: Unknown color '" << colorName 
                      << "', using black" << std::endl;
            legacyContext_.setColor(0, 0, 0);
        }
    }
    
    void drawRectangle(double x, double y, double width, double height) override {
        legacyContext_.fillRect(static_cast<int>(x), static_cast<int>(y),
                               static_cast<int>(width), static_cast<int>(height));
    }
    
    void drawLine(double x1, double y1, double x2, double y2) override {
        legacyContext_.drawLine(static_cast<int>(x1), static_cast<int>(y1),
                               static_cast<int>(x2), static_cast<int>(y2));
    }
};

void demonstrateGraphicsAdapter() {
    LegacyAPI::GraphicsContext legacyContext;
    LegacyGraphicsAdapter adapter(legacyContext);
    
    adapter.setColor("red");
    adapter.drawRectangle(10.5, 20.7, 100.3, 50.8);
    
    adapter.setColor("blue");
    adapter.drawLine(0.0, 0.0, 100.0, 100.0);
}
```

## Real-World Applications

### 1. **Database Adapter**
```cpp
// Standard database interface
class Database {
public:
    virtual ~Database() = default;
    virtual bool connect(const std::string& connectionString) = 0;
    virtual std::vector<std::string> executeQuery(const std::string& query) = 0;
    virtual void disconnect() = 0;
};

// Legacy database with different interface
class LegacyDatabase {
public:
    bool openConnection(const char* host, int port, const char* dbName) {
        std::cout << "Legacy DB: Connecting to " << host << ":" << port 
                  << "/" << dbName << std::endl;
        return true;
    }
    
    char** runSQL(const char* sql, int* rowCount) {
        std::cout << "Legacy DB: Executing SQL: " << sql << std::endl;
        *rowCount = 2;
        static char* results[] = {"Row1", "Row2", nullptr};
        return results;
    }
    
    void closeConnection() {
        std::cout << "Legacy DB: Connection closed" << std::endl;
    }
};

class DatabaseAdapter : public Database {
private:
    std::unique_ptr<LegacyDatabase> legacyDb_;
    bool connected_ = false;
    
public:
    DatabaseAdapter() : legacyDb_(std::make_unique<LegacyDatabase>()) {}
    
    bool connect(const std::string& connectionString) override {
        // Parse connection string (simplified)
        std::string host = "localhost";
        int port = 5432;
        std::string dbName = "mydb";
        
        connected_ = legacyDb_->openConnection(host.c_str(), port, dbName.c_str());
        return connected_;
    }
    
    std::vector<std::string> executeQuery(const std::string& query) override {
        if (!connected_) {
            throw std::runtime_error("Database not connected");
        }
        
        int rowCount = 0;
        char** results = legacyDb_->runSQL(query.c_str(), &rowCount);
        
        std::vector<std::string> resultVector;
        for (int i = 0; i < rowCount; ++i) {
            resultVector.emplace_back(results[i]);
        }
        
        return resultVector;
    }
    
    void disconnect() override {
        if (connected_) {
            legacyDb_->closeConnection();
            connected_ = false;
        }
    }
};
```

### 2. **File System Adapter**
```cpp
// Modern file interface
class FileSystem {
public:
    virtual ~FileSystem() = default;
    virtual std::string readFile(const std::string& path) = 0;
    virtual bool writeFile(const std::string& path, const std::string& content) = 0;
    virtual bool fileExists(const std::string& path) = 0;
};

// Legacy file operations
class LegacyFileOps {
public:
    FILE* openFile(const char* filename, const char* mode) {
        return fopen(filename, mode);
    }
    
    char* readAll(FILE* file) {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        char* buffer = new char[size + 1];
        fread(buffer, 1, size, file);
        buffer[size] = '\0';
        
        return buffer;
    }
    
    bool writeAll(FILE* file, const char* data) {
        size_t len = strlen(data);
        return fwrite(data, 1, len, file) == len;
    }
    
    void closeFile(FILE* file) {
        if (file) fclose(file);
    }
    
    bool checkFileExists(const char* filename) {
        FILE* file = fopen(filename, "r");
        if (file) {
            fclose(file);
            return true;
        }
        return false;
    }
};

class FileSystemAdapter : public FileSystem {
private:
    std::unique_ptr<LegacyFileOps> legacyOps_;
    
public:
    FileSystemAdapter() : legacyOps_(std::make_unique<LegacyFileOps>()) {}
    
    std::string readFile(const std::string& path) override {
        FILE* file = legacyOps_->openFile(path.c_str(), "r");
        if (!file) {
            throw std::runtime_error("Cannot open file: " + path);
        }
        
        char* content = legacyOps_->readAll(file);
        std::string result(content);
        delete[] content;
        
        legacyOps_->closeFile(file);
        return result;
    }
    
    bool writeFile(const std::string& path, const std::string& content) override {
        FILE* file = legacyOps_->openFile(path.c_str(), "w");
        if (!file) {
            return false;
        }
        
        bool success = legacyOps_->writeAll(file, content.c_str());
        legacyOps_->closeFile(file);
        return success;
    }
    
    bool fileExists(const std::string& path) override {
        return legacyOps_->checkFileExists(path.c_str());
    }
};
```

### 3. **Third-Party Library Integration**
```cpp
// Imagine a third-party JSON library with a different interface
namespace ThirdPartyJSON {
    class JSONParser {
    public:
        void* parseString(const char* jsonStr) {
            std::cout << "ThirdParty: Parsing JSON string" << std::endl;
            return reinterpret_cast<void*>(0x12345);  // Mock handle
        }
        
        const char* getValue(void* handle, const char* key) {
            std::cout << "ThirdParty: Getting value for key: " << key << std::endl;
            return "mock_value";
        }
        
        void cleanup(void* handle) {
            std::cout << "ThirdParty: Cleaning up JSON handle" << std::endl;
        }
    };
}

// Modern JSON interface your application expects
class JSONDocument {
public:
    virtual ~JSONDocument() = default;
    virtual bool parse(const std::string& jsonString) = 0;
    virtual std::string getString(const std::string& key) = 0;
    virtual int getInt(const std::string& key) = 0;
    virtual bool getBool(const std::string& key) = 0;
};

class ThirdPartyJSONAdapter : public JSONDocument {
private:
    ThirdPartyJSON::JSONParser parser_;
    void* handle_ = nullptr;
    
public:
    ~ThirdPartyJSONAdapter() {
        if (handle_) {
            parser_.cleanup(handle_);
        }
    }
    
    bool parse(const std::string& jsonString) override {
        if (handle_) {
            parser_.cleanup(handle_);
        }
        
        handle_ = parser_.parseString(jsonString.c_str());
        return handle_ != nullptr;
    }
    
    std::string getString(const std::string& key) override {
        if (!handle_) {
            throw std::runtime_error("JSON not parsed");
        }
        
        const char* value = parser_.getValue(handle_, key.c_str());
        return std::string(value ? value : "");
    }
    
    int getInt(const std::string& key) override {
        std::string strValue = getString(key);
        return std::stoi(strValue);
    }
    
    bool getBool(const std::string& key) override {
        std::string strValue = getString(key);
        return strValue == "true" || strValue == "1";
    }
};
```

## Advanced Adapter Patterns

### 1. **Two-Way Adapter**
```cpp
class ModernInterface {
public:
    virtual void modernMethod() = 0;
};

class LegacyInterface {
public:
    virtual void legacyMethod() = 0;
};

class TwoWayAdapter : public ModernInterface, public LegacyInterface {
private:
    std::unique_ptr<ModernInterface> modernImpl_;
    std::unique_ptr<LegacyInterface> legacyImpl_;
    
public:
    TwoWayAdapter(std::unique_ptr<ModernInterface> modern,
                  std::unique_ptr<LegacyInterface> legacy)
        : modernImpl_(std::move(modern)), legacyImpl_(std::move(legacy)) {}
    
    void modernMethod() override {
        if (modernImpl_) {
            modernImpl_->modernMethod();
        } else {
            // Adapt legacy to modern
            legacyImpl_->legacyMethod();
        }
    }
    
    void legacyMethod() override {
        if (legacyImpl_) {
            legacyImpl_->legacyMethod();
        } else {
            // Adapt modern to legacy
            modernImpl_->modernMethod();
        }
    }
};
```

### 2. **Pluggable Adapter**
```cpp
template<typename Target, typename Adaptee>
class PluggableAdapter : public Target {
private:
    std::unique_ptr<Adaptee> adaptee_;
    std::function<void(Target&, Adaptee&)> adaptFunction_;
    
public:
    PluggableAdapter(std::unique_ptr<Adaptee> adaptee,
                    std::function<void(Target&, Adaptee&)> adaptFunc)
        : adaptee_(std::move(adaptee)), adaptFunction_(adaptFunc) {}
    
    void performOperation() override {
        adaptFunction_(*this, *adaptee_);
    }
};
```

### 3. **Caching Adapter**
```cpp
class CachingAdapter : public Shape {
private:
    std::unique_ptr<Shape> adaptee_;
    mutable std::optional<double> cachedArea_;
    mutable bool areaDirty_ = true;
    
public:
    explicit CachingAdapter(std::unique_ptr<Shape> shape)
        : adaptee_(std::move(shape)) {}
    
    void draw() const override {
        adaptee_->draw();
    }
    
    std::string getType() const override {
        return adaptee_->getType() + " (Cached)";
    }
    
    double getArea() const override {
        if (areaDirty_ || !cachedArea_) {
            cachedArea_ = adaptee_->getArea();
            areaDirty_ = false;
        }
        return *cachedArea_;
    }
    
    void invalidateCache() {
        areaDirty_ = true;
        cachedArea_.reset();
    }
};
```

## Performance Considerations

### Benchmarking Adapter Overhead
```cpp
#include <chrono>

void benchmarkAdapterPerformance() {
    const int iterations = 1000000;
    
    // Direct call timing
    auto legacyCircle = std::make_unique<LegacyCircle>(5.0);
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        legacyCircle->computeArea();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto directTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Adapter call timing
    auto circleAdapter = std::make_unique<CircleAdapter>(5.0);
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        circleAdapter->getArea();
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto adapterTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Direct calls: " << directTime.count() << " μs" << std::endl;
    std::cout << "Adapter calls: " << adapterTime.count() << " μs" << std::endl;
    std::cout << "Overhead: " << (adapterTime.count() - directTime.count()) << " μs" << std::endl;
}
```

## Common Pitfalls and Solutions

### 1. **Memory Management Issues**
```cpp
// ❌ Problematic - raw pointer ownership unclear
class BadAdapter : public Shape {
    LegacyCircle* legacy_;  // Who owns this?
public:
    BadAdapter(LegacyCircle* legacy) : legacy_(legacy) {}
    // Destructor doesn't clean up!
};

// ✅ Better - clear ownership with smart pointers
class GoodAdapter : public Shape {
    std::unique_ptr<LegacyCircle> legacy_;
public:
    explicit GoodAdapter(std::unique_ptr<LegacyCircle> legacy) 
        : legacy_(std::move(legacy)) {}
    // Automatic cleanup via unique_ptr
};
```

### 2. **Interface Mismatch Handling**
```cpp
class RobustAdapter : public Shape {
private:
    std::unique_ptr<LegacyCircle> legacy_;
    
public:
    explicit RobustAdapter(std::unique_ptr<LegacyCircle> legacy)
        : legacy_(std::move(legacy)) {}
    
    double getArea() const override {
        try {
            return legacy_->computeArea();
        } catch (const std::exception& e) {
            std::cerr << "Error computing area: " << e.what() << std::endl;
            return 0.0;  // Default fallback
        }
    }
    
    void draw() const override {
        if (legacy_) {
            legacy_->oldDraw();
        } else {
            std::cout << "Warning: No legacy object to draw" << std::endl;
        }
    }
};
```

### 3. **Multiple Inheritance Diamond Problem**
```cpp
// ❌ Potential diamond problem
class ProblemAdapter : public Shape, public LegacyCircle {
    // If Shape and LegacyCircle share a common base...
};

// ✅ Better - use composition instead
class SafeAdapter : public Shape {
private:
    std::unique_ptr<LegacyCircle> legacy_;
public:
    // Composition avoids inheritance issues
};
```

## Testing Adapter Pattern

```cpp
#include <gtest/gtest.h>

class AdapterTest : public ::testing::Test {
protected:
    void SetUp() override {
        legacyCircle = std::make_unique<LegacyCircle>(5.0);
        adapter = std::make_unique<CircleAdapter>(5.0);
    }
    
    std::unique_ptr<LegacyCircle> legacyCircle;
    std::unique_ptr<CircleAdapter> adapter;
};

TEST_F(AdapterTest, AdapterPreservesAreaCalculation) {
    double legacyArea = legacyCircle->computeArea();
    double adapterArea = adapter->getArea();
    
    EXPECT_DOUBLE_EQ(legacyArea, adapterArea);
}

TEST_F(AdapterTest, AdapterImplementsTargetInterface) {
    Shape* shape = adapter.get();
    
    EXPECT_NO_THROW(shape->draw());
    EXPECT_NO_THROW(shape->getArea());
    EXPECT_NO_THROW(shape->getType());
}

TEST_F(AdapterTest, AdapterHandlesNullAdaptee) {
    auto nullAdapter = std::make_unique<RobustAdapter>(nullptr);
    
    EXPECT_NO_THROW(nullAdapter->draw());
    EXPECT_EQ(0.0, nullAdapter->getArea());
}
```

## Best Practices

### 1. **Use Composition Over Inheritance**
- Prefer object adapter over class adapter
- Avoid multiple inheritance complexity
- Better flexibility and maintainability

### 2. **Smart Pointer Management**
- Use `std::unique_ptr` for exclusive ownership
- Use `std::shared_ptr` for shared ownership
- Avoid raw pointers for memory management

### 3. **Error Handling**
- Handle interface mismatches gracefully
- Provide meaningful error messages
- Implement fallback behaviors

### 4. **Performance Optimization**
- Cache expensive operations when possible
- Minimize object creation overhead
- Consider lazy initialization

### 5. **Interface Design**
- Keep adapter interfaces minimal
- Follow single responsibility principle
- Document adaptation behavior clearly

## Comparison with Other Patterns

| Pattern | Purpose | Key Difference |
|---------|---------|----------------|
| **Adapter** | Interface compatibility | Converts existing interface |
| **Decorator** | Add functionality | Enhances without changing interface |
| **Facade** | Simplify complex system | Provides unified simple interface |
| **Proxy** | Control access | Same interface, different behavior |
| **Bridge** | Separate abstraction/implementation | Design-time separation |

## Conclusion

The Adapter pattern is essential for:
- **Legacy system integration** without code modification
- **Third-party library integration** with different interfaces
- **Interface standardization** across heterogeneous systems
- **Code reuse** in new contexts

Key considerations:
- **Choose composition over inheritance** for flexibility
- **Use smart pointers** for proper memory management
- **Handle errors gracefully** during interface translation
- **Consider performance implications** of additional indirection

The pattern is particularly valuable in enterprise systems where different components, libraries, and legacy systems must work together seamlessly.
