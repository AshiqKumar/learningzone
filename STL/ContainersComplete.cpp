// STL Containers Comprehensive Demo - All Standard Containers
// Compile: g++ -std=c++20 -o containers_complete containers_complete.cpp
// Run: ./containers_complete

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <set>
#include <multiset>
#include <map>
#include <multimap>
#include <unordered_set>
#include <unordered_map>
#include <unordered_multiset>
#include <unordered_multimap>
#include <stack>
#include <queue>
#include <priority_queue>
#include <string>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>

void demonstrate_sequence_containers() {
    std::cout << "\n=== SEQUENCE CONTAINERS ===" << std::endl;
    
    // 1. std::vector - Dynamic array
    {
        std::cout << "\n1. std::vector - Dynamic Array:" << std::endl;
        std::vector<int> vec = {1, 2, 3, 4, 5};
        
        vec.push_back(6);              // Add to end - O(1) amortized
        vec.insert(vec.begin() + 2, 99); // Insert at position - O(n)
        vec.pop_back();                // Remove last - O(1)
        
        std::cout << "Vector: ";
        for (int val : vec) std::cout << val << " ";
        std::cout << std::endl;
        
        std::cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << std::endl;
        std::cout << "Random access: vec[2] = " << vec[2] << std::endl;
        
        // Performance characteristics
        std::cout << "✅ Random access: O(1)" << std::endl;
        std::cout << "✅ Push/pop back: O(1) amortized" << std::endl;
        std::cout << "⚠️  Insert/erase middle: O(n)" << std::endl;
    }
    
    // 2. std::deque - Double-ended queue
    {
        std::cout << "\n2. std::deque - Double-ended Queue:" << std::endl;
        std::deque<int> dq = {10, 20, 30};
        
        dq.push_front(5);              // Add to front - O(1)
        dq.push_back(40);              // Add to back - O(1)
        dq.pop_front();                // Remove first - O(1)
        dq.pop_back();                 // Remove last - O(1)
        
        std::cout << "Deque: ";
        for (int val : dq) std::cout << val << " ";
        std::cout << std::endl;
        
        std::cout << "Random access: dq[1] = " << dq[1] << std::endl;
        
        std::cout << "✅ Push/pop both ends: O(1)" << std::endl;
        std::cout << "✅ Random access: O(1)" << std::endl;
        std::cout << "⚠️  Insert/erase middle: O(n)" << std::endl;
    }
    
    // 3. std::list - Doubly linked list
    {
        std::cout << "\n3. std::list - Doubly Linked List:" << std::endl;
        std::list<int> lst = {100, 200, 300};
        
        lst.push_front(50);            // Add to front - O(1)
        lst.push_back(400);            // Add to back - O(1)
        
        auto it = std::find(lst.begin(), lst.end(), 200);
        if (it != lst.end()) {
            lst.insert(it, 150);       // Insert before iterator - O(1)
        }
        
        lst.remove(300);               // Remove all instances - O(n)
        
        std::cout << "List: ";
        for (int val : lst) std::cout << val << " ";
        std::cout << std::endl;
        
        std::cout << "✅ Insert/erase anywhere: O(1) with iterator" << std::endl;
        std::cout << "✅ Splice operations: O(1)" << std::endl;
        std::cout << "❌ No random access" << std::endl;
    }
    
    // 4. std::forward_list - Singly linked list
    {
        std::cout << "\n4. std::forward_list - Singly Linked List:" << std::endl;
        std::forward_list<int> flst = {1000, 2000, 3000};
        
        flst.push_front(500);          // Add to front - O(1)
        
        auto it = flst.before_begin();
        flst.insert_after(it, 250);    // Insert after iterator - O(1)
        
        std::cout << "Forward List: ";
        for (int val : flst) std::cout << val << " ";
        std::cout << std::endl;
        
        std::cout << "✅ Memory efficient (no back pointer)" << std::endl;
        std::cout << "✅ Insert after: O(1)" << std::endl;
        std::cout << "❌ Only forward iteration" << std::endl;
    }
    
    // 5. std::array - Fixed-size array
    {
        std::cout << "\n5. std::array - Fixed-size Array:" << std::endl;
        std::array<int, 5> arr = {1, 2, 3, 4, 5};
        
        arr.fill(0);                   // Fill with value
        arr[0] = 10;
        arr.at(1) = 20;               // Bounds checking
        
        std::cout << "Array: ";
        for (int val : arr) std::cout << val << " ";
        std::cout << std::endl;
        
        std::cout << "Size (compile-time): " << arr.size() << std::endl;
        
        std::cout << "✅ Zero overhead wrapper" << std::endl;
        std::cout << "✅ STL container interface" << std::endl;
        std::cout << "⚠️  Fixed size at compile time" << std::endl;
    }
}

void demonstrate_associative_containers() {
    std::cout << "\n=== ASSOCIATIVE CONTAINERS (ORDERED) ===" << std::endl;
    
    // 1. std::set - Unique sorted elements
    {
        std::cout << "\n1. std::set - Unique Sorted Elements:" << std::endl;
        std::set<int> s = {30, 10, 20, 10, 40}; // Duplicate 10 ignored
        
        s.insert(25);                  // Insert - O(log n)
        s.erase(20);                   // Erase - O(log n)
        
        std::cout << "Set: ";
        for (int val : s) std::cout << val << " ";
        std::cout << std::endl;
        
        // Search operations
        if (s.find(25) != s.end()) {
            std::cout << "Found 25 in set" << std::endl;
        }
        
        std::cout << "✅ Always sorted" << std::endl;
        std::cout << "✅ Unique elements only" << std::endl;
        std::cout << "⚠️  All operations: O(log n)" << std::endl;
    }
    
    // 2. std::multiset - Sorted elements with duplicates
    {
        std::cout << "\n2. std::multiset - Sorted with Duplicates:" << std::endl;
        std::multiset<int> ms = {30, 10, 20, 10, 40}; // Keeps duplicates
        
        ms.insert(10);                 // Another 10
        
        std::cout << "Multiset: ";
        for (int val : ms) std::cout << val << " ";
        std::cout << std::endl;
        
        std::cout << "Count of 10: " << ms.count(10) << std::endl;
        
        // Find range of equal elements
        auto range = ms.equal_range(10);
        std::cout << "All 10s: ";
        for (auto it = range.first; it != range.second; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    // 3. std::map - Unique key-value pairs
    {
        std::cout << "\n3. std::map - Unique Key-Value Pairs:" << std::endl;
        std::map<std::string, int> ages = {
            {"Alice", 25}, {"Bob", 30}, {"Charlie", 35}
        };
        
        ages["David"] = 28;            // Insert/update - O(log n)
        ages.insert({"Eve", 22});      // Insert - O(log n)
        
        std::cout << "Map (sorted by key):" << std::endl;
        for (const auto& [name, age] : ages) { // C++17 structured binding
            std::cout << "  " << name << ": " << age << std::endl;
        }
        
        // Safe access
        if (auto it = ages.find("Bob"); it != ages.end()) {
            std::cout << "Bob's age: " << it->second << std::endl;
        }
        
        std::cout << "✅ Keys always sorted" << std::endl;
        std::cout << "✅ Unique keys only" << std::endl;
    }
    
    // 4. std::multimap - Multiple values per key
    {
        std::cout << "\n4. std::multimap - Multiple Values per Key:" << std::endl;
        std::multimap<std::string, int> grades = {
            {"Alice", 85}, {"Bob", 90}, {"Alice", 78}, {"Charlie", 92}, {"Bob", 88}
        };
        
        grades.insert({"Alice", 95});   // Another grade for Alice
        
        std::cout << "Student grades:" << std::endl;
        for (const auto& [student, grade] : grades) {
            std::cout << "  " << student << ": " << grade << std::endl;
        }
        
        // Find all grades for Alice
        std::cout << "Alice's grades: ";
        auto range = grades.equal_range("Alice");
        for (auto it = range.first; it != range.second; ++it) {
            std::cout << it->second << " ";
        }
        std::cout << std::endl;
    }
}

void demonstrate_unordered_containers() {
    std::cout << "\n=== UNORDERED ASSOCIATIVE CONTAINERS (HASH-BASED) ===" << std::endl;
    
    // 1. std::unordered_set - Hash-based unique elements
    {
        std::cout << "\n1. std::unordered_set - Hash-based Unique:" << std::endl;
        std::unordered_set<int> us = {30, 10, 20, 10, 40};
        
        us.insert(25);                 // Insert - O(1) average
        us.erase(20);                  // Erase - O(1) average
        
        std::cout << "Unordered Set: ";
        for (int val : us) std::cout << val << " "; // Order not guaranteed
        std::cout << std::endl;
        
        std::cout << "Bucket count: " << us.bucket_count() << std::endl;
        std::cout << "Load factor: " << us.load_factor() << std::endl;
        
        std::cout << "✅ Average O(1) operations" << std::endl;
        std::cout << "⚠️  No guaranteed order" << std::endl;
    }
    
    // 2. std::unordered_map - Hash-based key-value
    {
        std::cout << "\n2. std::unordered_map - Hash-based Key-Value:" << std::endl;
        std::unordered_map<std::string, int> word_count;
        
        std::vector<std::string> words = {"apple", "banana", "apple", "cherry", "banana"};
        
        for (const auto& word : words) {
            word_count[word]++;         // O(1) average access/insert
        }
        
        std::cout << "Word frequencies:" << std::endl;
        for (const auto& [word, count] : word_count) {
            std::cout << "  " << word << ": " << count << std::endl;
        }
        
        std::cout << "✅ Fast lookup and insertion" << std::endl;
        std::cout << "✅ Ideal for frequency counting" << std::endl;
    }
    
    // 3. Custom hash function demo
    {
        std::cout << "\n3. Custom Hash Function Example:" << std::endl;
        
        struct Person {
            std::string name;
            int age;
            
            bool operator==(const Person& other) const {
                return name == other.name && age == other.age;
            }
        };
        
        struct PersonHash {
            std::size_t operator()(const Person& p) const {
                auto h1 = std::hash<std::string>{}(p.name);
                auto h2 = std::hash<int>{}(p.age);
                return h1 ^ (h2 << 1); // Combine hashes
            }
        };
        
        std::unordered_set<Person, PersonHash> people;
        people.insert({"Alice", 25});
        people.insert({"Bob", 30});
        people.insert({"Alice", 25}); // Duplicate, won't be inserted
        
        std::cout << "Unique people count: " << people.size() << std::endl;
    }
}

void demonstrate_container_adapters() {
    std::cout << "\n=== CONTAINER ADAPTERS ===" << std::endl;
    
    // 1. std::stack - LIFO (Last In, First Out)
    {
        std::cout << "\n1. std::stack - LIFO Container:" << std::endl;
        std::stack<int> st;
        
        st.push(10);                   // Push - O(1)
        st.push(20);
        st.push(30);
        
        std::cout << "Stack operations (LIFO):" << std::endl;
        while (!st.empty()) {
            std::cout << "Pop: " << st.top() << std::endl; // Top and pop - O(1)
            st.pop();
        }
        
        std::cout << "✅ Simple LIFO operations" << std::endl;
        std::cout << "✅ Can use vector, deque, or list as underlying container" << std::endl;
    }
    
    // 2. std::queue - FIFO (First In, First Out)
    {
        std::cout << "\n2. std::queue - FIFO Container:" << std::endl;
        std::queue<int> q;
        
        q.push(10);                    // Push to back - O(1)
        q.push(20);
        q.push(30);
        
        std::cout << "Queue operations (FIFO):" << std::endl;
        while (!q.empty()) {
            std::cout << "Pop: " << q.front() << std::endl; // Front and pop - O(1)
            q.pop();
        }
        
        std::cout << "✅ Simple FIFO operations" << std::endl;
        std::cout << "✅ Usually uses deque as underlying container" << std::endl;
    }
    
    // 3. std::priority_queue - Heap-based priority queue
    {
        std::cout << "\n3. std::priority_queue - Heap-based Priority:" << std::endl;
        std::priority_queue<int> pq; // Max heap by default
        
        pq.push(30);                   // Push - O(log n)
        pq.push(10);
        pq.push(50);
        pq.push(20);
        
        std::cout << "Priority queue (max heap):" << std::endl;
        while (!pq.empty()) {
            std::cout << "Pop: " << pq.top() << std::endl; // Top element - O(1), pop - O(log n)
            pq.pop();
        }
        
        // Min heap example
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
        min_pq.push(30);
        min_pq.push(10);
        min_pq.push(50);
        min_pq.push(20);
        
        std::cout << "Min heap priority queue:" << std::endl;
        while (!min_pq.empty()) {
            std::cout << "Pop: " << min_pq.top() << std::endl;
            min_pq.pop();
        }
        
        std::cout << "✅ Efficient priority-based operations" << std::endl;
        std::cout << "✅ Customizable comparison function" << std::endl;
    }
}

void demonstrate_string_container() {
    std::cout << "\n=== STRING CONTAINER ===" << std::endl;
    
    std::string str = "Hello, World!";
    
    // String as container
    str.push_back('!');               // Add character - O(1) amortized
    str.insert(5, " Beautiful");      // Insert substring - O(n)
    str.erase(5, 10);                // Erase substring - O(n)
    
    std::cout << "String: " << str << std::endl;
    std::cout << "Length: " << str.length() << std::endl;
    std::cout << "Capacity: " << str.capacity() << std::endl;
    
    // String-specific operations
    std::cout << "Substring(0, 5): " << str.substr(0, 5) << std::endl;
    
    auto pos = str.find("World");
    if (pos != std::string::npos) {
        std::cout << "Found 'World' at position: " << pos << std::endl;
    }
    
    // String as sequence container
    std::cout << "Characters: ";
    for (char c : str) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    
    std::cout << "✅ Rich string manipulation functions" << std::endl;
    std::cout << "✅ Compatible with STL algorithms" << std::endl;
    std::cout << "✅ Dynamic sizing like vector" << std::endl;
}

void performance_comparison() {
    std::cout << "\n=== PERFORMANCE COMPARISON ===" << std::endl;
    
    const int SIZE = 100000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, SIZE);
    
    // Generate random data
    std::vector<int> data(SIZE);
    std::generate(data.begin(), data.end(), [&]() { return dis(gen); });
    
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    
    // Vector insertion at end
    {
        std::vector<int> vec;
        start = std::chrono::high_resolution_clock::now();
        for (int val : data) {
            vec.push_back(val);
        }
        end = std::chrono::high_resolution_clock::now();
        auto vector_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Vector push_back: " << vector_time.count() << " μs" << std::endl;
    }
    
    // Set insertion (sorted)
    {
        std::set<int> s;
        start = std::chrono::high_resolution_clock::now();
        for (int val : data) {
            s.insert(val);
        }
        end = std::chrono::high_resolution_clock::now();
        auto set_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Set insert: " << set_time.count() << " μs" << std::endl;
    }
    
    // Unordered set insertion (hash)
    {
        std::unordered_set<int> us;
        start = std::chrono::high_resolution_clock::now();
        for (int val : data) {
            us.insert(val);
        }
        end = std::chrono::high_resolution_clock::now();
        auto uset_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Unordered set insert: " << uset_time.count() << " μs" << std::endl;
    }
    
    std::cout << "\n⚡ Performance Tips:" << std::endl;
    std::cout << "• Use vector for sequential access" << std::endl;
    std::cout << "• Use unordered_map/set for fast lookups" << std::endl;
    std::cout << "• Use map/set when you need sorted order" << std::endl;
    std::cout << "• Use deque for frequent front/back operations" << std::endl;
    std::cout << "• Use list for frequent middle insertions" << std::endl;
}

int main() {
    std::cout << "=== COMPLETE STL CONTAINERS REFERENCE ===" << std::endl;
    
    demonstrate_sequence_containers();
    demonstrate_associative_containers();
    demonstrate_unordered_containers();
    demonstrate_container_adapters();
    demonstrate_string_container();
    performance_comparison();
    
    std::cout << "\n=== CONTAINER SELECTION GUIDE ===" << std::endl;
    std::cout << "🔹 **Fast random access:** vector, array, deque" << std::endl;
    std::cout << "🔹 **Frequent insertions/deletions:** list, forward_list" << std::endl;
    std::cout << "🔹 **Sorted unique elements:** set" << std::endl;
    std::cout << "🔹 **Fast lookup (unsorted):** unordered_set, unordered_map" << std::endl;
    std::cout << "🔹 **Key-value mapping:** map, unordered_map" << std::endl;
    std::cout << "🔹 **Duplicate keys:** multiset, multimap" << std::endl;
    std::cout << "🔹 **LIFO behavior:** stack" << std::endl;
    std::cout << "🔹 **FIFO behavior:** queue" << std::endl;
    std::cout << "🔹 **Priority-based:** priority_queue" << std::endl;
    std::cout << "🔹 **Text processing:** string" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:
g++ -std=c++20 -Wall -Wextra -O2 -o containers_complete containers_complete.cpp
./containers_complete

CONTAINER COMPLEXITY SUMMARY:

Sequence Containers:
- vector: Random access O(1), insert/erase back O(1), middle O(n)
- deque: Random access O(1), insert/erase ends O(1), middle O(n)
- list: Insert/erase anywhere O(1), no random access
- forward_list: Insert/erase O(1), forward iteration only
- array: All operations O(1), fixed size

Associative Containers (Tree-based):
- set/map: All operations O(log n), always sorted
- multiset/multimap: O(log n), allows duplicates

Unordered Associative (Hash-based):
- unordered_set/map: Average O(1), worst O(n)
- Load factor affects performance

Container Adapters:
- stack: All operations O(1)
- queue: All operations O(1)
- priority_queue: Insert/extract O(log n), top O(1)

Memory Characteristics:
- Contiguous: vector, array, string, deque (chunks)
- Node-based: list, forward_list, set/map, unordered_*
- Hybrid: deque (contiguous chunks)

Use Cases:
- Gaming: vector for entities, priority_queue for events
- Database: unordered_map for indices, set for sorting
- Text processing: string with algorithms
- Graph algorithms: vector for adjacency, set for visited
- Web servers: queue for requests, map for sessions
*/
