// C++17 std::variant - Type-Safe Union
// Compile: g++ -std=c++17 -o variant_demo variant_demo.cpp
// Run: ./variant_demo

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <map>
#include <type_traits>
#include <cassert>

// 1. Basic variant usage
using Value = std::variant<int, double, std::string>;

// 2. Custom types in variant
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    void print() const {
        std::cout << "Point(" << x << ", " << y << ")";
    }
};

struct Circle {
    Point center;
    double radius;
    Circle(Point c = {0, 0}, double r = 1) : center(c), radius(r) {}
    
    void print() const {
        std::cout << "Circle(center: ";
        center.print();
        std::cout << ", radius: " << radius << ")";
    }
};

struct Rectangle {
    Point top_left;
    double width, height;
    Rectangle(Point tl = {0, 0}, double w = 1, double h = 1) 
        : top_left(tl), width(w), height(h) {}
    
    void print() const {
        std::cout << "Rectangle(top_left: ";
        top_left.print();
        std::cout << ", width: " << width << ", height: " << height << ")";
    }
};

using Shape = std::variant<Point, Circle, Rectangle>;

// 3. Visitor patterns
class ShapeVisitor {
public:
    void operator()(const Point& p) const {
        std::cout << "Visiting point at (" << p.x << ", " << p.y << ")" << std::endl;
    }
    
    void operator()(const Circle& c) const {
        std::cout << "Visiting circle with center (" << c.center.x << ", " << c.center.y 
                  << ") and radius " << c.radius << std::endl;
    }
    
    void operator()(const Rectangle& r) const {
        std::cout << "Visiting rectangle at (" << r.top_left.x << ", " << r.top_left.y 
                  << ") with dimensions " << r.width << "x" << r.height << std::endl;
    }
};

// Generic lambda visitor
auto area_calculator = [](const auto& shape) -> double {
    using T = std::decay_t<decltype(shape)>;
    if constexpr (std::is_same_v<T, Point>) {
        return 0.0;  // Point has no area
    } else if constexpr (std::is_same_v<T, Circle>) {
        return 3.14159 * shape.radius * shape.radius;
    } else if constexpr (std::is_same_v<T, Rectangle>) {
        return shape.width * shape.height;
    }
    return 0.0;
};

// 4. Error handling with variant
enum class ErrorCode {
    SUCCESS,
    FILE_NOT_FOUND,
    PERMISSION_DENIED,
    INVALID_FORMAT,
    NETWORK_ERROR
};

struct Error {
    ErrorCode code;
    std::string message;
    
    Error(ErrorCode c, const std::string& msg) : code(c), message(msg) {}
};

template<typename T>
using Result = std::variant<T, Error>;

Result<std::string> read_file(const std::string& filename) {
    if (filename.empty()) {
        return Error{ErrorCode::INVALID_FORMAT, "Empty filename"};
    }
    if (filename == "nonexistent.txt") {
        return Error{ErrorCode::FILE_NOT_FOUND, "File not found: " + filename};
    }
    if (filename == "protected.txt") {
        return Error{ErrorCode::PERMISSION_DENIED, "Permission denied: " + filename};
    }
    
    return std::string{"File contents of " + filename};
}

Result<int> parse_number(const std::string& str) {
    if (str.empty()) {
        return Error{ErrorCode::INVALID_FORMAT, "Empty string"};
    }
    
    try {
        return std::stoi(str);
    } catch (const std::exception& e) {
        return Error{ErrorCode::INVALID_FORMAT, "Cannot parse '" + str + "' as number"};
    }
}

// 5. State machine with variant
struct StateIdle {};
struct StateRunning { 
    int progress = 0; 
    StateRunning(int p = 0) : progress(p) {}
};
struct StatePaused { 
    int saved_progress = 0; 
    StatePaused(int p = 0) : saved_progress(p) {}
};
struct StateCompleted {};
struct StateError { 
    std::string error_message; 
    StateError(const std::string& msg) : error_message(msg) {}
};

using State = std::variant<StateIdle, StateRunning, StatePaused, StateCompleted, StateError>;

class StateMachine {
private:
    State current_state;
    
public:
    StateMachine() : current_state(StateIdle{}) {}
    
    void start() {
        if (std::holds_alternative<StateIdle>(current_state)) {
            current_state = StateRunning{0};
            std::cout << "Started from idle state" << std::endl;
        } else if (std::holds_alternative<StatePaused>(current_state)) {
            auto paused = std::get<StatePaused>(current_state);
            current_state = StateRunning{paused.saved_progress};
            std::cout << "Resumed from paused state with progress " << paused.saved_progress << std::endl;
        } else {
            std::cout << "Cannot start from current state" << std::endl;
        }
    }
    
    void pause() {
        if (std::holds_alternative<StateRunning>(current_state)) {
            auto running = std::get<StateRunning>(current_state);
            current_state = StatePaused{running.progress};
            std::cout << "Paused with progress " << running.progress << std::endl;
        } else {
            std::cout << "Cannot pause from current state" << std::endl;
        }
    }
    
    void update_progress(int progress) {
        if (std::holds_alternative<StateRunning>(current_state)) {
            auto& running = std::get<StateRunning>(current_state);
            running.progress = progress;
            if (progress >= 100) {
                current_state = StateCompleted{};
                std::cout << "Task completed!" << std::endl;
            } else {
                std::cout << "Progress updated to " << progress << "%" << std::endl;
            }
        }
    }
    
    void error(const std::string& message) {
        current_state = StateError{message};
        std::cout << "Error occurred: " << message << std::endl;
    }
    
    void reset() {
        current_state = StateIdle{};
        std::cout << "Reset to idle state" << std::endl;
    }
    
    void print_state() const {
        std::visit([](const auto& state) {
            using T = std::decay_t<decltype(state)>;
            if constexpr (std::is_same_v<T, StateIdle>) {
                std::cout << "Current state: Idle";
            } else if constexpr (std::is_same_v<T, StateRunning>) {
                std::cout << "Current state: Running (progress: " << state.progress << "%)";
            } else if constexpr (std::is_same_v<T, StatePaused>) {
                std::cout << "Current state: Paused (saved progress: " << state.saved_progress << "%)";
            } else if constexpr (std::is_same_v<T, StateCompleted>) {
                std::cout << "Current state: Completed";
            } else if constexpr (std::is_same_v<T, StateError>) {
                std::cout << "Current state: Error (" << state.error_message << ")";
            }
            std::cout << std::endl;
        }, current_state);
    }
};

// 6. Configuration system with variant
struct DatabaseConfig {
    std::string host;
    int port;
    std::string database;
    DatabaseConfig(const std::string& h, int p, const std::string& db) 
        : host(h), port(p), database(db) {}
};

struct FileConfig {
    std::string path;
    bool read_only;
    FileConfig(const std::string& p, bool ro = false) : path(p), read_only(ro) {}
};

struct NetworkConfig {
    std::string url;
    int timeout_seconds;
    NetworkConfig(const std::string& u, int t = 30) : url(u), timeout_seconds(t) {}
};

using Config = std::variant<DatabaseConfig, FileConfig, NetworkConfig>;

class ConfigManager {
private:
    std::map<std::string, Config> configs;
    
public:
    void add_config(const std::string& name, Config config) {
        configs[name] = std::move(config);
    }
    
    void print_config(const std::string& name) const {
        auto it = configs.find(name);
        if (it == configs.end()) {
            std::cout << "Config '" << name << "' not found" << std::endl;
            return;
        }
        
        std::cout << "Config '" << name << "': ";
        std::visit([](const auto& config) {
            using T = std::decay_t<decltype(config)>;
            if constexpr (std::is_same_v<T, DatabaseConfig>) {
                std::cout << "Database(" << config.host << ":" << config.port 
                          << "/" << config.database << ")";
            } else if constexpr (std::is_same_v<T, FileConfig>) {
                std::cout << "File(" << config.path 
                          << ", read_only: " << config.read_only << ")";
            } else if constexpr (std::is_same_v<T, NetworkConfig>) {
                std::cout << "Network(" << config.url 
                          << ", timeout: " << config.timeout_seconds << "s)";
            }
        }, it->second);
        std::cout << std::endl;
    }
};

// 7. JSON-like data structure
using JsonValue = std::variant<
    std::nullptr_t,
    bool,
    int,
    double,
    std::string,
    std::vector<struct JsonNode>,
    std::map<std::string, struct JsonNode>
>;

struct JsonNode {
    JsonValue value;
    
    JsonNode() : value(nullptr) {}
    JsonNode(JsonValue v) : value(std::move(v)) {}
    
    template<typename T>
    bool is() const {
        return std::holds_alternative<T>(value);
    }
    
    template<typename T>
    const T& get() const {
        return std::get<T>(value);
    }
    
    void print(int indent = 0) const {
        std::string spaces(indent, ' ');
        std::visit([&](const auto& val) {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, std::nullptr_t>) {
                std::cout << "null";
            } else if constexpr (std::is_same_v<T, bool>) {
                std::cout << (val ? "true" : "false");
            } else if constexpr (std::is_same_v<T, int>) {
                std::cout << val;
            } else if constexpr (std::is_same_v<T, double>) {
                std::cout << val;
            } else if constexpr (std::is_same_v<T, std::string>) {
                std::cout << "\"" << val << "\"";
            } else if constexpr (std::is_same_v<T, std::vector<JsonNode>>) {
                std::cout << "[\n";
                for (size_t i = 0; i < val.size(); ++i) {
                    std::cout << spaces << "  ";
                    val[i].print(indent + 2);
                    if (i < val.size() - 1) std::cout << ",";
                    std::cout << "\n";
                }
                std::cout << spaces << "]";
            } else if constexpr (std::is_same_v<T, std::map<std::string, JsonNode>>) {
                std::cout << "{\n";
                auto it = val.begin();
                for (; it != val.end(); ++it) {
                    std::cout << spaces << "  \"" << it->first << "\": ";
                    it->second.print(indent + 2);
                    auto next_it = it;
                    if (++next_it != val.end()) std::cout << ",";
                    std::cout << "\n";
                }
                std::cout << spaces << "}";
            }
        }, value);
    }
};

int main() {
    std::cout << "=== C++17 STD::VARIANT DEMO ===" << std::endl;
    
    // 1. Basic variant usage
    std::cout << "\n1. Basic Variant Usage:" << std::endl;
    
    Value v1 = 42;
    Value v2 = 3.14;
    Value v3 = std::string("Hello");
    
    std::cout << "v1 holds int: " << std::holds_alternative<int>(v1) << std::endl;
    std::cout << "v1 value: " << std::get<int>(v1) << std::endl;
    std::cout << "v1 index: " << v1.index() << std::endl;
    
    std::cout << "v2 holds double: " << std::holds_alternative<double>(v2) << std::endl;
    std::cout << "v2 value: " << std::get<double>(v2) << std::endl;
    
    std::cout << "v3 holds string: " << std::holds_alternative<std::string>(v3) << std::endl;
    std::cout << "v3 value: " << std::get<std::string>(v3) << std::endl;
    
    // Safe access with get_if
    if (auto* ptr = std::get_if<int>(&v1)) {
        std::cout << "v1 safely accessed as int: " << *ptr << std::endl;
    }
    
    if (auto* ptr = std::get_if<double>(&v1)) {
        std::cout << "This won't print - v1 is not a double" << std::endl;
    } else {
        std::cout << "v1 is not a double" << std::endl;
    }
    
    // 2. Variant assignment
    std::cout << "\n2. Variant Assignment:" << std::endl;
    
    Value changing_var = 100;
    std::cout << "Initially int: " << std::get<int>(changing_var) << std::endl;
    
    changing_var = 2.718;
    std::cout << "Now double: " << std::get<double>(changing_var) << std::endl;
    
    changing_var = std::string("Now string");
    std::cout << "Now string: " << std::get<std::string>(changing_var) << std::endl;
    
    // 3. Visiting variants
    std::cout << "\n3. Visiting Variants:" << std::endl;
    
    std::vector<Value> values = {42, 3.14, std::string("Hello"), 100, 2.71, std::string("World")};
    
    // Using std::visit with lambda
    for (const auto& val : values) {
        std::visit([](const auto& v) {
            std::cout << "Value: " << v << " (type: " << typeid(v).name() << ")" << std::endl;
        }, val);
    }
    
    // Type-specific handling
    std::cout << "\nType-specific processing:" << std::endl;
    for (const auto& val : values) {
        std::visit([](const auto& v) {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, int>) {
                std::cout << "Processing integer: " << v << " -> " << (v * 2) << std::endl;
            } else if constexpr (std::is_same_v<T, double>) {
                std::cout << "Processing double: " << v << " -> " << (v / 2.0) << std::endl;
            } else if constexpr (std::is_same_v<T, std::string>) {
                std::cout << "Processing string: " << v << " -> " << v + "!" << std::endl;
            }
        }, val);
    }
    
    // 4. Custom types with variant
    std::cout << "\n4. Custom Types with Variant:" << std::endl;
    
    std::vector<Shape> shapes = {
        Point{1, 2},
        Circle{{3, 4}, 5},
        Rectangle{{0, 0}, 10, 20},
        Point{-1, -2}
    };
    
    std::cout << "Shape visitor:" << std::endl;
    ShapeVisitor visitor;
    for (const auto& shape : shapes) {
        std::visit(visitor, shape);
    }
    
    std::cout << "\nCalculating areas:" << std::endl;
    for (const auto& shape : shapes) {
        double area = std::visit(area_calculator, shape);
        std::cout << "Shape area: " << area << std::endl;
    }
    
    // 5. Error handling with Result type
    std::cout << "\n5. Error Handling with Result Type:" << std::endl;
    
    std::vector<std::string> filenames = {"data.txt", "", "nonexistent.txt", "protected.txt"};
    
    for (const auto& filename : filenames) {
        auto result = read_file(filename);
        
        if (std::holds_alternative<std::string>(result)) {
            std::cout << "Success: " << std::get<std::string>(result) << std::endl;
        } else {
            const auto& error = std::get<Error>(result);
            std::cout << "Error: " << error.message << std::endl;
        }
    }
    
    std::cout << "\nParsing numbers:" << std::endl;
    std::vector<std::string> number_strings = {"42", "3.14", "hello", "", "100"};
    
    for (const auto& str : number_strings) {
        auto result = parse_number(str);
        
        std::visit([&str](const auto& r) {
            using T = std::decay_t<decltype(r)>;
            if constexpr (std::is_same_v<T, int>) {
                std::cout << "Parsed '" << str << "' as: " << r << std::endl;
            } else if constexpr (std::is_same_v<T, Error>) {
                std::cout << "Failed to parse '" << str << "': " << r.message << std::endl;
            }
        }, result);
    }
    
    // 6. State machine demo
    std::cout << "\n6. State Machine Demo:" << std::endl;
    
    StateMachine machine;
    
    machine.print_state();
    machine.start();
    machine.print_state();
    
    machine.update_progress(25);
    machine.print_state();
    
    machine.pause();
    machine.print_state();
    
    machine.start();  // Resume
    machine.print_state();
    
    machine.update_progress(75);
    machine.update_progress(100);  // Complete
    machine.print_state();
    
    machine.reset();
    machine.print_state();
    
    machine.start();
    machine.error("Network connection lost");
    machine.print_state();
    
    // 7. Configuration management
    std::cout << "\n7. Configuration Management:" << std::endl;
    
    ConfigManager config_mgr;
    
    config_mgr.add_config("database", DatabaseConfig{"localhost", 5432, "myapp"});
    config_mgr.add_config("log_file", FileConfig{"/var/log/app.log", false});
    config_mgr.add_config("api", NetworkConfig{"https://api.example.com", 60});
    
    config_mgr.print_config("database");
    config_mgr.print_config("log_file");
    config_mgr.print_config("api");
    config_mgr.print_config("nonexistent");
    
    // 8. JSON-like structure
    std::cout << "\n8. JSON-like Structure:" << std::endl;
    
    // Create a complex JSON-like structure
    std::map<std::string, JsonNode> person_map;
    person_map["name"] = JsonNode{std::string("Alice")};
    person_map["age"] = JsonNode{30};
    person_map["height"] = JsonNode{5.6};
    person_map["married"] = JsonNode{true};
    person_map["spouse"] = JsonNode{nullptr};
    
    std::vector<JsonNode> hobbies;
    hobbies.emplace_back(std::string("reading"));
    hobbies.emplace_back(std::string("swimming"));
    hobbies.emplace_back(std::string("coding"));
    person_map["hobbies"] = JsonNode{hobbies};
    
    JsonNode person{person_map};
    
    std::cout << "JSON-like structure:" << std::endl;
    person.print();
    std::cout << std::endl;
    
    // Access nested values
    if (person.is<std::map<std::string, JsonNode>>()) {
        const auto& person_obj = person.get<std::map<std::string, JsonNode>>();
        
        if (auto it = person_obj.find("name"); it != person_obj.end()) {
            if (it->second.is<std::string>()) {
                std::cout << "Person's name: " << it->second.get<std::string>() << std::endl;
            }
        }
        
        if (auto it = person_obj.find("age"); it != person_obj.end()) {
            if (it->second.is<int>()) {
                std::cout << "Person's age: " << it->second.get<int>() << std::endl;
            }
        }
    }
    
    // 9. Exception handling
    std::cout << "\n9. Exception Handling:" << std::endl;
    
    Value test_var = 42;
    
    try {
        // This will work
        int value = std::get<int>(test_var);
        std::cout << "Successfully got int: " << value << std::endl;
        
        // This will throw
        std::string str_value = std::get<std::string>(test_var);
        std::cout << "This won't print" << std::endl;
    } catch (const std::bad_variant_access& e) {
        std::cout << "Caught bad_variant_access: " << e.what() << std::endl;
    }
    
    // 10. Performance considerations
    std::cout << "\n10. Performance Comparison:" << std::endl;
    
    // Variant approach
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 1000000; ++i) {
        Value perf_var = (i % 2 == 0) ? Value{i} : Value{static_cast<double>(i) / 2.0};
        
        std::visit([](const auto& v) {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, int>) {
                volatile int result = v * 2;
                (void)result;
            } else if constexpr (std::is_same_v<T, double>) {
                volatile double result = v * 2.0;
                (void)result;
            }
        }, perf_var);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Variant processing time: " << duration.count() << " microseconds" << std::endl;
    
    std::cout << "\n=== STD::VARIANT BENEFITS ===" << std::endl;
    std::cout << "✅ Type-safe union - no undefined behavior" << std::endl;
    std::cout << "✅ Compile-time type checking with std::visit" << std::endl;
    std::cout << "✅ Exception safety - throws on wrong type access" << std::endl;
    std::cout << "✅ Value semantics - proper copy/move semantics" << std::endl;
    std::cout << "✅ No heap allocation for value types" << std::endl;
    std::cout << "✅ Visitor pattern support with std::visit" << std::endl;
    std::cout << "✅ Perfect for state machines and error handling" << std::endl;
    std::cout << "✅ Composable - works with STL algorithms" << std::endl;
    std::cout << "⚠️  Small overhead (discriminator + largest type size)" << std::endl;
    std::cout << "⚠️  All types must be default constructible or handle carefully" << std::endl;
    std::cout << "⚠️  Can be complex with many alternative types" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++17 -Wall -Wextra -o variant_demo variant_demo.cpp
./variant_demo

C++17 std::variant Key Features:
1. Type-safe union that can hold one of several types
2. Compile-time type checking and visitor pattern support
3. Exception-safe access with proper error handling
4. Value semantics with proper copy/move operations

Basic Usage:
std::variant<int, double, string> v = 42;    // Holds int
v = 3.14;                                    // Now holds double
v = "hello";                                 // Now holds string

Access Methods:
- std::holds_alternative<T>(v)  - Check if variant holds type T
- std::get<T>(v)                - Get value of type T (throws if wrong type)
- std::get_if<T>(&v)           - Get pointer to value if type T, nullptr otherwise
- v.index()                     - Get index of currently held type
- std::visit(visitor, v)        - Apply visitor to current value

Common Patterns:
- State machines with different state types
- Error handling (Result<T, Error> pattern)
- Configuration systems with different config types
- JSON-like data structures
- Polymorphism without inheritance
- Type-safe unions replacing C-style unions

Visitor Pattern:
- Generic lambdas: [](const auto& value) { ... }
- Type-specific: if constexpr (std::is_same_v<T, SomeType>)
- Function objects with multiple operator() overloads
- std::visit for compile-time type dispatch

Benefits over Traditional Approaches:
- Safer than C-style unions (no undefined behavior)
- Cleaner than inheritance hierarchies for simple alternatives
- Better performance than virtual dispatch
- Type-safe at compile time
- Exception safety built-in

Performance:
- Size = sizeof(largest type) + discriminator
- No heap allocation for value types
- Fast access (no virtual dispatch)
- Visitor pattern optimized by compiler

Best Practices:
- Use with std::visit for type-safe operations
- Prefer generic lambdas with if constexpr for visitors
- Consider std::get_if for safe access without exceptions
- Keep type alternatives simple and related
- Use for state machines and error handling
- Don't overuse - sometimes inheritance is clearer
*/
