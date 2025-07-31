/*
 * Advanced Sorting Algorithms Implementation
 * 
 * This file contains multiple advanced sorting algorithms:
 * 1. Merge Sort
 * 2. Heap Sort  
 * 3. Counting Sort
 * 4. Radix Sort
 * 5. Bucket Sort
 * 
 * Each algorithm has different characteristics and optimal use cases
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <random>
#include <queue>
#include <cmath>
#include <iomanip>

class AdvancedSortingAlgorithms {
public:
    // MERGE SORT
    // Time Complexity: O(n log n) for all cases
    // Space Complexity: O(n)
    // Stable: Yes
    static void mergeSort(std::vector<int>& arr) {
        if (arr.size() <= 1) return;
        mergeSortRecursive(arr, 0, arr.size() - 1);
    }
    
    static void mergeSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Merge Sort Step-by-Step:\n";
        printArray(arr, "Initial Array");
        mergeSortVisual(arr, 0, arr.size() - 1, 0);
    }
    
    // Iterative merge sort (bottom-up approach)
    static void mergeSortIterative(std::vector<int>& arr) {
        int n = arr.size();
        
        for (int currSize = 1; currSize < n; currSize *= 2) {
            for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
                int mid = std::min(leftStart + currSize - 1, n - 1);
                int rightEnd = std::min(leftStart + 2 * currSize - 1, n - 1);
                
                if (mid < rightEnd) {
                    merge(arr, leftStart, mid, rightEnd);
                }
            }
        }
    }
    
    // HEAP SORT
    // Time Complexity: O(n log n) for all cases
    // Space Complexity: O(1)
    // Unstable: Yes
    static void heapSort(std::vector<int>& arr) {
        int n = arr.size();
        
        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        
        // Extract elements one by one
        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    
    static void heapSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Heap Sort Step-by-Step:\n";
        printArray(arr, "Initial Array");
        
        int n = arr.size();
        
        // Build max heap
        std::cout << "\nBuilding Max Heap:\n";
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
            std::cout << "After heapifying index " << i << ": ";
            printArrayInline(arr);
        }
        
        std::cout << "\nExtracting elements:\n";
        // Extract elements one by one
        for (int i = n - 1; i > 0; i--) {
            std::cout << "Extracting max element " << arr[0] << " to position " << i << "\n";
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
            std::cout << "Array after extraction: ";
            printArrayInline(arr);
        }
    }
    
    // COUNTING SORT
    // Time Complexity: O(n + k) where k is range of input
    // Space Complexity: O(k)
    // Stable: Yes
    static void countingSort(std::vector<int>& arr) {
        if (arr.empty()) return;
        
        int maxVal = *std::max_element(arr.begin(), arr.end());
        int minVal = *std::min_element(arr.begin(), arr.end());
        int range = maxVal - minVal + 1;
        
        std::vector<int> count(range, 0);
        std::vector<int> output(arr.size());
        
        // Count occurrences
        for (int num : arr) {
            count[num - minVal]++;
        }
        
        // Modify count array to store actual positions
        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }
        
        // Build output array
        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[arr[i] - minVal] - 1] = arr[i];
            count[arr[i] - minVal]--;
        }
        
        arr = output;
    }
    
    static void countingSortWithVisualization(std::vector<int>& arr) {
        if (arr.empty()) return;
        
        std::cout << "Counting Sort Step-by-Step:\n";
        printArray(arr, "Initial Array");
        
        int maxVal = *std::max_element(arr.begin(), arr.end());
        int minVal = *std::min_element(arr.begin(), arr.end());
        int range = maxVal - minVal + 1;
        
        std::cout << "Range: " << minVal << " to " << maxVal << " (size: " << range << ")\n";
        
        std::vector<int> count(range, 0);
        
        // Count occurrences
        for (int num : arr) {
            count[num - minVal]++;
        }
        
        std::cout << "Count array: [";
        for (int i = 0; i < count.size(); i++) {
            std::cout << count[i];
            if (i < count.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        
        // Modify count array to store actual positions
        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }
        
        std::cout << "Cumulative count array: [";
        for (int i = 0; i < count.size(); i++) {
            std::cout << count[i];
            if (i < count.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        
        std::vector<int> output(arr.size());
        
        // Build output array
        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[arr[i] - minVal] - 1] = arr[i];
            count[arr[i] - minVal]--;
        }
        
        arr = output;
        printArray(arr, "Sorted Array");
    }
    
    // RADIX SORT
    // Time Complexity: O(d * (n + k)) where d is digits, k is range
    // Space Complexity: O(n + k)
    // Stable: Yes
    static void radixSort(std::vector<int>& arr) {
        if (arr.empty()) return;
        
        int maxVal = *std::max_element(arr.begin(), arr.end());
        
        // Do counting sort for every digit
        for (int exp = 1; maxVal / exp > 0; exp *= 10) {
            countingSortByDigit(arr, exp);
        }
    }
    
    static void radixSortWithVisualization(std::vector<int>& arr) {
        if (arr.empty()) return;
        
        std::cout << "Radix Sort Step-by-Step:\n";
        printArray(arr, "Initial Array");
        
        int maxVal = *std::max_element(arr.begin(), arr.end());
        int digits = std::to_string(maxVal).length();
        
        std::cout << "Maximum value: " << maxVal << " (digits: " << digits << ")\n\n";
        
        // Do counting sort for every digit
        for (int exp = 1, digitPos = 1; maxVal / exp > 0; exp *= 10, digitPos++) {
            std::cout << "Sorting by digit " << digitPos << " (place value " << exp << "):\n";
            
            // Show current digits being considered
            std::cout << "Current digits: ";
            for (int num : arr) {
                std::cout << ((num / exp) % 10) << " ";
            }
            std::cout << "\n";
            
            countingSortByDigit(arr, exp);
            
            std::cout << "After sorting by digit " << digitPos << ": ";
            printArrayInline(arr);
            std::cout << "\n";
        }
    }
    
    // BUCKET SORT
    // Time Complexity: O(n + k) average, O(n²) worst case
    // Space Complexity: O(n + k)
    // Stable: Yes
    static void bucketSort(std::vector<double>& arr) {
        if (arr.empty()) return;
        
        int n = arr.size();
        std::vector<std::vector<double>> buckets(n);
        
        // Put array elements in different buckets
        for (double num : arr) {
            int bucketIndex = static_cast<int>(n * num);
            buckets[bucketIndex].push_back(num);
        }
        
        // Sort individual buckets
        for (auto& bucket : buckets) {
            std::sort(bucket.begin(), bucket.end());
        }
        
        // Concatenate all buckets
        int index = 0;
        for (const auto& bucket : buckets) {
            for (double num : bucket) {
                arr[index++] = num;
            }
        }
    }
    
    // Integer version of bucket sort
    static void bucketSortInteger(std::vector<int>& arr) {
        if (arr.empty()) return;
        
        int maxVal = *std::max_element(arr.begin(), arr.end());
        int minVal = *std::min_element(arr.begin(), arr.end());
        int range = maxVal - minVal + 1;
        int bucketCount = std::sqrt(arr.size());
        if (bucketCount == 0) bucketCount = 1;
        
        std::vector<std::vector<int>> buckets(bucketCount);
        
        // Put array elements in different buckets
        for (int num : arr) {
            int bucketIndex = (num - minVal) * bucketCount / range;
            if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1;
            buckets[bucketIndex].push_back(num);
        }
        
        // Sort individual buckets
        for (auto& bucket : buckets) {
            std::sort(bucket.begin(), bucket.end());
        }
        
        // Concatenate all buckets
        int index = 0;
        for (const auto& bucket : buckets) {
            for (int num : bucket) {
                arr[index++] = num;
            }
        }
    }
    
    static void bucketSortWithVisualization(std::vector<int>& arr) {
        if (arr.empty()) return;
        
        std::cout << "Bucket Sort Step-by-Step:\n";
        printArray(arr, "Initial Array");
        
        int maxVal = *std::max_element(arr.begin(), arr.end());
        int minVal = *std::min_element(arr.begin(), arr.end());
        int range = maxVal - minVal + 1;
        int bucketCount = std::sqrt(arr.size());
        if (bucketCount == 0) bucketCount = 1;
        
        std::cout << "Range: [" << minVal << ", " << maxVal << "], Bucket count: " << bucketCount << "\n";
        
        std::vector<std::vector<int>> buckets(bucketCount);
        
        // Put array elements in different buckets
        for (int num : arr) {
            int bucketIndex = (num - minVal) * bucketCount / range;
            if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1;
            buckets[bucketIndex].push_back(num);
            std::cout << "Putting " << num << " in bucket " << bucketIndex << "\n";
        }
        
        std::cout << "\nBuckets before sorting:\n";
        for (int i = 0; i < buckets.size(); i++) {
            std::cout << "Bucket " << i << ": [";
            for (int j = 0; j < buckets[i].size(); j++) {
                std::cout << buckets[i][j];
                if (j < buckets[i].size() - 1) std::cout << ", ";
            }
            std::cout << "]\n";
        }
        
        // Sort individual buckets
        for (auto& bucket : buckets) {
            std::sort(bucket.begin(), bucket.end());
        }
        
        std::cout << "\nBuckets after sorting:\n";
        for (int i = 0; i < buckets.size(); i++) {
            std::cout << "Bucket " << i << ": [";
            for (int j = 0; j < buckets[i].size(); j++) {
                std::cout << buckets[i][j];
                if (j < buckets[i].size() - 1) std::cout << ", ";
            }
            std::cout << "]\n";
        }
        
        // Concatenate all buckets
        int index = 0;
        for (const auto& bucket : buckets) {
            for (int num : bucket) {
                arr[index++] = num;
            }
        }
        
        printArray(arr, "Final Sorted Array");
    }
    
    // Performance comparison of all algorithms
    static void performanceComparison(std::vector<int>& arr, const std::string& caseType) {
        std::cout << "Performance Comparison (" << caseType << ", size: " << arr.size() << "):\n";
        std::cout << std::setw(15) << "Algorithm" << std::setw(15) << "Time (μs)" << std::setw(15) << "Space" << "\n";
        std::cout << std::string(45, '─') << "\n";
        
        // Merge Sort
        std::vector<int> mergeCopy = arr;
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(mergeCopy);
        auto end = std::chrono::high_resolution_clock::now();
        auto mergeDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(15) << "Merge Sort" << std::setw(15) << mergeDuration.count() << std::setw(15) << "O(n)" << "\n";
        
        // Heap Sort
        std::vector<int> heapCopy = arr;
        start = std::chrono::high_resolution_clock::now();
        heapSort(heapCopy);
        end = std::chrono::high_resolution_clock::now();
        auto heapDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(15) << "Heap Sort" << std::setw(15) << heapDuration.count() << std::setw(15) << "O(1)" << "\n";
        
        // Check if array is suitable for counting sort (small range)
        int maxVal = *std::max_element(arr.begin(), arr.end());
        int minVal = *std::min_element(arr.begin(), arr.end());
        if (maxVal - minVal < 10000) {
            std::vector<int> countCopy = arr;
            start = std::chrono::high_resolution_clock::now();
            countingSort(countCopy);
            end = std::chrono::high_resolution_clock::now();
            auto countDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << std::setw(15) << "Counting Sort" << std::setw(15) << countDuration.count() << std::setw(15) << "O(k)" << "\n";
        }
        
        // Radix Sort (positive integers only)
        if (minVal >= 0) {
            std::vector<int> radixCopy = arr;
            start = std::chrono::high_resolution_clock::now();
            radixSort(radixCopy);
            end = std::chrono::high_resolution_clock::now();
            auto radixDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << std::setw(15) << "Radix Sort" << std::setw(15) << radixDuration.count() << std::setw(15) << "O(n)" << "\n";
        }
        
        // Bucket Sort
        std::vector<int> bucketCopy = arr;
        start = std::chrono::high_resolution_clock::now();
        bucketSortInteger(bucketCopy);
        end = std::chrono::high_resolution_clock::now();
        auto bucketDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(15) << "Bucket Sort" << std::setw(15) << bucketDuration.count() << std::setw(15) << "O(n)" << "\n";
        
        std::cout << "\n";
    }

private:
    // Merge sort helper functions
    static void mergeSortRecursive(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            mergeSortRecursive(arr, left, mid);
            mergeSortRecursive(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
    static void mergeSortVisual(std::vector<int>& arr, int left, int right, int depth) {
        if (left < right) {
            std::string indent(depth * 2, ' ');
            std::cout << indent << "Dividing [" << left << ", " << right << "]: ";
            for (int i = left; i <= right; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << "\n";
            
            int mid = left + (right - left) / 2;
            
            mergeSortVisual(arr, left, mid, depth + 1);
            mergeSortVisual(arr, mid + 1, right, depth + 1);
            
            std::cout << indent << "Merging [" << left << ", " << mid << "] and [" 
                      << mid + 1 << ", " << right << "]\n";
            merge(arr, left, mid, right);
            
            std::cout << indent << "Result: ";
            for (int i = left; i <= right; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << "\n";
        }
    }
    
    static void merge(std::vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        std::vector<int> leftArr(n1);
        std::vector<int> rightArr(n2);
        
        for (int i = 0; i < n1; i++) {
            leftArr[i] = arr[left + i];
        }
        for (int j = 0; j < n2; j++) {
            rightArr[j] = arr[mid + 1 + j];
        }
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
    
    // Heap sort helper functions
    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
    
    // Radix sort helper function
    static void countingSortByDigit(std::vector<int>& arr, int exp) {
        std::vector<int> output(arr.size());
        std::vector<int> count(10, 0);
        
        // Count occurrences of digits
        for (int num : arr) {
            count[(num / exp) % 10]++;
        }
        
        // Change count[i] to store actual position
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        // Build output array
        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        
        arr = output;
    }
    
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

std::vector<double> generateRandomDoubleArray(int size, double minVal = 0.0, double maxVal = 1.0) {
    std::vector<double> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(minVal, maxVal);
    
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    
    return arr;
}

int main() {
    std::cout << "=== ADVANCED SORTING ALGORITHMS DEMONSTRATION ===\n\n";
    
    // 1. MERGE SORT
    std::cout << "1. MERGE SORT DEMONSTRATION:\n";
    std::vector<int> mergeArray = {12, 11, 13, 5, 6, 7};
    std::cout << "Characteristics: Stable, O(n log n) always, O(n) space\n";
    AdvancedSortingAlgorithms::mergeSortWithVisualization(mergeArray);
    std::cout << "\n";
    
    // 2. HEAP SORT
    std::cout << "2. HEAP SORT DEMONSTRATION:\n";
    std::vector<int> heapArray = {12, 11, 13, 5, 6, 7};
    std::cout << "Characteristics: Unstable, O(n log n) always, O(1) space\n";
    AdvancedSortingAlgorithms::heapSortWithVisualization(heapArray);
    std::cout << "\n";
    
    // 3. COUNTING SORT
    std::cout << "3. COUNTING SORT DEMONSTRATION:\n";
    std::vector<int> countArray = {4, 2, 2, 8, 3, 3, 1};
    std::cout << "Characteristics: Stable, O(n + k), best for small range\n";
    AdvancedSortingAlgorithms::countingSortWithVisualization(countArray);
    std::cout << "\n";
    
    // 4. RADIX SORT
    std::cout << "4. RADIX SORT DEMONSTRATION:\n";
    std::vector<int> radixArray = {170, 45, 75, 90, 2, 802, 24, 66};
    std::cout << "Characteristics: Stable, O(d(n + k)), good for integers\n";
    AdvancedSortingAlgorithms::radixSortWithVisualization(radixArray);
    std::cout << "\n";
    
    // 5. BUCKET SORT
    std::cout << "5. BUCKET SORT DEMONSTRATION:\n";
    std::vector<int> bucketArray = {29, 25, 3, 49, 9, 37, 21, 43};
    std::cout << "Characteristics: Stable, O(n + k) average, good for uniform distribution\n";
    AdvancedSortingAlgorithms::bucketSortWithVisualization(bucketArray);
    std::cout << "\n";
    
    // Bucket sort with floating point numbers
    std::cout << "6. BUCKET SORT WITH FLOATING POINT NUMBERS:\n";
    std::vector<double> doubleBucketArray = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    std::cout << "Original array: [";
    for (int i = 0; i < doubleBucketArray.size(); i++) {
        std::cout << std::fixed << std::setprecision(4) << doubleBucketArray[i];
        if (i < doubleBucketArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    AdvancedSortingAlgorithms::bucketSort(doubleBucketArray);
    
    std::cout << "Sorted array: [";
    for (int i = 0; i < doubleBucketArray.size(); i++) {
        std::cout << std::fixed << std::setprecision(4) << doubleBucketArray[i];
        if (i < doubleBucketArray.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n\n";
    
    // 7. PERFORMANCE COMPARISON
    std::cout << "7. PERFORMANCE COMPARISON:\n\n";
    
    // Random data
    std::vector<int> randomData = generateRandomArray(10000, 1, 1000);
    AdvancedSortingAlgorithms::performanceComparison(randomData, "Random Data");
    
    // Small range data (good for counting sort)
    std::vector<int> smallRangeData = generateRandomArray(10000, 1, 50);
    AdvancedSortingAlgorithms::performanceComparison(smallRangeData, "Small Range Data");
    
    // Large numbers (good for radix sort)
    std::vector<int> largeNumberData = generateRandomArray(5000, 1000, 99999);
    AdvancedSortingAlgorithms::performanceComparison(largeNumberData, "Large Numbers");
    
    // 8. ALGORITHM SELECTION GUIDE
    std::cout << "8. ALGORITHM SELECTION GUIDE:\n";
    std::cout << "┌─────────────────────────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ Algorithm      │ Best Case     │ Average Case  │ Worst Case    │ Space    │ Stable │\n";
    std::cout << "├─────────────────────────────────────────────────────────────────────────────────────┤\n";
    std::cout << "│ Merge Sort     │ O(n log n)    │ O(n log n)    │ O(n log n)    │ O(n)     │ Yes    │\n";
    std::cout << "│ Heap Sort      │ O(n log n)    │ O(n log n)    │ O(n log n)    │ O(1)     │ No     │\n";
    std::cout << "│ Counting Sort  │ O(n + k)      │ O(n + k)      │ O(n + k)      │ O(k)     │ Yes    │\n";
    std::cout << "│ Radix Sort     │ O(d(n + k))   │ O(d(n + k))   │ O(d(n + k))   │ O(n + k) │ Yes    │\n";
    std::cout << "│ Bucket Sort    │ O(n + k)      │ O(n + k)      │ O(n²)         │ O(n + k) │ Yes    │\n";
    std::cout << "└─────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    
    std::cout << "When to use each algorithm:\n";
    std::cout << "• Merge Sort: General purpose, stable sorting, guaranteed O(n log n)\n";
    std::cout << "• Heap Sort: When memory is limited, guaranteed O(n log n), in-place\n";
    std::cout << "• Counting Sort: Small range integers, when k is small compared to n\n";
    std::cout << "• Radix Sort: Large integers, when digits are limited\n";
    std::cout << "• Bucket Sort: Uniformly distributed data, floating point numbers\n\n";
    
    // 9. REAL-WORLD APPLICATIONS
    std::cout << "9. REAL-WORLD APPLICATIONS:\n\n";
    
    // Student grade sorting with merge sort (stable)
    std::cout << "A. Student Grade Sorting (Merge Sort - Stability Important):\n";
    struct Student {
        std::string name;
        int grade;
        std::string subject;
    };
    
    std::vector<Student> students = {
        {"Alice", 85, "Math"},
        {"Bob", 90, "Physics"},
        {"Charlie", 85, "Chemistry"},  // Same grade as Alice
        {"David", 92, "Math"},
        {"Eve", 85, "Physics"}         // Same grade as Alice and Charlie
    };
    
    std::cout << "Students before sorting:\n";
    for (const auto& s : students) {
        std::cout << s.name << " - " << s.grade << " (" << s.subject << ")\n";
    }
    
    // Sort by grade while maintaining original order for equal grades
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.grade < b.grade;
    });
    
    std::cout << "\nStudents after stable sorting by grade:\n";
    for (const auto& s : students) {
        std::cout << s.name << " - " << s.grade << " (" << s.subject << ")\n";
    }
    std::cout << "Note: Students with same grades maintain their relative order\n\n";
    
    // Age group counting (counting sort)
    std::cout << "B. Age Group Analysis (Counting Sort):\n";
    std::vector<int> ages = {23, 25, 23, 30, 28, 25, 23, 30, 28, 25, 30, 23};
    std::cout << "Ages: [";
    for (int i = 0; i < ages.size(); i++) {
        std::cout << ages[i];
        if (i < ages.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    AdvancedSortingAlgorithms::countingSort(ages);
    
    std::cout << "Sorted ages: [";
    for (int i = 0; i < ages.size(); i++) {
        std::cout << ages[i];
        if (i < ages.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    std::cout << "Perfect for age data with limited range!\n\n";
    
    // Phone number sorting (radix sort)
    std::cout << "C. Phone Number Sorting (Radix Sort concept):\n";
    std::vector<int> phoneNumbers = {5551234, 5559876, 5551111, 5558888, 5552222};
    std::cout << "Phone numbers: [";
    for (int i = 0; i < phoneNumbers.size(); i++) {
        std::cout << phoneNumbers[i];
        if (i < phoneNumbers.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    AdvancedSortingAlgorithms::radixSort(phoneNumbers);
    
    std::cout << "Sorted phone numbers: [";
    for (int i = 0; i < phoneNumbers.size(); i++) {
        std::cout << phoneNumbers[i];
        if (i < phoneNumbers.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    std::cout << "Radix sort is efficient for fixed-width integer data!\n\n";
    
    std::cout << "=== ADVANCED SORTING ALGORITHMS SUMMARY ===\n";
    std::cout << "\nKey Characteristics:\n";
    
    std::cout << "\n1. MERGE SORT:\n";
    std::cout << "   • Always O(n log n) - predictable performance\n";
    std::cout << "   • Stable - maintains relative order of equal elements\n";
    std::cout << "   • Requires O(n) extra space\n";
    std::cout << "   • Excellent for large datasets and linked lists\n";
    std::cout << "   • Used in: External sorting, when stability is required\n";
    
    std::cout << "\n2. HEAP SORT:\n";
    std::cout << "   • Always O(n log n) - guaranteed performance\n";
    std::cout << "   • In-place - requires only O(1) extra space\n";
    std::cout << "   • Not stable - may change relative order of equal elements\n";
    std::cout << "   • Used in: Memory-constrained environments, priority queues\n";
    
    std::cout << "\n3. COUNTING SORT:\n";
    std::cout << "   • Linear time O(n + k) when range k is small\n";
    std::cout << "   • Stable - preserves original order\n";
    std::cout << "   • Requires O(k) extra space for counting array\n";
    std::cout << "   • Used in: Small integer ranges, as subroutine in radix sort\n";
    
    std::cout << "\n4. RADIX SORT:\n";
    std::cout << "   • O(d(n + k)) where d is number of digits\n";
    std::cout << "   • Stable - important for multi-key sorting\n";
    std::cout << "   • Works well for fixed-width integer data\n";
    std::cout << "   • Used in: Large integer datasets, string sorting\n";
    
    std::cout << "\n5. BUCKET SORT:\n";
    std::cout << "   • O(n + k) average case for uniform distribution\n";
    std::cout << "   • O(n²) worst case if data clusters in few buckets\n";
    std::cout << "   • Stable - uses stable sort within buckets\n";
    std::cout << "   • Used in: Uniformly distributed data, floating-point numbers\n";
    
    return 0;
}
