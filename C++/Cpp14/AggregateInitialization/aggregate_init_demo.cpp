// C++14 Enhanced Aggregate Initialization
// Compile: g++ -std=c++14 -o aggregate_init_demo aggregate_init_demo.cpp
// Run: ./aggregate_init_demo

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <type_traits>

// 1. Basic aggregate types
struct Point2D {
    double x, y;
};

struct Point3D {
    double x, y, z;
};

struct Color {
    unsigned char r, g, b, a;
};

// 2. Aggregate with mixed types
struct Person {
    std::string name;
    int age;
    double height;
    bool is_student;
};

// 3. Nested aggregates
struct Rectangle {
    Point2D top_left;
    Point2D bottom_right;
    Color color;
};

struct Circle {
    Point2D center;
    double radius;
    Color color;
};

// 4. Aggregate with arrays
struct Matrix3x3 {
    double data[3][3];
};

struct StudentGrades {
    std::string name;
    int grades[5];
    double average;
};

// 5. Aggregate inheritance (C++14 allows aggregates with base classes under certain conditions)
struct BasePoint {
    double x, y;
};

struct NamedPoint : BasePoint {
    std::string name;
};

// 6. Aggregate with std containers
struct Configuration {
    std::string app_name;
    std::vector<std::string> modules;
    std::array<int, 4> version;
    bool debug_mode;
};

// 7. Template aggregates
template<typename T>
struct Pair {
    T first, second;
};

template<typename T, size_t N>
struct FixedArray {
    T data[N];
    size_t size;
};

// 8. Complex nested structure
struct Company {
    std::string name;
    struct Address {
        std::string street;
        std::string city;
        std::string country;
        int zip_code;
    } headquarters;
    
    struct Employee {
        std::string name;
        int id;
        std::string department;
        double salary;
    } employees[3];  // Fixed size array
    
    size_t employee_count;
};

// Helper function to print points
void print_point(const Point2D& p, const std::string& name = "Point") {
    std::cout << name << ": (" << p.x << ", " << p.y << ")" << std::endl;
}

void print_point(const Point3D& p, const std::string& name = "Point") {
    std::cout << name << ": (" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
}

void print_color(const Color& c, const std::string& name = "Color") {
    std::cout << name << ": RGBA(" << static_cast<int>(c.r) << ", " 
              << static_cast<int>(c.g) << ", " << static_cast<int>(c.b) 
              << ", " << static_cast<int>(c.a) << ")" << std::endl;
}

int main() {
    std::cout << "=== C++14 ENHANCED AGGREGATE INITIALIZATION DEMO ===" << std::endl;
    
    // 1. Basic aggregate initialization
    std::cout << "\n1. Basic Aggregate Initialization:" << std::endl;
    
    // Direct initialization
    Point2D p1{3.14, 2.71};
    Point2D p2 = {1.0, 2.0};
    
    // Copy initialization
    Point2D p3(p1);
    
    print_point(p1, "p1");
    print_point(p2, "p2");
    print_point(p3, "p3 (copy of p1)");
    
    // 3D points
    Point3D p3d1{1.0, 2.0, 3.0};
    Point3D p3d2 = {4.0, 5.0, 6.0};
    
    print_point(p3d1, "3D p1");
    print_point(p3d2, "3D p2");
    
    // 2. Color initialization
    std::cout << "\n2. Color Initialization:" << std::endl;
    
    Color red = {255, 0, 0, 255};
    Color green{0, 255, 0, 255};
    Color blue{0, 0, 255, 128};    // Semi-transparent blue
    Color white{255, 255, 255};   // Alpha defaults to 0 (omitted)
    
    print_color(red, "Red");
    print_color(green, "Green");
    print_color(blue, "Blue");
    print_color(white, "White");
    
    // 3. Mixed type aggregates
    std::cout << "\n3. Mixed Type Aggregates:" << std::endl;
    
    Person john = {"John Doe", 25, 5.9, true};
    Person jane{"Jane Smith", 30, 5.6, false};
    
    std::cout << "Person: " << john.name << ", Age: " << john.age 
              << ", Height: " << john.height << "ft, Student: " 
              << std::boolalpha << john.is_student << std::endl;
              
    std::cout << "Person: " << jane.name << ", Age: " << jane.age 
              << ", Height: " << jane.height << "ft, Student: " 
              << std::boolalpha << jane.is_student << std::endl;
    
    // 4. Nested aggregate initialization
    std::cout << "\n4. Nested Aggregate Initialization:" << std::endl;
    
    Rectangle rect = {
        {0.0, 0.0},        // top_left
        {10.0, 5.0},       // bottom_right
        {255, 0, 0, 255}   // red color
    };
    
    Circle circle = {
        {5.0, 5.0},        // center
        3.0,               // radius
        {0, 255, 0, 255}   // green color
    };
    
    std::cout << "Rectangle:" << std::endl;
    print_point(rect.top_left, "  Top-left");
    print_point(rect.bottom_right, "  Bottom-right");
    print_color(rect.color, "  Color");
    
    std::cout << "Circle:" << std::endl;
    print_point(circle.center, "  Center");
    std::cout << "  Radius: " << circle.radius << std::endl;
    print_color(circle.color, "  Color");
    
    // 5. Array member initialization
    std::cout << "\n5. Array Member Initialization:" << std::endl;
    
    Matrix3x3 identity = {{
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    }};
    
    std::cout << "Identity Matrix:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << identity.data[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    StudentGrades student = {
        "Alice Johnson",
        {95, 87, 92, 78, 88},
        88.0
    };
    
    std::cout << "\nStudent: " << student.name << std::endl;
    std::cout << "Grades: ";
    for (int grade : student.grades) {
        std::cout << grade << " ";
    }
    std::cout << "\nAverage: " << student.average << std::endl;
    
    // 6. Aggregate inheritance
    std::cout << "\n6. Aggregate Inheritance:" << std::endl;
    
    NamedPoint named_point = {{3.0, 4.0}, "Origin Point"};
    
    std::cout << "Named Point: " << named_point.name << std::endl;
    print_point(static_cast<BasePoint>(named_point), "  Coordinates");
    
    // 7. Standard container initialization
    std::cout << "\n7. Standard Container Initialization:" << std::endl;
    
    Configuration config = {
        "MyApp",
        {"core", "ui", "network", "database"},
        {1, 2, 3, 4},
        true
    };
    
    std::cout << "Application: " << config.app_name << std::endl;
    std::cout << "Modules: ";
    for (const auto& module : config.modules) {
        std::cout << module << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Version: ";
    for (const auto& ver : config.version) {
        std::cout << ver << ".";
    }
    std::cout << std::endl;
    
    std::cout << "Debug mode: " << std::boolalpha << config.debug_mode << std::endl;
    
    // 8. Template aggregate initialization
    std::cout << "\n8. Template Aggregate Initialization:" << std::endl;
    
    Pair<int> int_pair = {10, 20};
    Pair<double> double_pair{3.14, 2.71};
    Pair<std::string> string_pair{"Hello", "World"};
    
    std::cout << "Int pair: (" << int_pair.first << ", " << int_pair.second << ")" << std::endl;
    std::cout << "Double pair: (" << double_pair.first << ", " << double_pair.second << ")" << std::endl;
    std::cout << "String pair: (" << string_pair.first << ", " << string_pair.second << ")" << std::endl;
    
    FixedArray<int, 5> numbers = {{1, 2, 3, 4, 5}, 5};
    
    std::cout << "Fixed array: ";
    for (size_t i = 0; i < numbers.size; ++i) {
        std::cout << numbers.data[i] << " ";
    }
    std::cout << std::endl;
    
    // 9. Complex nested structure
    std::cout << "\n9. Complex Nested Structure:" << std::endl;
    
    Company tech_company = {
        "TechCorp",
        {"123 Tech Street", "Silicon Valley", "USA", 94025},
        {
            {"Alice Johnson", 1001, "Engineering", 95000.0},
            {"Bob Smith", 1002, "Marketing", 75000.0},
            {"Charlie Brown", 1003, "Sales", 65000.0}
        },
        3
    };
    
    std::cout << "Company: " << tech_company.name << std::endl;
    std::cout << "Headquarters: " << tech_company.headquarters.street << ", "
              << tech_company.headquarters.city << ", "
              << tech_company.headquarters.country << " "
              << tech_company.headquarters.zip_code << std::endl;
    
    std::cout << "Employees (" << tech_company.employee_count << "):" << std::endl;
    for (size_t i = 0; i < tech_company.employee_count; ++i) {
        const auto& emp = tech_company.employees[i];
        std::cout << "  " << emp.name << " (ID: " << emp.id 
                  << ", Dept: " << emp.department 
                  << ", Salary: $" << emp.salary << ")" << std::endl;
    }
    
    // 10. Designated initializers (C++20, but showing the concept)
    std::cout << "\n10. Advanced Initialization Patterns:" << std::endl;
    
    // Partial initialization (remaining members zero-initialized)
    Point2D partial{5.0};  // x = 5.0, y = 0.0
    print_point(partial, "Partial initialization");
    
    Color partial_color{255, 128};  // r = 255, g = 128, b = 0, a = 0
    print_color(partial_color, "Partial color");
    
    // Empty initialization (all members zero-initialized)
    Point2D zero_point{};
    print_point(zero_point, "Zero-initialized");
    
    // 11. Copy and move semantics with aggregates
    std::cout << "\n11. Copy and Move Semantics:" << std::endl;
    
    Person original{"Original Person", 40, 6.0, false};
    
    // Copy construction
    Person copied = original;
    std::cout << "Copied person: " << copied.name << std::endl;
    
    // Move construction
    Person moved = std::move(Person{"Temporary Person", 35, 5.8, true});
    std::cout << "Moved person: " << moved.name << std::endl;
    
    // Assignment
    Person assigned;
    assigned = {"Assigned Person", 28, 5.7, true};
    std::cout << "Assigned person: " << assigned.name << std::endl;
    
    // 12. Aggregate type checking
    std::cout << "\n12. Aggregate Type Checking:" << std::endl;
    
    std::cout << "Point2D is aggregate: " << std::boolalpha 
              << std::is_aggregate<Point2D>::value << std::endl;
    std::cout << "Person is aggregate: " 
              << std::is_aggregate<Person>::value << std::endl;
    std::cout << "std::vector<int> is aggregate: " 
              << std::is_aggregate<std::vector<int>>::value << std::endl;
    std::cout << "std::array<int, 5> is aggregate: " 
              << std::is_aggregate<std::array<int, 5>>::value << std::endl;
    
    // 13. Performance considerations
    std::cout << "\n13. Performance Considerations:" << std::endl;
    
    // Aggregate initialization can be very efficient
    constexpr Point2D compile_time_point{3.14, 2.71};
    constexpr Color compile_time_color{255, 0, 0, 255};
    
    std::cout << "Compile-time initialized point: ";
    print_point(compile_time_point, "Compile-time point");
    print_color(compile_time_color, "Compile-time color");
    
    // Arrays of aggregates
    std::array<Point2D, 3> points = {
        Point2D{0.0, 0.0},
        Point2D{1.0, 1.0},
        Point2D{2.0, 2.0}
    };
    
    std::cout << "Array of points:" << std::endl;
    for (size_t i = 0; i < points.size(); ++i) {
        print_point(points[i], "Point " + std::to_string(i));
    }
    
    std::cout << "\n=== AGGREGATE INITIALIZATION BENEFITS ===" << std::endl;
    std::cout << "✅ Clear, readable initialization syntax" << std::endl;
    std::cout << "✅ No need to define constructors for simple data structures" << std::endl;
    std::cout << "✅ Compile-time initialization possible" << std::endl;
    std::cout << "✅ Efficient - no hidden constructor calls" << std::endl;
    std::cout << "✅ Works with standard containers and arrays" << std::endl;
    std::cout << "✅ Supports nested initialization" << std::endl;
    std::cout << "✅ Partial initialization with zero-initialization of remaining" << std::endl;
    std::cout << "✅ Compatible with template deduction" << std::endl;
    std::cout << "⚠️  Requires all data members to be public" << std::endl;
    std::cout << "⚠️  Order-dependent initialization" << std::endl;
    std::cout << "⚠️  Cannot have user-declared constructors" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++14 -Wall -Wextra -o aggregate_init_demo aggregate_init_demo.cpp
./aggregate_init_demo

C++14 Enhanced Aggregate Initialization:
- Improvements to aggregate types and their initialization
- Better support for nested aggregates
- Enhanced compatibility with standard containers

Key Features:
1. Brace-enclosed initializer lists: Point{x, y}
2. Nested initialization: Rectangle{{x1,y1}, {x2,y2}, {r,g,b,a}}
3. Partial initialization: Point{x} (y becomes 0)
4. Empty initialization: Point{} (all members become 0)

Aggregate Requirements (C++14):
- No user-declared constructors
- No private or protected non-static data members
- No base classes (relaxed in C++17)
- No virtual functions

Benefits:
- Clean, readable initialization syntax
- No constructor overhead
- Compile-time initialization
- Natural support for POD types
- Easy integration with standard containers

Common Use Cases:
- Configuration structures
- Geometric data types
- Color representations
- Mathematical objects
- Simple data transfer objects
- Nested data structures

Performance:
- Zero overhead initialization
- Compile-time constant evaluation
- Direct member initialization
- No hidden constructor calls
*/
