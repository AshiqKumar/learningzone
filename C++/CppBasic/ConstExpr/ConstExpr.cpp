/**@brief brief description
* @details This code demonstrates the use of constexpr functions to define the size of std::array.
* The Prod1 function is a simple constexpr function that multiplies two integers.
* The Prod2 function is a more complex constexpr function that performs a multiplication with additional checks.
* Both functions can be used to define the size of std::array at compile time.
* Note: The lines below are commented out because they are not used in this example.
* They show how you could use the constexpr functions to initialize variables, but they are not necessary for the array sizes.
* @warning Uncommenting these lines will not affect the functionality of the code, but they are not needed for the array sizes.
// constexpr int result1 = Prod1(2, 3); // OK: constexpr function
// constexpr int result2 = Prod2(4, 5); // OK: constexpr function
// But if you want to use them, you can uncomment the following lines:
*/
/**********
Explanation:

std::array<T, N> is a fixed-size array type in C++ where T is the element type and N is the size (must be a compile-time constant).
Prod1(2,3) is a constexpr function, so its result (6) is known at compile time.
Therefore, arr3 is an array of 6 integers: std::array<int, 6>.
Summary:
This is valid because the array size is a compile-time constant, and std::array requires its size to be known at compile time. 
*/

#include<iostream>
#include<array>
using namespace std;


//C++11 feature, A constexpr function can only have a single executable statement
constexpr int Prod1(int x, int y) noexcept
{
	return x * y;
}

//C++14 feature, Can have more statements
constexpr int Prod2(int x, int y) noexcept
{
	int result{};
	if (x != 0)
	{
		if (y != 0)
		{
			result = x * y;
		}
	}
	return result;
}

int main()
{
	constexpr int val3 = 100; // Make this constexpr
    constexpr auto x3 = val3; // OK: val3 is constexpr
    array<int, val3> arr1;    // OK: val3 is constexpr
    // If you want another constexpr variable for array size:
    constexpr int x4 = 50;
    array<int, x4> arr2;      // OK: x4 is constexpr
    cout << "arr1 size: " << arr1.size() << endl;
    cout << "arr2 size: " << arr2.size() << endl;

	array<int, Prod1(2,3)> arr3; 
	array<float, Prod2(4, 5)> arr4;
	
	// constexpr int result1 = Prod1(2, 3);
    // constexpr int result2 = Prod2(4, 5);
   
	cout << arr3.size() << endl;
	cout << arr4.size() << endl;
	return 0;
}

/*
//Approach is correct and demonstrates how to use a constexpr function template to deduce array size at compile time for std::array.

#include<iostream>
#include<array>
using namespace std;

template<typename T, size_t N> constexpr size_t ArrSize(T(&)[N]) noexcept
{
	return N;
}

int main()
{
    int arr1[] = { 1,2,3,4,5 };
    array<int, ArrSize(arr1)> MyNewArray;

    // Optionally copy values
    for (size_t i = 0; i < MyNewArray.size(); ++i)
        MyNewArray[i] = arr1[i];

    cout << "MyNewArray size: " << MyNewArray.size() << endl;
    for (int v : MyNewArray)
        cout << v << " ";
    cout << endl;
    return 0;
}

/*
Certainly! Here’s a detailed explanation of your code and the concepts it demonstrates:

### Purpose
This code shows how to **deduce the size of a C-style array at compile time** using a `constexpr` function template, and then use that size 
as the template parameter for a `std::array`. This is a common pattern for writing 
safer and more generic C++ code.

#### 1. `ArrSize` Function Template

template<typename T, size_t N> 
constexpr size_t ArrSize(T(&)[N]) noexcept {
    return N;
}
- **What it does:**  
  - Takes a reference to a C-style array of any type `T` and size `N`.
  - Returns the size `N` at compile time.
- **Why it works:**  
  - When you pass an array like `int arr1[] = {1,2,3,4,5};`, the compiler deduces `N` as `5`.
  - `constexpr` ensures the result is a compile-time constant, so it can be used in contexts that require compile-time values (like template parameters).

#### 2. Using `ArrSize` with `std::array`

```cpp
array<int, ArrSize(arr1)> MyNewArray;
```
- **What it does:**  
  - Creates a `std::array<int, 5>` (since `ArrSize(arr1)` returns `5`).
  - `std::array` is a fixed-size array whose size must be known at compile time.

- **Why it’s useful:**  
  - Avoids hardcoding the array size.
  - Makes code more generic and less error-prone.

### Benefits

- **Type Safety:** No risk of mismatched array sizes.
- **Compile-Time Checking:** Errors are caught at compile time, not runtime.
- **Generic Code:** Works for any array type and size.
- `ArrSize` deduces array size at compile time.
- You can use it to create `std::array` with the same size as a C-style array.
- This pattern is safer and more maintainable than hardcoding sizes.

*/