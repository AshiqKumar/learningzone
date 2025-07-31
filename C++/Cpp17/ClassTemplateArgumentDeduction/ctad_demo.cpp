// C++17 Class Template Argument Deduction (CTAD)
// Compile: g++ -std=c++17 -o ctad_demo ctad_demo.cpp
// Run: ./ctad_demo

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <pair>
#include <tuple>
#include <string>
#include <memory>
#include <optional>
#include <array>
#include <deque>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>

// 1. Custom class template for demonstration
template<typename T, typename U = int>
class MyPair {
private:
    T first;
    U second;
    
public:
    MyPair(const T& f, const U& s) : first(f), second(s) {}
    
    const T& get_first() const { return first; }
    const U& get_second() const { return second; }
    
    void print() const {
        std::cout << "MyPair(" << first << ", " << second << ")" << std::endl;
    }
};

// 2. Custom deduction guides
template<typename T>
MyPair(T, T) -> MyPair<T, T>;  // When both types are the same

// 3. More complex template class
template<typename Container>
class Wrapper {
private:
    Container data;
    
public:
    template<typename... Args>
    Wrapper(Args&&... args) : data(std::forward<Args>(args)...) {}
    
    const Container& get() const { return data; }
    
    void print() const {
        std::cout << "Wrapper contains: ";
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Deduction guide for Wrapper
template<typename... Args>
Wrapper(Args&&...) -> Wrapper<std::vector<std::common_type_t<Args...>>>;

// 4. Template class with size parameter
template<typename T, size_t N>
class FixedArray {
private:
    T data[N];
    
public:
    template<typename... Args>
    FixedArray(Args&&... args) {
        static_assert(sizeof...(args) == N, "Wrong number of arguments");
        size_t i = 0;
        ((data[i++] = std::forward<Args>(args)), ...);
    }
    
    const T& operator[](size_t index) const { return data[index]; }
    T& operator[](size_t index) { return data[index]; }
    
    void print() const {
        std::cout << "FixedArray: ";
        for (size_t i = 0; i < N; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

// Deduction guide for FixedArray
template<typename... Args>
FixedArray(Args...) -> FixedArray<std::common_type_t<Args...>, sizeof...(Args)>;

// 5. Complex template with multiple parameters
template<typename Key, typename Value, typename Compare = std::less<Key>>
class SimpleMap {
private:
    std::map<Key, Value, Compare> data;
    
public:
    SimpleMap() = default;
    
    template<typename... Pairs>
    SimpleMap(Pairs&&... pairs) {
        (data.insert(std::forward<Pairs>(pairs)), ...);
    }
    
    void insert(const Key& k, const Value& v) {
        data[k] = v;
    }
    
    void print() const {
        std::cout << "SimpleMap: ";
        for (const auto& [key, value] : data) {
            std::cout << "{" << key << ":" << value << "} ";
        }
        std::cout << std::endl;
    }
};

// Deduction guides for SimpleMap
template<typename... Pairs>
SimpleMap(Pairs...) -> SimpleMap<
    typename std::tuple_element_t<0, std::common_type_t<Pairs...>>,
    typename std::tuple_element_t<1, std::common_type_t<Pairs...>>
>;

int main() {
    std::cout << "=== C++17 CLASS TEMPLATE ARGUMENT DEDUCTION (CTAD) DEMO ===" << std::endl;
    
    // 1. Standard library containers - before and after C++17
    std::cout << "\n1. Standard Library Containers:" << std::endl;
    
    // C++11/14 way - explicit template arguments required
    std::vector<int> vec_old{1, 2, 3, 4, 5};
    std::pair<int, std::string> pair_old{42, "hello"};
    
    // C++17 way - template arguments deduced
    std::vector vec{1, 2, 3, 4, 5};  // Deduced as std::vector<int>
    std::pair pair{42, std::string("hello")};  // Deduced as std::pair<int, std::string>
    
    std::cout << "Old way vector size: " << vec_old.size() << std::endl;
    std::cout << "C++17 vector size: " << vec.size() << std::endl;
    std::cout << "Old way pair: " << pair_old.first << ", " << pair_old.second << std::endl;
    std::cout << "C++17 pair: " << pair.first << ", " << pair.second << std::endl;
    
    // 2. More complex deductions
    std::cout << "\n2. Complex Type Deductions:" << std::endl;
    
    // Deduced from initializer list
    std::vector numbers{1, 2, 3, 4, 5};  // std::vector<int>
    std::vector words{"hello", "world", "C++17"};  // std::vector<const char*>
    std::vector strings{std::string("hello"), std::string("world")};  // std::vector<std::string>
    
    std::cout << "Numbers vector size: " << numbers.size() << std::endl;
    std::cout << "Words vector size: " << words.size() << std::endl;
    std::cout << "Strings vector size: " << strings.size() << std::endl;
    
    // Mixed types - common type deduction
    std::vector mixed{1, 2.5, 3.7f};  // std::vector<double> (common type)
    std::cout << "Mixed vector size: " << mixed.size() << " (type: double)" << std::endl;
    
    // 3. Map and set deductions
    std::cout << "\n3. Associative Container Deductions:" << std::endl;
    
    // Map deduction from pairs
    std::map map1{std::pair{1, "one"}, std::pair{2, "two"}, std::pair{3, "three"}};
    std::cout << "Map1 size: " << map1.size() << std::endl;
    
    // Alternative syntax
    std::map map2{std::make_pair(10, 100.0), std::make_pair(20, 200.0)};
    std::cout << "Map2 size: " << map2.size() << std::endl;
    
    // Set deduction
    std::set set1{5, 3, 8, 1, 9, 2};
    std::cout << "Set size: " << set1.size() << std::endl;
    
    // Unordered containers
    std::unordered_map umap{{1, "first"}, {2, "second"}, {3, "third"}};
    std::unordered_set uset{10, 20, 30, 40, 50};
    std::cout << "Unordered map size: " << umap.size() << std::endl;
    std::cout << "Unordered set size: " << uset.size() << std::endl;
    
    // 4. Tuple deductions
    std::cout << "\n4. Tuple Deductions:" << std::endl;
    
    auto tuple1 = std::make_tuple(42, "hello", 3.14);  // Old way
    std::tuple tuple2{42, "hello", 3.14};  // C++17 CTAD
    
    std::cout << "Tuple1 size: " << std::tuple_size_v<decltype(tuple1)> << std::endl;
    std::cout << "Tuple2 size: " << std::tuple_size_v<decltype(tuple2)> << std::endl;
    
    // Access tuple elements
    auto [t_int, t_str, t_double] = tuple2;
    std::cout << "Tuple2 contents: " << t_int << ", " << t_str << ", " << t_double << std::endl;
    
    // 5. Smart pointer deductions
    std::cout << "\n5. Smart Pointer Deductions:" << std::endl;
    
    // Unfortunately, std::shared_ptr and std::unique_ptr don't have CTAD
    // because they typically require make_shared/make_unique
    auto shared1 = std::make_shared<int>(42);
    auto unique1 = std::make_unique<std::string>("C++17");
    
    std::cout << "Shared ptr value: " << *shared1 << std::endl;
    std::cout << "Unique ptr value: " << *unique1 << std::endl;
    
    // 6. Array deductions
    std::cout << "\n6. Array Deductions:" << std::endl;
    
    std::array arr{1, 2, 3, 4, 5};  // std::array<int, 5>
    std::cout << "Array size: " << arr.size() << std::endl;
    
    // With different types
    std::array mixed_arr{1, 2.0, 3.0f};  // std::array<double, 3>
    std::cout << "Mixed array size: " << mixed_arr.size() << std::endl;
    
    // 7. Custom class deductions
    std::cout << "\n7. Custom Class Deductions:" << std::endl;
    
    // Without CTAD (C++11/14 style)
    MyPair<int, std::string> custom1{42, std::string("answer")};
    
    // With CTAD (C++17 style)
    MyPair custom2{42, std::string("answer")};  // MyPair<int, std::string>
    MyPair custom3{3.14, 2.71};  // Uses deduction guide: MyPair<double, double>
    
    custom1.print();
    custom2.print();
    custom3.print();
    
    // 8. Wrapper class with deduction guide
    std::cout << "\n8. Wrapper Class with Deduction Guide:" << std::endl;
    
    Wrapper wrapper1{1, 2, 3, 4, 5};  // Wrapper<std::vector<int>>
    Wrapper wrapper2{1.1, 2.2, 3.3};  // Wrapper<std::vector<double>>
    
    wrapper1.print();
    wrapper2.print();
    
    // 9. FixedArray with size deduction
    std::cout << "\n9. FixedArray with Size Deduction:" << std::endl;
    
    FixedArray fixed1{10, 20, 30};  // FixedArray<int, 3>
    FixedArray fixed2{1.1, 2.2, 3.3, 4.4, 5.5};  // FixedArray<double, 5>
    
    fixed1.print();
    fixed2.print();
    
    std::cout << "Fixed1 second element: " << fixed1[1] << std::endl;
    std::cout << "Fixed2 third element: " << fixed2[2] << std::endl;
    
    // 10. Container adapters
    std::cout << "\n10. Container Adapters:" << std::endl;
    
    // Stack deduction
    std::stack stack1{std::deque{1, 2, 3, 4, 5}};
    std::cout << "Stack top: " << stack1.top() << std::endl;
    
    // Queue deduction
    std::queue queue1{std::deque{10, 20, 30, 40}};
    std::cout << "Queue front: " << queue1.front() << std::endl;
    
    // Priority queue
    std::priority_queue pq{std::vector{3, 1, 4, 1, 5, 9, 2, 6}};
    std::cout << "Priority queue top: " << pq.top() << std::endl;
    
    // 11. Nested template deductions
    std::cout << "\n11. Nested Template Deductions:" << std::endl;
    
    std::vector<std::pair<int, std::string>> vec_pairs_old{
        {1, "one"}, {2, "two"}, {3, "three"}
    };
    
    std::vector vec_pairs{
        std::pair{1, "one"}, std::pair{2, "two"}, std::pair{3, "three"}
    };  // std::vector<std::pair<int, const char*>>
    
    std::cout << "Old vector of pairs size: " << vec_pairs_old.size() << std::endl;
    std::cout << "CTAD vector of pairs size: " << vec_pairs.size() << std::endl;
    
    // 12. Function return type deduction
    std::cout << "\n12. Function Return Type Integration:" << std::endl;
    
    auto create_vector = []() {
        return std::vector{1, 2, 3, 4, 5};  // Return type deduced
    };
    
    auto create_map = []() {
        return std::map{std::pair{1, "one"}, std::pair{2, "two"}};
    };
    
    auto vec_from_func = create_vector();
    auto map_from_func = create_map();
    
    std::cout << "Vector from function size: " << vec_from_func.size() << std::endl;
    std::cout << "Map from function size: " << map_from_func.size() << std::endl;
    
    // 13. Optional and variant
    std::cout << "\n13. Optional and Variant:" << std::endl;
    
    std::optional opt1{42};  // std::optional<int>
    std::optional opt2{std::string("hello")};  // std::optional<std::string>
    
    if (opt1) std::cout << "Optional1 value: " << *opt1 << std::endl;
    if (opt2) std::cout << "Optional2 value: " << *opt2 << std::endl;
    
    // 14. Performance considerations
    std::cout << "\n14. Performance and Best Practices:" << std::endl;
    
    // CTAD doesn't affect runtime performance - it's compile-time only
    auto start = std::chrono::high_resolution_clock::now();
    
    // Create many containers with CTAD
    for (int i = 0; i < 10000; ++i) {
        std::vector temp{i, i+1, i+2, i+3, i+4};
        (void)temp;  // Suppress unused warning
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Creating 10000 vectors with CTAD took: " << duration.count() << " microseconds" << std::endl;
    
    // 15. Common pitfalls and solutions
    std::cout << "\n15. Common Pitfalls:" << std::endl;
    
    // Pitfall 1: Expecting deduction where it doesn't work
    // std::vector vec_empty{};  // Error: can't deduce from empty braces
    std::vector<int> vec_empty{};  // Must specify type explicitly
    std::cout << "Empty vector size: " << vec_empty.size() << std::endl;
    
    // Pitfall 2: Mixed types can lead to unexpected common type
    std::vector mixed_surprise{1, 2.5};  // std::vector<double>, not std::vector<int>
    std::cout << "Mixed vector first element (as double): " << mixed_surprise[0] << std::endl;
    
    // Pitfall 3: Const char* vs std::string
    std::vector strings_vs_cstr{"hello", "world"};  // std::vector<const char*>
    std::vector explicit_strings{std::string("hello"), std::string("world")};  // std::vector<std::string>
    
    std::cout << "C-string vector size: " << strings_vs_cstr.size() << std::endl;
    std::cout << "String vector size: " << explicit_strings.size() << std::endl;
    
    std::cout << "\n=== CLASS TEMPLATE ARGUMENT DEDUCTION BENEFITS ===" << std::endl;
    std::cout << "✅ Cleaner, more readable code - less typing" << std::endl;
    std::cout << "✅ Consistent with function template argument deduction" << std::endl;
    std::cout << "✅ Reduces verbosity without losing type safety" << std::endl;
    std::cout << "✅ Works with most standard library class templates" << std::endl;
    std::cout << "✅ Custom deduction guides allow fine-tuned behavior" << std::endl;
    std::cout << "✅ No runtime overhead - purely compile-time feature" << std::endl;
    std::cout << "✅ Backward compatible - old explicit syntax still works" << std::endl;
    std::cout << "⚠️  Can lead to unexpected types with mixed type initialization" << std::endl;
    std::cout << "⚠️  Some containers can't deduce from empty initialization" << std::endl;
    std::cout << "⚠️  Requires understanding of common type deduction rules" << std::endl;
    std::cout << "⚠️  Custom classes need deduction guides for optimal experience" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++17 -Wall -Wextra -o ctad_demo ctad_demo.cpp
./ctad_demo

C++17 Class Template Argument Deduction (CTAD) Key Features:
1. Automatic template argument deduction for class templates
2. Works with constructors to infer template parameters
3. Custom deduction guides for fine-tuned behavior
4. Applies to most standard library class templates

Before C++17:
std::vector<int> vec{1, 2, 3};
std::pair<int, std::string> p{42, "hello"};

C++17 with CTAD:
std::vector vec{1, 2, 3};           // Deduced as std::vector<int>
std::pair p{42, std::string("hello")}; // Deduced as std::pair<int, std::string>

Deduction Process:
1. Compiler examines constructor arguments
2. Applies deduction guides if available
3. Falls back to constructor template deduction
4. Uses common type rules for mixed types

Custom Deduction Guides:
template<typename T>
MyClass(T, T) -> MyClass<T, T>;  // Guide for same-type constructor

Supported Containers:
- std::vector, std::deque, std::list
- std::map, std::set, std::unordered_map, std::unordered_set
- std::pair, std::tuple
- std::array (with size deduction)
- std::stack, std::queue, std::priority_queue
- std::optional

Benefits:
- Less verbose code
- Reduced typing errors
- Consistent with function templates
- Maintains type safety
- No runtime performance impact

Best Practices:
- Be aware of common type deduction
- Use explicit types when deduction is unclear
- Provide deduction guides for custom classes
- Test edge cases with mixed types
*/
