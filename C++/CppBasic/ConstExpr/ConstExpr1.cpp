/**********************************************************************************************************************
Here’s an explanation of your code and the C++ features it demonstrates:

### 1. `#include<iostream>` and `using namespace std;`
- Includes the standard input/output stream library.
- Allows you to use standard library names (like `cout`) without the `std::` prefix.

### 2. `class Point` 
    - **Note:** In C++11, member functions that modify members (like setters) could not be `constexpr`. In C++14 and later, this is allowed.

### 3. `main()`
- Creates two `constexpr` `Point` objects, `p1` and `p2`.
- Computes their midpoint at compile time using `constexpr auto mid = midpoint(p1, p2);`.
- All calculations are done at compile time, thanks to `constexpr`.

### **Summary**
This code shows how to use `constexpr` with classes and functions to enable compile-time calculations with user-defined types 
in C++14 and later. It demonstrates modern C++ features for efficient, type-safe, and compile-time programming.

*****************************************************************************************************************************/

#include<iostream>
using namespace std;

class Point
{
private:
	double x, y;
public:
	constexpr Point(double a, double b) noexcept :x(a), y(b) { }
	constexpr double Get_x() const noexcept  { return x; }
	constexpr double Get_y() const noexcept { return y; }
	//Not allowed in C++11, but ok now in C++14
	constexpr void setX(double newX) noexcept { x = newX; }
	constexpr void setY(double newY) noexcept { y = newY; }
};

constexpr Point midpoint(const Point& p1, const Point& p2) noexcept
{
	return { (p1.Get_x() + p2.Get_y()) / 2, // call constexpr
	(p1.Get_x() + p2.Get_y()) / 2 }; // member funcs
}
int main()
{
	constexpr Point p1(12.34, 67.87);
	constexpr Point p2(56.32, 98.47);

	constexpr auto mid = midpoint(p1, p2);
	cout << "Midpoint: (" << mid.Get_x() << ", " << mid.Get_y() << ")" << endl;
    return 0;
}