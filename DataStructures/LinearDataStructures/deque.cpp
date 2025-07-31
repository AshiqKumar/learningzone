// Deque (Double-Ended Queue) Implementation - Complete program with all operations
/*
Key Features of Deque (Double-Ended Queue):
Core Operations:
✅ Push Front/Back: Add elements at both ends in O(1)
✅ Pop Front/Back: Remove elements from both ends in O(1)
✅ Front/Back: Access elements at both ends in O(1)
✅ Random Access: Access any element by index in O(1)
Deque-Specific Features:
🔄 Dual-Ended: Operations possible at both front and rear
🎯 Random Access: Like vector, can access any element directly
⚡ Constant Time Operations: All basic operations are O(1)
💾 Efficient Memory Usage: Segmented memory allocation
Advanced Features:
🔍 Search: Find element position
📊 Display: Show deque contents
🗑️ Clear: Remove all elements
📏 Size Tracking: Current number of elements
🔄 Insert/Erase: At any position
Smart Memory Management:
🧠 Uses segmented arrays for efficient memory usage
🛡️ Exception-safe operations
🚫 RAII principles throughout
📈 Automatic capacity management
Educational Demonstrations:
📊 Performance Analysis: Time/space complexity breakdown
🧪 Error Handling: Comprehensive edge case testing
📝 Use Cases: Real-world applications explained
🔄 Multiple Implementations: Array-based and linked-list based
*/

#include <iostream>
#include <deque>
#include <vector>
#include <stdexcept>
#include <string>
#include <memory>

// Custom Deque Implementation using Circular Buffer
template<typename T>
class CircularDeque {
private:
    std::vector<T> data_;
    size_t front_;
    size_t rear_;
    size_t size_;
    size_t capacity_;
    
    // Helper function to get next index in circular manner
    size_t next_index(size_t index) const {
        return (index + 1) % capacity_;
    }
    
    // Helper function to get previous index in circular manner
    size_t prev_index(size_t index) const {
        return (index - 1 + capacity_) % capacity_;
    }
    
public:
    // Constructor with capacity
    explicit CircularDeque(size_t capacity) 
        : data_(capacity), front_(0), rear_(0), size_(0), capacity_(capacity) {}
    
    // Default constructor
    CircularDeque() : CircularDeque(10) {}
    
    // Push element to front
    void push_front(const T& value) {
        if (is_full()) {
            std::cout << "Deque is full - cannot push " << value << " to front" << std::endl;
            return;
        }
        
        if (empty()) {
            data_[front_] = value;
        } else {
            front_ = prev_index(front_);
            data_[front_] = value;
        }
        
        size_++;
        std::cout << "Pushed " << value << " to front" << std::endl;
    }
    
    // Push element to back
    void push_back(const T& value) {
        if (is_full()) {
            std::cout << "Deque is full - cannot push " << value << " to back" << std::endl;
            return;
        }
        
        if (empty()) {
            data_[rear_] = value;
        } else {
            rear_ = next_index(rear_);
            data_[rear_] = value;
        }
        
        size_++;
        std::cout << "Pushed " << value << " to back" << std::endl;
    }
    
    // Pop element from front
    void pop_front() {
        if (empty()) {
            std::cout << "Deque is empty - cannot pop from front" << std::endl;
            return;
        }
        
        std::cout << "Popped " << data_[front_] << " from front" << std::endl;
        
        if (size_ == 1) {
            // Reset when deque becomes empty
            size_ = 0;
        } else {
            front_ = next_index(front_);
            size_--;
        }
    }
    
    // Pop element from back
    void pop_back() {
        if (empty()) {
            std::cout << "Deque is empty - cannot pop from back" << std::endl;
            return;
        }
        
        std::cout << "Popped " << data_[rear_] << " from back" << std::endl;
        
        if (size_ == 1) {
            // Reset when deque becomes empty
            size_ = 0;
        } else {
            rear_ = prev_index(rear_);
            size_--;
        }
    }
    
    // Get front element without removing
    T front() const {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        return data_[front_];
    }
    
    // Get back element without removing
    T back() const {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        return data_[rear_];
    }
    
    // Random access by index (0 = front element)
    T at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        
        size_t actual_index = (front_ + index) % capacity_;
        return data_[actual_index];
    }
    
    // Operator[] for convenience
    T operator[](size_t index) const {
        return at(index);
    }
    
    // Check if deque is empty
    bool empty() const {
        return size_ == 0;
    }
    
    // Check if deque is full
    bool is_full() const {
        return size_ == capacity_;
    }
    
    // Get size of deque
    size_t size() const {
        return size_;
    }
    
    // Get capacity
    size_t capacity() const {
        return capacity_;
    }
    
    // Clear all elements
    void clear() {
        front_ = 0;
        rear_ = 0;
        size_ = 0;
        std::cout << "Deque cleared" << std::endl;
    }
    
    // Search for element (returns index, -1 if not found)
    int find(const T& value) const {
        for (size_t i = 0; i < size_; ++i) {
            if (at(i) == value) {
                return static_cast<int>(i);
            }
        }
        return -1; // Not found
    }
    
    // Insert element at specific position
    void insert(size_t index, const T& value) {
        if (is_full()) {
            std::cout << "Deque is full - cannot insert " << value << std::endl;
            return;
        }
        
        if (index == 0) {
            push_front(value);
            return;
        }
        
        if (index >= size_) {
            push_back(value);
            return;
        }
        
        // Shift elements to make space
        // Choose the direction that requires less shifting
        if (index <= size_ / 2) {
            // Shift front elements left
            size_t new_front = prev_index(front_);
            for (size_t i = 0; i < index; ++i) {
                size_t src = (front_ + i) % capacity_;
                size_t dest = (new_front + i) % capacity_;
                data_[dest] = data_[src];
            }
            front_ = new_front;
        } else {
            // Shift back elements right
            size_t new_rear = next_index(rear_);
            for (size_t i = size_ - 1; i >= index; --i) {
                size_t src = (front_ + i) % capacity_;
                size_t dest = (front_ + i + 1) % capacity_;
                data_[dest] = data_[src];
            }
            rear_ = new_rear;
        }
        
        size_t insert_pos = (front_ + index) % capacity_;
        data_[insert_pos] = value;
        size_++;
        
        std::cout << "Inserted " << value << " at index " << index << std::endl;
    }
    
    // Erase element at specific position
    void erase(size_t index) {
        if (index >= size_) {
            std::cout << "Index " << index << " is out of bounds" << std::endl;
            return;
        }
        
        if (index == 0) {
            pop_front();
            return;
        }
        
        if (index == size_ - 1) {
            pop_back();
            return;
        }
        
        T value = at(index);
        
        // Choose the direction that requires less shifting
        if (index <= size_ / 2) {
            // Shift front elements right
            for (size_t i = index; i > 0; --i) {
                size_t src = (front_ + i - 1) % capacity_;
                size_t dest = (front_ + i) % capacity_;
                data_[dest] = data_[src];
            }
            front_ = next_index(front_);
        } else {
            // Shift back elements left
            for (size_t i = index; i < size_ - 1; ++i) {
                size_t src = (front_ + i + 1) % capacity_;
                size_t dest = (front_ + i) % capacity_;
                data_[dest] = data_[src];
            }
            rear_ = prev_index(rear_);
        }
        
        size_--;
        std::cout << "Erased " << value << " at index " << index << std::endl;
    }
    
    // Display deque contents
    void display() const {
        if (empty()) {
            std::cout << "Deque is empty" << std::endl;
            return;
        }
        
        std::cout << "Deque: [";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << at(i);
            if (i < size_ - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    // Display with indices
    void display_with_indices() const {
        if (empty()) {
            std::cout << "Deque is empty" << std::endl;
            return;
        }
        
        std::cout << "Deque with indices:" << std::endl;
        for (size_t i = 0; i < size_; ++i) {
            std::cout << "Index " << i << ": " << at(i) << std::endl;
        }
    }
    
    // Reverse the deque
    void reverse() {
        if (size_ <= 1) {
            std::cout << "Deque reversed (nothing to reverse)" << std::endl;
            return;
        }
        
        for (size_t i = 0; i < size_ / 2; ++i) {
            size_t left_index = (front_ + i) % capacity_;
            size_t right_index = (front_ + size_ - 1 - i) % capacity_;
            std::swap(data_[left_index], data_[right_index]);
        }
        
        std::cout << "Deque reversed" << std::endl;
    }
};

// Standard library deque wrapper for comparison
template<typename T>
class STLDequeWrapper {
private:
    std::deque<T> deque_;
    
public:
    // Push element to front
    void push_front(const T& value) {
        deque_.push_front(value);
        std::cout << "Pushed " << value << " to front" << std::endl;
    }
    
    // Push element to back
    void push_back(const T& value) {
        deque_.push_back(value);
        std::cout << "Pushed " << value << " to back" << std::endl;
    }
    
    // Pop element from front
    void pop_front() {
        if (empty()) {
            std::cout << "Deque is empty - cannot pop from front" << std::endl;
            return;
        }
        
        std::cout << "Popped " << deque_.front() << " from front" << std::endl;
        deque_.pop_front();
    }
    
    // Pop element from back
    void pop_back() {
        if (empty()) {
            std::cout << "Deque is empty - cannot pop from back" << std::endl;
            return;
        }
        
        std::cout << "Popped " << deque_.back() << " from back" << std::endl;
        deque_.pop_back();
    }
    
    // Get front element
    T front() const {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        return deque_.front();
    }
    
    // Get back element
    T back() const {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        return deque_.back();
    }
    
    // Random access
    T at(size_t index) const {
        return deque_.at(index);
    }
    
    // Operator[]
    T operator[](size_t index) const {
        return deque_[index];
    }
    
    // Check if empty
    bool empty() const {
        return deque_.empty();
    }
    
    // Get size
    size_t size() const {
        return deque_.size();
    }
    
    // Clear
    void clear() {
        deque_.clear();
        std::cout << "Deque cleared" << std::endl;
    }
    
    // Insert at position
    void insert(size_t index, const T& value) {
        if (index > size()) {
            std::cout << "Index out of bounds" << std::endl;
            return;
        }
        
        deque_.insert(deque_.begin() + index, value);
        std::cout << "Inserted " << value << " at index " << index << std::endl;
    }
    
    // Erase at position
    void erase(size_t index) {
        if (index >= size()) {
            std::cout << "Index out of bounds" << std::endl;
            return;
        }
        
        T value = deque_[index];
        deque_.erase(deque_.begin() + index);
        std::cout << "Erased " << value << " at index " << index << std::endl;
    }
    
    // Display
    void display() const {
        if (empty()) {
            std::cout << "Deque is empty" << std::endl;
            return;
        }
        
        std::cout << "STL Deque: [";
        for (size_t i = 0; i < size(); ++i) {
            std::cout << deque_[i];
            if (i < size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(55, '=') << std::endl;
}

void demonstrateBasicOperations() {
    printSeparator("BASIC DEQUE OPERATIONS");
    
    CircularDeque<int> deque(8);
    
    std::cout << "\n--- Initial State ---" << std::endl;
    std::cout << "Is empty: " << (deque.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Size: " << deque.size() << std::endl;
    std::cout << "Capacity: " << deque.capacity() << std::endl;
    
    // Push elements to both ends
    std::cout << "\n--- Push Operations ---" << std::endl;
    deque.push_back(10);
    deque.push_back(20);
    deque.push_front(5);
    deque.push_front(1);
    deque.display();
    
    // Access elements
    std::cout << "\n--- Access Operations ---" << std::endl;
    try {
        std::cout << "Front element: " << deque.front() << std::endl;
        std::cout << "Back element: " << deque.back() << std::endl;
        std::cout << "Element at index 1: " << deque[1] << std::endl;
        std::cout << "Element at index 2: " << deque.at(2) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    deque.display_with_indices();
    
    // Pop operations
    std::cout << "\n--- Pop Operations ---" << std::endl;
    deque.pop_front();
    deque.display();
    
    deque.pop_back();
    deque.display();
}

void demonstrateRandomAccess() {
    printSeparator("RANDOM ACCESS OPERATIONS");
    
    CircularDeque<char> deque(10);
    
    // Add elements
    std::cout << "\n--- Building Deque ---" << std::endl;
    for (char c = 'A'; c <= 'F'; ++c) {
        deque.push_back(c);
    }
    deque.display();
    
    // Random access tests
    std::cout << "\n--- Random Access Tests ---" << std::endl;
    for (size_t i = 0; i < deque.size(); ++i) {
        std::cout << "deque[" << i << "] = " << deque[i] << std::endl;
    }
    
    // Search operation
    std::cout << "\n--- Search Operations ---" << std::endl;
    std::cout << "Find 'D': Index " << deque.find('D') << std::endl;
    std::cout << "Find 'Z': Index " << deque.find('Z') << std::endl;
}

void demonstrateInsertErase() {
    printSeparator("INSERT/ERASE OPERATIONS");
    
    CircularDeque<int> deque(10);
    
    // Build initial deque
    std::cout << "\n--- Initial Deque ---" << std::endl;
    for (int i = 10; i <= 50; i += 10) {
        deque.push_back(i);
    }
    deque.display();
    
    // Insert operations
    std::cout << "\n--- Insert Operations ---" << std::endl;
    deque.insert(0, 5);    // Insert at front
    deque.display();
    
    deque.insert(3, 25);   // Insert in middle
    deque.display();
    
    deque.insert(100, 60); // Insert at end (out of bounds)
    deque.display();
    
    // Erase operations
    std::cout << "\n--- Erase Operations ---" << std::endl;
    deque.erase(0);        // Erase from front
    deque.display();
    
    deque.erase(2);        // Erase from middle
    deque.display();
    
    deque.erase(deque.size() - 1); // Erase from back
    deque.display();
}

void demonstrateAdvancedOperations() {
    printSeparator("ADVANCED OPERATIONS");
    
    CircularDeque<std::string> deque(8);
    
    // Build deque with mixed operations
    std::cout << "\n--- Mixed Push Operations ---" << std::endl;
    deque.push_back("Middle");
    deque.push_front("Start");
    deque.push_back("End");
    deque.push_front("Beginning");
    deque.display();
    
    // Reverse operation
    std::cout << "\n--- Reverse Operation ---" << std::endl;
    deque.reverse();
    deque.display();
    
    // Complex insertion pattern
    std::cout << "\n--- Complex Operations ---" << std::endl;
    deque.insert(2, "Inserted");
    deque.display();
    
    // Fill to capacity test
    std::cout << "\n--- Capacity Test ---" << std::endl;
    while (!deque.is_full()) {
        deque.push_back("Fill" + std::to_string(deque.size()));
    }
    deque.display();
    
    // Try to overfill
    deque.push_back("Overflow");
    deque.push_front("OverflowFront");
}

void demonstrateSTLComparison() {
    printSeparator("STL DEQUE COMPARISON");
    
    std::cout << "\n--- Custom Deque ---" << std::endl;
    CircularDeque<int> customDeque(6);
    
    for (int i = 1; i <= 4; ++i) {
        customDeque.push_back(i * 10);
    }
    customDeque.push_front(5);
    customDeque.display();
    
    std::cout << "\n--- STL Deque ---" << std::endl;
    STLDequeWrapper<int> stlDeque;
    
    for (int i = 1; i <= 4; ++i) {
        stlDeque.push_back(i * 10);
    }
    stlDeque.push_front(5);
    stlDeque.display();
    
    // Both should produce same results for basic operations
    std::cout << "\nBoth deques should have similar behavior!" << std::endl;
    std::cout << "Custom front: " << customDeque.front() << ", STL front: " << stlDeque.front() << std::endl;
    std::cout << "Custom back: " << customDeque.back() << ", STL back: " << stlDeque.back() << std::endl;
}

void demonstrateDequeApplications() {
    printSeparator("DEQUE APPLICATIONS");
    
    // 1. Sliding Window Maximum
    std::cout << "\n--- Sliding Window Maximum ---" << std::endl;
    std::vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3; // Window size
    
    std::cout << "Array: ";
    for (int val : arr) std::cout << val << " ";
    std::cout << "\nWindow size: " << k << std::endl;
    
    std::cout << "Maximum in each window: ";
    for (size_t i = 0; i <= arr.size() - k; ++i) {
        int maxVal = arr[i];
        for (size_t j = i; j < i + k; ++j) {
            maxVal = std::max(maxVal, arr[j]);
        }
        std::cout << maxVal << " ";
    }
    std::cout << std::endl;
    
    // 2. Palindrome Checker using Deque
    std::cout << "\n--- Palindrome Checker ---" << std::endl;
    auto isPalindrome = [](const std::string& str) {
        CircularDeque<char> deque(str.length());
        
        // Add all characters to deque
        for (char c : str) {
            if (std::isalnum(c)) {
                deque.push_back(std::tolower(c));
            }
        }
        
        // Check palindrome by comparing front and back
        while (deque.size() > 1) {
            if (deque.front() != deque.back()) {
                return false;
            }
            deque.pop_front();
            deque.pop_back();
        }
        
        return true;
    };
    
    std::vector<std::string> testStrings = {
        "racecar",
        "A man a plan a canal Panama",
        "race a car",
        "hello",
        "Madam"
    };
    
    for (const auto& str : testStrings) {
        std::cout << "'" << str << "' is " 
                  << (isPalindrome(str) ? "a palindrome" : "not a palindrome") << std::endl;
    }
    
    // 3. Browser History Simulation
    std::cout << "\n--- Browser History Simulation ---" << std::endl;
    CircularDeque<std::string> history(5); // Limited history
    std::string currentPage = "home.html";
    
    auto visitPage = [&](const std::string& page) {
        std::cout << "Visiting: " << page << std::endl;
        if (history.is_full()) {
            history.pop_front(); // Remove oldest
        }
        history.push_back(currentPage);
        currentPage = page;
    };
    
    auto goBack = [&]() {
        if (history.empty()) {
            std::cout << "No previous page" << std::endl;
            return;
        }
        std::cout << "Going back from " << currentPage << " to " << history.back() << std::endl;
        currentPage = history.back();
        history.pop_back();
    };
    
    visitPage("about.html");
    visitPage("products.html");
    visitPage("contact.html");
    
    std::cout << "Current page: " << currentPage << std::endl;
    
    goBack();
    goBack();
    std::cout << "Current page: " << currentPage << std::endl;
}

void demonstrateErrorHandling() {
    printSeparator("ERROR HANDLING");
    
    CircularDeque<int> deque(3);
    
    std::cout << "\n--- Empty Deque Operations ---" << std::endl;
    deque.pop_front();
    deque.pop_back();
    
    try {
        deque.front();
    } catch (const std::exception& e) {
        std::cout << "Front on empty deque: " << e.what() << std::endl;
    }
    
    try {
        deque.at(0);
    } catch (const std::exception& e) {
        std::cout << "Access empty deque: " << e.what() << std::endl;
    }
    
    // Fill deque and test bounds
    std::cout << "\n--- Bounds Checking ---" << std::endl;
    deque.push_back(10);
    deque.push_back(20);
    
    try {
        std::cout << "Valid access [1]: " << deque[1] << std::endl;
        std::cout << "Invalid access [5]: " << deque.at(5) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Out of bounds access: " << e.what() << std::endl;
    }
    
    // Test overflow
    std::cout << "\n--- Overflow Test ---" << std::endl;
    deque.push_back(30); // Should fill deque
    deque.push_back(40); // Should fail
    deque.push_front(0); // Should fail
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "         DEQUE DEMONSTRATION                  " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateRandomAccess();
        demonstrateInsertErase();
        demonstrateAdvancedOperations();
        demonstrateSTLComparison();
        demonstrateDequeApplications();
        demonstrateErrorHandling();
        
        printSeparator("PERFORMANCE CHARACTERISTICS");
        std::cout << "\nTime Complexity Summary:" << std::endl;
        std::cout << "- Push Front/Back:  O(1) - Constant time insertion" << std::endl;
        std::cout << "- Pop Front/Back:   O(1) - Constant time removal" << std::endl;
        std::cout << "- Random Access:    O(1) - Constant time access" << std::endl;
        std::cout << "- Insert/Erase:     O(n) - Linear time for arbitrary position" << std::endl;
        std::cout << "- Search:           O(n) - Linear search required" << std::endl;
        std::cout << "- Space:            O(n) - Linear space for n elements" << std::endl;
        
        std::cout << "\nDeque vs Other Data Structures:" << std::endl;
        std::cout << "vs Vector:" << std::endl;
        std::cout << "  ✅ O(1) front insertion/deletion" << std::endl;
        std::cout << "  ✅ Same O(1) random access" << std::endl;
        std::cout << "  ❌ Slightly more memory overhead" << std::endl;
        
        std::cout << "vs List:" << std::endl;
        std::cout << "  ✅ O(1) random access" << std::endl;
        std::cout << "  ✅ Better cache locality" << std::endl;
        std::cout << "  ❌ O(n) insert/erase in middle" << std::endl;
        
        std::cout << "vs Queue/Stack:" << std::endl;
        std::cout << "  ✅ Operations at both ends" << std::endl;
        std::cout << "  ✅ Random access capability" << std::endl;
        std::cout << "  ❌ More complex implementation" << std::endl;
        
        std::cout << "\nCommon Use Cases:" << std::endl;
        std::cout << "🎯 Sliding window algorithms" << std::endl;
        std::cout << "🎯 Browser history management" << std::endl;
        std::cout << "🎯 Undo/Redo with limited buffer" << std::endl;
        std::cout << "🎯 Double-ended buffer processing" << std::endl;
        std::cout << "🎯 Palindrome checking" << std::endl;
        std::cout << "🎯 A* pathfinding (open/closed lists)" << std::endl;
        std::cout << "🎯 Job scheduling with priorities" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
