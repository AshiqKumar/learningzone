/*
 * Quick Sort Algorithm Implementation
 * 
 * Quick Sort:
 * - Efficient divide-and-conquer sorting algorithm
 * - Selects a pivot element and partitions array around it
 * - Time Complexity: O(n log n) average, O(n²) worst case
 * - Space Complexity: O(log n) average, O(n) worst case (due to recursion)
 * - Unstable: Generally not stable (depends on partitioning scheme)
 * - In-place: Yes (with optimal space usage)
 * 
 * Applications:
 * - General purpose sorting (default in many libraries)
 * - Large datasets
 * - When average-case performance is important
 * - Systems programming
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <random>
#include <stack>
#include <iomanip>

class QuickSort {
public:
    // Basic quick sort with Lomuto partition scheme
    static void sort(std::vector<int>& arr) {
        quickSortRecursive(arr, 0, arr.size() - 1);
    }
    
    // Quick sort with step-by-step visualization
    static void sortWithVisualization(std::vector<int>& arr) {
        std::cout << "Quick Sort Step-by-Step:\n";
        printArray(arr, "Initial Array");
        quickSortVisual(arr, 0, arr.size() - 1, 0);
    }
    
    // Quick sort with different pivot strategies
    enum class PivotStrategy {
        FIRST,
        LAST,
        MIDDLE,
        RANDOM,
        MEDIAN_OF_THREE
    };
    
    static void sortWithPivotStrategy(std::vector<int>& arr, PivotStrategy strategy) {
        quickSortWithStrategy(arr, 0, arr.size() - 1, strategy);
    }
    
    // Iterative quick sort (avoids recursion overhead)
    static void sortIterative(std::vector<int>& arr) {
        if (arr.empty()) return;
        
        std::stack<std::pair<int, int>> stack;
        stack.push({0, static_cast<int>(arr.size()) - 1});
        
        while (!stack.empty()) {
            auto [low, high] = stack.top();
            stack.pop();
            
            if (low < high) {
                int pi = lomutoPartition(arr, low, high);
                
                stack.push({low, pi - 1});
                stack.push({pi + 1, high});
            }
        }
    }
    
    // Hybrid quick sort (switches to insertion sort for small subarrays)
    static void sortHybrid(std::vector<int>& arr) {
        hybridQuickSort(arr, 0, arr.size() - 1);
    }
    
    // Three-way quick sort (handles duplicates efficiently)
    static void sortThreeWay(std::vector<int>& arr) {
        threeWayQuickSort(arr, 0, arr.size() - 1);
    }
    
    // Template version for any comparable type
    template<typename T>
    static void sortGeneric(std::vector<T>& arr) {
        quickSortGeneric(arr, 0, arr.size() - 1);
    }
    
    // Quick sort with custom comparator
    template<typename T, typename Compare>
    static void sortWithComparator(std::vector<T>& arr, Compare comp) {
        quickSortWithComparator(arr, 0, arr.size() - 1, comp);
    }
    
    // Quick select - find kth smallest element
    static int quickSelect(std::vector<int>& arr, int k) {
        if (k < 1 || k > arr.size()) return -1;
        return quickSelectHelper(arr, 0, arr.size() - 1, k - 1);
    }
    
    // Performance analysis with different pivot strategies
    static void performanceAnalysis(std::vector<int>& originalArr, const std::string& caseType) {
        std::cout << "Quick Sort Performance Analysis (" << caseType << "):\n";
        
        // Test different pivot strategies
        std::vector<PivotStrategy> strategies = {
            PivotStrategy::FIRST,
            PivotStrategy::LAST,
            PivotStrategy::MIDDLE,
            PivotStrategy::RANDOM,
            PivotStrategy::MEDIAN_OF_THREE
        };
        
        std::vector<std::string> strategyNames = {
            "First Element",
            "Last Element",
            "Middle Element",
            "Random Element",
            "Median of Three"
        };
        
        for (int i = 0; i < strategies.size(); i++) {
            std::vector<int> arr = originalArr;
            
            auto start = std::chrono::high_resolution_clock::now();
            sortWithPivotStrategy(arr, strategies[i]);
            auto end = std::chrono::high_resolution_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << std::left << std::setw(20) << strategyNames[i] 
                      << ": " << duration.count() << " microseconds\n";
        }
        std::cout << "\n";
    }

private:
    // Main recursive quick sort function
    static void quickSortRecursive(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = lomutoPartition(arr, low, high);
            
            quickSortRecursive(arr, low, pi - 1);
            quickSortRecursive(arr, pi + 1, high);
        }
    }
    
    // Quick sort with visualization
    static void quickSortVisual(std::vector<int>& arr, int low, int high, int depth) {
        if (low < high) {
            std::string indent(depth * 2, ' ');
            std::cout << indent << "Sorting subarray [" << low << ", " << high << "]: ";
            for (int i = low; i <= high; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << "\n";
            
            int pi = lomutoPartition(arr, low, high);
            
            std::cout << indent << "Pivot: " << arr[pi] << " at index " << pi << "\n";
            std::cout << indent << "After partition: ";
            for (int i = low; i <= high; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << "\n\n";
            
            quickSortVisual(arr, low, pi - 1, depth + 1);
            quickSortVisual(arr, pi + 1, high, depth + 1);
        }
    }
    
    // Quick sort with different pivot strategies
    static void quickSortWithStrategy(std::vector<int>& arr, int low, int high, PivotStrategy strategy) {
        if (low < high) {
            choosePivot(arr, low, high, strategy);
            int pi = lomutoPartition(arr, low, high);
            
            quickSortWithStrategy(arr, low, pi - 1, strategy);
            quickSortWithStrategy(arr, pi + 1, high, strategy);
        }
    }
    
    // Lomuto partition scheme
    static int lomutoPartition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
    // Hoare partition scheme (alternative)
    static int hoarePartition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[low];
        int i = low - 1;
        int j = high + 1;
        
        while (true) {
            do {
                i++;
            } while (arr[i] < pivot);
            
            do {
                j--;
            } while (arr[j] > pivot);
            
            if (i >= j) return j;
            std::swap(arr[i], arr[j]);
        }
    }
    
    // Choose pivot based on strategy
    static void choosePivot(std::vector<int>& arr, int low, int high, PivotStrategy strategy) {
        int pivotIndex = low;
        
        switch (strategy) {
            case PivotStrategy::FIRST:
                pivotIndex = low;
                break;
            case PivotStrategy::LAST:
                pivotIndex = high;
                break;
            case PivotStrategy::MIDDLE:
                pivotIndex = low + (high - low) / 2;
                break;
            case PivotStrategy::RANDOM: {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(low, high);
                pivotIndex = dis(gen);
                break;
            }
            case PivotStrategy::MEDIAN_OF_THREE: {
                int mid = low + (high - low) / 2;
                if (arr[mid] < arr[low]) std::swap(arr[low], arr[mid]);
                if (arr[high] < arr[low]) std::swap(arr[low], arr[high]);
                if (arr[high] < arr[mid]) std::swap(arr[mid], arr[high]);
                pivotIndex = mid;
                break;
            }
        }
        
        if (pivotIndex != high) {
            std::swap(arr[pivotIndex], arr[high]);
        }
    }
    
    // Hybrid quick sort with insertion sort for small subarrays
    static void hybridQuickSort(std::vector<int>& arr, int low, int high) {
        const int THRESHOLD = 10;
        
        if (high - low + 1 <= THRESHOLD) {
            insertionSort(arr, low, high);
        } else if (low < high) {
            int pi = lomutoPartition(arr, low, high);
            hybridQuickSort(arr, low, pi - 1);
            hybridQuickSort(arr, pi + 1, high);
        }
    }
    
    // Insertion sort for small subarrays
    static void insertionSort(std::vector<int>& arr, int low, int high) {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;
            
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    // Three-way partitioning for handling duplicates
    static void threeWayQuickSort(std::vector<int>& arr, int low, int high) {
        if (low >= high) return;
        
        int lt = low;      // arr[low..lt-1] < pivot
        int gt = high;     // arr[gt+1..high] > pivot
        int pivot = arr[low];
        int i = low;       // arr[lt..i-1] == pivot, arr[i..gt] unknown
        
        while (i <= gt) {
            if (arr[i] < pivot) {
                std::swap(arr[lt++], arr[i++]);
            } else if (arr[i] > pivot) {
                std::swap(arr[i], arr[gt--]);
            } else {
                i++;
            }
        }
        
        threeWayQuickSort(arr, low, lt - 1);
        threeWayQuickSort(arr, gt + 1, high);
    }
    
    // Generic template version
    template<typename T>
    static void quickSortGeneric(std::vector<T>& arr, int low, int high) {
        if (low < high) {
            int pi = partitionGeneric(arr, low, high);
            quickSortGeneric(arr, low, pi - 1);
            quickSortGeneric(arr, pi + 1, high);
        }
    }
    
    template<typename T>
    static int partitionGeneric(std::vector<T>& arr, int low, int high) {
        T pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
    // Quick sort with custom comparator
    template<typename T, typename Compare>
    static void quickSortWithComparator(std::vector<T>& arr, int low, int high, Compare comp) {
        if (low < high) {
            int pi = partitionWithComparator(arr, low, high, comp);
            quickSortWithComparator(arr, low, pi - 1, comp);
            quickSortWithComparator(arr, pi + 1, high, comp);
        }
    }
    
    template<typename T, typename Compare>
    static int partitionWithComparator(std::vector<T>& arr, int low, int high, Compare comp) {
        T pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (!comp(pivot, arr[j])) {  // arr[j] <= pivot
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
    // Quick select helper
    static int quickSelectHelper(std::vector<int>& arr, int low, int high, int k) {
        if (low == high) return arr[low];
        
        int pi = lomutoPartition(arr, low, high);
        
        if (k == pi) {
            return arr[k];
        } else if (k < pi) {
            return quickSelectHelper(arr, low, pi - 1, k);
        } else {
            return quickSelectHelper(arr, pi + 1, high, k);
        }
    }
    
    // Helper function to print array
    static void printArray(const std::vector<int>& arr, const std::string& label) {
        std::cout << label << ": [";
        for (int i = 0; i < arr.size(); i++) {
            std::cout << arr[i];
            if (i < arr.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
};

// Utility functions
void printArray(const std::vector<int>& arr, const std::string& label) {
    std::cout << label << ": [";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

std::vector<int> generateRandomArray(int size, int minVal = 1, int maxVal = 100) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minVal, maxVal);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    
    return arr;
}

std::vector<int> generateSortedArray(int size, bool ascending = true) {
    std::vector<int> arr(size);
    if (ascending) {
        std::iota(arr.begin(), arr.end(), 1);
    } else {
        std::iota(arr.rbegin(), arr.rend(), 1);
    }
    return arr;
}

std::vector<int> generateDuplicateArray(int size, int numUniqueValues = 5) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, numUniqueValues);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    
    return arr;
}

int main() {
    std::cout << "=== QUICK SORT ALGORITHM DEMONSTRATION ===\n\n";
    
    // Basic demonstration
    std::cout << "1. BASIC QUICK SORT:\n";
    std::vector<int> basicArray = {10, 7, 8, 9, 1, 5};
    printArray(basicArray, "Original Array");
    
    std::vector<int> sortedArray = basicArray;
    QuickSort::sort(sortedArray);
    printArray(sortedArray, "Sorted Array");
    std::cout << "\n";
    
    // Step-by-step visualization
    std::cout << "2. STEP-BY-STEP VISUALIZATION:\n";
    std::vector<int> visualArray = {3, 6, 8, 10, 1, 2, 1};
    QuickSort::sortWithVisualization(visualArray);
    std::cout << "\n";
    
    // Different pivot strategies
    std::cout << "3. DIFFERENT PIVOT STRATEGIES:\n";
    std::vector<int> pivotArray = {64, 34, 25, 12, 22, 11, 90};
    
    std::vector<std::string> strategyNames = {
        "First Element", "Last Element", "Middle Element", "Random Element", "Median of Three"
    };
    
    std::vector<QuickSort::PivotStrategy> strategies = {
        QuickSort::PivotStrategy::FIRST,
        QuickSort::PivotStrategy::LAST,
        QuickSort::PivotStrategy::MIDDLE,
        QuickSort::PivotStrategy::RANDOM,
        QuickSort::PivotStrategy::MEDIAN_OF_THREE
    };
    
    printArray(pivotArray, "Original Array");
    
    for (int i = 0; i < strategies.size(); i++) {
        std::vector<int> testArray = pivotArray;
        QuickSort::sortWithPivotStrategy(testArray, strategies[i]);
        std::cout << strategyNames[i] << " pivot: ";
        for (int val : testArray) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    
    // Iterative implementation
    std::cout << "4. ITERATIVE QUICK SORT:\n";
    std::vector<int> iterativeArray = {4, 2, 7, 1, 9, 3};
    printArray(iterativeArray, "Before Iterative Sort");
    QuickSort::sortIterative(iterativeArray);
    printArray(iterativeArray, "After Iterative Sort");
    std::cout << "\n";
    
    // Hybrid quick sort
    std::cout << "5. HYBRID QUICK SORT (with Insertion Sort for small subarrays):\n";
    std::vector<int> hybridArray = generateRandomArray(20, 1, 50);
    std::vector<int> hybridCopy = hybridArray;
    
    printArray(hybridArray, "Original Array");
    QuickSort::sortHybrid(hybridCopy);
    printArray(hybridCopy, "Hybrid Sorted Array");
    std::cout << "\n";
    
    // Three-way quick sort for arrays with many duplicates
    std::cout << "6. THREE-WAY QUICK SORT (efficient for duplicates):\n";
    std::vector<int> duplicateArray = {2, 1, 2, 1, 3, 2, 1, 3, 2, 1};
    printArray(duplicateArray, "Array with Duplicates");
    
    std::vector<int> threeWayCopy = duplicateArray;
    QuickSort::sortThreeWay(threeWayCopy);
    printArray(threeWayCopy, "Three-Way Sorted Array");
    std::cout << "\n";
    
    // Template usage with different data types
    std::cout << "7. GENERIC TEMPLATE SORTING:\n";
    
    // Character array
    std::vector<char> charArray = {'m', 'a', 'k', 'e', 'i', 't', 'q', 'u', 'i', 'c', 'k'};
    std::cout << "Character array before: [";
    for (int i = 0; i < charArray.size(); i++) {
        std::cout << charArray[i];
        if (i < charArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    QuickSort::sortGeneric(charArray);
    std::cout << "Character array after: [";
    for (int i = 0; i < charArray.size(); i++) {
        std::cout << charArray[i];
        if (i < charArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n\n";
    
    // Custom comparator (descending order)
    std::cout << "8. CUSTOM COMPARATOR (Descending Order):\n";
    std::vector<int> descArray = {5, 2, 8, 1, 9};
    printArray(descArray, "Original Array");
    
    QuickSort::sortWithComparator(descArray, [](int a, int b) { return a > b; });
    printArray(descArray, "Descending Sorted Array");
    std::cout << "\n";
    
    // Quick Select demonstration
    std::cout << "9. QUICK SELECT (Finding kth smallest element):\n";
    std::vector<int> selectArray = {7, 10, 4, 3, 20, 15};
    printArray(selectArray, "Original Array");
    
    for (int k = 1; k <= 3; k++) {
        std::vector<int> selectCopy = selectArray;
        int kthSmallest = QuickSort::quickSelect(selectCopy, k);
        std::cout << k << (k == 1 ? "st" : k == 2 ? "nd" : "rd") 
                  << " smallest element: " << kthSmallest << "\n";
    }
    std::cout << "\n";
    
    // Performance analysis
    std::cout << "10. PERFORMANCE ANALYSIS:\n";
    
    // Best/Average case (random array)
    std::vector<int> randomCase = generateRandomArray(10000);
    QuickSort::performanceAnalysis(randomCase, "Random Array");
    
    // Worst case (sorted array with first element as pivot)
    std::vector<int> worstCase = generateSortedArray(1000);
    std::cout << "Worst Case Performance (sorted array, size 1000):\n";
    auto start = std::chrono::high_resolution_clock::now();
    QuickSort::sortWithPivotStrategy(worstCase, QuickSort::PivotStrategy::FIRST);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "First Element Pivot: " << duration.count() << " microseconds\n";
    
    worstCase = generateSortedArray(1000);
    start = std::chrono::high_resolution_clock::now();
    QuickSort::sortWithPivotStrategy(worstCase, QuickSort::PivotStrategy::MEDIAN_OF_THREE);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Median of Three Pivot: " << duration.count() << " microseconds\n\n";
    
    // Arrays with many duplicates
    std::vector<int> manyDuplicates = generateDuplicateArray(5000, 10);
    std::cout << "Performance with Many Duplicates (size 5000, 10 unique values):\n";
    
    std::vector<int> regularCopy = manyDuplicates;
    start = std::chrono::high_resolution_clock::now();
    QuickSort::sort(regularCopy);
    end = std::chrono::high_resolution_clock::now();
    auto regularDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::vector<int> threeWayDuplicateCopy = manyDuplicates;
    start = std::chrono::high_resolution_clock::now();
    QuickSort::sortThreeWay(threeWayDuplicateCopy);
    end = std::chrono::high_resolution_clock::now();
    auto threeWayDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Regular Quick Sort: " << regularDuration.count() << " microseconds\n";
    std::cout << "Three-Way Quick Sort: " << threeWayDuration.count() << " microseconds\n";
    std::cout << "Improvement: " << (double)regularDuration.count() / threeWayDuration.count() << "x\n\n";
    
    // Real-world application example
    std::cout << "11. REAL-WORLD APPLICATION - Stock Price Analysis:\n";
    struct Stock {
        std::string symbol;
        double price;
        double changePercent;
        long long volume;
        
        bool operator<(const Stock& other) const {
            return price < other.price;
        }
    };
    
    std::vector<Stock> stocks = {
        {"AAPL", 150.25, 2.1, 50000000},
        {"GOOGL", 2800.50, -1.5, 25000000},
        {"MSFT", 300.75, 1.2, 35000000},
        {"AMZN", 3200.00, -0.8, 15000000},
        {"TSLA", 800.30, 5.5, 80000000}
    };
    
    std::cout << "Stocks before sorting by price:\n";
    std::cout << "Symbol\tPrice\t\tChange%\t\tVolume\n";
    std::cout << "─────────────────────────────────────────────────────────\n";
    for (const auto& stock : stocks) {
        std::cout << stock.symbol << "\t$" << std::fixed << std::setprecision(2) 
                  << stock.price << "\t\t" << stock.changePercent 
                  << "%\t\t" << stock.volume << "\n";
    }
    
    // Sort by price using quick sort
    QuickSort::sortGeneric(stocks);
    
    std::cout << "\nStocks after sorting by price (ascending):\n";
    std::cout << "Symbol\tPrice\t\tChange%\t\tVolume\n";
    std::cout << "─────────────────────────────────────────────────────────\n";
    for (const auto& stock : stocks) {
        std::cout << stock.symbol << "\t$" << std::fixed << std::setprecision(2) 
                  << stock.price << "\t\t" << stock.changePercent 
                  << "%\t\t" << stock.volume << "\n";
    }
    
    // Sort by volume (descending)
    QuickSort::sortWithComparator(stocks, [](const Stock& a, const Stock& b) {
        return a.volume > b.volume;
    });
    
    std::cout << "\nStocks after sorting by volume (descending):\n";
    std::cout << "Symbol\tPrice\t\tChange%\t\tVolume\n";
    std::cout << "─────────────────────────────────────────────────────────\n";
    for (const auto& stock : stocks) {
        std::cout << stock.symbol << "\t$" << std::fixed << std::setprecision(2) 
                  << stock.price << "\t\t" << stock.changePercent 
                  << "%\t\t" << stock.volume << "\n";
    }
    std::cout << "\n";
    
    std::cout << "=== QUICK SORT SUMMARY ===\n";
    std::cout << "Characteristics:\n";
    std::cout << "- Stable: Generally no (can be made stable with modifications)\n";
    std::cout << "- In-place: Yes (with optimal space usage)\n";
    std::cout << "- Adaptive: No (doesn't benefit from partially sorted data)\n";
    std::cout << "- Comparison-based: Yes\n";
    std::cout << "\nComplexity:\n";
    std::cout << "- Best Case: O(n log n) - when pivot divides array evenly\n";
    std::cout << "- Average Case: O(n log n)\n";
    std::cout << "- Worst Case: O(n²) - when pivot is always smallest or largest\n";
    std::cout << "- Space Complexity: O(log n) average, O(n) worst case (recursion stack)\n";
    std::cout << "\nAdvantages:\n";
    std::cout << "- Excellent average-case performance O(n log n)\n";
    std::cout << "- In-place sorting (minimal extra memory)\n";
    std::cout << "- Cache-efficient (good locality of reference)\n";
    std::cout << "- Practical and widely used\n";
    std::cout << "- Can be optimized for specific scenarios\n";
    std::cout << "\nDisadvantages:\n";
    std::cout << "- O(n²) worst-case time complexity\n";
    std::cout << "- Not stable (without modifications)\n";
    std::cout << "- Performance depends on pivot selection\n";
    std::cout << "- Recursive implementation uses stack space\n";
    std::cout << "\nOptimizations:\n";
    std::cout << "- Median-of-three pivot selection\n";
    std::cout << "- Random pivot selection\n";
    std::cout << "- Three-way partitioning for duplicates\n";
    std::cout << "- Hybrid approach (insertion sort for small subarrays)\n";
    std::cout << "- Iterative implementation to reduce stack usage\n";
    std::cout << "\nBest Use Cases:\n";
    std::cout << "- General-purpose sorting\n";
    std::cout << "- Large datasets with good average performance\n";
    std::cout << "- When memory is limited\n";
    std::cout << "- Systems programming\n";
    std::cout << "- Quick selection problems (finding kth element)\n";
    
    return 0;
}
