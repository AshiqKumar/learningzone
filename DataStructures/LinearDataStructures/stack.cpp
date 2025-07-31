// Stack Implementation - Complete program with all operations
/*
Key Features of Stack (LIFO - Last In First Out):
Core Operations:
✅ Push: Add element to top in O(1)
✅ Pop: Remove element from top in O(1)
✅ Top/Peek: Access top element in O(1)
✅ Empty Check: Check if stack is empty in O(1)
Stack-Specific Features:
📚 LIFO Principle: Last element added is first to be removed
🎯 Single Point Access: Only top element is accessible
⚡ Constant Time Operations: All basic operations are O(1)
💾 Memory Efficient: Contiguous memory allocation
Advanced Features:
🔍 Search: Find element position from top
📊 Display: Show stack contents (top to bottom)
🗑️ Clear: Remove all elements
📏 Size Tracking: Current number of elements
Smart Memory Management:
🧠 Uses std::vector for dynamic resizing
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
#include <vector>
#include <stdexcept>
#include <string>
#include <memory>

// Array-based Stack Implementation
template<typename T>
class ArrayStack {
private:
    std::vector<T> data_;
    
public:
    // Constructor
    ArrayStack() = default;
    
    // Constructor with initial capacity
    explicit ArrayStack(size_t capacity) {
        data_.reserve(capacity);
    }
    
    // Push element to top
    void push(const T& value) {
        data_.push_back(value);
        std::cout << "Pushed " << value << " to stack" << std::endl;
    }
    
    // Pop element from top
    void pop() {
        if (empty()) {
            std::cout << "Stack is empty - cannot pop" << std::endl;
            return;
        }
        
        std::cout << "Popped " << data_.back() << " from stack" << std::endl;
        data_.pop_back();
    }
    
    // Get top element without removing
    T top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data_.back();
    }
    
    // Peek at top element (alias for top)
    T peek() const {
        return top();
    }
    
    // Check if stack is empty
    bool empty() const {
        return data_.empty();
    }
    
    // Get size of stack
    size_t size() const {
        return data_.size();
    }
    
    // Get capacity (for vector-based implementation)
    size_t capacity() const {
        return data_.capacity();
    }
    
    // Clear all elements
    void clear() {
        data_.clear();
        std::cout << "Stack cleared" << std::endl;
    }
    
    // Search for element (returns position from top, -1 if not found)
    int search(const T& value) const {
        for (int i = data_.size() - 1; i >= 0; --i) {
            if (data_[i] == value) {
                return data_.size() - 1 - i; // Position from top (0-based)
            }
        }
        return -1; // Not found
    }
    
    // Display stack contents (top to bottom)
    void display() const {
        if (empty()) {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        
        std::cout << "Stack (top to bottom): ";
        for (int i = data_.size() - 1; i >= 0; --i) {
            std::cout << data_[i];
            if (i > 0) std::cout << " -> ";
        }
        std::cout << " -> [bottom]" << std::endl;
    }
    
    // Display with positions
    void display_with_positions() const {
        if (empty()) {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        
        std::cout << "Stack with positions from top:" << std::endl;
        for (int i = data_.size() - 1; i >= 0; --i) {
            std::cout << "Position " << (data_.size() - 1 - i) << ": " << data_[i] << std::endl;
        }
    }
    
    // Get element at position from top (0 = top element)
    T at(size_t position) const {
        if (position >= size()) {
            throw std::out_of_range("Position out of bounds");
        }
        return data_[size() - 1 - position];
    }
};

// Linked List-based Stack Implementation
template<typename T>
class LinkedStack {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };
    
    std::unique_ptr<Node> top_;
    size_t size_;
    
public:
    // Constructor
    LinkedStack() : top_(nullptr), size_(0) {}
    
    // Push element to top
    void push(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(top_);
        top_ = std::move(newNode);
        size_++;
        std::cout << "Pushed " << value << " to stack" << std::endl;
    }
    
    // Pop element from top
    void pop() {
        if (empty()) {
            std::cout << "Stack is empty - cannot pop" << std::endl;
            return;
        }
        
        std::cout << "Popped " << top_->data << " from stack" << std::endl;
        top_ = std::move(top_->next);
        size_--;
    }
    
    // Get top element without removing
    T top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return top_->data;
    }
    
    // Peek at top element (alias for top)
    T peek() const {
        return top();
    }
    
    // Check if stack is empty
    bool empty() const {
        return top_ == nullptr;
    }
    
    // Get size of stack
    size_t size() const {
        return size_;
    }
    
    // Clear all elements
    void clear() {
        while (!empty()) {
            pop();
        }
        std::cout << "Stack cleared" << std::endl;
    }
    
    // Search for element (returns position from top, -1 if not found)
    int search(const T& value) const {
        Node* current = top_.get();
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
    
    // Display stack contents (top to bottom)
    void display() const {
        if (empty()) {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        
        std::cout << "Stack (top to bottom): ";
        Node* current = top_.get();
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " -> ";
            current = current->next.get();
        }
        std::cout << " -> [bottom]" << std::endl;
    }
    
    // Display with positions
    void display_with_positions() const {
        if (empty()) {
            std::cout << "Stack is empty" << std::endl;
            return;
        }
        
        std::cout << "Stack with positions from top:" << std::endl;
        Node* current = top_.get();
        int position = 0;
        
        while (current) {
            std::cout << "Position " << position << ": " << current->data << std::endl;
            current = current->next.get();
            position++;
        }
    }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(55, '=') << std::endl;
}

void demonstrateArrayStack() {
    printSeparator("ARRAY-BASED STACK OPERATIONS");
    
    ArrayStack<int> stack(5); // Initial capacity of 5
    
    std::cout << "\n--- Basic Stack Operations ---" << std::endl;
    std::cout << "Is empty: " << (stack.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Size: " << stack.size() << std::endl;
    std::cout << "Capacity: " << stack.capacity() << std::endl;
    
    // Push elements
    std::cout << "\n--- Push Operations ---" << std::endl;
    for (int i = 10; i <= 50; i += 10) {
        stack.push(i);
    }
    
    stack.display();
    stack.display_with_positions();
    std::cout << "Size: " << stack.size() << std::endl;
    std::cout << "Capacity: " << stack.capacity() << std::endl;
    
    // Access top element
    std::cout << "\n--- Access Operations ---" << std::endl;
    try {
        std::cout << "Top element: " << stack.top() << std::endl;
        std::cout << "Peek element: " << stack.peek() << std::endl;
        std::cout << "Element at position 2 from top: " << stack.at(2) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Search operations
    std::cout << "\n--- Search Operations ---" << std::endl;
    std::cout << "Search for 30: Position " << stack.search(30) << std::endl;
    std::cout << "Search for 100: Position " << stack.search(100) << std::endl;
    
    // Pop operations
    std::cout << "\n--- Pop Operations ---" << std::endl;
    stack.pop();
    stack.pop();
    stack.display();
    
    std::cout << "Top after pops: " << stack.top() << std::endl;
}

void demonstrateLinkedStack() {
    printSeparator("LINKED LIST-BASED STACK OPERATIONS");
    
    LinkedStack<char> stack;
    
    std::cout << "\n--- Basic Stack Operations ---" << std::endl;
    std::cout << "Is empty: " << (stack.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Size: " << stack.size() << std::endl;
    
    // Push elements
    std::cout << "\n--- Push Operations ---" << std::endl;
    for (char c = 'A'; c <= 'E'; ++c) {
        stack.push(c);
    }
    
    stack.display();
    stack.display_with_positions();
    std::cout << "Size: " << stack.size() << std::endl;
    
    // Access top element
    std::cout << "\n--- Access Operations ---" << std::endl;
    try {
        std::cout << "Top element: " << stack.top() << std::endl;
        std::cout << "Peek element: " << stack.peek() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Search operations
    std::cout << "\n--- Search Operations ---" << std::endl;
    std::cout << "Search for 'C': Position " << stack.search('C') << std::endl;
    std::cout << "Search for 'Z': Position " << stack.search('Z') << std::endl;
    
    // Pop operations
    std::cout << "\n--- Pop Operations ---" << std::endl;
    while (!stack.empty()) {
        std::cout << "Top before pop: " << stack.top() << std::endl;
        stack.pop();
        std::cout << "Size after pop: " << stack.size() << std::endl;
    }
    
    // Try operations on empty stack
    std::cout << "\n--- Operations on Empty Stack ---" << std::endl;
    stack.pop(); // Should handle gracefully
    try {
        std::cout << "Top of empty stack: " << stack.top() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void demonstrateStackApplications() {
    printSeparator("STACK APPLICATIONS");
    
    // 1. Balanced Parentheses Check
    std::cout << "\n--- Balanced Parentheses Checker ---" << std::endl;
    auto checkBalanced = [](const std::string& expr) {
        ArrayStack<char> stack;
        
        for (char c : expr) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c);
            } else if (c == ')' || c == ']' || c == '}') {
                if (stack.empty()) return false;
                
                char top = stack.top();
                stack.pop();
                
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) {
                    return false;
                }
            }
        }
        
        return stack.empty();
    };
    
    std::vector<std::string> expressions = {
        "()",
        "()[]{}", 
        "([{}])",
        "([)]",
        "((("
    };
    
    for (const auto& expr : expressions) {
        std::cout << "Expression '" << expr << "' is " 
                  << (checkBalanced(expr) ? "balanced" : "not balanced") << std::endl;
    }
    
    // 2. Reverse a String
    std::cout << "\n--- String Reversal ---" << std::endl;
    auto reverseString = [](const std::string& str) {
        ArrayStack<char> stack;
        
        // Push all characters
        for (char c : str) {
            stack.push(c);
        }
        
        // Pop all characters to get reversed string
        std::string reversed;
        while (!stack.empty()) {
            reversed += stack.top();
            stack.pop();
        }
        
        return reversed;
    };
    
    std::string original = "Hello World!";
    std::string reversed = reverseString(original);
    std::cout << "Original: " << original << std::endl;
    std::cout << "Reversed: " << reversed << std::endl;
    
    // 3. Decimal to Binary Conversion
    std::cout << "\n--- Decimal to Binary Conversion ---" << std::endl;
    auto decimalToBinary = [](int decimal) {
        if (decimal == 0) return std::string("0");
        
        ArrayStack<int> stack;
        
        while (decimal > 0) {
            stack.push(decimal % 2);
            decimal /= 2;
        }
        
        std::string binary;
        while (!stack.empty()) {
            binary += std::to_string(stack.top());
            stack.pop();
        }
        
        return binary;
    };
    
    std::vector<int> numbers = {10, 25, 0, 128};
    for (int num : numbers) {
        std::cout << "Decimal " << num << " = Binary " << decimalToBinary(num) << std::endl;
    }
}

void demonstrateStringStack() {
    printSeparator("STRING STACK OPERATIONS");
    
    ArrayStack<std::string> stack;
    
    // Add some strings
    std::vector<std::string> words = {"Hello", "World", "Stack", "Data", "Structure"};
    
    std::cout << "\n--- Push String Operations ---" << std::endl;
    for (const auto& word : words) {
        stack.push(word);
    }
    
    stack.display();
    
    std::cout << "\n--- String Operations ---" << std::endl;
    std::cout << "Top string: " << stack.top() << std::endl;
    std::cout << "Search for 'Stack': Position " << stack.search("Stack") << std::endl;
    
    std::cout << "\n--- Pop String Operations ---" << std::endl;
    while (!stack.empty()) {
        std::cout << "Popping: " << stack.top() << std::endl;
        stack.pop();
    }
}

void demonstrateErrorHandling() {
    printSeparator("ERROR HANDLING");
    
    ArrayStack<int> stack;
    
    std::cout << "\n--- Error Handling Tests ---" << std::endl;
    
    // Test operations on empty stack
    try {
        stack.top();
    } catch (const std::exception& e) {
        std::cout << "Empty stack top() exception: " << e.what() << std::endl;
    }
    
    try {
        stack.at(0);
    } catch (const std::exception& e) {
        std::cout << "Empty stack at(0) exception: " << e.what() << std::endl;
    }
    
    // Add some elements and test out of bounds
    stack.push(10);
    stack.push(20);
    
    try {
        std::cout << "Valid at(1): " << stack.at(1) << std::endl;
        std::cout << "Invalid at(5): " << stack.at(5) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Out of bounds at(5) exception: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "         STACK DEMONSTRATION                  " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateArrayStack();
        demonstrateLinkedStack();
        demonstrateStackApplications();
        demonstrateStringStack();
        demonstrateErrorHandling();
        
        printSeparator("PERFORMANCE CHARACTERISTICS");
        std::cout << "\nTime Complexity Summary:" << std::endl;
        std::cout << "- Push:      O(1) - Constant time insertion" << std::endl;
        std::cout << "- Pop:       O(1) - Constant time removal" << std::endl;
        std::cout << "- Top/Peek:  O(1) - Constant time access" << std::endl;
        std::cout << "- Search:    O(n) - Linear search required" << std::endl;
        std::cout << "- Space:     O(n) - Linear space for n elements" << std::endl;
        
        std::cout << "\nArray vs Linked Implementation:" << std::endl;
        std::cout << "Array Stack:" << std::endl;
        std::cout << "  ✅ Cache-friendly (contiguous memory)" << std::endl;
        std::cout << "  ✅ Lower memory overhead per element" << std::endl;
        std::cout << "  ❌ May need reallocation for growth" << std::endl;
        
        std::cout << "Linked Stack:" << std::endl;
        std::cout << "  ✅ Dynamic size without reallocation" << std::endl;
        std::cout << "  ✅ No wasted memory" << std::endl;
        std::cout << "  ❌ Extra memory for pointers" << std::endl;
        std::cout << "  ❌ Not cache-friendly (scattered memory)" << std::endl;
        
        std::cout << "\nCommon Use Cases:" << std::endl;
        std::cout << "🎯 Function call management (call stack)" << std::endl;
        std::cout << "🎯 Expression evaluation and parsing" << std::endl;
        std::cout << "🎯 Undo operations in applications" << std::endl;
        std::cout << "🎯 Browser back button functionality" << std::endl;
        std::cout << "🎯 Recursion simulation" << std::endl;
        std::cout << "🎯 Balanced parentheses checking" << std::endl;
        std::cout << "🎯 Backtracking algorithms" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
