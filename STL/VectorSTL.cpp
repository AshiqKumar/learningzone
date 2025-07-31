//This program demonstrates the use of the STL vector in C++
//It supports dynamic arrays (ability to resize itself automatically), allowing you to add, remove, and access elements easily.
//Incresaes the size of the vector dynamically as needed during runtime.
// Vector double the size of the array when it runs out of space, making it efficient for dynamic data storage.
// It waits until the vector is full before allocating more memory, which helps in reducing memory fragmentation, it again doubles the size of the vector when it runs out of space.
//size() = actual number of elements in the vector
//capacity() = total space allocated (may be more than size, to allow efficient growth)
//The capacity is always greater than or equal to the size.
//Removing elements from a vector does not decrease its capacity. Use shrink_to_fit() if you want to reduce the capacity to match the size.
/*
Common Operations:
push_back(value): Add an element at the end.
size(): Get the number of elements.
[] or at(index): Access elements.
Iteration: Use range-based for loops or iterators.
*/
#include <iostream>
#include <vector>
#include <algorithm> // for sort, reverse

using namespace std;


void printVector(const std::vector<int>& vec) {
    for (int x : vec) {
        cout << x << " ";
    }
    cout << endl;
}

int main() 
{

    cout << "=== STL Vector Demo ===" << endl;
    std::vector<int> myVec = {1, 2, 3, 4};
    printVector(myVec);

    std::vector<int> vLength; // Zero length vector
    
    cout << vLength.size();   // Output: 0
    // Create and initialize a vector of integers
    vector<int> v = {1, 2, 3, 4, 5};

    cout << v.at(2) << endl; // Output: 3

    // Uncommenting the next line will throw an exception
    // cout << v.at(10) << endl; // std::out_of_range

    // Add an element at the end
    v.push_back(6);

    // Access and modify elements
    v[0] = 10;

     // Insert at a specific position
    v.insert(v.begin() + 2, 99); // Insert 99 at index 2
    v.insert(v.end(), 7); // Insert 7 at the end
    v.insert(v.begin(), 0); // Insert 0 at the beginning

    // Remove last element
    v.pop_back();

    // Remove element at a specific position
    v.erase(v.begin() + 1); // Remove element at index 1

    cout << "First element (front): " << v.front() << endl; // Output: 0
    cout << "Last element (back): " << v.back() << endl;    // Output: 6

    // You can also modify these elements
    v.front() = 100;
    v.back() = 500;

    cout << "Modified vector: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // Sort the vector
    sort(v.begin(), v.end());

    // Reverse the vector
    reverse(v.begin(), v.end());

    // Find an element
    auto it = find(v.begin(), v.end(), 99);
    if (it != v.end())
        cout << "Found 99 at index " << distance(v.begin(), it) << endl;

    // Print all elements
    cout << "Vector contents: ";
    //It iterates over each element in the vector v, assigning each value to x in turn.
    //for (int x : v) is a range-based for loop (C++11 and later).
    for (int x : v)  
    {
        cout << x << " ";
    }
    cout << endl;

    // Get the size of the vector
    cout << "Vector size: " << v.size() << endl;

        // Clear all elements
    v.clear();

    // Check if vector is empty, o/p-> Vector is empty: size and capacity! 0, 10
    if (v.empty())
        cout << "Vector is empty: size and capacity! " << v.size() << ", "<<v.capacity() << endl;

    vector<int> vInitialisation (5, 10); // Create a vector of size 5, initialized with 10
    
    cout << "Vector initialized with 5 elements of value 10: ";
    for (int x : vInitialisation) 
    {
        cout << x << " ";
    }

    vector<std::string> vIntString (5, "Hello"); // Create a vector of size 5, initialized with 10
    
    cout << "Vector initialized with 5 elements of valueS: ";
    for (string str : vIntString) 
    {
        cout << str << " ";
    }
    return 0;
}

/*
Summary of operations:

insert(): Insert element at a position
pop_back(): Remove last element
erase(): Remove element at a position
sort(): Sort elements
reverse(): Reverse elements
find(): Search for an element
clear(): Remove all elements
empty(): Check if vector is empty
These operations make std::vector a powerful and flexible container in C++.

Memory fragmentation is when available memory is split into small pieces, 
making large allocations difficult. std::vector helps reduce this by allocating memory in larger contiguous chunks.
*/