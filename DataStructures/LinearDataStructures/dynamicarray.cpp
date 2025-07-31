// Dynamic Array Implementation - Complete program with all operations
/*
Key Features of Dynamic Array:
Core Operations:
✅ Push Back: Add elements at end in O(1) amortized
✅ Pop Back: Remove elements from end in O(1)
✅ Random Access: Access any element by index in O(1)
✅ Insert/Erase: At any position with O(n) complexity
Dynamic Array Features:
📈 Dynamic Resizing: Automatically grows/shrinks as needed
🎯 Contiguous Memory: Elements stored in continuous memory
⚡ Cache Friendly: Better performance due to memory locality
💾 Efficient Memory Usage: Minimal memory overhead per element
Advanced Features:
🔍 Search: Find element position
📊 Display: Show array contents
🗑️ Clear: Remove all elements
📏 Size/Capacity Tracking: Monitor memory usage
🔄 Reserve: Pre-allocate memory for better performance
Smart Memory Management:
🧠 Exponential growth strategy for amortized O(1) insertions
🛡️ Exception-safe operations
🚫 RAII principles throughout
📈 Automatic memory management with reallocation
Educational Demonstrations:
📊 Performance Analysis: Time/space complexity breakdown
🧪 Error Handling: Comprehensive edge case testing
📝 Use Cases: Real-world applications explained
🔄 Growth strategies: Different expansion policies
*/

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <initializer_list>

template<typename T>
class DynamicArray {
private:
    std::unique_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
    
    // Growth factor for dynamic resizing
    static constexpr double GROWTH_FACTOR = 2.0;
    static constexpr size_t INITIAL_CAPACITY = 4;
    
    // Resize the array to new capacity
    void resize(size_t new_capacity) {
        if (new_capacity < size_) {
            throw std::invalid_argument("New capacity cannot be less than current size");
        }
        
        auto new_data = std::make_unique<T[]>(new_capacity);
        
        // Copy existing elements
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        
        data_ = std::move(new_data);
        capacity_ = new_capacity;
        
        std::cout << "Resized array to capacity " << capacity_ << std::endl;
    }
    
    // Ensure capacity is sufficient for n elements
    void ensure_capacity(size_t min_capacity) {
        if (capacity_ >= min_capacity) return;
        
        size_t new_capacity = std::max(min_capacity, 
                                      static_cast<size_t>(capacity_ * GROWTH_FACTOR));
        resize(new_capacity);
    }
    
public:
    // Default constructor
    DynamicArray() : data_(std::make_unique<T[]>(INITIAL_CAPACITY)), 
                     size_(0), capacity_(INITIAL_CAPACITY) {}
    
    // Constructor with initial capacity
    explicit DynamicArray(size_t initial_capacity) 
        : data_(std::make_unique<T[]>(initial_capacity)), 
          size_(0), capacity_(initial_capacity) {}
    
    // Constructor with initializer list
    DynamicArray(std::initializer_list<T> init_list) 
        : DynamicArray(init_list.size()) {
        for (const auto& item : init_list) {
            push_back(item);
        }
    }
    
    // Copy constructor
    DynamicArray(const DynamicArray& other) 
        : data_(std::make_unique<T[]>(other.capacity_)), 
          size_(other.size_), capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept
        : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    // Assignment operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            data_ = std::make_unique<T[]>(other.capacity_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    
    // Move assignment operator
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    // Add element at the end
    void push_back(const T& value) {
        ensure_capacity(size_ + 1);
        data_[size_++] = value;
        std::cout << "Pushed " << value << " (size: " << size_ << ", capacity: " << capacity_ << ")" << std::endl;
    }
    
    // Add element at the end (move version)
    void push_back(T&& value) {
        ensure_capacity(size_ + 1);
        data_[size_++] = std::move(value);
        std::cout << "Pushed (moved) element (size: " << size_ << ", capacity: " << capacity_ << ")" << std::endl;
    }
    
    // Remove last element
    void pop_back() {
        if (empty()) {
            std::cout << "Array is empty - cannot pop" << std::endl;
            return;
        }
        
        std::cout << "Popped " << data_[size_ - 1] << std::endl;
        --size_;
        
        // Shrink if too much unused capacity
        if (size_ > 0 && capacity_ > INITIAL_CAPACITY && size_ <= capacity_ / 4) {
            resize(capacity_ / 2);
        }
    }
    
    // Insert element at specific position
    void insert(size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("Index out of bounds");
        }
        
        ensure_capacity(size_ + 1);
        
        // Shift elements to the right
        for (size_t i = size_; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        
        data_[index] = value;
        ++size_;
        
        std::cout << "Inserted " << value << " at index " << index << std::endl;
    }
    
    // Erase element at specific position
    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        
        T value = data_[index];
        
        // Shift elements to the left
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        
        --size_;
        std::cout << "Erased " << value << " at index " << index << std::endl;
        
        // Shrink if too much unused capacity
        if (size_ > 0 && capacity_ > INITIAL_CAPACITY && size_ <= capacity_ / 4) {
            resize(capacity_ / 2);
        }
    }
    
    // Access element by index (const version)
    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }
    
    // Access element by index (non-const version)
    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data_[index];
    }
    
    // Operator[] (const version)
    const T& operator[](size_t index) const {
        return data_[index]; // No bounds checking for performance
    }
    
    // Operator[] (non-const version)
    T& operator[](size_t index) {
        return data_[index]; // No bounds checking for performance
    }
    
    // Get front element
    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Array is empty");
        }
        return data_[0];
    }
    
    // Get back element
    const T& back() const {
        if (empty()) {
            throw std::runtime_error("Array is empty");
        }
        return data_[size_ - 1];
    }
    
    // Get non-const front element
    T& front() {
        if (empty()) {
            throw std::runtime_error("Array is empty");
        }
        return data_[0];
    }
    
    // Get non-const back element
    T& back() {
        if (empty()) {
            throw std::runtime_error("Array is empty");
        }
        return data_[size_ - 1];
    }
    
    // Check if array is empty
    bool empty() const {
        return size_ == 0;
    }
    
    // Get size
    size_t size() const {
        return size_;
    }
    
    // Get capacity
    size_t capacity() const {
        return capacity_;
    }
    
    // Reserve capacity
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            resize(new_capacity);
            std::cout << "Reserved capacity " << new_capacity << std::endl;
        }
    }
    
    // Shrink to fit
    void shrink_to_fit() {
        if (size_ < capacity_) {
            resize(size_);
            std::cout << "Shrunk to fit (capacity now " << capacity_ << ")" << std::endl;
        }
    }
    
    // Clear all elements
    void clear() {
        size_ = 0;
        std::cout << "Array cleared (capacity remains " << capacity_ << ")" << std::endl;
    }
    
    // Find element (returns index or -1 if not found)
    int find(const T& value) const {
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] == value) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }
    
    // Check if array contains element
    bool contains(const T& value) const {
        return find(value) != -1;
    }
    
    // Sort the array
    void sort() {
        std::sort(data_.get(), data_.get() + size_);
        std::cout << "Array sorted" << std::endl;
    }
    
    // Reverse the array
    void reverse() {
        std::reverse(data_.get(), data_.get() + size_);
        std::cout << "Array reversed" << std::endl;
    }
    
    // Remove duplicates (keeps first occurrence)
    void remove_duplicates() {
        if (size_ <= 1) return;
        
        size_t write_index = 1;
        
        for (size_t read_index = 1; read_index < size_; ++read_index) {
            bool is_duplicate = false;
            
            // Check if current element exists in the already processed part
            for (size_t check = 0; check < write_index; ++check) {
                if (data_[read_index] == data_[check]) {
                    is_duplicate = true;
                    break;
                }
            }
            
            if (!is_duplicate) {
                data_[write_index++] = data_[read_index];
            }
        }
        
        size_t old_size = size_;
        size_ = write_index;
        
        std::cout << "Removed duplicates (" << (old_size - size_) << " duplicates removed)" << std::endl;
    }
    
    // Resize array to specific size with default value
    void resize_to(size_t new_size, const T& default_value = T{}) {
        if (new_size > capacity_) {
            ensure_capacity(new_size);
        }
        
        // Initialize new elements with default value
        for (size_t i = size_; i < new_size; ++i) {
            data_[i] = default_value;
        }
        
        size_ = new_size;
        std::cout << "Resized array to " << size_ << " elements" << std::endl;
    }
    
    // Display array contents
    void display() const {
        if (empty()) {
            std::cout << "Array is empty" << std::endl;
            return;
        }
        
        std::cout << "Array: [";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i < size_ - 1) std::cout << ", ";
        }
        std::cout << "] (size: " << size_ << ", capacity: " << capacity_ << ")" << std::endl;
    }
    
    // Display with indices
    void display_with_indices() const {
        if (empty()) {
            std::cout << "Array is empty" << std::endl;
            return;
        }
        
        std::cout << "Array with indices:" << std::endl;
        for (size_t i = 0; i < size_; ++i) {
            std::cout << "[" << i << "]: " << data_[i] << std::endl;
        }
    }
    
    // Get memory usage statistics
    void print_stats() const {
        std::cout << "=== Array Statistics ===" << std::endl;
        std::cout << "Size: " << size_ << std::endl;
        std::cout << "Capacity: " << capacity_ << std::endl;
        std::cout << "Memory efficiency: " << (size_ * 100.0 / capacity_) << "%" << std::endl;
        std::cout << "Memory used: " << (capacity_ * sizeof(T)) << " bytes" << std::endl;
        std::cout << "Empty slots: " << (capacity_ - size_) << std::endl;
    }
    
    // Iterator support (basic)
    T* begin() { return data_.get(); }
    T* end() { return data_.get() + size_; }
    const T* begin() const { return data_.get(); }
    const T* end() const { return data_.get() + size_; }
    const T* cbegin() const { return data_.get(); }
    const T* cend() const { return data_.get() + size_; }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(55, '=') << std::endl;
}

void demonstrateBasicOperations() {
    printSeparator("BASIC DYNAMIC ARRAY OPERATIONS");
    
    DynamicArray<int> arr;
    
    std::cout << "\n--- Initial State ---" << std::endl;
    arr.print_stats();
    arr.display();
    
    // Push back operations
    std::cout << "\n--- Push Back Operations ---" << std::endl;
    for (int i = 1; i <= 6; ++i) {
        arr.push_back(i * 10);
    }
    
    arr.display();
    arr.print_stats();
    
    // Access operations
    std::cout << "\n--- Access Operations ---" << std::endl;
    try {
        std::cout << "Front element: " << arr.front() << std::endl;
        std::cout << "Back element: " << arr.back() << std::endl;
        std::cout << "Element at index 2: " << arr[2] << std::endl;
        std::cout << "Element at index 4: " << arr.at(4) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Pop back operations
    std::cout << "\n--- Pop Back Operations ---" << std::endl;
    arr.pop_back();
    arr.pop_back();
    arr.display();
    arr.print_stats();
}

void demonstrateInsertErase() {
    printSeparator("INSERT/ERASE OPERATIONS");
    
    DynamicArray<char> arr{'A', 'C', 'E', 'G'};
    
    std::cout << "\n--- Initial Array ---" << std::endl;
    arr.display();
    
    // Insert operations
    std::cout << "\n--- Insert Operations ---" << std::endl;
    arr.insert(1, 'B');  // Insert at index 1
    arr.display();
    
    arr.insert(3, 'D');  // Insert at index 3
    arr.display();
    
    arr.insert(5, 'F');  // Insert at index 5
    arr.display();
    
    // Erase operations
    std::cout << "\n--- Erase Operations ---" << std::endl;
    arr.erase(0);        // Erase first element
    arr.display();
    
    arr.erase(2);        // Erase middle element
    arr.display();
    
    arr.erase(arr.size() - 1); // Erase last element
    arr.display();
}

void demonstrateCapacityManagement() {
    printSeparator("CAPACITY MANAGEMENT");
    
    DynamicArray<int> arr(2); // Start with small capacity
    
    std::cout << "\n--- Initial Small Capacity ---" << std::endl;
    arr.print_stats();
    
    // Force multiple reallocations
    std::cout << "\n--- Forcing Reallocations ---" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        std::cout << "Adding element " << i << ":" << std::endl;
        arr.push_back(i);
        arr.print_stats();
        std::cout << std::endl;
    }
    
    // Reserve capacity
    std::cout << "\n--- Reserve Operation ---" << std::endl;
    arr.reserve(20);
    arr.print_stats();
    
    // Shrink to fit
    std::cout << "\n--- Shrink to Fit ---" << std::endl;
    arr.shrink_to_fit();
    arr.print_stats();
    
    // Test shrinking on pop
    std::cout << "\n--- Auto-Shrinking on Pop ---" << std::endl;
    while (!arr.empty()) {
        arr.pop_back();
        if (arr.size() % 3 == 0) { // Show stats every 3 pops
            arr.print_stats();
        }
    }
}

void demonstrateAdvancedOperations() {
    printSeparator("ADVANCED OPERATIONS");
    
    DynamicArray<int> arr{30, 10, 40, 20, 50, 10, 30, 60};
    
    std::cout << "\n--- Original Array ---" << std::endl;
    arr.display();
    arr.display_with_indices();
    
    // Search operations
    std::cout << "\n--- Search Operations ---" << std::endl;
    std::cout << "Find 20: Index " << arr.find(20) << std::endl;
    std::cout << "Find 100: Index " << arr.find(100) << std::endl;
    std::cout << "Contains 40: " << (arr.contains(40) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 100: " << (arr.contains(100) ? "Yes" : "No") << std::endl;
    
    // Sort operation
    std::cout << "\n--- Sort Operation ---" << std::endl;
    DynamicArray<int> sortedArr = arr; // Copy for sorting
    sortedArr.sort();
    sortedArr.display();
    
    // Reverse operation
    std::cout << "\n--- Reverse Operation ---" << std::endl;
    arr.reverse();
    arr.display();
    
    // Remove duplicates
    std::cout << "\n--- Remove Duplicates ---" << std::endl;
    arr.reverse(); // Restore original order
    arr.remove_duplicates();
    arr.display();
}

void demonstrateResizeOperations() {
    printSeparator("RESIZE OPERATIONS");
    
    DynamicArray<std::string> arr{"Hello", "World"};
    
    std::cout << "\n--- Initial Array ---" << std::endl;
    arr.display();
    arr.print_stats();
    
    // Resize to larger size
    std::cout << "\n--- Resize to Larger Size ---" << std::endl;
    arr.resize_to(5, "Default");
    arr.display();
    arr.print_stats();
    
    // Resize to smaller size
    std::cout << "\n--- Resize to Smaller Size ---" << std::endl;
    arr.resize_to(3);
    arr.display();
    arr.print_stats();
    
    // Clear operation
    std::cout << "\n--- Clear Operation ---" << std::endl;
    arr.clear();
    arr.display();
    arr.print_stats();
}

void demonstrateIteratorSupport() {
    printSeparator("ITERATOR SUPPORT");
    
    DynamicArray<int> arr{1, 2, 3, 4, 5};
    
    std::cout << "\n--- Range-based For Loop ---" << std::endl;
    std::cout << "Elements: ";
    for (const auto& element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\n--- STL Algorithm Usage ---" << std::endl;
    // Use STL algorithms
    auto it = std::find(arr.begin(), arr.end(), 3);
    if (it != arr.end()) {
        std::cout << "Found element 3 at position: " << (it - arr.begin()) << std::endl;
    }
    
    // Count elements
    int count = std::count_if(arr.begin(), arr.end(), [](int x) { return x % 2 == 0; });
    std::cout << "Even numbers count: " << count << std::endl;
}

void demonstrateApplications() {
    printSeparator("DYNAMIC ARRAY APPLICATIONS");
    
    // 1. Growing Dataset
    std::cout << "\n--- Growing Dataset Simulation ---" << std::endl;
    DynamicArray<double> measurements;
    measurements.reserve(100); // Pre-allocate to avoid reallocations
    
    std::cout << "Recording measurements:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        double value = 20.5 + i * 2.3;
        measurements.push_back(value);
        if (i % 3 == 0) {
            std::cout << "Recorded " << (i + 1) << " measurements" << std::endl;
        }
    }
    
    measurements.display();
    std::cout << "Average: " << 
        (std::accumulate(measurements.begin(), measurements.end(), 0.0) / measurements.size()) 
        << std::endl;
    
    // 2. Dynamic String Array
    std::cout << "\n--- Dynamic String Management ---" << std::endl;
    DynamicArray<std::string> words;
    
    std::vector<std::string> input_words = {"Dynamic", "Array", "Implementation", "C++", "Data", "Structure"};
    
    for (const auto& word : input_words) {
        words.push_back(word);
    }
    
    words.display();
    
    // Find longest word
    auto longest = std::max_element(words.begin(), words.end(),
        [](const std::string& a, const std::string& b) {
            return a.length() < b.length();
        });
    
    if (longest != words.end()) {
        std::cout << "Longest word: '" << *longest << "' (" << longest->length() << " chars)" << std::endl;
    }
    
    // 3. Matrix Simulation (2D array as 1D)
    std::cout << "\n--- 2D Matrix as Dynamic Array ---" << std::endl;
    const size_t rows = 3, cols = 4;
    DynamicArray<int> matrix;
    matrix.resize_to(rows * cols, 0);
    
    // Fill matrix
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i * cols + j] = (i + 1) * (j + 1);
        }
    }
    
    // Display matrix
    std::cout << "3x4 Matrix:" << std::endl;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << matrix[i * cols + j] << "\t";
        }
        std::cout << std::endl;
    }
}

void demonstrateErrorHandling() {
    printSeparator("ERROR HANDLING");
    
    DynamicArray<int> arr;
    
    std::cout << "\n--- Empty Array Operations ---" << std::endl;
    arr.pop_back(); // Should handle gracefully
    
    try {
        arr.front();
    } catch (const std::exception& e) {
        std::cout << "Front on empty array: " << e.what() << std::endl;
    }
    
    try {
        arr.at(0);
    } catch (const std::exception& e) {
        std::cout << "Access empty array: " << e.what() << std::endl;
    }
    
    // Add some elements and test bounds
    std::cout << "\n--- Bounds Checking ---" << std::endl;
    arr.push_back(10);
    arr.push_back(20);
    
    try {
        std::cout << "Valid access [1]: " << arr.at(1) << std::endl;
        std::cout << "Invalid access [5]: " << arr.at(5) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Out of bounds access: " << e.what() << std::endl;
    }
    
    try {
        arr.insert(10, 100); // Out of bounds insert
    } catch (const std::exception& e) {
        std::cout << "Out of bounds insert: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "      DYNAMIC ARRAY DEMONSTRATION            " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateInsertErase();
        demonstrateCapacityManagement();
        demonstrateAdvancedOperations();
        demonstrateResizeOperations();
        demonstrateIteratorSupport();
        demonstrateApplications();
        demonstrateErrorHandling();
        
        printSeparator("PERFORMANCE CHARACTERISTICS");
        std::cout << "\nTime Complexity Summary:" << std::endl;
        std::cout << "- Random Access: O(1) - Direct indexing" << std::endl;
        std::cout << "- Push Back:     O(1) amortized - May trigger reallocation" << std::endl;
        std::cout << "- Pop Back:      O(1) - Simple decrement" << std::endl;
        std::cout << "- Insert:        O(n) - Requires shifting elements" << std::endl;
        std::cout << "- Erase:         O(n) - Requires shifting elements" << std::endl;
        std::cout << "- Search:        O(n) - Linear search" << std::endl;
        std::cout << "- Space:         O(n) - Additional space for growth" << std::endl;
        
        std::cout << "\nMemory Management:" << std::endl;
        std::cout << "Growth Strategy:" << std::endl;
        std::cout << "  ✅ Exponential growth (factor 2.0)" << std::endl;
        std::cout << "  ✅ Amortized O(1) insertions" << std::endl;
        std::cout << "  ✅ Automatic shrinking when utilization < 25%" << std::endl;
        
        std::cout << "Memory Characteristics:" << std::endl;
        std::cout << "  ✅ Contiguous memory layout" << std::endl;
        std::cout << "  ✅ Cache-friendly access patterns" << std::endl;
        std::cout << "  ✅ Minimal per-element overhead" << std::endl;
        std::cout << "  ❌ May waste memory during growth" << std::endl;
        
        std::cout << "\nComparison with Other Structures:" << std::endl;
        std::cout << "vs Static Array:" << std::endl;
        std::cout << "  ✅ Dynamic sizing" << std::endl;
        std::cout << "  ✅ Automatic memory management" << std::endl;
        std::cout << "  ❌ Slight overhead for capacity tracking" << std::endl;
        
        std::cout << "vs Linked List:" << std::endl;
        std::cout << "  ✅ O(1) random access" << std::endl;
        std::cout << "  ✅ Better cache locality" << std::endl;
        std::cout << "  ❌ O(n) insertion/deletion in middle" << std::endl;
        
        std::cout << "\nCommon Use Cases:" << std::endl;
        std::cout << "🎯 General-purpose container" << std::endl;
        std::cout << "🎯 When frequent random access is needed" << std::endl;
        std::cout << "🎯 Growing datasets with unknown final size" << std::endl;
        std::cout << "🎯 Implementing other data structures" << std::endl;
        std::cout << "🎯 Matrix and multi-dimensional data" << std::endl;
        std::cout << "🎯 Buffer management" << std::endl;
        std::cout << "🎯 Cache-friendly algorithms" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
