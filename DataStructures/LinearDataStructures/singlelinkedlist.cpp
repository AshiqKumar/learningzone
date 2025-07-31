/*
================================================================================
                        SINGLY LINKED LIST IMPLEMENTATION
================================================================================
* Author: Ashiq Kumar
* Date: 2018
* Updated: 2025 - Enhanced with modern C++ features
* 
* 🔥 COMPLETE IMPLEMENTATION FEATURES:
* 
* CORE OPERATIONS:
* ✅ Push Front/Back - Add elements at beginning/end
* ✅ Pop Front/Back - Remove elements from beginning/end
* ✅ Insert at Position - Insert at any position
* ✅ Remove at Position - Remove from any position
* 
* SEARCH & ACCESS:
* ✅ Find Element - Get position of element
* ✅ Contains Check - Boolean existence check
* ✅ Get Element - Access by index
* ✅ Front/Back Access - Get first/last elements
* ✅ Get Middle - Find middle element using two-pointer technique
* 
* ADVANCED OPERATIONS:
* ✅ Reverse List - Reverse the entire list
* ✅ Sort List - Bubble sort implementation
* ✅ Remove Duplicates - Remove duplicate values
* ✅ Update Element - Modify element at position
* ✅ Clear List - Remove all elements
* 
* UTILITY FEATURES:
* ✅ Display - Show list contents
* ✅ Display with Positions - Show elements with their positions
* ✅ Size/Empty checks - Get size and check if empty
* ✅ Template Support - Works with any data type
* 
* MEMORY MANAGEMENT:
* ✅ Smart Pointers - Uses std::unique_ptr for automatic memory management
* ✅ RAII Principles - No memory leaks
* ✅ Exception Safety - Proper error handling
* 
* COMPREHENSIVE DEMONSTRATIONS:
* - Basic Operations - Push, insert, access
* - Search Operations - Find, contains
* - Removal Operations - Pop, remove at position
* - Advanced Operations - Sort, reverse, remove duplicates
* - Error Handling - Empty list, out of bounds
* - String List - Template usage with strings
* 
* EDUCATIONAL FEATURES:
* 📊 Performance Analysis - Time/space complexity summary
* 📋 Advantages/Disadvantages - Clear pros and cons
* 🔍 Error Handling - Comprehensive exception handling
* 📝 Clear Output - Formatted demonstrations
* 
* The program is production-ready with modern C++ practices, comprehensive 
* error handling, and educational value. You can compile and run it to see 
* all the linked list operations in action!
* 
* COMPILATION:
* g++ -std=c++14 -o singlelinkedlist singlelinkedlist.cpp
* 
* USAGE:
* ./singlelinkedlist
* 
================================================================================
*/

#include <iostream>
#include <memory>

template<typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };
    
    std::unique_ptr<Node> head_;
    size_t size_;
    
public:
    // Constructor
    SinglyLinkedList() : head_(nullptr), size_(0) {}
    
    // Destructor (automatic with smart pointers)
    ~SinglyLinkedList() = default;
    
    // Add element at the beginning
    void push_front(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(head_);
        head_ = std::move(newNode);
        size_++;
        std::cout << "Added " << value << " at front" << std::endl;
    }
    
    // Add element at the end
    void push_back(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        
        if (!head_) {
            head_ = std::move(newNode);
        } else {
            Node* current = head_.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::move(newNode);
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
        Node* current = head_.get();
        
        for (size_t i = 0; i < position - 1; ++i) {
            current = current->next.get();
        }
        
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
        size_++;
        std::cout << "Inserted " << value << " at position " << position << std::endl;
    }
    
    // Remove from front
    void pop_front() {
        if (head_) {
            std::cout << "Removed " << head_->data << " from front" << std::endl;
            head_ = std::move(head_->next);
            size_--;
        } else {
            std::cout << "List is empty" << std::endl;
        }
    }
    
    // Remove from back
    void pop_back() {
        if (!head_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        if (!head_->next) {
            std::cout << "Removed " << head_->data << " from back" << std::endl;
            head_.reset();
            size_--;
            return;
        }
        
        Node* current = head_.get();
        while (current->next->next) {
            current = current->next.get();
        }
        
        std::cout << "Removed " << current->next->data << " from back" << std::endl;
        current->next.reset();
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
        
        Node* current = head_.get();
        for (size_t i = 0; i < position - 1; ++i) {
            current = current->next.get();
        }
        
        if (current->next) {
            std::cout << "Removed " << current->next->data << " at position " << position << std::endl;
            current->next = std::move(current->next->next);
            size_--;
        }
    }
    
    // Find element and return its position
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
        
        return -1; // Not found
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
        
        Node* current = head_.get();
        for (size_t i = 0; i < position; ++i) {
            current = current->next.get();
        }
        
        return current->data;
    }
    
    // Update element at specific position
    void update(size_t position, const T& value) {
        if (position >= size_) {
            std::cout << "Position " << position << " is out of bounds" << std::endl;
            return;
        }
        
        Node* current = head_.get();
        for (size_t i = 0; i < position; ++i) {
            current = current->next.get();
        }
        
        T oldValue = current->data;
        current->data = value;
        std::cout << "Updated position " << position << " from " << oldValue << " to " << value << std::endl;
    }
    
    // Reverse the list
    void reverse() {
        std::unique_ptr<Node> prev = nullptr;
        std::unique_ptr<Node> current = std::move(head_);
        
        while (current) {
            auto next = std::move(current->next);
            current->next = std::move(prev);
            prev = std::move(current);
            current = std::move(next);
        }
        
        head_ = std::move(prev);
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
    
    // Remove duplicates
    void remove_duplicates() {
        if (!head_) return;
        
        Node* current = head_.get();
        
        while (current && current->next) {
            if (current->data == current->next->data) {
                current->next = std::move(current->next->next);
                size_--;
            } else {
                current = current->next.get();
            }
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
    
    // Display list
    void display() const {
        if (!head_) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        
        std::cout << "List: ";
        Node* current = head_.get();
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " -> ";
            current = current->next.get();
        }
        std::cout << " -> nullptr" << std::endl;
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
        if (!head_) {
            throw std::runtime_error("List is empty");
        }
        
        Node* current = head_.get();
        while (current->next) {
            current = current->next.get();
        }
        
        return current->data;
    }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void demonstrateBasicOperations() {
    printSeparator("BASIC OPERATIONS");
    
    SinglyLinkedList<int> list;
    
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
    
    try {
        std::cout << "Middle element: " << list.get_middle() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void demonstrateSearchOperations() {
    printSeparator("SEARCH OPERATIONS");
    
    SinglyLinkedList<int> list;
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
    
    SinglyLinkedList<int> list;
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
    
    SinglyLinkedList<int> list;
    
    // Create unsorted list with duplicates
    int values[] = {30, 10, 40, 10, 20, 30, 50, 20};
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
    
    std::cout << "\n--- Remove Duplicates ---" << std::endl;
    list.remove_duplicates();
    list.display();
    
    std::cout << "\n--- Reverse Operation ---" << std::endl;
    list.reverse();
    list.display();
}

void demonstrateErrorHandling() {
    printSeparator("ERROR HANDLING");
    
    SinglyLinkedList<int> list;
    
    std::cout << "\n--- Operations on Empty List ---" << std::endl;
    list.display();
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
    list.display();
    list.update(10, 100); // Out of bounds
    list.remove_at(10);   // Out of bounds
}

void demonstrateStringList() {
    printSeparator("STRING LINKED LIST");
    
    SinglyLinkedList<std::string> stringList;
    
    // Add some strings
    stringList.push_back("Hello");
    stringList.push_back("World");
    stringList.push_front("Hi");
    stringList.push_back("C++");
    stringList.insert(2, "Beautiful");
    
    stringList.display();
    
    std::cout << "\nSearching for 'World': Position " << stringList.find("World") << std::endl;
    std::cout << "Middle element: " << stringList.get_middle() << std::endl;
    
    stringList.sort();
    stringList.display();
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   SINGLY LINKED LIST DEMONSTRATION    " << std::endl;
    std::cout << "========================================" << std::endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateSearchOperations();
        demonstrateRemovalOperations();
        demonstrateAdvancedOperations();
        demonstrateErrorHandling();
        demonstrateStringList();
        
        printSeparator("PERFORMANCE CHARACTERISTICS");
        std::cout << "\nTime Complexity Summary:" << std::endl;
        std::cout << "- Access:    O(n) - Must traverse from head" << std::endl;
        std::cout << "- Search:    O(n) - Linear search required" << std::endl;
        std::cout << "- Insert:    O(1) at known position, O(n) arbitrary" << std::endl;
        std::cout << "- Delete:    O(1) at known position, O(n) arbitrary" << std::endl;
        std::cout << "- Space:     O(n) - One node per element" << std::endl;
        
        std::cout << "\nAdvantages:" << std::endl;
        std::cout << "✅ Dynamic size" << std::endl;
        std::cout << "✅ Efficient insertion/deletion at front" << std::endl;
        std::cout << "✅ Memory allocated as needed" << std::endl;
        
        std::cout << "\nDisadvantages:" << std::endl;
        std::cout << "❌ No random access" << std::endl;
        std::cout << "❌ Extra memory for pointers" << std::endl;
        std::cout << "❌ Not cache-friendly" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "        DEMONSTRATION COMPLETE         " << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}
