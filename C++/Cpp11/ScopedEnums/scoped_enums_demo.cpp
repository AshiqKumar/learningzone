// C++11 Scoped Enumerations (enum class) - Type-Safe Enums
// Compile: g++ -std=c++11 -o scoped_enums_demo scoped_enums_demo.cpp
// Run: ./scoped_enums_demo

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <typeinfo>

// 1. Traditional C-style enum (problems)
enum TraditionalColor {
    RED,    // Problem: pollutes global namespace
    GREEN,  // Problem: implicitly converts to int
    BLUE    // Problem: different enums can be compared
};

enum TraditionalSize {
    SMALL,
    MEDIUM,
    LARGE
    // RED,  // Error: RED already defined!
};

// 2. C++11 Scoped Enumerations (enum class)
enum class Color {
    Red,
    Green,
    Blue,
    Yellow,
    Purple
};

enum class Size {
    Small,
    Medium,
    Large,
    ExtraLarge
};

// 3. Scoped enum with explicit underlying type
enum class Priority : int {
    Low = 1,
    Medium = 2,
    High = 3,
    Critical = 10
};

enum class Status : char {
    Pending = 'P',
    InProgress = 'I',
    Completed = 'C',
    Failed = 'F'
};

// 4. Scoped enum for bit flags (using underlying type)
enum class FilePermissions : unsigned int {
    None = 0,
    Read = 1,
    Write = 2,
    Execute = 4,
    ReadWrite = Read | Write,
    All = Read | Write | Execute
};

// 5. Scoped enum for days of week
enum class DayOfWeek {
    Monday = 1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

// 6. Scoped enum for HTTP status codes
enum class HttpStatus {
    OK = 200,
    BadRequest = 400,
    Unauthorized = 401,
    Forbidden = 403,
    NotFound = 404,
    InternalServerError = 500
};

// 7. Utility functions for enum class
std::string colorToString(Color c) {
    switch (c) {
        case Color::Red: return "Red";
        case Color::Green: return "Green";
        case Color::Blue: return "Blue";
        case Color::Yellow: return "Yellow";
        case Color::Purple: return "Purple";
        default: return "Unknown";
    }
}

std::string sizeToString(Size s) {
    switch (s) {
        case Size::Small: return "Small";
        case Size::Medium: return "Medium";
        case Size::Large: return "Large";
        case Size::ExtraLarge: return "Extra Large";
        default: return "Unknown";
    }
}

std::string statusToString(Status s) {
    switch (s) {
        case Status::Pending: return "Pending";
        case Status::InProgress: return "In Progress";
        case Status::Completed: return "Completed";
        case Status::Failed: return "Failed";
        default: return "Unknown";
    }
}

// 8. Class using scoped enums
class Product {
private:
    std::string name_;
    Color color_;
    Size size_;
    Priority priority_;
    
public:
    Product(const std::string& name, Color color, Size size, Priority priority)
        : name_(name), color_(color), size_(size), priority_(priority) {}
    
    void display() const {
        std::cout << "Product: " << name_ 
                  << " (Color: " << colorToString(color_)
                  << ", Size: " << sizeToString(size_)
                  << ", Priority: " << static_cast<int>(priority_) << ")" << std::endl;
    }
    
    Color getColor() const { return color_; }
    Size getSize() const { return size_; }
    Priority getPriority() const { return priority_; }
    
    void setColor(Color color) { color_ = color; }
    void setSize(Size size) { size_ = size; }
    void setPriority(Priority priority) { priority_ = priority; }
};

// 9. Template function with enum class
template<typename EnumType>
void printEnumValue(EnumType value) {
    std::cout << "Enum value: " << static_cast<int>(value) << std::endl;
}

// 10. Bit operations with scoped enum flags
FilePermissions operator|(FilePermissions lhs, FilePermissions rhs) {
    return static_cast<FilePermissions>(
        static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
    );
}

FilePermissions operator&(FilePermissions lhs, FilePermissions rhs) {
    return static_cast<FilePermissions>(
        static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs)
    );
}

bool hasPermission(FilePermissions permissions, FilePermissions check) {
    return (permissions & check) == check;
}

// 11. Enum class in containers
class TaskManager {
private:
    std::map<Priority, std::vector<std::string>> tasks_;
    
public:
    void addTask(const std::string& task, Priority priority) {
        tasks_[priority].push_back(task);
    }
    
    void displayTasks() const {
        for (const auto& pair : tasks_) {
            Priority priority = pair.first;
            const auto& task_list = pair.second;
            
            std::cout << "Priority " << static_cast<int>(priority) << " tasks:" << std::endl;
            for (const auto& task : task_list) {
                std::cout << "  - " << task << std::endl;
            }
        }
    }
    
    size_t getTaskCount(Priority priority) const {
        auto it = tasks_.find(priority);
        return (it != tasks_.end()) ? it->second.size() : 0;
    }
};

int main() {
    std::cout << "=== C++11 SCOPED ENUMERATIONS (enum class) DEMO ===" << std::endl;
    
    // 1. Traditional enum problems demonstration
    std::cout << "\n1. Traditional Enum Problems:" << std::endl;
    
    TraditionalColor old_color = RED;
    TraditionalSize old_size = SMALL;
    
    std::cout << "Traditional RED: " << RED << std::endl;
    std::cout << "Traditional SMALL: " << SMALL << std::endl;
    
    // Problems with traditional enums:
    if (old_color == old_size) {  // Compiles but logically wrong!
        std::cout << "❌ Traditional enums can be compared incorrectly!" << std::endl;
    }
    
    int color_as_int = old_color;  // Implicit conversion to int
    std::cout << "❌ Traditional enum converts to int: " << color_as_int << std::endl;
    
    // 2. Scoped enum basic usage
    std::cout << "\n2. Scoped Enum Basic Usage:" << std::endl;
    
    Color favorite_color = Color::Blue;
    Size shirt_size = Size::Medium;
    
    std::cout << "Favorite color: " << colorToString(favorite_color) << std::endl;
    std::cout << "Shirt size: " << sizeToString(shirt_size) << std::endl;
    
    // Benefits of scoped enums:
    // if (favorite_color == shirt_size) { }  // Compilation error - good!
    // int color_val = favorite_color;         // Compilation error - good!
    
    // Explicit conversion when needed
    int color_value = static_cast<int>(favorite_color);
    std::cout << "Color as int (explicit): " << color_value << std::endl;
    
    // 3. Scoped enums with explicit values
    std::cout << "\n3. Scoped Enums with Explicit Values:" << std::endl;
    
    Priority task_priority = Priority::High;
    Status current_status = Status::InProgress;
    
    std::cout << "Task priority: " << static_cast<int>(task_priority) << std::endl;
    std::cout << "Current status: " << statusToString(current_status) << std::endl;
    std::cout << "Status as char: " << static_cast<char>(current_status) << std::endl;
    
    // 4. Using scoped enums in classes
    std::cout << "\n4. Scoped Enums in Classes:" << std::endl;
    
    Product product1("T-Shirt", Color::Red, Size::Large, Priority::Medium);
    Product product2("Jeans", Color::Blue, Size::Small, Priority::Low);
    Product product3("Jacket", Color::Green, Size::ExtraLarge, Priority::High);
    
    product1.display();
    product2.display();
    product3.display();
    
    // Modify product properties
    product1.setColor(Color::Purple);
    product1.setPriority(Priority::Critical);
    std::cout << "\nAfter modification:" << std::endl;
    product1.display();
    
    // 5. Switch statements with scoped enums
    std::cout << "\n5. Switch Statements with Scoped Enums:" << std::endl;
    
    auto processColor = [](Color c) {
        switch (c) {
            case Color::Red:
                std::cout << "Processing red color - warm tone" << std::endl;
                break;
            case Color::Green:
                std::cout << "Processing green color - nature tone" << std::endl;
                break;
            case Color::Blue:
                std::cout << "Processing blue color - cool tone" << std::endl;
                break;
            case Color::Yellow:
                std::cout << "Processing yellow color - bright tone" << std::endl;
                break;
            case Color::Purple:
                std::cout << "Processing purple color - royal tone" << std::endl;
                break;
        }
    };
    
    processColor(Color::Red);
    processColor(Color::Green);
    processColor(Color::Blue);
    
    // 6. Bit flag operations with scoped enums
    std::cout << "\n6. Bit Flag Operations:" << std::endl;
    
    FilePermissions user_perms = FilePermissions::Read | FilePermissions::Write;
    FilePermissions admin_perms = FilePermissions::All;
    
    std::cout << "User permissions: " << static_cast<unsigned int>(user_perms) << std::endl;
    std::cout << "Admin permissions: " << static_cast<unsigned int>(admin_perms) << std::endl;
    
    std::cout << "User has read permission: " << hasPermission(user_perms, FilePermissions::Read) << std::endl;
    std::cout << "User has execute permission: " << hasPermission(user_perms, FilePermissions::Execute) << std::endl;
    std::cout << "Admin has all permissions: " << hasPermission(admin_perms, FilePermissions::All) << std::endl;
    
    // 7. Scoped enums with containers
    std::cout << "\n7. Scoped Enums with Containers:" << std::endl;
    
    TaskManager manager;
    manager.addTask("Review code", Priority::High);
    manager.addTask("Write documentation", Priority::Medium);
    manager.addTask("Fix minor bug", Priority::Low);
    manager.addTask("Security patch", Priority::Critical);
    manager.addTask("Refactor function", Priority::Medium);
    
    std::cout << "\nAll tasks:" << std::endl;
    manager.displayTasks();
    
    std::cout << "\nTask counts:" << std::endl;
    std::cout << "Critical tasks: " << manager.getTaskCount(Priority::Critical) << std::endl;
    std::cout << "High priority tasks: " << manager.getTaskCount(Priority::High) << std::endl;
    std::cout << "Medium priority tasks: " << manager.getTaskCount(Priority::Medium) << std::endl;
    std::cout << "Low priority tasks: " << manager.getTaskCount(Priority::Low) << std::endl;
    
    // 8. HTTP status codes example
    std::cout << "\n8. HTTP Status Codes Example:" << std::endl;
    
    auto handleHttpResponse = [](HttpStatus status) {
        switch (status) {
            case HttpStatus::OK:
                std::cout << "✅ Success: " << static_cast<int>(status) << std::endl;
                break;
            case HttpStatus::BadRequest:
                std::cout << "❌ Client Error: " << static_cast<int>(status) << std::endl;
                break;
            case HttpStatus::Unauthorized:
                std::cout << "🔒 Authentication required: " << static_cast<int>(status) << std::endl;
                break;
            case HttpStatus::NotFound:
                std::cout << "🔍 Not found: " << static_cast<int>(status) << std::endl;
                break;
            case HttpStatus::InternalServerError:
                std::cout << "🔥 Server Error: " << static_cast<int>(status) << std::endl;
                break;
            default:
                std::cout << "❓ Unknown status: " << static_cast<int>(status) << std::endl;
                break;
        }
    };
    
    handleHttpResponse(HttpStatus::OK);
    handleHttpResponse(HttpStatus::NotFound);
    handleHttpResponse(HttpStatus::InternalServerError);
    
    // 9. Template usage with scoped enums
    std::cout << "\n9. Template Usage with Scoped Enums:" << std::endl;
    
    std::cout << "Color enum values:" << std::endl;
    printEnumValue(Color::Red);
    printEnumValue(Color::Blue);
    
    std::cout << "Priority enum values:" << std::endl;
    printEnumValue(Priority::Low);
    printEnumValue(Priority::Critical);
    
    // 10. Days of week example
    std::cout << "\n10. Days of Week Example:" << std::endl;
    
    auto getDayName = [](DayOfWeek day) -> std::string {
        switch (day) {
            case DayOfWeek::Monday: return "Monday";
            case DayOfWeek::Tuesday: return "Tuesday";
            case DayOfWeek::Wednesday: return "Wednesday";
            case DayOfWeek::Thursday: return "Thursday";
            case DayOfWeek::Friday: return "Friday";
            case DayOfWeek::Saturday: return "Saturday";
            case DayOfWeek::Sunday: return "Sunday";
            default: return "Unknown";
        }
    };
    
    auto isWeekend = [](DayOfWeek day) -> bool {
        return day == DayOfWeek::Saturday || day == DayOfWeek::Sunday;
    };
    
    std::vector<DayOfWeek> week = {
        DayOfWeek::Monday, DayOfWeek::Tuesday, DayOfWeek::Wednesday,
        DayOfWeek::Thursday, DayOfWeek::Friday, DayOfWeek::Saturday,
        DayOfWeek::Sunday
    };
    
    std::cout << "Week schedule:" << std::endl;
    for (auto day : week) {
        std::cout << getDayName(day) << " (" << static_cast<int>(day) << "): "
                  << (isWeekend(day) ? "Weekend! 🎉" : "Workday 💼") << std::endl;
    }
    
    // 11. Comparison between traditional and scoped enums
    std::cout << "\n11. Traditional vs Scoped Enum Comparison:" << std::endl;
    
    std::cout << "\nTraditional enum characteristics:" << std::endl;
    std::cout << "- Pollutes global namespace" << std::endl;
    std::cout << "- Implicit conversion to int: " << (RED + 10) << std::endl;
    std::cout << "- Can be compared across different enums" << std::endl;
    
    std::cout << "\nScoped enum characteristics:" << std::endl;
    std::cout << "- No namespace pollution (Color::Red, Size::Small)" << std::endl;
    std::cout << "- No implicit conversion (must use static_cast)" << std::endl;
    std::cout << "- Type-safe comparisons only within same enum" << std::endl;
    std::cout << "- Can specify underlying type explicitly" << std::endl;
    
    std::cout << "\n=== SCOPED ENUM BENEFITS ===" << std::endl;
    std::cout << "✅ Type safety - no implicit conversions" << std::endl;
    std::cout << "✅ Namespace safety - no pollution" << std::endl;
    std::cout << "✅ Forward declaration support" << std::endl;
    std::cout << "✅ Explicit underlying type specification" << std::endl;
    std::cout << "✅ Better with templates and containers" << std::endl;
    std::cout << "✅ Prevents accidental comparisons between different enums" << std::endl;
    std::cout << "⚠️  Use enum class instead of enum for new code" << std::endl;
    std::cout << "⚠️  Explicit casting required for integer conversion" << std::endl;
    std::cout << "⚠️  Cannot use unqualified names (must use Enum::Value)" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -o scoped_enums_demo scoped_enums_demo.cpp
./scoped_enums_demo

Scoped Enumeration Features:
1. Type Safety: No implicit conversion to integers
2. Namespace Safety: Values don't pollute global namespace
3. Strong Typing: Cannot compare different enum types
4. Explicit Underlying Type: Can specify int, char, etc.
5. Forward Declaration: enum class Color; works

Benefits over Traditional Enums:
- Eliminates naming conflicts
- Prevents accidental integer conversions
- Type-safe comparisons
- Better integration with templates
- Clearer code intent

Syntax:
enum class EnumName : UnderlyingType {
    Value1,
    Value2 = explicit_value,
    Value3
};

Best Practices:
- Always use enum class for new code
- Use meaningful names for enum values
- Specify underlying type when needed
- Use switch statements without default for compile-time checking
- Combine with static_cast for explicit conversions
*/
