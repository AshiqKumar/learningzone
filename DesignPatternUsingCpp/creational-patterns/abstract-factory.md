# Abstract Factory Design Pattern in C++

## Overview

The **Abstract Factory Pattern** is a creational design pattern that provides an interface for creating families of related or dependent objects without specifying their concrete classes. It encapsulates a group of individual factories that have a common theme, allowing the creation of objects that belong to different product families while ensuring they are compatible with each other.

## Key Concepts

- **Abstract Factory**: Declares an interface for operations that create abstract products
- **Concrete Factory**: Implements operations to create concrete product objects
- **Abstract Product**: Declares an interface for a type of product object
- **Concrete Product**: Defines a product object created by the corresponding concrete factory
- **Client**: Uses only interfaces declared by Abstract Factory and Abstract Product classes

## Problem Solved

Without the Abstract Factory pattern:
- **Hard-coded object creation** scattered throughout the codebase
- **Tight coupling** between client code and specific product classes
- **Difficult platform/environment switching** requiring code modifications
- **Violation of Open/Closed Principle** when adding new product families
- **Multiple conditional statements** for object creation logic

## Solution Structure

```
                     ┌─────────────────┐
                     │     Client      │
                     └─────────────────┘
                              │
                              ▼
                     ┌─────────────────┐
                     │ AbstractFactory │
                     │ + createDeviceA()│
                     │ + createDeviceB()│
                     └─────────────────┘
                              △
                    ┌─────────┴─────────┐
           ┌────────▼────────┐ ┌────────▼────────┐
           │ ConcreteFactory1│ │ ConcreteFactory2│
           │ + createDeviceA()│ │ + createDeviceA()│
           │ + createDeviceB()│ │ + createDeviceB()│
           └─────────────────┘ └─────────────────┘
                    │                    │
                    ▼                    ▼
            ┌─────────────┐      ┌─────────────┐
            │  ProductA1  │      │  ProductA2  │
            └─────────────┘      └─────────────┘
            ┌─────────────┐      ┌─────────────┐
            │  ProductB1  │      │  ProductB2  │
            └─────────────┘      └─────────────┘
```

## Code Analysis

### Abstract Product Interface
```cpp
class Device {
public:
    virtual void send(string data) = 0;
};
```
**Purpose**: Defines the interface that all concrete devices must implement.

### Concrete Products
```cpp
class Wifi : public Device {
public:
    void send(string data) {
        cout << "Sent By Wifi: " << data << endl;
    }
};

class Bluetooth : public Device {
public:
    void send(string data) {
        cout << "Sent By Bluetooth: " << data << endl;
    }
};
```
**Purpose**: Concrete implementations of the Device interface for different communication methods.

### Abstract Factory
```cpp
class AbstractFactory {
public:
    virtual Device* get() = 0;
};
```
**Purpose**: Declares the interface for creating device objects.

### Concrete Factory
```cpp
class DeviceAbstractFactory : public AbstractFactory {
public:
    Device* get() {
        if (true) { // Conditions
            return new Wifi;
        } else {
            return new Bluetooth;
        }
    }
};
```
**Purpose**: Implements the creation logic for specific device types based on conditions.

## Advantages

### ✅ **Family Consistency**
- Ensures products from the same family work together
- Maintains compatibility across related objects
- Prevents mixing incompatible products

### ✅ **Isolation of Concrete Classes**
- Client code depends only on abstractions
- Concrete classes are isolated from client code
- Easy to swap entire product families

### ✅ **Easy Product Family Exchange**
- Change factory implementation to switch families
- No client code modification required
- Runtime family switching possible

### ✅ **Open/Closed Principle**
- Open for extension (new families)
- Closed for modification (existing code)
- Add new product families without breaking existing code

## Disadvantages

### ❌ **Code Complexity**
- Multiple classes and interfaces to maintain
- Can be overkill for simple scenarios
- Increases initial development time

### ❌ **Difficult to Support New Products**
- Adding new products requires changes to all factories
- Interface modifications propagate through hierarchy
- Can violate Open/Closed Principle for new product types

### ❌ **Runtime Overhead**
- Additional indirection through factory methods
- Object creation overhead
- Memory overhead for factory objects

## Improved Modern C++ Implementation

Here's an enhanced version addressing the original code's limitations:

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>

// Forward declarations
class Device;
class Sensor;
class Display;

// Abstract Product Interfaces
class Device {
public:
    virtual ~Device() = default;
    virtual void send(const std::string& data) = 0;
    virtual std::string getType() const = 0;
    virtual bool isConnected() const = 0;
    virtual void connect() = 0;
    virtual void disconnect() = 0;
};

class Sensor {
public:
    virtual ~Sensor() = default;
    virtual double readValue() = 0;
    virtual std::string getUnit() const = 0;
    virtual void calibrate() = 0;
    virtual bool isReady() const = 0;
};

class Display {
public:
    virtual ~Display() = default;
    virtual void show(const std::string& text) = 0;
    virtual void clear() = 0;
    virtual void setBrightness(int level) = 0;
    virtual std::string getResolution() const = 0;
};

// WiFi Product Family
class WiFiDevice : public Device {
private:
    bool connected_ = false;
    std::string ssid_;
    
public:
    explicit WiFiDevice(const std::string& ssid = "DefaultSSID") : ssid_(ssid) {}
    
    void send(const std::string& data) override {
        if (!connected_) {
            throw std::runtime_error("WiFi device not connected");
        }
        std::cout << "[WiFi:" << ssid_ << "] Sending: " << data << std::endl;
    }
    
    std::string getType() const override { return "WiFi"; }
    
    bool isConnected() const override { return connected_; }
    
    void connect() override {
        std::cout << "[WiFi] Connecting to " << ssid_ << "..." << std::endl;
        connected_ = true;
    }
    
    void disconnect() override {
        std::cout << "[WiFi] Disconnecting from " << ssid_ << std::endl;
        connected_ = false;
    }
    
    void setSSID(const std::string& ssid) { ssid_ = ssid; }
};

class WiFiSensor : public Sensor {
private:
    double lastValue_ = 0.0;
    bool calibrated_ = false;
    
public:
    double readValue() override {
        if (!calibrated_) {
            throw std::runtime_error("WiFi sensor not calibrated");
        }
        // Simulate reading from WiFi-connected sensor
        lastValue_ = 20.0 + (rand() % 100) / 10.0; // 20.0 to 30.0
        std::cout << "[WiFi Sensor] Read value: " << lastValue_ << " °C" << std::endl;
        return lastValue_;
    }
    
    std::string getUnit() const override { return "°C"; }
    
    void calibrate() override {
        std::cout << "[WiFi Sensor] Calibrating..." << std::endl;
        calibrated_ = true;
    }
    
    bool isReady() const override { return calibrated_; }
};

class WiFiDisplay : public Display {
private:
    int brightness_ = 80;
    std::string currentText_;
    
public:
    void show(const std::string& text) override {
        currentText_ = text;
        std::cout << "[WiFi Display] Showing: \"" << text << "\" (Brightness: " 
                  << brightness_ << "%)" << std::endl;
    }
    
    void clear() override {
        currentText_.clear();
        std::cout << "[WiFi Display] Screen cleared" << std::endl;
    }
    
    void setBrightness(int level) override {
        brightness_ = std::clamp(level, 0, 100);
        std::cout << "[WiFi Display] Brightness set to " << brightness_ << "%" << std::endl;
    }
    
    std::string getResolution() const override { return "1920x1080"; }
};

// Bluetooth Product Family
class BluetoothDevice : public Device {
private:
    bool connected_ = false;
    std::string deviceName_;
    
public:
    explicit BluetoothDevice(const std::string& name = "DefaultBT") : deviceName_(name) {}
    
    void send(const std::string& data) override {
        if (!connected_) {
            throw std::runtime_error("Bluetooth device not connected");
        }
        std::cout << "[Bluetooth:" << deviceName_ << "] Sending: " << data << std::endl;
    }
    
    std::string getType() const override { return "Bluetooth"; }
    
    bool isConnected() const override { return connected_; }
    
    void connect() override {
        std::cout << "[Bluetooth] Pairing with " << deviceName_ << "..." << std::endl;
        connected_ = true;
    }
    
    void disconnect() override {
        std::cout << "[Bluetooth] Disconnecting from " << deviceName_ << std::endl;
        connected_ = false;
    }
    
    void setDeviceName(const std::string& name) { deviceName_ = name; }
};

class BluetoothSensor : public Sensor {
private:
    double lastValue_ = 0.0;
    bool calibrated_ = false;
    
public:
    double readValue() override {
        if (!calibrated_) {
            throw std::runtime_error("Bluetooth sensor not calibrated");
        }
        // Simulate reading from Bluetooth sensor
        lastValue_ = 15.0 + (rand() % 80) / 10.0; // 15.0 to 23.0
        std::cout << "[Bluetooth Sensor] Read value: " << lastValue_ << " °C" << std::endl;
        return lastValue_;
    }
    
    std::string getUnit() const override { return "°C"; }
    
    void calibrate() override {
        std::cout << "[Bluetooth Sensor] Calibrating..." << std::endl;
        calibrated_ = true;
    }
    
    bool isReady() const override { return calibrated_; }
};

class BluetoothDisplay : public Display {
private:
    int brightness_ = 60;
    std::string currentText_;
    
public:
    void show(const std::string& text) override {
        currentText_ = text;
        std::cout << "[Bluetooth Display] Showing: \"" << text << "\" (Brightness: " 
                  << brightness_ << "%)" << std::endl;
    }
    
    void clear() override {
        currentText_.clear();
        std::cout << "[Bluetooth Display] Screen cleared" << std::endl;
    }
    
    void setBrightness(int level) override {
        brightness_ = std::clamp(level, 0, 100);
        std::cout << "[Bluetooth Display] Brightness set to " << brightness_ << "%" << std::endl;
    }
    
    std::string getResolution() const override { return "800x600"; }
};

// Abstract Factory Interface
class IoTDeviceFactory {
public:
    virtual ~IoTDeviceFactory() = default;
    virtual std::unique_ptr<Device> createDevice() = 0;
    virtual std::unique_ptr<Sensor> createSensor() = 0;
    virtual std::unique_ptr<Display> createDisplay() = 0;
    virtual std::string getFactoryType() const = 0;
};

// Concrete Factories
class WiFiDeviceFactory : public IoTDeviceFactory {
private:
    std::string ssid_;
    
public:
    explicit WiFiDeviceFactory(const std::string& ssid = "DefaultWiFi") : ssid_(ssid) {}
    
    std::unique_ptr<Device> createDevice() override {
        auto device = std::make_unique<WiFiDevice>(ssid_);
        std::cout << "[WiFi Factory] Created WiFi device" << std::endl;
        return device;
    }
    
    std::unique_ptr<Sensor> createSensor() override {
        auto sensor = std::make_unique<WiFiSensor>();
        std::cout << "[WiFi Factory] Created WiFi sensor" << std::endl;
        return sensor;
    }
    
    std::unique_ptr<Display> createDisplay() override {
        auto display = std::make_unique<WiFiDisplay>();
        std::cout << "[WiFi Factory] Created WiFi display" << std::endl;
        return display;
    }
    
    std::string getFactoryType() const override { return "WiFi Factory"; }
};

class BluetoothDeviceFactory : public IoTDeviceFactory {
private:
    std::string deviceName_;
    
public:
    explicit BluetoothDeviceFactory(const std::string& name = "DefaultBluetooth") 
        : deviceName_(name) {}
    
    std::unique_ptr<Device> createDevice() override {
        auto device = std::make_unique<BluetoothDevice>(deviceName_);
        std::cout << "[Bluetooth Factory] Created Bluetooth device" << std::endl;
        return device;
    }
    
    std::unique_ptr<Sensor> createSensor() override {
        auto sensor = std::make_unique<BluetoothSensor>();
        std::cout << "[Bluetooth Factory] Created Bluetooth sensor" << std::endl;
        return sensor;
    }
    
    std::unique_ptr<Display> createDisplay() override {
        auto display = std::make_unique<BluetoothDisplay>();
        std::cout << "[Bluetooth Factory] Created Bluetooth display" << std::endl;
        return display;
    }
    
    std::string getFactoryType() const override { return "Bluetooth Factory"; }
};

// Factory Registry for dynamic factory selection
class FactoryRegistry {
private:
    std::map<std::string, std::function<std::unique_ptr<IoTDeviceFactory>()>> factories_;
    
public:
    void registerFactory(const std::string& name, 
                        std::function<std::unique_ptr<IoTDeviceFactory>()> creator) {
        factories_[name] = creator;
    }
    
    std::unique_ptr<IoTDeviceFactory> createFactory(const std::string& name) {
        auto it = factories_.find(name);
        if (it != factories_.end()) {
            return it->second();
        }
        throw std::runtime_error("Unknown factory type: " + name);
    }
    
    std::vector<std::string> getAvailableFactories() const {
        std::vector<std::string> names;
        for (const auto& pair : factories_) {
            names.push_back(pair.first);
        }
        return names;
    }
};

// IoT System - Client class using the factory
class IoTSystem {
private:
    std::unique_ptr<IoTDeviceFactory> factory_;
    std::unique_ptr<Device> device_;
    std::unique_ptr<Sensor> sensor_;
    std::unique_ptr<Display> display_;
    
public:
    explicit IoTSystem(std::unique_ptr<IoTDeviceFactory> factory) 
        : factory_(std::move(factory)) {
        initializeComponents();
    }
    
    void initializeComponents() {
        std::cout << "\n=== Initializing IoT System with " 
                  << factory_->getFactoryType() << " ===" << std::endl;
        
        device_ = factory_->createDevice();
        sensor_ = factory_->createSensor();
        display_ = factory_->createDisplay();
        
        // Initialize all components
        device_->connect();
        sensor_->calibrate();
        display_->setBrightness(75);
    }
    
    void runSystemCycle() {
        try {
            if (!device_->isConnected()) {
                device_->connect();
            }
            
            if (!sensor_->isReady()) {
                sensor_->calibrate();
            }
            
            // Read sensor data
            double value = sensor_->readValue();
            
            // Display the data
            std::string message = "Temperature: " + std::to_string(value) + " " + sensor_->getUnit();
            display_->show(message);
            
            // Send data through device
            std::string data = "sensor_data:" + std::to_string(value);
            device_->send(data);
            
        } catch (const std::exception& e) {
            std::cerr << "System error: " << e.what() << std::endl;
            display_->show("Error: " + std::string(e.what()));
        }
    }
    
    void shutdown() {
        std::cout << "\n=== Shutting down IoT System ===" << std::endl;
        display_->clear();
        device_->disconnect();
    }
    
    void switchToFactory(std::unique_ptr<IoTDeviceFactory> newFactory) {
        shutdown();
        factory_ = std::move(newFactory);
        initializeComponents();
    }
    
    std::string getCurrentFactoryType() const {
        return factory_->getFactoryType();
    }
};

// Configuration-based factory selector
class ConfigurationManager {
private:
    std::map<std::string, std::string> config_;
    
public:
    void loadConfiguration() {
        // Simulate loading configuration from file/environment
        config_["communication_type"] = "wifi";  // or "bluetooth"
        config_["wifi_ssid"] = "IoT_Network";
        config_["bluetooth_device"] = "IoT_Device_BT";
        config_["environment"] = "production";   // or "development", "testing"
    }
    
    std::unique_ptr<IoTDeviceFactory> createFactoryFromConfig() {
        std::string commType = config_["communication_type"];
        
        if (commType == "wifi") {
            return std::make_unique<WiFiDeviceFactory>(config_["wifi_ssid"]);
        } else if (commType == "bluetooth") {
            return std::make_unique<BluetoothDeviceFactory>(config_["bluetooth_device"]);
        } else {
            throw std::runtime_error("Unknown communication type: " + commType);
        }
    }
    
    std::string getConfigValue(const std::string& key) const {
        auto it = config_.find(key);
        return (it != config_.end()) ? it->second : "";
    }
    
    void setConfigValue(const std::string& key, const std::string& value) {
        config_[key] = value;
    }
};
```

## Usage Examples

### Basic Usage
```cpp
int main() {
    try {
        // Method 1: Direct factory creation
        std::cout << "=== Method 1: Direct Factory Creation ===" << std::endl;
        auto wifiFactory = std::make_unique<WiFiDeviceFactory>("Home_WiFi");
        IoTSystem wifiSystem(std::move(wifiFactory));
        
        wifiSystem.runSystemCycle();
        
        // Method 2: Configuration-based creation
        std::cout << "\n=== Method 2: Configuration-based Creation ===" << std::endl;
        ConfigurationManager config;
        config.loadConfiguration();
        
        auto configFactory = config.createFactoryFromConfig();
        IoTSystem configSystem(std::move(configFactory));
        
        configSystem.runSystemCycle();
        
        // Method 3: Registry-based creation
        std::cout << "\n=== Method 3: Registry-based Creation ===" << std::endl;
        FactoryRegistry registry;
        
        registry.registerFactory("wifi", []() {
            return std::make_unique<WiFiDeviceFactory>("Registry_WiFi");
        });
        
        registry.registerFactory("bluetooth", []() {
            return std::make_unique<BluetoothDeviceFactory>("Registry_BT");
        });
        
        auto registryFactory = registry.createFactory("bluetooth");
        IoTSystem registrySystem(std::move(registryFactory));
        
        registrySystem.runSystemCycle();
        
        // Method 4: Runtime factory switching
        std::cout << "\n=== Method 4: Runtime Factory Switching ===" << std::endl;
        auto switchableFactory = std::make_unique<WiFiDeviceFactory>("Switchable_WiFi");
        IoTSystem switchableSystem(std::move(switchableFactory));
        
        switchableSystem.runSystemCycle();
        
        // Switch to Bluetooth
        auto bluetoothFactory = std::make_unique<BluetoothDeviceFactory>("Switchable_BT");
        switchableSystem.switchToFactory(std::move(bluetoothFactory));
        
        switchableSystem.runSystemCycle();
        
    } catch (const std::exception& e) {
        std::cerr << "Application error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
```

### Advanced Usage with Environment Detection
```cpp
class EnvironmentDetector {
public:
    enum class Environment { DEVELOPMENT, TESTING, PRODUCTION, EMBEDDED };
    
    static Environment detectEnvironment() {
        // In real implementation, this could check:
        // - Environment variables
        // - Hardware capabilities
        // - Network availability
        // - Configuration files
        
        // Simulate detection logic
        if (std::getenv("IOT_ENV")) {
            std::string env = std::getenv("IOT_ENV");
            if (env == "dev") return Environment::DEVELOPMENT;
            if (env == "test") return Environment::TESTING;
            if (env == "prod") return Environment::PRODUCTION;
            if (env == "embedded") return Environment::EMBEDDED;
        }
        
        return Environment::DEVELOPMENT; // Default
    }
    
    static std::unique_ptr<IoTDeviceFactory> createFactoryForEnvironment(Environment env) {
        switch (env) {
            case Environment::DEVELOPMENT:
                return std::make_unique<WiFiDeviceFactory>("Dev_WiFi");
            case Environment::TESTING:
                return std::make_unique<WiFiDeviceFactory>("Test_WiFi");
            case Environment::PRODUCTION:
                return std::make_unique<BluetoothDeviceFactory>("Prod_BT");
            case Environment::EMBEDDED:
                return std::make_unique<BluetoothDeviceFactory>("Embedded_BT");
            default:
                throw std::runtime_error("Unknown environment");
        }
    }
};

void demonstrateEnvironmentBasedCreation() {
    auto env = EnvironmentDetector::detectEnvironment();
    auto factory = EnvironmentDetector::createFactoryForEnvironment(env);
    
    IoTSystem system(std::move(factory));
    system.runSystemCycle();
}
```

## Real-World Applications

### 1. **Cross-Platform GUI Applications**
```cpp
// Abstract GUI Factory for different operating systems
class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Window> createWindow() = 0;
    virtual std::unique_ptr<Menu> createMenu() = 0;
};

class WindowsGUIFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
    
    std::unique_ptr<Window> createWindow() override {
        return std::make_unique<WindowsWindow>();
    }
    
    std::unique_ptr<Menu> createMenu() override {
        return std::make_unique<WindowsMenu>();
    }
};

class MacOSGUIFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }
    
    std::unique_ptr<Window> createWindow() override {
        return std::make_unique<MacWindow>();
    }
    
    std::unique_ptr<Menu> createMenu() override {
        return std::make_unique<MacMenu>();
    }
};

class LinuxGUIFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<LinuxButton>();
    }
    
    std::unique_ptr<Window> createWindow() override {
        return std::make_unique<LinuxWindow>();
    }
    
    std::unique_ptr<Menu> createMenu() override {
        return std::make_unique<LinuxMenu>();
    }
};

// Factory selection based on platform
std::unique_ptr<GUIFactory> createPlatformGUIFactory() {
#ifdef _WIN32
    return std::make_unique<WindowsGUIFactory>();
#elif __APPLE__
    return std::make_unique<MacOSGUIFactory>();
#elif __linux__
    return std::make_unique<LinuxGUIFactory>();
#else
    throw std::runtime_error("Unsupported platform");
#endif
}
```

### 2. **Database Access Layer**
```cpp
// Abstract Database Factory
class DatabaseFactory {
public:
    virtual ~DatabaseFactory() = default;
    virtual std::unique_ptr<Connection> createConnection() = 0;
    virtual std::unique_ptr<Command> createCommand() = 0;
    virtual std::unique_ptr<Transaction> createTransaction() = 0;
    virtual std::unique_ptr<DataReader> createDataReader() = 0;
};

class SQLServerFactory : public DatabaseFactory {
private:
    std::string connectionString_;
    
public:
    explicit SQLServerFactory(const std::string& connStr) : connectionString_(connStr) {}
    
    std::unique_ptr<Connection> createConnection() override {
        return std::make_unique<SQLServerConnection>(connectionString_);
    }
    
    std::unique_ptr<Command> createCommand() override {
        return std::make_unique<SQLServerCommand>();
    }
    
    std::unique_ptr<Transaction> createTransaction() override {
        return std::make_unique<SQLServerTransaction>();
    }
    
    std::unique_ptr<DataReader> createDataReader() override {
        return std::make_unique<SQLServerDataReader>();
    }
};

class MySQLFactory : public DatabaseFactory {
private:
    std::string connectionString_;
    
public:
    explicit MySQLFactory(const std::string& connStr) : connectionString_(connStr) {}
    
    std::unique_ptr<Connection> createConnection() override {
        return std::make_unique<MySQLConnection>(connectionString_);
    }
    
    std::unique_ptr<Command> createCommand() override {
        return std::make_unique<MySQLCommand>();
    }
    
    std::unique_ptr<Transaction> createTransaction() override {
        return std::make_unique<MySQLTransaction>();
    }
    
    std::unique_ptr<DataReader> createDataReader() override {
        return std::make_unique<MySQLDataReader>();
    }
};

class PostgreSQLFactory : public DatabaseFactory {
private:
    std::string connectionString_;
    
public:
    explicit PostgreSQLFactory(const std::string& connStr) : connectionString_(connStr) {}
    
    std::unique_ptr<Connection> createConnection() override {
        return std::make_unique<PostgreSQLConnection>(connectionString_);
    }
    
    std::unique_ptr<Command> createCommand() override {
        return std::make_unique<PostgreSQLCommand>();
    }
    
    std::unique_ptr<Transaction> createTransaction() override {
        return std::make_unique<PostgreSQLTransaction>();
    }
    
    std::unique_ptr<DataReader> createDataReader() override {
        return std::make_unique<PostgreSQLDataReader>();
    }
};

// Database abstraction layer
class DatabaseManager {
private:
    std::unique_ptr<DatabaseFactory> factory_;
    std::unique_ptr<Connection> connection_;
    
public:
    explicit DatabaseManager(std::unique_ptr<DatabaseFactory> factory) 
        : factory_(std::move(factory)) {
        connection_ = factory_->createConnection();
    }
    
    void executeQuery(const std::string& sql) {
        auto command = factory_->createCommand();
        command->setCommandText(sql);
        command->setConnection(connection_.get());
        
        auto reader = command->executeReader();
        while (reader->read()) {
            // Process data
        }
    }
    
    void executeTransaction(const std::vector<std::string>& commands) {
        auto transaction = factory_->createTransaction();
        transaction->begin();
        
        try {
            for (const auto& sql : commands) {
                auto command = factory_->createCommand();
                command->setCommandText(sql);
                command->setTransaction(transaction.get());
                command->executeNonQuery();
            }
            transaction->commit();
        } catch (...) {
            transaction->rollback();
            throw;
        }
    }
};
```

### 3. **Game Engine Renderer**
```cpp
// Graphics API abstraction
class GraphicsFactory {
public:
    virtual ~GraphicsFactory() = default;
    virtual std::unique_ptr<Renderer> createRenderer() = 0;
    virtual std::unique_ptr<Texture> createTexture() = 0;
    virtual std::unique_ptr<Shader> createShader() = 0;
    virtual std::unique_ptr<Buffer> createBuffer() = 0;
};

class DirectX11Factory : public GraphicsFactory {
public:
    std::unique_ptr<Renderer> createRenderer() override {
        return std::make_unique<DirectX11Renderer>();
    }
    
    std::unique_ptr<Texture> createTexture() override {
        return std::make_unique<DirectX11Texture>();
    }
    
    std::unique_ptr<Shader> createShader() override {
        return std::make_unique<DirectX11Shader>();
    }
    
    std::unique_ptr<Buffer> createBuffer() override {
        return std::make_unique<DirectX11Buffer>();
    }
};

class OpenGLFactory : public GraphicsFactory {
public:
    std::unique_ptr<Renderer> createRenderer() override {
        return std::make_unique<OpenGLRenderer>();
    }
    
    std::unique_ptr<Texture> createTexture() override {
        return std::make_unique<OpenGLTexture>();
    }
    
    std::unique_ptr<Shader> createShader() override {
        return std::make_unique<OpenGLShader>();
    }
    
    std::unique_ptr<Buffer> createBuffer() override {
        return std::make_unique<OpenGLBuffer>();
    }
};

class VulkanFactory : public GraphicsFactory {
public:
    std::unique_ptr<Renderer> createRenderer() override {
        return std::make_unique<VulkanRenderer>();
    }
    
    std::unique_ptr<Texture> createTexture() override {
        return std::make_unique<VulkanTexture>();
    }
    
    std::unique_ptr<Shader> createShader() override {
        return std::make_unique<VulkanShader>();
    }
    
    std::unique_ptr<Buffer> createBuffer() override {
        return std::make_unique<VulkanBuffer>();
    }
};

// Game engine using graphics factory
class GameEngine {
private:
    std::unique_ptr<GraphicsFactory> graphicsFactory_;
    std::unique_ptr<Renderer> renderer_;
    
public:
    explicit GameEngine(std::unique_ptr<GraphicsFactory> factory) 
        : graphicsFactory_(std::move(factory)) {
        renderer_ = graphicsFactory_->createRenderer();
    }
    
    void initializeGraphics() {
        renderer_->initialize();
    }
    
    void renderFrame() {
        renderer_->beginFrame();
        
        // Create graphics resources as needed
        auto texture = graphicsFactory_->createTexture();
        auto shader = graphicsFactory_->createShader();
        auto buffer = graphicsFactory_->createBuffer();
        
        // Render objects
        renderer_->draw();
        
        renderer_->endFrame();
    }
};

// Factory selection based on platform and capabilities
std::unique_ptr<GraphicsFactory> createGraphicsFactory() {
    // Check platform capabilities
    if (isDirectX11Available()) {
        return std::make_unique<DirectX11Factory>();
    } else if (isVulkanAvailable()) {
        return std::make_unique<VulkanFactory>();
    } else {
        return std::make_unique<OpenGLFactory>(); // Fallback
    }
}
```

## Advanced Abstract Factory Patterns

### 1. **Parameterized Factory**
```cpp
template<typename ProductFamily>
class ParameterizedFactory {
public:
    virtual ~ParameterizedFactory() = default;
    
    template<typename ProductType, typename... Args>
    std::unique_ptr<ProductType> create(Args&&... args) {
        return std::make_unique<typename ProductFamily::template Product<ProductType>>(
            std::forward<Args>(args)...);
    }
};

// Product family definition
struct WiFiProductFamily {
    template<typename T> struct Product;
};

template<>
struct WiFiProductFamily::Product<Device> {
    using type = WiFiDevice;
};

template<>
struct WiFiProductFamily::Product<Sensor> {
    using type = WiFiSensor;
};

// Usage
auto factory = std::make_unique<ParameterizedFactory<WiFiProductFamily>>();
auto device = factory->create<Device>("MySSID");
```

### 2. **Factory with Dependency Injection**
```cpp
class DIContainer {
private:
    std::map<std::string, std::function<std::any()>> services_;
    
public:
    template<typename T>
    void registerService(const std::string& name, std::function<std::unique_ptr<T>()> creator) {
        services_[name] = [creator]() -> std::any {
            return creator();
        };
    }
    
    template<typename T>
    std::unique_ptr<T> getService(const std::string& name) {
        auto it = services_.find(name);
        if (it != services_.end()) {
            return std::any_cast<std::unique_ptr<T>>(it->second());
        }
        throw std::runtime_error("Service not found: " + name);
    }
};

class DIAwareFactory : public IoTDeviceFactory {
private:
    std::shared_ptr<DIContainer> container_;
    
public:
    explicit DIAwareFactory(std::shared_ptr<DIContainer> container) 
        : container_(container) {}
    
    std::unique_ptr<Device> createDevice() override {
        return container_->getService<Device>("device");
    }
    
    std::unique_ptr<Sensor> createSensor() override {
        return container_->getService<Sensor>("sensor");
    }
    
    std::unique_ptr<Display> createDisplay() override {
        return container_->getService<Display>("display");
    }
    
    std::string getFactoryType() const override { return "DI Factory"; }
};
```

### 3. **Asynchronous Factory**
```cpp
#include <future>
#include <thread>

class AsyncIoTDeviceFactory : public IoTDeviceFactory {
public:
    std::future<std::unique_ptr<Device>> createDeviceAsync() {
        return std::async(std::launch::async, [this]() {
            // Simulate time-consuming device initialization
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return createDevice();
        });
    }
    
    std::future<std::unique_ptr<Sensor>> createSensorAsync() {
        return std::async(std::launch::async, [this]() {
            // Simulate sensor calibration time
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return createSensor();
        });
    }
    
    std::future<std::unique_ptr<Display>> createDisplayAsync() {
        return std::async(std::launch::async, [this]() {
            // Simulate display initialization
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            return createDisplay();
        });
    }
    
    // Parallel creation of all components
    std::tuple<std::unique_ptr<Device>, std::unique_ptr<Sensor>, std::unique_ptr<Display>>
    createAllAsync() {
        auto deviceFuture = createDeviceAsync();
        auto sensorFuture = createSensorAsync();
        auto displayFuture = createDisplayAsync();
        
        return std::make_tuple(
            deviceFuture.get(),
            sensorFuture.get(),
            displayFuture.get()
        );
    }
};

class AsyncWiFiFactory : public AsyncIoTDeviceFactory {
public:
    std::unique_ptr<Device> createDevice() override {
        return std::make_unique<WiFiDevice>();
    }
    
    std::unique_ptr<Sensor> createSensor() override {
        return std::make_unique<WiFiSensor>();
    }
    
    std::unique_ptr<Display> createDisplay() override {
        return std::make_unique<WiFiDisplay>();
    }
    
    std::string getFactoryType() const override { return "Async WiFi Factory"; }
};
```

## Performance Considerations

### Memory Usage Optimization
```cpp
// Object pool for reusing expensive objects
template<typename T>
class ObjectPool {
private:
    std::queue<std::unique_ptr<T>> pool_;
    std::mutex mutex_;
    std::function<std::unique_ptr<T>()> factory_;
    
public:
    explicit ObjectPool(std::function<std::unique_ptr<T>()> factory, size_t initialSize = 10)
        : factory_(factory) {
        for (size_t i = 0; i < initialSize; ++i) {
            pool_.push(factory_());
        }
    }
    
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
        pool_.push(std::move(obj));
    }
};

class PooledDeviceFactory : public IoTDeviceFactory {
private:
    ObjectPool<Device> devicePool_;
    ObjectPool<Sensor> sensorPool_;
    ObjectPool<Display> displayPool_;
    
public:
    PooledDeviceFactory() 
        : devicePool_([]() { return std::make_unique<WiFiDevice>(); })
        , sensorPool_([]() { return std::make_unique<WiFiSensor>(); })
        , displayPool_([]() { return std::make_unique<WiFiDisplay>(); }) {}
    
    std::unique_ptr<Device> createDevice() override {
        return devicePool_.acquire();
    }
    
    std::unique_ptr<Sensor> createSensor() override {
        return sensorPool_.acquire();
    }
    
    std::unique_ptr<Display> createDisplay() override {
        return displayPool_.acquire();
    }
    
    std::string getFactoryType() const override { return "Pooled Factory"; }
};
```

### Performance Benchmarking
```cpp
#include <chrono>

void benchmarkFactoryPerformance() {
    const int iterations = 10000;
    
    // Direct object creation
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto device = std::make_unique<WiFiDevice>();
        auto sensor = std::make_unique<WiFiSensor>();
        auto display = std::make_unique<WiFiDisplay>();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto directTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Factory-based creation
    auto factory = std::make_unique<WiFiDeviceFactory>();
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto device = factory->createDevice();
        auto sensor = factory->createSensor();
        auto display = factory->createDisplay();
    }
    end = std::chrono::high_resolution_clock::now();
    auto factoryTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Pooled factory creation
    auto pooledFactory = std::make_unique<PooledDeviceFactory>();
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto device = pooledFactory->createDevice();
        auto sensor = pooledFactory->createSensor();
        auto display = pooledFactory->createDisplay();
    }
    end = std::chrono::high_resolution_clock::now();
    auto pooledTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Direct creation: " << directTime.count() << " μs" << std::endl;
    std::cout << "Factory creation: " << factoryTime.count() << " μs" << std::endl;
    std::cout << "Pooled factory: " << pooledTime.count() << " μs" << std::endl;
}
```

## Testing Abstract Factory Pattern

```cpp
#include <gtest/gtest.h>

class AbstractFactoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        wifiFactory = std::make_unique<WiFiDeviceFactory>("TestWiFi");
        bluetoothFactory = std::make_unique<BluetoothDeviceFactory>("TestBT");
    }
    
    std::unique_ptr<WiFiDeviceFactory> wifiFactory;
    std::unique_ptr<BluetoothDeviceFactory> bluetoothFactory;
};

TEST_F(AbstractFactoryTest, WiFiFactoryCreatesWiFiProducts) {
    auto device = wifiFactory->createDevice();
    auto sensor = wifiFactory->createSensor();
    auto display = wifiFactory->createDisplay();
    
    EXPECT_EQ("WiFi", device->getType());
    EXPECT_EQ("°C", sensor->getUnit());
    EXPECT_EQ("1920x1080", display->getResolution());
}

TEST_F(AbstractFactoryTest, BluetoothFactoryCreatesBluetoothProducts) {
    auto device = bluetoothFactory->createDevice();
    auto sensor = bluetoothFactory->createSensor();
    auto display = bluetoothFactory->createDisplay();
    
    EXPECT_EQ("Bluetooth", device->getType());
    EXPECT_EQ("°C", sensor->getUnit());
    EXPECT_EQ("800x600", display->getResolution());
}

TEST_F(AbstractFactoryTest, ProductsFromSameFactoryWorkTogether) {
    auto device = wifiFactory->createDevice();
    auto sensor = wifiFactory->createSensor();
    auto display = wifiFactory->createDisplay();
    
    device->connect();
    sensor->calibrate();
    
    EXPECT_TRUE(device->isConnected());
    EXPECT_TRUE(sensor->isReady());
    
    EXPECT_NO_THROW(device->send("test data"));
    EXPECT_NO_THROW(sensor->readValue());
    EXPECT_NO_THROW(display->show("test message"));
}

TEST_F(AbstractFactoryTest, IoTSystemWorksWithDifferentFactories) {
    // Test with WiFi factory
    auto wifiSystem = std::make_unique<IoTSystem>(std::move(wifiFactory));
    EXPECT_NO_THROW(wifiSystem->runSystemCycle());
    
    // Test with Bluetooth factory
    auto bluetoothSystem = std::make_unique<IoTSystem>(std::move(bluetoothFactory));
    EXPECT_NO_THROW(bluetoothSystem->runSystemCycle());
}

TEST_F(AbstractFactoryTest, FactoryRegistryWorks) {
    FactoryRegistry registry;
    
    registry.registerFactory("wifi", []() {
        return std::make_unique<WiFiDeviceFactory>("RegistryWiFi");
    });
    
    registry.registerFactory("bluetooth", []() {
        return std::make_unique<BluetoothDeviceFactory>("RegistryBT");
    });
    
    auto wifiFactory = registry.createFactory("wifi");
    auto bluetoothFactory = registry.createFactory("bluetooth");
    
    EXPECT_EQ("WiFi Factory", wifiFactory->getFactoryType());
    EXPECT_EQ("Bluetooth Factory", bluetoothFactory->getFactoryType());
    
    EXPECT_THROW(registry.createFactory("unknown"), std::runtime_error);
}

TEST_F(AbstractFactoryTest, ConfigurationManagerWorks) {
    ConfigurationManager config;
    config.setConfigValue("communication_type", "wifi");
    config.setConfigValue("wifi_ssid", "TestNetwork");
    
    auto factory = config.createFactoryFromConfig();
    EXPECT_EQ("WiFi Factory", factory->getFactoryType());
    
    config.setConfigValue("communication_type", "bluetooth");
    config.setConfigValue("bluetooth_device", "TestDevice");
    
    factory = config.createFactoryFromConfig();
    EXPECT_EQ("Bluetooth Factory", factory->getFactoryType());
    
    config.setConfigValue("communication_type", "unknown");
    EXPECT_THROW(config.createFactoryFromConfig(), std::runtime_error);
}
```

## Common Pitfalls and Solutions

### 1. **Memory Leaks with Raw Pointers**
```cpp
// ❌ Problematic - potential memory leaks
class BadAbstractFactory {
public:
    virtual Device* createDevice() = 0;  // Raw pointer return
};

// Client code
Device* device = factory->createDevice();
// If exception occurs, device is leaked!

// ✅ Better - use smart pointers
class GoodAbstractFactory {
public:
    virtual std::unique_ptr<Device> createDevice() = 0;
};

// Client code
auto device = factory->createDevice();
// Automatic cleanup even with exceptions
```

### 2. **Missing Virtual Destructor**
```cpp
// ❌ Problematic - undefined behavior
class BadFactory {
public:
    // Missing virtual destructor
    virtual std::unique_ptr<Device> createDevice() = 0;
};

// ✅ Better - virtual destructor
class GoodFactory {
public:
    virtual ~GoodFactory() = default;  // Virtual destructor
    virtual std::unique_ptr<Device> createDevice() = 0;
};
```

### 3. **Inconsistent Product Families**
```cpp
// ❌ Problematic - mixing product families
class InconsistentFactory : public IoTDeviceFactory {
public:
    std::unique_ptr<Device> createDevice() override {
        return std::make_unique<WiFiDevice>();    // WiFi family
    }
    
    std::unique_ptr<Sensor> createSensor() override {
        return std::make_unique<BluetoothSensor>(); // Bluetooth family - WRONG!
    }
    
    std::unique_ptr<Display> createDisplay() override {
        return std::make_unique<WiFiDisplay>();   // WiFi family
    }
};

// ✅ Better - ensure family consistency
class ConsistentFactory : public IoTDeviceFactory {
public:
    std::unique_ptr<Device> createDevice() override {
        return std::make_unique<WiFiDevice>();    // All WiFi family
    }
    
    std::unique_ptr<Sensor> createSensor() override {
        return std::make_unique<WiFiSensor>();    // All WiFi family
    }
    
    std::unique_ptr<Display> createDisplay() override {
        return std::make_unique<WiFiDisplay>();   // All WiFi family
    }
};
```

### 4. **Thread Safety Issues**
```cpp
// ❌ Problematic - not thread-safe
class UnsafeFactory {
private:
    static std::unique_ptr<IoTDeviceFactory> instance_;
    
public:
    static IoTDeviceFactory* getInstance() {
        if (!instance_) {
            instance_ = std::make_unique<WiFiDeviceFactory>(); // Race condition!
        }
        return instance_.get();
    }
};

// ✅ Better - thread-safe singleton
class SafeFactory {
private:
    static std::unique_ptr<IoTDeviceFactory> instance_;
    static std::mutex mutex_;
    
public:
    static IoTDeviceFactory* getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_ = std::make_unique<WiFiDeviceFactory>();
        }
        return instance_.get();
    }
};

// ✅ Even better - C++11 thread-safe static initialization
class BestFactory {
public:
    static IoTDeviceFactory& getInstance() {
        static WiFiDeviceFactory instance; // Thread-safe in C++11+
        return instance;
    }
};
```

## Best Practices

### 1. **Use Smart Pointers**
- Always return `std::unique_ptr` or `std::shared_ptr`
- Avoid raw pointer ownership
- Enable RAII and automatic cleanup

### 2. **Ensure Product Family Consistency**
- All products from one factory should work together
- Design interfaces to enforce compatibility
- Document family relationships clearly

### 3. **Consider Factory Registration**
- Use registry pattern for dynamic factory selection
- Enable plugin architectures
- Support runtime factory discovery

### 4. **Handle Configuration Gracefully**
- Support multiple configuration sources
- Provide sensible defaults
- Validate configuration parameters

### 5. **Design for Testability**
- Inject factories as dependencies
- Support mock factories for testing
- Keep factory interfaces minimal

### 6. **Performance Optimization**
- Consider object pooling for expensive objects
- Use lazy initialization when appropriate
- Minimize factory overhead

## Comparison with Other Creational Patterns

| Pattern | Purpose | Key Difference |
|---------|---------|----------------|
| **Abstract Factory** | Create families of objects | Multiple related products |
| **Factory Method** | Create single objects | Single product creation |
| **Builder** | Construct complex objects | Step-by-step construction |
| **Singleton** | Ensure single instance | Instance management |
| **Prototype** | Clone existing objects | Object copying |

## When to Use Abstract Factory

### ✅ **Use When:**
- System needs to work with multiple product families
- Products in a family are designed to work together
- You want to enforce family consistency
- System should be independent of product creation
- Configuration determines which family to use

### ❌ **Don't Use When:**
- Only single products need to be created (use Factory Method)
- Product families rarely change
- Simplicity is more important than flexibility
- No clear product family relationships exist

## Conclusion

The Abstract Factory pattern is essential for:
- **Product family management** ensuring compatibility
- **Platform abstraction** enabling cross-platform development
- **Configuration-driven architecture** supporting multiple environments
- **Plugin systems** allowing runtime component selection
- **Testing isolation** through factory injection

Key benefits:
- **Family consistency** prevents incompatible product mixing
- **Easy switching** between product families
- **Isolation** from concrete product classes
- **Configuration support** for different environments

The pattern excels in enterprise applications, game engines, GUI frameworks, and any system requiring consistent object families that can be switched based on configuration or runtime conditions.

====================================================================================================
1. **Key Features:**
    - Complete Pattern Analysis – Detailed explanation of your Abstract Factory implementation
    - Visual Diagrams – ASCII art showing the Abstract Factory structure and relationships
    - Modern C++ Implementation – Enhanced version with smart pointers, RAII, and modern best practices
    - Real-World Applications – GUI frameworks, database layers, and game engine examples
    - Advanced Patterns – Registry-based, dependency injection, and asynchronous factories
    - Performance Optimization – Object pooling and benchmarking techniques
    - Comprehensive Testing – Unit tests and testing strategies
    - Best Practices – Professional development guidelines

2. **Documentation Structure:**
    - Pattern Overview – Core concepts and problem solved
    - Code Analysis – Detailed breakdown of your original implementation
    - Modern Implementation – IoT system example with multiple product families
    - Usage Examples – Configuration-based, registry-based, and environment detection
    - Real-World Applications – Cross-platform GUI, database abstraction, graphics API
    - Advanced Techniques – Parameterized factories, DI containers, async creation
    - Performance Considerations – Memory optimization and benchmarking
    - Testing Strategy – Comprehensive test suite examples
    - Common Pitfalls – Memory management, thread safety, and family consistency
    - Best Practices – Smart pointers, configuration handling, and design guidelines

3. **Improvements Made:**
    - Enhanced the original example with proper product families (Device, Sensor, Display)
    - Added smart pointer usage throughout for memory safety
    - Implemented factory registry for dynamic factory selection
    - Added configuration management for environment-based factory creation
    - Included comprehensive error handling and validation
    - Provided real-world examples from different domains
    - Added performance benchmarking and optimization techniques
    - Included extensive testing examples with Google Test framework
