// C++20 Parallel Algorithms with Modern Threading
// Compile: g++ -std=c++20 -pthread -ltbb -o parallel_algorithms parallel_algorithms.cpp
// Note: Requires Intel TBB library for full parallel execution policy support
// Alternative: g++ -std=c++20 -pthread -o parallel_algorithms parallel_algorithms.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <execution>
#include <chrono>
#include <random>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>
#include <string>
#include <map>
#include <set>
#include <functional>
#include <iterator>

// Custom parallel algorithms for educational purposes
namespace custom_parallel {

template<typename Iterator, typename Function>
void parallel_for_each(Iterator first, Iterator last, Function func, size_t num_threads = 0) {
    if (num_threads == 0) {
        num_threads = std::thread::hardware_concurrency();
    }
    
    const auto size = std::distance(first, last);
    const auto chunk_size = size / num_threads;
    
    if (chunk_size == 0) {
        std::for_each(first, last, func);
        return;
    }
    
    std::vector<std::jthread> threads;
    threads.reserve(num_threads);
    
    auto chunk_begin = first;
    for (size_t i = 0; i < num_threads - 1; ++i) {
        auto chunk_end = std::next(chunk_begin, chunk_size);
        
        threads.emplace_back([chunk_begin, chunk_end, func]() {
            std::for_each(chunk_begin, chunk_end, func);
        });
        
        chunk_begin = chunk_end;
    }
    
    // Handle remaining elements in main thread
    std::for_each(chunk_begin, last, func);
    
    // Wait for all threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

template<typename Iterator, typename T, typename BinaryOp>
T parallel_reduce(Iterator first, Iterator last, T init, BinaryOp op, size_t num_threads = 0) {
    if (num_threads == 0) {
        num_threads = std::thread::hardware_concurrency();
    }
    
    const auto size = std::distance(first, last);
    const auto chunk_size = size / num_threads;
    
    if (chunk_size == 0) {
        return std::accumulate(first, last, init, op);
    }
    
    std::vector<std::future<T>> futures;
    futures.reserve(num_threads);
    
    auto chunk_begin = first;
    for (size_t i = 0; i < num_threads - 1; ++i) {
        auto chunk_end = std::next(chunk_begin, chunk_size);
        
        futures.push_back(std::async(std::launch::async, [chunk_begin, chunk_end, init, op]() {
            return std::accumulate(chunk_begin, chunk_end, init, op);
        }));
        
        chunk_begin = chunk_end;
    }
    
    // Process remaining elements
    T result = std::accumulate(chunk_begin, last, init, op);
    
    // Combine results
    for (auto& future : futures) {
        result = op(result, future.get());
    }
    
    return result;
}

} // namespace custom_parallel

// Performance measurement utility
class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::string name;
    
public:
    explicit Timer(const std::string& timer_name) : name(timer_name) {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
    ~Timer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << name << ": " << duration.count() << " microseconds" << std::endl;
    }
};

void demonstrate_standard_parallel_algorithms() {
    std::cout << "\n=== 1. Standard Library Parallel Algorithms ===" << std::endl;
    
    // Create test data
    const size_t SIZE = 1000000;
    std::vector<int> data(SIZE);
    
    // Initialize with random values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    
    std::generate(data.begin(), data.end(), [&]() { return dis(gen); });
    
    std::cout << "Processing " << SIZE << " elements..." << std::endl;
    
    // 1. Sequential vs Parallel for_each
    {
        std::cout << "\n--- for_each Performance ---" << std::endl;
        
        std::vector<int> seq_data = data;
        std::vector<int> par_data = data;
        
        // Sequential
        {
            Timer timer("Sequential for_each");
            std::for_each(seq_data.begin(), seq_data.end(), [](int& x) {
                x = x * x + 1;  // Simple computation
            });
        }
        
        // Parallel (requires execution policy support)
        try {
            Timer timer("Parallel for_each");
            std::for_each(std::execution::par, par_data.begin(), par_data.end(), [](int& x) {
                x = x * x + 1;  // Same computation
            });
        } catch (const std::exception& e) {
            std::cout << "Parallel execution not supported: " << e.what() << std::endl;
            
            // Fallback to custom implementation
            Timer timer("Custom parallel for_each");
            custom_parallel::parallel_for_each(par_data.begin(), par_data.end(), [](int& x) {
                x = x * x + 1;
            });
        }
        
        // Verify results are identical
        bool results_match = std::equal(seq_data.begin(), seq_data.end(), par_data.begin());
        std::cout << "Results match: " << (results_match ? "Yes" : "No") << std::endl;
    }
    
    // 2. Sequential vs Parallel sort
    {
        std::cout << "\n--- sort Performance ---" << std::endl;
        
        std::vector<int> seq_data = data;
        std::vector<int> par_data = data;
        
        // Sequential sort
        {
            Timer timer("Sequential sort");
            std::sort(seq_data.begin(), seq_data.end());
        }
        
        // Parallel sort
        try {
            Timer timer("Parallel sort");
            std::sort(std::execution::par, par_data.begin(), par_data.end());
        } catch (const std::exception& e) {
            std::cout << "Parallel sort not supported: " << e.what() << std::endl;
        }
        
        // Verify sorting
        bool seq_sorted = std::is_sorted(seq_data.begin(), seq_data.end());
        bool par_sorted = std::is_sorted(par_data.begin(), par_data.end());
        std::cout << "Sequential sorted: " << (seq_sorted ? "Yes" : "No") << std::endl;
        std::cout << "Parallel sorted: " << (par_sorted ? "Yes" : "No") << std::endl;
    }
    
    // 3. Parallel accumulate/reduce
    {
        std::cout << "\n--- accumulate/reduce Performance ---" << std::endl;
        
        long long seq_sum = 0, par_sum = 0, custom_sum = 0;
        
        // Sequential accumulate
        {
            Timer timer("Sequential accumulate");
            seq_sum = std::accumulate(data.begin(), data.end(), 0LL);
        }
        
        // Parallel reduce
        try {
            Timer timer("Parallel reduce");
            par_sum = std::reduce(std::execution::par, data.begin(), data.end(), 0LL);
        } catch (const std::exception& e) {
            std::cout << "Parallel reduce not supported: " << e.what() << std::endl;
            par_sum = seq_sum; // Use sequential result
        }
        
        // Custom parallel reduce
        {
            Timer timer("Custom parallel reduce");
            custom_sum = custom_parallel::parallel_reduce(data.begin(), data.end(), 0LL, std::plus<long long>());
        }
        
        std::cout << "Sequential sum: " << seq_sum << std::endl;
        std::cout << "Parallel sum: " << par_sum << std::endl;
        std::cout << "Custom sum: " << custom_sum << std::endl;
        std::cout << "Results match: " << ((seq_sum == par_sum) && (seq_sum == custom_sum) ? "Yes" : "No") << std::endl;
    }
}

void demonstrate_parallel_transform() {
    std::cout << "\n=== 2. Parallel Transform Operations ===" << std::endl;
    
    const size_t SIZE = 500000;
    std::vector<double> input(SIZE);
    std::vector<double> output_seq(SIZE);
    std::vector<double> output_par(SIZE);
    
    // Initialize input data
    std::iota(input.begin(), input.end(), 1.0);
    
    std::cout << "Transforming " << SIZE << " elements..." << std::endl;
    
    // Complex mathematical transformation
    auto complex_transform = [](double x) {
        return std::sqrt(x) + std::sin(x / 1000.0) * std::cos(x / 2000.0);
    };
    
    // Sequential transform
    {
        Timer timer("Sequential transform");
        std::transform(input.begin(), input.end(), output_seq.begin(), complex_transform);
    }
    
    // Parallel transform
    try {
        Timer timer("Parallel transform");
        std::transform(std::execution::par, input.begin(), input.end(), output_par.begin(), complex_transform);
    } catch (const std::exception& e) {
        std::cout << "Parallel transform not supported: " << e.what() << std::endl;
        
        // Custom parallel transform
        Timer timer("Custom parallel transform");
        custom_parallel::parallel_for_each(input.begin(), input.end(), [&, i = 0](const double& x) mutable {
            size_t index = &x - &input[0];
            output_par[index] = complex_transform(x);
        });
    }
    
    // Verify results
    bool results_match = std::equal(output_seq.begin(), output_seq.end(), output_par.begin(),
                                   [](double a, double b) { return std::abs(a - b) < 1e-10; });
    std::cout << "Transform results match: " << (results_match ? "Yes" : "No") << std::endl;
    
    // Show sample results
    std::cout << "Sample results (first 5):" << std::endl;
    for (size_t i = 0; i < 5; ++i) {
        std::cout << "  " << input[i] << " -> " << output_seq[i] << std::endl;
    }
}

void demonstrate_parallel_find_and_search() {
    std::cout << "\n=== 3. Parallel Search Operations ===" << std::endl;
    
    const size_t SIZE = 1000000;
    std::vector<int> data(SIZE);
    
    // Fill with sequential numbers and some duplicates
    std::iota(data.begin(), data.end(), 1);
    
    // Add some specific values to search for
    data[SIZE/4] = 999999;
    data[SIZE/2] = 999999;
    data[3*SIZE/4] = 999999;
    
    std::cout << "Searching in " << SIZE << " elements..." << std::endl;
    
    const int search_value = 999999;
    
    // Sequential find
    std::vector<int>::iterator seq_result;
    {
        Timer timer("Sequential find");
        seq_result = std::find(data.begin(), data.end(), search_value);
    }
    
    // Parallel find
    std::vector<int>::iterator par_result;
    try {
        Timer timer("Parallel find");
        par_result = std::find(std::execution::par, data.begin(), data.end(), search_value);
    } catch (const std::exception& e) {
        std::cout << "Parallel find not supported: " << e.what() << std::endl;
        par_result = seq_result;
    }
    
    std::cout << "Sequential found at position: " << (seq_result - data.begin()) << std::endl;
    std::cout << "Parallel found at position: " << (par_result - data.begin()) << std::endl;
    
    // Count occurrences
    long seq_count, par_count;
    
    {
        Timer timer("Sequential count");
        seq_count = std::count(data.begin(), data.end(), search_value);
    }
    
    try {
        Timer timer("Parallel count");
        par_count = std::count(std::execution::par, data.begin(), data.end(), search_value);
    } catch (const std::exception& e) {
        std::cout << "Parallel count not supported" << std::endl;
        par_count = seq_count;
    }
    
    std::cout << "Sequential count: " << seq_count << std::endl;
    std::cout << "Parallel count: " << par_count << std::endl;
}

void demonstrate_parallel_string_processing() {
    std::cout << "\n=== 4. Parallel String Processing ===" << std::endl;
    
    // Generate test strings
    std::vector<std::string> strings;
    strings.reserve(100000);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> length_dis(5, 20);
    std::uniform_int_distribution<> char_dis(97, 122); // a-z
    
    for (int i = 0; i < 100000; ++i) {
        int len = length_dis(gen);
        std::string str;
        str.reserve(len);
        
        for (int j = 0; j < len; ++j) {
            str += static_cast<char>(char_dis(gen));
        }
        strings.push_back(str);
    }
    
    std::cout << "Processing " << strings.size() << " strings..." << std::endl;
    
    // String transformation: to uppercase
    std::vector<std::string> upper_seq = strings;
    std::vector<std::string> upper_par = strings;
    
    auto to_upper = [](std::string& s) {
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    };
    
    // Sequential
    {
        Timer timer("Sequential string transform");
        std::for_each(upper_seq.begin(), upper_seq.end(), to_upper);
    }
    
    // Parallel
    try {
        Timer timer("Parallel string transform");
        std::for_each(std::execution::par, upper_par.begin(), upper_par.end(), to_upper);
    } catch (const std::exception& e) {
        std::cout << "Parallel string transform not supported" << std::endl;
        Timer timer("Custom parallel string transform");
        custom_parallel::parallel_for_each(upper_par.begin(), upper_par.end(), to_upper);
    }
    
    // Verify first few results
    bool match = true;
    for (size_t i = 0; i < std::min(size_t(10), strings.size()); ++i) {
        if (upper_seq[i] != upper_par[i]) {
            match = false;
            break;
        }
    }
    std::cout << "String transform results match: " << (match ? "Yes" : "No") << std::endl;
    
    // Count strings containing specific substring
    const std::string substring = "abc";
    
    auto contains_substring = [&substring](const std::string& s) {
        return s.find(substring) != std::string::npos;
    };
    
    long seq_count, par_count;
    
    {
        Timer timer("Sequential substring count");
        seq_count = std::count_if(strings.begin(), strings.end(), contains_substring);
    }
    
    try {
        Timer timer("Parallel substring count");
        par_count = std::count_if(std::execution::par, strings.begin(), strings.end(), contains_substring);
    } catch (const std::exception& e) {
        std::cout << "Parallel count_if not supported" << std::endl;
        par_count = seq_count;
    }
    
    std::cout << "Strings containing '" << substring << "' - Sequential: " << seq_count 
              << ", Parallel: " << par_count << std::endl;
}

void demonstrate_parallel_numerical_computations() {
    std::cout << "\n=== 5. Parallel Numerical Computations ===" << std::endl;
    
    const size_t SIZE = 1000000;
    std::vector<double> data(SIZE);
    
    // Initialize with values for computation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.1, 10.0);
    
    std::generate(data.begin(), data.end(), [&]() { return dis(gen); });
    
    std::cout << "Numerical computations on " << SIZE << " elements..." << std::endl;
    
    // 1. Parallel partial_sum (prefix sum)
    std::vector<double> prefix_seq(SIZE), prefix_par(SIZE);
    
    {
        Timer timer("Sequential partial_sum");
        std::partial_sum(data.begin(), data.end(), prefix_seq.begin());
    }
    
    try {
        Timer timer("Parallel inclusive_scan");
        std::inclusive_scan(std::execution::par, data.begin(), data.end(), prefix_par.begin());
    } catch (const std::exception& e) {
        std::cout << "Parallel inclusive_scan not supported" << std::endl;
        // Fallback to sequential
        std::partial_sum(data.begin(), data.end(), prefix_par.begin());
    }
    
    // Verify first few results
    bool prefix_match = std::equal(prefix_seq.begin(), prefix_seq.begin() + 10, prefix_par.begin(),
                                  [](double a, double b) { return std::abs(a - b) < 1e-10; });
    std::cout << "Prefix sum results match: " << (prefix_match ? "Yes" : "No") << std::endl;
    
    // 2. Parallel statistical computations
    double seq_min, seq_max, par_min, par_max;
    
    // Find min/max
    {
        Timer timer("Sequential min_element");
        seq_min = *std::min_element(data.begin(), data.end());
    }
    
    try {
        Timer timer("Parallel min_element");
        par_min = *std::min_element(std::execution::par, data.begin(), data.end());
    } catch (const std::exception& e) {
        par_min = seq_min;
    }
    
    {
        Timer timer("Sequential max_element");
        seq_max = *std::max_element(data.begin(), data.end());
    }
    
    try {
        Timer timer("Parallel max_element");
        par_max = *std::max_element(std::execution::par, data.begin(), data.end());
    } catch (const std::exception& e) {
        par_max = seq_max;
    }
    
    std::cout << "Min - Sequential: " << seq_min << ", Parallel: " << par_min << std::endl;
    std::cout << "Max - Sequential: " << seq_max << ", Parallel: " << par_max << std::endl;
    
    // 3. Parallel variance computation
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    
    auto variance_op = [mean](double x) { 
        double diff = x - mean; 
        return diff * diff; 
    };
    
    double seq_variance, par_variance;
    
    {
        Timer timer("Sequential variance");
        std::vector<double> squared_diffs(data.size());
        std::transform(data.begin(), data.end(), squared_diffs.begin(), variance_op);
        seq_variance = std::accumulate(squared_diffs.begin(), squared_diffs.end(), 0.0) / data.size();
    }
    
    {
        Timer timer("Parallel variance");
        try {
            par_variance = std::transform_reduce(std::execution::par, data.begin(), data.end(), 
                                               0.0, std::plus<>(), variance_op) / data.size();
        } catch (const std::exception& e) {
            // Custom parallel implementation
            par_variance = custom_parallel::parallel_reduce(data.begin(), data.end(), 0.0,
                [variance_op](double acc, double val) {
                    return acc + variance_op(val);
                }) / data.size();
        }
    }
    
    std::cout << "Variance - Sequential: " << seq_variance << ", Parallel: " << par_variance << std::endl;
    std::cout << "Standard deviation: " << std::sqrt(seq_variance) << std::endl;
}

void demonstrate_execution_policies() {
    std::cout << "\n=== 6. Execution Policies ===" << std::endl;
    
    std::vector<int> data(100000);
    std::iota(data.begin(), data.end(), 1);
    
    std::cout << "Comparing different execution policies..." << std::endl;
    
    auto expensive_operation = [](int x) {
        // Simulate expensive computation
        double result = x;
        for (int i = 0; i < 100; ++i) {
            result = std::sin(result) + std::cos(result);
        }
        return static_cast<int>(result * 1000) % 1000;
    };
    
    // Sequential execution
    {
        std::vector<int> result(data.size());
        Timer timer("std::execution::seq");
        try {
            std::transform(std::execution::seq, data.begin(), data.end(), 
                          result.begin(), expensive_operation);
        } catch (const std::exception& e) {
            std::cout << "Sequential policy not available" << std::endl;
        }
    }
    
    // Parallel execution
    {
        std::vector<int> result(data.size());
        Timer timer("std::execution::par");
        try {
            std::transform(std::execution::par, data.begin(), data.end(), 
                          result.begin(), expensive_operation);
        } catch (const std::exception& e) {
            std::cout << "Parallel policy not available" << std::endl;
        }
    }
    
    // Parallel unsequenced execution (vectorized)
    {
        std::vector<int> result(data.size());
        Timer timer("std::execution::par_unseq");
        try {
            std::transform(std::execution::par_unseq, data.begin(), data.end(), 
                          result.begin(), expensive_operation);
        } catch (const std::exception& e) {
            std::cout << "Parallel unsequenced policy not available" << std::endl;
        }
    }
    
    // Unsequenced execution (vectorized, single-threaded)
    {
        std::vector<int> result(data.size());
        Timer timer("std::execution::unseq");
        try {
            std::transform(std::execution::unseq, data.begin(), data.end(), 
                          result.begin(), expensive_operation);
        } catch (const std::exception& e) {
            std::cout << "Unsequenced policy not available" << std::endl;
        }
    }
}

int main() {
    std::cout << "=== C++17/20 Parallel Algorithms Demo ===" << std::endl;
    std::cout << "Hardware concurrency: " << std::thread::hardware_concurrency() << " threads" << std::endl;
    
    try {
        demonstrate_standard_parallel_algorithms();
        demonstrate_parallel_transform();
        demonstrate_parallel_find_and_search();
        demonstrate_parallel_string_processing();
        demonstrate_parallel_numerical_computations();
        demonstrate_execution_policies();
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Parallel Algorithms Benefits ===" << std::endl;
    std::cout << "✅ Automatic parallelization" << std::endl;
    std::cout << "✅ No manual thread management" << std::endl;
    std::cout << "✅ Exception safety" << std::endl;
    std::cout << "✅ Policy-based execution control" << std::endl;
    std::cout << "✅ Vectorization support (unseq policies)" << std::endl;
    std::cout << "✅ Scalable to available hardware" << std::endl;
    
    std::cout << "\n=== Execution Policies ===" << std::endl;
    std::cout << "• std::execution::seq - Sequential execution" << std::endl;
    std::cout << "• std::execution::par - Parallel execution" << std::endl;
    std::cout << "• std::execution::unseq - Vectorized execution" << std::endl;
    std::cout << "• std::execution::par_unseq - Parallel + vectorized" << std::endl;
    
    std::cout << "\n=== When to Use Parallel Algorithms ===" << std::endl;
    std::cout << "• Large datasets (> 10K elements typically)" << std::endl;
    std::cout << "• CPU-intensive operations" << std::endl;
    std::cout << "• Independent computations" << std::endl;
    std::cout << "• Multi-core systems available" << std::endl;
    std::cout << "• Want simple parallelization" << std::endl;
    
    return 0;
}

/*
COMPILATION OPTIONS:

With TBB (Intel Threading Building Blocks):
g++ -std=c++20 -pthread -ltbb -Wall -Wextra -O2 -o parallel_algorithms parallel_algorithms.cpp

Without TBB (limited parallel support):
g++ -std=c++20 -pthread -Wall -Wextra -O2 -o parallel_algorithms parallel_algorithms.cpp

For maximum compatibility:
g++ -std=c++17 -pthread -Wall -Wextra -O2 -DUSE_CUSTOM_PARALLEL -o parallel_algorithms parallel_algorithms.cpp

Key Features Demonstrated:

C++17 Parallel Algorithms:
- std::for_each with execution policies
- std::transform with parallel execution
- std::sort with parallel execution
- std::find with parallel search
- std::count and std::count_if
- std::accumulate vs std::reduce
- std::min_element / std::max_element

C++20 Enhancements:
- std::inclusive_scan (parallel prefix sum)
- std::transform_reduce (map-reduce pattern)
- Better exception handling in parallel contexts

Execution Policies:

std::execution::seq:
- Sequential execution (same as without policy)
- Useful for debugging or small datasets

std::execution::par:
- Parallel execution across multiple threads
- Most common choice for CPU-bound work

std::execution::unseq:
- Vectorized execution (SIMD)
- Single-threaded but uses vector instructions

std::execution::par_unseq:
- Combined parallel and vectorized execution
- Maximum performance for suitable workloads

Performance Considerations:

Overhead Factors:
- Thread creation/synchronization costs
- Memory bandwidth limitations
- Cache coherency overhead
- Algorithm complexity

Optimal Use Cases:
- Large datasets (amortize overhead)
- CPU-intensive operations
- Independent computations
- Available parallel hardware

Implementation Details:

Standard Library Support:
- GCC: Limited support without TBB
- MSVC: Full support on Windows
- Clang: Requires additional libraries

Alternative Libraries:
- Intel TBB (Threading Building Blocks)
- Microsoft PPL (Parallel Patterns Library)
- OpenMP parallel algorithms
- Custom thread pool implementations

Real-world Applications:
- Image/video processing
- Scientific computations
- Data analytics
- Machine learning algorithms
- Financial modeling
- Simulation systems

Best Practices:
- Profile before parallelizing
- Consider data size vs overhead
- Ensure thread-safe operations
- Handle exceptions properly
- Test on target hardware
- Measure actual performance gains
*/
