// C++17 std::string_view - Non-owning String Reference
// Compile: g++ -std=c++17 -o string_view_demo string_view_demo.cpp
// Run: ./string_view_demo

#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <map>
#include <sstream>

// 1. String processing functions using string_view
bool starts_with(std::string_view str, std::string_view prefix) {
    return str.size() >= prefix.size() && 
           str.substr(0, prefix.size()) == prefix;
}

bool ends_with(std::string_view str, std::string_view suffix) {
    return str.size() >= suffix.size() && 
           str.substr(str.size() - suffix.size()) == suffix;
}

bool contains(std::string_view str, std::string_view substring) {
    return str.find(substring) != std::string_view::npos;
}

std::string_view trim_left(std::string_view str) {
    auto start = str.find_first_not_of(" \t\n\r");
    return (start == std::string_view::npos) ? "" : str.substr(start);
}

std::string_view trim_right(std::string_view str) {
    auto end = str.find_last_not_of(" \t\n\r");
    return (end == std::string_view::npos) ? "" : str.substr(0, end + 1);
}

std::string_view trim(std::string_view str) {
    return trim_left(trim_right(str));
}

// 2. Tokenization using string_view
std::vector<std::string_view> split(std::string_view str, char delimiter) {
    std::vector<std::string_view> tokens;
    
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string_view::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    
    // Add the last token
    tokens.push_back(str.substr(start));
    
    return tokens;
}

std::vector<std::string_view> split_whitespace(std::string_view str) {
    std::vector<std::string_view> tokens;
    
    size_t start = 0;
    while (start < str.length()) {
        // Skip whitespace
        while (start < str.length() && std::isspace(str[start])) {
            start++;
        }
        
        if (start >= str.length()) break;
        
        // Find end of token
        size_t end = start;
        while (end < str.length() && !std::isspace(str[end])) {
            end++;
        }
        
        tokens.push_back(str.substr(start, end - start));
        start = end;
    }
    
    return tokens;
}

// 3. Configuration parser using string_view
class SimpleConfigParser {
private:
    std::map<std::string, std::string> config;
    
    std::string_view trim_quotes(std::string_view str) {
        if (str.size() >= 2 && str.front() == '"' && str.back() == '"') {
            return str.substr(1, str.size() - 2);
        }
        return str;
    }
    
public:
    void parse_line(std::string_view line) {
        // Remove comments
        auto comment_pos = line.find('#');
        if (comment_pos != std::string_view::npos) {
            line = line.substr(0, comment_pos);
        }
        
        // Trim whitespace
        line = trim(line);
        
        if (line.empty()) return;
        
        // Find key-value separator
        auto eq_pos = line.find('=');
        if (eq_pos == std::string_view::npos) return;
        
        auto key = trim(line.substr(0, eq_pos));
        auto value = trim(line.substr(eq_pos + 1));
        
        // Remove quotes from value
        value = trim_quotes(value);
        
        config[std::string(key)] = std::string(value);
    }
    
    void parse_config(std::string_view config_text) {
        size_t start = 0;
        while (start < config_text.length()) {
            auto end = config_text.find('\n', start);
            if (end == std::string_view::npos) {
                end = config_text.length();
            }
            
            parse_line(config_text.substr(start, end - start));
            start = end + 1;
        }
    }
    
    std::string get(const std::string& key, const std::string& default_value = "") const {
        auto it = config.find(key);
        return (it != config.end()) ? it->second : default_value;
    }
    
    void print_config() const {
        std::cout << "Configuration:" << std::endl;
        for (const auto& [key, value] : config) {
            std::cout << "  " << key << " = " << value << std::endl;
        }
    }
};

// 4. Log parser using string_view
struct LogEntry {
    std::string_view timestamp;
    std::string_view level;
    std::string_view message;
    
    void print() const {
        std::cout << "[" << timestamp << "] " << level << ": " << message << std::endl;
    }
};

class LogParser {
public:
    static LogEntry parse_line(std::string_view line) {
        LogEntry entry;
        
        // Expected format: [timestamp] LEVEL: message
        if (line.empty() || line[0] != '[') {
            return entry;  // Invalid format
        }
        
        // Find timestamp
        auto timestamp_end = line.find(']');
        if (timestamp_end == std::string_view::npos) {
            return entry;
        }
        
        entry.timestamp = line.substr(1, timestamp_end - 1);
        
        // Skip "] "
        auto rest = line.substr(timestamp_end + 1);
        rest = trim_left(rest);
        
        // Find level
        auto colon_pos = rest.find(':');
        if (colon_pos == std::string_view::npos) {
            return entry;
        }
        
        entry.level = trim(rest.substr(0, colon_pos));
        entry.message = trim(rest.substr(colon_pos + 1));
        
        return entry;
    }
    
    static std::vector<LogEntry> parse_log(std::string_view log_text) {
        std::vector<LogEntry> entries;
        
        size_t start = 0;
        while (start < log_text.length()) {
            auto end = log_text.find('\n', start);
            if (end == std::string_view::npos) {
                end = log_text.length();
            }
            
            auto entry = parse_line(log_text.substr(start, end - start));
            if (!entry.timestamp.empty()) {  // Valid entry
                entries.push_back(entry);
            }
            
            start = end + 1;
        }
        
        return entries;
    }
    
    static void filter_by_level(const std::vector<LogEntry>& entries, std::string_view level) {
        std::cout << "Entries with level '" << level << "':" << std::endl;
        for (const auto& entry : entries) {
            if (entry.level == level) {
                entry.print();
            }
        }
    }
};

// 5. Command line argument parser
class CommandLineParser {
private:
    std::map<std::string, std::string> options;
    std::vector<std::string> positional_args;
    
public:
    void parse(int argc, char* argv[]) {
        for (int i = 1; i < argc; ++i) {
            std::string_view arg = argv[i];
            
            if (starts_with(arg, "--")) {
                // Long option: --key=value or --key value
                auto key_value = arg.substr(2);
                auto eq_pos = key_value.find('=');
                
                if (eq_pos != std::string_view::npos) {
                    // --key=value format
                    auto key = key_value.substr(0, eq_pos);
                    auto value = key_value.substr(eq_pos + 1);
                    options[std::string(key)] = std::string(value);
                } else {
                    // --key value format
                    std::string key(key_value);
                    if (i + 1 < argc && !starts_with(argv[i + 1], "-")) {
                        options[key] = argv[i + 1];
                        ++i;  // Skip the next argument
                    } else {
                        options[key] = "true";  // Flag option
                    }
                }
            } else if (starts_with(arg, "-") && arg.length() > 1) {
                // Short option: -k value or -k
                auto key = arg.substr(1);
                if (i + 1 < argc && !starts_with(argv[i + 1], "-")) {
                    options[std::string(key)] = argv[i + 1];
                    ++i;
                } else {
                    options[std::string(key)] = "true";
                }
            } else {
                // Positional argument
                positional_args.emplace_back(arg);
            }
        }
    }
    
    std::string get_option(const std::string& key, const std::string& default_value = "") const {
        auto it = options.find(key);
        return (it != options.end()) ? it->second : default_value;
    }
    
    bool has_option(const std::string& key) const {
        return options.find(key) != options.end();
    }
    
    const std::vector<std::string>& get_positional_args() const {
        return positional_args;
    }
    
    void print_parsed() const {
        std::cout << "Options:" << std::endl;
        for (const auto& [key, value] : options) {
            std::cout << "  --" << key << " = " << value << std::endl;
        }
        
        std::cout << "Positional arguments:" << std::endl;
        for (const auto& arg : positional_args) {
            std::cout << "  " << arg << std::endl;
        }
    }
};

// 6. Performance comparison helpers
void process_string_copy(const std::string& str) {
    // Simulate string processing with copying
    auto upper_str = str;
    std::transform(upper_str.begin(), upper_str.end(), upper_str.begin(), ::toupper);
    volatile auto len = upper_str.length();  // Prevent optimization
    (void)len;
}

void process_string_view(std::string_view str) {
    // Simulate string processing without copying
    for (char c : str) {
        volatile char upper_c = std::toupper(c);  // Prevent optimization
        (void)upper_c;
    }
}

// Traditional C-style string processing
void process_c_string(const char* str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
        volatile char upper_c = std::toupper(str[i]);
        (void)upper_c;
    }
}

// 7. URL parser using string_view
struct URL {
    std::string_view scheme;
    std::string_view host;
    std::string_view port;
    std::string_view path;
    std::string_view query;
    std::string_view fragment;
    
    void print() const {
        std::cout << "URL Components:" << std::endl;
        std::cout << "  Scheme: " << (scheme.empty() ? "(none)" : scheme) << std::endl;
        std::cout << "  Host: " << (host.empty() ? "(none)" : host) << std::endl;
        std::cout << "  Port: " << (port.empty() ? "(none)" : port) << std::endl;
        std::cout << "  Path: " << (path.empty() ? "(none)" : path) << std::endl;
        std::cout << "  Query: " << (query.empty() ? "(none)" : query) << std::endl;
        std::cout << "  Fragment: " << (fragment.empty() ? "(none)" : fragment) << std::endl;
    }
};

class URLParser {
public:
    static URL parse(std::string_view url) {
        URL result;
        std::string_view remaining = url;
        
        // Extract fragment (#fragment)
        auto fragment_pos = remaining.find('#');
        if (fragment_pos != std::string_view::npos) {
            result.fragment = remaining.substr(fragment_pos + 1);
            remaining = remaining.substr(0, fragment_pos);
        }
        
        // Extract query (?query)
        auto query_pos = remaining.find('?');
        if (query_pos != std::string_view::npos) {
            result.query = remaining.substr(query_pos + 1);
            remaining = remaining.substr(0, query_pos);
        }
        
        // Extract scheme (scheme://)
        auto scheme_pos = remaining.find("://");
        if (scheme_pos != std::string_view::npos) {
            result.scheme = remaining.substr(0, scheme_pos);
            remaining = remaining.substr(scheme_pos + 3);
        }
        
        // Extract path (everything after first /)
        auto path_pos = remaining.find('/');
        if (path_pos != std::string_view::npos) {
            result.path = remaining.substr(path_pos);
            remaining = remaining.substr(0, path_pos);
        }
        
        // Extract port (:port)
        auto port_pos = remaining.find(':');
        if (port_pos != std::string_view::npos) {
            result.port = remaining.substr(port_pos + 1);
            remaining = remaining.substr(0, port_pos);
        }
        
        // Remaining is host
        result.host = remaining;
        
        return result;
    }
};

int main() {
    std::cout << "=== C++17 STD::STRING_VIEW DEMO ===" << std::endl;
    
    // 1. Basic string_view usage
    std::cout << "\n1. Basic String_View Usage:" << std::endl;
    
    // Creating string_views from different sources
    const char* c_string = "Hello, World!";
    std::string std_string = "C++17 is awesome";
    
    std::string_view sv1 = c_string;
    std::string_view sv2 = std_string;
    std::string_view sv3 = "String literal";
    std::string_view sv4 = sv2.substr(0, 5);  // "C++17"
    
    std::cout << "sv1: " << sv1 << " (size: " << sv1.size() << ")" << std::endl;
    std::cout << "sv2: " << sv2 << " (size: " << sv2.size() << ")" << std::endl;
    std::cout << "sv3: " << sv3 << " (size: " << sv3.size() << ")" << std::endl;
    std::cout << "sv4: " << sv4 << " (size: " << sv4.size() << ")" << std::endl;
    
    // String operations
    std::cout << "sv1 starts with 'Hello': " << starts_with(sv1, "Hello") << std::endl;
    std::cout << "sv2 ends with 'awesome': " << ends_with(sv2, "awesome") << std::endl;
    std::cout << "sv2 contains '17': " << contains(sv2, "17") << std::endl;
    
    // 2. Substring operations (no copying)
    std::cout << "\n2. Substring Operations:" << std::endl;
    
    std::string_view text = "  The quick brown fox jumps over the lazy dog  ";
    std::cout << "Original: '" << text << "'" << std::endl;
    
    auto trimmed = trim(text);
    std::cout << "Trimmed: '" << trimmed << "'" << std::endl;
    
    auto first_word = trimmed.substr(0, trimmed.find(' '));
    std::cout << "First word: '" << first_word << "'" << std::endl;
    
    auto last_word = trimmed.substr(trimmed.rfind(' ') + 1);
    std::cout << "Last word: '" << last_word << "'" << std::endl;
    
    // 3. Tokenization
    std::cout << "\n3. Tokenization:" << std::endl;
    
    std::string_view csv_line = "apple,banana,cherry,date,elderberry";
    auto tokens = split(csv_line, ',');
    
    std::cout << "CSV tokens:" << std::endl;
    for (const auto& token : tokens) {
        std::cout << "  '" << token << "'" << std::endl;
    }
    
    std::string_view sentence = "  The   quick    brown   fox  ";
    auto words = split_whitespace(sentence);
    
    std::cout << "Words:" << std::endl;
    for (const auto& word : words) {
        std::cout << "  '" << word << "'" << std::endl;
    }
    
    // 4. Configuration parsing
    std::cout << "\n4. Configuration Parsing:" << std::endl;
    
    std::string_view config_text = R"(
# Database configuration
host = "localhost"
port = 5432
database = "myapp"
username = alice
password = "secret123"

# Logging
log_level = info
log_file = "/var/log/app.log"

# Features
debug = true
ssl_enabled = false
)";
    
    SimpleConfigParser config;
    config.parse_config(config_text);
    config.print_config();
    
    std::cout << "\nAccessing individual settings:" << std::endl;
    std::cout << "Database host: " << config.get("host") << std::endl;
    std::cout << "Port: " << config.get("port") << std::endl;
    std::cout << "Debug enabled: " << config.get("debug") << std::endl;
    std::cout << "Max connections (default): " << config.get("max_connections", "100") << std::endl;
    
    // 5. Log parsing
    std::cout << "\n5. Log Parsing:" << std::endl;
    
    std::string_view log_text = R"([2023-10-15 10:30:15] INFO: Application started
[2023-10-15 10:30:16] DEBUG: Loading configuration
[2023-10-15 10:30:17] INFO: Database connection established
[2023-10-15 10:30:18] WARNING: High memory usage detected
[2023-10-15 10:30:19] ERROR: Failed to process request
[2023-10-15 10:30:20] INFO: Request processed successfully)";
    
    auto log_entries = LogParser::parse_log(log_text);
    
    std::cout << "All log entries:" << std::endl;
    for (const auto& entry : log_entries) {
        entry.print();
    }
    
    std::cout << std::endl;
    LogParser::filter_by_level(log_entries, "ERROR");
    
    std::cout << std::endl;
    LogParser::filter_by_level(log_entries, "WARNING");
    
    // 6. URL parsing
    std::cout << "\n6. URL Parsing:" << std::endl;
    
    std::vector<std::string_view> urls = {
        "https://www.example.com:8080/path/to/resource?param1=value1&param2=value2#section1",
        "http://localhost/index.html",
        "ftp://files.example.com:21/downloads/file.zip",
        "www.example.com/simple",
        "https://api.service.com/v1/users?limit=10"
    };
    
    for (const auto& url : urls) {
        std::cout << "\nParsing URL: " << url << std::endl;
        auto parsed = URLParser::parse(url);
        parsed.print();
    }
    
    // 7. Command line argument simulation
    std::cout << "\n7. Command Line Parsing Simulation:" << std::endl;
    
    // Simulate argc/argv
    const char* fake_argv[] = {
        "program",
        "--verbose",
        "--output", "result.txt",
        "--count=42",
        "-f", "input.txt",
        "-x",
        "file1.txt",
        "file2.txt"
    };
    int fake_argc = sizeof(fake_argv) / sizeof(fake_argv[0]);
    
    CommandLineParser parser;
    parser.parse(fake_argc, const_cast<char**>(fake_argv));
    parser.print_parsed();
    
    std::cout << "\nQuerying specific options:" << std::endl;
    std::cout << "Verbose mode: " << (parser.has_option("verbose") ? "enabled" : "disabled") << std::endl;
    std::cout << "Output file: " << parser.get_option("output", "stdout") << std::endl;
    std::cout << "Count: " << parser.get_option("count", "0") << std::endl;
    
    // 8. String comparisons
    std::cout << "\n8. String Comparisons:" << std::endl;
    
    std::string str1 = "Hello";
    std::string str2 = "Hello, World!";
    const char* cstr = "Hello";
    
    std::string_view sv_str1 = str1;
    std::string_view sv_str2 = str2.substr(0, 5);  // "Hello"
    std::string_view sv_cstr = cstr;
    
    std::cout << "sv_str1 == sv_str2: " << (sv_str1 == sv_str2) << std::endl;
    std::cout << "sv_str1 == sv_cstr: " << (sv_str1 == sv_cstr) << std::endl;
    std::cout << "sv_str1 == \"Hello\": " << (sv_str1 == "Hello") << std::endl;
    
    // Lexicographic comparison
    std::cout << "sv_str1 < \"World\": " << (sv_str1 < "World") << std::endl;
    std::cout << "sv_str1 > \"Apple\": " << (sv_str1 > "Apple") << std::endl;
    
    // 9. Performance comparison
    std::cout << "\n9. Performance Comparison:" << std::endl;
    
    const std::string test_string(10000, 'A');  // Large string
    const int iterations = 100000;
    
    // String copying approach
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        process_string_copy(test_string);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto string_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // String_view approach
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        process_string_view(test_string);
    }
    end = std::chrono::high_resolution_clock::now();
    auto string_view_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // C-string approach
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        process_c_string(test_string.c_str());
    }
    end = std::chrono::high_resolution_clock::now();
    auto c_string_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Performance (" << iterations << " iterations on " << test_string.size() << " char string):" << std::endl;
    std::cout << "String copying: " << string_duration.count() << " microseconds" << std::endl;
    std::cout << "String_view: " << string_view_duration.count() << " microseconds" << std::endl;
    std::cout << "C-string: " << c_string_duration.count() << " microseconds" << std::endl;
    
    if (string_duration.count() > 0) {
        std::cout << "String_view speedup: " << static_cast<double>(string_duration.count()) / string_view_duration.count() << "x" << std::endl;
    }
    
    // 10. Advanced string_view operations
    std::cout << "\n10. Advanced Operations:" << std::endl;
    
    std::string_view data = "abcdefghijklmnopqrstuvwxyz";
    
    // Iterator usage
    std::cout << "First 5 characters: ";
    auto it = data.begin();
    for (int i = 0; i < 5 && it != data.end(); ++i, ++it) {
        std::cout << *it;
    }
    std::cout << std::endl;
    
    // Reverse iteration
    std::cout << "Last 5 characters (reversed): ";
    auto rit = data.rbegin();
    for (int i = 0; i < 5 && rit != data.rend(); ++i, ++rit) {
        std::cout << *rit;
    }
    std::cout << std::endl;
    
    // Find operations
    std::cout << "Position of 'j': " << data.find('j') << std::endl;
    std::cout << "Position of 'xyz': " << data.find("xyz") << std::endl;
    std::cout << "Last position of 'a': " << data.rfind('a') << std::endl;
    
    // Prefix/suffix removal
    std::string_view prefixed = "prefix_data_suffix";
    if (starts_with(prefixed, "prefix_")) {
        auto without_prefix = prefixed.substr(7);  // Remove "prefix_"
        std::cout << "Without prefix: " << without_prefix << std::endl;
        
        if (ends_with(without_prefix, "_suffix")) {
            auto clean = without_prefix.substr(0, without_prefix.size() - 7);  // Remove "_suffix"
            std::cout << "Clean data: " << clean << std::endl;
        }
    }
    
    std::cout << "\n=== STD::STRING_VIEW BENEFITS ===" << std::endl;
    std::cout << "✅ No memory allocation - references existing string data" << std::endl;
    std::cout << "✅ Fast substring operations - no copying involved" << std::endl;
    std::cout << "✅ Works with any string-like source (std::string, C-strings, literals)" << std::endl;
    std::cout << "✅ Reduced function parameter complexity (one type for all strings)" << std::endl;
    std::cout << "✅ Better performance for read-only string operations" << std::endl;
    std::cout << "✅ Consistent interface with std::string methods" << std::endl;
    std::cout << "✅ Implicit conversion from std::string and C-strings" << std::endl;
    std::cout << "⚠️  Non-owning - must ensure underlying string remains valid" << std::endl;
    std::cout << "⚠️  No null termination guarantee - can't directly pass to C APIs" << std::endl;
    std::cout << "⚠️  Dangling references if source string is destroyed" << std::endl;
    std::cout << "⚠️  Cannot modify the underlying string data" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++17 -Wall -Wextra -o string_view_demo string_view_demo.cpp
./string_view_demo

C++17 std::string_view Key Features:
1. Non-owning view of string data (lightweight reference)
2. No memory allocation for substring operations
3. Works with all string types (std::string, C-strings, literals)
4. Consistent interface similar to std::string

Basic Usage:
std::string_view sv = "hello";        // From string literal
std::string_view sv2 = std_string;    // From std::string
std::string_view sv3 = c_string;      // From C-string
std::string_view sv4 = sv.substr(1, 3); // Substring (no copying)

Key Benefits:
- Zero-cost substring operations
- Eliminates function overloads for different string types
- Significant performance improvements for read-only operations
- Reduced memory allocations in string processing

Common Operations:
- sv.size(), sv.length() - Get size
- sv.data() - Get pointer to first character
- sv.substr(pos, len) - Get substring view
- sv.find(str), sv.rfind(str) - Find operations
- sv.starts_with(prefix), sv.ends_with(suffix) - C++20
- sv.remove_prefix(n), sv.remove_suffix(n) - Modify view

Use Cases:
- Function parameters for read-only string operations
- String parsing and tokenization
- Configuration file processing
- Log file analysis
- Command line argument processing
- Text processing without modification

Safety Considerations:
- Ensure underlying string remains valid during string_view lifetime
- Cannot be used with C APIs expecting null-terminated strings
- Be careful with temporary string objects
- Consider lifetime when returning string_view from functions

Performance:
- Substring operations are O(1) instead of O(n)
- No memory allocation overhead
- Reduced copying in function calls
- Better cache locality for string processing

Best Practices:
- Use for function parameters that only read strings
- Prefer over const std::string& for read-only operations
- Be mindful of object lifetimes
- Use std::string when you need to own or modify the data
- Consider using .data() with .size() for C API interop
*/
