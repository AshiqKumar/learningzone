// STL Iterators Comprehensive Reference
// Compile: g++ -std=c++20 -o iterators_complete iterators_complete.cpp
// Run: ./iterators_complete

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <forward_list>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <sstream>

void demonstrate_iterator_categories() {
    std::cout << "\n=== ITERATOR CATEGORIES ===" << std::endl;
    
    // 1. Input Iterators - Read-only, single pass
    {
        std::cout << "\n1. Input Iterators (read-only, single pass):" << std::endl;
        
        std::istringstream iss("10 20 30 40 50");
        std::istream_iterator<int> input_it(iss);
        std::istream_iterator<int> input_end;
        
        std::cout << "Reading from stream: ";
        while (input_it != input_end) {
            std::cout << *input_it << " ";
            ++input_it;
        }
        std::cout << std::endl;
        
        std::cout << "✅ Can read (*it)" << std::endl;
        std::cout << "✅ Can increment (++it)" << std::endl;
        std::cout << "❌ Cannot write" << std::endl;
        std::cout << "❌ Cannot decrement" << std::endl;
        std::cout << "❌ Single pass only" << std::endl;
    }
    
    // 2. Output Iterators - Write-only, single pass
    {
        std::cout << "\n2. Output Iterators (write-only, single pass):" << std::endl;
        
        std::vector<int> source = {1, 2, 3, 4, 5};
        std::ostringstream oss;
        
        std::copy(source.begin(), source.end(), 
                  std::ostream_iterator<int>(oss, " "));
        
        std::cout << "Written to stream: " << oss.str() << std::endl;
        
        std::cout << "✅ Can write (*it = value)" << std::endl;
        std::cout << "✅ Can increment (++it)" << std::endl;
        std::cout << "❌ Cannot read" << std::endl;
        std::cout << "❌ Cannot decrement" << std::endl;
        std::cout << "❌ Single pass only" << std::endl;
    }
    
    // 3. Forward Iterators - Read/write, multi-pass
    {
        std::cout << "\n3. Forward Iterators (multi-pass, forward only):" << std::endl;
        
        std::forward_list<int> flist = {1, 2, 3, 4, 5};
        
        std::cout << "Forward list: ";
        for (auto it = flist.begin(); it != flist.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Modify elements
        for (auto it = flist.begin(); it != flist.end(); ++it) {
            *it *= 2;
        }
        
        std::cout << "After doubling: ";
        for (int val : flist) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        
        std::cout << "✅ Can read and write" << std::endl;
        std::cout << "✅ Multi-pass (can iterate multiple times)" << std::endl;
        std::cout << "✅ Can increment (++it)" << std::endl;
        std::cout << "❌ Cannot decrement" << std::endl;
        std::cout << "❌ No random access" << std::endl;
    }
    
    // 4. Bidirectional Iterators - Forward + backward
    {
        std::cout << "\n4. Bidirectional Iterators (forward and backward):" << std::endl;
        
        std::list<int> lst = {1, 2, 3, 4, 5};
        
        std::cout << "Forward: ";
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Backward: ";
        for (auto it = lst.rbegin(); it != lst.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Using reverse iteration with regular iterators
        std::cout << "Reverse with regular iterators: ";
        auto it = lst.end();
        while (it != lst.begin()) {
            --it;
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        std::cout << "✅ Can read and write" << std::endl;
        std::cout << "✅ Can increment (++it) and decrement (--it)" << std::endl;
        std::cout << "✅ Multi-pass" << std::endl;
        std::cout << "❌ No random access (no +/- integers)" << std::endl;
    }
    
    // 5. Random Access Iterators - Full functionality
    {
        std::cout << "\n5. Random Access Iterators (full functionality):" << std::endl;
        
        std::vector<int> vec = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        
        std::cout << "Vector: ";
        for (int val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        
        auto it = vec.begin();
        std::cout << "it[0]: " << it[0] << std::endl;
        std::cout << "it[5]: " << it[5] << std::endl;
        std::cout << "*(it + 3): " << *(it + 3) << std::endl;
        
        auto it2 = it + 7;
        std::cout << "Distance between iterators: " << (it2 - it) << std::endl;
        
        // Comparison operations
        std::cout << "it < it2: " << std::boolalpha << (it < it2) << std::endl;
        std::cout << "it + 5 >= it2: " << (it + 5 >= it2) << std::endl;
        
        std::cout << "✅ All bidirectional features" << std::endl;
        std::cout << "✅ Random access (it[n], it+n, it-n)" << std::endl;
        std::cout << "✅ Iterator arithmetic (it1 - it2)" << std::endl;
        std::cout << "✅ Comparison operators (<, <=, >, >=)" << std::endl;
    }
}

void demonstrate_iterator_adapters() {
    std::cout << "\n=== ITERATOR ADAPTERS ===" << std::endl;
    
    // 1. Reverse Iterators
    {
        std::cout << "\n1. Reverse Iterators:" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5};
        
        std::cout << "Forward: ";
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Reverse: ";
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Manual reverse iterator creation
        std::cout << "Manual reverse: ";
        std::reverse_iterator<std::vector<int>::iterator> rev_it(vec.end());
        std::reverse_iterator<std::vector<int>::iterator> rev_end(vec.begin());
        
        for (auto it = rev_it; it != rev_end; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    // 2. Insert Iterators
    {
        std::cout << "\n2. Insert Iterators:" << std::endl;
        
        std::vector<int> source = {1, 2, 3, 4, 5};
        std::vector<int> dest;
        std::list<int> dest_list;
        
        // Back insert iterator
        std::cout << "Using back_inserter:" << std::endl;
        std::copy(source.begin(), source.end(), std::back_inserter(dest));
        std::cout << "dest: ";
        for (int val : dest) std::cout << val << " ";
        std::cout << std::endl;
        
        // Front insert iterator (for containers that support push_front)
        std::cout << "Using front_inserter:" << std::endl;
        std::copy(source.begin(), source.end(), std::front_inserter(dest_list));
        std::cout << "dest_list: ";
        for (int val : dest_list) std::cout << val << " ";
        std::cout << std::endl;
        
        // General insert iterator
        std::cout << "Using inserter:" << std::endl;
        std::vector<int> dest2 = {100, 200};
        auto insert_pos = dest2.begin() + 1; // Insert after 100
        std::copy(source.begin(), source.begin() + 3, 
                  std::inserter(dest2, insert_pos));
        std::cout << "dest2: ";
        for (int val : dest2) std::cout << val << " ";
        std::cout << std::endl;
    }
    
    // 3. Stream Iterators
    {
        std::cout << "\n3. Stream Iterators:" << std::endl;
        
        // Input stream iterator
        std::string input_data = "10 20 30 40 50";
        std::istringstream iss(input_data);
        
        std::vector<int> numbers;
        std::copy(std::istream_iterator<int>(iss),
                  std::istream_iterator<int>(),
                  std::back_inserter(numbers));
        
        std::cout << "Read from stream: ";
        for (int val : numbers) std::cout << val << " ";
        std::cout << std::endl;
        
        // Output stream iterator
        std::ostringstream oss;
        std::copy(numbers.begin(), numbers.end(),
                  std::ostream_iterator<int>(oss, ", "));
        
        std::cout << "Written to stream: " << oss.str() << std::endl;
    }
    
    // 4. Move Iterator (C++11)
    {
        std::cout << "\n4. Move Iterator:" << std::endl;
        
        std::vector<std::string> source = {"apple", "banana", "cherry", "date"};
        std::vector<std::string> dest;
        
        std::cout << "Before move - source: ";
        for (const auto& s : source) std::cout << "'" << s << "' ";
        std::cout << std::endl;
        
        // Use move iterator to move elements instead of copying
        std::copy(std::make_move_iterator(source.begin()),
                  std::make_move_iterator(source.end()),
                  std::back_inserter(dest));
        
        std::cout << "After move - dest: ";
        for (const auto& s : dest) std::cout << "'" << s << "' ";
        std::cout << std::endl;
        
        std::cout << "After move - source: ";
        for (const auto& s : source) std::cout << "'" << s << "' ";
        std::cout << std::endl;
    }
}

void demonstrate_iterator_operations() {
    std::cout << "\n=== ITERATOR OPERATIONS ===" << std::endl;
    
    // 1. advance and distance
    {
        std::cout << "\n1. advance and distance:" << std::endl;
        
        std::vector<int> vec = {10, 20, 30, 40, 50, 60, 70, 80};
        
        auto it = vec.begin();
        std::cout << "Initial position: " << *it << std::endl;
        
        std::advance(it, 3); // Move iterator forward by 3
        std::cout << "After advance(3): " << *it << std::endl;
        
        std::advance(it, -2); // Move iterator backward by 2
        std::cout << "After advance(-2): " << *it << std::endl;
        
        auto distance = std::distance(vec.begin(), it);
        std::cout << "Distance from begin: " << distance << std::endl;
        
        // With bidirectional iterators (list)
        std::list<int> lst = {1, 2, 3, 4, 5};
        auto list_it = lst.begin();
        std::advance(list_it, 2);
        std::cout << "List iterator after advance(2): " << *list_it << std::endl;
    }
    
    // 2. next and prev (C++11)
    {
        std::cout << "\n2. next and prev:" << std::endl;
        
        std::vector<int> vec = {10, 20, 30, 40, 50};
        
        auto it = vec.begin();
        std::cout << "Current: " << *it << std::endl;
        
        auto next_it = std::next(it, 2); // Get iterator 2 positions ahead
        std::cout << "Next(2): " << *next_it << std::endl;
        
        auto prev_it = std::prev(vec.end(), 1); // Get iterator 1 position back from end
        std::cout << "Prev from end(1): " << *prev_it << std::endl;
        
        // Original iterator unchanged
        std::cout << "Original iterator still: " << *it << std::endl;
    }
    
    // 3. Iterator traits
    {
        std::cout << "\n3. Iterator Traits:" << std::endl;
        
        using VecIter = std::vector<int>::iterator;
        using ListIter = std::list<int>::iterator;
        
        std::cout << "Vector iterator category: ";
        if (std::is_same_v<std::iterator_traits<VecIter>::iterator_category,
                          std::random_access_iterator_tag>) {
            std::cout << "Random Access" << std::endl;
        }
        
        std::cout << "List iterator category: ";
        if (std::is_same_v<std::iterator_traits<ListIter>::iterator_category,
                          std::bidirectional_iterator_tag>) {
            std::cout << "Bidirectional" << std::endl;
        }
        
        // Value type
        using ValueType = std::iterator_traits<VecIter>::value_type;
        std::cout << "Vector iterator value type size: " << sizeof(ValueType) << std::endl;
    }
}

void demonstrate_custom_iterators() {
    std::cout << "\n=== CUSTOM ITERATORS ===" << std::endl;
    
    // Simple range iterator
    class Range {
    public:
        class iterator {
        private:
            int current_;
            
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = int;
            using difference_type = std::ptrdiff_t;
            using pointer = int*;
            using reference = int&;
            
            explicit iterator(int start) : current_(start) {}
            
            int operator*() const { return current_; }
            
            iterator& operator++() {
                ++current_;
                return *this;
            }
            
            iterator operator++(int) {
                iterator temp = *this;
                ++current_;
                return temp;
            }
            
            bool operator==(const iterator& other) const {
                return current_ == other.current_;
            }
            
            bool operator!=(const iterator& other) const {
                return current_ != other.current_;
            }
        };
        
    private:
        int start_, end_;
        
    public:
        Range(int start, int end) : start_(start), end_(end) {}
        
        iterator begin() const { return iterator(start_); }
        iterator end() const { return iterator(end_); }
    };
    
    std::cout << "\n1. Custom Range Iterator:" << std::endl;
    
    Range range(1, 6);
    std::cout << "Range [1, 6): ";
    for (int val : range) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Use with STL algorithms
    auto count = std::count_if(range.begin(), range.end(), 
                              [](int x) { return x % 2 == 0; });
    std::cout << "Even numbers in range: " << count << std::endl;
}

void demonstrate_iterator_patterns() {
    std::cout << "\n=== COMMON ITERATOR PATTERNS ===" << std::endl;
    
    // 1. Erase-remove idiom
    {
        std::cout << "\n1. Erase-Remove Idiom:" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 2, 4, 2, 5, 6};
        
        std::cout << "Before: ";
        for (int val : vec) std::cout << val << " ";
        std::cout << std::endl;
        
        // Remove all 2s
        auto new_end = std::remove(vec.begin(), vec.end(), 2);
        vec.erase(new_end, vec.end());
        
        std::cout << "After removing 2s: ";
        for (int val : vec) std::cout << val << " ";
        std::cout << std::endl;
    }
    
    // 2. Safe iteration with erase
    {
        std::cout << "\n2. Safe Iteration with Erase:" << std::endl;
        
        std::map<int, std::string> data = {
            {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}
        };
        
        std::cout << "Before: ";
        for (const auto& pair : data) {
            std::cout << "{" << pair.first << ":" << pair.second << "} ";
        }
        std::cout << std::endl;
        
        // Remove even keys
        for (auto it = data.begin(); it != data.end();) {
            if (it->first % 2 == 0) {
                it = data.erase(it); // erase returns next valid iterator
            } else {
                ++it;
            }
        }
        
        std::cout << "After removing even keys: ";
        for (const auto& pair : data) {
            std::cout << "{" << pair.first << ":" << pair.second << "} ";
        }
        std::cout << std::endl;
    }
    
    // 3. Iterator debugging
    {
        std::cout << "\n3. Iterator Validity:" << std::endl;
        
        std::vector<int> vec = {1, 2, 3, 4, 5};
        auto it = vec.begin() + 2;
        
        std::cout << "Iterator points to: " << *it << std::endl;
        
        // Operations that may invalidate iterators
        vec.push_back(6); // May invalidate if reallocation occurs
        
        // Check if iterator is still valid (position-based)
        if (std::distance(vec.begin(), vec.end()) > 2) {
            auto new_it = vec.begin() + 2;
            std::cout << "New iterator points to: " << *new_it << std::endl;
        }
        
        std::cout << "⚠️  Iterator invalidation rules:" << std::endl;
        std::cout << "   • vector: push_back may invalidate all" << std::endl;
        std::cout << "   • list: only erased iterators invalidated" << std::endl;
        std::cout << "   • deque: push_front/back may invalidate all" << std::endl;
        std::cout << "   • map/set: only erased iterators invalidated" << std::endl;
    }
    
    // 4. Iterator-based algorithms composition
    {
        std::cout << "\n4. Algorithm Composition:" << std::endl;
        
        std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6, 0};
        
        std::cout << "Original: ";
        for (int val : data) std::cout << val << " ";
        std::cout << std::endl;
        
        // Chain operations: remove zeros, sort, then take first 5
        auto new_end = std::remove(data.begin(), data.end(), 0);
        data.erase(new_end, data.end());
        
        std::sort(data.begin(), data.end());
        
        if (data.size() > 5) {
            data.erase(data.begin() + 5, data.end());
        }
        
        std::cout << "Processed (no zeros, sorted, first 5): ";
        for (int val : data) std::cout << val << " ";
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "=== COMPLETE STL ITERATORS REFERENCE ===" << std::endl;
    
    demonstrate_iterator_categories();
    demonstrate_iterator_adapters();
    demonstrate_iterator_operations();
    demonstrate_custom_iterators();
    demonstrate_iterator_patterns();
    
    std::cout << "\n=== ITERATOR SUMMARY ===" << std::endl;
    std::cout << "🔹 **Iterator Categories (weakest to strongest):**" << std::endl;
    std::cout << "   • Input: read-only, single pass (istream_iterator)" << std::endl;
    std::cout << "   • Output: write-only, single pass (ostream_iterator)" << std::endl;
    std::cout << "   • Forward: read/write, multi-pass (forward_list)" << std::endl;
    std::cout << "   • Bidirectional: forward + backward (list, set, map)" << std::endl;
    std::cout << "   • Random Access: full functionality (vector, deque, array)" << std::endl;
    
    std::cout << "\n🔹 **Iterator Adapters:**" << std::endl;
    std::cout << "   • Reverse: iterate backwards (rbegin/rend)" << std::endl;
    std::cout << "   • Insert: insert instead of overwrite (back_inserter)" << std::endl;
    std::cout << "   • Stream: read/write from streams (istream/ostream_iterator)" << std::endl;
    std::cout << "   • Move: move instead of copy (make_move_iterator)" << std::endl;
    
    std::cout << "\n🔹 **Key Operations:**" << std::endl;
    std::cout << "   • advance(it, n): move iterator n steps" << std::endl;
    std::cout << "   • distance(first, last): count steps between iterators" << std::endl;
    std::cout << "   • next(it, n): get iterator n steps ahead" << std::endl;
    std::cout << "   • prev(it, n): get iterator n steps back" << std::endl;
    
    std::cout << "\n🔹 **Best Practices:**" << std::endl;
    std::cout << "   • Use iterator_traits for generic code" << std::endl;
    std::cout << "   • Be aware of iterator invalidation rules" << std::endl;
    std::cout << "   • Use const_iterator when not modifying" << std::endl;
    std::cout << "   • Prefer range-based for loops when appropriate" << std::endl;
    std::cout << "   • Use erase-remove idiom for element removal" << std::endl;
    
    return 0;
}

/*
ITERATOR PERFORMANCE CHARACTERISTICS:

Category Capabilities:
Input Iterator:
- Operations: ==, !=, *, ++
- Single pass only
- Read-only access

Output Iterator:
- Operations: *, ++, = (assignment)
- Single pass only
- Write-only access

Forward Iterator:
- All input iterator operations
- Multi-pass iteration
- Default constructible

Bidirectional Iterator:
- All forward iterator operations
- Additional: --
- Can iterate backwards

Random Access Iterator:
- All bidirectional iterator operations
- Additional: +, -, +=, -=, [], <, >, <=, >=
- Constant time random access

Container Iterator Categories:
- array, vector, deque: Random Access
- list, set, map, multiset, multimap: Bidirectional
- forward_list: Forward
- unordered_set, unordered_map: Forward
- input streams: Input
- output streams: Output

Iterator Invalidation Rules:
Vector/String:
- insert/push_back: may invalidate all if reallocation
- erase: invalidates from erased position to end

Deque:
- push_front/back: may invalidate all iterators
- insert: invalidates all
- erase at ends: only erased iterator
- erase in middle: all iterators

List/Forward_list:
- insert: no invalidation
- erase: only erased iterators

Associative containers (set, map):
- insert: no invalidation
- erase: only erased iterators

Unordered containers:
- insert: may invalidate all if rehashing
- erase: only erased iterators
*/
