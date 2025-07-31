// C++20 Formatting and Localization Module
// Demonstrates std::format, locale-aware formatting, and internationalization

export module formatting_localization;

// Import C++20 formatting and locale facilities
import <format>;
import <locale>;
import <iostream>;
import <string>;
import <vector>;
import <chrono>;
import <numbers>;
import <iomanip>;
import <sstream>;

// Export formatting utilities
export namespace FormattingUtils {
    
    // Basic formatting demonstrations
    void demonstrate_basic_formatting();
    
    // Advanced formatting with custom types
    void demonstrate_advanced_formatting();
    
    // Locale-aware formatting
    void demonstrate_locale_formatting();
    
    // Date and time formatting
    void demonstrate_datetime_formatting();
    
    // Number and currency formatting
    void demonstrate_number_formatting();
    
    // Custom formatter for user-defined types
    template<typename T>
    std::string format_container(const std::vector<T>& container, 
                                const std::string& separator = ", ");
}

// Custom class for demonstrating user-defined formatters
export class Point3D {
public:
    double x, y, z;
    
    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    // Getters for formatting
    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_z() const { return z; }
};

// Custom formatter specialization for Point3D
export template<>
struct std::formatter<Point3D> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }
    
    auto format(const Point3D& point, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "Point3D({:.2f}, {:.2f}, {:.2f})", 
                             point.get_x(), point.get_y(), point.get_z());
    }
};

// Localization utilities
export namespace LocalizationUtils {
    
    // Set up different locales
    void setup_locales();
    
    // Demonstrate currency formatting in different locales
    void demonstrate_currency_locales();
    
    // Demonstrate number formatting in different locales
    void demonstrate_number_locales();
    
    // Demonstrate date formatting in different locales
    void demonstrate_date_locales();
    
    // Multi-language message formatting
    void demonstrate_multilingual_messages();
}

// Performance comparison utilities
export namespace PerformanceUtils {
    
    // Compare std::format vs traditional methods
    void compare_formatting_performance();
    
    // Memory usage comparison
    void compare_memory_usage();
}

// Implementation section

namespace FormattingUtils {
    
    void demonstrate_basic_formatting() {
        std::cout << "\n=== BASIC C++20 FORMATTING ===" << std::endl;
        
        // Basic string formatting
        std::string name = "Alice";
        int age = 30;
        double height = 5.75;
        
        // std::format - type-safe and efficient
        std::string basic_msg = std::format("Hello, {}! You are {} years old and {:.2f} feet tall.", 
                                          name, age, height);
        std::cout << "Basic: " << basic_msg << std::endl;
        
        // Positional arguments
        std::string positional = std::format("Name: {0}, Age: {1}, Height: {2:.1f}ft", 
                                            name, age, height);
        std::cout << "Positional: " << positional << std::endl;
        
        // Named arguments (C++20 style)
        std::string formatted = std::format("Person {{ name: \"{}\", age: {}, height: {:.3f} }}", 
                                           name, age, height);
        std::cout << "JSON-like: " << formatted << std::endl;
        
        // Width and alignment
        std::cout << "\n--- Width and Alignment ---" << std::endl;
        std::cout << std::format("Left:   '{:<10}'", "text") << std::endl;
        std::cout << std::format("Right:  '{:>10}'", "text") << std::endl;
        std::cout << std::format("Center: '{:^10}'", "text") << std::endl;
        std::cout << std::format("Fill:   '{:*^10}'", "text") << std::endl;
        
        // Number formatting
        std::cout << "\n--- Number Formatting ---" << std::endl;
        int number = 42;
        std::cout << std::format("Binary:     {:b}", number) << std::endl;
        std::cout << std::format("Octal:      {:o}", number) << std::endl;
        std::cout << std::format("Hex lower:  {:x}", number) << std::endl;
        std::cout << std::format("Hex upper:  {:X}", number) << std::endl;
        std::cout << std::format("With base:  {:#x}", number) << std::endl;
        
        // Floating point formatting
        double pi = std::numbers::pi;
        std::cout << std::format("Default:    {}", pi) << std::endl;
        std::cout << std::format("Fixed:      {:.6f}", pi) << std::endl;
        std::cout << std::format("Scientific: {:.4e}", pi) << std::endl;
        std::cout << std::format("General:    {:.4g}", pi) << std::endl;
        std::cout << std::format("Percent:    {:.2%}", 0.1234) << std::endl;
    }
    
    void demonstrate_advanced_formatting() {
        std::cout << "\n=== ADVANCED FORMATTING ===" << std::endl;
        
        // Container formatting
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        std::cout << "Vector: " << format_container(numbers) << std::endl;
        std::cout << "Vector (custom): " << format_container(numbers, " | ") << std::endl;
        
        // Custom object formatting
        Point3D point(3.14159, 2.71828, 1.41421);
        std::cout << std::format("Point: {}", point) << std::endl;
        
        // Multiple points
        std::vector<Point3D> points = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}
        };
        
        std::cout << "\nPoints list:" << std::endl;
        for (size_t i = 0; i < points.size(); ++i) {
            std::cout << std::format("  Point[{}]: {}", i, points[i]) << std::endl;
        }
        
        // Conditional formatting
        std::cout << "\n--- Conditional Formatting ---" << std::endl;
        for (int score : {95, 87, 76, 65, 54}) {
            std::string grade = score >= 90 ? "A" : 
                               score >= 80 ? "B" : 
                               score >= 70 ? "C" : 
                               score >= 60 ? "D" : "F";
            
            std::cout << std::format("Score: {:3d} → Grade: {} {}", 
                                    score, grade, 
                                    score >= 70 ? "✅" : "❌") << std::endl;
        }
        
        // Table formatting
        std::cout << "\n--- Table Formatting ---" << std::endl;
        std::cout << std::format("{:^10} | {:^8} | {:^10}", "Name", "Age", "Salary") << std::endl;
        std::cout << std::format("{:-^10}-+-{:-^8}-+-{:-^10}", "", "", "") << std::endl;
        
        struct Person { std::string name; int age; double salary; };
        std::vector<Person> people = {
            {"Alice", 30, 75000.50},
            {"Bob", 25, 68000.00},
            {"Charlie", 35, 82000.75}
        };
        
        for (const auto& person : people) {
            std::cout << std::format("{:<10} | {:>8} | ${:>9.2f}", 
                                    person.name, person.age, person.salary) << std::endl;
        }
    }
    
    void demonstrate_datetime_formatting() {
        std::cout << "\n=== DATE/TIME FORMATTING ===" << std::endl;
        
        // Current time
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        
        // Basic time formatting
        std::cout << "Current time:" << std::endl;
        std::cout << std::format("  ISO format: {:%Y-%m-%d %H:%M:%S}", 
                                std::chrono::floor<std::chrono::seconds>(now)) << std::endl;
        
        // Different date formats
        std::cout << "\nDifferent formats:" << std::endl;
        auto tp = std::chrono::floor<std::chrono::seconds>(now);
        std::cout << std::format("  US format:  {:%m/%d/%Y}", tp) << std::endl;
        std::cout << std::format("  EU format:  {:%d/%m/%Y}", tp) << std::endl;
        std::cout << std::format("  Full date:  {:%A, %B %d, %Y}", tp) << std::endl;
        std::cout << std::format("  Time only:  {:%I:%M:%S %p}", tp) << std::endl;
        
        // Duration formatting
        auto duration = std::chrono::hours(25) + std::chrono::minutes(30) + std::chrono::seconds(45);
        auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration % std::chrono::hours(1));
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration % std::chrono::minutes(1));
        
        std::cout << std::format("\nDuration: {}h {}m {}s", 
                                hours.count(), minutes.count(), seconds.count()) << std::endl;
    }
    
    void demonstrate_number_formatting() {
        std::cout << "\n=== NUMBER FORMATTING ===" << std::endl;
        
        // Large numbers with separators
        long long big_number = 1234567890123LL;
        std::cout << std::format("Big number: {:L}", big_number) << std::endl;
        
        // Scientific notation
        double scientific = 0.000000123456789;
        std::cout << std::format("Scientific: {:.3e}", scientific) << std::endl;
        std::cout << std::format("Auto:       {:g}", scientific) << std::endl;
        
        // Precision control
        double precise = std::numbers::pi;
        for (int precision = 1; precision <= 6; ++precision) {
            std::cout << std::format("π with {} digits: {:.{}f}", 
                                    precision, precise, precision) << std::endl;
        }
        
        // Sign formatting
        std::vector<double> values = {42.5, -17.3, 0.0, 100.0};
        std::cout << "\nSign formatting:" << std::endl;
        for (double val : values) {
            std::cout << std::format("Value: {:+8.2f} | Space: {: 8.2f} | Default: {:8.2f}", 
                                    val, val, val) << std::endl;
        }
    }
    
    template<typename T>
    std::string format_container(const std::vector<T>& container, const std::string& separator) {
        if (container.empty()) {
            return "[]";
        }
        
        std::string result = "[";
        for (size_t i = 0; i < container.size(); ++i) {
            if constexpr (std::is_arithmetic_v<T>) {
                result += std::format("{}", container[i]);
            } else {
                result += std::format("{}", container[i]);
            }
            if (i < container.size() - 1) {
                result += separator;
            }
        }
        result += "]";
        return result;
    }
}

namespace LocalizationUtils {
    
    void demonstrate_locale_formatting() {
        std::cout << "\n=== LOCALE-AWARE FORMATTING ===" << std::endl;
        
        double amount = 1234567.89;
        
        try {
            // US locale
            std::locale us_locale("en_US.UTF-8");
            std::cout.imbue(us_locale);
            std::cout << "US Locale:" << std::endl;
            std::cout << std::format("  Number: {:.2f}", amount) << std::endl;
            
            // German locale (if available)
            try {
                std::locale de_locale("de_DE.UTF-8");
                std::cout.imbue(de_locale);
                std::cout << "German Locale:" << std::endl;
                std::cout << std::format("  Number: {:.2f}", amount) << std::endl;
            } catch (const std::runtime_error&) {
                std::cout << "German locale not available" << std::endl;
            }
            
            // French locale (if available)
            try {
                std::locale fr_locale("fr_FR.UTF-8");
                std::cout.imbue(fr_locale);
                std::cout << "French Locale:" << std::endl;
                std::cout << std::format("  Number: {:.2f}", amount) << std::endl;
            } catch (const std::runtime_error&) {
                std::cout << "French locale not available" << std::endl;
            }
            
        } catch (const std::runtime_error& e) {
            std::cout << "Locale support limited: " << e.what() << std::endl;
            std::cout << "Using default locale formatting" << std::endl;
        }
        
        // Reset to default locale
        std::cout.imbue(std::locale::classic());
    }
    
    void demonstrate_currency_locales() {
        std::cout << "\n=== CURRENCY FORMATTING ===" << std::endl;
        
        double price = 1299.99;
        
        // Different currency representations
        std::cout << std::format("USD: ${:.2f}", price) << std::endl;
        std::cout << std::format("EUR: €{:.2f}", price) << std::endl;
        std::cout << std::format("GBP: £{:.2f}", price) << std::endl;
        std::cout << std::format("JPY: ¥{:.0f}", price * 110) << std::endl;
        
        // Currency with proper formatting
        std::cout << "\nFormatted currencies:" << std::endl;
        
        struct Currency { std::string symbol; std::string code; double rate; };
        std::vector<Currency> currencies = {
            {"$", "USD", 1.0},
            {"€", "EUR", 0.85},
            {"£", "GBP", 0.73},
            {"¥", "JPY", 110.0},
            {"₹", "INR", 74.5}
        };
        
        for (const auto& curr : currencies) {
            double converted = price * curr.rate;
            if (curr.code == "JPY") {
                std::cout << std::format("{} {:>8.0f} {}", curr.symbol, converted, curr.code) << std::endl;
            } else {
                std::cout << std::format("{} {:>8.2f} {}", curr.symbol, converted, curr.code) << std::endl;
            }
        }
    }
    
    void demonstrate_multilingual_messages() {
        std::cout << "\n=== MULTILINGUAL MESSAGES ===" << std::endl;
        
        std::string username = "Alice";
        int messages = 5;
        
        // Different language greetings
        struct Greeting {
            std::string language;
            std::string hello;
            std::string messages_fmt;
        };
        
        std::vector<Greeting> greetings = {
            {"English", "Hello", "You have {} new message{}"},
            {"Spanish", "Hola", "Tienes {} mensaje{} nuevo{}"},
            {"French", "Bonjour", "Vous avez {} nouveau{} message{}"},
            {"German", "Hallo", "Sie haben {} neue{} Nachricht{}"},
            {"Japanese", "こんにちは", "{}件の新しいメッセージがあります"}
        };
        
        for (const auto& greeting : greetings) {
            std::cout << std::format("{} ({}):", greeting.language, greeting.hello) << std::endl;
            
            if (greeting.language == "Japanese") {
                std::cout << std::format("  {}, {}!", 
                                        greeting.hello, username) << std::endl;
                std::cout << std::format("  {}", 
                                        std::format(greeting.messages_fmt, messages)) << std::endl;
            } else {
                // Handle pluralization for Western languages
                std::string plural_suffix = (messages == 1) ? "" : "s";
                std::string spanish_plural = (messages == 1) ? "" : "s";
                
                std::cout << std::format("  {}, {}!", 
                                        greeting.hello, username) << std::endl;
                
                if (greeting.language == "Spanish") {
                    std::cout << std::format("  {}", 
                                            std::format(greeting.messages_fmt, 
                                                      messages, spanish_plural, spanish_plural)) << std::endl;
                } else if (greeting.language == "French") {
                    std::string fr_plural = (messages == 1) ? "" : "x";
                    std::string fr_msg_plural = (messages == 1) ? "" : "s";
                    std::cout << std::format("  {}", 
                                            std::format(greeting.messages_fmt, 
                                                      messages, fr_plural, fr_msg_plural)) << std::endl;
                } else if (greeting.language == "German") {
                    std::string de_plural = (messages == 1) ? "" : "n";
                    std::string de_msg_plural = (messages == 1) ? "" : "en";
                    std::cout << std::format("  {}", 
                                            std::format(greeting.messages_fmt, 
                                                      messages, de_plural, de_msg_plural)) << std::endl;
                } else {
                    std::cout << std::format("  {}", 
                                            std::format(greeting.messages_fmt, 
                                                      messages, plural_suffix)) << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }
}

namespace PerformanceUtils {
    
    void compare_formatting_performance() {
        std::cout << "\n=== PERFORMANCE COMPARISON ===" << std::endl;
        
        const int iterations = 100000;
        std::string name = "Performance Test";
        int value = 12345;
        double decimal = 67.89;
        
        // Time std::format
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            volatile auto result = std::format("Name: {}, Value: {}, Decimal: {:.2f}", 
                                             name, value, decimal);
        }
        auto format_time = std::chrono::high_resolution_clock::now() - start;
        
        // Time stringstream (traditional method)
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            std::stringstream ss;
            ss << "Name: " << name << ", Value: " << value 
               << ", Decimal: " << std::fixed << std::setprecision(2) << decimal;
            volatile auto result = ss.str();
        }
        auto stream_time = std::chrono::high_resolution_clock::now() - start;
        
        auto format_ms = std::chrono::duration_cast<std::chrono::milliseconds>(format_time).count();
        auto stream_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stream_time).count();
        
        std::cout << std::format("std::format time:  {:>6} ms", format_ms) << std::endl;
        std::cout << std::format("stringstream time: {:>6} ms", stream_ms) << std::endl;
        
        if (format_ms < stream_ms) {
            double speedup = static_cast<double>(stream_ms) / format_ms;
            std::cout << std::format("std::format is {:.1f}x faster! 🚀", speedup) << std::endl;
        } else if (stream_ms < format_ms) {
            double speedup = static_cast<double>(format_ms) / stream_ms;
            std::cout << std::format("stringstream is {:.1f}x faster", speedup) << std::endl;
        } else {
            std::cout << "Performance is roughly equal" << std::endl;
        }
        
        std::cout << "\n✅ std::format benefits:" << std::endl;
        std::cout << "  • Type safety at compile time" << std::endl;
        std::cout << "  • Cleaner, more readable syntax" << std::endl;
        std::cout << "  • Better performance in most cases" << std::endl;
        std::cout << "  • No manual precision/formatting setup" << std::endl;
    }
}
