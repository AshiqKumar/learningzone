/*
 * Specialized Sorting Algorithms Implementation
 * 
 * This file contains additional specialized sorting algorithms:
 * 1. Tim Sort (Hybrid merge-insertion sort)
 * 2. Intro Sort (Introspective Sort)
 * 3. Cycle Sort (Minimum writes)
 * 4. Pancake Sort (Flipping algorithm)
 * 5. Bogo Sort (Random sort - educational/humorous)
 * 6. Gnome Sort (Simple comparison sort)
 * 7. Comb Sort (Improved bubble sort)
 * 8. Bitonic Sort (Parallel sorting network)
 * 9. Sleep Sort (Time-based sorting)
 * 10. Strand Sort (Natural merge variant)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <random>
#include <iomanip>
#include <cmath>
#include <thread>
#include <future>
#include <stack>
#include <queue>
#include <functional>

class SpecializedSortingAlgorithms {
public:
    
    // TIM SORT (Simplified implementation)
    // Production sorting algorithm used in Python and Java
    // Hybrid of merge sort and insertion sort with run detection
    static void timSort(std::vector<int>& arr) {
        const int MIN_MERGE = 32;
        int n = arr.size();
        
        // Sort individual subarrays of size MIN_MERGE using insertion sort
        for (int i = 0; i < n; i += MIN_MERGE) {
            int right = std::min(i + MIN_MERGE - 1, n - 1);
            insertionSort(arr, i, right);
        }
        
        // Start merging from size MIN_MERGE
        for (int size = MIN_MERGE; size < n; size *= 2) {
            for (int start = 0; start < n; start += size * 2) {
                int mid = start + size - 1;
                int end = std::min(start + size * 2 - 1, n - 1);
                
                if (mid < end) {
                    merge(arr, start, mid, end);
                }
            }
        }
    }
    
    static void timSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Tim Sort Step-by-Step (Simplified):\n";
        printArray(arr, "Initial Array");
        
        const int MIN_MERGE = 4; // Smaller for demonstration
        int n = arr.size();
        
        std::cout << "\nPhase 1: Insertion sort on small runs (size " << MIN_MERGE << "):\n";
        
        // Sort individual subarrays using insertion sort
        for (int i = 0; i < n; i += MIN_MERGE) {
            int right = std::min(i + MIN_MERGE - 1, n - 1);
            std::cout << "Sorting subarray [" << i << ", " << right << "]: ";
            for (int k = i; k <= right; k++) {
                std::cout << arr[k] << " ";
            }
            std::cout << "\n";
            
            insertionSort(arr, i, right);
            
            std::cout << "After sorting: ";
            for (int k = i; k <= right; k++) {
                std::cout << arr[k] << " ";
            }
            std::cout << "\n";
        }
        
        std::cout << "\nPhase 2: Merging runs:\n";
        
        // Start merging
        for (int size = MIN_MERGE; size < n; size *= 2) {
            std::cout << "Merge size: " << size << "\n";
            for (int start = 0; start < n; start += size * 2) {
                int mid = start + size - 1;
                int end = std::min(start + size * 2 - 1, n - 1);
                
                if (mid < end) {
                    std::cout << "  Merging [" << start << ", " << mid << "] and [" 
                              << (mid + 1) << ", " << end << "]\n";
                    merge(arr, start, mid, end);
                }
            }
            std::cout << "  Array after merge phase: ";
            printArrayInline(arr);
        }
    }
    
    // INTRO SORT (Introspective Sort)
    // Hybrid algorithm: Quick sort -> Heap sort -> Insertion sort
    // Used in C++ STL std::sort
    static void introSort(std::vector<int>& arr) {
        int maxDepth = 2 * log2(arr.size());
        introSortRecursive(arr, 0, arr.size() - 1, maxDepth);
    }
    
    static void introSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Intro Sort Step-by-Step:\n";
        printArray(arr, "Initial Array");
        
        int maxDepth = 2 * log2(arr.size());
        std::cout << "Maximum recursion depth: " << maxDepth << "\n\n";
        
        introSortRecursiveVisual(arr, 0, arr.size() - 1, maxDepth, 0);
    }
    
    // CYCLE SORT
    // Minimizes the number of writes to the original array
    // Useful when write operations are expensive
    static void cycleSort(std::vector<int>& arr) {
        int writes = 0;
        
        for (int cycleStart = 0; cycleStart < arr.size() - 1; cycleStart++) {
            int item = arr[cycleStart];
            int pos = cycleStart;
            
            // Find position where we put the item
            for (int i = cycleStart + 1; i < arr.size(); i++) {
                if (arr[i] < item) {
                    pos++;
                }
            }
            
            // If item is already in correct position
            if (pos == cycleStart) continue;
            
            // Skip duplicates
            while (item == arr[pos]) {
                pos++;
            }
            
            // Put the item in its correct position
            if (pos != cycleStart) {
                std::swap(item, arr[pos]);
                writes++;
            }
            
            // Rotate the rest of the cycle
            while (pos != cycleStart) {
                pos = cycleStart;
                
                // Find position where we put the element
                for (int i = cycleStart + 1; i < arr.size(); i++) {
                    if (arr[i] < item) {
                        pos++;
                    }
                }
                
                // Skip duplicates
                while (item == arr[pos]) {
                    pos++;
                }
                
                // Put the item in its correct position
                if (item != arr[pos]) {
                    std::swap(item, arr[pos]);
                    writes++;
                }
            }
        }
        
        std::cout << "Total writes performed: " << writes << "\n";
    }
    
    // PANCAKE SORT
    // Only allowed operation is to flip the array from position 0 to some position i
    static void pancakeSort(std::vector<int>& arr) {
        for (int currSize = arr.size(); currSize > 1; currSize--) {
            // Find index of maximum element in current size
            int maxIdx = findMaxIndex(arr, currSize);
            
            // If maximum is not at the end, do following steps
            if (maxIdx != currSize - 1) {
                // First flip to bring maximum to front if it's not already there
                if (maxIdx != 0) {
                    flip(arr, maxIdx);
                }
                
                // Now flip to bring maximum to the end
                flip(arr, currSize - 1);
            }
        }
    }
    
    static void pancakeSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Pancake Sort Step-by-Step:\n";
        std::cout << "Goal: Sort by only flipping prefixes of the array\n";
        printArray(arr, "Initial Array");
        
        for (int currSize = arr.size(); currSize > 1; currSize--) {
            std::cout << "\nSorting elements 0 to " << (currSize - 1) << "\n";
            
            // Find index of maximum element in current size
            int maxIdx = findMaxIndex(arr, currSize);
            std::cout << "Maximum element " << arr[maxIdx] << " at position " << maxIdx << "\n";
            
            if (maxIdx != currSize - 1) {
                if (maxIdx != 0) {
                    std::cout << "Flipping array from 0 to " << maxIdx << " to bring max to front\n";
                    flip(arr, maxIdx);
                    std::cout << "After flip: ";
                    printArrayInline(arr);
                }
                
                std::cout << "Flipping array from 0 to " << (currSize - 1) << " to bring max to position " << (currSize - 1) << "\n";
                flip(arr, currSize - 1);
                std::cout << "After flip: ";
                printArrayInline(arr);
            }
        }
    }
    
    // BOGO SORT (Permutation Sort)
    // Randomly shuffles array until it's sorted
    // Extremely inefficient - for educational/humor purposes
    static void bogoSort(std::vector<int>& arr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        int attempts = 0;
        const int MAX_ATTEMPTS = 1000000; // Safety limit
        
        while (!isSorted(arr) && attempts < MAX_ATTEMPTS) {
            std::shuffle(arr.begin(), arr.end(), gen);
            attempts++;
        }
        
        std::cout << "Bogo Sort completed in " << attempts << " attempts!\n";
        if (attempts >= MAX_ATTEMPTS) {
            std::cout << "Warning: Reached maximum attempts limit.\n";
        }
    }
    
    // GNOME SORT (Stupid Sort)
    // Simple comparison sort similar to insertion sort
    static void gnomeSort(std::vector<int>& arr) {
        int index = 0;
        while (index < arr.size()) {
            if (index == 0) {
                index++;
            } else if (arr[index] >= arr[index - 1]) {
                index++;
            } else {
                std::swap(arr[index], arr[index - 1]);
                index--;
            }
        }
    }
    
    static void gnomeSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Gnome Sort Step-by-Step:\n";
        std::cout << "Algorithm: Move forward if in order, swap and move backward if not\n";
        printArray(arr, "Initial Array");
        
        int index = 0;
        int step = 1;
        
        while (index < arr.size()) {
            std::cout << "\nStep " << step++ << ": Position " << index;
            
            if (index == 0) {
                std::cout << " (at start, move forward)\n";
                index++;
            } else if (arr[index] >= arr[index - 1]) {
                std::cout << " (" << arr[index] << " >= " << arr[index-1] << ", move forward)\n";
                index++;
            } else {
                std::cout << " (" << arr[index] << " < " << arr[index-1] << ", swap and move backward)\n";
                std::swap(arr[index], arr[index - 1]);
                index--;
            }
            
            std::cout << "Array: ";
            for (int i = 0; i < arr.size(); i++) {
                if (i == index) std::cout << "[" << arr[i] << "] ";
                else std::cout << arr[i] << " ";
            }
            std::cout << "\n";
        }
    }
    
    // COMB SORT
    // Improvement over bubble sort using gap sequence
    static void combSort(std::vector<int>& arr) {
        int n = arr.size();
        int gap = n;
        const double shrink = 1.3;
        bool swapped = true;
        
        while (gap != 1 || swapped) {
            gap = getNextGap(gap, shrink);
            swapped = false;
            
            for (int i = 0; i < n - gap; i++) {
                if (arr[i] > arr[i + gap]) {
                    std::swap(arr[i], arr[i + gap]);
                    swapped = true;
                }
            }
        }
    }
    
    static void combSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Comb Sort Step-by-Step:\n";
        std::cout << "Improvement over bubble sort using shrinking gap\n";
        printArray(arr, "Initial Array");
        
        int n = arr.size();
        int gap = n;
        const double shrink = 1.3;
        bool swapped = true;
        int iteration = 1;
        
        while (gap != 1 || swapped) {
            gap = getNextGap(gap, shrink);
            swapped = false;
            
            std::cout << "\nIteration " << iteration++ << " with gap = " << gap << "\n";
            
            for (int i = 0; i < n - gap; i++) {
                std::cout << "Comparing arr[" << i << "] = " << arr[i] 
                         << " with arr[" << (i + gap) << "] = " << arr[i + gap];
                
                if (arr[i] > arr[i + gap]) {
                    std::cout << " (swap needed)\n";
                    std::swap(arr[i], arr[i + gap]);
                    swapped = true;
                } else {
                    std::cout << " (no swap)\n";
                }
            }
            
            std::cout << "Array after iteration: ";
            printArrayInline(arr);
        }
    }
    
    // BITONIC SORT
    // Parallel sorting network - works only for power of 2 sizes
    static void bitonicSort(std::vector<int>& arr) {
        if (!isPowerOfTwo(arr.size())) {
            std::cout << "Bitonic Sort requires array size to be power of 2\n";
            // Pad array to next power of 2
            int nextPow2 = 1;
            while (nextPow2 < arr.size()) nextPow2 *= 2;
            
            while (arr.size() < nextPow2) {
                arr.push_back(INT_MAX); // Use max value as padding
            }
        }
        
        bitonicSortRecursive(arr, 0, arr.size(), true);
        
        // Remove padding
        while (!arr.empty() && arr.back() == INT_MAX) {
            arr.pop_back();
        }
    }
    
    // SLEEP SORT (Humorous/Educational)
    // Each element "sleeps" for time proportional to its value
    // Only works for positive integers and is not practical
    static void sleepSort(std::vector<int>& arr) {
        std::cout << "Sleep Sort: Each number sleeps for its value in milliseconds\n";
        std::cout << "Note: This is not a practical sorting algorithm!\n";
        
        if (arr.size() > 20) {
            std::cout << "Array too large for sleep sort demonstration\n";
            return;
        }
        
        // Check for negative numbers
        for (int num : arr) {
            if (num <= 0) {
                std::cout << "Sleep Sort only works with positive integers\n";
                return;
            }
        }
        
        std::vector<int> result;
        std::mutex resultMutex;
        std::vector<std::thread> threads;
        
        for (int num : arr) {
            threads.emplace_back([num, &result, &resultMutex]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(num * 10)); // Scale for demo
                std::lock_guard<std::mutex> lock(resultMutex);
                result.push_back(num);
                std::cout << num << " ";
                std::cout.flush();
            });
        }
        
        std::cout << "Sleeping... Output order: ";
        for (auto& t : threads) {
            t.join();
        }
        std::cout << "\n";
        
        arr = result;
    }
    
    // STRAND SORT
    // Natural merge sort variant that works well with pre-sorted subsequences
    static void strandSort(std::vector<int>& arr) {
        if (arr.empty()) return;
        
        std::vector<int> result;
        std::vector<int> input = arr;
        
        while (!input.empty()) {
            std::vector<int> strand;
            strand.push_back(input[0]);
            input.erase(input.begin());
            
            // Build strand by finding elements in increasing order
            for (auto it = input.begin(); it != input.end();) {
                if (*it >= strand.back()) {
                    strand.push_back(*it);
                    it = input.erase(it);
                } else {
                    ++it;
                }
            }
            
            // Merge strand with result
            result = mergeStrands(result, strand);
        }
        
        arr = result;
    }
    
    static void strandSortWithVisualization(std::vector<int>& arr) {
        std::cout << "Strand Sort Step-by-Step:\n";
        std::cout << "Repeatedly extracts increasing subsequences and merges them\n";
        printArray(arr, "Initial Array");
        
        if (arr.empty()) return;
        
        std::vector<int> result;
        std::vector<int> input = arr;
        int iteration = 1;
        
        while (!input.empty()) {
            std::cout << "\n=== Iteration " << iteration++ << " ===\n";
            std::cout << "Remaining input: ";
            printVectorInline(input);
            
            std::vector<int> strand;
            strand.push_back(input[0]);
            input.erase(input.begin());
            
            std::cout << "Starting strand with: " << strand[0] << "\n";
            
            // Build strand by finding elements in increasing order
            for (auto it = input.begin(); it != input.end();) {
                if (*it >= strand.back()) {
                    std::cout << "Adding " << *it << " to strand (>= " << strand.back() << ")\n";
                    strand.push_back(*it);
                    it = input.erase(it);
                } else {
                    ++it;
                }
            }
            
            std::cout << "Extracted strand: ";
            printVectorInline(strand);
            
            // Merge strand with result
            result = mergeStrands(result, strand);
            std::cout << "Result after merge: ";
            printVectorInline(result);
        }
        
        arr = result;
    }
    
    // Performance comparison of specialized algorithms
    static void performanceComparison(const std::vector<int>& original, const std::string& caseType) {
        std::cout << "Performance Comparison - Specialized Algorithms (" << caseType << ", size: " << original.size() << "):\n";
        std::cout << std::setw(20) << "Algorithm" << std::setw(15) << "Time (μs)" << std::setw(20) << "Special Feature" << "\n";
        std::cout << std::string(55, '─') << "\n";
        
        // Tim Sort
        std::vector<int> arr1 = original;
        auto start = std::chrono::high_resolution_clock::now();
        timSort(arr1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(20) << "Tim Sort" << std::setw(15) << duration1.count() << std::setw(20) << "Adaptive hybrid" << "\n";
        
        // Intro Sort
        std::vector<int> arr2 = original;
        start = std::chrono::high_resolution_clock::now();
        introSort(arr2);
        end = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(20) << "Intro Sort" << std::setw(15) << duration2.count() << std::setw(20) << "Worst-case O(n log n)" << "\n";
        
        // Gnome Sort (only for small arrays)
        if (original.size() <= 100) {
            std::vector<int> arr3 = original;
            start = std::chrono::high_resolution_clock::now();
            gnomeSort(arr3);
            end = std::chrono::high_resolution_clock::now();
            auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << std::setw(20) << "Gnome Sort" << std::setw(15) << duration3.count() << std::setw(20) << "Simple logic" << "\n";
        }
        
        // Comb Sort
        std::vector<int> arr4 = original;
        start = std::chrono::high_resolution_clock::now();
        combSort(arr4);
        end = std::chrono::high_resolution_clock::now();
        auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(20) << "Comb Sort" << std::setw(15) << duration4.count() << std::setw(20) << "Gap-based improvement" << "\n";
        
        // Strand Sort
        std::vector<int> arr5 = original;
        start = std::chrono::high_resolution_clock::now();
        strandSort(arr5);
        end = std::chrono::high_resolution_clock::now();
        auto duration5 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << std::setw(20) << "Strand Sort" << std::setw(15) << duration5.count() << std::setw(20) << "Natural sequences" << "\n";
        
        std::cout << "\n";
    }

private:
    // Helper functions for Tim Sort
    static void insertionSort(std::vector<int>& arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    static void merge(std::vector<int>& arr, int left, int mid, int right) {
        std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
        std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);
        
        int i = 0, j = 0, k = left;
        
        while (i < leftArr.size() && j < rightArr.size()) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k++] = leftArr[i++];
            } else {
                arr[k++] = rightArr[j++];
            }
        }
        
        while (i < leftArr.size()) arr[k++] = leftArr[i++];
        while (j < rightArr.size()) arr[k++] = rightArr[j++];
    }
    
    // Helper functions for Intro Sort
    static void introSortRecursive(std::vector<int>& arr, int low, int high, int depthLimit) {
        if (high - low < 16) {
            insertionSort(arr, low, high);
        } else if (depthLimit == 0) {
            heapSort(arr, low, high);
        } else {
            int pivot = partition(arr, low, high);
            introSortRecursive(arr, low, pivot - 1, depthLimit - 1);
            introSortRecursive(arr, pivot + 1, high, depthLimit - 1);
        }
    }
    
    static void introSortRecursiveVisual(std::vector<int>& arr, int low, int high, int depthLimit, int depth) {
        std::string indent(depth * 2, ' ');
        
        if (high - low < 4) {
            std::cout << indent << "Small subarray [" << low << ", " << high << "] - using insertion sort\n";
            insertionSort(arr, low, high);
        } else if (depthLimit == 0) {
            std::cout << indent << "Depth limit reached for [" << low << ", " << high << "] - using heap sort\n";
            heapSort(arr, low, high);
        } else {
            std::cout << indent << "Quick sort on [" << low << ", " << high << "] (depth limit: " << depthLimit << ")\n";
            int pivot = partition(arr, low, high);
            std::cout << indent << "Pivot at position " << pivot << "\n";
            
            introSortRecursiveVisual(arr, low, pivot - 1, depthLimit - 1, depth + 1);
            introSortRecursiveVisual(arr, pivot + 1, high, depthLimit - 1, depth + 1);
        }
    }
    
    static int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
    static void heapSort(std::vector<int>& arr, int start, int end) {
        int n = end - start + 1;
        std::vector<int> temp(arr.begin() + start, arr.begin() + end + 1);
        
        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(temp, n, i);
        }
        
        // Extract elements
        for (int i = n - 1; i > 0; i--) {
            std::swap(temp[0], temp[i]);
            heapify(temp, i, 0);
        }
        
        // Copy back
        for (int i = 0; i < n; i++) {
            arr[start + i] = temp[i];
        }
    }
    
    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left] > arr[largest]) largest = left;
        if (right < n && arr[right] > arr[largest]) largest = right;
        
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
    
    // Helper functions for Pancake Sort
    static int findMaxIndex(const std::vector<int>& arr, int n) {
        int maxIdx = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i] > arr[maxIdx]) {
                maxIdx = i;
            }
        }
        return maxIdx;
    }
    
    static void flip(std::vector<int>& arr, int i) {
        std::reverse(arr.begin(), arr.begin() + i + 1);
    }
    
    // Helper functions for Comb Sort
    static int getNextGap(int gap, double shrink) {
        gap = static_cast<int>(gap / shrink);
        return gap < 1 ? 1 : gap;
    }
    
    // Helper functions for Bitonic Sort
    static bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
    
    static void bitonicSortRecursive(std::vector<int>& arr, int low, int cnt, bool dir) {
        if (cnt > 1) {
            int k = cnt / 2;
            bitonicSortRecursive(arr, low, k, true);
            bitonicSortRecursive(arr, low + k, k, false);
            bitonicMerge(arr, low, cnt, dir);
        }
    }
    
    static void bitonicMerge(std::vector<int>& arr, int low, int cnt, bool dir) {
        if (cnt > 1) {
            int k = cnt / 2;
            for (int i = low; i < low + k; i++) {
                if ((arr[i] > arr[i + k]) == dir) {
                    std::swap(arr[i], arr[i + k]);
                }
            }
            bitonicMerge(arr, low, k, dir);
            bitonicMerge(arr, low + k, k, dir);
        }
    }
    
    // Helper functions for Strand Sort
    static std::vector<int> mergeStrands(const std::vector<int>& left, const std::vector<int>& right) {
        std::vector<int> result;
        int i = 0, j = 0;
        
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                result.push_back(left[i++]);
            } else {
                result.push_back(right[j++]);
            }
        }
        
        while (i < left.size()) result.push_back(left[i++]);
        while (j < right.size()) result.push_back(right[j++]);
        
        return result;
    }
    
    // Helper functions
    static bool isSorted(const std::vector<int>& arr) {
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i - 1]) return false;
        }
        return true;
    }
    
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
    
    static void printVectorInline(const std::vector<int>& arr) {
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
    std::cout << "=== SPECIALIZED SORTING ALGORITHMS DEMONSTRATION ===\n\n";
    
    // 1. TIM SORT
    std::cout << "1. TIM SORT DEMONSTRATION:\n";
    std::vector<int> timArray = {5, 2, 4, 6, 1, 3, 8, 7, 10, 9, 12, 11};
    std::cout << "Characteristics: Hybrid merge-insertion, adaptive, stable\n";
    std::cout << "Used in: Python sorted(), Java Arrays.sort()\n\n";
    SpecializedSortingAlgorithms::timSortWithVisualization(timArray);
    std::cout << "\n";
    
    // 2. INTRO SORT
    std::cout << "2. INTRO SORT (INTROSPECTIVE SORT) DEMONSTRATION:\n";
    std::vector<int> introArray = {12, 3, 7, 9, 14, 6, 11, 2};
    std::cout << "Characteristics: Hybrid quick-heap-insertion, O(n log n) guaranteed\n";
    std::cout << "Used in: C++ STL std::sort\n\n";
    SpecializedSortingAlgorithms::introSortWithVisualization(introArray);
    std::cout << "\n";
    
    // 3. CYCLE SORT
    std::cout << "3. CYCLE SORT DEMONSTRATION:\n";
    std::vector<int> cycleArray = {20, 30, 10, 40, 50};
    std::cout << "Characteristics: Minimizes writes, unstable, O(n²)\n";
    std::cout << "Best for: When write operations are expensive (e.g., EEPROM)\n\n";
    SpecializedSortingAlgorithms::printArray(cycleArray, "Original Array");
    SpecializedSortingAlgorithms::cycleSort(cycleArray);
    SpecializedSortingAlgorithms::printArray(cycleArray, "Sorted Array");
    std::cout << "\n";
    
    // 4. PANCAKE SORT
    std::cout << "4. PANCAKE SORT DEMONSTRATION:\n";
    std::vector<int> pancakeArray = {3, 1, 4, 1, 5};
    std::cout << "Characteristics: Only flipping allowed, unique constraint\n";
    std::cout << "Application: Sorting with restricted operations\n\n";
    SpecializedSortingAlgorithms::pancakeSortWithVisualization(pancakeArray);
    std::cout << "\n";
    
    // 5. BOGO SORT
    std::cout << "5. BOGO SORT DEMONSTRATION:\n";
    std::vector<int> bogoArray = {3, 1, 2, 4}; // Small array for safety
    std::cout << "Characteristics: Random shuffling, extremely inefficient\n";
    std::cout << "Purpose: Educational/humor, worst possible algorithm\n\n";
    SpecializedSortingAlgorithms::printArray(bogoArray, "Original Array");
    SpecializedSortingAlgorithms::bogoSort(bogoArray);
    SpecializedSortingAlgorithms::printArray(bogoArray, "Sorted Array");
    std::cout << "\n";
    
    // 6. GNOME SORT
    std::cout << "6. GNOME SORT (STUPID SORT) DEMONSTRATION:\n";
    std::vector<int> gnomeArray = {5, 2, 8, 1, 9};
    std::cout << "Characteristics: Simple logic, similar to insertion sort\n";
    std::cout << "Advantage: Very simple to understand and implement\n\n";
    SpecializedSortingAlgorithms::gnomeSortWithVisualization(gnomeArray);
    std::cout << "\n";
    
    // 7. COMB SORT
    std::cout << "7. COMB SORT DEMONSTRATION:\n";
    std::vector<int> combArray = {8, 4, 1, 56, 3, -44, 23, -6, 28, 0};
    std::cout << "Characteristics: Improved bubble sort with gap sequence\n";
    std::cout << "Advantage: Better performance than bubble sort\n\n";
    SpecializedSortingAlgorithms::combSortWithVisualization(combArray);
    std::cout << "\n";
    
    // 8. STRAND SORT
    std::cout << "8. STRAND SORT DEMONSTRATION:\n";
    std::vector<int> strandArray = {10, 5, 30, 40, 2, 4, 9};
    std::cout << "Characteristics: Natural merge variant, adaptive\n";
    std::cout << "Best for: Data with many pre-sorted subsequences\n\n";
    SpecializedSortingAlgorithms::strandSortWithVisualization(strandArray);
    std::cout << "\n";
    
    // 9. SLEEP SORT (if array is small)
    std::cout << "9. SLEEP SORT DEMONSTRATION:\n";
    std::vector<int> sleepArray = {3, 1, 4, 2}; // Very small for demo
    std::cout << "Characteristics: Time-based, parallel, humorous\n";
    std::cout << "Purpose: Educational curiosity, not practical\n\n";
    SpecializedSortingAlgorithms::sleepSort(sleepArray);
    SpecializedSortingAlgorithms::printArray(sleepArray, "Final Result");
    std::cout << "\n";
    
    // 10. PERFORMANCE COMPARISON
    std::cout << "10. PERFORMANCE COMPARISON:\n\n";
    
    // Random data
    std::vector<int> randomData = generateRandomArray(1000);
    SpecializedSortingAlgorithms::performanceComparison(randomData, "Random Data");
    
    // Nearly sorted data
    std::vector<int> nearlySortedData = generateNearlySortedArray(1000, 10);
    SpecializedSortingAlgorithms::performanceComparison(nearlySortedData, "Nearly Sorted Data");
    
    // 11. ALGORITHM CHARACTERISTICS TABLE
    std::cout << "11. SPECIALIZED ALGORITHMS COMPARISON:\n";
    std::cout << "┌──────────────────────────────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│ Algorithm      │ Time Complexity   │ Space │ Stable │ Special Characteristic           │\n";
    std::cout << "├──────────────────────────────────────────────────────────────────────────────────────────┤\n";
    std::cout << "│ Tim Sort       │ O(n) to O(n log n)│ O(n)  │ Yes    │ Adaptive hybrid, real-world use  │\n";
    std::cout << "│ Intro Sort     │ O(n log n)        │ O(log)│ No     │ Guaranteed O(n log n), STL std   │\n";
    std::cout << "│ Cycle Sort     │ O(n²)             │ O(1)  │ No     │ Minimizes memory writes          │\n";
    std::cout << "│ Pancake Sort   │ O(n²)             │ O(1)  │ No     │ Only flipping operations allowed │\n";
    std::cout << "│ Bogo Sort      │ O(∞) avg          │ O(1)  │ No     │ Random shuffling (humor)         │\n";
    std::cout << "│ Gnome Sort     │ O(n²)             │ O(1)  │ Yes    │ Extremely simple logic           │\n";
    std::cout << "│ Comb Sort      │ O(n log n)        │ O(1)  │ No     │ Improved bubble sort with gaps   │\n";
    std::cout << "│ Strand Sort    │ O(n²) worst       │ O(n)  │ Yes    │ Good for pre-sorted subsequences │\n";
    std::cout << "│ Sleep Sort     │ O(max(input))     │ O(n)  │ Yes    │ Time-based, parallel (humor)     │\n";
    std::cout << "│ Bitonic Sort   │ O(n log² n)       │ O(log)│ No     │ Parallel sorting network         │\n";
    std::cout << "└──────────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    
    // 12. REAL-WORLD APPLICATIONS
    std::cout << "12. REAL-WORLD APPLICATIONS:\n\n";
    
    std::cout << "A. Production Sorting Algorithms:\n";
    std::cout << "• Tim Sort: Used in Python's sorted() and sort(), Java's Arrays.sort()\n";
    std::cout << "• Intro Sort: Used in C++ STL std::sort, .NET Framework\n";
    std::cout << "• Dual-Pivot Quick Sort: Used in Java 7+ for primitive arrays\n\n";
    
    std::cout << "B. Specialized Applications:\n";
    std::cout << "• Cycle Sort: Embedded systems with limited write cycles (EEPROM/Flash)\n";
    std::cout << "• Pancake Sort: Robotics with limited operations, stack-based systems\n";
    std::cout << "• Strand Sort: Data streams with natural ordering patterns\n";
    std::cout << "• Bitonic Sort: Parallel computing, GPU sorting kernels\n\n";
    
    std::cout << "C. Educational Value:\n";
    std::cout << "• Gnome Sort: Teaching basic sorting concepts\n";
    std::cout << "• Bogo Sort: Demonstrating algorithmic efficiency importance\n";
    std::cout << "• Sleep Sort: Understanding parallelism and time-based algorithms\n\n";
    
    // 13. ALGORITHM SELECTION GUIDE
    std::cout << "13. WHEN TO USE EACH SPECIALIZED ALGORITHM:\n\n";
    
    std::cout << "Production Ready:\n";
    std::cout << "• Tim Sort: General-purpose stable sorting, mixed data patterns\n";
    std::cout << "• Intro Sort: General-purpose unstable sorting, guaranteed performance\n\n";
    
    std::cout << "Special Constraints:\n";
    std::cout << "• Cycle Sort: When minimizing memory writes is crucial\n";
    std::cout << "• Pancake Sort: When only certain operations are allowed\n";
    std::cout << "• Comb Sort: Simple improvement over bubble sort\n\n";
    
    std::cout << "Data Characteristics:\n";
    std::cout << "• Strand Sort: Data with many pre-sorted runs\n";
    std::cout << "• Bitonic Sort: Parallel processing on power-of-2 datasets\n\n";
    
    std::cout << "Educational/Research:\n";
    std::cout << "• Gnome Sort: Teaching sorting fundamentals\n";
    std::cout << "• Bogo Sort: Demonstrating worst-case scenarios\n";
    std::cout << "• Sleep Sort: Understanding unconventional approaches\n\n";
    
    std::cout << "=== SPECIALIZED SORTING ALGORITHMS SUMMARY ===\n";
    std::cout << "\nKey Insights:\n";
    std::cout << "• Production algorithms like Tim Sort and Intro Sort are carefully engineered hybrids\n";
    std::cout << "• Specialized constraints can lead to unique algorithmic approaches\n";
    std::cout << "• Educational algorithms help understand fundamental concepts\n";
    std::cout << "• Real-world performance often depends on data patterns, not just theoretical complexity\n";
    std::cout << "• Modern sorting libraries use hybrid approaches for optimal performance\n\n";
    
    std::cout << "The landscape of sorting algorithms shows that there's often no single 'best' algorithm,\n";
    std::cout << "but rather different algorithms optimized for different scenarios, constraints, and goals!\n";
    
    return 0;
}
