/**
 * @file mutable_demo.cpp
 * @brief Demonstration of 'mutable' storage class
 * 
 * Compile: g++ -std=c++17 -Wall -Wextra mutable_demo.cpp -o mutable_demo
 * Run: ./mutable_demo
 */

#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include <chrono>
#include <memory>

// Basic class demonstrating mutable
class Counter {
private:
    mutable int count_;           // Can be modified in const methods
    mutable int access_count_;    // Tracks how many times accessed
    std::string name_;
    
public:
    Counter(const std::string& name) : count_(0), access_count_(0), name_(name) {}
    
    // Const method that can modify mutable members
    int getCount() const {
        access_count_++;              // OK - mutable member
        std::cout << "Accessing count (access #" << access_count_ << ")" << std::endl;
        return count_;
    }
    
    // Const method that modifies mutable member
    void incrementCount() const {
        count_++;                     // OK - mutable member
        access_count_++;              // OK - mutable member
        std::cout << "Count incremented to " << count_ << std::endl;
    }
    
    // Regular method
    void setName(const std::string& name) {
        name_ = name;                 // OK - non-const method
    }
    
    const std::string& getName() const {
        access_count_++;              // OK - mutable member
        return name_;
    }
    
    int getAccessCount() const {
        return access_count_;
    }
};

// Cache example with mutable
class ExpensiveCalculator {
private:
    mutable bool cache_valid_;
    mutable double cached_result_;
    double input_;
    
    double expensiveCalculation() const {
        std::cout << "Performing expensive calculation..." << std::endl;
        // Simulate expensive operation
        double result = 0.0;
        for (int i = 0; i < 1000; ++i) {
            result += input_ * i * 0.001;
        }
        return result;
    }
    
public:
    ExpensiveCalculator(double input) : cache_valid_(false), cached_result_(0.0), input_(input) {}
    
    // Const method with mutable caching
    double getResult() const {
        if (!cache_valid_) {
            cached_result_ = expensiveCalculation();
            cache_valid_ = true;         // Modify mutable member in const method
            std::cout << "Result cached" << std::endl;
        } else {
            std::cout << "Using cached result" << std::endl;
        }
        return cached_result_;
    }
    
    void setInput(double input) {
        input_ = input;
        cache_valid_ = false;            // Invalidate cache
    }
};

// Thread-safe class with mutable mutex
class ThreadSafeCounter {
private:
    mutable std::mutex mutex_;       // Mutable mutex for const methods
    int count_;
    
public:
    ThreadSafeCounter(int initial = 0) : count_(initial) {}
    
    // Const method that needs to lock (modify mutable mutex)
    int getCount() const {
        std::lock_guard<std::mutex> lock(mutex_);  // OK - mutable mutex
        return count_;
    }
    
    void increment() {
        std::lock_guard<std::mutex> lock(mutex_);
        count_++;
    }
    
    void decrement() {
        std::lock_guard<std::mutex> lock(mutex_);
        count_--;
    }
    
    // Const method that modifies internal state for debugging
    void debugPrint() const {
        std::lock_guard<std::mutex> lock(mutex_);  // OK - mutable mutex
        std::cout << "Debug: Current count is " << count_ << std::endl;
    }
};

// Statistics tracking with mutable
class DataProcessor {
private:
    std::vector<int> data_;
    mutable bool stats_valid_;
    mutable double mean_;
    mutable double max_;
    mutable double min_;
    mutable int access_count_;
    
    void calculateStats() const {
        if (data_.empty()) return;
        
        access_count_++;
        std::cout << "Calculating statistics (calculation #" << access_count_ << ")..." << std::endl;
        
        double sum = 0;
        max_ = data_[0];
        min_ = data_[0];
        
        for (int value : data_) {
            sum += value;
            if (value > max_) max_ = value;
            if (value < min_) min_ = value;
        }
        
        mean_ = sum / data_.size();
        stats_valid_ = true;
    }
    
public:
    DataProcessor() : stats_valid_(false), mean_(0), max_(0), min_(0), access_count_(0) {}
    
    void addData(int value) {
        data_.push_back(value);
        stats_valid_ = false;  // Invalidate cached statistics
    }
    
    // Const methods with lazy evaluation using mutable
    double getMean() const {
        if (!stats_valid_) calculateStats();
        return mean_;
    }
    
    double getMax() const {
        if (!stats_valid_) calculateStats();
        return max_;
    }
    
    double getMin() const {
        if (!stats_valid_) calculateStats();
        return min_;
    }
    
    size_t getDataSize() const {
        return data_.size();
    }
};

// Lazy initialization with mutable
class LazyResource {
private:
    mutable std::unique_ptr<std::vector<int>> resource_;
    mutable bool initialized_;
    
    void initializeResource() const {
        std::cout << "Lazy initialization of resource..." << std::endl;
        resource_ = std::make_unique<std::vector<int>>();
        for (int i = 0; i < 10; ++i) {
            resource_->push_back(i * i);
        }
        initialized_ = true;
    }
    
public:
    LazyResource() : initialized_(false) {}
    
    // Const method with lazy initialization
    const std::vector<int>& getResource() const {
        if (!initialized_) {
            initializeResource();  // Modifies mutable members
        }
        return *resource_;
    }
    
    bool isInitialized() const {
        return initialized_;
    }
};

// Function demonstrating const correctness
void demonstrateConstCorrectness() {
    std::cout << "\n=== Const Correctness with Mutable ===" << std::endl;
    
    const Counter const_counter("Constant Counter");
    
    // These work because of mutable members
    std::cout << "Count: " << const_counter.getCount() << std::endl;
    const_counter.incrementCount();  // Modifies mutable member
    std::cout << "Count: " << const_counter.getCount() << std::endl;
    
    // const_counter.setName("New Name");  // Error: non-const method on const object
    std::cout << "Name: " << const_counter.getName() << std::endl;
    std::cout << "Access count: " << const_counter.getAccessCount() << std::endl;
}

// Template function demonstrating mutable in generic code
template<typename T>
void processConstObject(const T& obj) {
    std::cout << "\nProcessing const object..." << std::endl;
    // Can call const methods that modify mutable members
    auto result = obj.getCount();
    std::cout << "Result: " << result << std::endl;
}

int main() {
    std::cout << "=== MUTABLE STORAGE CLASS DEMO ===" << std::endl;
    
    // 1. Basic mutable demonstration
    std::cout << "\n1. Basic Mutable Usage:" << std::endl;
    
    Counter counter("Basic Counter");
    std::cout << "Initial count: " << counter.getCount() << std::endl;
    counter.incrementCount();
    counter.incrementCount();
    std::cout << "Final count: " << counter.getCount() << std::endl;
    std::cout << "Total accesses: " << counter.getAccessCount() << std::endl;
    
    // 2. Const correctness
    demonstrateConstCorrectness();
    
    // 3. Caching with mutable
    std::cout << "\n3. Caching with Mutable:" << std::endl;
    
    ExpensiveCalculator calc(42.0);
    
    std::cout << "First call (will calculate):" << std::endl;
    double result1 = calc.getResult();
    std::cout << "Result: " << result1 << std::endl;
    
    std::cout << "\nSecond call (will use cache):" << std::endl;
    double result2 = calc.getResult();
    std::cout << "Result: " << result2 << std::endl;
    
    std::cout << "\nChanging input (invalidates cache):" << std::endl;
    calc.setInput(100.0);
    double result3 = calc.getResult();
    std::cout << "Result: " << result3 << std::endl;
    
    // 4. Thread safety with mutable mutex
    std::cout << "\n4. Thread Safety with Mutable Mutex:" << std::endl;
    
    ThreadSafeCounter safe_counter(10);
    
    std::cout << "Initial count: " << safe_counter.getCount() << std::endl;
    safe_counter.increment();
    safe_counter.increment();
    safe_counter.debugPrint();  // Const method using mutable mutex
    
    const ThreadSafeCounter& const_ref = safe_counter;
    std::cout << "Count via const reference: " << const_ref.getCount() << std::endl;
    const_ref.debugPrint();     // Const method on const reference
    
    // 5. Statistics with lazy evaluation
    std::cout << "\n5. Statistics with Lazy Evaluation:" << std::endl;
    
    DataProcessor processor;
    processor.addData(10);
    processor.addData(20);
    processor.addData(30);
    processor.addData(5);
    processor.addData(25);
    
    const DataProcessor& const_processor = processor;
    
    std::cout << "Data size: " << const_processor.getDataSize() << std::endl;
    std::cout << "Mean: " << const_processor.getMean() << std::endl;        // Calculates stats
    std::cout << "Max: " << const_processor.getMax() << std::endl;          // Uses cached stats
    std::cout << "Min: " << const_processor.getMin() << std::endl;          // Uses cached stats
    
    // Add more data
    processor.addData(100);
    std::cout << "\nAfter adding data:" << std::endl;
    std::cout << "Mean: " << const_processor.getMean() << std::endl;        // Recalculates stats
    
    // 6. Lazy initialization
    std::cout << "\n6. Lazy Initialization:" << std::endl;
    
    LazyResource lazy;
    std::cout << "Is initialized: " << lazy.isInitialized() << std::endl;
    
    const LazyResource& const_lazy = lazy;
    std::cout << "Getting resource..." << std::endl;
    const auto& resource = const_lazy.getResource();  // Triggers initialization
    
    std::cout << "Resource size: " << resource.size() << std::endl;
    std::cout << "Is initialized: " << const_lazy.isInitialized() << std::endl;
    
    std::cout << "Resource contents: ";
    for (int value : resource) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    // 7. Template usage
    std::cout << "\n7. Template Usage:" << std::endl;
    
    const Counter template_counter("Template Counter");
    processConstObject(template_counter);
    
    // 8. Performance comparison
    std::cout << "\n8. Performance Benefits:" << std::endl;
    
    ExpensiveCalculator perf_calc(1000.0);
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 5; ++i) {
        perf_calc.getResult();  // First call calculates, rest use cache
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "5 calls with caching took " << duration.count() << " microseconds" << std::endl;
    
    // Without caching (simulate by changing input each time)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 5; ++i) {
        perf_calc.setInput(1000.0 + i);  // Invalidates cache each time
        perf_calc.getResult();
    }
    end = std::chrono::high_resolution_clock::now();
    
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "5 calls without caching took " << duration.count() << " microseconds" << std::endl;
    
    std::cout << "\n=== MUTABLE BENEFITS ===" << std::endl;
    std::cout << "✅ Enables logical const-ness (const interface, mutable implementation)" << std::endl;
    std::cout << "✅ Allows caching in const methods for performance" << std::endl;
    std::cout << "✅ Enables thread-safe const methods with mutable mutex" << std::endl;
    std::cout << "✅ Supports lazy initialization in const context" << std::endl;
    std::cout << "✅ Permits internal state tracking (counters, statistics)" << std::endl;
    
    std::cout << "\n=== MUTABLE BEST PRACTICES ===" << std::endl;
    std::cout << "⚠️  Use sparingly - only for implementation details" << std::endl;
    std::cout << "⚠️  Don't break logical const-ness of the object" << std::endl;
    std::cout << "⚠️  Document why mutable is necessary" << std::endl;
    std::cout << "⚠️  Common use cases: caching, statistics, thread safety" << std::endl;
    std::cout << "⚠️  Avoid mutable for core object state" << std::endl;
    
    return 0;
}

/*
Mutable Storage Class Summary:

Purpose:
- Allows modification of class members in const methods
- Enables "logical const-ness" vs "bitwise const-ness"
- Supports implementation details that don't affect object's logical state

Common Use Cases:
1. Caching - Store computed results for performance
2. Statistics/Counters - Track access patterns without changing logical state
3. Thread Safety - Mutable mutex for const methods
4. Lazy Initialization - Initialize resources on first access
5. Debug/Logging - Add debugging info without breaking const interface

Key Concepts:
- Logical Const-ness: Object appears unchanged from user perspective
- Bitwise Const-ness: No bits in object are modified
- mutable allows logical const-ness while breaking bitwise const-ness

Rules:
- Can only be applied to non-static class members
- Allows modification in const methods
- Not applicable to references
- Cannot be applied to const members

Best Practices:
1. Use for implementation details only
2. Don't expose mutable members publicly
3. Document the reason for mutable usage
4. Ensure thread safety if needed
5. Don't break logical const-ness

Anti-patterns:
- Using mutable to bypass const correctness
- Making core object state mutable
- Overusing mutable instead of proper design

Performance Benefits:
- Caching expensive computations
- Avoiding redundant calculations
- Lazy initialization of resources
- Statistics gathering without performance impact

Thread Safety:
- mutable mutex enables thread-safe const methods
- Be careful with race conditions on mutable members
- Consider using atomic types for simple counters
*/
