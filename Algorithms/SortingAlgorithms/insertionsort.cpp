/*
 * Insertion Sort and Variants Implementation
 * 
 * This file contains:
 * 1. Basic Insertion Sort
 * 2. Binary Insertion Sort
 * 3. Shell Sort (Shellsort) - advanced variant
 * 4. Tim Sort concepts (hybrid approach)
 * 
 * These algorithms are particularly effective for small arrays
 * and nearly sorted data
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <random>
#include <iomanip>
#include <cmath>

class InsertionSortAlgorithms {
public:
    // BASIC INSERTION SORT
    // Time Complexity: O(n²) worst/average, O(n) best
    // Space Complexity: O(1)
    // Stable: Yes
    static void insertionSort(std::vector<int>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            int key = arr[i];
            int j = i - 1;
            
            // Move elements greater than key one position ahead
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    static void insertionSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Insertion Sort Step-by-Step:\n";
        printArray(arr, "Initial Array");
        
        for (int i = 1; i < arr.size(); i++) {
            int key = arr[i];
            std::cout << "\nStep " << i << ": Inserting " << key << " from position " << i << "\n";
            
            // Show the sorted portion and current element
            std::cout << "Sorted portion: [";
            for (int k = 0; k < i; k++) {
                std::cout << arr[k];
                if (k < i - 1) std::cout << ", ";
            }
            std::cout << "], Current element: " << key << "\n";
            
            int j = i - 1;
            int shifts = 0;
            
            // Move elements and show each shift
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                shifts++;
                std::cout << "  Shift " << shifts << ": Moving " << arr[j] << " to position " << (j + 1) << "\n";
                j--;
            }
            
            arr[j + 1] = key;
            std::cout << "  Placing " << key << " at position " << (j + 1) << "\n";
            
            // Show array after this step
            std::cout << "After step " << i << ": ";
            printArrayInline(arr);
        }
    }
    
    // BINARY INSERTION SORT
    // Uses binary search to find insertion position
    // Time Complexity: O(n²) still due to shifting, but fewer comparisons
    static void binaryInsertionSort(std::vector<int>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            int key = arr[i];
            int left = 0, right = i;
            
            // Binary search for insertion position
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (arr[mid] > key) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            
            // Shift elements to make room
            for (int j = i - 1; j >= left; j--) {
                arr[j + 1] = arr[j];
            }
            arr[left] = key;
        }
    }
    
    static void binaryInsertionSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Binary Insertion Sort Step-by-Step:\n";
        printArray(arr, "Initial Array");
        
        for (int i = 1; i < arr.size(); i++) {
            int key = arr[i];
            std::cout << "\nStep " << i << ": Inserting " << key << " using binary search\n";
            
            int left = 0, right = i;
            int comparisons = 0;
            
            // Binary search for insertion position
            while (left < right) {
                int mid = left + (right - left) / 2;
                comparisons++;
                std::cout << "  Binary search: comparing with arr[" << mid << "] = " << arr[mid];
                
                if (arr[mid] > key) {
                    std::cout << " (key is smaller, search left half)\n";
                    right = mid;
                } else {
                    std::cout << " (key is larger or equal, search right half)\n";
                    left = mid + 1;
                }
            }
            
            std::cout << "  Found insertion position: " << left << " (after " << comparisons << " comparisons)\n";
            
            // Shift elements to make room
            int shifts = i - left;
            if (shifts > 0) {
                std::cout << "  Shifting " << shifts << " elements to the right\n";
            }
            
            for (int j = i - 1; j >= left; j--) {
                arr[j + 1] = arr[j];
            }
            arr[left] = key;
            
            std::cout << "After step " << i << ": ";
            printArrayInline(arr);
        }
    }
    
    // SHELL SORT
    // Advanced insertion sort with gap sequence
    // Time Complexity: O(n log²n) to O(n^1.5) depending on gap sequence
    static void shellSort(std::vector<int>& arr) {
        int n = arr.size();
        
        // Start with a big gap, then reduce the gap
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // Do a gapped insertion sort
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j;
                
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }
    }
    
    static void shellSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Shell Sort Step-by-Step:\n";
        printArray(arr, "Initial Array");
        
        int n = arr.size();
        int step = 1;
        
        // Start with a big gap, then reduce the gap
        for (int gap = n / 2; gap > 0; gap /= 2) {
            std::cout << "\n=== Gap = " << gap << " ===\n";
            
            if (gap == 1) {
                std::cout << "Final pass (gap = 1) is regular insertion sort\n";
            }
            
            // Show the subarrays formed by current gap
            std::cout << "Subarrays with gap " << gap << ":\n";
            for (int start = 0; start < gap; start++) {
                std::cout << "  Subarray " << start << ": ";
                for (int i = start; i < n; i += gap) {
                    std::cout << arr[i] << " ";
                }
                std::cout << "\n";
            }
            
            // Do a gapped insertion sort
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                std::cout << "\nProcessing element at position " << i << " (value: " << temp << ")\n";
                
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    std::cout << "  Comparing with element at position " << (j - gap) << " (value: " << arr[j - gap] << ")\n";
                    std::cout << "  Moving " << arr[j - gap] << " from position " << (j - gap) << " to position " << j << "\n";
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
                
                if (j != i) {
                    std::cout << "  Placing " << temp << " at position " << j << "\n";
                }
                
                std::cout << "Array after processing position " << i << ": ";
                printArrayInline(arr);
            }
            
            std::cout << "Array after gap " << gap << " phase: ";
            printArrayInline(arr);
        }
    }
    
    // SHELL SORT WITH DIFFERENT GAP SEQUENCES
    
    // Knuth's gap sequence: 1, 4, 13, 40, 121, ...
    static void shellSortKnuth(std::vector<int>& arr) {
        int n = arr.size();
        
        // Generate Knuth's gap sequence
        int gap = 1;
        while (gap < n / 3) {
            gap = 3 * gap + 1;
        }
        
        while (gap >= 1) {
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
            gap /= 3;
        }
    }
    
    // Hibbard's gap sequence: 1, 3, 7, 15, 31, ...
    static void shellSortHibbard(std::vector<int>& arr) {
        int n = arr.size();
        
        // Generate Hibbard's gap sequence
        std::vector<int> gaps;
        for (int k = 1; (1 << k) - 1 < n; k++) {
            gaps.push_back((1 << k) - 1);
        }
        
        // Use gaps in reverse order
        for (int g = gaps.size() - 1; g >= 0; g--) {
            int gap = gaps[g];
            
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }
    }
    
    // TIM SORT CONCEPTS (simplified implementation)
    // This is a simplified version showing the concept
    static void timSortConcept(std::vector<int>& arr) {
        const int MIN_MERGE = 32;
        
        if (arr.size() < MIN_MERGE) {
            insertionSort(arr);
            return;
        }
        
        // For demonstration, we'll just use insertion sort
        // Real TimSort is much more complex with run detection and galloping
        insertionSort(arr);
    }
    
    // PERFORMANCE COMPARISON
    static void performanceComparison(const std::vector<int>& original, const std::string& caseType) {
        std::cout << "Performance Comparison - Insertion Sort Variants (" << caseType << ", size: " << original.size() << "):\n";
        std::cout << std::setw(20) << "Algorithm" << std::setw(15) << "Time (μs)" << std::setw(15) << "Comparisons" << "\n";
        std::cout << std::string(50, '─') << "\n";
        
        // Basic Insertion Sort
        std::vector<int> arr1 = original;
        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(arr1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(20) << "Basic Insertion" << std::setw(15) << duration1.count() << std::setw(15) << "O(n²)" << "\n";
        
        // Binary Insertion Sort
        std::vector<int> arr2 = original;
        start = std::chrono::high_resolution_clock::now();
        binaryInsertionSort(arr2);
        end = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(20) << "Binary Insertion" << std::setw(15) << duration2.count() << std::setw(15) << "O(n log n)*" << "\n";
        
        // Shell Sort (standard)
        std::vector<int> arr3 = original;
        start = std::chrono::high_resolution_clock::now();
        shellSort(arr3);
        end = std::chrono::high_resolution_clock::now();
        auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(20) << "Shell Sort" << std::setw(15) << duration3.count() << std::setw(15) << "O(n^1.5)" << "\n";
        
        // Shell Sort with Knuth's sequence
        std::vector<int> arr4 = original;
        start = std::chrono::high_resolution_clock::now();
        shellSortKnuth(arr4);
        end = std::chrono::high_resolution_clock::now();
        auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(20) << "Shell Sort (Knuth)" << std::setw(15) << duration4.count() << std::setw(15) << "O(n^1.5)" << "\n";
        
        std::cout << "*Binary insertion has fewer comparisons but same number of shifts\n\n";
    }
    
    // ADAPTIVE BEHAVIOR DEMONSTRATION
    static void adaptiveBehaviorDemo() {
        std::cout << "ADAPTIVE BEHAVIOR DEMONSTRATION:\n\n";
        
        // Nearly sorted array
        std::vector<int> nearlySorted = {1, 2, 3, 5, 4, 6, 7, 8, 9, 10};
        std::cout << "1. Nearly Sorted Array:\n";
        printArray(nearlySorted, "Original");
        
        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(nearlySorted);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        printArray(nearlySorted, "Sorted");
        std::cout << "Time taken: " << duration.count() << " microseconds (very fast!)\n\n";
        
        // Reverse sorted array
        std::vector<int> reverseSorted = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        std::cout << "2. Reverse Sorted Array (worst case):\n";
        printArray(reverseSorted, "Original");
        
        start = std::chrono::high_resolution_clock::now();
        insertionSort(reverseSorted);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        printArray(reverseSorted, "Sorted");
        std::cout << "Time taken: " << duration.count() << " microseconds (much slower)\n\n";
        
        // Already sorted array
        std::vector<int> alreadySorted = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::cout << "3. Already Sorted Array (best case):\n";
        printArray(alreadySorted, "Original");
        
        start = std::chrono::high_resolution_clock::now();
        insertionSort(alreadySorted);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        printArray(alreadySorted, "Sorted");
        std::cout << "Time taken: " << duration.count() << " microseconds (fastest - O(n)!)\n\n";
    }

private:
    // Helper functions
    static void printArray(const std::vector<int>& arr, const std::string& label) {
        std::cout << label << ": [";
        for (int i = 0; i < arr.size(); i++) {
            std::cout << arr[i];
            if (i < arr.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
    
    static void printArrayInline(const std::vector<int>& arr) {
        std::cout << "[";
        for (int i = 0; i < arr.size(); i++) {
            std::cout << arr[i];
            if (i < arr.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
};

// Template version for different data types
template<typename T>
class TemplateInsertionSort {
public:
    static void insertionSort(std::vector<T>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            T key = arr[i];
            int j = i - 1;
            
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    // With custom comparator
    template<typename Compare>
    static void insertionSort(std::vector<T>& arr, Compare comp) {
        for (int i = 1; i < arr.size(); i++) {
            T key = arr[i];
            int j = i - 1;
            
            while (j >= 0 && comp(key, arr[j])) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
};

// Utility functions
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

std::vector<int> generateNearlySortedArray(int size, int swaps = 3) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < swaps; i++) {
        int pos1 = gen() % size;
        int pos2 = gen() % size;
        std::swap(arr[pos1], arr[pos2]);
    }
    
    return arr;
}

int main() {
    std::cout << "=== INSERTION SORT AND VARIANTS DEMONSTRATION ===\n\n";
    
    // 1. BASIC INSERTION SORT
    std::cout << "1. BASIC INSERTION SORT DEMONSTRATION:\n";
    std::vector<int> basicArray = {5, 2, 4, 6, 1, 3};
    std::cout << "Characteristics: Simple, stable, adaptive, in-place\n";
    std::cout << "Best for: Small arrays, nearly sorted data\n\n";
    InsertionSortAlgorithms::insertionSortWithVisualization(basicArray);
    std::cout << "\n";
    
    // 2. BINARY INSERTION SORT
    std::cout << "2. BINARY INSERTION SORT DEMONSTRATION:\n";
    std::vector<int> binaryArray = {5, 2, 4, 6, 1, 3};
    std::cout << "Characteristics: Fewer comparisons, same number of shifts\n";
    std::cout << "Best for: When comparisons are expensive\n\n";
    InsertionSortAlgorithms::binaryInsertionSortWithVisualization(binaryArray);
    std::cout << "\n";
    
    // 3. SHELL SORT
    std::cout << "3. SHELL SORT DEMONSTRATION:\n";
    std::vector<int> shellArray = {12, 34, 54, 2, 3, 1, 56, 78, 23, 90};
    std::cout << "Characteristics: Advanced insertion sort, reduces inversions\n";
    std::cout << "Best for: Medium-sized arrays, better than O(n²) sorts\n\n";
    InsertionSortAlgorithms::shellSortWithVisualization(shellArray);
    std::cout << "\n";
    
    // 4. ADAPTIVE BEHAVIOR
    std::cout << "4. ADAPTIVE BEHAVIOR OF INSERTION SORT:\n";
    InsertionSortAlgorithms::adaptiveBehaviorDemo();
    
    // 5. PERFORMANCE COMPARISON
    std::cout << "5. PERFORMANCE COMPARISON:\n\n";
    
    // Random data
    std::vector<int> randomData = generateRandomArray(1000);
    InsertionSortAlgorithms::performanceComparison(randomData, "Random Data");
    
    // Nearly sorted data
    std::vector<int> nearlySortedData = generateNearlySortedArray(1000, 10);
    InsertionSortAlgorithms::performanceComparison(nearlySortedData, "Nearly Sorted Data");
    
    // Small array
    std::vector<int> smallData = generateRandomArray(50);
    InsertionSortAlgorithms::performanceComparison(smallData, "Small Array");
    
    // 6. TEMPLATE USAGE
    std::cout << "6. TEMPLATE INSERTION SORT:\n\n";
    
    // String sorting
    std::vector<std::string> strings = {"banana", "apple", "cherry", "date", "elderberry"};
    std::cout << "Sorting strings: [";
    for (int i = 0; i < strings.size(); i++) {
        std::cout << strings[i];
        if (i < strings.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    TemplateInsertionSort<std::string>::insertionSort(strings);
    
    std::cout << "Sorted strings: [";
    for (int i = 0; i < strings.size(); i++) {
        std::cout << strings[i];
        if (i < strings.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n\n";
    
    // Custom comparator (descending order)
    std::vector<int> descendingArray = {5, 2, 8, 1, 9, 3};
    std::cout << "Sorting integers in descending order: [";
    for (int i = 0; i < descendingArray.size(); i++) {
        std::cout << descendingArray[i];
        if (i < descendingArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    TemplateInsertionSort<int>::insertionSort(descendingArray, [](int a, int b) { return a > b; });
    
    std::cout << "Result: [";
    for (int i = 0; i < descendingArray.size(); i++) {
        std::cout << descendingArray[i];
        if (i < descendingArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n\n";
    
    // 7. REAL-WORLD APPLICATIONS
    std::cout << "7. REAL-WORLD APPLICATIONS:\n\n";
    
    // A. Online algorithm - processing streaming data
    std::cout << "A. Online Algorithm - Processing Streaming Data:\n";
    std::vector<int> onlineData;
    std::vector<int> newElements = {45, 23, 67, 12, 89, 34, 56};
    
    std::cout << "Processing elements as they arrive:\n";
    for (int element : newElements) {
        onlineData.push_back(element);
        std::cout << "Added " << element << ", current array: [";
        for (int i = 0; i < onlineData.size(); i++) {
            std::cout << onlineData[i];
            if (i < onlineData.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        
        // Keep array sorted using insertion sort principle
        int j = onlineData.size() - 2;
        int key = element;
        while (j >= 0 && onlineData[j] > key) {
            onlineData[j + 1] = onlineData[j];
            j--;
        }
        onlineData[j + 1] = key;
        
        std::cout << "After sorting: [";
        for (int i = 0; i < onlineData.size(); i++) {
            std::cout << onlineData[i];
            if (i < onlineData.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n\n";
    }
    
    // B. Playing card sorting
    std::cout << "B. Playing Card Sorting (Natural Human Method):\n";
    std::vector<std::string> cards = {"7♠", "A♥", "K♦", "3♣", "J♠", "Q♥", "2♦", "10♣"};
    std::cout << "Cards in hand: [";
    for (int i = 0; i < cards.size(); i++) {
        std::cout << cards[i];
        if (i < cards.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    std::cout << "Humans naturally use insertion sort when organizing cards!\n";
    std::cout << "Pick each card and find its correct position among already sorted cards.\n\n";
    
    // 8. ALGORITHM CHARACTERISTICS SUMMARY
    std::cout << "8. ALGORITHM CHARACTERISTICS SUMMARY:\n";
    std::cout << "┌─────────────────────────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ Algorithm           │ Best Case │ Average   │ Worst     │ Space │ Stable │ Adaptive │\n";
    std::cout << "├─────────────────────────────────────────────────────────────────────────────────────┤\n";
    std::cout << "│ Insertion Sort      │ O(n)      │ O(n²)     │ O(n²)     │ O(1)  │ Yes    │ Yes      │\n";
    std::cout << "│ Binary Insertion    │ O(n log n)│ O(n²)     │ O(n²)     │ O(1)  │ Yes    │ Yes      │\n";
    std::cout << "│ Shell Sort          │ O(n log n)│ O(n^1.25) │ O(n^1.5)  │ O(1)  │ No     │ Yes      │\n";
    std::cout << "│ Shell Sort (Knuth)  │ O(n log n)│ O(n^1.25) │ O(n^1.5)  │ O(1)  │ No     │ Yes      │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    
    std::cout << "Key advantages of Insertion Sort variants:\n";
    std::cout << "• Simple implementation and understanding\n";
    std::cout << "• Stable sorting (maintains relative order of equal elements)\n";
    std::cout << "• Adaptive (performs well on nearly sorted data)\n";
    std::cout << "• In-place (requires only O(1) additional memory)\n";
    std::cout << "• Online (can sort data as it's received)\n";
    std::cout << "• Efficient for small datasets\n";
    std::cout << "• Shell sort provides significant improvement for medium-sized arrays\n\n";
    
    std::cout << "When to use:\n";
    std::cout << "• Small arrays (n < 50)\n";
    std::cout << "• Nearly sorted data\n";
    std::cout << "• As a subroutine in hybrid algorithms (like TimSort)\n";
    std::cout << "• Online algorithms where data arrives one element at a time\n";
    std::cout << "• When simplicity and stability are more important than efficiency\n";
    std::cout << "• Shell sort for medium-sized arrays when O(n log n) algorithms are overkill\n";
    
    return 0;
}
