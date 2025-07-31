// Lock-Free Data Structures and Atomic Operations in Modern C++
// Compile: g++ -std=c++20 -pthread -O2 -o lockfree_structures lockfree_structures.cpp
// Run: ./lockfree_structures

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <memory>
#include <chrono>
#include <random>
#include <array>
#include <cassert>
#include <functional>
#include <type_traits>

// 1. Lock-free stack using atomic pointers
template<typename T>
class LockFreeStack {
private:
    struct Node {
        T data;
        std::atomic<Node*> next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    std::atomic<Node*> head_{nullptr};
    std::atomic<size_t> size_{0};
    
public:
    LockFreeStack() = default;
    
    ~LockFreeStack() {
        while (Node* node = head_.load()) {
            head_.store(node->next.load());
            delete node;
        }
    }
    
    // Non-copyable, movable
    LockFreeStack(const LockFreeStack&) = delete;
    LockFreeStack& operator=(const LockFreeStack&) = delete;
    
    void push(const T& value) {
        Node* new_node = new Node(value);
        Node* current_head = head_.load();
        
        do {
            new_node->next.store(current_head);
        } while (!head_.compare_exchange_weak(current_head, new_node));
        
        size_.fetch_add(1, std::memory_order_relaxed);
    }
    
    bool pop(T& result) {
        Node* current_head = head_.load();
        
        do {
            if (current_head == nullptr) {
                return false; // Stack is empty
            }
        } while (!head_.compare_exchange_weak(current_head, current_head->next.load()));
        
        result = current_head->data;
        delete current_head;
        size_.fetch_sub(1, std::memory_order_relaxed);
        return true;
    }
    
    bool empty() const {
        return head_.load() == nullptr;
    }
    
    size_t size() const {
        return size_.load(std::memory_order_relaxed);
    }
};

// 2. Lock-free queue using atomic pointers (Michael & Scott algorithm)
template<typename T>
class LockFreeQueue {
private:
    struct Node {
        std::atomic<T*> data{nullptr};
        std::atomic<Node*> next{nullptr};
        
        Node() = default;
    };
    
    std::atomic<Node*> head_;
    std::atomic<Node*> tail_;
    std::atomic<size_t> size_{0};
    
public:
    LockFreeQueue() {
        Node* dummy = new Node;
        head_.store(dummy);
        tail_.store(dummy);
    }
    
    ~LockFreeQueue() {
        while (Node* node = head_.load()) {
            head_.store(node->next.load());
            delete node->data.load();
            delete node;
        }
    }
    
    // Non-copyable
    LockFreeQueue(const LockFreeQueue&) = delete;
    LockFreeQueue& operator=(const LockFreeQueue&) = delete;
    
    void enqueue(const T& value) {
        Node* new_node = new Node;
        T* data = new T(value);
        new_node->data.store(data);
        
        Node* prev_tail = tail_.exchange(new_node);
        prev_tail->next.store(new_node);
        
        size_.fetch_add(1, std::memory_order_relaxed);
    }
    
    bool dequeue(T& result) {
        Node* head = head_.load();
        Node* next = head->next.load();
        
        if (next == nullptr) {
            return false; // Queue is empty
        }
        
        T* data = next->data.load();
        if (data == nullptr) {
            return false; // Another thread got this item
        }
        
        if (!head_.compare_exchange_weak(head, next)) {
            return false; // Another thread changed head
        }
        
        result = *data;
        delete data;
        delete head;
        size_.fetch_sub(1, std::memory_order_relaxed);
        return true;
    }
    
    bool empty() const {
        Node* head = head_.load();
        Node* next = head->next.load();
        return next == nullptr;
    }
    
    size_t size() const {
        return size_.load(std::memory_order_relaxed);
    }
};

// 3. Lock-free hash map using atomic operations
template<typename Key, typename Value, size_t TableSize = 1024>
class LockFreeHashMap {
private:
    struct Node {
        std::atomic<Key> key;
        std::atomic<Value> value;
        std::atomic<Node*> next{nullptr};
        std::atomic<bool> deleted{false};
        
        Node(const Key& k, const Value& v) : key(k), value(v) {}
    };
    
    std::array<std::atomic<Node*>, TableSize> buckets_;
    std::atomic<size_t> size_{0};
    
    size_t hash(const Key& key) const {
        return std::hash<Key>{}(key) % TableSize;
    }
    
public:
    LockFreeHashMap() {
        for (auto& bucket : buckets_) {
            bucket.store(nullptr);
        }
    }
    
    ~LockFreeHashMap() {
        for (auto& bucket : buckets_) {
            Node* node = bucket.load();
            while (node) {
                Node* next = node->next.load();
                delete node;
                node = next;
            }
        }
    }
    
    bool insert(const Key& key, const Value& value) {
        size_t bucket_index = hash(key);
        Node* new_node = new Node(key, value);
        
        Node* expected = nullptr;
        if (buckets_[bucket_index].compare_exchange_strong(expected, new_node)) {
            size_.fetch_add(1, std::memory_order_relaxed);
            return true;
        }
        
        // Collision - add to chain
        Node* current = buckets_[bucket_index].load();
        while (current) {
            if (current->key.load() == key && !current->deleted.load()) {
                delete new_node;
                return false; // Key already exists
            }
            
            Node* next = current->next.load();
            if (next == nullptr) {
                if (current->next.compare_exchange_weak(next, new_node)) {
                    size_.fetch_add(1, std::memory_order_relaxed);
                    return true;
                }
            }
            current = next;
        }
        
        delete new_node;
        return false;
    }
    
    bool find(const Key& key, Value& result) const {
        size_t bucket_index = hash(key);
        Node* current = buckets_[bucket_index].load();
        
        while (current) {
            if (current->key.load() == key && !current->deleted.load()) {
                result = current->value.load();
                return true;
            }
            current = current->next.load();
        }
        
        return false;
    }
    
    bool erase(const Key& key) {
        size_t bucket_index = hash(key);
        Node* current = buckets_[bucket_index].load();
        
        while (current) {
            if (current->key.load() == key && !current->deleted.load()) {
                current->deleted.store(true);
                size_.fetch_sub(1, std::memory_order_relaxed);
                return true;
            }
            current = current->next.load();
        }
        
        return false;
    }
    
    size_t size() const {
        return size_.load(std::memory_order_relaxed);
    }
};

// 4. Atomic reference counter for lock-free memory management
template<typename T>
class AtomicSharedPtr {
private:
    struct ControlBlock {
        T* ptr;
        std::atomic<int> ref_count;
        
        ControlBlock(T* p) : ptr(p), ref_count(1) {}
        
        ~ControlBlock() {
            delete ptr;
        }
    };
    
    std::atomic<ControlBlock*> control_block_{nullptr};
    
public:
    AtomicSharedPtr() = default;
    
    explicit AtomicSharedPtr(T* ptr) {
        if (ptr) {
            control_block_.store(new ControlBlock(ptr));
        }
    }
    
    AtomicSharedPtr(const AtomicSharedPtr& other) {
        ControlBlock* other_cb = other.control_block_.load();
        if (other_cb) {
            other_cb->ref_count.fetch_add(1);
            control_block_.store(other_cb);
        }
    }
    
    AtomicSharedPtr& operator=(const AtomicSharedPtr& other) {
        if (this != &other) {
            reset();
            
            ControlBlock* other_cb = other.control_block_.load();
            if (other_cb) {
                other_cb->ref_count.fetch_add(1);
                control_block_.store(other_cb);
            }
        }
        return *this;
    }
    
    ~AtomicSharedPtr() {
        reset();
    }
    
    T* get() const {
        ControlBlock* cb = control_block_.load();
        return cb ? cb->ptr : nullptr;
    }
    
    T& operator*() const {
        return *get();
    }
    
    T* operator->() const {
        return get();
    }
    
    void reset() {
        ControlBlock* cb = control_block_.exchange(nullptr);
        if (cb && cb->ref_count.fetch_sub(1) == 1) {
            delete cb;
        }
    }
    
    long use_count() const {
        ControlBlock* cb = control_block_.load();
        return cb ? cb->ref_count.load() : 0;
    }
    
    explicit operator bool() const {
        return get() != nullptr;
    }
};

// 5. Lock-free ring buffer (SPSC - Single Producer Single Consumer)
template<typename T, size_t Size>
class LockFreeRingBuffer {
private:
    static_assert((Size & (Size - 1)) == 0, "Size must be power of 2");
    static constexpr size_t MASK = Size - 1;
    
    std::array<T, Size> buffer_;
    std::atomic<size_t> write_pos_{0};
    std::atomic<size_t> read_pos_{0};
    
public:
    bool push(const T& item) {
        size_t current_write = write_pos_.load(std::memory_order_relaxed);
        size_t next_write = (current_write + 1) & MASK;
        
        if (next_write == read_pos_.load(std::memory_order_acquire)) {
            return false; // Buffer full
        }
        
        buffer_[current_write] = item;
        write_pos_.store(next_write, std::memory_order_release);
        return true;
    }
    
    bool pop(T& item) {
        size_t current_read = read_pos_.load(std::memory_order_relaxed);
        
        if (current_read == write_pos_.load(std::memory_order_acquire)) {
            return false; // Buffer empty
        }
        
        item = buffer_[current_read];
        read_pos_.store((current_read + 1) & MASK, std::memory_order_release);
        return true;
    }
    
    size_t size() const {
        size_t write = write_pos_.load(std::memory_order_relaxed);
        size_t read = read_pos_.load(std::memory_order_relaxed);
        return (write - read) & MASK;
    }
    
    bool empty() const {
        return read_pos_.load(std::memory_order_relaxed) == 
               write_pos_.load(std::memory_order_relaxed);
    }
    
    bool full() const {
        size_t write = write_pos_.load(std::memory_order_relaxed);
        size_t read = read_pos_.load(std::memory_order_relaxed);
        return ((write + 1) & MASK) == read;
    }
};

// 6. Memory ordering demonstration
void demonstrate_memory_ordering() {
    std::cout << "\n=== Memory Ordering Examples ===" << std::endl;
    
    // Relaxed ordering - no synchronization
    {
        std::cout << "\n--- Relaxed Ordering ---" << std::endl;
        std::atomic<int> counter{0};
        std::atomic<bool> ready{false};
        
        std::vector<std::jthread> threads;
        
        // Multiple threads incrementing counter with relaxed ordering
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back([&counter, &ready, i]() {
                while (!ready.load(std::memory_order_relaxed)) {
                    std::this_thread::yield();
                }
                
                for (int j = 0; j < 1000; ++j) {
                    counter.fetch_add(1, std::memory_order_relaxed);
                }
                
                std::cout << "Thread " << i << " completed" << std::endl;
            });
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ready.store(true, std::memory_order_relaxed);
        
        for (auto& t : threads) {
            t.join();
        }
        
        std::cout << "Final counter value (relaxed): " << counter.load() << std::endl;
    }
    
    // Acquire-Release ordering
    {
        std::cout << "\n--- Acquire-Release Ordering ---" << std::endl;
        std::atomic<int> data{0};
        std::atomic<bool> data_ready{false};
        
        // Producer thread
        std::jthread producer([&data, &data_ready]() {
            data.store(42, std::memory_order_relaxed);
            data_ready.store(true, std::memory_order_release); // Release
            std::cout << "Producer: Data published" << std::endl;
        });
        
        // Consumer thread
        std::jthread consumer([&data, &data_ready]() {
            while (!data_ready.load(std::memory_order_acquire)) { // Acquire
                std::this_thread::yield();
            }
            
            int value = data.load(std::memory_order_relaxed);
            std::cout << "Consumer: Read data = " << value << std::endl;
        });
        
        producer.join();
        consumer.join();
    }
    
    // Sequential consistency (default)
    {
        std::cout << "\n--- Sequential Consistency ---" << std::endl;
        std::atomic<int> x{0}, y{0};
        std::atomic<int> r1{0}, r2{0};
        
        std::jthread t1([&x, &y, &r1]() {
            x.store(1); // seq_cst by default
            r1.store(y.load());
        });
        
        std::jthread t2([&x, &y, &r2]() {
            y.store(1); // seq_cst by default
            r2.store(x.load());
        });
        
        t1.join();
        t2.join();
        
        std::cout << "Sequential consistency: r1=" << r1.load() 
                  << ", r2=" << r2.load() << std::endl;
        std::cout << "Both r1 and r2 cannot be 0 with sequential consistency" << std::endl;
    }
}

// Performance testing utilities
template<typename Container>
void test_concurrent_operations(Container& container, const std::string& name, 
                               int num_threads, int ops_per_thread) {
    std::cout << "\n--- Testing " << name << " ---" << std::endl;
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::vector<std::jthread> threads;
    std::atomic<int> completed_ops{0};
    
    // Producer threads
    for (int i = 0; i < num_threads / 2; ++i) {
        threads.emplace_back([&container, &completed_ops, ops_per_thread, i]() {
            std::random_device rd;
            std::mt19937 gen(rd());
            
            for (int j = 0; j < ops_per_thread; ++j) {
                container.push(i * 1000 + j);
                completed_ops.fetch_add(1, std::memory_order_relaxed);
            }
        });
    }
    
    // Consumer threads
    for (int i = num_threads / 2; i < num_threads; ++i) {
        threads.emplace_back([&container, &completed_ops, ops_per_thread]() {
            int value;
            int successful_pops = 0;
            
            while (successful_pops < ops_per_thread) {
                if (container.pop(value)) {
                    successful_pops++;
                    completed_ops.fetch_add(1, std::memory_order_relaxed);
                } else {
                    std::this_thread::yield();
                }
            }
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    std::cout << name << " completed " << completed_ops.load() << " operations" << std::endl;
    std::cout << "Time: " << duration.count() << " microseconds" << std::endl;
    std::cout << "Operations/second: " << (completed_ops.load() * 1000000.0) / duration.count() << std::endl;
}

int main() {
    std::cout << "=== Lock-Free Data Structures and Atomic Operations ===" << std::endl;
    
    // Test lock-free stack
    {
        std::cout << "\n=== 1. Lock-Free Stack Test ===" << std::endl;
        
        LockFreeStack<int> stack;
        
        // Single-threaded test
        for (int i = 0; i < 10; ++i) {
            stack.push(i);
        }
        
        std::cout << "Stack size after pushes: " << stack.size() << std::endl;
        
        int value;
        std::cout << "Popped values: ";
        while (stack.pop(value)) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
        // Multi-threaded performance test
        LockFreeStack<int> concurrent_stack;
        test_concurrent_operations(concurrent_stack, "Lock-Free Stack", 8, 1000);
    }
    
    // Test lock-free queue
    {
        std::cout << "\n=== 2. Lock-Free Queue Test ===" << std::endl;
        
        LockFreeQueue<int> queue;
        
        // Single-threaded test
        for (int i = 0; i < 10; ++i) {
            queue.enqueue(i);
        }
        
        std::cout << "Queue size after enqueues: " << queue.size() << std::endl;
        
        int value;
        std::cout << "Dequeued values: ";
        while (queue.dequeue(value)) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
        // Multi-threaded test
        std::cout << "\nMulti-threaded queue test..." << std::endl;
        
        std::vector<std::jthread> threads;
        std::atomic<int> total_enqueued{0};
        std::atomic<int> total_dequeued{0};
        
        // Producer threads
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back([&queue, &total_enqueued, i]() {
                for (int j = 0; j < 1000; ++j) {
                    queue.enqueue(i * 1000 + j);
                    total_enqueued.fetch_add(1, std::memory_order_relaxed);
                }
            });
        }
        
        // Consumer threads
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back([&queue, &total_dequeued]() {
                int value;
                int count = 0;
                
                while (count < 1000) {
                    if (queue.dequeue(value)) {
                        count++;
                        total_dequeued.fetch_add(1, std::memory_order_relaxed);
                    } else {
                        std::this_thread::yield();
                    }
                }
            });
        }
        
        for (auto& thread : threads) {
            thread.join();
        }
        
        std::cout << "Total enqueued: " << total_enqueued.load() << std::endl;
        std::cout << "Total dequeued: " << total_dequeued.load() << std::endl;
        std::cout << "Final queue size: " << queue.size() << std::endl;
    }
    
    // Test lock-free hash map
    {
        std::cout << "\n=== 3. Lock-Free Hash Map Test ===" << std::endl;
        
        LockFreeHashMap<int, std::string> hashmap;
        
        // Single-threaded test
        hashmap.insert(1, "one");
        hashmap.insert(2, "two");
        hashmap.insert(3, "three");
        
        std::string value;
        if (hashmap.find(2, value)) {
            std::cout << "Found key 2: " << value << std::endl;
        }
        
        std::cout << "Hash map size: " << hashmap.size() << std::endl;
        
        // Multi-threaded test
        std::vector<std::jthread> threads;
        std::atomic<int> successful_inserts{0};
        std::atomic<int> successful_finds{0};
        
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back([&hashmap, &successful_inserts, i]() {
                for (int j = 0; j < 1000; ++j) {
                    int key = i * 1000 + j;
                    if (hashmap.insert(key, "value_" + std::to_string(key))) {
                        successful_inserts.fetch_add(1, std::memory_order_relaxed);
                    }
                }
            });
        }
        
        for (int i = 0; i < 2; ++i) {
            threads.emplace_back([&hashmap, &successful_finds]() {
                std::string result;
                for (int j = 0; j < 2000; ++j) {
                    if (hashmap.find(j, result)) {
                        successful_finds.fetch_add(1, std::memory_order_relaxed);
                    }
                }
            });
        }
        
        for (auto& thread : threads) {
            thread.join();
        }
        
        std::cout << "Successful inserts: " << successful_inserts.load() << std::endl;
        std::cout << "Successful finds: " << successful_finds.load() << std::endl;
        std::cout << "Final hash map size: " << hashmap.size() << std::endl;
    }
    
    // Test atomic shared pointer
    {
        std::cout << "\n=== 4. Atomic Shared Pointer Test ===" << std::endl;
        
        AtomicSharedPtr<int> shared_ptr(new int(42));
        std::cout << "Initial value: " << *shared_ptr << std::endl;
        std::cout << "Use count: " << shared_ptr.use_count() << std::endl;
        
        // Test copy constructor
        AtomicSharedPtr<int> shared_ptr2 = shared_ptr;
        std::cout << "After copy - Use count: " << shared_ptr.use_count() << std::endl;
        
        shared_ptr2.reset();
        std::cout << "After reset - Use count: " << shared_ptr.use_count() << std::endl;
    }
    
    // Test ring buffer
    {
        std::cout << "\n=== 5. Lock-Free Ring Buffer Test ===" << std::endl;
        
        LockFreeRingBuffer<int, 16> ring_buffer;
        
        // Single producer, single consumer test
        std::jthread producer([&ring_buffer]() {
            for (int i = 0; i < 100; ++i) {
                while (!ring_buffer.push(i)) {
                    std::this_thread::yield();
                }
            }
            std::cout << "Producer finished" << std::endl;
        });
        
        std::jthread consumer([&ring_buffer]() {
            int value;
            int count = 0;
            
            while (count < 100) {
                if (ring_buffer.pop(value)) {
                    count++;
                    if (count % 25 == 0) {
                        std::cout << "Consumer received: " << value << std::endl;
                    }
                } else {
                    std::this_thread::yield();
                }
            }
            std::cout << "Consumer finished" << std::endl;
        });
        
        producer.join();
        consumer.join();
        
        std::cout << "Final buffer size: " << ring_buffer.size() << std::endl;
    }
    
    // Memory ordering demonstrations
    demonstrate_memory_ordering();
    
    std::cout << "\n=== Lock-Free Programming Benefits ===" << std::endl;
    std::cout << "✅ No deadlocks or priority inversion" << std::endl;
    std::cout << "✅ Better scalability on multi-core systems" << std::endl;
    std::cout << "✅ Reduced contention and context switching" << std::endl;
    std::cout << "✅ Predictable performance characteristics" << std::endl;
    std::cout << "✅ Fault tolerance (no blocking on thread failure)" << std::endl;
    
    std::cout << "\n=== Key Atomic Operations ===" << std::endl;
    std::cout << "• compare_exchange_weak/strong - CAS operations" << std::endl;
    std::cout << "• fetch_add/sub - Atomic arithmetic" << std::endl;
    std::cout << "• load/store - Basic atomic access" << std::endl;
    std::cout << "• exchange - Atomic swap" << std::endl;
    
    std::cout << "\n=== Memory Ordering Models ===" << std::endl;
    std::cout << "• memory_order_relaxed - No ordering constraints" << std::endl;
    std::cout << "• memory_order_acquire - Acquire semantics" << std::endl;
    std::cout << "• memory_order_release - Release semantics" << std::endl;
    std::cout << "• memory_order_acq_rel - Both acquire and release" << std::endl;
    std::cout << "• memory_order_seq_cst - Sequential consistency (default)" << std::endl;
    
    return 0;
}

/*
COMPILATION AND OPTIMIZATION:

Basic compilation:
g++ -std=c++20 -pthread -O2 -o lockfree_structures lockfree_structures.cpp

With additional optimizations:
g++ -std=c++20 -pthread -O3 -march=native -DNDEBUG -o lockfree_structures lockfree_structures.cpp

With debugging:
g++ -std=c++20 -pthread -g -fsanitize=thread -o lockfree_structures lockfree_structures.cpp

Key Concepts:

Lock-Free Programming:
- Uses atomic operations instead of locks
- Compare-and-swap (CAS) operations
- Memory ordering guarantees
- ABA problem prevention

Atomic Operations:
- Hardware-level synchronization
- Guaranteed atomicity without locks
- Memory barrier effects
- Platform-specific optimizations

Memory Ordering:
- Controls how memory operations are reordered
- Affects performance and correctness
- Different models for different use cases
- Critical for multi-core systems

Data Structures Implemented:

1. Lock-Free Stack:
- Uses atomic pointer swapping
- LIFO ordering maintained
- ABA problem handled by immediate deletion

2. Lock-Free Queue (FIFO):
- Michael & Scott algorithm
- Separate head/tail pointers
- Handles concurrent enqueue/dequeue

3. Lock-Free Hash Map:
- Chaining for collision resolution
- Lazy deletion marking
- Atomic key-value operations

4. Atomic Shared Pointer:
- Reference counting with atomics
- Memory management without locks
- Safe concurrent access

5. Lock-Free Ring Buffer:
- Single producer, single consumer
- Power-of-2 sizing for efficiency
- Memory ordering for synchronization

Performance Characteristics:

Advantages:
- No lock contention
- Better scalability
- Predictable latency
- No deadlocks
- Composable operations

Disadvantages:
- Complex implementation
- Memory ordering complexity
- Platform-dependent behavior
- Potential for live-lock
- Harder to debug

Real-world Applications:
- High-frequency trading systems
- Real-time audio/video processing
- Network packet processing
- Game engine updates
- Concurrent data analytics
- Operating system kernels
- Database storage engines

Best Practices:
- Use established algorithms (Michael & Scott, etc.)
- Careful memory ordering selection
- Extensive testing on target platforms
- Profile performance characteristics
- Consider alternative solutions first
- Understand ABA problem implications
- Plan for memory reclamation strategies

Testing Considerations:
- Multi-core stress testing
- Memory sanitizers (ThreadSanitizer)
- Weak memory model testing
- Performance benchmarking
- Correctness verification
- Race condition detection
*/
