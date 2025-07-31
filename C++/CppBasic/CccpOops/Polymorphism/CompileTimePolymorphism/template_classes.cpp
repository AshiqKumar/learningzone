// template_classes.cpp - Demonstrates template classes in C++
// Compile: g++ -std=c++17 -Wall -Wextra template_classes.cpp -o template_classes

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>

// 1. Basic Template Class
template<typename T>
class Stack {
private:
    std::vector<T> elements;
    
public:
    Stack() = default;
    
    void push(const T& element) {
        elements.push_back(element);
    }
    
    void push(T&& element) {
        elements.push_back(std::move(element));
    }
    
    T pop() {
        if (elements.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        T result = std::move(elements.back());
        elements.pop_back();
        return result;
    }
    
    const T& top() const {
        if (elements.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return elements.back();
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
    
    void display() const {
        std::cout << "Stack (top to bottom): ";
        for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
};

// 2. Template Class with Multiple Parameters
template<typename Key, typename Value, typename Compare = std::less<Key>>
class SimpleMap {
private:
    struct Pair {
        Key key;
        Value value;
        
        Pair(const Key& k, const Value& v) : key(k), value(v) {}
        Pair(Key&& k, Value&& v) : key(std::move(k)), value(std::move(v)) {}
    };
    
    std::vector<Pair> data;
    Compare comp;
    
public:
    SimpleMap(Compare c = Compare{}) : comp(c) {}
    
    void insert(const Key& key, const Value& value) {
        auto it = findKey(key);
        if (it != data.end()) {
            it->value = value;  // Update existing
        } else {
            data.emplace_back(key, value);
            // Keep sorted for binary search
            std::sort(data.begin(), data.end(), 
                     [this](const Pair& a, const Pair& b) {
                         return comp(a.key, b.key);
                     });
        }
    }
    
    Value& operator[](const Key& key) {
        auto it = findKey(key);
        if (it != data.end()) {
            return it->value;
        } else {
            data.emplace_back(key, Value{});
            std::sort(data.begin(), data.end(), 
                     [this](const Pair& a, const Pair& b) {
                         return comp(a.key, b.key);
                     });
            return findKey(key)->value;
        }
    }
    
    bool contains(const Key& key) const {
        return findKey(key) != data.end();
    }
    
    size_t size() const {
        return data.size();
    }
    
    void display() const {
        std::cout << "Map contents:" << std::endl;
        for (const auto& pair : data) {
            std::cout << "  " << pair.key << " -> " << pair.value << std::endl;
        }
    }
    
private:
    auto findKey(const Key& key) -> decltype(data.begin()) {
        return std::find_if(data.begin(), data.end(),
                           [&key](const Pair& p) { return p.key == key; });
    }
    
    auto findKey(const Key& key) const -> decltype(data.begin()) {
        return std::find_if(data.begin(), data.end(),
                           [&key](const Pair& p) { return p.key == key; });
    }
};

// 3. Template Class with Non-Type Parameters
template<typename T, size_t Size>
class Array {
private:
    T data[Size];
    
public:
    Array() = default;
    
    Array(std::initializer_list<T> init) {
        if (init.size() > Size) {
            throw std::invalid_argument("Too many initializers");
        }
        
        size_t i = 0;
        for (const auto& element : init) {
            data[i++] = element;
        }
        
        // Initialize remaining elements to default
        for (; i < Size; ++i) {
            data[i] = T{};
        }
    }
    
    T& operator[](size_t index) {
        if (index >= Size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= Size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    constexpr size_t size() const {
        return Size;
    }
    
    T* begin() { return data; }
    T* end() { return data + Size; }
    const T* begin() const { return data; }
    const T* end() const { return data + Size; }
    
    void fill(const T& value) {
        for (size_t i = 0; i < Size; ++i) {
            data[i] = value;
        }
    }
    
    void display() const {
        std::cout << "Array[" << Size << "]: ";
        for (const auto& element : *this) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
};

// 4. Template Class with Default Template Arguments
template<typename T, typename Allocator = std::allocator<T>>
class Vector {
private:
    T* data;
    size_t capacity;
    size_t count;
    Allocator alloc;
    
public:
    Vector() : data(nullptr), capacity(0), count(0) {}
    
    explicit Vector(size_t initialCapacity) 
        : capacity(initialCapacity), count(0) {
        data = alloc.allocate(capacity);
    }
    
    ~Vector() {
        clear();
        if (data) {
            alloc.deallocate(data, capacity);
        }
    }
    
    // Copy constructor
    Vector(const Vector& other) 
        : capacity(other.capacity), count(other.count) {
        data = alloc.allocate(capacity);
        for (size_t i = 0; i < count; ++i) {
            std::allocator_traits<Allocator>::construct(alloc, data + i, other.data[i]);
        }
    }
    
    // Move constructor
    Vector(Vector&& other) noexcept 
        : data(other.data), capacity(other.capacity), count(other.count) {
        other.data = nullptr;
        other.capacity = 0;
        other.count = 0;
    }
    
    void push_back(const T& value) {
        if (count >= capacity) {
            resize();
        }
        std::allocator_traits<Allocator>::construct(alloc, data + count, value);
        ++count;
    }
    
    void push_back(T&& value) {
        if (count >= capacity) {
            resize();
        }
        std::allocator_traits<Allocator>::construct(alloc, data + count, std::move(value));
        ++count;
    }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
    
    size_t size() const { return count; }
    size_t getCapacity() const { return capacity; }
    
    void clear() {
        for (size_t i = 0; i < count; ++i) {
            std::allocator_traits<Allocator>::destroy(alloc, data + i);
        }
        count = 0;
    }
    
    void display() const {
        std::cout << "Vector[" << count << "/" << capacity << "]: ";
        for (size_t i = 0; i < count; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    
private:
    void resize() {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = alloc.allocate(newCapacity);
        
        for (size_t i = 0; i < count; ++i) {
            std::allocator_traits<Allocator>::construct(alloc, newData + i, std::move(data[i]));
            std::allocator_traits<Allocator>::destroy(alloc, data + i);
        }
        
        if (data) {
            alloc.deallocate(data, capacity);
        }
        
        data = newData;
        capacity = newCapacity;
    }
};

// 5. Variadic Template Class
template<typename... Types>
class Tuple;

// Base case: empty tuple
template<>
class Tuple<> {
public:
    static constexpr size_t size() { return 0; }
};

// Recursive case
template<typename Head, typename... Tail>
class Tuple<Head, Tail...> : private Tuple<Tail...> {
private:
    Head value;
    
public:
    Tuple(const Head& h, const Tail&... t) 
        : Tuple<Tail...>(t...), value(h) {}
    
    static constexpr size_t size() { 
        return 1 + Tuple<Tail...>::size(); 
    }
    
    template<size_t Index>
    auto get() -> decltype(auto) {
        if constexpr (Index == 0) {
            return value;
        } else {
            return Tuple<Tail...>::template get<Index - 1>();
        }
    }
    
    template<size_t Index>
    auto get() const -> decltype(auto) {
        if constexpr (Index == 0) {
            return value;
        } else {
            return Tuple<Tail...>::template get<Index - 1>();
        }
    }
    
    void display() const {
        std::cout << value;
        if constexpr (sizeof...(Tail) > 0) {
            std::cout << ", ";
            Tuple<Tail...>::display();
        }
    }
};

// Helper function to make tuples
template<typename... Types>
Tuple<Types...> makeTuple(const Types&... args) {
    return Tuple<Types...>(args...);
}

// 6. Template Class with Friend Functions
template<typename T>
class Point {
private:
    T x, y;
    
public:
    Point(T x_val = T{}, T y_val = T{}) : x(x_val), y(y_val) {}
    
    // Template friend function
    template<typename U>
    friend Point<U> operator+(const Point<U>& a, const Point<U>& b);
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Point<U>& p);
    
    T getX() const { return x; }
    T getY() const { return y; }
    
    void setX(T x_val) { x = x_val; }
    void setY(T y_val) { y = y_val; }
};

template<typename T>
Point<T> operator+(const Point<T>& a, const Point<T>& b) {
    return Point<T>(a.x + b.x, a.y + b.y);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

// 7. Template Class Inheritance
template<typename T>
class Shape {
protected:
    T area_value;
    
public:
    Shape() : area_value(T{}) {}
    virtual ~Shape() = default;
    
    virtual T area() const = 0;
    virtual void display() const = 0;
};

template<typename T>
class Rectangle : public Shape<T> {
private:
    T width, height;
    
public:
    Rectangle(T w, T h) : width(w), height(h) {
        this->area_value = width * height;
    }
    
    T area() const override {
        return width * height;
    }
    
    void display() const override {
        std::cout << "Rectangle: " << width << "x" << height 
                  << " (area: " << area() << ")" << std::endl;
    }
};

template<typename T>
class Circle : public Shape<T> {
private:
    T radius;
    static constexpr double PI = 3.14159265359;
    
public:
    Circle(T r) : radius(r) {
        this->area_value = static_cast<T>(PI * radius * radius);
    }
    
    T area() const override {
        return static_cast<T>(PI * radius * radius);
    }
    
    void display() const override {
        std::cout << "Circle: radius=" << radius 
                  << " (area: " << area() << ")" << std::endl;
    }
};

// Demonstration functions
void demonstrateBasicTemplateClass() {
    std::cout << "\n=== BASIC TEMPLATE CLASS (STACK) ===" << std::endl;
    
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    
    std::cout << "Top element: " << intStack.top() << std::endl;
    std::cout << "Popped: " << intStack.pop() << std::endl;
    intStack.display();
    
    Stack<std::string> stringStack;
    stringStack.push("First");
    stringStack.push("Second");
    stringStack.push("Third");
    stringStack.display();
}

void demonstrateMultipleParameters() {
    std::cout << "\n=== MULTIPLE TEMPLATE PARAMETERS (MAP) ===" << std::endl;
    
    SimpleMap<std::string, int> nameAge;
    nameAge.insert("Alice", 25);
    nameAge.insert("Bob", 30);
    nameAge.insert("Charlie", 35);
    nameAge.display();
    
    nameAge["David"] = 40;
    std::cout << "Alice's age: " << nameAge["Alice"] << std::endl;
    
    // Using custom comparator
    SimpleMap<int, std::string, std::greater<int>> reverseMap;
    reverseMap.insert(3, "Three");
    reverseMap.insert(1, "One");
    reverseMap.insert(2, "Two");
    reverseMap.display();
}

void demonstrateNonTypeParameters() {
    std::cout << "\n=== NON-TYPE TEMPLATE PARAMETERS (ARRAY) ===" << std::endl;
    
    Array<int, 5> arr1{1, 2, 3, 4, 5};
    arr1.display();
    
    Array<double, 3> arr2{1.1, 2.2, 3.3};
    arr2.display();
    
    Array<std::string, 4> arr3{"Hello", "Template", "Array"};
    arr3.display();
    
    arr1.fill(99);
    arr1.display();
}

void demonstrateCustomVector() {
    std::cout << "\n=== TEMPLATE CLASS WITH ALLOCATOR ===" << std::endl;
    
    Vector<int> vec(2);
    vec.push_back(10);
    vec.push_back(20);
    vec.display();
    
    vec.push_back(30);  // Should trigger resize
    vec.push_back(40);
    vec.display();
    
    Vector<std::string> stringVec(1);
    stringVec.push_back("Template");
    stringVec.push_back("Vector");
    stringVec.push_back("Example");
    stringVec.display();
}

void demonstrateVariadicTemplate() {
    std::cout << "\n=== VARIADIC TEMPLATE CLASS (TUPLE) ===" << std::endl;
    
    auto tuple1 = makeTuple(42, 3.14, std::string("Hello"));
    std::cout << "Tuple size: " << tuple1.size() << std::endl;
    std::cout << "Tuple contents: ";
    tuple1.display();
    std::cout << std::endl;
    
    std::cout << "Element 0: " << tuple1.get<0>() << std::endl;
    std::cout << "Element 1: " << tuple1.get<1>() << std::endl;
    std::cout << "Element 2: " << tuple1.get<2>() << std::endl;
    
    auto tuple2 = makeTuple(100, 'A');
    std::cout << "Tuple2 contents: ";
    tuple2.display();
    std::cout << std::endl;
}

void demonstrateTemplateWithFriends() {
    std::cout << "\n=== TEMPLATE CLASS WITH FRIEND FUNCTIONS ===" << std::endl;
    
    Point<int> p1(3, 4);
    Point<int> p2(1, 2);
    
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    
    Point<int> p3 = p1 + p2;
    std::cout << "p1 + p2: " << p3 << std::endl;
    
    Point<double> pd1(2.5, 3.7);
    Point<double> pd2(1.2, 4.8);
    Point<double> pd3 = pd1 + pd2;
    std::cout << "Double points: " << pd1 << " + " << pd2 << " = " << pd3 << std::endl;
}

void demonstrateTemplateInheritance() {
    std::cout << "\n=== TEMPLATE CLASS INHERITANCE ===" << std::endl;
    
    std::vector<std::unique_ptr<Shape<double>>> shapes;
    
    shapes.push_back(std::make_unique<Rectangle<double>>(5.0, 3.0));
    shapes.push_back(std::make_unique<Circle<double>>(2.5));
    shapes.push_back(std::make_unique<Rectangle<double>>(4.0, 4.0));
    
    for (const auto& shape : shapes) {
        shape->display();
    }
    
    double totalArea = 0.0;
    for (const auto& shape : shapes) {
        totalArea += shape->area();
    }
    std::cout << "Total area: " << totalArea << std::endl;
}

int main() {
    std::cout << "=== COMPILE-TIME POLYMORPHISM: TEMPLATE CLASSES ===" << std::endl;
    std::cout << "Template classes provide generic container and algorithm" << std::endl;
    std::cout << "implementations with compile-time type safety and optimization." << std::endl;
    
    demonstrateBasicTemplateClass();
    demonstrateMultipleParameters();
    demonstrateNonTypeParameters();
    demonstrateCustomVector();
    demonstrateVariadicTemplate();
    demonstrateTemplateWithFriends();
    demonstrateTemplateInheritance();
    
    std::cout << "\n=== TEMPLATE CLASS FEATURES ===" << std::endl;
    std::cout << "1. Type Parameterization - Generic data structures" << std::endl;
    std::cout << "2. Non-Type Parameters - Compile-time constants" << std::endl;
    std::cout << "3. Template Specialization - Custom implementations" << std::endl;
    std::cout << "4. Variadic Templates - Variable number of types" << std::endl;
    std::cout << "5. Template Inheritance - Polymorphic templates" << std::endl;
    std::cout << "6. SFINAE Support - Conditional compilation" << std::endl;
    
    return 0;
}

/* Expected Output:
=== COMPILE-TIME POLYMORPHISM: TEMPLATE CLASSES ===
Template classes provide generic container and algorithm
implementations with compile-time type safety and optimization.

=== BASIC TEMPLATE CLASS (STACK) ===
Stack (top to bottom): 30 20 10 
Top element: 30
Popped: 30
Stack (top to bottom): 20 10 
Stack (top to bottom): Third Second First 

=== MULTIPLE TEMPLATE PARAMETERS (MAP) ===
Map contents:
  Alice -> 25
  Bob -> 30
  Charlie -> 35
Alice's age: 25
Map contents:
  3 -> Three
  2 -> Two
  1 -> One

=== NON-TYPE TEMPLATE PARAMETERS (ARRAY) ===
Array[5]: 1 2 3 4 5 
Array[3]: 1.1 2.2 3.3 
Array[4]: Hello Template Array  
Array[5]: 99 99 99 99 99 

=== TEMPLATE CLASS WITH ALLOCATOR ===
Vector[2/2]: 10 20 
Vector[4/4]: 10 20 30 40 
Vector[3/4]: Template Vector Example 

=== VARIADIC TEMPLATE CLASS (TUPLE) ===
Tuple size: 3
Tuple contents: 42, 3.14, Hello
Element 0: 42
Element 1: 3.14
Element 2: Hello
Tuple2 contents: 100, A

=== TEMPLATE CLASS WITH FRIEND FUNCTIONS ===
p1: (3, 4)
p2: (1, 2)
p1 + p2: (4, 6)
Double points: (2.5, 3.7) + (1.2, 4.8) = (3.7, 8.5)

=== TEMPLATE CLASS INHERITANCE ===
Rectangle: 5x3 (area: 15)
Circle: radius=2.5 (area: 19.635)
Rectangle: 4x4 (area: 16)
Total area: 50.635

=== TEMPLATE CLASS FEATURES ===
1. Type Parameterization - Generic data structures
2. Non-Type Parameters - Compile-time constants
3. Template Specialization - Custom implementations
4. Variadic Templates - Variable number of types
5. Template Inheritance - Polymorphic templates
6. SFINAE Support - Conditional compilation
*/
