/*
 * Advanced Searching Algorithms Implementation
 *
 * This file contains multiple advanced searching algorithms:
 * 1. Exponential Search (Doubling Search)
 * 2. Ternary Search
 * 3. Jump Search (Block Search)
 * 4. Fibonacci Search
 *
 * Algorithm         Best Case   Worst Case    Works On         Key Feature
 * Exponential       O(1)        O(log i)      Sorted arrays    Fast range finding + binary search
 * Ternary           O(log₃ n)   O(log₃ n)     Unimodal arrays  Divides into 3 parts
 * Jump              O(√n)       O(√n)         Sorted arrays    Block-wise search
 * Fibonacci         O(log n)    O(log n)      Sorted arrays    Uses Fibonacci sequence
 *
 * Each algorithm has different characteristics and use cases.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <string>

class AdvancedSearchAlgorithms {
public:
    // EXPONENTIAL SEARCH
    // Time Complexity: O(log n)
    // Best for: Unbounded/infinite arrays, when size is unknown
    static int exponentialSearch(const std::vector<int>& arr, int target) {
        int n = arr.size();
        if (n == 0) return -1;
        
        // If element is at first position
        if (arr[0] == target) return 0;
        
        // Find range for binary search by repeated doubling
        int bound = 1;
        while (bound < n && arr[bound] < target) {
            bound *= 2;
        }
        
        // Perform binary search in found range
        return binarySearch(arr, target, bound / 2, std::min(bound, n - 1));
    }
    
    static int exponentialSearchWithSteps(const std::vector<int>& arr, int target) {
        std::cout << "Exponential Search steps for target " << target << ":\n";
        
        int n = arr.size();
        if (n == 0) return -1;
        
        if (arr[0] == target) {
            std::cout << "Found at index 0\n";
            return 0;
        }
        
        int bound = 1;
        int step = 1;
        std::cout << "Step " << step << ": Checking bound " << bound << ", arr[" << bound << "]=" << arr[bound];
        
        while (bound < n && arr[bound] < target) {
            std::cout << " -> Too small, doubling bound\n";
            bound *= 2;
            step++;
            if (bound < n) {
                std::cout << "Step " << step << ": Checking bound " << bound << ", arr[" << bound << "]=" << arr[std::min(bound, n-1)];
            }
        }
        
        std::cout << " -> Found range [" << bound/2 << ", " << std::min(bound, n-1) << "]\n";
        std::cout << "Performing binary search in range...\n";
        
        return binarySearch(arr, target, bound / 2, std::min(bound, n - 1));
    }
    
    // TERNARY SEARCH
    // Time Complexity: O(log₃ n)
    // Best for: Unimodal functions, finding maximum/minimum
    static int ternarySearch(const std::vector<int>& arr, int target) {
        return ternarySearchRecursive(arr, target, 0, arr.size() - 1);
    }
    
    static int ternarySearchRecursive(const std::vector<int>& arr, int target, int left, int right) {
        if (left > right) return -1;
        
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        if (arr[mid1] == target) return mid1;
        if (arr[mid2] == target) return mid2;
        
        if (target < arr[mid1]) {
            return ternarySearchRecursive(arr, target, left, mid1 - 1);
        } else if (target > arr[mid2]) {
            return ternarySearchRecursive(arr, target, mid2 + 1, right);
        } else {
            return ternarySearchRecursive(arr, target, mid1 + 1, mid2 - 1);
        }
    }
    
    static int ternarySearchWithSteps(const std::vector<int>& arr, int target, int left, int right, int step = 1) {
        if (left > right) {
            std::cout << "Range exhausted. Element not found.\n";
            return -1;
        }
        
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        std::cout << "Step " << step << ": Range [" << left << ", " << right << "], mid1=" << mid1 
                  << " (arr[mid1]=" << arr[mid1] << "), mid2=" << mid2 << " (arr[mid2]=" << arr[mid2] << ")";
        
        if (arr[mid1] == target) {
            std::cout << " -> Found at mid1!\n";
            return mid1;
        }
        if (arr[mid2] == target) {
            std::cout << " -> Found at mid2!\n";
            return mid2;
        }
        
        if (target < arr[mid1]) {
            std::cout << " -> Search left third\n";
            return ternarySearchWithSteps(arr, target, left, mid1 - 1, step + 1);
        } else if (target > arr[mid2]) {
            std::cout << " -> Search right third\n";
            return ternarySearchWithSteps(arr, target, mid2 + 1, right, step + 1);
        } else {
            std::cout << " -> Search middle third\n";
            return ternarySearchWithSteps(arr, target, mid1 + 1, mid2 - 1, step + 1);
        }
    }
    
    // Find maximum in unimodal array using ternary search
    static int findMaximumUnimodal(const std::vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (right - left > 2) {
            int mid1 = left + (right - left) / 3;
            int mid2 = right - (right - left) / 3;
            
            if (arr[mid1] < arr[mid2]) {
                left = mid1;
            } else {
                right = mid2;
            }
        }
        
        // Check remaining elements
        int maxIndex = left;
        for (int i = left + 1; i <= right; i++) {
            if (arr[i] > arr[maxIndex]) {
                maxIndex = i;
            }
        }
        
        return maxIndex;
    }
    
    // JUMP SEARCH (Block Search)
    // Time Complexity: O(√n)
    // Best for: Sorted arrays when binary search overhead is concern
    static int jumpSearch(const std::vector<int>& arr, int target) {
        int n = arr.size();
        int jump = std::sqrt(n);
        int prev = 0;
        
        // Find block where element is present
        while (arr[std::min(jump, n) - 1] < target) {
            prev = jump;
            jump += std::sqrt(n);
            if (prev >= n) return -1;
        }
        
        // Linear search in identified block
        while (arr[prev] < target) {
            prev++;
            if (prev == std::min(jump, n)) return -1;
        }
        
        if (arr[prev] == target) return prev;
        return -1;
    }
    
    static int jumpSearchWithSteps(const std::vector<int>& arr, int target) {
        std::cout << "Jump Search steps for target " << target << ":\n";
        
        int n = arr.size();
        int jump = std::sqrt(n);
        int prev = 0;
        int step = 1;
        
        std::cout << "Block size (√n): " << jump << "\n";
        
        // Find block where element is present
        while (arr[std::min(jump, n) - 1] < target) {
            std::cout << "Step " << step << ": Checking block ending at index " << std::min(jump, n) - 1 
                      << ", value=" << arr[std::min(jump, n) - 1] << " -> Jump to next block\n";
            prev = jump;
            jump += std::sqrt(n);
            step++;
            if (prev >= n) {
                std::cout << "Reached end of array. Element not found.\n";
                return -1;
            }
        }
        
        std::cout << "Step " << step << ": Found potential block [" << prev << ", " << std::min(jump, n) - 1 << "]\n";
        std::cout << "Performing linear search in block...\n";
        
        // Linear search in identified block
        int linearStep = 1;
        while (arr[prev] < target) {
            std::cout << "Linear step " << linearStep << ": arr[" << prev << "]=" << arr[prev] << " -> Continue\n";
            prev++;
            linearStep++;
            if (prev == std::min(jump, n)) {
                std::cout << "Block exhausted. Element not found.\n";
                return -1;
            }
        }
        
        if (arr[prev] == target) {
            std::cout << "Found at index " << prev << "!\n";
            return prev;
        }
        
        std::cout << "Element not found.\n";
        return -1;
    }
    
    // FIBONACCI SEARCH
    // Time Complexity: O(log n)
    // Best for: Arrays where division is expensive
    static int fibonacciSearch(const std::vector<int>& arr, int target) {
        int n = arr.size();
        
        // Initialize fibonacci numbers
        int fibM2 = 0;    // (m-2)'th Fibonacci number
        int fibM1 = 1;    // (m-1)'th Fibonacci number
        int fibM = fibM2 + fibM1;  // m'th Fibonacci number
        
        // Find smallest fibonacci number greater than or equal to n
        while (fibM < n) {
            fibM2 = fibM1;
            fibM1 = fibM;
            fibM = fibM2 + fibM1;
        }
        
        int offset = -1;
        
        while (fibM > 1) {
            // Check if fibM2 is a valid location
            int i = std::min(offset + fibM2, n - 1);
            
            if (arr[i] < target) {
                fibM = fibM1;
                fibM1 = fibM2;
                fibM2 = fibM - fibM1;
                offset = i;
            } else if (arr[i] > target) {
                fibM = fibM2;
                fibM1 = fibM1 - fibM2;
                fibM2 = fibM - fibM1;
            } else {
                return i;
            }
        }
        
        // Check last element
        if (fibM1 && offset + 1 < n && arr[offset + 1] == target) {
            return offset + 1;
        }
        
        return -1;
    }

private:
    // Helper function for binary search
    static int binarySearch(const std::vector<int>& arr, int target, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) return mid;
            else if (arr[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
};

// Utility functions
void printArray(const std::vector<int>& arr, const std::string& label, int maxElements = 20) {
    std::cout << label << ": [";
    for (int i = 0; i < std::min(maxElements, static_cast<int>(arr.size())); i++) {
        std::cout << arr[i];
        if (i < std::min(maxElements, static_cast<int>(arr.size())) - 1) std::cout << ", ";
    }
    if (arr.size() > maxElements) std::cout << "...";
    std::cout << "] (size: " << arr.size() << ")\n";
}

void performanceComparison(const std::vector<int>& arr, int target) {
    std::cout << "Performance comparison for target " << target << ":\n";
    
    // Exponential Search
    auto start = std::chrono::high_resolution_clock::now();
    int expResult = AdvancedSearchAlgorithms::exponentialSearch(arr, target);
    auto end = std::chrono::high_resolution_clock::now();
    auto expTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    // Ternary Search
    start = std::chrono::high_resolution_clock::now();
    int ternResult = AdvancedSearchAlgorithms::ternarySearch(arr, target);
    end = std::chrono::high_resolution_clock::now();
    auto ternTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    // Jump Search
    start = std::chrono::high_resolution_clock::now();
    int jumpResult = AdvancedSearchAlgorithms::jumpSearch(arr, target);
    end = std::chrono::high_resolution_clock::now();
    auto jumpTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    // Fibonacci Search
    start = std::chrono::high_resolution_clock::now();
    int fibResult = AdvancedSearchAlgorithms::fibonacciSearch(arr, target);
    end = std::chrono::high_resolution_clock::now();
    auto fibTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "Exponential Search: " << (expResult != -1 ? "Found at " + std::to_string(expResult) : "Not found") 
              << " (" << expTime.count() << " ns)\n";
    std::cout << "Ternary Search: " << (ternResult != -1 ? "Found at " + std::to_string(ternResult) : "Not found") 
              << " (" << ternTime.count() << " ns)\n";
    std::cout << "Jump Search: " << (jumpResult != -1 ? "Found at " + std::to_string(jumpResult) : "Not found") 
              << " (" << jumpTime.count() << " ns)\n";
    std::cout << "Fibonacci Search: " << (fibResult != -1 ? "Found at " + std::to_string(fibResult) : "Not found") 
              << " (" << fibTime.count() << " ns)\n\n";
}

int main() {
    std::cout << "=== ADVANCED SEARCHING ALGORITHMS DEMONSTRATION ===\n\n";
    
    // Test data
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39};
    printArray(arr, "Test Array");
    std::cout << "\n";
    
    // 1. EXPONENTIAL SEARCH
    std::cout << "1. EXPONENTIAL SEARCH DEMONSTRATION:\n";
    std::cout << "Best for: Unbounded arrays, when array size is unknown\n";
    std::cout << "Time Complexity: O(log n)\n\n";
    
    int target1 = 25;
    int expResult = AdvancedSearchAlgorithms::exponentialSearchWithSteps(arr, target1);
    std::cout << "Result: " << (expResult != -1 ? "Found at index " + std::to_string(expResult) : "Not found") << "\n\n";
    
    // 2. TERNARY SEARCH
    std::cout << "2. TERNARY SEARCH DEMONSTRATION:\n";
    std::cout << "Best for: Sorted arrays, finding extrema in unimodal functions\n";
    std::cout << "Time Complexity: O(log₃ n)\n\n";
    
    int target2 = 17;
    std::cout << "Ternary Search steps for target " << target2 << ":\n";
    int ternResult = AdvancedSearchAlgorithms::ternarySearchWithSteps(arr, target2, 0, arr.size() - 1);
    std::cout << "Result: " << (ternResult != -1 ? "Found at index " + std::to_string(ternResult) : "Not found") << "\n\n";
    
    // Ternary search for finding maximum in unimodal array
    std::cout << "Finding maximum in unimodal array:\n";
    std::vector<int> unimodal = {1, 3, 8, 12, 4, 2};
    printArray(unimodal, "Unimodal Array");
    int maxIndex = AdvancedSearchAlgorithms::findMaximumUnimodal(unimodal);
    std::cout << "Maximum element: " << unimodal[maxIndex] << " at index " << maxIndex << "\n\n";
    
    // 3. JUMP SEARCH
    std::cout << "3. JUMP SEARCH DEMONSTRATION:\n";
    std::cout << "Best for: Sorted arrays when binary search overhead is a concern\n";
    std::cout << "Time Complexity: O(√n)\n\n";
    
    int target3 = 23;
    int jumpResult = AdvancedSearchAlgorithms::jumpSearchWithSteps(arr, target3);
    std::cout << "Result: " << (jumpResult != -1 ? "Found at index " + std::to_string(jumpResult) : "Not found") << "\n\n";
    
    // 4. FIBONACCI SEARCH
    std::cout << "4. FIBONACCI SEARCH DEMONSTRATION:\n";
    std::cout << "Best for: Arrays where division operation is expensive\n";
    std::cout << "Time Complexity: O(log n)\n\n";
    
    int target4 = 29;
    int fibResult = AdvancedSearchAlgorithms::fibonacciSearch(arr, target4);
    std::cout << "Fibonacci Search for " << target4 << ": ";
    std::cout << (fibResult != -1 ? "Found at index " + std::to_string(fibResult) : "Not found") << "\n\n";
    
    // 5. PERFORMANCE COMPARISON
    std::cout << "5. PERFORMANCE COMPARISON:\n";
    
    // Small array
    performanceComparison(arr, 25);
    
    // Large array
    std::vector<int> largeArr(10000);
    std::iota(largeArr.begin(), largeArr.end(), 1);
    std::cout << "Large array performance (size: " << largeArr.size() << "):\n";
    performanceComparison(largeArr, 7500);
    
    // Very large array
    std::vector<int> veryLargeArr(1000000);
    std::iota(veryLargeArr.begin(), veryLargeArr.end(), 1);
    std::cout << "Very large array performance (size: " << veryLargeArr.size() << "):\n";
    performanceComparison(veryLargeArr, 750000);
    
    // 6. REAL-WORLD APPLICATIONS
    std::cout << "6. REAL-WORLD APPLICATIONS:\n\n";
    
    // Exponential search in log files (unbounded search)
    std::cout << "A. Exponential Search - Log File Analysis:\n";
    std::cout << "Scenario: Searching in continuously growing log files\n";
    std::vector<int> logTimestamps = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200};
    printArray(logTimestamps, "Log Timestamps");
    int searchTime = 700;
    int logResult = AdvancedSearchAlgorithms::exponentialSearch(logTimestamps, searchTime);
    std::cout << "Searching for timestamp " << searchTime << ": ";
    std::cout << (logResult != -1 ? "Found at position " + std::to_string(logResult) : "Not found") << "\n\n";
    
    // Jump search in database index
    std::cout << "B. Jump Search - Database Index:\n";
    std::cout << "Scenario: Searching in sorted database index blocks\n";
    std::vector<int> dbIndex = {1001, 1005, 1010, 1015, 1020, 1025, 1030, 1035, 1040, 1045, 1050};
    printArray(dbIndex, "Database Index");
    int recordId = 1030;
    int dbResult = AdvancedSearchAlgorithms::jumpSearch(dbIndex, recordId);
    std::cout << "Searching for record ID " << recordId << ": ";
    std::cout << (dbResult != -1 ? "Found at index " + std::to_string(dbResult) : "Not found") << "\n\n";
    
    // Ternary search for optimization
    std::cout << "C. Ternary Search - Function Optimization:\n";
    std::cout << "Scenario: Finding maximum profit point in business function\n";
    std::vector<int> profitFunction = {10, 25, 45, 70, 90, 95, 85, 60, 30, 5};  // Unimodal
    printArray(profitFunction, "Profit Function Values");
    int optimalIndex = AdvancedSearchAlgorithms::findMaximumUnimodal(profitFunction);
    std::cout << "Optimal point: Index " << optimalIndex << ", Profit = " << profitFunction[optimalIndex] << "\n\n";
    
    // Algorithm selection guide
    std::cout << "7. ALGORITHM SELECTION GUIDE:\n";
    std::cout << "┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ Algorithm        │ Time Complexity │ Best Use Cases              │\n";
    std::cout << "├─────────────────────────────────────────────────────────────────┤\n";
    std::cout << "│ Exponential      │ O(log n)        │ Unbounded arrays            │\n";
    std::cout << "│ Ternary          │ O(log₃ n)       │ Unimodal functions          │\n";
    std::cout << "│ Jump            │ O(√n)           │ Block-based data            │\n";
    std::cout << "│ Fibonacci        │ O(log n)        │ Division-expensive systems  │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────┘\n\n";
    
    std::cout << "=== ADVANCED SEARCHING ALGORITHMS SUMMARY ===\n";
    
    std::cout << "\n1. EXPONENTIAL SEARCH:\n";
    std::cout << "   Advantages: Works with unbounded arrays, O(log n) complexity\n";
    std::cout << "   Best for: Growing datasets, infinite streams\n";
    std::cout << "   Use cases: Log files, streaming data, unbounded searches\n";
    
    std::cout << "\n2. TERNARY SEARCH:\n";
    std::cout << "   Advantages: Divides search space into three parts\n";
    std::cout << "   Best for: Finding extrema in unimodal functions\n";
    std::cout << "   Use cases: Optimization problems, peak finding\n";
    
    std::cout << "\n3. JUMP SEARCH:\n";
    std::cout << "   Advantages: Simple, O(√n) complexity, block-based\n";
    std::cout << "   Best for: When linear search is too slow, binary search overhead is high\n";
    std::cout << "   Use cases: Database indices, block storage systems\n";
    
    std::cout << "\n4. FIBONACCI SEARCH:\n";
    std::cout << "   Advantages: Uses addition instead of division, O(log n)\n";
    std::cout << "   Best for: Systems where division is expensive\n";
    std::cout << "   Use cases: Embedded systems, processors without division units\n";
    
    return 0;
}
