// C++11 Unordered Containers - Hash-based STL Containers
// Compile: g++ -std=c++11 -o unordered_containers_demo unordered_containers_demo.cpp
// Run: ./unordered_containers_demo

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <multiset>
#include <multimap>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>
#include <bitset>

// Custom class for demonstrating hash containers
struct Person {
    std::string name;
    int age;
    std::string city;
    
    Person(const std::string& n, int a, const std::string& c) 
        : name(n), age(a), city(c) {}
    
    // Equality operator for unordered containers
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age && city == other.city;
    }
    
    // Less-than operator for ordered containers
    bool operator<(const Person& other) const {
        if (name != other.name) return name < other.name;
        if (age != other.age) return age < other.age;
        return city < other.city;
    }
    
    void display() const {
        std::cout << name << " (" << age << ", " << city << ")";
    }
};

// Custom hash function for Person
struct PersonHash {
    std::size_t operator()(const Person& p) const {
        auto h1 = std::hash<std::string>{}(p.name);
        auto h2 = std::hash<int>{}(p.age);
        auto h3 = std::hash<std::string>{}(p.city);
        
        // Combine hashes
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

// Performance comparison utility
template<typename Container, typename Value>
double measureInsertionTime(Container& container, const std::vector<Value>& values) {
    auto start = std::chrono::high_resolution_clock::now();
    
    for (const auto& value : values) {
        container.insert(value);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return duration.count();
}

template<typename Container, typename Value>
double measureLookupTime(const Container& container, const std::vector<Value>& values) {
    auto start = std::chrono::high_resolution_clock::now();
    
    int found_count = 0;
    for (const auto& value : values) {
        if (container.find(value) != container.end()) {
            found_count++;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Prevent optimization from eliminating the loop
    volatile int dummy = found_count;
    (void)dummy;
    
    return duration.count();
}

int main() {
    std::cout << "=== C++11 UNORDERED CONTAINERS DEMO ===" << std::endl;
    
    // 1. unordered_set - Hash-based unique elements
    std::cout << "\n1. unordered_set - Hash-based Unique Elements:" << std::endl;
    
    std::unordered_set<int> unordered_int_set;
    
    // Insert elements
    unordered_int_set.insert(42);
    unordered_int_set.insert(17);
    unordered_int_set.insert(8);
    unordered_int_set.insert(42);  // Duplicate - won't be inserted
    unordered_int_set.insert(23);
    
    std::cout << "unordered_set contents: ";
    for (const auto& value : unordered_int_set) {
        std::cout << value << " ";  // Order is not guaranteed!
    }
    std::cout << std::endl;
    
    std::cout << "Size: " << unordered_int_set.size() << std::endl;
    std::cout << "Contains 42: " << (unordered_int_set.find(42) != unordered_int_set.end()) << std::endl;
    std::cout << "Contains 99: " << (unordered_int_set.find(99) != unordered_int_set.end()) << std::endl;
    
    // 2. unordered_map - Hash-based key-value pairs
    std::cout << "\n2. unordered_map - Hash-based Key-Value Pairs:" << std::endl;
    
    std::unordered_map<std::string, int> word_count;
    
    // Count words
    std::vector<std::string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    for (const auto& word : words) {
        word_count[word]++;
    }
    
    std::cout << "Word frequencies:" << std::endl;
    for (const auto& pair : word_count) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    
    // Using find vs operator[]
    std::cout << "\nLookup methods:" << std::endl;
    auto it = word_count.find("banana");
    if (it != word_count.end()) {
        std::cout << "Found 'banana': " << it->second << std::endl;
    }
    
    // operator[] creates entry if not exists
    std::cout << "New entry 'orange': " << word_count["orange"] << std::endl;
    std::cout << "Size after operator[]: " << word_count.size() << std::endl;
    
    // 3. multiset - Ordered multiple identical elements
    std::cout << "\n3. multiset - Ordered Multiple Identical Elements:" << std::endl;
    
    std::multiset<int> multi_int_set;
    
    // Insert with duplicates
    std::vector<int> values = {5, 3, 8, 3, 1, 8, 5, 5};
    for (int val : values) {
        multi_int_set.insert(val);
    }
    
    std::cout << "multiset contents (sorted): ";
    for (const auto& value : multi_int_set) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Size: " << multi_int_set.size() << std::endl;
    std::cout << "Count of 5: " << multi_int_set.count(5) << std::endl;
    std::cout << "Count of 3: " << multi_int_set.count(3) << std::endl;
    
    // Find range of equal elements
    auto range = multi_int_set.equal_range(5);
    std::cout << "All occurrences of 5: ";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 4. multimap - Ordered multiple key-value pairs
    std::cout << "\n4. multimap - Ordered Multiple Key-Value Pairs:" << std::endl;
    
    std::multimap<std::string, int> student_grades;
    
    // Same student can have multiple grades
    student_grades.insert({"Alice", 85});
    student_grades.insert({"Bob", 92});
    student_grades.insert({"Alice", 78});
    student_grades.insert({"Charlie", 96});
    student_grades.insert({"Bob", 88});
    student_grades.insert({"Alice", 91});
    
    std::cout << "Student grades:" << std::endl;
    for (const auto& pair : student_grades) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    
    // Find all grades for a specific student
    std::cout << "\nAlice's grades: ";
    auto alice_range = student_grades.equal_range("Alice");
    for (auto it = alice_range.first; it != alice_range.second; ++it) {
        std::cout << it->second << " ";
    }
    std::cout << std::endl;
    
    // Calculate average grade for Alice
    double sum = 0;
    int count = 0;
    for (auto it = alice_range.first; it != alice_range.second; ++it) {
        sum += it->second;
        count++;
    }
    if (count > 0) {
        std::cout << "Alice's average: " << sum / count << std::endl;
    }
    
    // 5. Custom hash function with unordered containers
    std::cout << "\n5. Custom Hash Function with unordered_set:" << std::endl;
    
    std::unordered_set<Person, PersonHash> person_set;
    
    person_set.insert(Person("Alice", 30, "New York"));
    person_set.insert(Person("Bob", 25, "Chicago"));
    person_set.insert(Person("Charlie", 35, "Los Angeles"));
    person_set.insert(Person("Alice", 30, "New York"));  // Duplicate
    
    std::cout << "Unique persons:" << std::endl;
    for (const auto& person : person_set) {
        std::cout << "  ";
        person.display();
        std::cout << std::endl;
    }
    std::cout << "Total unique persons: " << person_set.size() << std::endl;
    
    // 6. unordered_map with custom objects
    std::cout << "\n6. unordered_map with Custom Objects:" << std::endl;
    
    std::unordered_map<Person, std::string, PersonHash> person_jobs;
    
    person_jobs[Person("Alice", 30, "New York")] = "Software Engineer";
    person_jobs[Person("Bob", 25, "Chicago")] = "Data Scientist";
    person_jobs[Person("Charlie", 35, "Los Angeles")] = "Product Manager";
    
    std::cout << "Person jobs:" << std::endl;
    for (const auto& pair : person_jobs) {
        std::cout << "  ";
        pair.first.display();
        std::cout << " -> " << pair.second << std::endl;
    }
    
    // 7. Container properties and bucket information
    std::cout << "\n7. Hash Container Properties:" << std::endl;
    
    std::unordered_set<int> hash_analysis;
    for (int i = 0; i < 20; ++i) {
        hash_analysis.insert(i);
    }
    
    std::cout << "Hash container analysis:" << std::endl;
    std::cout << "  Size: " << hash_analysis.size() << std::endl;
    std::cout << "  Bucket count: " << hash_analysis.bucket_count() << std::endl;
    std::cout << "  Load factor: " << hash_analysis.load_factor() << std::endl;
    std::cout << "  Max load factor: " << hash_analysis.max_load_factor() << std::endl;
    
    // Show bucket distribution
    std::cout << "  Bucket sizes: ";
    for (size_t i = 0; i < std::min(hash_analysis.bucket_count(), size_t(10)); ++i) {
        std::cout << hash_analysis.bucket_size(i) << " ";
    }
    std::cout << "..." << std::endl;
    
    // 8. Performance comparison: ordered vs unordered
    std::cout << "\n8. Performance Comparison (Ordered vs Unordered):" << std::endl;
    
    const int TEST_SIZE = 10000;
    std::vector<int> test_data;
    
    // Generate random test data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TEST_SIZE * 2);
    
    for (int i = 0; i < TEST_SIZE; ++i) {
        test_data.push_back(dis(gen));
    }
    
    // Test set vs unordered_set
    std::set<int> ordered_set;
    std::unordered_set<int> hash_set;
    
    double ordered_insert_time = measureInsertionTime(ordered_set, test_data);
    double hash_insert_time = measureInsertionTime(hash_set, test_data);
    
    std::cout << "Insertion time (" << TEST_SIZE << " elements):" << std::endl;
    std::cout << "  std::set: " << ordered_insert_time << " μs" << std::endl;
    std::cout << "  std::unordered_set: " << hash_insert_time << " μs" << std::endl;
    
    // Test lookup performance
    std::vector<int> lookup_data;
    for (int i = 0; i < 1000; ++i) {
        lookup_data.push_back(dis(gen));
    }
    
    double ordered_lookup_time = measureLookupTime(ordered_set, lookup_data);
    double hash_lookup_time = measureLookupTime(hash_set, lookup_data);
    
    std::cout << "Lookup time (1000 searches):" << std::endl;
    std::cout << "  std::set: " << ordered_lookup_time << " μs" << std::endl;
    std::cout << "  std::unordered_set: " << hash_lookup_time << " μs" << std::endl;
    
    // 9. Hash collisions and rehashing
    std::cout << "\n9. Hash Collisions and Rehashing:" << std::endl;
    
    std::unordered_map<int, std::string> rehash_demo;
    
    std::cout << "Initial bucket count: " << rehash_demo.bucket_count() << std::endl;
    
    // Force rehashing by adding many elements
    for (int i = 0; i < 100; ++i) {
        rehash_demo[i] = "value_" + std::to_string(i);
        
        if (i % 20 == 0) {
            std::cout << "After " << i << " insertions - Buckets: " 
                      << rehash_demo.bucket_count() << ", Load factor: " 
                      << rehash_demo.load_factor() << std::endl;
        }
    }
    
    // Manual rehashing
    std::cout << "\nManual rehash to 200 buckets:" << std::endl;
    rehash_demo.rehash(200);
    std::cout << "After rehash - Buckets: " << rehash_demo.bucket_count() 
              << ", Load factor: " << rehash_demo.load_factor() << std::endl;
    
    // 10. Advanced multimap/multiset usage
    std::cout << "\n10. Advanced multimap/multiset Usage:" << std::endl;
    
    // Event scheduling with multimap
    std::multimap<int, std::string> event_schedule;  // time -> event
    
    event_schedule.insert({9, "Team Meeting"});
    event_schedule.insert({10, "Code Review"});
    event_schedule.insert({9, "Coffee Break"});    // Same time, different event
    event_schedule.insert({14, "Project Planning"});
    event_schedule.insert({10, "Email Check"});    // Same time as Code Review
    
    std::cout << "Event schedule (sorted by time):" << std::endl;
    for (const auto& event : event_schedule) {
        std::cout << "  " << event.first << ":00 - " << event.second << std::endl;
    }
    
    // Find all events at 10:00
    std::cout << "\nEvents at 10:00:" << std::endl;
    auto events_at_10 = event_schedule.equal_range(10);
    for (auto it = events_at_10.first; it != events_at_10.second; ++it) {
        std::cout << "  " << it->second << std::endl;
    }
    
    // Remove specific event
    std::cout << "\nRemoving 'Email Check' from 10:00..." << std::endl;
    for (auto it = events_at_10.first; it != events_at_10.second; ++it) {
        if (it->second == "Email Check") {
            event_schedule.erase(it);
            break;
        }
    }
    
    std::cout << "Updated schedule:" << std::endl;
    for (const auto& event : event_schedule) {
        std::cout << "  " << event.first << ":00 - " << event.second << std::endl;
    }
    
    // 11. Container method comparison
    std::cout << "\n11. Container Method Comparison:" << std::endl;
    
    std::cout << "\nMethod availability:" << std::endl;
    std::cout << "Container         | find | count | bucket_* | rehash | equal_range" << std::endl;
    std::cout << "------------------|------|-------|----------|--------|-----------" << std::endl;
    std::cout << "set               |  ✓   |   ✓   |    ✗     |   ✗    |     ✓" << std::endl;
    std::cout << "multiset          |  ✓   |   ✓   |    ✗     |   ✗    |     ✓" << std::endl;
    std::cout << "map               |  ✓   |   ✓   |    ✗     |   ✗    |     ✓" << std::endl;
    std::cout << "multimap          |  ✓   |   ✓   |    ✗     |   ✗    |     ✓" << std::endl;
    std::cout << "unordered_set     |  ✓   |   ✓   |    ✓     |   ✓    |     ✓" << std::endl;
    std::cout << "unordered_map     |  ✓   |   ✓   |    ✓     |   ✓    |     ✓" << std::endl;
    
    // 12. Real-world usage patterns
    std::cout << "\n12. Real-World Usage Patterns:" << std::endl;
    
    // Word frequency analysis
    std::cout << "\nWord frequency analysis:" << std::endl;
    std::string text = "the quick brown fox jumps over the lazy dog the fox is quick";
    std::unordered_map<std::string, int> frequency;
    
    // Simple tokenization
    std::string word;
    for (char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                frequency[word]++;
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        frequency[word]++;
    }
    
    // Sort by frequency (move to vector for sorting)
    std::vector<std::pair<std::string, int>> word_freq(frequency.begin(), frequency.end());
    std::sort(word_freq.begin(), word_freq.end(), 
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::cout << "Most frequent words:" << std::endl;
    for (const auto& pair : word_freq) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    
    std::cout << "\n=== CONTAINER COMPARISON SUMMARY ===" << std::endl;
    std::cout << "\nOrdered Containers (Tree-based):" << std::endl;
    std::cout << "✅ Guaranteed sorted order" << std::endl;
    std::cout << "✅ O(log n) insert, find, delete" << std::endl;
    std::cout << "✅ Range operations (lower_bound, upper_bound)" << std::endl;
    std::cout << "✅ Stable iteration order" << std::endl;
    std::cout << "⚠️  Slower than hash containers for basic operations" << std::endl;
    
    std::cout << "\nUnordered Containers (Hash-based):" << std::endl;
    std::cout << "✅ Average O(1) insert, find, delete" << std::endl;
    std::cout << "✅ Faster for basic operations" << std::endl;
    std::cout << "✅ Bucket-based organization" << std::endl;
    std::cout << "⚠️  No guaranteed iteration order" << std::endl;
    std::cout << "⚠️  Worst case O(n) if hash collisions" << std::endl;
    std::cout << "⚠️  Requires good hash function" << std::endl;
    
    std::cout << "\nMulti-containers:" << std::endl;
    std::cout << "✅ Allow duplicate keys/values" << std::endl;
    std::cout << "✅ equal_range() for finding all duplicates" << std::endl;
    std::cout << "✅ count() returns actual number of elements" << std::endl;
    std::cout << "⚠️  No operator[] (would be ambiguous)" << std::endl;
    
    std::cout << "\nWhen to use what:" << std::endl;
    std::cout << "🔹 unordered_map/set: Fast lookups, order doesn't matter" << std::endl;
    std::cout << "🔹 map/set: Need sorted order, range queries" << std::endl;
    std::cout << "🔹 multimap/multiset: Multiple values per key" << std::endl;
    std::cout << "🔹 Custom hash: For user-defined types in unordered containers" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++11 -Wall -Wextra -O2 -o unordered_containers_demo unordered_containers_demo.cpp
./unordered_containers_demo

New C++11 Containers:
1. unordered_set: Hash-based set, O(1) average operations
2. unordered_map: Hash-based map, O(1) average operations
3. unordered_multiset: Hash-based multiset (C++11)
4. unordered_multimap: Hash-based multimap (C++11)

Existing containers enhanced:
- multiset: Now with more methods and better performance
- multimap: Enhanced with improved algorithms

Key Features:
- Hash-based containers for O(1) average performance
- Custom hash functions for user-defined types
- Bucket-based organization with load factor management
- Rehashing support for optimal performance
- equal_range() for multi-containers

Performance Benefits:
- Significantly faster lookups for large datasets
- Better cache locality in some scenarios
- Configurable load factors and bucket counts

Best Practices:
- Use unordered_* for fast lookups when order doesn't matter
- Use map/set when you need sorted iteration
- Implement good hash functions for custom types
- Monitor load factors for optimal performance
- Use multi-containers when you need duplicate keys
*/
