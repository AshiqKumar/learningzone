// FriendFunctionOverloading.cpp - Demonstrates friend function overloading in C++
// Compile: g++ -std=c++17 -Wall -Wextra FriendFunctionOverloading.cpp -o friend_overload

#include <iostream>
#include <string>
#include <vector>

// 1. Basic Friend Function Overloading Example
class Number {
private:
    int value;
    
public:
    Number(int v = 0) : value(v) {}
    
    // Multiple overloaded friend functions with same name but different parameters
    friend Number add(const Number& a, const Number& b);
    friend Number add(const Number& a, int b);
    friend Number add(int a, const Number& b);
    friend Number add(const Number& a, const Number& b, const Number& c);
    
    // Overloaded friend comparison functions
    friend bool isEqual(const Number& a, const Number& b);
    friend bool isEqual(const Number& a, int b);
    friend bool isEqual(int a, const Number& b);
    
    // Overloaded friend output functions
    friend void print(const Number& n);
    friend void print(const Number& n, const std::string& prefix);
    friend void print(const std::vector<Number>& numbers);
    
    int getValue() const { return value; }
};

// Implementation of overloaded friend functions
Number add(const Number& a, const Number& b) {
    return Number(a.value + b.value);
}

Number add(const Number& a, int b) {
    return Number(a.value + b);
}

Number add(int a, const Number& b) {
    return Number(a + b.value);
}

Number add(const Number& a, const Number& b, const Number& c) {
    return Number(a.value + b.value + c.value);
}

bool isEqual(const Number& a, const Number& b) {
    return a.value == b.value;
}

bool isEqual(const Number& a, int b) {
    return a.value == b;
}

bool isEqual(int a, const Number& b) {
    return a == b.value;
}

void print(const Number& n) {
    std::cout << "Number: " << n.value << std::endl;
}

void print(const Number& n, const std::string& prefix) {
    std::cout << prefix << n.value << std::endl;
}

void print(const std::vector<Number>& numbers) {
    std::cout << "Numbers: [";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i].value;
        if (i < numbers.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// 2. Advanced Example: Matrix class with overloaded friend operators
class Matrix {
private:
    std::vector<std::vector<int>> data;
    size_t rows, cols;
    
public:
    Matrix(size_t r, size_t c, int initial = 0) : rows(r), cols(c) {
        data.resize(rows, std::vector<int>(cols, initial));
    }
    
    Matrix(std::initializer_list<std::initializer_list<int>> init) {
        rows = init.size();
        cols = init.begin()->size();
        data.resize(rows);
        
        size_t i = 0;
        for (const auto& row : init) {
            data[i] = std::vector<int>(row);
            ++i;
        }
    }
    
    // Overloaded friend operators for different types of multiplication
    friend Matrix operator*(const Matrix& a, const Matrix& b);        // Matrix multiplication
    friend Matrix operator*(const Matrix& a, int scalar);             // Matrix-scalar multiplication
    friend Matrix operator*(int scalar, const Matrix& a);             // Scalar-matrix multiplication
    friend std::vector<int> operator*(const Matrix& a, const std::vector<int>& vec); // Matrix-vector multiplication
    
    // Overloaded friend addition operators
    friend Matrix operator+(const Matrix& a, const Matrix& b);        // Matrix addition
    friend Matrix operator+(const Matrix& a, int scalar);             // Matrix + scalar (add to all elements)
    friend Matrix operator+(int scalar, const Matrix& a);             // Scalar + matrix
    
    // Overloaded friend comparison operators
    friend bool operator==(const Matrix& a, const Matrix& b);
    friend bool operator!=(const Matrix& a, const Matrix& b);
    
    // Overloaded friend stream operators
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    friend std::istream& operator>>(std::istream& is, Matrix& m);
    
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    
    int& operator()(size_t r, size_t c) { return data[r][c]; }
    const int& operator()(size_t r, size_t c) const { return data[r][c]; }
};

// Implementation of overloaded friend operators
Matrix operator*(const Matrix& a, const Matrix& b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Matrix dimensions don't match for multiplication");
    }
    
    Matrix result(a.rows, b.cols, 0);
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < b.cols; ++j) {
            for (size_t k = 0; k < a.cols; ++k) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

Matrix operator*(const Matrix& a, int scalar) {
    Matrix result(a.rows, a.cols);
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            result.data[i][j] = a.data[i][j] * scalar;
        }
    }
    return result;
}

Matrix operator*(int scalar, const Matrix& a) {
    return a * scalar;  // Reuse the above implementation
}

std::vector<int> operator*(const Matrix& a, const std::vector<int>& vec) {
    if (a.cols != vec.size()) {
        throw std::invalid_argument("Matrix columns must match vector size");
    }
    
    std::vector<int> result(a.rows, 0);
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            result[i] += a.data[i][j] * vec[j];
        }
    }
    return result;
}

Matrix operator+(const Matrix& a, const Matrix& b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    Matrix result(a.rows, a.cols);
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix operator+(const Matrix& a, int scalar) {
    Matrix result(a.rows, a.cols);
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            result.data[i][j] = a.data[i][j] + scalar;
        }
    }
    return result;
}

Matrix operator+(int scalar, const Matrix& a) {
    return a + scalar;
}

bool operator==(const Matrix& a, const Matrix& b) {
    if (a.rows != b.rows || a.cols != b.cols) return false;
    
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            if (a.data[i][j] != b.data[i][j]) return false;
        }
    }
    return true;
}

bool operator!=(const Matrix& a, const Matrix& b) {
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (size_t i = 0; i < m.rows; ++i) {
        os << "[";
        for (size_t j = 0; j < m.cols; ++j) {
            os << m.data[i][j];
            if (j < m.cols - 1) os << ", ";
        }
        os << "]";
        if (i < m.rows - 1) os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m) {
    for (size_t i = 0; i < m.rows; ++i) {
        for (size_t j = 0; j < m.cols; ++j) {
            is >> m.data[i][j];
        }
    }
    return is;
}

// 3. Template Class with Overloaded Friend Functions
template<typename T>
class Point {
private:
    T x, y;
    
public:
    Point(T x_val = T{}, T y_val = T{}) : x(x_val), y(y_val) {}
    
    // Overloaded friend functions for different distance calculations
    template<typename U>
    friend double distance(const Point<U>& p1, const Point<U>& p2);
    
    template<typename U>
    friend U distance_squared(const Point<U>& p1, const Point<U>& p2);
    
    template<typename U>
    friend double distance(const Point<U>& p);  // Distance from origin
    
    // Overloaded friend operators
    template<typename U>
    friend Point<U> operator+(const Point<U>& p1, const Point<U>& p2);
    
    template<typename U>
    friend Point<U> operator+(const Point<U>& p, U scalar);
    
    template<typename U>
    friend Point<U> operator+(U scalar, const Point<U>& p);
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Point<U>& p);
    
    T getX() const { return x; }
    T getY() const { return y; }
};

// Template friend function implementations
template<typename T>
double distance(const Point<T>& p1, const Point<T>& p2) {
    T dx = p1.x - p2.x;
    T dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

template<typename T>
T distance_squared(const Point<T>& p1, const Point<T>& p2) {
    T dx = p1.x - p2.x;
    T dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

template<typename T>
double distance(const Point<T>& p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

template<typename T>
Point<T> operator+(const Point<T>& p1, const Point<T>& p2) {
    return Point<T>(p1.x + p2.x, p1.y + p2.y);
}

template<typename T>
Point<T> operator+(const Point<T>& p, T scalar) {
    return Point<T>(p.x + scalar, p.y + scalar);
}

template<typename T>
Point<T> operator+(T scalar, const Point<T>& p) {
    return p + scalar;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

// Demonstration functions
void demonstrateBasicFriendOverloading() {
    std::cout << "\n=== BASIC FRIEND FUNCTION OVERLOADING ===" << std::endl;
    
    Number n1(10);
    Number n2(20);
    Number n3(30);
    
    // Test overloaded add functions
    Number result1 = add(n1, n2);           // Number + Number
    Number result2 = add(n1, 5);            // Number + int
    Number result3 = add(15, n2);           // int + Number
    Number result4 = add(n1, n2, n3);       // Three Numbers
    
    std::cout << "add(n1, n2) = " << result1.getValue() << std::endl;
    std::cout << "add(n1, 5) = " << result2.getValue() << std::endl;
    std::cout << "add(15, n2) = " << result3.getValue() << std::endl;
    std::cout << "add(n1, n2, n3) = " << result4.getValue() << std::endl;
    
    // Test overloaded equality functions
    std::cout << "isEqual(n1, n2): " << (isEqual(n1, n2) ? "true" : "false") << std::endl;
    std::cout << "isEqual(n1, 10): " << (isEqual(n1, 10) ? "true" : "false") << std::endl;
    std::cout << "isEqual(20, n2): " << (isEqual(20, n2) ? "true" : "false") << std::endl;
    
    // Test overloaded print functions
    print(n1);
    print(n2, "Value: ");
    print({n1, n2, n3});
}

void demonstrateMatrixFriendOverloading() {
    std::cout << "\n=== MATRIX FRIEND OPERATOR OVERLOADING ===" << std::endl;
    
    Matrix m1{{1, 2}, {3, 4}};
    Matrix m2{{5, 6}, {7, 8}};
    Matrix m3(2, 2, 1);  // 2x2 matrix filled with 1s
    
    std::cout << "Matrix m1:\n" << m1 << std::endl;
    std::cout << "Matrix m2:\n" << m2 << std::endl;
    
    // Matrix multiplication
    Matrix product = m1 * m2;
    std::cout << "m1 * m2:\n" << product << std::endl;
    
    // Scalar multiplication
    Matrix scaled1 = m1 * 3;
    Matrix scaled2 = 2 * m1;
    std::cout << "m1 * 3:\n" << scaled1 << std::endl;
    std::cout << "2 * m1:\n" << scaled2 << std::endl;
    
    // Matrix-vector multiplication
    std::vector<int> vec{1, 2};
    std::vector<int> result_vec = m1 * vec;
    std::cout << "m1 * [1, 2] = [" << result_vec[0] << ", " << result_vec[1] << "]" << std::endl;
    
    // Matrix addition
    Matrix sum1 = m1 + m2;
    Matrix sum2 = m1 + 10;  // Add 10 to all elements
    std::cout << "m1 + m2:\n" << sum1 << std::endl;
    std::cout << "m1 + 10:\n" << sum2 << std::endl;
    
    // Comparison
    std::cout << "m1 == m2: " << (m1 == m2 ? "true" : "false") << std::endl;
    std::cout << "m1 != m2: " << (m1 != m2 ? "true" : "false") << std::endl;
}

void demonstrateTemplateFriendOverloading() {
    std::cout << "\n=== TEMPLATE FRIEND FUNCTION OVERLOADING ===" << std::endl;
    
    Point<int> p1(3, 4);
    Point<int> p2(6, 8);
    Point<double> p3(1.5, 2.5);
    Point<double> p4(4.5, 6.5);
    
    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << "p3 = " << p3 << std::endl;
    std::cout << "p4 = " << p4 << std::endl;
    
    // Distance calculations (overloaded)
    std::cout << "Distance p1 to p2: " << distance(p1, p2) << std::endl;
    std::cout << "Distance squared p1 to p2: " << distance_squared(p1, p2) << std::endl;
    std::cout << "Distance p1 from origin: " << distance(p1) << std::endl;
    
    std::cout << "Distance p3 to p4: " << distance(p3, p4) << std::endl;
    std::cout << "Distance p3 from origin: " << distance(p3) << std::endl;
    
    // Point addition (overloaded)
    Point<int> sum1 = p1 + p2;
    Point<int> sum2 = p1 + 10;
    Point<int> sum3 = 5 + p1;
    
    std::cout << "p1 + p2 = " << sum1 << std::endl;
    std::cout << "p1 + 10 = " << sum2 << std::endl;
    std::cout << "5 + p1 = " << sum3 << std::endl;
}

int main() {
    std::cout << "=== FRIEND FUNCTION OVERLOADING IN C++ ===" << std::endl;
    std::cout << "Friend functions can be overloaded just like regular functions." << std::endl;
    std::cout << "They follow the same overloading rules based on parameter types." << std::endl;
    
    demonstrateBasicFriendOverloading();
    demonstrateMatrixFriendOverloading();
    demonstrateTemplateFriendOverloading();
    
    std::cout << "\n=== KEY POINTS ABOUT FRIEND FUNCTION OVERLOADING ===" << std::endl;
    std::cout << "1. ✅ Friend functions CAN be overloaded" << std::endl;
    std::cout << "2. Same overloading rules apply (different parameter types/count)" << std::endl;
    std::cout << "3. Each overloaded version must be declared as friend separately" << std::endl;
    std::cout << "4. Template friend functions can also be overloaded" << std::endl;
    std::cout << "5. Friend function overloading enables flexible APIs" << std::endl;
    std::cout << "6. Particularly useful for operators with different operand types" << std::endl;
    std::cout << "7. Maintains encapsulation while providing multiple interfaces" << std::endl;
    
    return 0;
}

/* Expected Output:
=== FRIEND FUNCTION OVERLOADING IN C++ ===
Friend functions can be overloaded just like regular functions.
They follow the same overloading rules based on parameter types.

=== BASIC FRIEND FUNCTION OVERLOADING ===
add(n1, n2) = 30
add(n1, 5) = 15
add(15, n2) = 35
add(n1, n2, n3) = 60
isEqual(n1, n2): false
isEqual(n1, 10): true
isEqual(20, n2): true
Number: 10
Value: 20
Numbers: [10, 20, 30]

=== MATRIX FRIEND OPERATOR OVERLOADING ===
Matrix m1:
[1, 2]
[3, 4]
Matrix m2:
[5, 6]
[7, 8]
m1 * m2:
[19, 22]
[43, 50]
m1 * 3:
[3, 6]
[9, 12]
2 * m1:
[2, 4]
[6, 8]
m1 * [1, 2] = [5, 11]
m1 + m2:
[6, 8]
[10, 12]
m1 + 10:
[11, 12]
[13, 14]
m1 == m2: false
m1 != m2: true

=== TEMPLATE FRIEND FUNCTION OVERLOADING ===
p1 = (3, 4)
p2 = (6, 8)
p3 = (1.5, 2.5)
p4 = (4.5, 6.5)
Distance p1 to p2: 5
Distance squared p1 to p2: 25
Distance p1 from origin: 5
Distance p3 to p4: 5
Distance p3 from origin: 2.91548
p1 + p2 = (9, 12)
p1 + 10 = (13, 14)
5 + p1 = (8, 9)

=== KEY POINTS ABOUT FRIEND FUNCTION OVERLOADING ===
1. ✅ Friend functions CAN be overloaded
2. Same overloading rules apply (different parameter types/count)
3. Each overloaded version must be declared as friend separately
4. Template friend functions can also be overloaded
5. Friend function overloading enables flexible APIs
6. Particularly useful for operators with different operand types
7. Maintains encapsulation while providing multiple interfaces
*/
