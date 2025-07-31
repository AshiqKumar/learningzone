// Doubly Linked List Implementation - Complete program with all operations
/*
Key Features of the Doubly Linked List:
Core Operations:
✅ Push/Pop: Front and back operations in O(1)
✅ Insert/Remove: At any position with optimized access
✅ Search: Both forward and backward search capabilities
✅ Access: Get/update elements at any position
Doubly-Specific Advantages:
🔄 Bidirectional Traversal: Can move forward and backward
⚡ Performance Optimization: Chooses shortest path (from head or tail)
🎯 Efficient Deletion: O(1) when node reference is known
📍 Tail Access: Direct access to the last element
Advanced Features:
🔀 Reverse: Efficient in-place reversal
🔄 Sort: Bubble sort implementation
🗑️ Remove Duplicates: Preserves original order
✂️ Split/Merge: Advanced list manipulation
🎯 Middle Element: Two-pointer technique
🔍 Bidirectional Search: Forward and backward searching
Smart Memory Management:
🧠 Uses std::unique_ptr for automatic memory management
🔗 Raw prev pointers to avoid circular ownership issues
🛡️ Exception-safe operations
🚫 RAII principles throughout
Educational Demonstrations:
📊 Performance Analysis: Time/space complexity breakdown
🧪 Error Handling: Comprehensive edge case testing
📝 Use Cases: Real-world applications explained
🔄 Bidirectional Features: Showcases unique doubly properties
Optimizations:
Smart Access: Starts from head or tail based on position
Efficient Updates: O(n/2) average case instead of O(n)
Memory Efficient: Proper cleanup and move semantics
*/

#include <iostream>
#include <memory>
#include <stdexcept>

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node* prev;  // Raw pointer to avoid circular ownership
        
        explicit Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    std::unique_ptr<Node> head_;
    Node* tail_;  // Raw pointer for easy back access
    size_t size_;
    
public:
    // Constructor
    DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
    
    // Destructor (automatic with smart pointers)
    ~DoublyLinkedList() = default;
    
    // Add element at the beginning
    void push_front(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        
        if (!head_) {
            // First node
            head_ = std::move(newNode);
            tail_ = head_.get();
        } else {
            // Insert at front
            newNode->next = std::move(head_);
            newNode->next->prev = newNode.get();
            head_ = std::move(newNode);
        }
        
        size_++;
        std::cout << "Added " << value << " at front" << std::endl;
    }
    
    // Add element at the end
    void push_back(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        
        if (!head_) {
            // First node
            head_ = std::move(newNode);
            tail_ = head_.get();
        } else {
            // Insert at back
            newNode->prev = tail_;
            tail_->next = std::move(newNode);
            tail_ = tail_->next.get();
        }
        
        size_++;
        std::cout << "Added " << value << " at back" << std::endl;
    }
    
    // Insert at specific position
    void insert(size_t position, const T& value) {
        if (position == 0) {
            push_front(value);
            return;
        }
        
        if (position >= size_) {
            push_back(value);
            return;
        }
        
        auto newNode = std::make_unique<Node>(value);
        
        // Optimize: start from head or tail based on position
        if (position <= size_ / 2) {
            // Start from head
            Node* current = head_.get();
            for (size_t i = 0; i < position; ++i) {
                current = current->next.get();
            }
            
            // Insert before current
            newNode->next = std::move(current->prev->next);
            newNode->prev = current->prev;
            current->prev->next = std::move(newNode);
            current->prev = current->prev->next.get();
        } else {
            // Start from tail
            Node* current = tail_;
            for (size_t i = size_ - 1; i > position; --i) {
                current = current->prev;
            }
            
            // Insert before current
            newNode->next = std::move(current->prev->next);
            newNode->prev = current->prev;
            current->prev->next = std::move(newNode);
            current->prev = current->prev->next.get();
        }
        
        size_++;
        std::cout << "Inserted " << value << " at position " << position << std::endl;
    }
    
    // Remove from front
    void pop_front() {
        if (!head_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        std::cout << "Removed " << head_->data << " from front" << std::endl;
        
        if (size_ == 1) {
            // Only one node
            head_.reset();
            tail_ = nullptr;
        } else {
            head_ = std::move(head_->next);
            head_->prev = nullptr;
        }
        
        size_--;
    }
    
    // Remove from back
    void pop_back() {
        if (!head_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        std::cout << "Removed " << tail_->data << " from back" << std::endl;
        
        if (size_ == 1) {
            // Only one node
            head_.reset();
            tail_ = nullptr;
        } else {
            tail_ = tail_->prev;
            tail_->next.reset();
        }
        
        size_--;
    }
    
    // Remove element at specific position
    void remove_at(size_t position) {
        if (position >= size_) {
            std::cout << "Position " << position << " is out of bounds" << std::endl;
            return;
        }
        
        if (position == 0) {
            pop_front();
            return;
        }
        
        if (position == size_ - 1) {
            pop_back();
            return;
        }
        
        Node* current;
        
        // Optimize: start from head or tail based on position
        if (position <= size_ / 2) {
            // Start from head
            current = head_.get();
            for (size_t i = 0; i < position; ++i) {
                current = current->next.get();
            }
        } else {
            // Start from tail
            current = tail_;
            for (size_t i = size_ - 1; i > position; --i) {
                current = current->prev;
            }
        }
        
        std::cout << "Removed " << current->data << " at position " << position << std::endl;
        
        // Update links
        current->prev->next = std::move(current->next);
        if (current->next) {
            current->next->prev = current->prev;
        }
        
        size_--;
    }
    
    // Find element and return its position (forward search)
    int find(const T& value) const {
        Node* current = head_.get();
        int position = 0;
        
        while (current) {
            if (current->data == value) {
                return position;
            }
            current = current->next.get();
            position++;
        }
        
        return -1;  // Not found
    }
    
    // Find element from back and return its position (backward search)
    int find_reverse(const T& value) const {
        Node* current = tail_;
        int position = size_ - 1;
        
        while (current) {
            if (current->data == value) {
                return position;
            }
            current = current->prev;
            position--;
        }
        
        return -1;  // Not found
    }
    
    // Check if element exists
    bool contains(const T& value) const {
        return find(value) != -1;
    }
    
    // Get element at specific position
    T get(size_t position) const {
        if (position >= size_) {
            throw std::out_of_range("Position out of bounds");
        }
        
        Node* current;
        
        // Optimize: start from head or tail based on position
        if (position <= size_ / 2) {
            // Start from head
            current = head_.get();
            for (size_t i = 0; i < position; ++i) {
                current = current->next.get();
            }
        } else {
            // Start from tail
            current = tail_;
            for (size_t i = size_ - 1; i > position; --i) {
                current = current->prev;
            }
        }
        
        return current->data;
    }
    
    // Update element at specific position
    void update(size_t position, const T& value) {
        if (position >= size_) {
            std::cout << "Position " << position << " is out of bounds" << std::endl;
            return;
        }
        
        Node* current;
        
        // Optimize: start from head or tail based on position
        if (position <= size_ / 2) {
            current = head_.get();
            for (size_t i = 0; i < position; ++i) {
                current = current->next.get();
            }
        } else {
            current = tail_;
            for (size_t i = size_ - 1; i > position; --i) {
                current = current->prev;
            }
        }
        
        T oldValue = current->data;
        current->data = value;
        std::cout << "Updated position " << position << " from " << oldValue << " to " << value << std::endl;
    }
    
    // Reverse the list
    void reverse() {
        if (size_ <= 1) {
            std::cout << "List reversed (nothing to reverse)" << std::endl;
            return;
        }
        
        Node* current = head_.get();
        tail_ = current;  // Old head becomes new tail
        
        while (current) {
            Node* nextNode = current->next.get();
            
            // Swap next and prev pointers
            std::swap(current->next, current->prev);
            
            // Move to next node (which is now prev due to swap)
            current = nextNode;
        }
        
        // Update head to old tail
        head_ = std::unique_ptr<Node>(tail_->prev);
        tail_->prev = nullptr;
        
        std::cout << "List reversed" << std::endl;
    }
    
    // Sort the list (bubble sort)
    void sort() {
        if (size_ <= 1) return;
        
        bool swapped;
        do {
            swapped = false;
            Node* current = head_.get();
            
            while (current && current->next) {
                if (current->data > current->next->data) {
                    // Swap data
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next.get();
            }
        } while (swapped);
        
        std::cout << "List sorted" << std::endl;
    }
    
    // Remove duplicates (preserves order)
    void remove_duplicates() {
        if (size_ <= 1) return;
        
        Node* current = head_.get();
        
        while (current) {
            Node* runner = current->next.get();
            
            while (runner) {
                if (runner->data == current->data) {
                    // Remove duplicate
                    Node* nodeToRemove = runner;
                    runner = runner->next.get();
                    
                    if (nodeToRemove->next) {
                        nodeToRemove->next->prev = nodeToRemove->prev;
                    } else {
                        tail_ = nodeToRemove->prev;
                    }
                    
                    if (nodeToRemove->prev) {
                        nodeToRemove->prev->next = std::move(nodeToRemove->next);
                    }
                    
                    size_--;
                } else {
                    runner = runner->next.get();
                }
            }
            
            current = current->next.get();
        }
        
        std::cout << "Duplicates removed" << std::endl;
    }
    
    // Get middle element
    T get_middle() const {
        if (!head_) {
            throw std::runtime_error("List is empty");
        }
        
        Node* slow = head_.get();
        Node* fast = head_.get();
        
        // Two-pointer technique to find middle
        while (fast && fast->next) {
            slow = slow->next.get();
            fast = fast->next->next.get();
        }
        
        return slow->data;
    }
    
    // Merge with another doubly linked list
    void merge(DoublyLinkedList<T>& other) {
        if (other.empty()) return;
        
        if (empty()) {
            *this = std::move(other);
            return;
        }
        
        // Connect this list's tail to other's head
        tail_->next = std::move(other.head_);
        tail_->next->prev = tail_;
        tail_ = other.tail_;
        size_ += other.size_;
        
        // Reset other list
        other.tail_ = nullptr;
        other.size_ = 0;
        
        std::cout << "Lists merged" << std::endl;
    }
    
    // Split the list at given position
    DoublyLinkedList<T> split_at(size_t position) {
        DoublyLinkedList<T> newList;
        
        if (position >= size_ || position == 0) {
            return newList;
        }
        
        // Find the split point
        Node* current = head_.get();
        for (size_t i = 0; i < position; ++i) {
            current = current->next.get();
        }
        
        // Create new list from current to tail
        newList.head_ = std::move(current->prev->next);
        newList.tail_ = tail_;
        newList.size_ = size_ - position;
        
        // Update this list
        tail_ = current->prev;
        tail_->next.reset();
        size_ = position;
        
        // Fix new list's head
        newList.head_->prev = nullptr;
        
        std::cout << "List split at position " << position << std::endl;
        return newList;
    }
    
    // Display list forward
    void display_forward() const {
        if (!head_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        std::cout << "Forward: ";
        Node* current = head_.get();
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " <-> ";
            current = current->next.get();
        }
        std::cout << " <-> nullptr" << std::endl;
    }
    
    // Display list backward
    void display_backward() const {
        if (!tail_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        std::cout << "Backward: ";
        Node* current = tail_;
        while (current) {
            std::cout << current->data;
            if (current->prev) std::cout << " <-> ";
            current = current->prev;
        }
        std::cout << " <-> nullptr" << std::endl;
    }
    
    // Display both directions
    void display() const {
        display_forward();
    }
    
    // Display with positions
    void display_with_positions() const {
        if (!head_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        std::cout << "List with positions:" << std::endl;
        Node* current = head_.get();
        int position = 0;
        
        while (current) {
            std::cout << "Position " << position << ": " << current->data << std::endl;
            current = current->next.get();
            position++;
        }
    }
    
    // Get size
    size_t size() const { 
        return size_; 
    }
    
    // Check if empty
    bool empty() const { 
        return head_ == nullptr; 
    }
    
    // Clear the list
    void clear() {
        head_.reset();
        tail_ = nullptr;
        size_ = 0;
        std::cout << "List cleared" << std::endl;
    }
    
    // Get front element
    T front() const {
        if (!head_) {
            throw std::runtime_error("List is empty");
        }
        return head_->data;
    }
    
    // Get back element
    T back() const {
        if (!tail_) {
            throw std::runtime_error("List is empty");
        }
        return tail_->data;
    }
    
    // Move constructor
    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head_(std::move(other.head_)), tail_(other.tail_), size_(other.size_) {
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    
    // Move assignment operator
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            head_ = std::move(other.head_);
            tail_ = other.tail_;
            size_ = other.size_;
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    
    // Copy constructor (disabled for simplicity)
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(55, '=') << std::endl;
}

void demonstrateBasicOperations() {
    printSeparator("BASIC OPERATIONS");
    
    DoublyLinkedList<int> list;
    
    // Test push operations
    std::cout << "\n--- Push Operations ---" << std::endl;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);
    list.display_forward();
    list.display_backward();
    
    // Test insert operation
    std::cout << "\n--- Insert Operations ---" << std::endl;
    list.insert(2, 15);
    list.insert(0, 1);
    list.insert(100, 50); // Insert at end
    list.display_forward();
    
    // Test access operations
    std::cout << "\n--- Access Operations ---" << std::endl;
    std::cout << "Size: " << list.size() << std::endl;
    std::cout << "Front: " << list.front() << std::endl;
    std::cout << "Back: " << list.back() << std::endl;
    std::cout << "Element at position 3: " << list.get(3) << std::endl;
    
    try {
        std::cout << "Middle element: " << list.get_middle() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void demonstrateSearchOperations() {
    printSeparator("SEARCH OPERATIONS");
    
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(20);
    list.push_back(40);
    list.display_forward();
    
    // Test find operations
    std::cout << "\n--- Find Operations ---" << std::endl;
    std::cout << "Find 20 (forward): Position " << list.find(20) << std::endl;
    std::cout << "Find 20 (backward): Position " << list.find_reverse(20) << std::endl;
    std::cout << "Find 100: Position " << list.find(100) << std::endl;
    std::cout << "Contains 30: " << (list.contains(30) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 100: " << (list.contains(100) ? "Yes" : "No") << std::endl;
}

void demonstrateRemovalOperations() {
    printSeparator("REMOVAL OPERATIONS");
    
    DoublyLinkedList<int> list;
    for (int i = 1; i <= 6; ++i) {
        list.push_back(i * 10);
    }
    
    std::cout << "\n--- Initial List ---" << std::endl;
    list.display_forward();
    
    std::cout << "\n--- Pop Operations ---" << std::endl;
    list.pop_front();
    list.display_forward();
    
    list.pop_back();
    list.display_forward();
    
    std::cout << "\n--- Remove at Position ---" << std::endl;
    list.remove_at(1);
    list.display_forward();
    
    list.remove_at(10); // Out of bounds test
}

void demonstrateAdvancedOperations() {
    printSeparator("ADVANCED OPERATIONS");
    
    DoublyLinkedList<int> list;
    
    // Create unsorted list with duplicates
    int values[] = {30, 10, 40, 10, 20, 30, 50, 20};
    for (int val : values) {
        list.push_back(val);
    }
    
    std::cout << "\n--- Original List ---" << std::endl;
    list.display_forward();
    list.display_backward();
    list.display_with_positions();
    
    std::cout << "\n--- Update Operation ---" << std::endl;
    list.update(2, 25);
    list.display_forward();
    
    std::cout << "\n--- Remove Duplicates ---" << std::endl;
    list.remove_duplicates();
    list.display_forward();
    
    std::cout << "\n--- Sort Operation ---" << std::endl;
    list.sort();
    list.display_forward();
    
    std::cout << "\n--- Reverse Operation ---" << std::endl;
    list.reverse();
    list.display_forward();
    list.display_backward();
}

void demonstrateDoublySpecificFeatures() {
    printSeparator("DOUBLY-SPECIFIC FEATURES");
    
    DoublyLinkedList<char> list;
    
    // Add letters
    for (char c = 'A'; c <= 'F'; ++c) {
        list.push_back(c);
    }
    
    std::cout << "\n--- Bidirectional Display ---" << std::endl;
    list.display_forward();
    list.display_backward();
    
    std::cout << "\n--- Split Operation ---" << std::endl;
    auto secondHalf = list.split_at(3);
    
    std::cout << "First half: ";
    list.display_forward();
    std::cout << "Second half: ";
    secondHalf.display_forward();
    
    std::cout << "\n--- Merge Operation ---" << std::endl;
    list.merge(secondHalf);
    list.display_forward();
    
    std::cout << "\n--- Bidirectional Search ---" << std::endl;
    std::cout << "Forward search for 'D': Position " << list.find('D') << std::endl;
    std::cout << "Backward search for 'D': Position " << list.find_reverse('D') << std::endl;
}

void demonstrateErrorHandling() {
    printSeparator("ERROR HANDLING");
    
    DoublyLinkedList<int> list;
    
    std::cout << "\n--- Operations on Empty List ---" << std::endl;
    list.display_forward();
    list.display_backward();
    list.pop_front();
    list.pop_back();
    
    try {
        std::cout << "Trying to access front of empty list..." << std::endl;
        int front = list.front();
        std::cout << "Front: " << front << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "Trying to get element at position 0 from empty list..." << std::endl;
        int element = list.get(0);
        std::cout << "Element: " << element << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    // Add some elements and test out of bounds
    list.push_back(10);
    list.push_back(20);
    
    std::cout << "\n--- Out of Bounds Test ---" << std::endl;
    list.display_forward();
    list.update(10, 100); // Out of bounds
    list.remove_at(10);   // Out of bounds
}

void demonstrateStringList() {
    printSeparator("STRING DOUBLY LINKED LIST");
    
    DoublyLinkedList<std::string> stringList;
    
    // Add some strings
    stringList.push_back("Hello");
    stringList.push_back("World");
    stringList.push_front("Hi");
    stringList.push_back("C++");
    stringList.insert(2, "Beautiful");
    
    std::cout << "\n--- Forward and Backward Display ---" << std::endl;
    stringList.display_forward();
    stringList.display_backward();
    
    std::cout << "\nSearching for 'World':" << std::endl;
    std::cout << "Forward search: Position " << stringList.find("World") << std::endl;
    std::cout << "Backward search: Position " << stringList.find_reverse("World") << std::endl;
    
    std::cout << "Front element: " << stringList.front() << std::endl;
    std::cout << "Back element: " << stringList.back() << std::endl;
    std::cout << "Middle element: " << stringList.get_middle() << std::endl;
    
    stringList.sort();
    std::cout << "\nAfter sorting:" << std::endl;
    stringList.display_forward();
}

void demonstratePerformanceOptimization() {
    printSeparator("PERFORMANCE OPTIMIZATION");
    
    DoublyLinkedList<int> list;
    
    // Add many elements
    for (int i = 1; i <= 10; ++i) {
        list.push_back(i * 10);
    }
    
    list.display_forward();
    
    std::cout << "\n--- Optimized Access ---" << std::endl;
    std::cout << "Accessing element at position 2 (from head): " << list.get(2) << std::endl;
    std::cout << "Accessing element at position 8 (from tail): " << list.get(8) << std::endl;
    
    std::cout << "\n--- Optimized Update ---" << std::endl;
    list.update(1, 999);  // Close to head
    list.update(9, 888);  // Close to tail
    list.display_forward();
    
    std::cout << "\n--- Optimized Removal ---" << std::endl;
    list.remove_at(1);   // Close to head
    list.remove_at(7);   // Close to tail (adjusted for previous removal)
    list.display_forward();
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "    DOUBLY LINKED LIST DEMONSTRATION          " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateSearchOperations();
        demonstrateRemovalOperations();
        demonstrateAdvancedOperations();
        demonstrateDoublySpecificFeatures();
        demonstratePerformanceOptimization();
        demonstrateErrorHandling();
        demonstrateStringList();
        
        printSeparator("PERFORMANCE CHARACTERISTICS");
        std::cout << "\nTime Complexity Summary:" << std::endl;
        std::cout << "- Access:    O(n/2) avg, O(n) worst - Can start from either end" << std::endl;
        std::cout << "- Search:    O(n) - Can search forward or backward" << std::endl;
        std::cout << "- Insert:    O(1) at known position, O(n/2) avg arbitrary" << std::endl;
        std::cout << "- Delete:    O(1) at known position, O(n/2) avg arbitrary" << std::endl;
        std::cout << "- Space:     O(n) - Two pointers per node" << std::endl;
        
        std::cout << "\nAdvantages over Singly Linked List:" << std::endl;
        std::cout << "✅ Bidirectional traversal" << std::endl;
        std::cout << "✅ O(1) deletion with node reference" << std::endl;
        std::cout << "✅ Efficient operations at both ends" << std::endl;
        std::cout << "✅ Better average performance for access/insert/delete" << std::endl;
        
        std::cout << "\nDisadvantages:" << std::endl;
        std::cout << "❌ Extra memory for prev pointers" << std::endl;
        std::cout << "❌ More complex implementation" << std::endl;
        std::cout << "❌ Additional pointer maintenance overhead" << std::endl;
        
        std::cout << "\nCommon Use Cases:" << std::endl;
        std::cout << "🎯 Browser history (back/forward)" << std::endl;
        std::cout << "🎯 Undo/Redo functionality" << std::endl;
        std::cout << "🎯 Music players (previous/next)" << std::endl;
        std::cout << "🎯 Cache implementations (LRU)" << std::endl;
        std::cout << "🎯 Text editors (cursor movement)" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
