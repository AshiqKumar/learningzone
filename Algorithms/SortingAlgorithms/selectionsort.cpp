/*
 * Selection Sort Algorithm Implementation
 * 
 * Selection Sort:
 * - Simple comparison-based sorting algorithm
 * - Finds minimum element and places it at the beginning
 * - Time Complexity: O(n²) for all cases
 * - Space Complexity: O(1)
 * - Unstable: No (doesn't maintain relative order of equal elements)
 * - In-place: Yes
 * 
 * Applications:
 * - Small datasets
 * - When memory write is costly (minimizes number of swaps)
 * - When simplicity is preferred
 * - Educational purposes
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <random>
#include <iomanip>

class SelectionSort {
public:
    // Basic selection sort implementation
    static void sort(std::vector<int>& arr) {
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            // Find minimum element in remaining unsorted array
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            
            // Swap found minimum element with first element
            if (minIndex != i) {
                std::swap(arr[i], arr[minIndex]);
            }
        }
    }
    
    // Selection sort with step-by-step visualization
    static void sortWithVisualization(std::vector<int>& arr) {
        int n = arr.size();
        std::cout << "Selection Sort Step-by-Step:\n";
        printArray(arr, "Initial");
        
        for (int i = 0; i < n - 1; i++) {
            std::cout << "\nIteration " << i + 1 << ":\n";
            std::cout << "Finding minimum in subarray [" << i << ", " << n - 1 << "]\n";
            
            int minIndex = i;
            int minValue = arr[i];
            
            for (int j = i + 1; j < n; j++) {
                std::cout << "Comparing arr[" << j << "]=" << arr[j] 
                          << " with current min=" << minValue;
                
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                    minValue = arr[j];
                    std::cout << " -> New minimum found at index " << j;
                }
                std::cout << "\n";
            }
            
            if (minIndex != i) {
                std::cout << "Swapping arr[" << i << "]=" << arr[i] 
                          << " with arr[" << minIndex << "]=" << arr[minIndex] << "\n";
                std::swap(arr[i], arr[minIndex]);
            } else {
                std::cout << "Minimum is already at correct position\n";
            }
            
            printArray(arr, "After iteration " + std::to_string(i + 1));
            std::cout << "Sorted portion: [0, " << i << "], Unsorted portion: [" << i + 1 << ", " << n - 1 << "]\n";
        }
    }
    
    // Selection sort with comparison and swap counting
    static std::pair<int, int> sortWithCounts(std::vector<int>& arr) {
        int n = arr.size();
        int comparisons = 0;
        int swaps = 0;
        
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            
            for (int j = i + 1; j < n; j++) {
                comparisons++;
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            
            if (minIndex != i) {
                std::swap(arr[i], arr[minIndex]);
                swaps++;
            }
        }
        
        return {comparisons, swaps};
    }
    
    // Recursive selection sort
    static void sortRecursive(std::vector<int>& arr, int startIndex = 0) {
        int n = arr.size();
        
        // Base case
        if (startIndex >= n - 1) return;
        
        // Find minimum element in remaining array
        int minIndex = startIndex;
        for (int j = startIndex + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap if necessary
        if (minIndex != startIndex) {
            std::swap(arr[startIndex], arr[minIndex]);
        }
        
        // Recursively sort the rest
        sortRecursive(arr, startIndex + 1);
    }
    
    // Template version for any comparable type
    template<typename T>
    static void sortGeneric(std::vector<T>& arr) {
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            
            if (minIndex != i) {
                std::swap(arr[i], arr[minIndex]);
            }
        }
    }
    
    // Selection sort with custom comparator
    template<typename T, typename Compare>
    static void sortWithComparator(std::vector<T>& arr, Compare comp) {
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            int selectedIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (comp(arr[j], arr[selectedIndex])) {
                    selectedIndex = j;
                }
            }
            
            if (selectedIndex != i) {
                std::swap(arr[i], arr[selectedIndex]);
            }
        }
    }
    
    // Find kth smallest element using selection sort approach
    static int findKthSmallest(std::vector<int>& arr, int k) {
        if (k < 1 || k > arr.size()) return -1;
        
        int n = arr.size();
        
        for (int i = 0; i < k; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            
            if (minIndex != i) {
                std::swap(arr[i], arr[minIndex]);
            }
        }
        
        return arr[k - 1];
    }
    
    // Stability demonstration
    static void stabilityDemo() {
        struct Element {
            int value;
            char id;
            
            bool operator<(const Element& other) const {
                return value < other.value;
            }
        };
        
        std::vector<Element> arr = {{3, 'A'}, {1, 'B'}, {3, 'C'}, {2, 'D'}};
        
        std::cout << "Stability Demonstration:\n";
        std::cout << "Original array: ";
        for (const auto& elem : arr) {
            std::cout << "(" << elem.value << "," << elem.id << ") ";
        }
        std::cout << "\n";
        
        sortGeneric(arr);
        
        std::cout << "After selection sort: ";
        for (const auto& elem : arr) {
            std::cout << "(" << elem.value << "," << elem.id << ") ";
        }
        std::cout << "\n";
        std::cout << "Note: Selection sort is unstable - relative order of equal elements may change\n\n";
    }
    
    // Performance analysis
    static void performanceAnalysis(std::vector<int>& arr, const std::string& caseType) {
        std::vector<int> arrCopy = arr;
        
        auto start = std::chrono::high_resolution_clock::now();
        auto counts = sortWithCounts(arrCopy);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Selection Sort Performance (" << caseType << "):\n";
        std::cout << "Array size: " << arr.size() << "\n";
        std::cout << "Comparisons: " << counts.first << "\n";
        std::cout << "Swaps: " << counts.second << "\n";
        std::cout << "Time taken: " << duration.count() << " microseconds\n";
        std::cout << "Theoretical comparisons: " << (arr.size() * (arr.size() - 1)) / 2 << "\n";
        std::cout << "Maximum possible swaps: " << arr.size() - 1 << "\n\n";
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

int main() {
    std::cout << "=== SELECTION SORT ALGORITHM DEMONSTRATION ===\n\n";
    
    // Basic demonstration
    std::cout << "1. BASIC SELECTION SORT:\n";
    std::vector<int> basicArray = {64, 25, 12, 22, 11, 90};
    printArray(basicArray, "Original Array");
    
    std::vector<int> sortedArray = basicArray;
    SelectionSort::sort(sortedArray);
    printArray(sortedArray, "Sorted Array");
    std::cout << "\n";
    
    // Step-by-step visualization
    std::cout << "2. STEP-BY-STEP VISUALIZATION:\n";
    std::vector<int> visualArray = {29, 10, 14, 37, 13};
    SelectionSort::sortWithVisualization(visualArray);
    std::cout << "\n";
    
    // Recursive implementation
    std::cout << "3. RECURSIVE SELECTION SORT:\n";
    std::vector<int> recursiveArray = {5, 2, 8, 1, 9};
    printArray(recursiveArray, "Before Recursive Sort");
    SelectionSort::sortRecursive(recursiveArray);
    printArray(recursiveArray, "After Recursive Sort");
    std::cout << "\n";
    
    // Template usage with different data types
    std::cout << "4. GENERIC TEMPLATE SORTING:\n";
    
    // Character array
    std::vector<char> charArray = {'d', 'a', 'c', 'b', 'e'};
    std::cout << "Character array before: [";
    for (int i = 0; i < charArray.size(); i++) {
        std::cout << charArray[i];
        if (i < charArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    SelectionSort::sortGeneric(charArray);
    std::cout << "Character array after: [";
    for (int i = 0; i < charArray.size(); i++) {
        std::cout << charArray[i];
        if (i < charArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    // String array
    std::vector<std::string> stringArray = {"zebra", "apple", "orange", "banana"};
    std::cout << "String array before: [";
    for (int i = 0; i < stringArray.size(); i++) {
        std::cout << stringArray[i];
        if (i < stringArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    SelectionSort::sortGeneric(stringArray);
    std::cout << "String array after: [";
    for (int i = 0; i < stringArray.size(); i++) {
        std::cout << stringArray[i];
        if (i < stringArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n\n";
    
    // Custom comparator (descending order)
    std::cout << "5. CUSTOM COMPARATOR (Descending Order):\n";
    std::vector<int> descArray = {3, 7, 1, 9, 2, 8};
    printArray(descArray, "Original Array");
    
    SelectionSort::sortWithComparator(descArray, [](int a, int b) { return a > b; });
    printArray(descArray, "Descending Sorted Array");
    std::cout << "\n";
    
    // Finding kth smallest element
    std::cout << "6. FINDING KTH SMALLEST ELEMENT:\n";
    std::vector<int> kthArray = {7, 10, 4, 3, 20, 15};
    printArray(kthArray, "Original Array");
    
    std::vector<int> kthCopy = kthArray;
    int k = 3;
    int kthSmallest = SelectionSort::findKthSmallest(kthCopy, k);
    std::cout << k << "rd smallest element: " << kthSmallest << "\n";
    
    kthCopy = kthArray;
    k = 1;
    int smallest = SelectionSort::findKthSmallest(kthCopy, k);
    std::cout << k << "st smallest element: " << smallest << "\n\n";
    
    // Stability demonstration
    std::cout << "7. STABILITY ANALYSIS:\n";
    SelectionSort::stabilityDemo();
    
    // Performance analysis
    std::cout << "8. PERFORMANCE ANALYSIS:\n";
    
    // Best case (already sorted) - same as worst case for selection sort
    std::vector<int> bestCase = generateSortedArray(1000);
    SelectionSort::performanceAnalysis(bestCase, "Already Sorted");
    
    // Worst case (reverse sorted) - same performance as best case
    std::vector<int> worstCase = generateSortedArray(1000, false);
    SelectionSort::performanceAnalysis(worstCase, "Reverse Sorted");
    
    // Average case (random)
    std::vector<int> averageCase = generateRandomArray(1000);
    SelectionSort::performanceAnalysis(averageCase, "Random Array");
    
    // Comparison with other O(n²) sorts - swap analysis
    std::cout << "9. SWAP ANALYSIS COMPARISON:\n";
    std::cout << "Comparing number of swaps for different array configurations:\n";
    std::cout << "Configuration\t\tSelection Sort Swaps\tBubble Sort Swaps (approx)\n";
    std::cout << "──────────────────────────────────────────────────────────────────\n";
    
    // Random array
    std::vector<int> testArray = generateRandomArray(100);
    std::vector<int> selectionCopy = testArray;
    std::vector<int> bubbleCopy = testArray;
    
    auto selectionCounts = SelectionSort::sortWithCounts(selectionCopy);
    
    // Bubble sort swap count estimation (for comparison)
    int bubbleSwaps = 0;
    int n = bubbleCopy.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bubbleCopy[j] > bubbleCopy[j + 1]) {
                std::swap(bubbleCopy[j], bubbleCopy[j + 1]);
                bubbleSwaps++;
            }
        }
    }
    
    std::cout << "Random (n=100)\t\t" << selectionCounts.second << "\t\t\t" << bubbleSwaps << "\n";
    
    // Real-world application example
    std::cout << "\n10. REAL-WORLD APPLICATION - Tournament Ranking:\n";
    struct Player {
        std::string name;
        int score;
        int gamesPlayed;
        
        bool operator<(const Player& other) const {
            // Sort by score descending, then by games played ascending
            if (score != other.score) return score > other.score;
            return gamesPlayed < other.gamesPlayed;
        }
    };
    
    std::vector<Player> players = {
        {"Alice", 85, 10},
        {"Bob", 92, 12},
        {"Charlie", 78, 8},
        {"David", 92, 15},  // Same score as Bob
        {"Eve", 88, 11}
    };
    
    std::cout << "Players before sorting:\n";
    std::cout << "Name\t\tScore\tGames Played\n";
    std::cout << "────────────────────────────────────\n";
    for (const auto& player : players) {
        std::cout << std::left << std::setw(12) << player.name 
                  << player.score << "\t" << player.gamesPlayed << "\n";
    }
    
    SelectionSort::sortGeneric(players);
    
    std::cout << "\nPlayers after sorting (by score desc, then games asc):\n";
    std::cout << "Rank\tName\t\tScore\tGames Played\n";
    std::cout << "────────────────────────────────────────────────\n";
    for (int i = 0; i < players.size(); i++) {
        std::cout << i + 1 << "\t" << std::left << std::setw(12) << players[i].name 
                  << players[i].score << "\t" << players[i].gamesPlayed << "\n";
    }
    std::cout << "\n";
    
    // Memory write optimization demonstration
    std::cout << "11. MEMORY WRITE OPTIMIZATION:\n";
    std::cout << "Selection sort minimizes memory writes (swaps).\n";
    std::cout << "This is beneficial when:\n";
    std::cout << "- Writing to memory is expensive (e.g., flash memory)\n";
    std::cout << "- Working with large objects where copying is costly\n";
    std::cout << "- Network-based storage systems\n\n";
    
    // Complexity analysis demonstration
    std::cout << "12. COMPLEXITY ANALYSIS:\n";
    std::cout << "Selection sort always performs exactly n(n-1)/2 comparisons\n";
    std::cout << "Size\tActual Comparisons\tTheoretical n(n-1)/2\tSwaps\n";
    std::cout << "──────────────────────────────────────────────────────────────\n";
    
    for (int size : {10, 20, 50, 100}) {
        std::vector<int> testArray = generateRandomArray(size);
        auto counts = SelectionSort::sortWithCounts(testArray);
        int theoretical = (size * (size - 1)) / 2;
        
        std::cout << size << "\t" << counts.first << "\t\t\t" << theoretical 
                  << "\t\t" << counts.second << "\n";
    }
    
    std::cout << "\n=== SELECTION SORT SUMMARY ===\n";
    std::cout << "Characteristics:\n";
    std::cout << "- Stable: No (doesn't maintain relative order of equal elements)\n";
    std::cout << "- In-place: Yes (requires only O(1) extra memory)\n";
    std::cout << "- Adaptive: No (same performance regardless of input)\n";
    std::cout << "- Comparison-based: Yes\n";
    std::cout << "\nComplexity:\n";
    std::cout << "- Best Case: O(n²) - same as worst case\n";
    std::cout << "- Average Case: O(n²)\n";
    std::cout << "- Worst Case: O(n²)\n";
    std::cout << "- Space Complexity: O(1)\n";
    std::cout << "\nAdvantages:\n";
    std::cout << "- Simple to understand and implement\n";
    std::cout << "- Minimal memory writes (at most n-1 swaps)\n";
    std::cout << "- Performs well on small datasets\n";
    std::cout << "- No additional memory space needed\n";
    std::cout << "- Never makes more than O(n) swaps\n";
    std::cout << "\nDisadvantages:\n";
    std::cout << "- O(n²) time complexity for all cases\n";
    std::cout << "- Not stable (relative order of equal elements may change)\n";
    std::cout << "- Not adaptive (doesn't benefit from partially sorted data)\n";
    std::cout << "- Not suitable for large datasets\n";
    std::cout << "\nBest Use Cases:\n";
    std::cout << "- Small datasets\n";
    std::cout << "- When memory write is costly (flash memory, network storage)\n";
    std::cout << "- When simplicity is preferred over efficiency\n";
    std::cout << "- Finding k smallest/largest elements\n";
    std::cout << "- Educational purposes\n";
    
    return 0;
}
