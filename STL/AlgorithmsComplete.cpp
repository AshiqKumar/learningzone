// STL Algorithms Comprehensive Reference
// Compile: g++ -std=c++20 -o algorithms_complete algorithms_complete.cpp
// Run: ./algorithms_complete

#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <random>
#include <chrono>
#include <set>
#include <map>

void demonstrate_non_modifying_algorithms() {
    std::cout << "\n=== NON-MODIFYING SEQUENCE ALGORITHMS ===" << std::endl;
    
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> pattern = {4, 5, 6};
    
    // 1. all_of, any_of, none_of
    {
        std::cout << "\n1. Condition Testing:" << std::endl;
        
        bool all_positive = std::all_of(data.begin(), data.end(), 
                                      [](int x) { return x > 0; });
        bool any_even = std::any_of(data.begin(), data.end(), 
                                   [](int x) { return x % 2 == 0; });
        bool none_negative = std::none_of(data.begin(), data.end(), 
                                        [](int x) { return x < 0; });
        
        std::cout << "All positive: " << std::boolalpha << all_positive << std::endl;
        std::cout << "Any even: " << any_even << std::endl;
        std::cout << "None negative: " << none_negative << std::endl;
    }
    
    // 2. for_each and for_each_n
    {
        std::cout << "\n2. for_each Operations:" << std::endl;
        
        std::cout << "Original: ";
        std::for_each(data.begin(), data.end(), [](int x) { std::cout << x << " "; });
        std::cout << std::endl;
        
        std::cout << "Doubled: ";
        std::for_each(data.begin(), data.end(), [](int x) { std::cout << x * 2 << " "; });
        std::cout << std::endl;
        
        std::cout << "First 5 elements: ";
        std::for_each_n(data.begin(), 5, [](int x) { std::cout << x << " "; });
        std::cout << std::endl;
    }
    
    // 3. count and count_if
    {
        std::cout << "\n3. Counting Elements:" << std::endl;
        
        int count_5 = std::count(data.begin(), data.end(), 5);
        int count_even = std::count_if(data.begin(), data.end(), 
                                      [](int x) { return x % 2 == 0; });
        int count_gt_5 = std::count_if(data.begin(), data.end(), 
                                      [](int x) { return x > 5; });
        
        std::cout << "Count of 5: " << count_5 << std::endl;
        std::cout << "Count of even numbers: " << count_even << std::endl;
        std::cout << "Count > 5: " << count_gt_5 << std::endl;
    }
    
    // 4. find variations
    {
        std::cout << "\n4. Finding Elements:" << std::endl;
        
        auto it1 = std::find(data.begin(), data.end(), 7);
        if (it1 != data.end()) {
            std::cout << "Found 7 at position: " << std::distance(data.begin(), it1) << std::endl;
        }
        
        auto it2 = std::find_if(data.begin(), data.end(), 
                               [](int x) { return x > 8; });
        if (it2 != data.end()) {
            std::cout << "First element > 8: " << *it2 << std::endl;
        }
        
        auto it3 = std::find_if_not(data.begin(), data.end(), 
                                   [](int x) { return x < 5; });
        if (it3 != data.end()) {
            std::cout << "First element not < 5: " << *it3 << std::endl;
        }
    }
    
    // 5. find_end, find_first_of
    {
        std::cout << "\n5. Pattern Finding:" << std::endl;
        
        auto it_end = std::find_end(data.begin(), data.end(), 
                                   pattern.begin(), pattern.end());
        if (it_end != data.end()) {
            std::cout << "Last occurrence of pattern [4,5,6] starts at position: " 
                      << std::distance(data.begin(), it_end) << std::endl;
        }
        
        std::vector<int> search_set = {3, 7, 11};
        auto it_first = std::find_first_of(data.begin(), data.end(), 
                                          search_set.begin(), search_set.end());
        if (it_first != data.end()) {
            std::cout << "First element from {3,7,11}: " << *it_first << std::endl;
        }
    }
    
    // 6. adjacent_find
    {
        std::cout << "\n6. Adjacent Elements:" << std::endl;
        
        std::vector<int> with_duplicates = {1, 2, 3, 3, 4, 5, 6, 6};
        auto it_adj = std::adjacent_find(with_duplicates.begin(), with_duplicates.end());
        
        if (it_adj != with_duplicates.end()) {
            std::cout << "First duplicate: " << *it_adj << " at position " 
                      << std::distance(with_duplicates.begin(), it_adj) << std::endl;
        }
    }
    
    // 7. search algorithms
    {
        std::cout << "\n7. Sequence Search:" << std::endl;
        
        auto it_search = std::search(data.begin(), data.end(), 
                                    pattern.begin(), pattern.end());
        if (it_search != data.end()) {
            std::cout << "Pattern [4,5,6] found at position: " 
                      << std::distance(data.begin(), it_search) << std::endl;
        }
        
        // Search for n consecutive elements
        auto it_search_n = std::search_n(data.begin(), data.end(), 2, 5);
        std::vector<int> consecutive = {1, 2, 3, 4, 5, 5, 6, 7};
        auto it_consecutive = std::search_n(consecutive.begin(), consecutive.end(), 2, 5);
        if (it_consecutive != consecutive.end()) {
            std::cout << "Found 2 consecutive 5s starting at position: " 
                      << std::distance(consecutive.begin(), it_consecutive) << std::endl;
        }
    }
}

void demonstrate_modifying_algorithms() {
    std::cout << "\n=== MODIFYING SEQUENCE ALGORITHMS ===" << std::endl;
    
    // 1. copy variations
    {
        std::cout << "\n1. Copy Operations:" << std::endl;
        
        std::vector<int> source = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::vector<int> dest(10);
        std::vector<int> dest_if, dest_n;
        
        // Basic copy
        std::copy(source.begin(), source.end(), dest.begin());
        std::cout << "Copied: ";
        for (int x : dest) std::cout << x << " ";
        std::cout << std::endl;
        
        // Copy with condition
        std::copy_if(source.begin(), source.end(), std::back_inserter(dest_if),
                    [](int x) { return x % 2 == 0; });
        std::cout << "Even numbers: ";
        for (int x : dest_if) std::cout << x << " ";
        std::cout << std::endl;
        
        // Copy n elements
        std::copy_n(source.begin(), 5, std::back_inserter(dest_n));
        std::cout << "First 5: ";
        for (int x : dest_n) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 2. move operations
    {
        std::cout << "\n2. Move Operations:" << std::endl;
        
        std::vector<std::string> source = {"apple", "banana", "cherry", "date"};
        std::vector<std::string> dest(4);
        
        std::cout << "Before move - Source: ";
        for (const auto& s : source) std::cout << "'" << s << "' ";
        std::cout << std::endl;
        
        std::move(source.begin(), source.end(), dest.begin());
        
        std::cout << "After move - Dest: ";
        for (const auto& s : dest) std::cout << "'" << s << "' ";
        std::cout << std::endl;
        
        std::cout << "After move - Source: ";
        for (const auto& s : source) std::cout << "'" << s << "' ";
        std::cout << std::endl;
    }
    
    // 3. fill and generate
    {
        std::cout << "\n3. Fill and Generate:" << std::endl;
        
        std::vector<int> vec1(10);
        std::fill(vec1.begin(), vec1.end(), 42);
        std::cout << "Filled with 42: ";
        for (int x : vec1) std::cout << x << " ";
        std::cout << std::endl;
        
        std::vector<int> vec2(10);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        
        std::generate(vec2.begin(), vec2.end(), [&]() { return dis(gen); });
        std::cout << "Random generated: ";
        for (int x : vec2) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 4. transform
    {
        std::cout << "\n4. Transform Operations:" << std::endl;
        
        std::vector<int> numbers = {1, 2, 3, 4, 5};
        std::vector<int> squares(5);
        std::vector<std::string> words = {"hello", "world", "stl", "algorithms"};
        std::vector<std::string> upper_words(4);
        
        // Transform to squares
        std::transform(numbers.begin(), numbers.end(), squares.begin(),
                      [](int x) { return x * x; });
        std::cout << "Squares: ";
        for (int x : squares) std::cout << x << " ";
        std::cout << std::endl;
        
        // Transform strings to uppercase
        std::transform(words.begin(), words.end(), upper_words.begin(),
                      [](const std::string& s) {
                          std::string result = s;
                          std::transform(result.begin(), result.end(), result.begin(), ::toupper);
                          return result;
                      });
        std::cout << "Uppercase: ";
        for (const auto& s : upper_words) std::cout << s << " ";
        std::cout << std::endl;
        
        // Binary transform (two input ranges)
        std::vector<int> a = {1, 2, 3, 4, 5};
        std::vector<int> b = {10, 20, 30, 40, 50};
        std::vector<int> sum(5);
        
        std::transform(a.begin(), a.end(), b.begin(), sum.begin(), std::plus<int>());
        std::cout << "Element-wise sum: ";
        for (int x : sum) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 5. replace operations
    {
        std::cout << "\n5. Replace Operations:" << std::endl;
        
        std::vector<int> data = {1, 2, 3, 2, 4, 2, 5};
        std::vector<int> data_copy = data;
        
        std::cout << "Original: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Replace all 2s with 99
        std::replace(data.begin(), data.end(), 2, 99);
        std::cout << "Replace 2->99: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Replace if condition
        std::replace_if(data_copy.begin(), data_copy.end(), 
                       [](int x) { return x % 2 == 0; }, 0);
        std::cout << "Replace even->0: ";
        for (int x : data_copy) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 6. remove operations (erase-remove idiom)
    {
        std::cout << "\n6. Remove Operations:" << std::endl;
        
        std::vector<int> data = {1, 2, 3, 2, 4, 2, 5, 6};
        std::vector<int> data_copy = data;
        
        std::cout << "Before remove: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Remove all 2s (erase-remove idiom)
        auto new_end = std::remove(data.begin(), data.end(), 2);
        data.erase(new_end, data.end());
        
        std::cout << "After remove 2: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Remove if even
        auto new_end2 = std::remove_if(data_copy.begin(), data_copy.end(), 
                                      [](int x) { return x % 2 == 0; });
        data_copy.erase(new_end2, data_copy.end());
        
        std::cout << "After remove even: ";
        for (int x : data_copy) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 7. unique operation
    {
        std::cout << "\n7. Remove Consecutive Duplicates:" << std::endl;
        
        std::vector<int> data = {1, 1, 2, 2, 2, 3, 1, 1, 4, 4};
        
        std::cout << "Before unique: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        auto new_end = std::unique(data.begin(), data.end());
        data.erase(new_end, data.end());
        
        std::cout << "After unique: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 8. reverse and rotate
    {
        std::cout << "\n8. Reverse and Rotate:" << std::endl;
        
        std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8};
        std::vector<int> data_copy = data;
        
        std::cout << "Original: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        std::reverse(data.begin(), data.end());
        std::cout << "Reversed: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Rotate left by 3 positions
        std::rotate(data_copy.begin(), data_copy.begin() + 3, data_copy.end());
        std::cout << "Rotated left by 3: ";
        for (int x : data_copy) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 9. random_shuffle and shuffle
    {
        std::cout << "\n9. Shuffle Operations:" << std::endl;
        
        std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8};
        
        std::cout << "Original: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(data.begin(), data.end(), g);
        
        std::cout << "Shuffled: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
    }
}

void demonstrate_sorting_algorithms() {
    std::cout << "\n=== SORTING AND RELATED ALGORITHMS ===" << std::endl;
    
    // 1. sort variations
    {
        std::cout << "\n1. Sorting Operations:" << std::endl;
        
        std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
        std::vector<int> data_copy = data;
        std::vector<int> data_copy2 = data;
        
        std::cout << "Original: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Full sort
        std::sort(data.begin(), data.end());
        std::cout << "Sorted: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Stable sort (maintains relative order of equal elements)
        std::stable_sort(data_copy.begin(), data_copy.end(), std::greater<int>());
        std::cout << "Stable sort (desc): ";
        for (int x : data_copy) std::cout << x << " ";
        std::cout << std::endl;
        
        // Partial sort (only first n elements sorted)
        std::partial_sort(data_copy2.begin(), data_copy2.begin() + 4, data_copy2.end());
        std::cout << "Partial sort (first 4): ";
        for (int x : data_copy2) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 2. nth_element
    {
        std::cout << "\n2. nth_element Operation:" << std::endl;
        
        std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
        
        std::cout << "Finding 4th smallest element (index 3):" << std::endl;
        std::cout << "Before: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        std::nth_element(data.begin(), data.begin() + 3, data.end());
        
        std::cout << "After nth_element(3): ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        std::cout << "4th smallest element: " << data[3] << std::endl;
    }
    
    // 3. Binary search operations (require sorted range)
    {
        std::cout << "\n3. Binary Search Operations:" << std::endl;
        
        std::vector<int> sorted_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        bool found = std::binary_search(sorted_data.begin(), sorted_data.end(), 5);
        std::cout << "Binary search for 5: " << std::boolalpha << found << std::endl;
        
        // Lower bound (first position where element could be inserted)
        auto lb = std::lower_bound(sorted_data.begin(), sorted_data.end(), 5);
        std::cout << "Lower bound for 5: position " << std::distance(sorted_data.begin(), lb) << std::endl;
        
        // Upper bound (last position where element could be inserted)
        auto ub = std::upper_bound(sorted_data.begin(), sorted_data.end(), 5);
        std::cout << "Upper bound for 5: position " << std::distance(sorted_data.begin(), ub) << std::endl;
        
        // Equal range (range where element exists)
        auto er = std::equal_range(sorted_data.begin(), sorted_data.end(), 5);
        std::cout << "Equal range for 5: [" << std::distance(sorted_data.begin(), er.first)
                  << ", " << std::distance(sorted_data.begin(), er.second) << ")" << std::endl;
    }
    
    // 4. Heap operations
    {
        std::cout << "\n4. Heap Operations:" << std::endl;
        
        std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
        
        std::cout << "Original: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Make heap (max heap)
        std::make_heap(data.begin(), data.end());
        std::cout << "Max heap: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Check if heap
        bool is_heap = std::is_heap(data.begin(), data.end());
        std::cout << "Is heap: " << std::boolalpha << is_heap << std::endl;
        
        // Push to heap
        data.push_back(15);
        std::push_heap(data.begin(), data.end());
        std::cout << "After push 15: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Pop from heap
        std::pop_heap(data.begin(), data.end());
        int max_val = data.back();
        data.pop_back();
        std::cout << "Popped max: " << max_val << std::endl;
        std::cout << "After pop: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        // Heap sort
        std::sort_heap(data.begin(), data.end());
        std::cout << "Heap sorted: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
    }
}

void demonstrate_numeric_algorithms() {
    std::cout << "\n=== NUMERIC ALGORITHMS ===" << std::endl;
    
    // 1. accumulate
    {
        std::cout << "\n1. Accumulate Operations:" << std::endl;
        
        std::vector<int> data = {1, 2, 3, 4, 5};
        
        // Sum
        int sum = std::accumulate(data.begin(), data.end(), 0);
        std::cout << "Sum: " << sum << std::endl;
        
        // Product
        int product = std::accumulate(data.begin(), data.end(), 1, std::multiplies<int>());
        std::cout << "Product: " << product << std::endl;
        
        // Concatenate strings
        std::vector<std::string> words = {"Hello", " ", "STL", " ", "World"};
        std::string result = std::accumulate(words.begin(), words.end(), std::string(""));
        std::cout << "Concatenated: '" << result << "'" << std::endl;
    }
    
    // 2. inner_product
    {
        std::cout << "\n2. Inner Product:" << std::endl;
        
        std::vector<int> a = {1, 2, 3, 4, 5};
        std::vector<int> b = {2, 3, 4, 5, 6};
        
        int dot_product = std::inner_product(a.begin(), a.end(), b.begin(), 0);
        std::cout << "Dot product: " << dot_product << std::endl;
        
        // Custom operations (sum of products)
        int custom = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                       std::plus<int>(), std::multiplies<int>());
        std::cout << "Custom inner product: " << custom << std::endl;
    }
    
    // 3. partial_sum
    {
        std::cout << "\n3. Partial Sum (Prefix Sum):" << std::endl;
        
        std::vector<int> data = {1, 2, 3, 4, 5};
        std::vector<int> prefix_sums(5);
        
        std::partial_sum(data.begin(), data.end(), prefix_sums.begin());
        
        std::cout << "Original: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        std::cout << "Prefix sums: ";
        for (int x : prefix_sums) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 4. adjacent_difference
    {
        std::cout << "\n4. Adjacent Difference:" << std::endl;
        
        std::vector<int> data = {1, 4, 9, 16, 25};
        std::vector<int> differences(5);
        
        std::adjacent_difference(data.begin(), data.end(), differences.begin());
        
        std::cout << "Original: ";
        for (int x : data) std::cout << x << " ";
        std::cout << std::endl;
        
        std::cout << "Differences: ";
        for (int x : differences) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 5. iota
    {
        std::cout << "\n5. Iota (Sequential Fill):" << std::endl;
        
        std::vector<int> sequence(10);
        std::iota(sequence.begin(), sequence.end(), 1);
        
        std::cout << "Sequence starting from 1: ";
        for (int x : sequence) std::cout << x << " ";
        std::cout << std::endl;
    }
}

void demonstrate_set_algorithms() {
    std::cout << "\n=== SET ALGORITHMS (on sorted ranges) ===" << std::endl;
    
    std::vector<int> set1 = {1, 2, 3, 4, 5, 6};
    std::vector<int> set2 = {4, 5, 6, 7, 8, 9};
    
    std::cout << "Set 1: ";
    for (int x : set1) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << "Set 2: ";
    for (int x : set2) std::cout << x << " ";
    std::cout << std::endl;
    
    // 1. set_union
    {
        std::vector<int> result;
        std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(),
                      std::back_inserter(result));
        std::cout << "Union: ";
        for (int x : result) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 2. set_intersection
    {
        std::vector<int> result;
        std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                             std::back_inserter(result));
        std::cout << "Intersection: ";
        for (int x : result) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 3. set_difference
    {
        std::vector<int> result;
        std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
                           std::back_inserter(result));
        std::cout << "Set1 - Set2: ";
        for (int x : result) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 4. set_symmetric_difference
    {
        std::vector<int> result;
        std::set_symmetric_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
                                     std::back_inserter(result));
        std::cout << "Symmetric difference: ";
        for (int x : result) std::cout << x << " ";
        std::cout << std::endl;
    }
    
    // 5. includes
    {
        std::vector<int> subset = {2, 3, 4};
        bool is_subset = std::includes(set1.begin(), set1.end(), subset.begin(), subset.end());
        std::cout << "Is {2,3,4} subset of set1: " << std::boolalpha << is_subset << std::endl;
    }
}

void demonstrate_permutation_algorithms() {
    std::cout << "\n=== PERMUTATION ALGORITHMS ===" << std::endl;
    
    // 1. is_permutation
    {
        std::cout << "\n1. Permutation Testing:" << std::endl;
        
        std::vector<int> vec1 = {1, 2, 3, 4, 5};
        std::vector<int> vec2 = {5, 4, 3, 2, 1};
        std::vector<int> vec3 = {1, 2, 3, 4, 6};
        
        bool perm1 = std::is_permutation(vec1.begin(), vec1.end(), vec2.begin());
        bool perm2 = std::is_permutation(vec1.begin(), vec1.end(), vec3.begin());
        
        std::cout << "vec1 and vec2 are permutations: " << std::boolalpha << perm1 << std::endl;
        std::cout << "vec1 and vec3 are permutations: " << std::boolalpha << perm2 << std::endl;
    }
    
    // 2. next_permutation and prev_permutation
    {
        std::cout << "\n2. Generate Permutations:" << std::endl;
        
        std::vector<int> data = {1, 2, 3};
        
        std::cout << "All permutations of {1,2,3}:" << std::endl;
        do {
            for (int x : data) std::cout << x << " ";
            std::cout << std::endl;
        } while (std::next_permutation(data.begin(), data.end()));
        
        // Reset to last permutation
        data = {3, 2, 1};
        std::cout << "\nReverse order permutations:" << std::endl;
        do {
            for (int x : data) std::cout << x << " ";
            std::cout << std::endl;
        } while (std::prev_permutation(data.begin(), data.end()));
    }
}

void demonstrate_min_max_algorithms() {
    std::cout << "\n=== MIN/MAX ALGORITHMS ===" << std::endl;
    
    std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // 1. min_element, max_element
    {
        auto min_it = std::min_element(data.begin(), data.end());
        auto max_it = std::max_element(data.begin(), data.end());
        
        std::cout << "Min element: " << *min_it << " at position " 
                  << std::distance(data.begin(), min_it) << std::endl;
        std::cout << "Max element: " << *max_it << " at position " 
                  << std::distance(data.begin(), max_it) << std::endl;
    }
    
    // 2. minmax_element
    {
        auto minmax_pair = std::minmax_element(data.begin(), data.end());
        std::cout << "Min: " << *minmax_pair.first << ", Max: " << *minmax_pair.second << std::endl;
    }
    
    // 3. clamp (C++17)
    {
        std::cout << "Clamping values between 3 and 7:" << std::endl;
        for (int x : data) {
            int clamped = std::clamp(x, 3, 7);
            std::cout << x << " -> " << clamped << ", ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "=== COMPLETE STL ALGORITHMS REFERENCE ===" << std::endl;
    
    demonstrate_non_modifying_algorithms();
    demonstrate_modifying_algorithms();
    demonstrate_sorting_algorithms();
    demonstrate_numeric_algorithms();
    demonstrate_set_algorithms();
    demonstrate_permutation_algorithms();
    demonstrate_min_max_algorithms();
    
    std::cout << "\n=== ALGORITHM CATEGORIES SUMMARY ===" << std::endl;
    std::cout << "🔹 **Non-modifying:** for_each, find, count, search, equal" << std::endl;
    std::cout << "🔹 **Modifying:** copy, transform, replace, remove, unique" << std::endl;
    std::cout << "🔹 **Sorting:** sort, partial_sort, nth_element, binary_search" << std::endl;
    std::cout << "🔹 **Numeric:** accumulate, inner_product, partial_sum, iota" << std::endl;
    std::cout << "🔹 **Set operations:** union, intersection, difference (on sorted ranges)" << std::endl;
    std::cout << "🔹 **Heap:** make_heap, push_heap, pop_heap, sort_heap" << std::endl;
    std::cout << "🔹 **Permutation:** next_permutation, prev_permutation" << std::endl;
    std::cout << "🔹 **Min/Max:** min_element, max_element, minmax_element, clamp" << std::endl;
    
    std::cout << "\n=== PERFORMANCE CONSIDERATIONS ===" << std::endl;
    std::cout << "• Most algorithms work with iterators (container-agnostic)" << std::endl;
    std::cout << "• Many algorithms have *_if variants for conditional operations" << std::endl;
    std::cout << "• Use appropriate iterator categories (random access vs bidirectional)" << std::endl;
    std::cout << "• Consider parallel execution policies (C++17)" << std::endl;
    std::cout << "• Erase-remove idiom for efficient element removal" << std::endl;
    std::cout << "• Binary search algorithms require sorted ranges" << std::endl;
    std::cout << "• Set algorithms work on sorted ranges" << std::endl;
    
    return 0;
}

/*
ALGORITHM COMPLEXITY REFERENCE:

Non-modifying:
- find, count: O(n)
- search: O(n*m) where m is pattern size
- binary_search: O(log n) - requires sorted

Modifying:
- copy, transform: O(n)
- remove: O(n) but doesn't change container size
- unique: O(n) - requires sorted for best results

Sorting:
- sort: O(n log n) average, O(n²) worst case
- stable_sort: O(n log n)
- partial_sort: O(n log k) where k is sorted portion
- nth_element: O(n) average

Numeric:
- accumulate: O(n)
- partial_sum: O(n)
- inner_product: O(n)

Set operations:
- All set algorithms: O(m + n) on sorted ranges

Heap:
- make_heap: O(n)
- push/pop_heap: O(log n)
- sort_heap: O(n log n)

Memory Requirements:
- Most algorithms use O(1) extra space
- Some like merge, set_union may need O(n) space
- In-place algorithms modify input directly

Iterator Requirements:
- Input iterators: find, count, accumulate
- Forward iterators: search, adjacent_find
- Bidirectional: reverse, rotate
- Random access: sort, nth_element, binary_search
*/
