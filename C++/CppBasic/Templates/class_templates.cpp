// class_templates.cpp - Simple Class Template Examples
// Compile: g++ -std=c++17 -Wall -Wextra class_templates.cpp -o class_templates

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// 1. Basic Class Template - Simple Container
template<typename T>
class Container {
private:
    T data;
    
public:
    Container(T value) : data(value) {}
    
    T getValue() const {
        return data;
    }
    
    void setValue(T value) {
        data = value;
    }
    
    void display() const {
        std::cout << "Container holds: " << data << std::endl;
    }
};

// 2. Class Template with Multiple Parameters
template<typename T, typename U>
class Pair {
private:
    T first;
    U second;
    
public:
    Pair(T f, U s) : first(f), second(s) {}
    
    T getFirst() const { return first; }
    U getSecond() const { return second; }
    
    void setFirst(T f) { first = f; }
    void setSecond(U s) { second = s; }
    
    void display() const {
        std::cout << "Pair: (" << first << ", " << second << ")" << std::endl;
    }
};

// 3. Class Template with Non-Type Parameter
template<typename T, size_t SIZE>
class Array {
private:
    T data[SIZE];
    
public:
    Array() {
        for (size_t i = 0; i < SIZE; ++i) {
            data[i] = T{};  // Default initialize
        }
    }
    
    T& operator[](size_t index) {
        if (index >= SIZE) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= SIZE) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    size_t size() const { return SIZE; }
    
    void fill(T value) {
        for (size_t i = 0; i < SIZE; ++i) {
            data[i] = value;
        }
    }
    
    void display() const {
        std::cout << "Array contents: ";
        for (size_t i = 0; i < SIZE; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

// 4. Simple Stack Class Template
template<typename T>
class Stack {
private:
    std::vector<T> elements;
    
public:
    void push(const T& item) {
        elements.push_back(item);
    }
    
    void pop() {
        if (elements.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        elements.pop_back();
    }
    
    T top() const {
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

// 5. Class Template with Default Parameter
template<typename T = int>
class Calculator {
private:
    T value;
    
public:
    Calculator(T v = T{}) : value(v) {}
    
    Calculator add(T v) const {
        return Calculator(value + v);
    }
    
    Calculator multiply(T v) const {
        return Calculator(value * v);
    }
    
    T getValue() const { return value; }
    
    void display() const {
        std::cout << "Calculator value: " << value << std::endl;
    }
};

// 6. Class Template Specialization for strings
template<>
class Container<std::string> {
private:
    std::string data;
    
public:
    Container(std::string value) : data(value) {}
    
    std::string getValue() const {
        return data;
    }
    
    void setValue(std::string value) {
        data = value;
    }
    
    // Special method for string specialization
    void displayUpperCase() const {
        std::string upper = data;
        for (char& c : upper) {
            c = std::toupper(c);
        }
        std::cout << "Container holds (uppercase): " << upper << std::endl;
    }
    
    void display() const {
        std::cout << "String Container holds: \"" << data << "\"" << std::endl;
    }
};

// 7. Simple Box Class Template
template<typename T>
class Box {
private:
    T width, height, depth;
    
public:
    Box(T w, T h, T d) : width(w), height(h), depth(d) {}
    
    T volume() const {
        return width * height * depth;
    }
    
    T surfaceArea() const {
        return 2 * (width * height + width * depth + height * depth);
    }
    
    void display() const {
        std::cout << "Box dimensions: " << width << " x " << height << " x " << depth << std::endl;
        std::cout << "Volume: " << volume() << ", Surface Area: " << surfaceArea() << std::endl;
    }
};

int main() {
    std::cout << "=== CLASS TEMPLATES EXAMPLES ===" << std::endl;
    
    // 1. Basic Container template
    std::cout << "\n1. Basic Container Template:" << std::endl;
    Container<int> intContainer(42);
    Container<double> doubleContainer(3.14);
    Container<std::string> stringContainer("Hello Templates");
    
    intContainer.display();
    doubleContainer.display();
    stringContainer.display();
    stringContainer.displayUpperCase();  // Special method for string specialization
    
    // 2. Pair template with multiple types
    std::cout << "\n2. Pair Template with Multiple Types:" << std::endl;
    Pair<int, std::string> nameAge(25, "Alice");
    Pair<double, char> scoreGrade(95.5, 'A');
    
    nameAge.display();
    scoreGrade.display();
    
    // 3. Array template with non-type parameter
    std::cout << "\n3. Array Template with Size Parameter:" << std::endl;
    Array<int, 5> intArray;
    Array<char, 3> charArray;
    
    // Fill arrays
    intArray.fill(10);
    charArray[0] = 'A';
    charArray[1] = 'B';
    charArray[2] = 'C';
    
    intArray.display();
    charArray.display();
    
    std::cout << "Array sizes: int array = " << intArray.size() 
              << ", char array = " << charArray.size() << std::endl;
    
    // 4. Stack template
    std::cout << "\n4. Stack Template:" << std::endl;
    Stack<int> intStack;
    Stack<std::string> stringStack;
    
    // Push elements
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    
    stringStack.push("First");
    stringStack.push("Second");
    stringStack.push("Third");
    
    intStack.display();
    stringStack.display();
    
    // Pop elements
    std::cout << "Popping from int stack: " << intStack.top() << std::endl;
    intStack.pop();
    intStack.display();
    
    // 5. Calculator with default template parameter
    std::cout << "\n5. Calculator with Default Template Parameter:" << std::endl;
    Calculator<> defaultCalc(10);        // Uses default int type
    Calculator<double> doubleCalc(5.5);
    
    auto result1 = defaultCalc.add(5).multiply(2);
    auto result2 = doubleCalc.add(2.5).multiply(3.0);
    
    result1.display();
    result2.display();
    
    // 6. Box template for geometry
    std::cout << "\n6. Box Template for Geometry:" << std::endl;
    Box<int> intBox(3, 4, 5);
    Box<double> doubleBox(2.5, 3.5, 4.5);
    
    intBox.display();
    doubleBox.display();
    
    // 7. Demonstrating template instantiation
    std::cout << "\n7. Multiple Instantiations:" << std::endl;
    Container<int> c1(100);
    Container<int> c2(200);     // Same instantiation as c1
    Container<float> c3(1.5f);  // Different instantiation
    
    c1.display();
    c2.display();
    c3.display();
    
    // 8. Using template objects in containers
    std::cout << "\n8. Template Objects in Containers:" << std::endl;
    std::vector<Container<int>> containers;
    containers.emplace_back(1);
    containers.emplace_back(2);
    containers.emplace_back(3);
    
    std::cout << "Container vector contents:" << std::endl;
    for (const auto& container : containers) {
        container.display();
    }
    
    std::cout << "\n=== CLASS TEMPLATE BENEFITS ===" << std::endl;
    std::cout << "✅ Generic data structures that work with any type" << std::endl;
    std::cout << "✅ Type safety at compile-time" << std::endl;
    std::cout << "✅ Code reusability across different data types" << std::endl;
    std::cout << "✅ No runtime overhead" << std::endl;
    std::cout << "✅ Can be specialized for specific types" << std::endl;
    
    std::cout << "\n=== KEY CONCEPTS ===" << std::endl;
    std::cout << "• Class templates are instantiated when objects are created" << std::endl;
    std::cout << "• Template parameters must be explicitly specified" << std::endl;
    std::cout << "• Each type combination creates a separate class" << std::endl;
    std::cout << "• Can have default template parameters" << std::endl;
    std::cout << "• Can be specialized for specific types" << std::endl;
    std::cout << "• Non-type parameters allow compile-time constants" << std::endl;
    
    return 0;
}

/*
Class Template Key Points:

1. Syntax:
   template<typename T>
   class ClassName {
       // class definition
   };

2. Instantiation:
   ClassName<int> object;  // Must explicitly specify type

3. Multiple Parameters:
   template<typename T, typename U, size_t N>

4. Default Parameters:
   template<typename T = int>

5. Specialization:
   template<>
   class ClassName<SpecificType> {
       // specialized implementation
   };

6. Non-Type Parameters:
   template<typename T, size_t SIZE>
   - Allows compile-time constants as parameters

7. Best Practices:
   - Use clear and descriptive template parameter names
   - Provide default parameters when appropriate
   - Consider specializations for specific types
   - Document template requirements and constraints
   - Use SFINAE or concepts for advanced constraints

8. Common Use Cases:
   - Generic containers (vector, stack, queue)
   - Mathematical classes (Matrix, Complex)
   - Resource management (smart pointers)
   - Policy-based design
*/
