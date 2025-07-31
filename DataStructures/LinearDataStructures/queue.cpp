// Queue Implementation - Complete program with all operations
/*
Key Features of Queue (FIFO - First In First Out):
Core Operations:
✅ Enqueue: Add element to rear in O(1)
✅ Dequeue: Remove element from front in O(1)
✅ Front: Access front element in O(1)
✅ Rear: Access rear element in O(1)
Queue-Specific Features:
📚 FIFO Principle: First element added is first to be removed
🎯 Two-Point Access: Front for removal, rear for insertion
⚡ Constant Time Operations: All basic operations are O(1)
💾 Efficient Memory Usage: Circular array implementation
Advanced Features:
🔍 Search: Find element position from front
📊 Display: Show queue contents (front to rear)
🗑️ Clear: Remove all elements
📏 Size Tracking: Current number of elements
Smart Memory Management:
🧠 Multiple implementations: Array, Linked List, Circular
🛡️ Exception-safe operations
🚫 RAII principles throughout
📈 Automatic capacity management for dynamic queues
Educational Demonstrations:
📊 Performance Analysis: Time/space complexity breakdown
🧪 Error Handling: Comprehensive edge case testing
📝 Use Cases: Real-world applications explained
🔄 Multiple Implementations: Array, linked-list, and circular
*/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <memory>

// Circular Array-based Queue Implementation
template<typename T>
class CircularArrayQueue {
private:
    std::vector<T> data_;
    size_t front_;
    size_t rear_;
    size_t size_;
    size_t capacity_;
    
public:
    // Constructor with capacity
    explicit CircularArrayQueue(size_t capacity) 
        : data_(capacity), front_(0), rear_(0), size_(0), capacity_(capacity) {}
    
    // Default constructor
    CircularArrayQueue() : CircularArrayQueue(10) {}
    
    // Enqueue element to rear
    void enqueue(const T& value) {
        if (is_full()) {
            std::cout << "Queue is full - cannot enqueue " << value << std::endl;
            return;
        }
        
        data_[rear_] = value;
        rear_ = (rear_ + 1) % capacity_;
        size_++;
        std::cout << "Enqueued " << value << " to queue" << std::endl;
    }
    
    // Dequeue element from front
    void dequeue() {
        if (empty()) {
            std::cout << "Queue is empty - cannot dequeue" << std::endl;
            return;
        }
        
        std::cout << "Dequeued " << data_[front_] << " from queue" << std::endl;
        front_ = (front_ + 1) % capacity_;
        size_--;
    }
    
    // Get front element without removing
    T front() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return data_[front_];
    }
    
    // Get rear element without removing
    T rear() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        size_t rear_index = (rear_ - 1 + capacity_) % capacity_;
        return data_[rear_index];
    }
    
    // Check if queue is empty
    bool empty() const {
        return size_ == 0;
    }
    
    // Check if queue is full
    bool is_full() const {
        return size_ == capacity_;
    }
    
    // Get size of queue
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
        std::cout << "Queue cleared" << std::endl;
    }
    
    // Search for element (returns position from front, -1 if not found)
    int search(const T& value) const {
        if (empty()) return -1;
        
        for (size_t i = 0; i < size_; ++i) {
            size_t index = (front_ + i) % capacity_;
            if (data_[index] == value) {
                return static_cast<int>(i);
            }
        }
        return -1; // Not found
    }
    
    // Display queue contents (front to rear)
    void display() const {
        if (empty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Queue (front to rear): ";
        for (size_t i = 0; i < size_; ++i) {
            size_t index = (front_ + i) % capacity_;
            std::cout << data_[index];
            if (i < size_ - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
    
    // Display with positions
    void display_with_positions() const {
        if (empty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Queue with positions from front:" << std::endl;
        for (size_t i = 0; i < size_; ++i) {
            size_t index = (front_ + i) % capacity_;
            std::cout << "Position " << i << ": " << data_[index] << std::endl;
        }
    }
    
    // Get element at position from front (0 = front element)
    T at(size_t position) const {
        if (position >= size_) {
            throw std::out_of_range("Position out of bounds");
        }
        size_t index = (front_ + position) % capacity_;
        return data_[index];
    }
};

// Dynamic Array-based Queue Implementation
template<typename T>
class DynamicQueue {
private:
    std::vector<T> data_;
    size_t front_;
    
public:
    // Constructor
    DynamicQueue() : front_(0) {}
    
    // Enqueue element to rear
    void enqueue(const T& value) {
        data_.push_back(value);
        std::cout << "Enqueued " << value << " to queue" << std::endl;
    }
    
    // Dequeue element from front
    void dequeue() {
        if (empty()) {
            std::cout << "Queue is empty - cannot dequeue" << std::endl;
            return;
        }
        
        std::cout << "Dequeued " << data_[front_] << " from queue" << std::endl;
        front_++;
        
        // Optimize: Reset when queue becomes empty or when front becomes too large
        if (empty() || front_ > data_.size() / 2) {
            data_.erase(data_.begin(), data_.begin() + front_);
            front_ = 0;
        }
    }
    
    // Get front element without removing
    T front() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return data_[front_];
    }
    
    // Get rear element without removing
    T rear() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return data_.back();
    }
    
    // Check if queue is empty
    bool empty() const {
        return front_ >= data_.size();
    }
    
    // Get size of queue
    size_t size() const {
        return empty() ? 0 : data_.size() - front_;
    }
    
    // Clear all elements
    void clear() {
        data_.clear();
        front_ = 0;
        std::cout << "Queue cleared" << std::endl;
    }
    
    // Search for element (returns position from front, -1 if not found)
    int search(const T& value) const {
        for (size_t i = front_; i < data_.size(); ++i) {
            if (data_[i] == value) {
                return static_cast<int>(i - front_);
            }
        }
        return -1; // Not found
    }
    
    // Display queue contents (front to rear)
    void display() const {
        if (empty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Queue (front to rear): ";
        for (size_t i = front_; i < data_.size(); ++i) {
            std::cout << data_[i];
            if (i < data_.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
    
    // Display with positions
    void display_with_positions() const {
        if (empty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Queue with positions from front:" << std::endl;
        for (size_t i = front_; i < data_.size(); ++i) {
            std::cout << "Position " << (i - front_) << ": " << data_[i] << std::endl;
        }
    }
    
    // Get element at position from front (0 = front element)
    T at(size_t position) const {
        if (position >= size()) {
            throw std::out_of_range("Position out of bounds");
        }
        return data_[front_ + position];
    }
};

// Linked List-based Queue Implementation
template<typename T>
class LinkedQueue {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };
    
    std::unique_ptr<Node> front_;
    Node* rear_; // Raw pointer for easy rear access
    size_t size_;
    
public:
    // Constructor
    LinkedQueue() : front_(nullptr), rear_(nullptr), size_(0) {}
    
    // Enqueue element to rear
    void enqueue(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        
        if (empty()) {
            front_ = std::move(newNode);
            rear_ = front_.get();
        } else {
            rear_->next = std::move(newNode);
            rear_ = rear_->next.get();
        }
        
        size_++;
        std::cout << "Enqueued " << value << " to queue" << std::endl;
    }
    
    // Dequeue element from front
    void dequeue() {
        if (empty()) {
            std::cout << "Queue is empty - cannot dequeue" << std::endl;
            return;
        }
        
        std::cout << "Dequeued " << front_->data << " from queue" << std::endl;
        
        if (size_ == 1) {
            front_.reset();
            rear_ = nullptr;
        } else {
            front_ = std::move(front_->next);
        }
        
        size_--;
    }
    
    // Get front element without removing
    T front() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front_->data;
    }
    
    // Get rear element without removing
    T rear() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return rear_->data;
    }
    
    // Check if queue is empty
    bool empty() const {
        return front_ == nullptr;
    }
    
    // Get size of queue
    size_t size() const {
        return size_;
    }
    
    // Clear all elements
    void clear() {
        while (!empty()) {
            dequeue();
        }
        std::cout << "Queue cleared" << std::endl;
    }
    
    // Search for element (returns position from front, -1 if not found)
    int search(const T& value) const {
        Node* current = front_.get();
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
    
    // Display queue contents (front to rear)
    void display() const {
        if (empty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Queue (front to rear): ";
        Node* current = front_.get();
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " -> ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }
    
    // Display with positions
    void display_with_positions() const {
        if (empty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Queue with positions from front:" << std::endl;
        Node* current = front_.get();
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

void demonstrateCircularQueue() {
    printSeparator("CIRCULAR ARRAY QUEUE OPERATIONS");
    
    CircularArrayQueue<int> queue(5);
    
    std::cout << "\n--- Basic Queue Operations ---" << std::endl;
    std::cout << "Is empty: " << (queue.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Is full: " << (queue.is_full() ? "Yes" : "No") << std::endl;
    std::cout << "Size: " << queue.size() << std::endl;
    std::cout << "Capacity: " << queue.capacity() << std::endl;
    
    // Enqueue elements
    std::cout << "\n--- Enqueue Operations ---" << std::endl;
    for (int i = 10; i <= 40; i += 10) {
        queue.enqueue(i);
    }
    
    queue.display();
    queue.display_with_positions();
    std::cout << "Size: " << queue.size() << std::endl;
    std::cout << "Is full: " << (queue.is_full() ? "Yes" : "No") << std::endl;
    
    // Access front and rear elements
    std::cout << "\n--- Access Operations ---" << std::endl;
    try {
        std::cout << "Front element: " << queue.front() << std::endl;
        std::cout << "Rear element: " << queue.rear() << std::endl;
        std::cout << "Element at position 2: " << queue.at(2) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Search operations
    std::cout << "\n--- Search Operations ---" << std::endl;
    std::cout << "Search for 30: Position " << queue.search(30) << std::endl;
    std::cout << "Search for 100: Position " << queue.search(100) << std::endl;
    
    // Dequeue operations
    std::cout << "\n--- Dequeue Operations ---" << std::endl;
    queue.dequeue();
    queue.dequeue();
    queue.display();
    
    // Test circular behavior - add more elements
    std::cout << "\n--- Circular Behavior Test ---" << std::endl;
    queue.enqueue(50);
    queue.enqueue(60);
    queue.enqueue(70); // Should fill the queue
    queue.display();
    
    queue.enqueue(80); // Should fail - queue full
}

void demonstrateDynamicQueue() {
    printSeparator("DYNAMIC ARRAY QUEUE OPERATIONS");
    
    DynamicQueue<char> queue;
    
    std::cout << "\n--- Basic Queue Operations ---" << std::endl;
    std::cout << "Is empty: " << (queue.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Size: " << queue.size() << std::endl;
    
    // Enqueue elements
    std::cout << "\n--- Enqueue Operations ---" << std::endl;
    for (char c = 'A'; c <= 'E'; ++c) {
        queue.enqueue(c);
    }
    
    queue.display();
    queue.display_with_positions();
    std::cout << "Size: " << queue.size() << std::endl;
    
    // Access front and rear elements
    std::cout << "\n--- Access Operations ---" << std::endl;
    try {
        std::cout << "Front element: " << queue.front() << std::endl;
        std::cout << "Rear element: " << queue.rear() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Search operations
    std::cout << "\n--- Search Operations ---" << std::endl;
    std::cout << "Search for 'C': Position " << queue.search('C') << std::endl;
    std::cout << "Search for 'Z': Position " << queue.search('Z') << std::endl;
    
    // Dequeue operations
    std::cout << "\n--- Dequeue Operations ---" << std::endl;
    queue.dequeue();
    queue.dequeue();
    queue.display();
    
    // Add more elements to test dynamic growth
    std::cout << "\n--- Dynamic Growth Test ---" << std::endl;
    for (char c = 'F'; c <= 'J'; ++c) {
        queue.enqueue(c);
    }
    queue.display();
}

void demonstrateLinkedQueue() {
    printSeparator("LINKED LIST QUEUE OPERATIONS");
    
    LinkedQueue<std::string> queue;
    
    std::cout << "\n--- Basic Queue Operations ---" << std::endl;
    std::cout << "Is empty: " << (queue.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Size: " << queue.size() << std::endl;
    
    // Enqueue elements
    std::cout << "\n--- Enqueue Operations ---" << std::endl;
    std::vector<std::string> words = {"First", "Second", "Third", "Fourth"};
    for (const auto& word : words) {
        queue.enqueue(word);
    }
    
    queue.display();
    queue.display_with_positions();
    std::cout << "Size: " << queue.size() << std::endl;
    
    // Access front and rear elements
    std::cout << "\n--- Access Operations ---" << std::endl;
    try {
        std::cout << "Front element: " << queue.front() << std::endl;
        std::cout << "Rear element: " << queue.rear() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Search operations
    std::cout << "\n--- Search Operations ---" << std::endl;
    std::cout << "Search for 'Third': Position " << queue.search("Third") << std::endl;
    std::cout << "Search for 'NotFound': Position " << queue.search("NotFound") << std::endl;
    
    // Dequeue all elements
    std::cout << "\n--- Complete Dequeue Test ---" << std::endl;
    while (!queue.empty()) {
        std::cout << "Front before dequeue: " << queue.front() << std::endl;
        queue.dequeue();
        std::cout << "Size after dequeue: " << queue.size() << std::endl;
    }
    
    // Try operations on empty queue
    std::cout << "\n--- Operations on Empty Queue ---" << std::endl;
    queue.dequeue(); // Should handle gracefully
    try {
        std::cout << "Front of empty queue: " << queue.front() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void demonstrateQueueApplications() {
    printSeparator("QUEUE APPLICATIONS");
    
    // 1. Job Scheduling Simulation
    std::cout << "\n--- Job Scheduling Simulation ---" << std::endl;
    struct Job {
        int id;
        std::string name;
        
        Job(int i, const std::string& n) : id(i), name(n) {}
    };
    
    // Custom operator<< for Job
    auto printJob = [](const Job& job) {
        return "Job" + std::to_string(job.id) + "(" + job.name + ")";
    };
    
    LinkedQueue<Job> jobQueue;
    
    // Add jobs to queue
    std::vector<Job> jobs = {
        {1, "Print Document"},
        {2, "Send Email"},
        {3, "Backup Data"},
        {4, "Update System"}
    };
    
    std::cout << "Adding jobs to queue:" << std::endl;
    for (const auto& job : jobs) {
        jobQueue.enqueue(job);
        std::cout << "Queued: " << printJob(job) << std::endl;
    }
    
    std::cout << "\nProcessing jobs (FIFO order):" << std::endl;
    while (!jobQueue.empty()) {
        Job currentJob = jobQueue.front();
        std::cout << "Processing: " << printJob(currentJob) << std::endl;
        jobQueue.dequeue();
    }
    
    // 2. Level Order Tree Traversal Simulation
    std::cout << "\n--- Binary Tree Level Order Traversal ---" << std::endl;
    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
        
        TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
    };
    
    // Create a simple binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    // Level order traversal using queue
    std::cout << "Tree structure (level order): ";
    LinkedQueue<TreeNode*> nodeQueue;
    nodeQueue.enqueue(root);
    
    while (!nodeQueue.empty()) {
        TreeNode* current = nodeQueue.front();
        nodeQueue.dequeue();
        
        std::cout << current->data << " ";
        
        if (current->left) nodeQueue.enqueue(current->left);
        if (current->right) nodeQueue.enqueue(current->right);
    }
    std::cout << std::endl;
    
    // Clean up tree memory (simplified)
    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;
    
    // 3. Buffer Management Simulation
    std::cout << "\n--- Buffer Management (Producer-Consumer) ---" << std::endl;
    CircularArrayQueue<int> buffer(5);
    
    // Producer adds data
    std::cout << "Producer adding data to buffer:" << std::endl;
    for (int i = 1; i <= 7; ++i) {
        if (!buffer.is_full()) {
            buffer.enqueue(i * 100);
        } else {
            std::cout << "Buffer full - cannot add " << (i * 100) << std::endl;
        }
    }
    
    buffer.display();
    
    // Consumer processes data
    std::cout << "\nConsumer processing data from buffer:" << std::endl;
    while (!buffer.empty()) {
        std::cout << "Processing: " << buffer.front() << std::endl;
        buffer.dequeue();
    }
}

void demonstrateErrorHandling() {
    printSeparator("ERROR HANDLING");
    
    CircularArrayQueue<int> queue(3);
    
    std::cout << "\n--- Error Handling Tests ---" << std::endl;
    
    // Test operations on empty queue
    try {
        queue.front();
    } catch (const std::exception& e) {
        std::cout << "Empty queue front() exception: " << e.what() << std::endl;
    }
    
    try {
        queue.rear();
    } catch (const std::exception& e) {
        std::cout << "Empty queue rear() exception: " << e.what() << std::endl;
    }
    
    try {
        queue.at(0);
    } catch (const std::exception& e) {
        std::cout << "Empty queue at(0) exception: " << e.what() << std::endl;
    }
    
    // Fill queue and test overflow
    std::cout << "\n--- Overflow Handling ---" << std::endl;
    for (int i = 1; i <= 4; ++i) {
        queue.enqueue(i * 10);
    }
    
    // Test out of bounds access
    try {
        std::cout << "Valid at(1): " << queue.at(1) << std::endl;
        std::cout << "Invalid at(5): " << queue.at(5) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Out of bounds at(5) exception: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "         QUEUE DEMONSTRATION                  " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateCircularQueue();
        demonstrateDynamicQueue();
        demonstrateLinkedQueue();
        demonstrateQueueApplications();
        demonstrateErrorHandling();
        
        printSeparator("PERFORMANCE CHARACTERISTICS");
        std::cout << "\nTime Complexity Summary:" << std::endl;
        std::cout << "- Enqueue:   O(1) - Constant time insertion" << std::endl;
        std::cout << "- Dequeue:   O(1) - Constant time removal" << std::endl;
        std::cout << "- Front:     O(1) - Constant time access" << std::endl;
        std::cout << "- Rear:      O(1) - Constant time access" << std::endl;
        std::cout << "- Search:    O(n) - Linear search required" << std::endl;
        std::cout << "- Space:     O(n) - Linear space for n elements" << std::endl;
        
        std::cout << "\nImplementation Comparison:" << std::endl;
        std::cout << "Circular Array Queue:" << std::endl;
        std::cout << "  ✅ Fixed memory usage" << std::endl;
        std::cout << "  ✅ Cache-friendly access" << std::endl;
        std::cout << "  ❌ Fixed capacity (can be full)" << std::endl;
        
        std::cout << "Dynamic Array Queue:" << std::endl;
        std::cout << "  ✅ Unlimited growth" << std::endl;
        std::cout << "  ✅ No capacity restrictions" << std::endl;
        std::cout << "  ❌ May waste memory over time" << std::endl;
        
        std::cout << "Linked List Queue:" << std::endl;
        std::cout << "  ✅ True dynamic sizing" << std::endl;
        std::cout << "  ✅ No memory waste" << std::endl;
        std::cout << "  ❌ Extra memory for pointers" << std::endl;
        std::cout << "  ❌ Not cache-friendly" << std::endl;
        
        std::cout << "\nCommon Use Cases:" << std::endl;
        std::cout << "🎯 Task scheduling in operating systems" << std::endl;
        std::cout << "🎯 Buffer management in I/O operations" << std::endl;
        std::cout << "🎯 Breadth-First Search (BFS) algorithms" << std::endl;
        std::cout << "🎯 Level-order tree traversal" << std::endl;
        std::cout << "🎯 Producer-consumer problems" << std::endl;
        std::cout << "🎯 Print job management" << std::endl;
        std::cout << "🎯 Handling requests in web servers" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
