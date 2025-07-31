/*
 * Binary Search Algorithm Implementation
 * 
 * Binary Search:
 * - Divide and conquer algorithm for searching in sorted arrays
 * - Repeatedly divides search space in half
 * - Time Complexity: O(log n)
 * - Space Complexity: O(1) iterative, O(log n) recursive
 * 
 * Prerequisites:
 * - Array must be sorted
 * 
 * Applications:
 * - Large sorted datasets
 * - Database indexing
 * - Search engines
 * - Finding insertion points
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <cmath>

class BinarySearch {
public:
    // Iterative binary search
    static int searchIterative(const std::vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;  // Avoid overflow
            
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;  // Element not found
    }
    
    // Recursive binary search
    static int searchRecursive(const std::vector<int>& arr, int target) {
        return searchRecursiveHelper(arr, target, 0, arr.size() - 1);
    }
    
private:
    static int searchRecursiveHelper(const std::vector<int>& arr, int target, int left, int right) {
        if (left > right) {
            return -1;
        }
        
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            return searchRecursiveHelper(arr, target, mid + 1, right);
        } else {
            return searchRecursiveHelper(arr, target, left, mid - 1);
        }
    }
    
public:
    // Find first occurrence in array with duplicates
    static int findFirstOccurrence(const std::vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                result = mid;
                right = mid - 1;  // Continue searching in left half
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    // Find last occurrence in array with duplicates
    static int findLastOccurrence(const std::vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                result = mid;
                left = mid + 1;  // Continue searching in right half
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    // Count occurrences using binary search
    static int countOccurrences(const std::vector<int>& arr, int target) {
        int first = findFirstOccurrence(arr, target);
        if (first == -1) return 0;
        
        int last = findLastOccurrence(arr, target);
        return last - first + 1;
    }
    
    // Find insertion point (lower_bound)
    static int findInsertionPoint(const std::vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size();
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
    
    // Find upper bound
    static int findUpperBound(const std::vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size();
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
    
    // Search in rotated sorted array
    static int searchInRotatedArray(const std::vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                return mid;
            }
            
            // Check which half is sorted
            if (arr[left] <= arr[mid]) {  // Left half is sorted
                if (target >= arr[left] && target < arr[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {  // Right half is sorted
                if (target > arr[mid] && target <= arr[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
    
    // Find peak element (local maximum)
    static int findPeakElement(const std::vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] < arr[mid + 1]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
    
    // Square root using binary search
    static double squareRoot(double x, double precision = 1e-6) {
        if (x < 0) return -1;
        if (x == 0 || x == 1) return x;
        
        double left = 0;
        double right = x;
        if (x < 1) right = 1;
        
        while (right - left > precision) {
            double mid = left + (right - left) / 2;
            
            if (mid * mid == x) {
                return mid;
            } else if (mid * mid < x) {
                left = mid;
            } else {
                right = mid;
            }
        }
        
        return left + (right - left) / 2;
    }
    
    // Template version for any comparable type
    template<typename T>
    static int searchGeneric(const std::vector<T>& arr, const T& target) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
    
    // Performance analysis with step counting
    static int searchWithSteps(const std::vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        int steps = 0;
        
        std::cout << "Binary Search Steps for target " << target << ":\n";
        
        while (left <= right) {
            steps++;
            int mid = left + (right - left) / 2;
            
            std::cout << "Step " << steps << ": left=" << left << ", right=" << right 
                      << ", mid=" << mid << ", arr[mid]=" << arr[mid];
            
            if (arr[mid] == target) {
                std::cout << " -> FOUND!\n";
                return mid;
            } else if (arr[mid] < target) {
                std::cout << " -> Go right\n";
                left = mid + 1;
            } else {
                std::cout << " -> Go left\n";
                right = mid - 1;
            }
        }
        
        std::cout << "Element not found after " << steps << " steps.\n";
        return -1;
    }
    
    // Performance comparison
    static void performanceComparison(const std::vector<int>& arr, int target) {
        auto start = std::chrono::high_resolution_clock::now();
        int result = searchIterative(arr, target);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        int theoreticalSteps = static_cast<int>(std::ceil(std::log2(arr.size())));
        
        std::cout << "Binary Search Performance:\n";
        std::cout << "Array size: " << arr.size() << "\n";
        std::cout << "Target: " << target << "\n";
        std::cout << "Result: " << (result != -1 ? "Found at index " + std::to_string(result) : "Not found") << "\n";
        std::cout << "Time taken: " << duration.count() << " microseconds\n";
        std::cout << "Theoretical max steps: " << theoreticalSteps << "\n\n";
    }
};

// Utility functions
void printArray(const std::vector<int>& arr, const std::string& label) {
    std::cout << label << ": [";
    for (int i = 0; i < std::min(20, static_cast<int>(arr.size())); i++) {
        std::cout << arr[i];
        if (i < std::min(20, static_cast<int>(arr.size())) - 1) std::cout << ", ";
    }
    if (arr.size() > 20) std::cout << "...";
    std::cout << "] (size: " << arr.size() << ")\n";
}

int main() {
    std::cout << "=== BINARY SEARCH ALGORITHM DEMONSTRATION ===\n\n";
    
    // Test data
    std::vector<int> sortedArr = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    std::vector<int> duplicatesArr = {1, 2, 2, 2, 3, 4, 4, 5, 6, 6, 6, 6, 7};
    std::vector<int> rotatedArr = {4, 5, 6, 7, 0, 1, 2};
    
    printArray(sortedArr, "Sorted Array");
    printArray(duplicatesArr, "Array with Duplicates");
    printArray(rotatedArr, "Rotated Sorted Array");
    std::cout << "\n";
    
    // Basic binary search
    std::cout << "1. BASIC BINARY SEARCH:\n";
    int target1 = 23;
    int result1 = BinarySearch::searchIterative(sortedArr, target1);
    std::cout << "Iterative search for " << target1 << ": ";
    if (result1 != -1) {
        std::cout << "Found at index " << result1 << "\n";
    } else {
        std::cout << "Not found\n";
    }
    
    int result2 = BinarySearch::searchRecursive(sortedArr, target1);
    std::cout << "Recursive search for " << target1 << ": ";
    if (result2 != -1) {
        std::cout << "Found at index " << result2 << "\n";
    } else {
        std::cout << "Not found\n";
    }
    
    int target3 = 99;
    int result3 = BinarySearch::searchIterative(sortedArr, target3);
    std::cout << "Search for " << target3 << ": ";
    if (result3 != -1) {
        std::cout << "Found at index " << result3 << "\n";
    } else {
        std::cout << "Not found\n";
    }
    std::cout << "\n";
    
    // Search with steps visualization
    std::cout << "2. BINARY SEARCH STEP-BY-STEP:\n";
    BinarySearch::searchWithSteps(sortedArr, 23);
    std::cout << "\n";
    BinarySearch::searchWithSteps(sortedArr, 99);
    std::cout << "\n";
    
    // Handling duplicates
    std::cout << "3. HANDLING DUPLICATES:\n";
    printArray(duplicatesArr, "Array");
    int target4 = 2;
    int first = BinarySearch::findFirstOccurrence(duplicatesArr, target4);
    int last = BinarySearch::findLastOccurrence(duplicatesArr, target4);
    int count = BinarySearch::countOccurrences(duplicatesArr, target4);
    
    std::cout << "Target " << target4 << ":\n";
    std::cout << "First occurrence: " << first << "\n";
    std::cout << "Last occurrence: " << last << "\n";
    std::cout << "Total occurrences: " << count << "\n";
    
    target4 = 6;
    first = BinarySearch::findFirstOccurrence(duplicatesArr, target4);
    last = BinarySearch::findLastOccurrence(duplicatesArr, target4);
    count = BinarySearch::countOccurrences(duplicatesArr, target4);
    
    std::cout << "Target " << target4 << ":\n";
    std::cout << "First occurrence: " << first << "\n";
    std::cout << "Last occurrence: " << last << "\n";
    std::cout << "Total occurrences: " << count << "\n\n";
    
    // Insertion point
    std::cout << "4. FINDING INSERTION POINTS:\n";
    std::vector<int> insertArr = {1, 3, 5, 7, 9};
    printArray(insertArr, "Array");
    
    int insertTargets[] = {0, 2, 4, 6, 8, 10};
    for (int target : insertTargets) {
        int insertPoint = BinarySearch::findInsertionPoint(insertArr, target);
        std::cout << "Insert " << target << " at index " << insertPoint << "\n";
    }
    std::cout << "\n";
    
    // Rotated array search
    std::cout << "5. SEARCH IN ROTATED SORTED ARRAY:\n";
    printArray(rotatedArr, "Rotated Array");
    
    int rotatedTargets[] = {0, 4, 6, 3};
    for (int target : rotatedTargets) {
        int result = BinarySearch::searchInRotatedArray(rotatedArr, target);
        std::cout << "Search for " << target << ": ";
        if (result != -1) {
            std::cout << "Found at index " << result << "\n";
        } else {
            std::cout << "Not found\n";
        }
    }
    std::cout << "\n";
    
    // Peak element
    std::cout << "6. FIND PEAK ELEMENT:\n";
    std::vector<int> peakArr = {1, 2, 3, 1};
    printArray(peakArr, "Array");
    int peakIndex = BinarySearch::findPeakElement(peakArr);
    std::cout << "Peak element: " << peakArr[peakIndex] << " at index " << peakIndex << "\n";
    
    std::vector<int> peakArr2 = {1, 2, 1, 3, 5, 6, 4};
    printArray(peakArr2, "Array");
    int peakIndex2 = BinarySearch::findPeakElement(peakArr2);
    std::cout << "Peak element: " << peakArr2[peakIndex2] << " at index " << peakIndex2 << "\n\n";
    
    // Square root
    std::cout << "7. SQUARE ROOT USING BINARY SEARCH:\n";
    double numbers[] = {4.0, 9.0, 2.0, 10.0, 25.0};
    for (double num : numbers) {
        double sqrt_val = BinarySearch::squareRoot(num);
        std::cout << "√" << num << " = " << sqrt_val << " (verification: " << sqrt_val * sqrt_val << ")\n";
    }
    std::cout << "\n";
    
    // Template search with strings
    std::cout << "8. GENERIC TEMPLATE SEARCH (Strings):\n";
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank"};
    std::cout << "Sorted names: [";
    for (int i = 0; i < names.size(); i++) {
        std::cout << names[i];
        if (i < names.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    std::string targetName = "David";
    int nameIndex = BinarySearch::searchGeneric(names, targetName);
    std::cout << "Searching for '" << targetName << "': ";
    if (nameIndex != -1) {
        std::cout << "Found at index " << nameIndex << "\n";
    } else {
        std::cout << "Not found\n";
    }
    std::cout << "\n";
    
    // Performance analysis
    std::cout << "9. PERFORMANCE ANALYSIS:\n";
    
    // Small array
    std::vector<int> smallArr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    BinarySearch::performanceComparison(smallArr, 7);
    
    // Large array
    std::vector<int> largeArr(100000);
    std::iota(largeArr.begin(), largeArr.end(), 1);
    BinarySearch::performanceComparison(largeArr, 75000);
    
    // Very large array
    std::vector<int> veryLargeArr(1000000);
    std::iota(veryLargeArr.begin(), veryLargeArr.end(), 1);
    BinarySearch::performanceComparison(veryLargeArr, 999999);
    
    // Real-world application: Phone book
    std::cout << "10. REAL-WORLD APPLICATION - Phone Book:\n";
    struct Contact {
        std::string name;
        std::string phone;
        
        bool operator<(const Contact& other) const {
            return name < other.name;
        }
        
        bool operator==(const Contact& other) const {
            return name == other.name;
        }
    };
    
    std::vector<Contact> phoneBook = {
        {"Alice Johnson", "555-0101"},
        {"Bob Smith", "555-0102"},
        {"Charlie Brown", "555-0103"},
        {"David Wilson", "555-0104"},
        {"Eve Davis", "555-0105"}
    };
    
    std::cout << "Phone Book (sorted by name):\n";
    for (const auto& contact : phoneBook) {
        std::cout << contact.name << ": " << contact.phone << "\n";
    }
    
    Contact searchContact = {"Charlie Brown", ""};
    int contactIndex = BinarySearch::searchGeneric(phoneBook, searchContact);
    
    if (contactIndex != -1) {
        std::cout << "\nFound contact: " << phoneBook[contactIndex].name 
                  << " -> " << phoneBook[contactIndex].phone << "\n";
    } else {
        std::cout << "\nContact not found\n";
    }
    
    std::cout << "\n=== BINARY SEARCH SUMMARY ===\n";
    std::cout << "Advantages:\n";
    std::cout << "- O(log n) time complexity - very efficient for large datasets\n";
    std::cout << "- Eliminates half of remaining elements in each step\n";
    std::cout << "- Predictable performance\n";
    std::cout << "- Space efficient (O(1) for iterative version)\n";
    std::cout << "\nDisadvantages:\n";
    std::cout << "- Requires sorted data\n";
    std::cout << "- Not suitable for linked lists (no random access)\n";
    std::cout << "- Overhead for small datasets\n";
    std::cout << "\nBest Use Cases:\n";
    std::cout << "- Large sorted datasets\n";
    std::cout << "- Database indexing\n";
    std::cout << "- Finding insertion points\n";
    std::cout << "- Range queries in sorted data\n";
    std::cout << "- Mathematical computations (square root, etc.)\n";
    
    return 0;
}
