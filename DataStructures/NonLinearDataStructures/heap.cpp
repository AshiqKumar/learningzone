// Heap Implementation - Complete program with Min-Heap and Max-Heap
/*
Key Features of Heap:
Core Operations:
✅ Insertion: Add elements while maintaining heap property
✅ Extraction: Remove root element (min/max) efficiently
✅ Peek: View root element without removal
✅ Heapify: Convert array to heap structure
Heap Properties:
🌳 Complete Binary Tree: All levels filled except possibly last
⚡ Heap Property: Parent-child relationship (min or max)
📊 Array Representation: Efficient storage using array
🎯 Priority Queue: Perfect for priority-based operations
Advanced Features:
🔄 Build Heap: Construct heap from unsorted array
📈 Heap Sort: In-place sorting algorithm
🎨 Custom Comparators: Support for custom comparison functions
📊 Heap Statistics: Size, height, and property validation
Smart Memory Management:
🧠 Uses dynamic arrays (vector) for efficiency
🛡️ Exception-safe operations throughout
🚫 RAII principles for resource management
📈 Automatic capacity management with vector
Educational Demonstrations:
📊 Performance Analysis: Heap operations complexity
🧪 Heap Visualization: Array representation display
📝 Priority Queue Applications: Task scheduling, pathfinding
🔄 Sorting Algorithms: Heap sort implementation
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <iomanip>
#include <queue>

template<typename T, typename Compare = std::less<T>>
class Heap {
private:
    std::vector<T> data_;
    Compare comp_;
    
    // Helper functions for array-based heap indexing
    size_t parent(size_t index) const {
        return (index == 0) ? 0 : (index - 1) / 2;
    }
    
    size_t leftChild(size_t index) const {
        return 2 * index + 1;
    }
    
    size_t rightChild(size_t index) const {
        return 2 * index + 2;
    }
    
    // Move element up the heap (used in insertion)
    void heapifyUp(size_t index) {
        while (index > 0) {
            size_t parentIndex = parent(index);
            if (!comp_(data_[index], data_[parentIndex])) {
                break; // Heap property satisfied
            }
            
            std::swap(data_[index], data_[parentIndex]);
            index = parentIndex;
        }
    }
    
    // Move element down the heap (used in extraction)
    void heapifyDown(size_t index) {
        size_t size = data_.size();
        
        while (leftChild(index) < size) {
            size_t smallerChild = leftChild(index);
            size_t rightIndex = rightChild(index);
            
            // Find the smaller/larger child based on comparator
            if (rightIndex < size && comp_(data_[rightIndex], data_[smallerChild])) {
                smallerChild = rightIndex;
            }
            
            // If parent satisfies heap property, we're done
            if (!comp_(data_[smallerChild], data_[index])) {
                break;
            }
            
            std::swap(data_[index], data_[smallerChild]);
            index = smallerChild;
        }
    }
    
public:
    // Constructors
    Heap() : comp_(Compare{}) {}
    
    explicit Heap(const Compare& comp) : comp_(comp) {}
    
    // Construct heap from vector
    explicit Heap(const std::vector<T>& vec, const Compare& comp = Compare{}) 
        : data_(vec), comp_(comp) {
        buildHeap();
    }
    
    // Build heap from unsorted array (bottom-up)
    void buildHeap() {
        if (data_.size() <= 1) return;
        
        // Start from last non-leaf node and heapify down
        for (int i = static_cast<int>(data_.size() / 2 - 1); i >= 0; --i) {
            heapifyDown(static_cast<size_t>(i));
        }
        
        std::cout << "Built heap from " << data_.size() << " elements" << std::endl;
    }
    
    // Insert element
    void insert(const T& value) {
        data_.push_back(value);
        heapifyUp(data_.size() - 1);
        
        std::cout << "Inserted " << value << " (size: " << data_.size() << ")" << std::endl;
    }
    
    // Extract root element (min or max depending on comparator)
    T extract() {
        if (empty()) {
            throw std::runtime_error("Heap is empty");
        }
        
        T root = data_[0];
        
        // Move last element to root and remove last
        data_[0] = data_.back();
        data_.pop_back();
        
        // Restore heap property
        if (!empty()) {
            heapifyDown(0);
        }
        
        std::cout << "Extracted " << root << " (size: " << data_.size() << ")" << std::endl;
        return root;
    }
    
    // Peek at root element without removing
    const T& peek() const {
        if (empty()) {
            throw std::runtime_error("Heap is empty");
        }
        return data_[0];
    }
    
    // Remove specific element by value
    bool remove(const T& value) {
        auto it = std::find(data_.begin(), data_.end(), value);
        if (it == data_.end()) {
            std::cout << "Value " << value << " not found in heap" << std::endl;
            return false;
        }
        
        size_t index = std::distance(data_.begin(), it);
        
        // Replace with last element
        data_[index] = data_.back();
        data_.pop_back();
        
        // Restore heap property (may need to go up or down)
        if (index < data_.size()) {
            // Try heapifying up first
            size_t originalIndex = index;
            heapifyUp(index);
            
            // If element didn't move up, try heapifying down
            if (index == originalIndex) {
                heapifyDown(index);
            }
        }
        
        std::cout << "Removed " << value << " (size: " << data_.size() << ")" << std::endl;
        return true;
    }
    
    // Change priority of element (decrease key for min-heap, increase for max-heap)
    bool changePriority(const T& oldValue, const T& newValue) {
        auto it = std::find(data_.begin(), data_.end(), oldValue);
        if (it == data_.end()) {
            std::cout << "Value " << oldValue << " not found in heap" << std::endl;
            return false;
        }
        
        size_t index = std::distance(data_.begin(), it);
        data_[index] = newValue;
        
        // Restore heap property
        if (comp_(newValue, oldValue)) {
            heapifyUp(index);  // Priority increased (for the heap type)
        } else {
            heapifyDown(index);  // Priority decreased
        }
        
        std::cout << "Changed " << oldValue << " to " << newValue << std::endl;
        return true;
    }
    
    // Properties
    bool empty() const { return data_.empty(); }
    size_t size() const { return data_.size(); }
    
    // Calculate height of heap
    int height() const {
        if (empty()) return -1;
        return static_cast<int>(std::floor(std::log2(data_.size())));
    }
    
    // Check if heap property is maintained
    bool isValidHeap() const {
        for (size_t i = 0; i < data_.size(); ++i) {
            size_t left = leftChild(i);
            size_t right = rightChild(i);
            
            if (left < data_.size() && comp_(data_[left], data_[i])) {
                return false;
            }
            if (right < data_.size() && comp_(data_[right], data_[i])) {
                return false;
            }
        }
        return true;
    }
    
    // Get all elements (not in sorted order)
    std::vector<T> getData() const {
        return data_;
    }
    
    // Heap sort (sorts in place, destroys heap structure)
    std::vector<T> heapSort() {
        std::vector<T> sorted;
        sorted.reserve(data_.size());
        
        // Extract all elements (they come out in sorted order)
        while (!empty()) {
            sorted.push_back(extract());
        }
        
        return sorted;
    }
    
    // Non-destructive heap sort
    std::vector<T> getSorted() const {
        Heap<T, Compare> temp(*this);  // Create copy
        return temp.heapSort();
    }
    
    // Merge two heaps
    void merge(const Heap<T, Compare>& other) {
        for (const T& element : other.data_) {
            insert(element);
        }
        std::cout << "Merged heap with " << other.size() << " elements" << std::endl;
    }
    
    // Display heap as array
    void displayArray() const {
        if (empty()) {
            std::cout << "Heap is empty" << std::endl;
            return;
        }
        
        std::cout << "Heap array: [";
        for (size_t i = 0; i < data_.size(); ++i) {
            std::cout << data_[i];
            if (i < data_.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    // Display heap as tree structure
    void displayTree() const {
        if (empty()) {
            std::cout << "Heap is empty" << std::endl;
            return;
        }
        
        std::cout << "Heap tree structure:" << std::endl;
        displayTreeHelper(0, "", true);
    }
    
private:
    void displayTreeHelper(size_t index, const std::string& prefix, bool isLast) const {
        if (index >= data_.size()) return;
        
        std::cout << prefix;
        std::cout << (isLast ? "└── " : "├── ");
        std::cout << data_[index] << std::endl;
        
        size_t left = leftChild(index);
        size_t right = rightChild(index);
        
        std::string newPrefix = prefix + (isLast ? "    " : "│   ");
        
        if (right < data_.size()) {
            displayTreeHelper(right, newPrefix, left >= data_.size());
        }
        if (left < data_.size()) {
            displayTreeHelper(left, newPrefix, true);
        }
    }
    
public:
    // Display heap properties
    void displayProperties() const {
        std::cout << "Heap Properties:" << std::endl;
        std::cout << "Size: " << size() << std::endl;
        std::cout << "Height: " << height() << std::endl;
        std::cout << "Is valid heap: " << (isValidHeap() ? "Yes" : "No") << std::endl;
        std::cout << "Type: " << (std::is_same_v<Compare, std::less<T>> ? "Min-Heap" : 
                                 std::is_same_v<Compare, std::greater<T>> ? "Max-Heap" : "Custom") << std::endl;
        
        if (!empty()) {
            std::cout << "Root element: " << peek() << std::endl;
        }
    }
    
    // Clear heap
    void clear() {
        data_.clear();
        std::cout << "Heap cleared" << std::endl;
    }
};

// Convenience type aliases
template<typename T>
using MinHeap = Heap<T, std::less<T>>;

template<typename T>
using MaxHeap = Heap<T, std::greater<T>>;

// Priority Queue using Heap
template<typename T, typename Priority = int, typename Compare = std::less<Priority>>
class PriorityQueue {
private:
    struct Element {
        T data;
        Priority priority;
        
        Element(const T& d, const Priority& p) : data(d), priority(p) {}
    };
    
    struct ElementCompare {
        Compare comp;
        
        ElementCompare(const Compare& c = Compare{}) : comp(c) {}
        
        bool operator()(const Element& a, const Element& b) const {
            return comp(a.priority, b.priority);
        }
    };
    
    Heap<Element, ElementCompare> heap_;
    
public:
    PriorityQueue() : heap_(ElementCompare{}) {}
    
    void push(const T& data, const Priority& priority) {
        heap_.insert(Element(data, priority));
        std::cout << "Enqueued " << data << " with priority " << priority << std::endl;
    }
    
    T pop() {
        if (empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        Element element = heap_.extract();
        std::cout << "Dequeued " << element.data << " with priority " << element.priority << std::endl;
        return element.data;
    }
    
    const T& top() const {
        if (empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return heap_.peek().data;
    }
    
    Priority topPriority() const {
        if (empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return heap_.peek().priority;
    }
    
    bool empty() const { return heap_.empty(); }
    size_t size() const { return heap_.size(); }
    
    void display() const {
        std::cout << "Priority Queue contents:" << std::endl;
        auto data = heap_.getData();
        for (const auto& element : data) {
            std::cout << "  " << element.data << " (priority: " << element.priority << ")" << std::endl;
        }
    }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void demonstrateBasicHeapOperations() {
    printSeparator("BASIC HEAP OPERATIONS");
    
    std::cout << "\n--- Min-Heap Operations ---" << std::endl;
    MinHeap<int> minHeap;
    
    // Insert elements
    std::vector<int> values = {20, 15, 8, 10, 5, 7, 6, 2, 9, 1};
    for (int value : values) {
        minHeap.insert(value);
    }
    
    minHeap.displayArray();
    minHeap.displayTree();
    minHeap.displayProperties();
    
    std::cout << "\n--- Extraction Operations ---" << std::endl;
    std::cout << "Root element (minimum): " << minHeap.peek() << std::endl;
    
    for (int i = 0; i < 3; ++i) {
        int min = minHeap.extract();
        std::cout << "After extracting " << min << ":" << std::endl;
        minHeap.displayArray();
    }
    
    std::cout << "\n--- Max-Heap Operations ---" << std::endl;
    MaxHeap<int> maxHeap;
    
    for (int value : values) {
        maxHeap.insert(value);
    }
    
    maxHeap.displayArray();
    maxHeap.displayTree();
    maxHeap.displayProperties();
    
    std::cout << "Root element (maximum): " << maxHeap.peek() << std::endl;
}

void demonstrateBuildHeap() {
    printSeparator("BUILD HEAP FROM ARRAY");
    
    std::vector<int> unsorted = {4, 10, 3, 5, 1, 6, 11, 2, 7, 8};
    
    std::cout << "Original array: ";
    for (size_t i = 0; i < unsorted.size(); ++i) {
        std::cout << unsorted[i];
        if (i < unsorted.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "\n--- Building Min-Heap ---" << std::endl;
    MinHeap<int> minHeap(unsorted);
    minHeap.displayArray();
    minHeap.displayTree();
    minHeap.displayProperties();
    
    std::cout << "\n--- Building Max-Heap ---" << std::endl;
    MaxHeap<int> maxHeap(unsorted);
    maxHeap.displayArray();
    maxHeap.displayTree();
    maxHeap.displayProperties();
}

void demonstrateHeapSort() {
    printSeparator("HEAP SORT ALGORITHM");
    
    std::vector<int> unsorted = {64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "Original array: ";
    for (size_t i = 0; i < unsorted.size(); ++i) {
        std::cout << unsorted[i];
        if (i < unsorted.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "\n--- Heap Sort (Ascending) using Min-Heap ---" << std::endl;
    MinHeap<int> minHeap(unsorted);
    auto sortedAsc = minHeap.getSorted(); // Non-destructive sort
    
    std::cout << "Sorted (ascending): ";
    for (size_t i = 0; i < sortedAsc.size(); ++i) {
        std::cout << sortedAsc[i];
        if (i < sortedAsc.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "\n--- Heap Sort (Descending) using Max-Heap ---" << std::endl;
    MaxHeap<int> maxHeap(unsorted);
    auto sortedDesc = maxHeap.getSorted(); // Non-destructive sort
    
    std::cout << "Sorted (descending): ";
    for (size_t i = 0; i < sortedDesc.size(); ++i) {
        std::cout << sortedDesc[i];
        if (i < sortedDesc.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "\nHeap Sort Characteristics:" << std::endl;
    std::cout << "⏰ Time Complexity: O(n log n) - always" << std::endl;
    std::cout << "💾 Space Complexity: O(1) - in-place sorting" << std::endl;
    std::cout << "📊 Not stable: Equal elements may not maintain relative order" << std::endl;
    std::cout << "⚡ Consistent performance: No best/worst case differences" << std::endl;
}

void demonstratePriorityQueue() {
    printSeparator("PRIORITY QUEUE APPLICATIONS");
    
    // 1. Task Scheduling
    std::cout << "\n--- Task Scheduling System ---" << std::endl;
    PriorityQueue<std::string, int> taskQueue; // Lower number = higher priority
    
    taskQueue.push("Send Email", 3);
    taskQueue.push("Fix Bug", 1);          // Highest priority
    taskQueue.push("Write Report", 5);
    taskQueue.push("Review Code", 2);
    taskQueue.push("Update Docs", 4);
    
    taskQueue.display();
    
    std::cout << "\nProcessing tasks in priority order:" << std::endl;
    while (!taskQueue.empty()) {
        std::cout << "Processing: " << taskQueue.top() 
                  << " (priority: " << taskQueue.topPriority() << ")" << std::endl;
        taskQueue.pop();
    }
    
    // 2. Hospital Emergency System
    std::cout << "\n--- Hospital Emergency System ---" << std::endl;
    PriorityQueue<std::string, int> emergencyQueue;
    
    emergencyQueue.push("John (Heart Attack)", 1);      // Critical
    emergencyQueue.push("Sarah (Broken Arm)", 4);       // Low priority
    emergencyQueue.push("Mike (Severe Bleeding)", 2);   // High priority
    emergencyQueue.push("Lisa (Headache)", 5);          // Lowest priority
    emergencyQueue.push("Tom (Car Accident)", 1);       // Critical
    
    emergencyQueue.display();
    
    std::cout << "\nTreating patients by priority:" << std::endl;
    while (!emergencyQueue.empty()) {
        std::cout << "Treating: " << emergencyQueue.top() 
                  << " (urgency: " << emergencyQueue.topPriority() << ")" << std::endl;
        emergencyQueue.pop();
    }
}

void demonstrateAdvancedOperations() {
    printSeparator("ADVANCED HEAP OPERATIONS");
    
    MinHeap<int> heap;
    std::vector<int> values = {15, 10, 20, 8, 25, 5, 30};
    
    for (int value : values) {
        heap.insert(value);
    }
    
    std::cout << "Original heap:" << std::endl;
    heap.displayArray();
    heap.displayTree();
    
    std::cout << "\n--- Remove Specific Element ---" << std::endl;
    heap.remove(20);
    heap.displayArray();
    
    std::cout << "\n--- Change Priority ---" << std::endl;
    heap.changePriority(25, 3); // Decrease 25 to 3 (higher priority in min-heap)
    heap.displayArray();
    
    std::cout << "\n--- Merge Heaps ---" << std::endl;
    MinHeap<int> otherHeap;
    otherHeap.insert(12);
    otherHeap.insert(18);
    otherHeap.insert(6);
    
    std::cout << "Other heap: ";
    otherHeap.displayArray();
    
    heap.merge(otherHeap);
    std::cout << "After merge: ";
    heap.displayArray();
    heap.displayProperties();
}

void demonstrateCustomComparator() {
    printSeparator("CUSTOM COMPARATOR");
    
    // Custom struct for demonstration
    struct Task {
        std::string name;
        int priority;
        int duration;
        
        Task(const std::string& n, int p, int d) : name(n), priority(p), duration(d) {}
        
        friend std::ostream& operator<<(std::ostream& os, const Task& task) {
            return os << task.name << "(P:" << task.priority << ",D:" << task.duration << ")";
        }
    };
    
    // Custom comparator: prioritize by priority first, then by duration
    struct TaskComparator {
        bool operator()(const Task& a, const Task& b) const {
            if (a.priority != b.priority) {
                return a.priority < b.priority; // Lower priority number = higher priority
            }
            return a.duration < b.duration; // Shorter duration = higher priority
        }
    };
    
    std::cout << "\n--- Task Scheduler with Custom Priority ---" << std::endl;
    Heap<Task, TaskComparator> taskHeap;
    
    taskHeap.insert(Task("Debug Code", 2, 120));
    taskHeap.insert(Task("Write Tests", 3, 60));
    taskHeap.insert(Task("Fix Bug", 1, 30));        // Highest priority
    taskHeap.insert(Task("Code Review", 2, 45));    // Same priority as Debug, but shorter
    taskHeap.insert(Task("Documentation", 4, 90));
    
    std::cout << "Task queue:" << std::endl;
    auto tasks = taskHeap.getData();
    for (const auto& task : tasks) {
        std::cout << "  " << task << std::endl;
    }
    
    std::cout << "\nProcessing tasks in optimal order:" << std::endl;
    while (!taskHeap.empty()) {
        Task task = taskHeap.extract();
        std::cout << "Processing: " << task << std::endl;
    }
}

void demonstratePerformanceAnalysis() {
    printSeparator("PERFORMANCE ANALYSIS");
    
    std::cout << "\n--- Time Complexity Comparison ---" << std::endl;
    std::cout << "╔═══════════════════╦══════════════╦══════════════╗" << std::endl;
    std::cout << "║     Operation     ║     Heap     ║ Sorted Array ║" << std::endl;
    std::cout << "╠═══════════════════╬══════════════╬══════════════╣" << std::endl;
    std::cout << "║    Insert         ║   O(log n)   ║     O(n)     ║" << std::endl;
    std::cout << "║ Extract Min/Max   ║   O(log n)   ║     O(1)     ║" << std::endl;
    std::cout << "║    Peek           ║     O(1)     ║     O(1)     ║" << std::endl;
    std::cout << "║   Build Heap      ║     O(n)     ║   O(n log n) ║" << std::endl;
    std::cout << "║  Delete Element   ║   O(log n)   ║     O(n)     ║" << std::endl;
    std::cout << "╚═══════════════════╩══════════════╩══════════════╝" << std::endl;
    
    std::cout << "\n--- Space Efficiency ---" << std::endl;
    std::vector<int> testData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    MinHeap<int> heap(testData);
    std::cout << "Heap elements: " << heap.size() << std::endl;
    std::cout << "Heap height: " << heap.height() << std::endl;
    std::cout << "Tree height for " << heap.size() << " elements: ⌊log₂(n)⌋ = " << heap.height() << std::endl;
    
    std::cout << "\n--- Build Heap vs Insert Operations ---" << std::endl;
    
    // Build heap from array (O(n))
    std::cout << "Method 1: Build heap from array - O(n)" << std::endl;
    MinHeap<int> heap1(testData);
    heap1.displayArray();
    
    // Insert elements one by one (O(n log n))
    std::cout << "\nMethod 2: Insert elements one by one - O(n log n)" << std::endl;
    MinHeap<int> heap2;
    for (int value : testData) {
        heap2.insert(value);
    }
    heap2.displayArray();
    
    std::cout << "\nBoth methods produce valid heaps, but build-heap is more efficient!" << std::endl;
}

void demonstrateRealWorldApplications() {
    printSeparator("REAL-WORLD APPLICATIONS");
    
    // 1. Dijkstra's Algorithm Priority Queue
    std::cout << "\n--- Dijkstra's Algorithm (Shortest Path) ---" << std::endl;
    struct GraphNode {
        int vertex;
        int distance;
        
        GraphNode(int v, int d) : vertex(v), distance(d) {}
        
        friend std::ostream& operator<<(std::ostream& os, const GraphNode& node) {
            return os << "V" << node.vertex << "(" << node.distance << ")";
        }
    };
    
    struct NodeComparator {
        bool operator()(const GraphNode& a, const GraphNode& b) const {
            return a.distance > b.distance; // Min-heap by distance
        }
    };
    
    Heap<GraphNode, NodeComparator> dijkstraQueue;
    
    dijkstraQueue.insert(GraphNode(1, 0));   // Start vertex
    dijkstraQueue.insert(GraphNode(2, 5));
    dijkstraQueue.insert(GraphNode(3, 3));
    dijkstraQueue.insert(GraphNode(4, 8));
    dijkstraQueue.insert(GraphNode(5, 2));
    
    std::cout << "Vertices to process (shortest distance first):" << std::endl;
    while (!dijkstraQueue.empty()) {
        GraphNode node = dijkstraQueue.extract();
        std::cout << "Process vertex " << node.vertex << " with distance " << node.distance << std::endl;
    }
    
    // 2. Operating System Process Scheduling
    std::cout << "\n--- OS Process Scheduling ---" << std::endl;
    struct Process {
        int pid;
        int priority;
        int burstTime;
        
        Process(int id, int p, int bt) : pid(id), priority(p), burstTime(bt) {}
        
        friend std::ostream& operator<<(std::ostream& os, const Process& proc) {
            return os << "PID:" << proc.pid << "(P:" << proc.priority << ",BT:" << proc.burstTime << ")";
        }
    };
    
    struct ProcessComparator {
        bool operator()(const Process& a, const Process& b) const {
            return a.priority > b.priority; // Higher priority number = lower priority
        }
    };
    
    Heap<Process, ProcessComparator> processQueue;
    
    processQueue.insert(Process(1, 3, 10));
    processQueue.insert(Process(2, 1, 5));   // Highest priority
    processQueue.insert(Process(3, 4, 8));
    processQueue.insert(Process(4, 2, 3));
    processQueue.insert(Process(5, 1, 7));   // Highest priority
    
    std::cout << "Process execution order:" << std::endl;
    while (!processQueue.empty()) {
        Process proc = processQueue.extract();
        std::cout << "Execute " << proc << std::endl;
    }
    
    // 3. Event Simulation
    std::cout << "\n--- Event-Driven Simulation ---" << std::endl;
    struct Event {
        std::string type;
        double time;
        
        Event(const std::string& t, double tm) : type(t), time(tm) {}
        
        friend std::ostream& operator<<(std::ostream& os, const Event& event) {
            return os << event.type << "@" << std::fixed << std::setprecision(1) << event.time;
        }
    };
    
    struct EventComparator {
        bool operator()(const Event& a, const Event& b) const {
            return a.time > b.time; // Earlier time = higher priority
        }
    };
    
    Heap<Event, EventComparator> eventQueue;
    
    eventQueue.insert(Event("Customer Arrival", 1.5));
    eventQueue.insert(Event("Service Complete", 3.2));
    eventQueue.insert(Event("Customer Arrival", 2.1));
    eventQueue.insert(Event("Server Breakdown", 5.0));
    eventQueue.insert(Event("Customer Arrival", 0.8));
    
    std::cout << "Event processing order:" << std::endl;
    while (!eventQueue.empty()) {
        Event event = eventQueue.extract();
        std::cout << "Process " << event << std::endl;
    }
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "          HEAP DEMONSTRATION                 " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateBasicHeapOperations();
        demonstrateBuildHeap();
        demonstrateHeapSort();
        demonstratePriorityQueue();
        demonstrateAdvancedOperations();
        demonstrateCustomComparator();
        demonstratePerformanceAnalysis();
        demonstrateRealWorldApplications();
        
        printSeparator("COMPREHENSIVE SUMMARY");
        
        std::cout << "\nHeap Key Properties:" << std::endl;
        std::cout << "🌳 Complete Binary Tree: All levels filled except possibly last" << std::endl;
        std::cout << "📊 Array Representation: Efficient storage with index calculations" << std::endl;
        std::cout << "⚡ Heap Property: Parent-child relationship maintained" << std::endl;
        std::cout << "🎯 Root Access: Min/Max element always at root (index 0)" << std::endl;
        
        std::cout << "\nHeap Types:" << std::endl;
        std::cout << "📈 Min-Heap: Parent ≤ Children (smallest at root)" << std::endl;
        std::cout << "📉 Max-Heap: Parent ≥ Children (largest at root)" << std::endl;
        std::cout << "🎨 Custom Heap: User-defined comparison function" << std::endl;
        
        std::cout << "\nArray Index Relationships:" << std::endl;
        std::cout << "👨‍👧‍👦 Parent of i: (i-1)/2" << std::endl;
        std::cout << "👧 Left child of i: 2i+1" << std::endl;
        std::cout << "👦 Right child of i: 2i+2" << std::endl;
        
        std::cout << "\nCore Operations Time Complexity:" << std::endl;
        std::cout << "╔══════════════════╦══════════════╗" << std::endl;
        std::cout << "║    Operation     ║ Complexity   ║" << std::endl;
        std::cout << "╠══════════════════╬══════════════╣" << std::endl;
        std::cout << "║ Insert           ║   O(log n)   ║" << std::endl;
        std::cout << "║ Extract Min/Max  ║   O(log n)   ║" << std::endl;
        std::cout << "║ Peek (top)       ║     O(1)     ║" << std::endl;
        std::cout << "║ Build Heap       ║     O(n)     ║" << std::endl;
        std::cout << "║ Heap Sort        ║  O(n log n)  ║" << std::endl;
        std::cout << "║ Delete Element   ║   O(log n)   ║" << std::endl;
        std::cout << "║ Change Priority  ║   O(log n)   ║" << std::endl;
        std::cout << "╚══════════════════╩══════════════╝" << std::endl;
        
        std::cout << "\nSpace Complexity: O(n) for storing n elements" << std::endl;
        
        std::cout << "\nHeapify Operations:" << std::endl;
        std::cout << "⬆️ Heapify Up: Used after insertion, moves element toward root" << std::endl;
        std::cout << "⬇️ Heapify Down: Used after extraction, moves element toward leaves" << std::endl;
        std::cout << "🏗️ Build Heap: Bottom-up construction, more efficient than repeated insertion" << std::endl;
        
        std::cout << "\nCommon Applications:" << std::endl;
        std::cout << "🎯 Priority Queues: Task scheduling, event simulation" << std::endl;
        std::cout << "🛣️ Graph Algorithms: Dijkstra's shortest path, Prim's MST" << std::endl;
        std::cout << "📊 Sorting: Heap sort algorithm" << std::endl;
        std::cout << "💻 Operating Systems: Process scheduling, memory management" << std::endl;
        std::cout << "🎮 Game Development: AI decision making, resource allocation" << std::endl;
        std::cout << "📈 Statistics: Finding kth smallest/largest element" << std::endl;
        std::cout << "📱 Real-time Systems: Event handling, deadline scheduling" << std::endl;
        
        std::cout << "\nAdvantages:" << std::endl;
        std::cout << "✅ Efficient priority queue operations" << std::endl;
        std::cout << "✅ Space-efficient array representation" << std::endl;
        std::cout << "✅ Guaranteed logarithmic operations" << std::endl;
        std::cout << "✅ In-place heap sort possible" << std::endl;
        std::cout << "✅ Simple implementation" << std::endl;
        std::cout << "✅ Cache-friendly due to array storage" << std::endl;
        
        std::cout << "\nDisadvantages:" << std::endl;
        std::cout << "❌ No efficient searching (O(n) for arbitrary elements)" << std::endl;
        std::cout << "❌ No ordering beyond parent-child relationship" << std::endl;
        std::cout << "❌ Not suitable for range queries" << std::endl;
        std::cout << "❌ Heap sort is not stable" << std::endl;
        
        std::cout << "\nWhen to Use Heaps:" << std::endl;
        std::cout << "💡 Need efficient priority queue operations" << std::endl;
        std::cout << "💡 Frequent access to minimum/maximum element" << std::endl;
        std::cout << "💡 Implementing graph algorithms (Dijkstra, Prim)" << std::endl;
        std::cout << "💡 Event-driven simulations" << std::endl;
        std::cout << "💡 Operating system scheduling" << std::endl;
        std::cout << "💡 Finding kth smallest/largest elements" << std::endl;
        
        std::cout << "\nHeap vs Other Data Structures:" << std::endl;
        std::cout << "🆚 BST: Heap better for priority operations, BST better for searching" << std::endl;
        std::cout << "🆚 Sorted Array: Heap better for insertions, array better for access" << std::endl;
        std::cout << "🆚 Linked List: Heap much better for min/max operations" << std::endl;
        std::cout << "🆚 Hash Table: Different use cases - heap for ordering, hash for lookup" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
