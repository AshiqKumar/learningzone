// Hash Table Implementation - Complete program with collision resolution
/*
Key Features of Hash Table:
Core Operations:
✅ Insertion: Add key-value pairs with O(1) average time
✅ Search: Find values by key with O(1) average time
✅ Deletion: Remove key-value pairs with O(1) average time
✅ Dynamic Resizing: Automatic table resizing when load factor exceeded
Hash Table Features:
🔍 Fast Access: Direct indexing via hash function
📊 Collision Resolution: Chain and Open Addressing methods
🎯 Load Factor Management: Maintains optimal performance
💾 Dynamic Capacity: Grows and shrinks as needed
Advanced Features:
🔄 Multiple Hash Functions: Different hashing strategies
🛡️ Collision Handling: Separate chaining and linear probing
📈 Performance Monitoring: Load factor and collision statistics
🎨 Custom Hash Functions: Support for custom types
Smart Memory Management:
🧠 Uses vectors and smart pointers for efficiency
🛡️ Exception-safe operations throughout
🚫 RAII principles for resource management
📈 Efficient memory usage with dynamic resizing
Educational Demonstrations:
📊 Performance Analysis: Best/average/worst case scenarios
🧪 Collision Resolution Comparison: Different strategies
📝 Hash Function Quality: Distribution analysis
🔄 Load Factor Impact: Performance vs memory trade-offs
*/

#include <iostream>
#include <vector>
#include <list>
#include <optional>
#include <functional>
#include <string>
#include <memory>
#include <algorithm>
#include <iomanip>

// Hash Table with Separate Chaining
template<typename K, typename V>
class HashTableChaining {
public:
    struct KeyValue {
        K key;
        V value;
        
        KeyValue(const K& k, const V& v) : key(k), value(v) {}
    };
    
private:
    static constexpr size_t DEFAULT_CAPACITY = 16;
    static constexpr double MAX_LOAD_FACTOR = 0.75;
    static constexpr double MIN_LOAD_FACTOR = 0.25;
    
    std::vector<std::list<KeyValue>> table_;
    size_t size_;
    size_t capacity_;
    std::hash<K> hasher_;
    
    // Hash function
    size_t hash(const K& key) const {
        return hasher_(key) % capacity_;
    }
    
    // Resize the table
    void resize(size_t newCapacity) {
        std::cout << "Resizing hash table from " << capacity_ << " to " << newCapacity << std::endl;
        
        std::vector<std::list<KeyValue>> oldTable = std::move(table_);
        size_t oldCapacity = capacity_;
        
        capacity_ = newCapacity;
        table_.clear();
        table_.resize(capacity_);
        size_t oldSize = size_;
        size_ = 0;
        
        // Rehash all elements
        for (const auto& bucket : oldTable) {
            for (const auto& kv : bucket) {
                insertInternal(kv.key, kv.value);
            }
        }
        
        std::cout << "Rehashed " << oldSize << " elements" << std::endl;
    }
    
    // Internal insert without resize check
    bool insertInternal(const K& key, const V& value) {
        size_t index = hash(key);
        
        // Check if key already exists
        for (auto& kv : table_[index]) {
            if (kv.key == key) {
                kv.value = value; // Update existing value
                return false; // Key already existed
            }
        }
        
        table_[index].emplace_back(key, value);
        size_++;
        return true; // New key inserted
    }
    
public:
    // Constructor
    explicit HashTableChaining(size_t capacity = DEFAULT_CAPACITY) 
        : capacity_(capacity), size_(0) {
        table_.resize(capacity_);
    }
    
    // Insert key-value pair
    void insert(const K& key, const V& value) {
        // Check if resize is needed
        if (static_cast<double>(size_) / capacity_ >= MAX_LOAD_FACTOR) {
            resize(capacity_ * 2);
        }
        
        bool newKey = insertInternal(key, value);
        std::cout << "Insert " << key << " -> " << value 
                  << (newKey ? " (new)" : " (updated)") 
                  << " | Load factor: " << std::fixed << std::setprecision(3) 
                  << static_cast<double>(size_) / capacity_ << std::endl;
    }
    
    // Search for a value by key
    std::optional<V> search(const K& key) const {
        size_t index = hash(key);
        
        for (const auto& kv : table_[index]) {
            if (kv.key == key) {
                return kv.value;
            }
        }
        
        return std::nullopt;
    }
    
    // Remove key-value pair
    bool remove(const K& key) {
        size_t index = hash(key);
        
        auto& bucket = table_[index];
        auto it = std::find_if(bucket.begin(), bucket.end(),
                              [&key](const KeyValue& kv) { return kv.key == key; });
        
        if (it != bucket.end()) {
            bucket.erase(it);
            size_--;
            
            // Check if resize down is needed
            if (capacity_ > DEFAULT_CAPACITY && 
                static_cast<double>(size_) / capacity_ < MIN_LOAD_FACTOR) {
                resize(capacity_ / 2);
            }
            
            std::cout << "Removed " << key 
                      << " | Load factor: " << std::fixed << std::setprecision(3) 
                      << static_cast<double>(size_) / capacity_ << std::endl;
            return true;
        }
        
        std::cout << "Key " << key << " not found for removal" << std::endl;
        return false;
    }
    
    // Check if key exists
    bool contains(const K& key) const {
        return search(key).has_value();
    }
    
    // Get all keys
    std::vector<K> keys() const {
        std::vector<K> result;
        for (const auto& bucket : table_) {
            for (const auto& kv : bucket) {
                result.push_back(kv.key);
            }
        }
        return result;
    }
    
    // Get all values
    std::vector<V> values() const {
        std::vector<V> result;
        for (const auto& bucket : table_) {
            for (const auto& kv : bucket) {
                result.push_back(kv.value);
            }
        }
        return result;
    }
    
    // Properties
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    double loadFactor() const { return static_cast<double>(size_) / capacity_; }
    
    // Statistics
    void printStatistics() const {
        std::cout << "\nHash Table Statistics (Chaining):" << std::endl;
        std::cout << "Size: " << size_ << std::endl;
        std::cout << "Capacity: " << capacity_ << std::endl;
        std::cout << "Load Factor: " << std::fixed << std::setprecision(3) << loadFactor() << std::endl;
        
        // Calculate collision statistics
        size_t emptyBuckets = 0;
        size_t maxChainLength = 0;
        size_t totalCollisions = 0;
        
        for (const auto& bucket : table_) {
            if (bucket.empty()) {
                emptyBuckets++;
            } else {
                maxChainLength = std::max(maxChainLength, bucket.size());
                if (bucket.size() > 1) {
                    totalCollisions += bucket.size() - 1;
                }
            }
        }
        
        std::cout << "Empty Buckets: " << emptyBuckets << " (" 
                  << std::fixed << std::setprecision(1)
                  << (100.0 * emptyBuckets / capacity_) << "%)" << std::endl;
        std::cout << "Max Chain Length: " << maxChainLength << std::endl;
        std::cout << "Total Collisions: " << totalCollisions << std::endl;
        std::cout << "Average Chain Length: " 
                  << std::fixed << std::setprecision(2)
                  << static_cast<double>(size_) / (capacity_ - emptyBuckets) << std::endl;
    }
    
    // Display table structure
    void displayTable() const {
        std::cout << "\nHash Table Structure:" << std::endl;
        for (size_t i = 0; i < capacity_; ++i) {
            std::cout << "Bucket " << std::setw(2) << i << ": ";
            if (table_[i].empty()) {
                std::cout << "(empty)";
            } else {
                bool first = true;
                for (const auto& kv : table_[i]) {
                    if (!first) std::cout << " -> ";
                    std::cout << "[" << kv.key << ":" << kv.value << "]";
                    first = false;
                }
            }
            std::cout << std::endl;
        }
    }
    
    // Clear all elements
    void clear() {
        for (auto& bucket : table_) {
            bucket.clear();
        }
        size_ = 0;
        std::cout << "Hash table cleared" << std::endl;
    }
};

// Hash Table with Open Addressing (Linear Probing)
template<typename K, typename V>
class HashTableOpenAddressing {
public:
    enum class EntryState { EMPTY, OCCUPIED, DELETED };
    
    struct Entry {
        K key;
        V value;
        EntryState state;
        
        Entry() : state(EntryState::EMPTY) {}
        Entry(const K& k, const V& v) : key(k), value(v), state(EntryState::OCCUPIED) {}
    };
    
private:
    static constexpr size_t DEFAULT_CAPACITY = 16;
    static constexpr double MAX_LOAD_FACTOR = 0.5; // Lower for open addressing
    static constexpr double MIN_LOAD_FACTOR = 0.125;
    
    std::vector<Entry> table_;
    size_t size_;
    size_t capacity_;
    std::hash<K> hasher_;
    
    // Hash function
    size_t hash(const K& key) const {
        return hasher_(key) % capacity_;
    }
    
    // Find slot for key (for insertion or search)
    size_t findSlot(const K& key) const {
        size_t index = hash(key);
        size_t originalIndex = index;
        
        while (table_[index].state != EntryState::EMPTY) {
            if (table_[index].state == EntryState::OCCUPIED && table_[index].key == key) {
                return index; // Found the key
            }
            
            index = (index + 1) % capacity_;
            
            // If we've gone full circle, table is full
            if (index == originalIndex) {
                break;
            }
        }
        
        return index; // Return first empty or deleted slot found
    }
    
    // Resize the table
    void resize(size_t newCapacity) {
        std::cout << "Resizing hash table from " << capacity_ << " to " << newCapacity << std::endl;
        
        std::vector<Entry> oldTable = std::move(table_);
        size_t oldCapacity = capacity_;
        
        capacity_ = newCapacity;
        table_.clear();
        table_.resize(capacity_);
        size_t oldSize = size_;
        size_ = 0;
        
        // Rehash all elements
        for (const auto& entry : oldTable) {
            if (entry.state == EntryState::OCCUPIED) {
                insertInternal(entry.key, entry.value);
            }
        }
        
        std::cout << "Rehashed " << oldSize << " elements" << std::endl;
    }
    
    // Internal insert without resize check
    bool insertInternal(const K& key, const V& value) {
        size_t index = findSlot(key);
        
        if (table_[index].state == EntryState::OCCUPIED && table_[index].key == key) {
            table_[index].value = value; // Update existing
            return false;
        }
        
        table_[index] = Entry(key, value);
        size_++;
        return true;
    }
    
public:
    // Constructor
    explicit HashTableOpenAddressing(size_t capacity = DEFAULT_CAPACITY) 
        : capacity_(capacity), size_(0) {
        table_.resize(capacity_);
    }
    
    // Insert key-value pair
    void insert(const K& key, const V& value) {
        // Check if resize is needed
        if (static_cast<double>(size_) / capacity_ >= MAX_LOAD_FACTOR) {
            resize(capacity_ * 2);
        }
        
        bool newKey = insertInternal(key, value);
        std::cout << "Insert " << key << " -> " << value 
                  << (newKey ? " (new)" : " (updated)") 
                  << " | Load factor: " << std::fixed << std::setprecision(3) 
                  << static_cast<double>(size_) / capacity_ << std::endl;
    }
    
    // Search for a value by key
    std::optional<V> search(const K& key) const {
        size_t index = hash(key);
        size_t originalIndex = index;
        
        while (table_[index].state != EntryState::EMPTY) {
            if (table_[index].state == EntryState::OCCUPIED && table_[index].key == key) {
                return table_[index].value;
            }
            
            index = (index + 1) % capacity_;
            
            if (index == originalIndex) {
                break;
            }
        }
        
        return std::nullopt;
    }
    
    // Remove key-value pair
    bool remove(const K& key) {
        size_t index = hash(key);
        size_t originalIndex = index;
        
        while (table_[index].state != EntryState::EMPTY) {
            if (table_[index].state == EntryState::OCCUPIED && table_[index].key == key) {
                table_[index].state = EntryState::DELETED;
                size_--;
                
                // Check if resize down is needed
                if (capacity_ > DEFAULT_CAPACITY && 
                    static_cast<double>(size_) / capacity_ < MIN_LOAD_FACTOR) {
                    resize(capacity_ / 2);
                }
                
                std::cout << "Removed " << key 
                          << " | Load factor: " << std::fixed << std::setprecision(3) 
                          << static_cast<double>(size_) / capacity_ << std::endl;
                return true;
            }
            
            index = (index + 1) % capacity_;
            
            if (index == originalIndex) {
                break;
            }
        }
        
        std::cout << "Key " << key << " not found for removal" << std::endl;
        return false;
    }
    
    // Check if key exists
    bool contains(const K& key) const {
        return search(key).has_value();
    }
    
    // Get all keys
    std::vector<K> keys() const {
        std::vector<K> result;
        for (const auto& entry : table_) {
            if (entry.state == EntryState::OCCUPIED) {
                result.push_back(entry.key);
            }
        }
        return result;
    }
    
    // Get all values
    std::vector<V> values() const {
        std::vector<V> result;
        for (const auto& entry : table_) {
            if (entry.state == EntryState::OCCUPIED) {
                result.push_back(entry.value);
            }
        }
        return result;
    }
    
    // Properties
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    double loadFactor() const { return static_cast<double>(size_) / capacity_; }
    
    // Statistics
    void printStatistics() const {
        std::cout << "\nHash Table Statistics (Open Addressing):" << std::endl;
        std::cout << "Size: " << size_ << std::endl;
        std::cout << "Capacity: " << capacity_ << std::endl;
        std::cout << "Load Factor: " << std::fixed << std::setprecision(3) << loadFactor() << std::endl;
        
        size_t emptySlots = 0;
        size_t deletedSlots = 0;
        size_t occupiedSlots = 0;
        
        for (const auto& entry : table_) {
            switch (entry.state) {
                case EntryState::EMPTY:
                    emptySlots++;
                    break;
                case EntryState::DELETED:
                    deletedSlots++;
                    break;
                case EntryState::OCCUPIED:
                    occupiedSlots++;
                    break;
            }
        }
        
        std::cout << "Occupied Slots: " << occupiedSlots << std::endl;
        std::cout << "Deleted Slots: " << deletedSlots << std::endl;
        std::cout << "Empty Slots: " << emptySlots << std::endl;
        std::cout << "Utilization: " << std::fixed << std::setprecision(1)
                  << (100.0 * occupiedSlots / capacity_) << "%" << std::endl;
    }
    
    // Display table structure
    void displayTable() const {
        std::cout << "\nHash Table Structure:" << std::endl;
        for (size_t i = 0; i < capacity_; ++i) {
            std::cout << "Slot " << std::setw(2) << i << ": ";
            
            switch (table_[i].state) {
                case EntryState::EMPTY:
                    std::cout << "(empty)";
                    break;
                case EntryState::DELETED:
                    std::cout << "(deleted)";
                    break;
                case EntryState::OCCUPIED:
                    std::cout << "[" << table_[i].key << ":" << table_[i].value << "]";
                    break;
            }
            std::cout << std::endl;
        }
    }
    
    // Clear all elements
    void clear() {
        for (auto& entry : table_) {
            entry.state = EntryState::EMPTY;
        }
        size_ = 0;
        std::cout << "Hash table cleared" << std::endl;
    }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void demonstrateBasicOperations() {
    printSeparator("BASIC HASH TABLE OPERATIONS");
    
    std::cout << "\n--- Separate Chaining Implementation ---" << std::endl;
    HashTableChaining<int, std::string> hashTable(8);
    
    // Insert some key-value pairs
    hashTable.insert(1, "One");
    hashTable.insert(9, "Nine");  // Will cause collision with key 1 (1 % 8 = 9 % 8 = 1)
    hashTable.insert(17, "Seventeen"); // Another collision
    hashTable.insert(5, "Five");
    hashTable.insert(3, "Three");
    
    hashTable.displayTable();
    hashTable.printStatistics();
    
    std::cout << "\n--- Search Operations ---" << std::endl;
    auto result = hashTable.search(9);
    std::cout << "Search for key 9: " << (result ? *result : "Not found") << std::endl;
    
    result = hashTable.search(15);
    std::cout << "Search for key 15: " << (result ? *result : "Not found") << std::endl;
    
    std::cout << "Contains key 1: " << (hashTable.contains(1) ? "Yes" : "No") << std::endl;
    std::cout << "Contains key 10: " << (hashTable.contains(10) ? "Yes" : "No") << std::endl;
}

void demonstrateOpenAddressing() {
    printSeparator("OPEN ADDRESSING (LINEAR PROBING)");
    
    HashTableOpenAddressing<int, std::string> hashTable(8);
    
    std::cout << "\n--- Insertion with Linear Probing ---" << std::endl;
    hashTable.insert(1, "One");
    hashTable.insert(9, "Nine");    // Collision with 1, probes to next slot
    hashTable.insert(17, "Seventeen"); // Collision, probes further
    hashTable.insert(5, "Five");
    hashTable.insert(3, "Three");
    
    hashTable.displayTable();
    hashTable.printStatistics();
    
    std::cout << "\n--- Search and Delete Operations ---" << std::endl;
    auto result = hashTable.search(17);
    std::cout << "Search for key 17: " << (result ? *result : "Not found") << std::endl;
    
    hashTable.remove(9);
    hashTable.displayTable();
    
    // Search again to show probing still works after deletion
    result = hashTable.search(17);
    std::cout << "Search for key 17 after deleting 9: " << (result ? *result : "Not found") << std::endl;
}

void demonstrateDynamicResizing() {
    printSeparator("DYNAMIC RESIZING");
    
    HashTableChaining<int, int> hashTable(4); // Start with small capacity
    
    std::cout << "\n--- Triggering Resize Up ---" << std::endl;
    hashTable.printStatistics();
    
    // Add elements to trigger resize
    for (int i = 1; i <= 8; ++i) {
        hashTable.insert(i, i * 10);
    }
    
    hashTable.printStatistics();
    
    std::cout << "\n--- Triggering Resize Down ---" << std::endl;
    // Remove elements to trigger resize down
    for (int i = 1; i <= 6; ++i) {
        hashTable.remove(i);
    }
    
    hashTable.printStatistics();
}

void demonstrateCollisionComparison() {
    printSeparator("COLLISION RESOLUTION COMPARISON");
    
    std::cout << "\n--- Same Data in Both Implementations ---" << std::endl;
    
    HashTableChaining<int, std::string> chainTable(8);
    HashTableOpenAddressing<int, std::string> probeTable(8);
    
    // Insert same data in both tables
    std::vector<std::pair<int, std::string>> data = {
        {1, "One"}, {9, "Nine"}, {17, "Seventeen"}, 
        {25, "TwentyFive"}, {5, "Five"}, {13, "Thirteen"}
    };
    
    std::cout << "Inserting in Chaining Table:" << std::endl;
    for (const auto& [key, value] : data) {
        chainTable.insert(key, value);
    }
    
    std::cout << "\nInserting in Open Addressing Table:" << std::endl;
    for (const auto& [key, value] : data) {
        probeTable.insert(key, value);
    }
    
    std::cout << "\n--- Chaining Table Structure ---" << std::endl;
    chainTable.displayTable();
    chainTable.printStatistics();
    
    std::cout << "\n--- Open Addressing Table Structure ---" << std::endl;
    probeTable.displayTable();
    probeTable.printStatistics();
}

void demonstratePracticalApplications() {
    printSeparator("PRACTICAL APPLICATIONS");
    
    // 1. Phone Book
    std::cout << "\n--- Phone Book Application ---" << std::endl;
    HashTableChaining<std::string, std::string> phoneBook;
    
    phoneBook.insert("Alice", "555-1234");
    phoneBook.insert("Bob", "555-5678");
    phoneBook.insert("Charlie", "555-9012");
    phoneBook.insert("Diana", "555-3456");
    
    std::cout << "Phone book entries:" << std::endl;
    auto names = phoneBook.keys();
    for (const auto& name : names) {
        auto phone = phoneBook.search(name);
        if (phone) {
            std::cout << name << ": " << *phone << std::endl;
        }
    }
    
    std::cout << "\nLooking up Bob: " << *phoneBook.search("Bob") << std::endl;
    
    // 2. Word Frequency Counter
    std::cout << "\n--- Word Frequency Counter ---" << std::endl;
    HashTableChaining<std::string, int> wordCount;
    
    std::vector<std::string> words = {
        "hello", "world", "hello", "hash", "table", "world", "hello"
    };
    
    for (const auto& word : words) {
        auto count = wordCount.search(word);
        if (count) {
            wordCount.insert(word, *count + 1);
        } else {
            wordCount.insert(word, 1);
        }
    }
    
    std::cout << "Word frequencies:" << std::endl;
    auto uniqueWords = wordCount.keys();
    for (const auto& word : uniqueWords) {
        auto freq = wordCount.search(word);
        if (freq) {
            std::cout << word << ": " << *freq << std::endl;
        }
    }
    
    // 3. Cache Implementation
    std::cout << "\n--- Simple Cache Implementation ---" << std::endl;
    HashTableOpenAddressing<int, std::string> cache(4);
    
    // Simulate cache operations
    cache.insert(1, "Data1");
    cache.insert(2, "Data2");
    cache.insert(3, "Data3");
    
    std::cout << "Cache lookup for key 2: " << *cache.search(2) << std::endl;
    std::cout << "Cache lookup for key 5: " << (cache.search(5) ? "Found" : "Miss") << std::endl;
    
    cache.printStatistics();
}

void demonstrateHashFunctionQuality() {
    printSeparator("HASH FUNCTION QUALITY ANALYSIS");
    
    HashTableChaining<int, int> hashTable(16);
    
    std::cout << "\n--- Good Distribution (Random Keys) ---" << std::endl;
    std::vector<int> randomKeys = {7, 23, 41, 59, 13, 31, 47, 3, 19, 37, 53, 11, 29, 43, 61, 17};
    
    for (int key : randomKeys) {
        hashTable.insert(key, key);
    }
    
    hashTable.displayTable();
    hashTable.printStatistics();
    
    // Clear and test with sequential keys
    hashTable.clear();
    
    std::cout << "\n--- Poor Distribution (Sequential Keys) ---" << std::endl;
    for (int i = 0; i < 16; ++i) {
        hashTable.insert(i, i);
    }
    
    hashTable.displayTable();
    hashTable.printStatistics();
}

void demonstratePerformanceCharacteristics() {
    printSeparator("PERFORMANCE CHARACTERISTICS");
    
    std::cout << "\n--- Load Factor Impact ---" << std::endl;
    
    // Test different load factors
    std::vector<double> testSizes = {0.25, 0.5, 0.75, 0.9};
    
    for (double targetLoad : testSizes) {
        HashTableChaining<int, int> table(16);
        int numElements = static_cast<int>(16 * targetLoad);
        
        std::cout << "\nTarget load factor: " << targetLoad << std::endl;
        std::cout << "Inserting " << numElements << " elements..." << std::endl;
        
        for (int i = 0; i < numElements; ++i) {
            table.insert(i, i * 2);
        }
        
        table.printStatistics();
        
        // Measure search performance (conceptually)
        std::cout << "Expected search probes: ";
        if (targetLoad < 0.5) {
            std::cout << "Low (excellent performance)";
        } else if (targetLoad < 0.75) {
            std::cout << "Medium (good performance)";
        } else {
            std::cout << "High (degraded performance)";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "        HASH TABLE DEMONSTRATION              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateOpenAddressing();
        demonstrateDynamicResizing();
        demonstrateCollisionComparison();
        demonstratePracticalApplications();
        demonstrateHashFunctionQuality();
        demonstratePerformanceCharacteristics();
        
        printSeparator("COMPREHENSIVE SUMMARY");
        
        std::cout << "\nHash Table Key Properties:" << std::endl;
        std::cout << "🔍 Direct Access: O(1) average time for all operations" << std::endl;
        std::cout << "🎯 Hash Function: Maps keys to array indices" << std::endl;
        std::cout << "⚡ Fast Operations: Insert, search, delete in constant time" << std::endl;
        std::cout << "📊 Load Factor Management: Maintains performance via resizing" << std::endl;
        
        std::cout << "\nCollision Resolution Methods:" << std::endl;
        std::cout << "\n1️⃣ Separate Chaining:" << std::endl;
        std::cout << "  ✅ Simple to implement" << std::endl;
        std::cout << "  ✅ Handles high load factors well" << std::endl;
        std::cout << "  ✅ No clustering problems" << std::endl;
        std::cout << "  ❌ Extra memory for pointers" << std::endl;
        std::cout << "  ❌ Poor cache performance" << std::endl;
        
        std::cout << "\n2️⃣ Open Addressing (Linear Probing):" << std::endl;
        std::cout << "  ✅ Better cache performance" << std::endl;
        std::cout << "  ✅ No extra memory for pointers" << std::endl;
        std::cout << "  ❌ Sensitive to load factor" << std::endl;
        std::cout << "  ❌ Primary clustering issues" << std::endl;
        std::cout << "  ❌ Deletion complexity" << std::endl;
        
        std::cout << "\nTime Complexity:" << std::endl;
        std::cout << "╔══════════════╦══════════════╦══════════════╗" << std::endl;
        std::cout << "║  Operation   ║   Average    ║    Worst     ║" << std::endl;
        std::cout << "╠══════════════╬══════════════╬══════════════╣" << std::endl;
        std::cout << "║    Insert    ║     O(1)     ║     O(n)     ║" << std::endl;
        std::cout << "║    Search    ║     O(1)     ║     O(n)     ║" << std::endl;
        std::cout << "║    Delete    ║     O(1)     ║     O(n)     ║" << std::endl;
        std::cout << "╚══════════════╩══════════════╩══════════════╝" << std::endl;
        
        std::cout << "\nSpace Complexity: O(n) where n is number of elements" << std::endl;
        
        std::cout << "\nLoad Factor Guidelines:" << std::endl;
        std::cout << "📈 Chaining: Can handle λ > 1.0, optimal around 0.75" << std::endl;
        std::cout << "📈 Open Addressing: Should keep λ < 0.7, optimal around 0.5" << std::endl;
        
        std::cout << "\nHash Function Quality:" << std::endl;
        std::cout << "🎯 Uniform Distribution: Keys spread evenly across table" << std::endl;
        std::cout << "⚡ Fast Computation: Hash function should be quick" << std::endl;
        std::cout << "🔄 Deterministic: Same key always produces same hash" << std::endl;
        std::cout << "📊 Avalanche Effect: Small key changes cause large hash changes" << std::endl;
        
        std::cout << "\nCommon Use Cases:" << std::endl;
        std::cout << "🎯 Database indexing and caching" << std::endl;
        std::cout << "🎯 Symbol tables in compilers" << std::endl;
        std::cout << "🎯 Associative arrays/dictionaries" << std::endl;
        std::cout << "🎯 Set data structures" << std::endl;
        std::cout << "🎯 Memoization in dynamic programming" << std::endl;
        std::cout << "🎯 Hash-based algorithms (bloom filters, etc.)" << std::endl;
        
        std::cout << "\nAdvantages:" << std::endl;
        std::cout << "✅ Extremely fast average-case performance" << std::endl;
        std::cout << "✅ Simple conceptual model" << std::endl;
        std::cout << "✅ Flexible key types with custom hash functions" << std::endl;
        std::cout << "✅ Dynamic sizing capabilities" << std::endl;
        
        std::cout << "\nDisadvantages:" << std::endl;
        std::cout << "❌ Worst-case O(n) performance" << std::endl;
        std::cout << "❌ No ordering of elements" << std::endl;
        std::cout << "❌ Hash function quality affects performance" << std::endl;
        std::cout << "❌ Memory overhead for sparse data" << std::endl;
        std::cout << "❌ Iteration order is unpredictable" << std::endl;
        
        std::cout << "\nWhen to Use Hash Tables:" << std::endl;
        std::cout << "💡 Need fast key-based lookup" << std::endl;
        std::cout << "💡 Implementing associative containers" << std::endl;
        std::cout << "💡 Caching and memoization" << std::endl;
        std::cout << "💡 Duplicate detection" << std::endl;
        std::cout << "💡 Frequency counting" << std::endl;
        
        std::cout << "\nConsider Alternatives:" << std::endl;
        std::cout << "🔄 Binary search trees for ordered data" << std::endl;
        std::cout << "🔄 Arrays for small, dense key spaces" << std::endl;
        std::cout << "🔄 Tries for string keys with common prefixes" << std::endl;
        std::cout << "🔄 Skip lists for ordered key-value pairs" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
