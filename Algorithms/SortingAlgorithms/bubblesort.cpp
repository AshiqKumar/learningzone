/*
 * Bubble Sort Algorithm Implementation
 * 
 * Bubble Sort:
 * - Simple comparison-based sorting algorithm
 * - Repeatedly swaps adjacent elements if they're in wrong order
 * - Time Complexity: O(n²) average and worst case, O(n) best case
 * - Space Complexity: O(1)
 * - Stable: Yes (maintains relative order of equal elements)
 * - In-place: Yes
 * 
 * Applications:
 * - Educational purposes (algorithm learning)
 * - Small datasets
 * - Nearly sorted arrays (optimized version)
 * - When simplicity is more important than efficiency
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <random>

class BubbleSort {
public:
    // Basic bubble sort implementation
    static void sort(std::vector<int>& arr) {
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    
    // Optimized bubble sort (stops early if array becomes sorted)
    static void sortOptimized(std::vector<int>& arr) {
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            
            // If no swapping occurred, array is sorted
            if (!swapped) {
                std::cout << "Early termination at iteration " << i + 1 << "\n";
                break;
            }
        }
    }
    
    // Bubble sort with step-by-step visualization
    static void sortWithVisualization(std::vector<int>& arr) {
        int n = arr.size();
        std::cout << "Bubble Sort Step-by-Step:\n";
        printArray(arr, "Initial");
        
        for (int i = 0; i < n - 1; i++) {
            std::cout << "\nIteration " << i + 1 << ":\n";
            bool swapped = false;
            
            for (int j = 0; j < n - i - 1; j++) {
                std::cout << "Comparing arr[" << j << "]=" << arr[j] 
                          << " and arr[" << j + 1 << "]=" << arr[j + 1];
                
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    std::cout << " -> Swap occurred";
                    swapped = true;
                }
                std::cout << "\n";
            }
            
            printArray(arr, "After iteration " + std::to_string(i + 1));
            
            if (!swapped) {
                std::cout << "No swaps needed. Array is sorted!\n";
                break;
            }
        }
    }
    
    // Bubble sort with comparison and swap counting
    static std::pair<int, int> sortWithCounts(std::vector<int>& arr) {
        int n = arr.size();
        int comparisons = 0;
        int swaps = 0;
        
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            
            for (int j = 0; j < n - i - 1; j++) {
                comparisons++;
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swaps++;
                    swapped = true;
                }
            }
            
            if (!swapped) break;
        }
        
        return {comparisons, swaps};
    }
    
    // Recursive bubble sort
    static void sortRecursive(std::vector<int>& arr, int n = -1) {
        if (n == -1) n = arr.size();
        
        // Base case
        if (n == 1) return;
        
        // One pass of bubble sort
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
            }
        }
        
        // Largest element is now at end, so recur for remaining elements
        sortRecursive(arr, n - 1);
    }
    
    // Template version for any comparable type
    template<typename T>
    static void sortGeneric(std::vector<T>& arr) {
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            
            if (!swapped) break;
        }
    }
    
    // Bubble sort with custom comparator
    template<typename T, typename Compare>
    static void sortWithComparator(std::vector<T>& arr, Compare comp) {
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            
            for (int j = 0; j < n - i - 1; j++) {
                if (comp(arr[j + 1], arr[j])) {  // comp(a, b) returns true if a should come before b
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            
            if (!swapped) break;
        }
    }
    
    // Cocktail shaker sort (bidirectional bubble sort)
    static void cocktailShakerSort(std::vector<int>& arr) {
        bool swapped = true;
        int start = 0;
        int end = arr.size() - 1;
        
        while (swapped) {
            swapped = false;
            
            // Forward pass
            for (int i = start; i < end; i++) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
            
            if (!swapped) break;
            
            end--;
            swapped = false;
            
            // Backward pass
            for (int i = end - 1; i >= start; i--) {
                if (arr[i] > arr[i + 1]) {
                    std::swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
            
            start++;
        }
    }
    
    // Performance analysis
    static void performanceAnalysis(std::vector<int>& arr, const std::string& caseType) {
        std::vector<int> arrCopy = arr;
        
        auto start = std::chrono::high_resolution_clock::now();
        auto counts = sortWithCounts(arrCopy);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Bubble Sort Performance (" << caseType << "):\n";
        std::cout << "Array size: " << arr.size() << "\n";
        std::cout << "Comparisons: " << counts.first << "\n";
        std::cout << "Swaps: " << counts.second << "\n";
        std::cout << "Time taken: " << duration.count() << " microseconds\n";
        std::cout << "Theoretical comparisons (worst case): " << (arr.size() * (arr.size() - 1)) / 2 << "\n\n";
    }

private:
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

std::vector<int> generateNearlySortedArray(int size, int swaps = 2) {
    std::vector<int> arr = generateSortedArray(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    
    for (int i = 0; i < swaps; i++) {
        int idx1 = dis(gen);
        int idx2 = dis(gen);
        std::swap(arr[idx1], arr[idx2]);
    }
    
    return arr;
}

int main() {
    std::cout << "=== BUBBLE SORT ALGORITHM DEMONSTRATION ===\n\n";
    
    // Basic demonstration
    std::cout << "1. BASIC BUBBLE SORT:\n";
    std::vector<int> basicArray = {64, 34, 25, 12, 22, 11, 90};
    printArray(basicArray, "Original Array");
    
    std::vector<int> sortedArray = basicArray;
    BubbleSort::sort(sortedArray);
    printArray(sortedArray, "Sorted Array");
    std::cout << "\n";
    
    // Step-by-step visualization
    std::cout << "2. STEP-BY-STEP VISUALIZATION:\n";
    std::vector<int> visualArray = {5, 2, 8, 1, 9};
    BubbleSort::sortWithVisualization(visualArray);
    std::cout << "\n";
    
    // Optimized bubble sort demonstration
    std::cout << "3. OPTIMIZED BUBBLE SORT (Early Termination):\n";
    std::vector<int> nearlyArray = {1, 2, 5, 3, 4};  // Nearly sorted
    printArray(nearlyArray, "Nearly Sorted Array");
    std::cout << "Using optimized bubble sort:\n";
    BubbleSort::sortOptimized(nearlyArray);
    printArray(nearlyArray, "Final Result");
    std::cout << "\n";
    
    // Recursive implementation
    std::cout << "4. RECURSIVE BUBBLE SORT:\n";
    std::vector<int> recursiveArray = {3, 7, 1, 4, 6};
    printArray(recursiveArray, "Before Recursive Sort");
    BubbleSort::sortRecursive(recursiveArray);
    printArray(recursiveArray, "After Recursive Sort");
    std::cout << "\n";
    
    // Template usage with different data types
    std::cout << "5. GENERIC TEMPLATE SORTING:\n";
    
    // Double array
    std::vector<double> doubleArray = {3.7, 1.2, 4.9, 2.1, 8.5};
    std::cout << "Double array before: [";
    for (int i = 0; i < doubleArray.size(); i++) {
        std::cout << doubleArray[i];
        if (i < doubleArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    BubbleSort::sortGeneric(doubleArray);
    std::cout << "Double array after: [";
    for (int i = 0; i < doubleArray.size(); i++) {
        std::cout << doubleArray[i];
        if (i < doubleArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    // String array
    std::vector<std::string> stringArray = {"banana", "apple", "cherry", "date"};
    std::cout << "String array before: [";
    for (int i = 0; i < stringArray.size(); i++) {
        std::cout << stringArray[i];
        if (i < stringArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    BubbleSort::sortGeneric(stringArray);
    std::cout << "String array after: [";
    for (int i = 0; i < stringArray.size(); i++) {
        std::cout << stringArray[i];
        if (i < stringArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n\n";
    
    // Custom comparator (descending order)
    std::cout << "6. CUSTOM COMPARATOR (Descending Order):\n";
    std::vector<int> descArray = {5, 2, 8, 1, 9, 3};
    printArray(descArray, "Original Array");
    
    BubbleSort::sortWithComparator(descArray, [](int a, int b) { return a > b; });
    printArray(descArray, "Descending Sorted Array");
    std::cout << "\n";
    
    // Cocktail shaker sort
    std::cout << "7. COCKTAIL SHAKER SORT (Bidirectional Bubble Sort):\n";
    std::vector<int> cocktailArray = {5, 1, 4, 2, 8, 0, 2};
    printArray(cocktailArray, "Before Cocktail Sort");
    BubbleSort::cocktailShakerSort(cocktailArray);
    printArray(cocktailArray, "After Cocktail Sort");
    std::cout << "\n";
    
    // Performance analysis
    std::cout << "8. PERFORMANCE ANALYSIS:\n";
    
    // Best case (already sorted)
    std::vector<int> bestCase = generateSortedArray(1000);
    BubbleSort::performanceAnalysis(bestCase, "Best Case - Already Sorted");
    
    // Worst case (reverse sorted)
    std::vector<int> worstCase = generateSortedArray(1000, false);
    BubbleSort::performanceAnalysis(worstCase, "Worst Case - Reverse Sorted");
    
    // Average case (random)
    std::vector<int> averageCase = generateRandomArray(1000);
    BubbleSort::performanceAnalysis(averageCase, "Average Case - Random");
    
    // Nearly sorted
    std::vector<int> nearlySorted = generateNearlySortedArray(1000, 10);
    BubbleSort::performanceAnalysis(nearlySorted, "Nearly Sorted");
    
    // Real-world application example
    std::cout << "9. REAL-WORLD APPLICATION - Student Grades:\n";
    struct Student {
        std::string name;
        int grade;
        
        bool operator>(const Student& other) const {
            return grade > other.grade;  // Sort by grade
        }
    };
    
    std::vector<Student> students = {
        {"Alice", 85},
        {"Bob", 92},
        {"Charlie", 78},
        {"David", 88},
        {"Eve", 95}
    };
    
    std::cout << "Students before sorting by grade:\n";
    for (const auto& student : students) {
        std::cout << student.name << ": " << student.grade << "\n";
    }
    
    // Sort using custom comparator
    BubbleSort::sortWithComparator(students, [](const Student& a, const Student& b) {
        return a.grade < b.grade;  // Ascending order by grade
    });
    
    std::cout << "\nStudents after sorting by grade (ascending):\n";
    for (const auto& student : students) {
        std::cout << student.name << ": " << student.grade << "\n";
    }
    std::cout << "\n";
    
    // Complexity analysis demonstration
    std::cout << "10. COMPLEXITY ANALYSIS:\n";
    std::cout << "Time Complexity Analysis for different array sizes:\n";
    std::cout << "Size\tComparisons (Actual)\tComparisons (Theoretical O(n²))\tRatio\n";
    std::cout << "────────────────────────────────────────────────────────────────────\n";
    
    for (int size : {10, 50, 100, 500}) {
        std::vector<int> testArray = generateRandomArray(size);
        auto counts = BubbleSort::sortWithCounts(testArray);
        int theoretical = (size * (size - 1)) / 2;
        double ratio = (double)counts.first / theoretical;
        
        std::cout << size << "\t" << counts.first << "\t\t\t" << theoretical 
                  << "\t\t\t" << std::fixed << std::setprecision(3) << ratio << "\n";
    }
    
    std::cout << "\n=== BUBBLE SORT SUMMARY ===\n";
    std::cout << "Characteristics:\n";
    std::cout << "- Stable: Yes (maintains relative order of equal elements)\n";
    std::cout << "- In-place: Yes (requires only O(1) extra memory)\n";
    std::cout << "- Adaptive: Yes (performs better on nearly sorted arrays)\n";
    std::cout << "- Comparison-based: Yes\n";
    std::cout << "\nComplexity:\n";
    std::cout << "- Best Case: O(n) - when array is already sorted (optimized version)\n";
    std::cout << "- Average Case: O(n²)\n";
    std::cout << "- Worst Case: O(n²) - when array is reverse sorted\n";
    std::cout << "- Space Complexity: O(1)\n";
    std::cout << "\nAdvantages:\n";
    std::cout << "- Simple to understand and implement\n";
    std::cout << "- No additional memory space needed\n";
    std::cout << "- Stable sorting algorithm\n";
    std::cout << "- Can detect if array is already sorted (optimized version)\n";
    std::cout << "\nDisadvantages:\n";
    std::cout << "- Poor time complexity O(n²)\n";
    std::cout << "- Not suitable for large datasets\n";
    std::cout << "- More writes compared to selection sort\n";
    std::cout << "\nBest Use Cases:\n";
    std::cout << "- Educational purposes (learning sorting concepts)\n";
    std::cout << "- Very small datasets\n";
    std::cout << "- Nearly sorted arrays (with optimization)\n";
    std::cout << "- When simplicity is more important than efficiency\n";
    
    return 0;
}
