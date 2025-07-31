// C++17 Inline Variables - Header-Only Static Variables
// Compile: g++ -std=c++17 -o inline_variables_demo inline_variables_demo.cpp
// Run: ./inline_variables_demo

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

// 1. Basic inline variables
inline int global_counter = 0;
inline std::string app_name = "C++17 Demo";
inline const double pi = 3.14159265358979323846;

// 2. Complex inline variables
inline std::vector<std::string> default_colors = {
    "red", "green", "blue", "yellow", "magenta", "cyan"
};

inline std::map<std::string, int> error_codes = {
    {"SUCCESS", 0},
    {"ERROR_FILE_NOT_FOUND", 404},
    {"ERROR_ACCESS_DENIED", 403},
    {"ERROR_INTERNAL", 500}
};

// 3. Inline variables in namespace
namespace config {
    inline std::string database_url = "localhost:5432";
    inline int max_connections = 100;
    inline bool debug_mode = true;
    inline std::chrono::seconds timeout{30};
}

// 4. Class with inline static members
class Logger {
public:
    // C++17: inline static variables can be initialized in class
    inline static std::string log_level = "INFO";
    inline static int max_log_files = 5;
    inline static bool console_output = true;
    
    // Complex inline static members
    inline static std::vector<std::string> log_categories = {
        "DEBUG", "INFO", "WARNING", "ERROR", "FATAL"
    };
    
    static void log(const std::string& message) {
        if (console_output) {
            std::cout << "[" << log_level << "] " << message << std::endl;
        }
    }
    
    static void configure(const std::string& level, bool console = true) {
        log_level = level;
        console_output = console;
    }
};

// 5. Template class with inline static variables
template<typename T>
class Counter {
public:
    inline static T count = T{};
    inline static std::string type_name = typeid(T).name();
    
    static void increment() { ++count; }
    static void reset() { count = T{}; }
    static T get() { return count; }
    
    static void print_info() {
        std::cout << "Counter<" << type_name << "> = " << count << std::endl;
    }
};

// 6. Inline variables with custom types
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

inline Point origin{0.0, 0.0};
inline Point default_scale{1.0, 1.0};

// 7. Inline constexpr variables
inline constexpr int max_array_size = 1000;
inline constexpr double golden_ratio = 1.618033988749895;
inline constexpr const char* version = "1.0.0";

// Template inline constexpr variables
template<typename T>
inline constexpr T max_value = std::numeric_limits<T>::max();

template<typename T>
inline constexpr bool is_numeric = std::is_arithmetic_v<T>;

// 8. Inline variables for configuration
namespace graphics {
    inline int screen_width = 1920;
    inline int screen_height = 1080;
    inline bool fullscreen = false;
    inline std::string renderer = "OpenGL";
    
    inline std::map<std::string, std::pair<int, int>> resolutions = {
        {"720p", {1280, 720}},
        {"1080p", {1920, 1080}},
        {"1440p", {2560, 1440}},
        {"4K", {3840, 2160}}
    };
}

// 9. Registry pattern with inline variables
class ServiceRegistry {
private:
    inline static std::map<std::string, void*> services;
    
public:
    template<typename T>
    static void register_service(const std::string& name, T* service) {
        services[name] = static_cast<void*>(service);
    }
    
    template<typename T>
    static T* get_service(const std::string& name) {
        auto it = services.find(name);
        return (it != services.end()) ? static_cast<T*>(it->second) : nullptr;
    }
    
    static void list_services() {
        std::cout << "Registered services:" << std::endl;
        for (const auto& [name, ptr] : services) {
            std::cout << "  " << name << " -> " << ptr << std::endl;
        }
    }
};

// 10. Comparison with C++11/14 approach
namespace old_style {
    // C++11/14: Header-only static variables required external definition
    // This would be in header:
    // extern const std::string app_version;
    // extern std::vector<int> default_values;
    
    // And in source file:
    // const std::string app_version = "1.0.0";
    // std::vector<int> default_values = {1, 2, 3, 4, 5};
    
    // Or using functions to avoid ODR issues:
    const std::string& get_app_version() {
        static const std::string version = "1.0.0";
        return version;
    }
    
    std::vector<int>& get_default_values() {
        static std::vector<int> values = {1, 2, 3, 4, 5};
        return values;
    }
}

// 11. Performance testing utilities
namespace perf {
    inline std::chrono::high_resolution_clock::time_point start_time;
    inline std::vector<std::pair<std::string, std::chrono::microseconds>> measurements;
    
    void start_timer() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
    void end_timer(const std::string& operation) {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        measurements.emplace_back(operation, duration);
    }
    
    void print_results() {
        std::cout << "Performance measurements:" << std::endl;
        for (const auto& [op, time] : measurements) {
            std::cout << "  " << op << ": " << time.count() << " microseconds" << std::endl;
        }
        measurements.clear();
    }
}

int main() {
    std::cout << "=== C++17 INLINE VARIABLES DEMO ===" << std::endl;
    
    // 1. Basic inline variables usage
    std::cout << "\n1. Basic Inline Variables:" << std::endl;
    
    std::cout << "Global counter: " << global_counter << std::endl;
    std::cout << "App name: " << app_name << std::endl;
    std::cout << "Pi value: " << pi << std::endl;
    
    // Modify global variables
    global_counter = 42;
    app_name = "Modified App";
    
    std::cout << "After modification:" << std::endl;
    std::cout << "Global counter: " << global_counter << std::endl;
    std::cout << "App name: " << app_name << std::endl;
    
    // 2. Complex inline variables
    std::cout << "\n2. Complex Inline Variables:" << std::endl;
    
    std::cout << "Default colors: ";
    for (const auto& color : default_colors) {
        std::cout << color << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Error codes:" << std::endl;
    for (const auto& [name, code] : error_codes) {
        std::cout << "  " << name << " = " << code << std::endl;
    }
    
    // 3. Namespace inline variables
    std::cout << "\n3. Namespace Configuration:" << std::endl;
    
    std::cout << "Database URL: " << config::database_url << std::endl;
    std::cout << "Max connections: " << config::max_connections << std::endl;
    std::cout << "Debug mode: " << std::boolalpha << config::debug_mode << std::endl;
    std::cout << "Timeout: " << config::timeout.count() << " seconds" << std::endl;
    
    // Modify configuration
    config::debug_mode = false;
    config::max_connections = 200;
    
    std::cout << "After configuration change:" << std::endl;
    std::cout << "Debug mode: " << config::debug_mode << std::endl;
    std::cout << "Max connections: " << config::max_connections << std::endl;
    
    // 4. Class inline static members
    std::cout << "\n4. Class Inline Static Members:" << std::endl;
    
    Logger::log("Application started");
    Logger::log("Processing data...");
    
    std::cout << "Current log level: " << Logger::log_level << std::endl;
    std::cout << "Max log files: " << Logger::max_log_files << std::endl;
    std::cout << "Console output: " << Logger::console_output << std::endl;
    
    std::cout << "Available log categories: ";
    for (const auto& category : Logger::log_categories) {
        std::cout << category << " ";
    }
    std::cout << std::endl;
    
    // Change logger configuration
    Logger::configure("DEBUG", true);
    Logger::log("Debug message");
    
    // 5. Template class inline static variables
    std::cout << "\n5. Template Class Inline Static Variables:" << std::endl;
    
    Counter<int>::increment();
    Counter<int>::increment();
    Counter<int>::increment();
    Counter<int>::print_info();
    
    Counter<double>::increment();
    Counter<double>::increment();
    Counter<double>::print_info();
    
    Counter<std::string>::print_info();  // Default initialized
    
    std::cout << "Int counter value: " << Counter<int>::get() << std::endl;
    std::cout << "Double counter value: " << Counter<double>::get() << std::endl;
    
    // Reset counters
    Counter<int>::reset();
    Counter<double>::reset();
    
    std::cout << "After reset:" << std::endl;
    Counter<int>::print_info();
    Counter<double>::print_info();
    
    // 6. Custom type inline variables
    std::cout << "\n6. Custom Type Inline Variables:" << std::endl;
    
    std::cout << "Origin point: (" << origin.x << ", " << origin.y << ")" << std::endl;
    std::cout << "Default scale: (" << default_scale.x << ", " << default_scale.y << ")" << std::endl;
    
    // Modify custom objects
    origin.x = 10.0;
    origin.y = 20.0;
    
    std::cout << "Modified origin: (" << origin.x << ", " << origin.y << ")" << std::endl;
    
    // 7. Inline constexpr variables
    std::cout << "\n7. Inline Constexpr Variables:" << std::endl;
    
    std::cout << "Max array size: " << max_array_size << std::endl;
    std::cout << "Golden ratio: " << golden_ratio << std::endl;
    std::cout << "Version: " << version << std::endl;
    
    // Template constexpr variables
    std::cout << "Max int: " << max_value<int> << std::endl;
    std::cout << "Max double: " << max_value<double> << std::endl;
    std::cout << "Is int numeric: " << is_numeric<int> << std::endl;
    std::cout << "Is string numeric: " << is_numeric<std::string> << std::endl;
    
    // 8. Graphics configuration
    std::cout << "\n8. Graphics Configuration:" << std::endl;
    
    std::cout << "Screen resolution: " << graphics::screen_width << "x" << graphics::screen_height << std::endl;
    std::cout << "Fullscreen: " << graphics::fullscreen << std::endl;
    std::cout << "Renderer: " << graphics::renderer << std::endl;
    
    std::cout << "Available resolutions:" << std::endl;
    for (const auto& [name, resolution] : graphics::resolutions) {
        std::cout << "  " << name << ": " << resolution.first << "x" << resolution.second << std::endl;
    }
    
    // Change graphics settings
    auto [width, height] = graphics::resolutions["1440p"];
    graphics::screen_width = width;
    graphics::screen_height = height;
    graphics::fullscreen = true;
    
    std::cout << "After changing to 1440p fullscreen:" << std::endl;
    std::cout << "Screen resolution: " << graphics::screen_width << "x" << graphics::screen_height << std::endl;
    std::cout << "Fullscreen: " << graphics::fullscreen << std::endl;
    
    // 9. Service registry example
    std::cout << "\n9. Service Registry with Inline Variables:" << std::endl;
    
    // Register some dummy services
    int database_service = 100;
    std::string file_service = "FileSystem";
    double math_service = 3.14159;
    
    ServiceRegistry::register_service("database", &database_service);
    ServiceRegistry::register_service("filesystem", &file_service);
    ServiceRegistry::register_service("math", &math_service);
    
    ServiceRegistry::list_services();
    
    // Retrieve services
    auto* db = ServiceRegistry::get_service<int>("database");
    auto* fs = ServiceRegistry::get_service<std::string>("filesystem");
    
    if (db) std::cout << "Database service value: " << *db << std::endl;
    if (fs) std::cout << "Filesystem service value: " << *fs << std::endl;
    
    // 10. Performance comparison
    std::cout << "\n10. Performance Comparison:" << std::endl;
    
    // Test inline variable access
    perf::start_timer();
    volatile int sum = 0;
    for (int i = 0; i < 1000000; ++i) {
        sum += global_counter;
    }
    perf::end_timer("Inline variable access");
    
    // Test function-based access (old style)
    perf::start_timer();
    sum = 0;
    for (int i = 0; i < 1000000; ++i) {
        sum += old_style::get_app_version().length();
    }
    perf::end_timer("Function-based access");
    
    perf::print_results();
    
    // 11. Header-only library benefits
    std::cout << "\n11. Header-Only Library Benefits:" << std::endl;
    
    std::cout << "Inline variables enable true header-only libraries:" << std::endl;
    std::cout << "✅ No separate .cpp files needed for static variables" << std::endl;
    std::cout << "✅ No ODR (One Definition Rule) violations" << std::endl;
    std::cout << "✅ Easy distribution and inclusion" << std::endl;
    std::cout << "✅ Template libraries can have static data" << std::endl;
    
    // 12. Thread safety considerations
    std::cout << "\n12. Thread Safety Notes:" << std::endl;
    
    std::cout << "Inline variables are not automatically thread-safe:" << std::endl;
    std::cout << "⚠️  Multiple threads modifying inline variables need synchronization" << std::endl;
    std::cout << "⚠️  const/constexpr inline variables are naturally thread-safe" << std::endl;
    std::cout << "⚠️  Consider std::atomic for thread-safe counters" << std::endl;
    
    // 13. Best practices demonstration
    std::cout << "\n13. Best Practices:" << std::endl;
    
    // Good: const/constexpr for immutable data
    inline static const std::string good_practice_1 = "immutable config";
    inline static constexpr int good_practice_2 = 42;
    
    // Good: namespace for grouping related variables
    namespace good_practices {
        inline int setting1 = 100;
        inline bool setting2 = true;
        inline std::string setting3 = "default";
    }
    
    std::cout << "Good practice examples:" << std::endl;
    std::cout << "  Immutable config: " << good_practice_1 << std::endl;
    std::cout << "  Constexpr value: " << good_practice_2 << std::endl;
    std::cout << "  Grouped settings: " << good_practices::setting1 
              << ", " << good_practices::setting2 
              << ", " << good_practices::setting3 << std::endl;
    
    std::cout << "\n=== INLINE VARIABLES BENEFITS ===" << std::endl;
    std::cout << "✅ True header-only libraries with static data" << std::endl;
    std::cout << "✅ No ODR violations - one definition per translation unit" << std::endl;
    std::cout << "✅ Cleaner than function-based static variable access" << std::endl;
    std::cout << "✅ Perfect for configuration and registry patterns" << std::endl;
    std::cout << "✅ Template class static members can be defined inline" << std::endl;
    std::cout << "✅ Consistent with inline functions - same linkage rules" << std::endl;
    std::cout << "✅ No performance overhead compared to regular static variables" << std::endl;
    std::cout << "⚠️  Not automatically thread-safe (like regular static variables)" << std::endl;
    std::cout << "⚠️  Still subject to static initialization order issues" << std::endl;
    std::cout << "⚠️  Can increase binary size if used excessively" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++17 -Wall -Wextra -o inline_variables_demo inline_variables_demo.cpp
./inline_variables_demo

C++17 Inline Variables Key Features:
1. Static variables can be defined inline in headers
2. Eliminates ODR (One Definition Rule) violations
3. Enables true header-only libraries with static data
4. Works with template class static members

Before C++17 (Header-only problems):
// header.h
extern const std::string config;  // Declaration
// source.cpp
const std::string config = "value";  // Definition (required)

C++17 Inline Variables:
// header.h
inline const std::string config = "value";  // Definition in header!

Syntax:
inline int variable = value;                    // Basic inline variable
inline static int Class::member = value;       // Class static member
inline constexpr double pi = 3.14159;         // Constexpr inline

Benefits:
- Header-only libraries with static data
- No ODR violations
- Template class static members work properly
- Cleaner than function-based access patterns
- Same performance as regular static variables

Use Cases:
- Configuration systems
- Registry patterns
- Mathematical constants
- Default values and settings
- Template class static data
- Header-only library development

Best Practices:
- Use const/constexpr for immutable data
- Group related variables in namespaces
- Consider thread safety for mutable variables
- Prefer over function-based static access
- Document initialization dependencies
*/
