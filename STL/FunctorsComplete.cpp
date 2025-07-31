// STL Function Objects and Predicates Comprehensive Reference
// Compile: g++ -std=c++20 -o functors_complete functors_complete.cpp
// Run: ./functors_complete

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <random>

void demonstrate_built_in_functors() {
    std::cout << "\n=== BUILT-IN FUNCTION OBJECTS ===" << std::endl;
    
    // 1. Arithmetic Function Objects
    {
        std::cout << "\n1. Arithmetic Function Objects:" << std::endl;
        
        std::vector<int> nums1 = {10, 20, 30, 40, 50};
        std::vector<int> nums2 = {1, 2, 3, 4, 5};
        std::vector<int> result(nums1.size());
        
        // std::plus
        std::transform(nums1.begin(), nums1.end(), nums2.begin(), 
                      result.begin(), std::plus<int>());
        std::cout << "Addition: ";
        for (int val : result) std::cout << val << " ";
        std::cout << std::endl;
        
        // std::multiplies
        std::transform(nums1.begin(), nums1.end(), nums2.begin(),
                      result.begin(), std::multiplies<int>());
        std::cout << "Multiplication: ";
        for (int val : result) std::cout << val << " ";
        std::cout << std::endl;
        
        // std::minus
        std::transform(nums1.begin(), nums1.end(), nums2.begin(),
                      result.begin(), std::minus<int>());
        std::cout << "Subtraction: ";
        for (int val : result) std::cout << val << " ";
        std::cout << std::endl;
        
        // Using with single argument (bind or lambda alternative)
        std::vector<int> doubled(nums1.size());
        std::transform(nums1.begin(), nums1.end(), doubled.begin(),
                      std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
        std::cout << "Doubled: ";
        for (int val : doubled) std::cout << val << " ";
        std::cout << std::endl;
    }
    
    // 2. Comparison Function Objects
    {
        std::cout << "\n2. Comparison Function Objects:" << std::endl;
        
        std::vector<int> data = {5, 2, 8, 1, 9, 3, 7};
        
        // std::greater - for descending sort
        std::vector<int> desc_sorted = data;
        std::sort(desc_sorted.begin(), desc_sorted.end(), std::greater<int>());
        std::cout << "Descending sort: ";
        for (int val : desc_sorted) std::cout << val << " ";
        std::cout << std::endl;
        
        // std::less (default for sorting)
        std::vector<int> asc_sorted = data;
        std::sort(asc_sorted.begin(), asc_sorted.end(), std::less<int>());
        std::cout << "Ascending sort: ";
        for (int val : asc_sorted) std::cout << val << " ";
        std::cout << std::endl;
        
        // Using with containers
        std::set<int, std::greater<int>> desc_set(data.begin(), data.end());
        std::cout << "Set with greater<>: ";
        for (int val : desc_set) std::cout << val << " ";
        std::cout << std::endl;
        
        // Count elements greater than 5
        auto count = std::count_if(data.begin(), data.end(),
                                  std::bind(std::greater<int>(), std::placeholders::_1, 5));
        std::cout << "Numbers > 5: " << count << std::endl;
    }
    
    // 3. Logical Function Objects
    {
        std::cout << "\n3. Logical Function Objects:" << std::endl;
        
        std::vector<bool> bool_vec1 = {true, false, true, false, true};
        std::vector<bool> bool_vec2 = {false, true, true, false, false};
        std::vector<bool> result(bool_vec1.size());
        
        // std::logical_and
        std::transform(bool_vec1.begin(), bool_vec1.end(), bool_vec2.begin(),
                      result.begin(), std::logical_and<bool>());
        std::cout << "Logical AND: ";
        for (bool val : result) std::cout << std::boolalpha << val << " ";
        std::cout << std::endl;
        
        // std::logical_or
        std::transform(bool_vec1.begin(), bool_vec1.end(), bool_vec2.begin(),
                      result.begin(), std::logical_or<bool>());
        std::cout << "Logical OR: ";
        for (bool val : result) std::cout << val << " ";
        std::cout << std::endl;
        
        // std::logical_not (unary)
        std::transform(bool_vec1.begin(), bool_vec1.end(), result.begin(),
                      std::logical_not<bool>());
        std::cout << "Logical NOT: ";
        for (bool val : result) std::cout << val << " ";
        std::cout << std::endl;
    }
    
    // 4. Bitwise Function Objects (C++14)
    {
        std::cout << "\n4. Bitwise Function Objects:" << std::endl;
        
        std::vector<int> nums1 = {12, 15, 8, 3}; // Binary: 1100, 1111, 1000, 0011
        std::vector<int> nums2 = {10, 7, 12, 5}; // Binary: 1010, 0111, 1100, 0101
        std::vector<int> result(nums1.size());
        
        // std::bit_and
        std::transform(nums1.begin(), nums1.end(), nums2.begin(),
                      result.begin(), std::bit_and<int>());
        std::cout << "Bitwise AND: ";
        for (int val : result) std::cout << val << " ";
        std::cout << std::endl;
        
        // std::bit_or
        std::transform(nums1.begin(), nums1.end(), nums2.begin(),
                      result.begin(), std::bit_or<int>());
        std::cout << "Bitwise OR: ";
        for (int val : result) std::cout << val << " ";
        std::cout << std::endl;
        
        // std::bit_xor
        std::transform(nums1.begin(), nums1.end(), nums2.begin(),
                      result.begin(), std::bit_xor<int>());
        std::cout << "Bitwise XOR: ";
        for (int val : result) std::cout << val << " ";
        std::cout << std::endl;
    }
}

void demonstrate_predicates() {
    std::cout << "\n=== PREDICATES ===" << std::endl;
    
    // 1. Unary Predicates
    {
        std::cout << "\n1. Unary Predicates:" << std::endl;
        
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // Lambda as unary predicate
        auto is_even = [](int n) { return n % 2 == 0; };
        auto is_odd = [](int n) { return n % 2 != 0; };
        
        auto even_count = std::count_if(numbers.begin(), numbers.end(), is_even);
        std::cout << "Even numbers: " << even_count << std::endl;
        
        auto first_odd = std::find_if(numbers.begin(), numbers.end(), is_odd);
        std::cout << "First odd number: " << *first_odd << std::endl;
        
        // Using with partition
        std::vector<int> partitioned = numbers;
        auto partition_point = std::partition(partitioned.begin(), partitioned.end(), is_even);
        
        std::cout << "Partitioned (even first): ";
        for (int val : partitioned) std::cout << val << " ";
        std::cout << std::endl;
        std::cout << "Partition point at index: " 
                  << std::distance(partitioned.begin(), partition_point) << std::endl;
    }
    
    // 2. Binary Predicates
    {
        std::cout << "\n2. Binary Predicates:" << std::endl;
        
        std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
        
        // Custom comparator for sorting by length
        auto compare_length = [](const std::string& a, const std::string& b) {
            return a.length() < b.length();
        };
        
        std::vector<std::string> sorted_by_length = words;
        std::sort(sorted_by_length.begin(), sorted_by_length.end(), compare_length);
        
        std::cout << "Sorted by length: ";
        for (const auto& word : sorted_by_length) std::cout << word << " ";
        std::cout << std::endl;
        
        // Using with unique (requires sorted data)
        std::vector<std::string> words_with_dups = {"apple", "apple", "banana", "banana", "cherry"};
        
        auto same_first_char = [](const std::string& a, const std::string& b) {
            return a[0] == b[0];
        };
        
        auto new_end = std::unique(words_with_dups.begin(), words_with_dups.end(), same_first_char);
        words_with_dups.erase(new_end, words_with_dups.end());
        
        std::cout << "After unique by first char: ";
        for (const auto& word : words_with_dups) std::cout << word << " ";
        std::cout << std::endl;
    }
    
    // 3. Predicate Composition
    {
        std::cout << "\n3. Predicate Composition:" << std::endl;
        
        std::vector<int> numbers = {-5, -3, -1, 0, 1, 2, 3, 4, 5, 6, 8, 10, 12};
        
        auto is_positive = [](int n) { return n > 0; };
        auto is_even = [](int n) { return n % 2 == 0; };
        
        // Compose predicates: positive AND even
        auto is_positive_and_even = [=](int n) {
            return is_positive(n) && is_even(n);
        };
        
        auto count = std::count_if(numbers.begin(), numbers.end(), is_positive_and_even);
        std::cout << "Positive and even numbers: " << count << std::endl;
        
        // Using std::all_of, std::any_of, std::none_of
        std::vector<int> positive_nums = {2, 4, 6, 8, 10};
        
        bool all_positive = std::all_of(positive_nums.begin(), positive_nums.end(), is_positive);
        bool any_even = std::any_of(positive_nums.begin(), positive_nums.end(), is_even);
        bool none_negative = std::none_of(positive_nums.begin(), positive_nums.end(), 
                                         [](int n) { return n < 0; });
        
        std::cout << "All positive: " << std::boolalpha << all_positive << std::endl;
        std::cout << "Any even: " << any_even << std::endl;
        std::cout << "None negative: " << none_negative << std::endl;
    }
}

void demonstrate_custom_functors() {
    std::cout << "\n=== CUSTOM FUNCTION OBJECTS ===" << std::endl;
    
    // 1. Simple Function Object
    {
        std::cout << "\n1. Simple Function Object:" << std::endl;
        
        struct Square {
            int operator()(int x) const {
                return x * x;
            }
        };
        
        Square square_func;
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        std::vector<int> squares(numbers.size());
        
        std::transform(numbers.begin(), numbers.end(), squares.begin(), square_func);
        
        std::cout << "Numbers: ";
        for (int n : numbers) std::cout << n << " ";
        std::cout << std::endl;
        
        std::cout << "Squares: ";
        for (int s : squares) std::cout << s << " ";
        std::cout << std::endl;
    }
    
    // 2. Stateful Function Object
    {
        std::cout << "\n2. Stateful Function Object:" << std::endl;
        
        class Accumulator {
        private:
            int sum_;
            
        public:
            Accumulator() : sum_(0) {}
            
            int operator()(int value) {
                sum_ += value;
                return sum_;
            }
            
            int get_sum() const { return sum_; }
        };
        
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        std::vector<int> running_sums(numbers.size());
        
        std::transform(numbers.begin(), numbers.end(), running_sums.begin(), Accumulator());
        
        std::cout << "Running sums: ";
        for (int sum : running_sums) std::cout << sum << " ";
        std::cout << std::endl;
        
        // Get final state
        Accumulator acc;
        std::for_each(numbers.begin(), numbers.end(), std::ref(acc));
        std::cout << "Final accumulator sum: " << acc.get_sum() << std::endl;
    }
    
    // 3. Generic Function Object
    {
        std::cout << "\n3. Generic Function Object:" << std::endl;
        
        template<typename T>
        struct MultiplyBy {
            T factor;
            
            explicit MultiplyBy(T f) : factor(f) {}
            
            T operator()(const T& value) const {
                return value * factor;
            }
        };
        
        std::vector<int> ints = {1, 2, 3, 4, 5};
        std::vector<double> doubles = {1.1, 2.2, 3.3, 4.4, 5.5};
        
        std::vector<int> int_results(ints.size());
        std::vector<double> double_results(doubles.size());
        
        std::transform(ints.begin(), ints.end(), int_results.begin(), MultiplyBy<int>(3));
        std::transform(doubles.begin(), doubles.end(), double_results.begin(), MultiplyBy<double>(2.5));
        
        std::cout << "Integers * 3: ";
        for (int val : int_results) std::cout << val << " ";
        std::cout << std::endl;
        
        std::cout << "Doubles * 2.5: ";
        for (double val : double_results) std::cout << val << " ";
        std::cout << std::endl;
    }
    
    // 4. Function Object for Custom Comparison
    {
        std::cout << "\n4. Custom Comparison Function Object:" << std::endl;
        
        struct Person {
            std::string name;
            int age;
            
            Person(const std::string& n, int a) : name(n), age(a) {}
        };
        
        struct CompareByAge {
            bool operator()(const Person& a, const Person& b) const {
                return a.age < b.age;
            }
        };
        
        struct CompareByName {
            bool operator()(const Person& a, const Person& b) const {
                return a.name < b.name;
            }
        };
        
        std::vector<Person> people = {
            {"Alice", 30},
            {"Bob", 25},
            {"Charlie", 35},
            {"Diana", 28}
        };
        
        // Sort by age
        std::vector<Person> by_age = people;
        std::sort(by_age.begin(), by_age.end(), CompareByAge());
        
        std::cout << "Sorted by age: ";
        for (const auto& p : by_age) {
            std::cout << p.name << "(" << p.age << ") ";
        }
        std::cout << std::endl;
        
        // Sort by name
        std::vector<Person> by_name = people;
        std::sort(by_name.begin(), by_name.end(), CompareByName());
        
        std::cout << "Sorted by name: ";
        for (const auto& p : by_name) {
            std::cout << p.name << "(" << p.age << ") ";
        }
        std::cout << std::endl;
        
        // Using with containers
        std::set<Person, CompareByAge> people_by_age(people.begin(), people.end());
        std::cout << "Set ordered by age: ";
        for (const auto& p : people_by_age) {
            std::cout << p.name << "(" << p.age << ") ";
        }
        std::cout << std::endl;
    }
}

void demonstrate_bind_and_function() {
    std::cout << "\n=== BIND AND FUNCTION ===" << std::endl;
    
    // 1. std::bind
    {
        std::cout << "\n1. std::bind Examples:" << std::endl;
        
        auto multiply = [](int a, int b, int c) { return a * b * c; };
        
        // Bind all arguments
        auto multiply_2_3_4 = std::bind(multiply, 2, 3, 4);
        std::cout << "2 * 3 * 4 = " << multiply_2_3_4() << std::endl;
        
        // Bind some arguments, use placeholders for others
        auto multiply_by_6 = std::bind(multiply, std::placeholders::_1, 2, 3);
        std::cout << "5 * 2 * 3 = " << multiply_by_6(5) << std::endl;
        
        // Reorder arguments
        auto multiply_reordered = std::bind(multiply, std::placeholders::_3, 
                                           std::placeholders::_1, std::placeholders::_2);
        std::cout << "multiply(3, 1, 2) as (2, 3, 1) = " << multiply_reordered(1, 2, 3) << std::endl;
        
        // Use with STL algorithms
        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // Count numbers greater than 5
        auto greater_than_5 = std::bind(std::greater<int>(), std::placeholders::_1, 5);
        auto count = std::count_if(numbers.begin(), numbers.end(), greater_than_5);
        std::cout << "Numbers > 5: " << count << std::endl;
        
        // Transform with bound function
        std::vector<int> doubled(numbers.size());
        auto double_it = std::bind(std::multiplies<int>(), std::placeholders::_1, 2);
        std::transform(numbers.begin(), numbers.end(), doubled.begin(), double_it);
        
        std::cout << "Doubled: ";
        for (int val : doubled) std::cout << val << " ";
        std::cout << std::endl;
    }
    
    // 2. std::function
    {
        std::cout << "\n2. std::function Examples:" << std::endl;
        
        // Function wrapper for different callable types
        std::function<int(int)> func;
        
        // Regular function
        auto square = [](int x) { return x * x; };
        func = square;
        std::cout << "Lambda square(4) = " << func(4) << std::endl;
        
        // Function object
        struct Cube {
            int operator()(int x) const { return x * x * x; }
        };
        
        func = Cube();
        std::cout << "Function object cube(3) = " << func(3) << std::endl;
        
        // Bound function
        auto multiply = [](int a, int b) { return a * b; };
        func = std::bind(multiply, std::placeholders::_1, 5);
        std::cout << "Bound function multiply by 5(6) = " << func(6) << std::endl;
        
        // Using function as parameter
        auto apply_operation = [](const std::vector<int>& vec, std::function<int(int)> op) {
            std::vector<int> result;
            std::transform(vec.begin(), vec.end(), std::back_inserter(result), op);
            return result;
        };
        
        std::vector<int> nums = {1, 2, 3, 4, 5};
        auto squares = apply_operation(nums, [](int x) { return x * x; });
        
        std::cout << "Applied square operation: ";
        for (int val : squares) std::cout << val << " ";
        std::cout << std::endl;
    }
    
    // 3. Member Function Binding
    {
        std::cout << "\n3. Member Function Binding:" << std::endl;
        
        class Calculator {
        public:
            int add(int a, int b) const { return a + b; }
            int multiply(int a, int b) const { return a * b; }
            void set_base(int base) { base_ = base; }
            int add_to_base(int value) const { return base_ + value; }
            
        private:
            int base_ = 0;
        };
        
        Calculator calc;
        calc.set_base(10);
        
        // Bind member function with specific object
        auto add_func = std::bind(&Calculator::add, &calc, std::placeholders::_1, std::placeholders::_2);
        std::cout << "Bound add(3, 7) = " << add_func(3, 7) << std::endl;
        
        // Bind member function with object placeholder
        auto multiply_func = std::bind(&Calculator::multiply, std::placeholders::_1,
                                      std::placeholders::_2, std::placeholders::_3);
        std::cout << "Bound multiply with object placeholder: " << multiply_func(&calc, 4, 5) << std::endl;
        
        // Bind member function with partial arguments
        auto add_to_base_func = std::bind(&Calculator::add_to_base, &calc, std::placeholders::_1);
        std::cout << "Add 25 to base(10): " << add_to_base_func(25) << std::endl;
        
        // Using with std::function
        std::function<int(int, int)> operation = std::bind(&Calculator::add, &calc,
                                                          std::placeholders::_1, std::placeholders::_2);
        std::cout << "Function wrapper for member function: " << operation(8, 12) << std::endl;
    }
}

void demonstrate_hash_functors() {
    std::cout << "\n=== HASH FUNCTION OBJECTS ===" << std::endl;
    
    // 1. Built-in Hash Functions
    {
        std::cout << "\n1. Built-in Hash Functions:" << std::endl;
        
        std::hash<int> int_hasher;
        std::hash<std::string> string_hasher;
        std::hash<double> double_hasher;
        
        int num = 42;
        std::string str = "Hello";
        double d = 3.14159;
        
        std::cout << "Hash of " << num << ": " << int_hasher(num) << std::endl;
        std::cout << "Hash of '" << str << "': " << string_hasher(str) << std::endl;
        std::cout << "Hash of " << d << ": " << double_hasher(d) << std::endl;
        
        // Using with unordered containers
        std::unordered_map<std::string, int> word_count;
        word_count["hello"] = 1;
        word_count["world"] = 2;
        
        std::cout << "Unordered map uses hash for keys automatically" << std::endl;
    }
    
    // 2. Custom Hash Function
    {
        std::cout << "\n2. Custom Hash Function:" << std::endl;
        
        struct Point {
            int x, y;
            
            Point(int x_val, int y_val) : x(x_val), y(y_val) {}
            
            bool operator==(const Point& other) const {
                return x == other.x && y == other.y;
            }
        };
        
        // Custom hash function object
        struct PointHash {
            std::size_t operator()(const Point& p) const {
                // Combine hashes of x and y
                std::hash<int> int_hash;
                return int_hash(p.x) ^ (int_hash(p.y) << 1);
            }
        };
        
        std::unordered_map<Point, std::string, PointHash> point_names;
        point_names[Point(0, 0)] = "Origin";
        point_names[Point(1, 1)] = "Unit";
        point_names[Point(-1, -1)] = "Negative Unit";
        
        std::cout << "Point hash map:" << std::endl;
        for (const auto& pair : point_names) {
            std::cout << "(" << pair.first.x << ", " << pair.first.y 
                      << ") -> " << pair.second << std::endl;
        }
        
        // Using hash function directly
        PointHash hasher;
        Point p(5, 7);
        std::cout << "Hash of Point(5, 7): " << hasher(p) << std::endl;
    }
    
    // 3. Hash Specialization
    {
        std::cout << "\n3. Hash Specialization:" << std::endl;
        
        struct Person {
            std::string name;
            int age;
            
            Person(const std::string& n, int a) : name(n), age(a) {}
            
            bool operator==(const Person& other) const {
                return name == other.name && age == other.age;
            }
        };
    }
}

void demonstrate_real_world_examples() {
    std::cout << "\n=== REAL-WORLD EXAMPLES ===" << std::endl;
    
    // 1. Custom Priority Queue
    {
        std::cout << "\n1. Custom Priority Queue:" << std::endl;
        
        struct Task {
            std::string name;
            int priority;
            
            Task(const std::string& n, int p) : name(n), priority(p) {}
        };
        
        // Custom comparator for priority queue (min-heap by priority)
        struct TaskComparator {
            bool operator()(const Task& a, const Task& b) const {
                return a.priority > b.priority; // Higher priority value = lower priority
            }
        };
        
        std::priority_queue<Task, std::vector<Task>, TaskComparator> task_queue;
        
        task_queue.push(Task("Low Priority Task", 3));
        task_queue.push(Task("High Priority Task", 1));
        task_queue.push(Task("Medium Priority Task", 2));
        task_queue.push(Task("Critical Task", 0));
        
        std::cout << "Task execution order:" << std::endl;
        while (!task_queue.empty()) {
            const Task& task = task_queue.top();
            std::cout << "- " << task.name << " (priority: " << task.priority << ")" << std::endl;
            task_queue.pop();
        }
    }
    
    // 2. Statistical Operations
    {
        std::cout << "\n2. Statistical Operations with Function Objects:" << std::endl;
        
        std::vector<double> data = {1.5, 2.3, 1.8, 4.2, 3.1, 2.7, 1.9, 3.8, 2.1, 2.9};
        
        // Mean using accumulate
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        double mean = sum / data.size();
        std::cout << "Mean: " << mean << std::endl;
        
        // Variance calculation using custom function object
        struct VarianceCalculator {
            double mean_;
            
            explicit VarianceCalculator(double mean) : mean_(mean) {}
            
            double operator()(double sum, double value) const {
                double diff = value - mean_;
                return sum + diff * diff;
            }
        };
        
        double variance_sum = std::accumulate(data.begin(), data.end(), 0.0, VarianceCalculator(mean));
        double variance = variance_sum / (data.size() - 1);
        std::cout << "Variance: " << variance << std::endl;
        
        // Count outliers (more than 1 standard deviation from mean)
        double std_dev = std::sqrt(variance);
        auto is_outlier = [mean, std_dev](double value) {
            return std::abs(value - mean) > std_dev;
        };
        
        auto outlier_count = std::count_if(data.begin(), data.end(), is_outlier);
        std::cout << "Outliers (> 1 std dev): " << outlier_count << std::endl;
    }
    
    // 3. String Processing Pipeline
    {
        std::cout << "\n3. String Processing Pipeline:" << std::endl;
        
        std::vector<std::string> words = {
            "Hello", "WORLD", "this", "IS", "a", "TEST", "of", "STRING", "processing"
        };
        
        std::cout << "Original: ";
        for (const auto& word : words) std::cout << word << " ";
        std::cout << std::endl;
        
        // Convert to lowercase
        auto to_lower = [](std::string word) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            return word;
        };
        
        std::vector<std::string> processed(words.size());
        std::transform(words.begin(), words.end(), processed.begin(), to_lower);
        
        std::cout << "Lowercase: ";
        for (const auto& word : processed) std::cout << word << " ";
        std::cout << std::endl;
        
        // Filter words longer than 3 characters
        auto is_long_enough = [](const std::string& word) { return word.length() > 3; };
        
        std::vector<std::string> filtered;
        std::copy_if(processed.begin(), processed.end(), std::back_inserter(filtered), is_long_enough);
        
        std::cout << "Filtered (>3 chars): ";
        for (const auto& word : filtered) std::cout << word << " ";
        std::cout << std::endl;
        
        // Sort by length using custom comparator
        auto compare_length = [](const std::string& a, const std::string& b) {
            if (a.length() != b.length()) {
                return a.length() < b.length();
            }
            return a < b; // Alphabetical for same length
        };
        
        std::sort(filtered.begin(), filtered.end(), compare_length);
        
        std::cout << "Sorted by length: ";
        for (const auto& word : filtered) std::cout << word << " ";
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "=== COMPLETE STL FUNCTION OBJECTS & PREDICATES REFERENCE ===" << std::endl;
    
    demonstrate_built_in_functors();
    demonstrate_predicates();
    demonstrate_custom_functors();
    demonstrate_bind_and_function();
    demonstrate_hash_functors();
    demonstrate_real_world_examples();
    
    std::cout << "\n=== FUNCTION OBJECTS SUMMARY ===" << std::endl;
    std::cout << "🔹 **Built-in Function Objects:**" << std::endl;
    std::cout << "   • Arithmetic: plus, minus, multiplies, divides, modulus, negate" << std::endl;
    std::cout << "   • Comparison: equal_to, not_equal_to, greater, less, greater_equal, less_equal" << std::endl;
    std::cout << "   • Logical: logical_and, logical_or, logical_not" << std::endl;
    std::cout << "   • Bitwise: bit_and, bit_or, bit_xor" << std::endl;
    
    std::cout << "\n🔹 **Predicates:**" << std::endl;
    std::cout << "   • Unary: takes one argument, returns bool" << std::endl;
    std::cout << "   • Binary: takes two arguments, returns bool" << std::endl;
    std::cout << "   • Used with: find_if, count_if, remove_if, partition, etc." << std::endl;
    
    std::cout << "\n🔹 **Advanced Features:**" << std::endl;
    std::cout << "   • std::bind: bind arguments to create new functions" << std::endl;
    std::cout << "   • std::function: type-erased wrapper for any callable" << std::endl;
    std::cout << "   • Custom hash functions for unordered containers" << std::endl;
    std::cout << "   • Member function binding with std::mem_fn" << std::endl;
    
    std::cout << "\n🔹 **Best Practices:**" << std::endl;
    std::cout << "   • Prefer lambdas for simple predicates" << std::endl;
    std::cout << "   • Use function objects for stateful operations" << std::endl;
    std::cout << "   • Make function objects const when possible" << std::endl;
    std::cout << "   • Consider std::function for type erasure" << std::endl;
    std::cout << "   • Use transparent operators (auto template params)" << std::endl;
    
    return 0;
}

/*
FUNCTION OBJECTS PERFORMANCE NOTES:

Function Object Types:
1. Function Pointers:
   - Overhead: Call through pointer (may prevent inlining)
   - Use case: When function is determined at runtime

2. Function Objects (Functors):
   - Overhead: Minimal (can be inlined)
   - Use case: When state is needed or for better performance

3. Lambdas:
   - Overhead: Minimal (usually inlined)
   - Use case: Local scope, simple operations

4. std::function:
   - Overhead: Type erasure overhead
   - Use case: When you need to store different callable types

Performance Tips:
- Function objects are often faster than function pointers
- Lambdas without captures are often converted to function pointers
- Lambdas with captures create function objects
- std::bind creates function objects but may be slower than lambdas
- Template functions with function object parameters can inline better

Memory Considerations:
- Function objects can store state (member variables)
- std::function has memory overhead for type erasure
- Lambdas capture by value/reference affect memory usage
- Large captured objects should use reference capture when safe

STL Algorithm Integration:
- Most STL algorithms accept function objects as template parameters
- This allows for compile-time optimization and inlining
- Custom predicates enable powerful data filtering and transformation
- Function composition creates reusable, testable code components
*/
