// C++17 std::any - Type-Erased Container
// Compile: g++ -std=c++17 -o any_demo any_demo.cpp
// Run: ./any_demo

#include <iostream>
#include <any>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include <memory>

// 1. Custom types for demonstration
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "Point(" << p.x << ", " << p.y << ")";
    }
};

struct Person {
    std::string name;
    int age;
    Person(const std::string& n, int a) : name(n), age(a) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << "Person(name: " << p.name << ", age: " << p.age << ")";
    }
};

// 2. Generic container using std::any
class AnyContainer {
private:
    std::vector<std::any> items;
    
public:
    template<typename T>
    void add(T&& item) {
        items.emplace_back(std::forward<T>(item));
    }
    
    size_t size() const {
        return items.size();
    }
    
    std::any& at(size_t index) {
        return items.at(index);
    }
    
    const std::any& at(size_t index) const {
        return items.at(index);
    }
    
    template<typename T>
    T* get_if(size_t index) {
        if (index < items.size()) {
            return std::any_cast<T>(&items[index]);
        }
        return nullptr;
    }
    
    template<typename T>
    std::vector<T*> find_all() {
        std::vector<T*> results;
        for (auto& item : items) {
            if (auto* ptr = std::any_cast<T>(&item)) {
                results.push_back(ptr);
            }
        }
        return results;
    }
    
    void print_types() const {
        std::cout << "Container types:" << std::endl;
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << "  [" << i << "]: " << items[i].type().name();
            if (items[i].has_value()) {
                std::cout << " (has value)";
            } else {
                std::cout << " (empty)";
            }
            std::cout << std::endl;
        }
    }
};

// 3. Configuration system with std::any
class FlexibleConfig {
private:
    std::map<std::string, std::any> settings;
    
public:
    template<typename T>
    void set(const std::string& key, T&& value) {
        settings[key] = std::forward<T>(value);
    }
    
    template<typename T>
    T get(const std::string& key) const {
        auto it = settings.find(key);
        if (it != settings.end()) {
            return std::any_cast<T>(it->second);
        }
        throw std::runtime_error("Key not found or wrong type: " + key);
    }
    
    template<typename T>
    T get_or_default(const std::string& key, const T& default_value) const {
        auto it = settings.find(key);
        if (it != settings.end()) {
            try {
                return std::any_cast<T>(it->second);
            } catch (const std::bad_any_cast&) {
                return default_value;
            }
        }
        return default_value;
    }
    
    bool has_key(const std::string& key) const {
        return settings.find(key) != settings.end();
    }
    
    template<typename T>
    bool is_type(const std::string& key) const {
        auto it = settings.find(key);
        if (it != settings.end()) {
            return it->second.type() == typeid(T);
        }
        return false;
    }
    
    void remove(const std::string& key) {
        settings.erase(key);
    }
    
    void clear() {
        settings.clear();
    }
    
    void print_all() const {
        std::cout << "Configuration settings:" << std::endl;
        for (const auto& [key, value] : settings) {
            std::cout << "  " << key << ": " << value.type().name();
            if (value.has_value()) {
                std::cout << " (has value)";
                
                // Try to print some common types
                if (value.type() == typeid(int)) {
                    std::cout << " = " << std::any_cast<int>(value);
                } else if (value.type() == typeid(double)) {
                    std::cout << " = " << std::any_cast<double>(value);
                } else if (value.type() == typeid(std::string)) {
                    std::cout << " = \"" << std::any_cast<std::string>(value) << "\"";
                } else if (value.type() == typeid(bool)) {
                    std::cout << " = " << (std::any_cast<bool>(value) ? "true" : "false");
                }
            } else {
                std::cout << " (empty)";
            }
            std::cout << std::endl;
        }
    }
};

// 4. Property system for objects
class GameObject {
private:
    std::map<std::string, std::any> properties;
    std::string object_name;
    
public:
    GameObject(const std::string& name) : object_name(name) {}
    
    template<typename T>
    void set_property(const std::string& name, T&& value) {
        properties[name] = std::forward<T>(value);
    }
    
    template<typename T>
    T get_property(const std::string& name) const {
        auto it = properties.find(name);
        if (it != properties.end()) {
            return std::any_cast<T>(it->second);
        }
        throw std::runtime_error("Property not found: " + name);
    }
    
    template<typename T>
    bool has_property_of_type(const std::string& name) const {
        auto it = properties.find(name);
        return it != properties.end() && it->second.type() == typeid(T);
    }
    
    bool has_property(const std::string& name) const {
        return properties.find(name) != properties.end();
    }
    
    void remove_property(const std::string& name) {
        properties.erase(name);
    }
    
    std::vector<std::string> list_properties() const {
        std::vector<std::string> keys;
        for (const auto& [key, value] : properties) {
            keys.push_back(key);
        }
        return keys;
    }
    
    void print_properties() const {
        std::cout << "GameObject '" << object_name << "' properties:" << std::endl;
        for (const auto& [name, value] : properties) {
            std::cout << "  " << name << ": " << value.type().name() << std::endl;
        }
    }
    
    const std::string& name() const { return object_name; }
};

// 5. Event system with std::any
class Event {
private:
    std::string event_type;
    std::map<std::string, std::any> data;
    
public:
    Event(const std::string& type) : event_type(type) {}
    
    template<typename T>
    void add_data(const std::string& key, T&& value) {
        data[key] = std::forward<T>(value);
    }
    
    template<typename T>
    T get_data(const std::string& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return std::any_cast<T>(it->second);
        }
        throw std::runtime_error("Event data not found: " + key);
    }
    
    template<typename T>
    bool has_data_of_type(const std::string& key) const {
        auto it = data.find(key);
        return it != data.end() && it->second.type() == typeid(T);
    }
    
    const std::string& type() const { return event_type; }
    
    void print() const {
        std::cout << "Event '" << event_type << "' data:" << std::endl;
        for (const auto& [key, value] : data) {
            std::cout << "  " << key << ": " << value.type().name() << std::endl;
        }
    }
};

class EventHandler {
public:
    virtual ~EventHandler() = default;
    virtual void handle(const Event& event) = 0;
};

class LoggingHandler : public EventHandler {
public:
    void handle(const Event& event) override {
        std::cout << "Logging: Received event '" << event.type() << "'" << std::endl;
        
        // Handle specific event types
        if (event.type() == "user_login") {
            if (event.has_data_of_type<std::string>("username")) {
                auto username = event.get_data<std::string>("username");
                std::cout << "  User logged in: " << username << std::endl;
            }
        } else if (event.type() == "file_operation") {
            if (event.has_data_of_type<std::string>("filename") && 
                event.has_data_of_type<std::string>("operation")) {
                auto filename = event.get_data<std::string>("filename");
                auto operation = event.get_data<std::string>("operation");
                std::cout << "  File " << operation << ": " << filename << std::endl;
            }
        }
    }
};

// 6. Serialization helpers
class Serializer {
public:
    static std::string serialize(const std::any& value) {
        if (value.type() == typeid(int)) {
            return std::to_string(std::any_cast<int>(value));
        } else if (value.type() == typeid(double)) {
            return std::to_string(std::any_cast<double>(value));
        } else if (value.type() == typeid(std::string)) {
            return "\"" + std::any_cast<std::string>(value) + "\"";
        } else if (value.type() == typeid(bool)) {
            return std::any_cast<bool>(value) ? "true" : "false";
        } else if (value.type() == typeid(Point)) {
            const auto& p = std::any_cast<Point>(value);
            return "Point(" + std::to_string(p.x) + "," + std::to_string(p.y) + ")";
        }
        return "unknown_type:" + std::string(value.type().name());
    }
    
    static std::any deserialize(const std::string& str, const std::type_info& target_type) {
        if (target_type == typeid(int)) {
            return std::stoi(str);
        } else if (target_type == typeid(double)) {
            return std::stod(str);
        } else if (target_type == typeid(std::string)) {
            if (str.size() >= 2 && str.front() == '"' && str.back() == '"') {
                return str.substr(1, str.size() - 2);
            }
            return str;
        } else if (target_type == typeid(bool)) {
            return str == "true";
        }
        throw std::runtime_error("Unsupported type for deserialization");
    }
};

// 7. Performance comparison helpers
template<typename T>
class TypedContainer {
private:
    std::vector<T> items;
    
public:
    void add(const T& item) {
        items.push_back(item);
    }
    
    const T& get(size_t index) const {
        return items.at(index);
    }
    
    size_t size() const {
        return items.size();
    }
};

int main() {
    std::cout << "=== C++17 STD::ANY DEMO ===" << std::endl;
    
    // 1. Basic std::any usage
    std::cout << "\n1. Basic Any Usage:" << std::endl;
    
    std::any a1 = 42;
    std::any a2 = 3.14;
    std::any a3 = std::string("Hello");
    std::any a4;  // Empty any
    
    std::cout << "a1 has value: " << a1.has_value() << std::endl;
    std::cout << "a1 type: " << a1.type().name() << std::endl;
    std::cout << "a4 has value: " << a4.has_value() << std::endl;
    
    // Safe casting
    try {
        int value = std::any_cast<int>(a1);
        std::cout << "a1 value: " << value << std::endl;
    } catch (const std::bad_any_cast& e) {
        std::cout << "Bad cast: " << e.what() << std::endl;
    }
    
    // Pointer-based casting (safe)
    if (auto* ptr = std::any_cast<int>(&a1)) {
        std::cout << "a1 value (pointer cast): " << *ptr << std::endl;
    }
    
    if (auto* ptr = std::any_cast<double>(&a1)) {
        std::cout << "This won't print - a1 is not a double" << std::endl;
    } else {
        std::cout << "a1 is not a double" << std::endl;
    }
    
    // 2. Any with custom types
    std::cout << "\n2. Any with Custom Types:" << std::endl;
    
    std::any point_any = Point{3.5, 4.2};
    std::any person_any = Person{"Alice", 30};
    
    if (point_any.type() == typeid(Point)) {
        Point p = std::any_cast<Point>(point_any);
        std::cout << "Point: " << p << std::endl;
    }
    
    if (person_any.type() == typeid(Person)) {
        Person person = std::any_cast<Person>(person_any);
        std::cout << "Person: " << person << std::endl;
    }
    
    // 3. Generic container
    std::cout << "\n3. Generic Container:" << std::endl;
    
    AnyContainer container;
    
    container.add(42);
    container.add(3.14);
    container.add(std::string("Hello"));
    container.add(Point{1, 2});
    container.add(Person{"Bob", 25});
    container.add(true);
    
    std::cout << "Container size: " << container.size() << std::endl;
    container.print_types();
    
    // Retrieve specific types
    if (auto* int_ptr = container.get_if<int>(0)) {
        std::cout << "First item as int: " << *int_ptr << std::endl;
    }
    
    if (auto* point_ptr = container.get_if<Point>(3)) {
        std::cout << "Fourth item as Point: " << *point_ptr << std::endl;
    }
    
    // Find all items of specific type
    auto all_strings = container.find_all<std::string>();
    std::cout << "Found " << all_strings.size() << " strings" << std::endl;
    
    auto all_points = container.find_all<Point>();
    std::cout << "Found " << all_points.size() << " points" << std::endl;
    for (auto* point : all_points) {
        std::cout << "  Point: " << *point << std::endl;
    }
    
    // 4. Flexible configuration system
    std::cout << "\n4. Flexible Configuration:" << std::endl;
    
    FlexibleConfig config;
    
    config.set("debug", true);
    config.set("port", 8080);
    config.set("server_name", std::string("MyServer"));
    config.set("timeout", 30.5);
    config.set("allowed_ips", std::vector<std::string>{"127.0.0.1", "192.168.1.1"});
    
    config.print_all();
    
    // Retrieve values
    std::cout << "\nRetrieving configuration values:" << std::endl;
    std::cout << "Debug mode: " << config.get<bool>("debug") << std::endl;
    std::cout << "Port: " << config.get<int>("port") << std::endl;
    std::cout << "Server name: " << config.get<std::string>("server_name") << std::endl;
    std::cout << "Timeout: " << config.get<double>("timeout") << std::endl;
    
    // Using defaults
    std::cout << "Max connections (default): " << config.get_or_default("max_connections", 100) << std::endl;
    std::cout << "Log level (default): " << config.get_or_default("log_level", std::string("INFO")) << std::endl;
    
    // Type checking
    std::cout << "Port is int: " << config.is_type<int>("port") << std::endl;
    std::cout << "Port is string: " << config.is_type<std::string>("port") << std::endl;
    
    // 5. GameObject property system
    std::cout << "\n5. GameObject Property System:" << std::endl;
    
    GameObject player("Player");
    
    player.set_property("health", 100);
    player.set_property("position", Point{10.5, 20.3});
    player.set_property("name", std::string("Hero"));
    player.set_property("alive", true);
    player.set_property("inventory", std::vector<std::string>{"sword", "potion", "key"});
    
    player.print_properties();
    
    // Access properties
    std::cout << "\nPlayer properties:" << std::endl;
    std::cout << "Health: " << player.get_property<int>("health") << std::endl;
    std::cout << "Position: " << player.get_property<Point>("position") << std::endl;
    std::cout << "Name: " << player.get_property<std::string>("name") << std::endl;
    std::cout << "Alive: " << player.get_property<bool>("alive") << std::endl;
    
    // Property existence checks
    std::cout << "Has 'health' property: " << player.has_property("health") << std::endl;
    std::cout << "Has 'mana' property: " << player.has_property("mana") << std::endl;
    std::cout << "Health is int: " << player.has_property_of_type<int>("health") << std::endl;
    std::cout << "Health is string: " << player.has_property_of_type<std::string>("health") << std::endl;
    
    // 6. Event system
    std::cout << "\n6. Event System:" << std::endl;
    
    LoggingHandler handler;
    
    // User login event
    Event login_event("user_login");
    login_event.add_data("username", std::string("alice"));
    login_event.add_data("timestamp", 1634567890);
    login_event.add_data("ip_address", std::string("192.168.1.100"));
    
    handler.handle(login_event);
    
    // File operation event
    Event file_event("file_operation");
    file_event.add_data("filename", std::string("data.txt"));
    file_event.add_data("operation", std::string("read"));
    file_event.add_data("size", 1024);
    
    handler.handle(file_event);
    
    // 7. Any assignment and reassignment
    std::cout << "\n7. Any Assignment and Reassignment:" << std::endl;
    
    std::any changing_any = 42;
    std::cout << "Initially int: " << std::any_cast<int>(changing_any) << std::endl;
    
    changing_any = 3.14;
    std::cout << "Now double: " << std::any_cast<double>(changing_any) << std::endl;
    
    changing_any = std::string("Now string");
    std::cout << "Now string: " << std::any_cast<std::string>(changing_any) << std::endl;
    
    changing_any = Point{5, 6};
    std::cout << "Now Point: " << std::any_cast<Point>(changing_any) << std::endl;
    
    changing_any.reset();
    std::cout << "After reset, has value: " << changing_any.has_value() << std::endl;
    
    // 8. Serialization example
    std::cout << "\n8. Serialization Example:" << std::endl;
    
    std::vector<std::any> values = {
        42,
        3.14,
        std::string("Hello"),
        true,
        Point{1.5, 2.5}
    };
    
    std::cout << "Serialized values:" << std::endl;
    for (const auto& value : values) {
        std::cout << "  " << Serializer::serialize(value) << std::endl;
    }
    
    // 9. Exception handling
    std::cout << "\n9. Exception Handling:" << std::endl;
    
    std::any test_any = 42;
    
    try {
        int correct = std::any_cast<int>(test_any);
        std::cout << "Correct cast: " << correct << std::endl;
    } catch (const std::bad_any_cast& e) {
        std::cout << "This won't print" << std::endl;
    }
    
    try {
        std::string wrong = std::any_cast<std::string>(test_any);
        std::cout << "This won't print" << std::endl;
    } catch (const std::bad_any_cast& e) {
        std::cout << "Caught bad_any_cast: " << e.what() << std::endl;
    }
    
    // 10. Performance comparison
    std::cout << "\n10. Performance Comparison:" << std::endl;
    
    const int iterations = 1000000;
    
    // std::any approach
    auto start = std::chrono::high_resolution_clock::now();
    
    AnyContainer any_container;
    for (int i = 0; i < iterations; ++i) {
        any_container.add(i);
    }
    
    int any_sum = 0;
    for (size_t i = 0; i < any_container.size(); ++i) {
        if (auto* ptr = any_container.get_if<int>(i)) {
            any_sum += *ptr;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto any_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Typed container approach
    start = std::chrono::high_resolution_clock::now();
    
    TypedContainer<int> typed_container;
    for (int i = 0; i < iterations; ++i) {
        typed_container.add(i);
    }
    
    int typed_sum = 0;
    for (size_t i = 0; i < typed_container.size(); ++i) {
        typed_sum += typed_container.get(i);
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto typed_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Performance (" << iterations << " operations):" << std::endl;
    std::cout << "std::any container: " << any_duration.count() << " microseconds (sum: " << any_sum << ")" << std::endl;
    std::cout << "Typed container: " << typed_duration.count() << " microseconds (sum: " << typed_sum << ")" << std::endl;
    std::cout << "Overhead factor: " << static_cast<double>(any_duration.count()) / typed_duration.count() << "x" << std::endl;
    
    std::cout << "\n=== STD::ANY BENEFITS ===" << std::endl;
    std::cout << "✅ Type erasure - store any type without knowing it at compile time" << std::endl;
    std::cout << "✅ Value semantics - proper copy/move semantics" << std::endl;
    std::cout << "✅ Type safety - runtime type checking with exceptions" << std::endl;
    std::cout << "✅ No inheritance required - works with any copyable type" << std::endl;
    std::cout << "✅ Perfect for generic containers and configuration systems" << std::endl;
    std::cout << "✅ Exception safety - throws on wrong type access" << std::endl;
    std::cout << "✅ Small object optimization in some implementations" << std::endl;
    std::cout << "⚠️  Runtime overhead - type checking and possible heap allocation" << std::endl;
    std::cout << "⚠️  Loss of compile-time type safety" << std::endl;
    std::cout  << "⚠️  Requires exception handling for type safety" << std::endl;
    std::cout << "⚠️  Not suitable for performance-critical code" << std::endl;
    std::cout << "⚠️  Can hide design issues - sometimes polymorphism is better" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++17 -Wall -Wextra -o any_demo any_demo.cpp
./any_demo

C++17 std::any Key Features:
1. Type-erased container for any copyable type
2. Runtime type safety with exception handling
3. Value semantics with proper copy/move operations
4. No inheritance requirements for stored types

Basic Usage:
std::any a = 42;                  // Store int
a = 3.14;                         // Now store double
a = std::string("hello");         // Now store string

Access Methods:
- a.has_value()           - Check if any contains a value
- a.type()               - Get type_info of stored type
- std::any_cast<T>(a)    - Cast to type T (throws if wrong type)
- std::any_cast<T>(&a)   - Get pointer to T, nullptr if wrong type
- a.reset()              - Clear the any

Common Use Cases:
- Configuration systems with mixed types
- Generic containers for different types
- Property systems for game objects
- Event systems with arbitrary data
- Plugin systems with unknown types
- Serialization frameworks

Type Safety:
- Runtime type checking with std::bad_any_cast exception
- Use std::any_cast<T*> for safe pointer-based access
- Check type with a.type() == typeid(T)
- Always handle std::bad_any_cast exceptions

Performance Characteristics:
- Small object optimization for small types
- Heap allocation for large types
- Runtime type checking overhead
- Slower than typed alternatives
- Memory overhead for type information

Best Practices:
- Use for truly generic scenarios where type is unknown
- Always handle std::bad_any_cast exceptions
- Prefer std::variant when types are known at compile time
- Consider performance impact in hot paths
- Use std::any_cast<T*> for safe access without exceptions
- Document expected types when using in APIs

Comparison with Alternatives:
- vs void*: Type safe, but slower
- vs std::variant: More flexible, but less performant
- vs inheritance: No base class required, but runtime overhead
- vs templates: Runtime polymorphism vs compile-time
*/
