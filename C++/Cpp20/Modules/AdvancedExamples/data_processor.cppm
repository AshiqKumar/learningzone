// Advanced C++20 Module Example - Generic Data Processing Module
// Demonstrates advanced module features: partitions, concepts, and complex templates

export module data_processor;

// Import what we need
import <vector>;
import <algorithm>;
import <numeric>;
import <concepts>;
import <type_traits>;
import <iostream>;
import <string>;
import <functional>;

// C++20 Concepts for type safety
export template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

export template<typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
};

export template<typename T>
concept Printable = requires(T t) {
    std::cout << t;
};

// Module partition declaration (advanced feature)
export module data_processor:statistics;
export module data_processor:algorithms;

// Main data processor class with advanced templates
export template<Numeric T>
class DataProcessor {
private:
    std::vector<T> data_;
    std::string name_;
    
    // Private template helper - not exported
    template<typename Predicate>
    std::vector<T> filter_internal(Predicate pred) const;
    
public:
    explicit DataProcessor(std::string name) : name_(std::move(name)) {}
    
    // Constructor with initializer list
    DataProcessor(std::string name, std::initializer_list<T> init_data) 
        : name_(std::move(name)), data_(init_data) {}
    
    // Template constructor for any container
    template<typename Container>
    requires std::convertible_to<typename Container::value_type, T>
    DataProcessor(std::string name, const Container& container)
        : name_(std::move(name)), data_(container.begin(), container.end()) {}
    
    // Data manipulation
    void add(T value) { data_.push_back(value); }
    void add_range(std::initializer_list<T> values);
    
    template<typename Iterator>
    void add_range(Iterator first, Iterator last);
    
    void clear() { data_.clear(); }
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    
    // Statistical operations using concepts
    template<Numeric U = T>
    U sum() const requires std::convertible_to<T, U>;
    
    template<Numeric U = T>
    double mean() const requires std::convertible_to<T, U>;
    
    template<Comparable U = T>
    U min_value() const requires std::convertible_to<T, U>;
    
    template<Comparable U = T>
    U max_value() const requires std::convertible_to<T, U>;
    
    // Advanced filtering with lambda support
    template<typename Predicate>
    std::vector<T> filter(Predicate pred) const;
    
    // Transform operation
    template<typename UnaryOp>
    auto transform(UnaryOp op) const -> std::vector<decltype(op(T{}))>;
    
    // Fold operation (reduce)
    template<typename BinaryOp>
    T fold(T initial, BinaryOp op) const;
    
    // Partition data
    template<typename Predicate>
    std::pair<std::vector<T>, std::vector<T>> partition(Predicate pred) const;
    
    // Advanced grouping by key
    template<typename KeySelector>
    requires std::invocable<KeySelector, T>
    auto group_by(KeySelector key_func) const 
        -> std::vector<std::pair<decltype(key_func(T{})), std::vector<T>>>;
    
    // Chain operations (fluent interface)
    DataProcessor& sort();
    DataProcessor& reverse();
    DataProcessor& unique();
    
    // Utility
    const std::string& name() const { return name_; }
    std::vector<T> to_vector() const { return data_; }
    
    // Print with concept constraint
    void print() const requires Printable<T>;
    
    // Iterator support
    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }
    auto begin() const { return data_.cbegin(); }
    auto end() const { return data_.cend(); }
};

// Specialized processors for common types
export using IntProcessor = DataProcessor<int>;
export using DoubleProcessor = DataProcessor<double>;
export using FloatProcessor = DataProcessor<float>;

// Factory functions with perfect forwarding
export template<Numeric T, typename... Args>
auto make_processor(Args&&... args) -> DataProcessor<T> {
    return DataProcessor<T>(std::forward<Args>(args)...);
}

// Utility functions for data generation
export template<Numeric T>
std::vector<T> generate_sequence(T start, T end, T step = T{1});

export template<Numeric T>
std::vector<T> generate_random(size_t count, T min_val, T max_val);

// Advanced algorithm exports
export template<Numeric T>
bool is_sorted(const std::vector<T>& data);

export template<Numeric T>
std::vector<T> merge_sorted(const std::vector<T>& vec1, const std::vector<T>& vec2);

export template<typename T, typename Predicate>
size_t count_if_advanced(const std::vector<T>& data, Predicate pred);

// Template implementations (hidden from users but available)

template<Numeric T>
template<typename Predicate>
std::vector<T> DataProcessor<T>::filter_internal(Predicate pred) const {
    std::vector<T> result;
    std::copy_if(data_.begin(), data_.end(), std::back_inserter(result), pred);
    return result;
}

template<Numeric T>
void DataProcessor<T>::add_range(std::initializer_list<T> values) {
    data_.insert(data_.end(), values.begin(), values.end());
}

template<Numeric T>
template<typename Iterator>
void DataProcessor<T>::add_range(Iterator first, Iterator last) {
    data_.insert(data_.end(), first, last);
}

template<Numeric T>
template<Numeric U>
U DataProcessor<T>::sum() const requires std::convertible_to<T, U> {
    return std::accumulate(data_.begin(), data_.end(), U{});
}

template<Numeric T>
template<Numeric U>
double DataProcessor<T>::mean() const requires std::convertible_to<T, U> {
    if (data_.empty()) return 0.0;
    return static_cast<double>(sum<U>()) / data_.size();
}

template<Numeric T>
template<Comparable U>
U DataProcessor<T>::min_value() const requires std::convertible_to<T, U> {
    if (data_.empty()) throw std::runtime_error("Cannot find min of empty data");
    return static_cast<U>(*std::min_element(data_.begin(), data_.end()));
}

template<Numeric T>
template<Comparable U>
U DataProcessor<T>::max_value() const requires std::convertible_to<T, U> {
    if (data_.empty()) throw std::runtime_error("Cannot find max of empty data");
    return static_cast<U>(*std::max_element(data_.begin(), data_.end()));
}

template<Numeric T>
template<typename Predicate>
std::vector<T> DataProcessor<T>::filter(Predicate pred) const {
    return filter_internal(pred);
}

template<Numeric T>
template<typename UnaryOp>
auto DataProcessor<T>::transform(UnaryOp op) const -> std::vector<decltype(op(T{}))> {
    std::vector<decltype(op(T{}))> result;
    result.reserve(data_.size());
    std::transform(data_.begin(), data_.end(), std::back_inserter(result), op);
    return result;
}

template<Numeric T>
template<typename BinaryOp>
T DataProcessor<T>::fold(T initial, BinaryOp op) const {
    return std::accumulate(data_.begin(), data_.end(), initial, op);
}

template<Numeric T>
template<typename Predicate>
std::pair<std::vector<T>, std::vector<T>> DataProcessor<T>::partition(Predicate pred) const {
    std::vector<T> true_part, false_part;
    for (const T& item : data_) {
        if (pred(item)) {
            true_part.push_back(item);
        } else {
            false_part.push_back(item);
        }
    }
    return {true_part, false_part};
}

template<Numeric T>
template<typename KeySelector>
requires std::invocable<KeySelector, T>
auto DataProcessor<T>::group_by(KeySelector key_func) const 
    -> std::vector<std::pair<decltype(key_func(T{})), std::vector<T>>> {
    
    using KeyType = decltype(key_func(T{}));
    std::vector<std::pair<KeyType, std::vector<T>>> groups;
    
    for (const T& item : data_) {
        KeyType key = key_func(item);
        
        // Find existing group or create new one
        auto it = std::find_if(groups.begin(), groups.end(),
                              [&key](const auto& group) { return group.first == key; });
        
        if (it != groups.end()) {
            it->second.push_back(item);
        } else {
            groups.emplace_back(key, std::vector<T>{item});
        }
    }
    
    return groups;
}

template<Numeric T>
DataProcessor<T>& DataProcessor<T>::sort() {
    std::sort(data_.begin(), data_.end());
    return *this;
}

template<Numeric T>
DataProcessor<T>& DataProcessor<T>::reverse() {
    std::reverse(data_.begin(), data_.end());
    return *this;
}

template<Numeric T>
DataProcessor<T>& DataProcessor<T>::unique() {
    std::sort(data_.begin(), data_.end());
    data_.erase(std::unique(data_.begin(), data_.end()), data_.end());
    return *this;
}

template<Numeric T>
void DataProcessor<T>::print() const requires Printable<T> {
    std::cout << name_ << " [" << data_.size() << " elements]: ";
    for (size_t i = 0; i < data_.size() && i < 10; ++i) {  // Limit output
        std::cout << data_[i];
        if (i < std::min(data_.size() - 1, static_cast<size_t>(9))) std::cout << ", ";
    }
    if (data_.size() > 10) std::cout << " ... (" << (data_.size() - 10) << " more)";
    std::cout << std::endl;
}

// Free function implementations
template<Numeric T>
std::vector<T> generate_sequence(T start, T end, T step) {
    std::vector<T> result;
    for (T val = start; val <= end; val += step) {
        result.push_back(val);
    }
    return result;
}

template<Numeric T>
bool is_sorted(const std::vector<T>& data) {
    return std::is_sorted(data.begin(), data.end());
}

template<Numeric T>
std::vector<T> merge_sorted(const std::vector<T>& vec1, const std::vector<T>& vec2) {
    std::vector<T> result;
    result.reserve(vec1.size() + vec2.size());
    std::merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::back_inserter(result));
    return result;
}

template<typename T, typename Predicate>
size_t count_if_advanced(const std::vector<T>& data, Predicate pred) {
    return std::count_if(data.begin(), data.end(), pred);
}
