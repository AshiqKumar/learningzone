// C++20 Formatting and Localization Demo
import formatting_localization;
import <iostream>;
import <locale>;
import <thread>;
import <chrono>;

int main() {
    std::cout << "=== C++20 FORMATTING & LOCALIZATION DEMO ===" << std::endl;
    std::cout << "Demonstrating std::format, custom formatters, and locale support\n" << std::endl;
    
    try {
        // Set up UTF-8 locale if possible
        try {
            std::locale::global(std::locale(""));
        } catch (...) {
            std::cout << "Note: Using default locale (UTF-8 may not be fully supported)\n" << std::endl;
        }
        
        // 1. Basic Formatting Features
        FormattingUtils::demonstrate_basic_formatting();
        
        // 2. Advanced Formatting with Custom Types
        FormattingUtils::demonstrate_advanced_formatting();
        
        // 3. Date and Time Formatting
        FormattingUtils::demonstrate_datetime_formatting();
        
        // 4. Number Formatting
        FormattingUtils::demonstrate_number_formatting();
        
        // 5. Locale-Aware Formatting
        LocalizationUtils::demonstrate_locale_formatting();
        
        // 6. Currency Formatting in Different Locales
        LocalizationUtils::demonstrate_currency_locales();
        
        // 7. Multilingual Message Formatting
        LocalizationUtils::demonstrate_multilingual_messages();
        
        // 8. Performance Comparison
        PerformanceUtils::compare_formatting_performance();
        
        // 9. Real-world Examples
        std::cout << "\n=== REAL-WORLD EXAMPLES ===" << std::endl;
        
        // Log message formatting
        std::cout << "\n--- Log Message Formatting ---" << std::endl;
        auto now = std::chrono::system_clock::now();
        std::string log_level = "INFO";
        std::string component = "AuthService";
        std::string message = "User login successful";
        std::string user_id = "alice@example.com";
        
        std::string log_entry = std::format("[{:%Y-%m-%d %H:%M:%S}] {} [{}] {} (user: {})",
                                           std::chrono::floor<std::chrono::seconds>(now),
                                           log_level, component, message, user_id);
        std::cout << "Log: " << log_entry << std::endl;
        
        // Configuration file formatting
        std::cout << "\n--- Configuration Display ---" << std::endl;
        struct Config {
            std::string database_url;
            int max_connections;
            double timeout_seconds;
            bool debug_mode;
        };
        
        Config config{"postgresql://localhost:5432/mydb", 100, 30.5, true};
        
        std::cout << "Configuration:" << std::endl;
        std::cout << std::format("  Database URL:     {}", config.database_url) << std::endl;
        std::cout << std::format("  Max Connections:  {:>3}", config.max_connections) << std::endl;
        std::cout << std::format("  Timeout:          {:.1f}s", config.timeout_seconds) << std::endl;
        std::cout << std::format("  Debug Mode:       {}", config.debug_mode ? "ON" : "OFF") << std::endl;
        
        // Error message formatting
        std::cout << "\n--- Error Message Formatting ---" << std::endl;
        int error_code = 404;
        std::string endpoint = "/api/users/12345";
        std::string method = "GET";
        
        std::string error_msg = std::format("❌ HTTP {} Error: {} {} - Resource not found", 
                                          error_code, method, endpoint);
        std::cout << error_msg << std::endl;
        
        // Progress reporting
        std::cout << "\n--- Progress Reporting ---" << std::endl;
        for (int progress = 0; progress <= 100; progress += 20) {
            int bars = progress / 5;  // 20 bars total
            std::string progress_bar = std::string(bars, '█') + std::string(20 - bars, '░');
            std::cout << std::format("\rProgress: [{}] {:3}%", progress_bar, progress);
            std::cout.flush();
            
            if (progress < 100) {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
        std::cout << " ✅ Complete!" << std::endl;
        
        // Data validation formatting
        std::cout << "\n--- Data Validation Results ---" << std::endl;
        struct ValidationResult {
            std::string field;
            bool valid;
            std::string message;
        };
        
        std::vector<ValidationResult> validations = {
            {"email", true, "Valid email format"},
            {"password", false, "Password too short (min 8 characters)"},
            {"age", true, "Valid age range"},
            {"phone", false, "Invalid phone number format"}
        };
        
        std::cout << std::format("{:<12} | {:<6} | {}", "Field", "Status", "Message") << std::endl;
        std::cout << std::format("{:-<12}-+-{:-<6}-+-{:-<35}", "", "", "") << std::endl;
        
        for (const auto& result : validations) {
            std::string status = result.valid ? "✅ PASS" : "❌ FAIL";
            std::cout << std::format("{:<12} | {:<6} | {}", 
                                    result.field, status, result.message) << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== C++20 FORMATTING FEATURES SUMMARY ===" << std::endl;
    std::cout << "✅ std::format - Type-safe string formatting" << std::endl;
    std::cout << "✅ Custom formatters for user-defined types" << std::endl;
    std::cout << "✅ Positional and named argument support" << std::endl;
    std::cout << "✅ Width, alignment, and fill character control" << std::endl;
    std::cout << "✅ Number base formatting (binary, octal, hex)" << std::endl;
    std::cout << "✅ Floating-point precision and notation control" << std::endl;
    std::cout << "✅ Date and time formatting with chrono" << std::endl;
    std::cout << "✅ Locale-aware number and currency formatting" << std::endl;
    std::cout << "✅ Multilingual message support" << std::endl;
    std::cout << "✅ Performance improvements over traditional methods" << std::endl;
    std::cout << "✅ Clean, readable syntax for complex formatting" << std::endl;
    
    std::cout << "\n🌐 LOCALIZATION BENEFITS:" << std::endl;
    std::cout << "• Automatic number formatting per locale" << std::endl;
    std::cout << "• Currency symbol and placement handling" << std::endl;
    std::cout << "• Date/time format customization" << std::endl;
    std::cout << "• Character encoding support (UTF-8)" << std::endl;
    std::cout << "• Pluralization rule handling" << std::endl;
    std::cout << "• Right-to-left text support (when available)" << std::endl;
    
    return 0;
}

/*
COMPILE AND RUN:

This example demonstrates C++20 std::format and localization features:

Features Demonstrated:
1. **Basic Formatting**: Type-safe string formatting with std::format
2. **Advanced Formatting**: Custom formatters for user-defined types
3. **Width & Alignment**: Left, right, center alignment with fill characters
4. **Number Formatting**: Binary, octal, hex, scientific notation
5. **Date/Time Formatting**: Chrono integration with format strings
6. **Locale Support**: Number and currency formatting per locale
7. **Multilingual**: Different language message formatting
8. **Performance**: Comparison with traditional stringstream methods
9. **Real-world Examples**: Logging, config display, error messages, progress bars

Windows (MSVC):
    cl /EHsc /std:c++20 /experimental:module formatting_localization.cppm /c
    cl /EHsc /std:c++20 formatting_localization.obj demo_formatting.cpp /Fe:formatting_demo.exe
    formatting_demo.exe

Linux/macOS (GCC 11+):
    g++ -std=c++20 -fmodules-ts -c formatting_localization.cppm
    g++ -std=c++20 -fmodules-ts -o formatting_demo demo_formatting.cpp
    ./formatting_demo

Linux/macOS (Clang 15+):
    clang++ -std=c++20 --precompile formatting_localization.cppm -o formatting_localization.pcm
    clang++ -std=c++20 -fprebuilt-module-path=. -o formatting_demo demo_formatting.cpp
    ./formatting_demo

Note: std::format support varies by compiler:
- MSVC 2019 16.10+: Full support
- GCC 13+: Full support
- Clang 14+: Partial support (improving)
- Some features may require linking with specific libraries

For full locale support, ensure your system has the required locale packages installed.
*/
