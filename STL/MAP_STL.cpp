
//A std::map in STL is an associative container that stores elements as key-value pairs,where each key is unique and automatically sorted.
//std::map is used for fast, sorted key-value storage with unique keys. Common operations: insert, find, erase, iterate, and access by key.
//In std::map, unique keys mean that each key can appear only once in the map—no duplicates are allowed.
//Each key is associated with exactly one value that means 
//Each key is unique—if you try to insert another "Alice", it will update the value for "Alice" instead of adding a new entry.
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    // Create a map with string keys and int values
    map<string, int> age;

    // Insert elements
    age["Alice"] = 30;
    age["Bob"] = 25;
    age["Charlie"] = 28;

    // Insert using insert()
    age.insert({"David", 35});

    // Access and print values
    cout << "Ages in the map:" << endl;
    for (const auto& pair : age) 
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Find and erase an element
    auto it = age.find("Bob");
    if (it != age.end()) {
        age.erase(it);
    }

    cout << "\nAfter erasing Bob:" << endl;
    for (const auto& pair : age) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}