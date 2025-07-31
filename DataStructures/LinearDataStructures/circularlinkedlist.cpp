// Circular Linked List Implementation - Complete program with all operations
/*
Circular Linked List Features:
Core Operations:
✅ Push Front/Back - Add elements at beginning/end
✅ Pop Front/Back - Remove elements from beginning/end
✅ Insert at Position - Insert at any position
✅ Remove at Position - Remove from any position
Search & Access:
✅ Find Element - Get position of element with circular traversal
✅ Contains Check - Boolean existence check
✅ Get Element - Access by index
✅ Front/Back Access - Get first/last elements
Circular-Specific Operations:
✅ Display Cycles - Show multiple complete cycles
✅ Rotate List - Rotate by k positions (forward/backward)
✅ Split List - Divide into two equal halves
✅ Circular Check - Verify list maintains circular property
Advanced Operations:
✅ Reverse List - Reverse the entire circular list
✅ Sort List - Bubble sort with circular traversal
✅ Update Element - Modify element at position

Memory Management:
✅ Smart Pointers - Uses std::shared_ptr for circular references
✅ Proper Cleanup - Breaks circular links to prevent memory leaks
✅ RAII Principles - Automatic resource management

Key Differences from Singly Linked List:
🔄 Circular Structure:
Last node points back to first node
No NULL pointers in a non-empty list
Can traverse infinitely
📍 Tail Pointer:
Maintains pointer to tail for O(1) access to both ends
Head is always tail_->next
🔍 Traversal:
Uses do-while loops to handle circular nature
Stops when returning to starting point
🔧 Special Features:
Rotation - Circular shift of elements
Cycles Display - Show multiple rounds
Split - Divide into two circular lists

Comprehensive Demonstrations:
Basic Operations - Push, insert, access
Search Operations - Find, contains
Removal Operations - Pop, remove at position
Advanced Operations - Sort, reverse, rotate
Circular Features - Cycles, split, rotation
Error Handling - Empty list, out of bounds
String List - Template usage with strings
Performance Characteristics:
Time Complexity: Same as singly linked list
Space Complexity: O(n) - one node per element
Advantages: Efficient operations at both ends, no NULL pointers
Use Cases: Round-robin scheduling, circular buffers, playlists
The program is production-ready with modern C++ practices, comprehensive error handling, and demonstrates all the unique features of circular linked lists!
*/

#include <iostream>
#include <memory>
#include <stdexcept>

template<typename T>
class CircularLinkedList {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };
    
    std::shared_ptr<Node> tail_;  // Points to the last node
    size_t size_;
    
public:
    // Constructor
    CircularLinkedList() : tail_(nullptr), size_(0) {}
    
    // Destructor
    ~CircularLinkedList() {
        clear();
    }
    
    // Add element at the beginning
    void push_front(const T& value) {
        auto newNode = std::make_shared<Node>(value);
        
        if (!tail_) {
            // First node - points to itself
            tail_ = newNode;
            newNode->next = newNode;
        } else {
            // Insert at beginning (after tail, before head)
            newNode->next = tail_->next;  // Point to current head
            tail_->next = newNode;        // Tail points to new head
        }
        
        size_++;
        std::cout << "Added " << value << " at front" << std::endl;
    }
    
    // Add element at the end
    void push_back(const T& value) {
        auto newNode = std::make_shared<Node>(value);
        
        if (!tail_) {
            // First node - points to itself
            tail_ = newNode;
            newNode->next = newNode;
        } else {
            // Insert at end
            newNode->next = tail_->next;  // Point to head
            tail_->next = newNode;        // Old tail points to new node
            tail_ = newNode;              // Update tail pointer
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
        
        auto newNode = std::make_shared<Node>(value);
        auto current = tail_->next;  // Start from head
        
        // Traverse to position - 1
        for (size_t i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        size_++;
        
        std::cout << "Inserted " << value << " at position " << position << std::endl;
    }
    
    // Remove from front
    void pop_front() {
        if (!tail_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        auto head = tail_->next;
        std::cout << "Removed " << head->data << " from front" << std::endl;
        
        if (size_ == 1) {
            // Only one node
            tail_.reset();
        } else {
            tail_->next = head->next;  // Skip the head node
        }
        
        size_--;
    }
    
    // Remove from back
    void pop_back() {
        if (!tail_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        std::cout << "Removed " << tail_->data << " from back" << std::endl;
        
        if (size_ == 1) {
            // Only one node
            tail_.reset();
        } else {
            // Find the node before tail
            auto current = tail_->next;  // Start from head
            while (current->next != tail_) {
                current = current->next;
            }
            
            current->next = tail_->next;  // Point to head
            tail_ = current;              // Update tail
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
        
        auto current = tail_->next;  // Start from head
        
        // Traverse to position - 1
        for (size_t i = 0; i < position - 1; ++i) {
            current = current->next;
        }
        
        auto nodeToRemove = current->next;
        std::cout << "Removed " << nodeToRemove->data << " at position " << position << std::endl;
        
        current->next = nodeToRemove->next;
        size_--;
    }
    
    // Find element and return its position
    int find(const T& value) const {
        if (!tail_) return -1;
        
        auto current = tail_->next;  // Start from head
        int position = 0;
        
        do {
            if (current->data == value) {
                return position;
            }
            current = current->next;
            position++;
        } while (current != tail_->next);
        
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
        
        auto current = tail_->next;  // Start from head
        for (size_t i = 0; i < position; ++i) {
            current = current->next;
        }
        
        return current->data;
    }
    
    // Update element at specific position
    void update(size_t position, const T& value) {
        if (position >= size_) {
            std::cout << "Position " << position << " is out of bounds" << std::endl;
            return;
        }
        
        auto current = tail_->next;  // Start from head
        for (size_t i = 0; i < position; ++i) {
            current = current->next;
        }
        
        T oldValue = current->data;
        current->data = value;
        std::cout << "Updated position " << position << " from " << oldValue << " to " << value << std::endl;
    }
    
    // Reverse the list
    void reverse() {
        if (!tail_ || size_ <= 1) {
            std::cout << "List reversed (nothing to reverse)" << std::endl;
            return;
        }
        
        auto prev = tail_;
        auto current = tail_->next;  // Start from head
        auto head = current;
        
        do {
            auto next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        } while (current != head);
        
        tail_ = head;  // Old head becomes new tail
        std::cout << "List reversed" << std::endl;
    }
    
    // Sort the list (bubble sort)
    void sort() {
        if (size_ <= 1) return;
        
        bool swapped;
        do {
            swapped = false;
            auto current = tail_->next;  // Start from head
            
            for (size_t i = 0; i < size_ - 1; ++i) {
                if (current->data > current->next->data) {
                    // Swap data
                    T temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        
        std::cout << "List sorted" << std::endl;
    }
    
    // Split the list into two equal halves
    std::pair<CircularLinkedList<T>, CircularLinkedList<T>> split() {
        CircularLinkedList<T> first, second;
        
        if (size_ <= 1) {
            if (size_ == 1) {
                first.push_back(tail_->data);
            }
            return {std::move(first), std::move(second)};
        }
        
        size_t mid = size_ / 2;
        auto current = tail_->next;  // Start from head
        
        // Add first half
        for (size_t i = 0; i < mid; ++i) {
            first.push_back(current->data);
            current = current->next;
        }
        
        // Add second half
        for (size_t i = mid; i < size_; ++i) {
            second.push_back(current->data);
            current = current->next;
        }
        
        std::cout << "List split into two halves" << std::endl;
        return {std::move(first), std::move(second)};
    }
    
    // Rotate the list by k positions
    void rotate(int k) {
        if (!tail_ || size_ <= 1 || k == 0) return;
        
        // Normalize k to be within [0, size)
        k = ((k % static_cast<int>(size_)) + size_) % size_;
        
        if (k == 0) return;
        
        // Find the new tail (k positions from current head)
        auto newTail = tail_->next;  // Start from head
        for (int i = 0; i < k - 1; ++i) {
            newTail = newTail->next;
        }
        
        tail_ = newTail;
        std::cout << "List rotated by " << k << " positions" << std::endl;
    }
    
    // Display list
    void display() const {
        if (!tail_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        std::cout << "Circular List: ";
        auto current = tail_->next;  // Start from head
        
        do {
            std::cout << current->data;
            current = current->next;
            if (current != tail_->next) std::cout << " -> ";
        } while (current != tail_->next);
        
        std::cout << " -> (back to head)" << std::endl;
    }
    
    // Display with positions
    void display_with_positions() const {
        if (!tail_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        std::cout << "Circular List with positions:" << std::endl;
        auto current = tail_->next;  // Start from head
        int position = 0;
        
        do {
            std::cout << "Position " << position << ": " << current->data << std::endl;
            current = current->next;
            position++;
        } while (current != tail_->next);
    }
    
    // Display n complete cycles
    void display_cycles(int cycles) const {
        if (!tail_ || cycles <= 0) {
            std::cout << "Cannot display cycles" << std::endl;
            return;
        }
        
        std::cout << "Showing " << cycles << " complete cycles:" << std::endl;
        auto current = tail_->next;  // Start from head
        
        for (int cycle = 0; cycle < cycles; ++cycle) {
            std::cout << "Cycle " << (cycle + 1) << ": ";
            
            for (size_t i = 0; i < size_; ++i) {
                std::cout << current->data;
                current = current->next;
                if (i < size_ - 1) std::cout << " -> ";
            }
            std::cout << std::endl;
        }
    }
    
    // Get size
    size_t size() const { 
        return size_; 
    }
    
    // Check if empty
    bool empty() const { 
        return tail_ == nullptr; 
    }
    
    // Clear the list
    void clear() {
        if (!tail_) return;
        
        // Break the circular link to prevent infinite destruction
        auto head = tail_->next;
        tail_->next.reset();
        tail_.reset();
        
        size_ = 0;
        std::cout << "List cleared" << std::endl;
    }
    
    // Get front element
    T front() const {
        if (!tail_) {
            throw std::runtime_error("List is empty");
        }
        return tail_->next->data;
    }
    
    // Get back element
    T back() const {
        if (!tail_) {
            throw std::runtime_error("List is empty");
        }
        return tail_->data;
    }
    
    // Check if the list is properly circular
    bool is_circular() const {
        if (!tail_) return true;  // Empty list is considered circular
        
        auto slow = tail_->next;
        auto fast = tail_->next;
        
        do {
            slow = slow->next;
            fast = fast->next->next;
        } while (slow != fast && fast != tail_->next && fast->next != tail_->next);
        
        return slow == fast;
    }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(55, '=') << std::endl;
}

void demonstrateBasicOperations() {
    printSeparator("BASIC OPERATIONS");
    
    CircularLinkedList<int> list;
    
    // Test push operations
    std::cout << "\n--- Push Operations ---" << std::endl;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);
    list.display();
    
    // Test insert operation
    std::cout << "\n--- Insert Operations ---" << std::endl;
    list.insert(2, 15);
    list.insert(0, 1);
    list.insert(100, 50); // Insert at end
    list.display();
    
    // Test access operations
    std::cout << "\n--- Access Operations ---" << std::endl;
    std::cout << "Size: " << list.size() << std::endl;
    std::cout << "Front: " << list.front() << std::endl;
    std::cout << "Back: " << list.back() << std::endl;
    std::cout << "Element at position 3: " << list.get(3) << std::endl;
    std::cout << "Is circular: " << (list.is_circular() ? "Yes" : "No") << std::endl;
}

void demonstrateSearchOperations() {
    printSeparator("SEARCH OPERATIONS");
    
    CircularLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(20);
    list.push_back(40);
    list.display();
    
    // Test find operations
    std::cout << "\n--- Find Operations ---" << std::endl;
    std::cout << "Find 20: Position " << list.find(20) << std::endl;
    std::cout << "Find 100: Position " << list.find(100) << std::endl;
    std::cout << "Contains 30: " << (list.contains(30) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 100: " << (list.contains(100) ? "Yes" : "No") << std::endl;
}

void demonstrateRemovalOperations() {
    printSeparator("REMOVAL OPERATIONS");
    
    CircularLinkedList<int> list;
    for (int i = 1; i <= 6; ++i) {
        list.push_back(i * 10);
    }
    
    std::cout << "\n--- Initial List ---" << std::endl;
    list.display();
    
    std::cout << "\n--- Pop Operations ---" << std::endl;
    list.pop_front();
    list.display();
    
    list.pop_back();
    list.display();
    
    std::cout << "\n--- Remove at Position ---" << std::endl;
    list.remove_at(1);
    list.display();
    
    list.remove_at(10); // Out of bounds test
}

void demonstrateAdvancedOperations() {
    printSeparator("ADVANCED OPERATIONS");
    
    CircularLinkedList<int> list;
    
    // Create unsorted list
    int values[] = {30, 10, 40, 20, 50};
    for (int val : values) {
        list.push_back(val);
    }
    
    std::cout << "\n--- Original List ---" << std::endl;
    list.display();
    list.display_with_positions();
    
    std::cout << "\n--- Update Operation ---" << std::endl;
    list.update(2, 25);
    list.display();
    
    std::cout << "\n--- Sort Operation ---" << std::endl;
    list.sort();
    list.display();
    
    std::cout << "\n--- Reverse Operation ---" << std::endl;
    list.reverse();
    list.display();
    
    std::cout << "\n--- Rotation Operations ---" << std::endl;
    list.rotate(2);
    list.display();
    
    list.rotate(-1);  // Rotate backward
    list.display();
}

void demonstrateCircularFeatures() {
    printSeparator("CIRCULAR-SPECIFIC FEATURES");
    
    CircularLinkedList<char> list;
    
    // Add letters
    for (char c = 'A'; c <= 'E'; ++c) {
        list.push_back(c);
    }
    
    std::cout << "\n--- Circular Display ---" << std::endl;
    list.display();
    
    std::cout << "\n--- Multiple Cycles ---" << std::endl;
    list.display_cycles(3);
    
    std::cout << "\n--- Split Operation ---" << std::endl;
    auto [first, second] = list.split();
    std::cout << "First half: ";
    first.display();
    std::cout << "Second half: ";
    second.display();
    
    std::cout << "\n--- Circular Property Check ---" << std::endl;
    std::cout << "Original list is circular: " << (list.is_circular() ? "Yes" : "No") << std::endl;
    std::cout << "First half is circular: " << (first.is_circular() ? "Yes" : "No") << std::endl;
}

void demonstrateErrorHandling() {
    printSeparator("ERROR HANDLING");
    
    CircularLinkedList<int> list;
    
    std::cout << "\n--- Operations on Empty List ---" << std::endl;
    list.display();
    list.pop_front();
    list.pop_back();
    list.display_cycles(1);
    
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
    list.display();
    list.update(10, 100); // Out of bounds
    list.remove_at(10);   // Out of bounds
}

void demonstrateStringList() {
    printSeparator("STRING CIRCULAR LIST");
    
    CircularLinkedList<std::string> stringList;
    
    // Add some strings
    stringList.push_back("Hello");
    stringList.push_back("World");
    stringList.push_front("Hi");
    stringList.push_back("C++");
    stringList.insert(2, "Beautiful");
    
    stringList.display();
    
    std::cout << "\nSearching for 'World': Position " << stringList.find("World") << std::endl;
    std::cout << "Front element: " << stringList.front() << std::endl;
    std::cout << "Back element: " << stringList.back() << std::endl;
    
    std::cout << "\n--- Showing 2 cycles ---" << std::endl;
    stringList.display_cycles(2);
    
    stringList.sort();
    std::cout << "\nAfter sorting:" << std::endl;
    stringList.display();
}

int main() {
    std::cout << "============================================" << std::endl;
    std::cout << "   CIRCULAR LINKED LIST DEMONSTRATION      " << std::endl;
    std::cout << "============================================" << std::endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateSearchOperations();
        demonstrateRemovalOperations();
        demonstrateAdvancedOperations();
        demonstrateCircularFeatures();
        demonstrateErrorHandling();
        demonstrateStringList();
        
        printSeparator("PERFORMANCE CHARACTERISTICS");
        std::cout << "\nTime Complexity Summary:" << std::endl;
        std::cout << "- Access:    O(n) - Must traverse from head/tail" << std::endl;
        std::cout << "- Search:    O(n) - Linear search required" << std::endl;
        std::cout << "- Insert:    O(1) at known position, O(n) arbitrary" << std::endl;
        std::cout << "- Delete:    O(1) at known position, O(n) arbitrary" << std::endl;
        std::cout << "- Space:     O(n) - One node per element" << std::endl;
        
        std::cout << "\nAdvantages:" << std::endl;
        std::cout << "✅ Efficient insertion/deletion at both ends" << std::endl;
        std::cout << "✅ No NULL pointers - always connected" << std::endl;
        std::cout << "✅ Useful for round-robin algorithms" << std::endl;
        std::cout << "✅ Can traverse infinitely" << std::endl;
        
        std::cout << "\nDisadvantages:" << std::endl;
        std::cout << "❌ More complex than singly linked list" << std::endl;
        std::cout << "❌ Risk of infinite loops if not handled properly" << std::endl;
        std::cout << "❌ Extra care needed for memory management" << std::endl;
        
        std::cout << "\nCommon Use Cases:" << std::endl;
        std::cout << "🎯 Round-robin scheduling" << std::endl;
        std::cout << "🎯 Circular buffers" << std::endl;
        std::cout << "🎯 Multiplayer games (turn-based)" << std::endl;
        std::cout << "🎯 Music playlists (repeat mode)" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n============================================" << std::endl;
    std::cout << "         DEMONSTRATION COMPLETE            " << std::endl;
    std::cout << "============================================" << std::endl;
    
    return 0;
}
