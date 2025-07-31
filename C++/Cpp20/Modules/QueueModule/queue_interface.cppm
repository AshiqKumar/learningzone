// C++20 Modules - Queue Data Structures Module Interface
// This module provides various queue implementations using modern C++20 modules

export module queue_module;

// Import standard library modules
import <iostream>;
import <vector>;
import <memory>;
import <stdexcept>;
import <string>;

// ==================== EXPORTED CIRCULAR ARRAY QUEUE ====================

export template<typename T>
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
        std::cout << "Enqueued " << value << " to circular queue" << std::endl;
    }
    
    // Dequeue element from front
    void dequeue() {
        if (empty()) {
            std::cout << "Queue is empty - cannot dequeue" << std::endl;
            return;
        }
        
        std::cout << "Dequeued " << data_[front_] << " from circular queue" << std::endl;
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
        std::cout << "Circular queue cleared" << std::endl;
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
        return -1;
    }
    
    // Display queue contents (front to rear)
    void display() const {
        if (empty()) {
            std::cout << "Circular queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Circular queue contents (front to rear): ";
        for (size_t i = 0; i < size_; ++i) {
            size_t index = (front_ + i) % capacity_;
            std::cout << data_[index];
            if (i < size_ - 1) std::cout << " <- ";
        }
        std::cout << std::endl;
    }
};

// ==================== EXPORTED DYNAMIC QUEUE ====================

export template<typename T>
class DynamicQueue {
private:
    std::vector<T> data_;
    size_t front_;
    
    void resize_if_needed() {
        if (front_ >= data_.size() / 2) {
            // Compact the queue by moving elements to the front
            size_t queue_size = data_.size() - front_;
            for (size_t i = 0; i < queue_size; ++i) {
                data_[i] = data_[front_ + i];
            }
            data_.resize(queue_size);
            front_ = 0;
        }
    }
    
public:
    DynamicQueue() : front_(0) {
        data_.reserve(10);  // Initial capacity
    }
    
    // Enqueue element to rear
    void enqueue(const T& value) {
        data_.push_back(value);
        std::cout << "Enqueued " << value << " to dynamic queue" << std::endl;
    }
    
    // Dequeue element from front
    void dequeue() {
        if (empty()) {
            std::cout << "Queue is empty - cannot dequeue" << std::endl;
            return;
        }
        
        std::cout << "Dequeued " << data_[front_] << " from dynamic queue" << std::endl;
        front_++;
        resize_if_needed();
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
        if (empty()) return 0;
        return data_.size() - front_;
    }
    
    // Clear all elements
    void clear() {
        data_.clear();
        front_ = 0;
        std::cout << "Dynamic queue cleared" << std::endl;
    }
    
    // Search for element (returns position from front, -1 if not found)
    int search(const T& value) const {
        if (empty()) return -1;
        
        for (size_t i = front_; i < data_.size(); ++i) {
            if (data_[i] == value) {
                return static_cast<int>(i - front_);
            }
        }
        return -1;
    }
    
    // Display queue contents
    void display() const {
        if (empty()) {
            std::cout << "Dynamic queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Dynamic queue contents (front to rear): ";
        for (size_t i = front_; i < data_.size(); ++i) {
            std::cout << data_[i];
            if (i < data_.size() - 1) std::cout << " <- ";
        }
        std::cout << std::endl;
    }
};

// ==================== EXPORTED LINKED QUEUE ====================

export template<typename T>
class LinkedQueue {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };
    
    std::unique_ptr<Node> front_;
    Node* rear_;  // Raw pointer since it's managed by the chain
    size_t size_;
    
public:
    LinkedQueue() : front_(nullptr), rear_(nullptr), size_(0) {}
    
    // Enqueue element to rear
    void enqueue(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        
        if (empty()) {
            rear_ = newNode.get();
            front_ = std::move(newNode);
        } else {
            rear_->next = std::move(newNode);
            rear_ = rear_->next.get();
        }
        
        size_++;
        std::cout << "Enqueued " << value << " to linked queue" << std::endl;
    }
    
    // Dequeue element from front
    void dequeue() {
        if (empty()) {
            std::cout << "Queue is empty - cannot dequeue" << std::endl;
            return;
        }
        
        std::cout << "Dequeued " << front_->data << " from linked queue" << std::endl;
        
        front_ = std::move(front_->next);
        size_--;
        
        if (empty()) {
            rear_ = nullptr;
        }
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
            front_ = std::move(front_->next);
        }
        rear_ = nullptr;
        size_ = 0;
        std::cout << "Linked queue cleared" << std::endl;
    }
    
    // Search for element (returns position from front, -1 if not found)
    int search(const T& value) const {
        if (empty()) return -1;
        
        Node* current = front_.get();
        int position = 0;
        
        while (current) {
            if (current->data == value) {
                return position;
            }
            current = current->next.get();
            position++;
        }
        
        return -1;
    }
    
    // Display queue contents
    void display() const {
        if (empty()) {
            std::cout << "Linked queue is empty" << std::endl;
            return;
        }
        
        std::cout << "Linked queue contents (front to rear): ";
        Node* current = front_.get();
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " <- ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }
};

// ==================== EXPORTED UTILITY FUNCTIONS ====================

// Export utility function for queue comparisons
export template<typename QueueType>
void demonstrate_queue(QueueType& queue, const std::string& queue_name) {
    std::cout << "\n=== " << queue_name << " Demonstration ===" << std::endl;
    
    // Test basic operations
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.display();
    
    std::cout << "Front element: " << queue.front() << std::endl;
    std::cout << "Rear element: " << queue.rear() << std::endl;
    std::cout << "Queue size: " << queue.size() << std::endl;
    
    // Search for elements
    std::cout << "Search for 20: " << (queue.search(20) != -1 ? "Found" : "Not found") << std::endl;
    std::cout << "Search for 50: " << (queue.search(50) != -1 ? "Found" : "Not found") << std::endl;
    
    // Dequeue operations
    queue.dequeue();
    queue.display();
    queue.dequeue();
    queue.display();
    
    std::cout << "Queue size after dequeues: " << queue.size() << std::endl;
}

// Export performance comparison function
export void compare_queue_performance();

// Export queue type aliases for convenience
export template<typename T> using CircularQueue = CircularArrayQueue<T>;
export template<typename T> using DynamicArrayQueue = DynamicQueue<T>;
export template<typename T> using ListQueue = LinkedQueue<T>;

/*
KEY MODULE CONCEPTS DEMONSTRATED:

1. TEMPLATE CLASSES IN MODULES:
   - Complete template implementation must be in the interface module
   - Templates are instantiated at the point of use
   - All template code must be visible to importers

2. ENCAPSULATION WITH MODULES:
   - Private member functions remain truly private
   - Internal implementation details are hidden
   - Better than traditional headers where everything is visible

3. MULTIPLE EXPORTS:
   - Can export multiple classes from a single module
   - Template aliases work seamlessly
   - Utility functions can be exported alongside classes

4. SMART POINTER COMPATIBILITY:
   - std::unique_ptr works perfectly with modules
   - RAII principles maintained
   - Memory management is automatic and safe

5. MODULE INTERFACE DESIGN:
   - Clean public API through explicit exports
   - Implementation details hidden from importers
   - Template instantiation happens at import site

This module demonstrates how C++20 modules provide better organization,
faster compilation, and stronger encapsulation than traditional headers!
*/
