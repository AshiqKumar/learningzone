#include <iostream>
#include <array>
using namespace std;

int main() {
    // Declare and initialize a std::array of size 5
    array<int, 5> arr = {10, 20, 30, 40, 50};
    array<int, 5> arr1 = {1, 2, 3, 4, 5};

        // Swap contents of arr1 and arr2
    arr.swap(arr1);

    cout << "After swap:" << endl;
    cout << "arr: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    cout << "arr1: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;



    // Access elements using index
    cout << "First element: " << arr[0] << endl;

    // Modify an element
    arr[2] = 99;

    // Print all elements
    cout << "Array contents: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // Get size of the array
    cout << "Array size: " << arr.size() << endl;

    // Access front and back
    cout << "Front: " << arr.front() << ", Back: " << arr.back() << endl;

    // Access with bounds checking
    cout << "Element at index 1 (using at()): " << arr.at(1) << endl;

    // Fill all elements with a value
    arr.fill(7);
    cout << "Array after fill(7): ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // Using iterators
    cout << "Array using iterators: ";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}