/*
 * Interpolation Search Algorithm Implementation
 * 
 * Interpolation Search:
 * - Improved version of binary search for uniformly distributed sorted arrays
 * - Uses interpolation formula to estimate position of target
 * - Time Complexity: O(log log n) for uniform distribution, O(n) worst case
 * - Space Complexity: O(1)
 * 
 * Prerequisites:
 * - Array must be sorted
 * - Works best with uniformly distributed data
 * 
 * Applications:
 * - Large sorted datasets with uniform distribution
 * - Phone books, dictionaries
 * - Numerical datasets
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <cmath>
#include <random>

class InterpolationSearch {
public:
    // Basic interpolation search
    static int search(const std::vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left <= right && target >= arr[left] && target <= arr[right]) {
            // If array has only one element
            if (left == right) {
                if (arr[left] == target) return left;
                return -1;
            }
            
            // Calculate position using interpolation formula
            int pos = left + ((double)(target - arr[left]) / (arr[right] - arr[left])) * (right - left);
            
            // Ensure pos is within bounds
            pos = std::max(left, std::min(pos, right));
            
            if (arr[pos] == target) {
                return pos;
            } else if (arr[pos] < target) {
                left = pos + 1;
            } else {
                right = pos - 1;
            }
        }
        
        return -1;  // Element not found
    }
    
    // Interpolation search with step counting
    static int searchWithSteps(const std::vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        int steps = 0;
        
        std::cout << "Interpolation Search Steps for target " << target << ":\n";
        
        while (left <= right && target >= arr[left] && target <= arr[right]) {
            steps++;
            
            if (left == right) {
                std::cout << "Step " << steps << ": Single element at index " << left 
                          << ", arr[" << left << "]=" << arr[left];
                if (arr[left] == target) {
                    std::cout << " -> FOUND!\n";
                    return left;
                } else {
                    std::cout << " -> NOT FOUND\n";
                    return -1;
                }
            }
            
            // Calculate interpolated position
            double ratio = (double)(target - arr[left]) / (arr[right] - arr[left]);
            int pos = left + ratio * (right - left);
            pos = std::max(left, std::min(pos, right));
            
            std::cout << "Step " << steps << ": left=" << left << ", right=" << right 
                      << ", ratio=" << ratio << ", pos=" << pos << ", arr[pos]=" << arr[pos];
            
            if (arr[pos] == target) {
                std::cout << " -> FOUND!\n";
                return pos;
            } else if (arr[pos] < target) {
                std::cout << " -> Go right\n";
                left = pos + 1;
            } else {
                std::cout << " -> Go left\n";
                right = pos - 1;
            }
        }
        
        std::cout << "Element not found after " << steps << " steps.\n";
        return -1;
    }
    
    // Find first occurrence in array with duplicates
    static int findFirstOccurrence(const std::vector<int>& arr, int target) {
        int index = search(arr, target);
        if (index == -1) return -1;
        
        // Move left to find first occurrence
        while (index > 0 && arr[index - 1] == target) {
            index--;
        }
        
        return index;
    }
    
    // Find last occurrence in array with duplicates
    static int findLastOccurrence(const std::vector<int>& arr, int target) {
        int index = search(arr, target);
        if (index == -1) return -1;
        
        // Move right to find last occurrence
        while (index < arr.size() - 1 && arr[index + 1] == target) {
            index++;
        }
        
        return index;
    }
    
    // Count occurrences
    static int countOccurrences(const std::vector<int>& arr, int target) {
        int first = findFirstOccurrence(arr, target);
        if (first == -1) return 0;
        
        int last = findLastOccurrence(arr, target);
        return last - first + 1;
    }
    
    // Interpolation search for floating point numbers
    static int searchDouble(const std::vector<double>& arr, double target, double epsilon = 1e-9) {
        int left = 0;
        int right = arr.size() - 1;
        
        while (left <= right && target >= arr[left] - epsilon && target <= arr[right] + epsilon) {
            if (left == right) {
                if (std::abs(arr[left] - target) <= epsilon) return left;
                return -1;
            }
            
            // Calculate position using interpolation formula
            if (std::abs(arr[right] - arr[left]) <= epsilon) {
                // Array elements are nearly equal, use linear search
                for (int i = left; i <= right; i++) {
                    if (std::abs(arr[i] - target) <= epsilon) return i;
                }
                return -1;
            }
            
            int pos = left + ((target - arr[left]) / (arr[right] - arr[left])) * (right - left);
            pos = std::max(left, std::min(pos, right));
            
            if (std::abs(arr[pos] - target) <= epsilon) {
                return pos;
            } else if (arr[pos] < target) {
                left = pos + 1;
            } else {
                right = pos - 1;
            }
        }
        
        return -1;
    }
    
    // Performance comparison with binary search
    static void performanceComparison(const std::vector<int>& arr, int target) {
        // Interpolation search
        auto start = std::chrono::high_resolution_clock::now();
        int interpResult = search(arr, target);
        auto end = std::chrono::high_resolution_clock::now();
        auto interpDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Binary search for comparison
        start = std::chrono::high_resolution_clock::now();
        int binaryResult = binarySearch(arr, target);
        end = std::chrono::high_resolution_clock::now();
        auto binaryDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Performance Comparison for array size " << arr.size() << ":\n";
        std::cout << "Target: " << target << "\n";
        std::cout << "Interpolation Search: " << (interpResult != -1 ? "Found at " + std::to_string(interpResult) : "Not found") 
                  << " (" << interpDuration.count() << " μs)\n";
        std::cout << "Binary Search: " << (binaryResult != -1 ? "Found at " + std::to_string(binaryResult) : "Not found") 
                  << " (" << binaryDuration.count() << " μs)\n";
        
        if (interpDuration.count() > 0 && binaryDuration.count() > 0) {
            double speedup = (double)binaryDuration.count() / interpDuration.count();
            std::cout << "Speedup: " << speedup << "x\n";
        }
        std::cout << "\n";
    }

private:
    // Binary search for comparison
    static int binarySearch(const std::vector<int>& arr, int target) {
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

void printDoubleArray(const std::vector<double>& arr, const std::string& label, int maxElements = 20) {
    std::cout << label << ": [";
    for (int i = 0; i < std::min(maxElements, static_cast<int>(arr.size())); i++) {
        std::cout << std::fixed << std::setprecision(2) << arr[i];
        if (i < std::min(maxElements, static_cast<int>(arr.size())) - 1) std::cout << ", ";
    }
    if (arr.size() > maxElements) std::cout << "...";
    std::cout << "] (size: " << arr.size() << ")\n";
}

std::vector<int> generateUniformData(int size, int start = 1, int step = 1) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = start + i * step;
    }
    return arr;
}

std::vector<int> generateNonUniformData(int size) {
    std::vector<int> arr;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Generate clusters of data
    for (int cluster = 0; cluster < 5; cluster++) {
        int clusterStart = cluster * 1000;
        int clusterSize = size / 5;
        
        for (int i = 0; i < clusterSize; i++) {
            arr.push_back(clusterStart + i);
        }
    }
    
    std::sort(arr.begin(), arr.end());
    return arr;
}

int main() {
    std::cout << "=== INTERPOLATION SEARCH ALGORITHM DEMONSTRATION ===\n\n";
    
    // Test data - uniform distribution
    std::vector<int> uniformArr = generateUniformData(20, 10, 5);  // 10, 15, 20, 25, ...
    printArray(uniformArr, "Uniform Distribution Array");
    
    // Test data - non-uniform distribution
    std::vector<int> nonUniformArr = {1, 2, 3, 4, 100, 200, 300, 1000, 2000, 5000};
    printArray(nonUniformArr, "Non-Uniform Distribution Array");
    
    std::cout << "\n";
    
    // Basic interpolation search
    std::cout << "1. BASIC INTERPOLATION SEARCH (Uniform Data):\n";
    int target1 = 45;  // Should be at index 7 in uniformArr
    int result1 = InterpolationSearch::search(uniformArr, target1);
    std::cout << "Searching for " << target1 << ": ";
    if (result1 != -1) {
        std::cout << "Found at index " << result1 << "\n";
    } else {
        std::cout << "Not found\n";
    }
    
    int target2 = 99;
    int result2 = InterpolationSearch::search(uniformArr, target2);
    std::cout << "Searching for " << target2 << ": ";
    if (result2 != -1) {
        std::cout << "Found at index " << result2 << "\n";
    } else {
        std::cout << "Not found\n";
    }
    std::cout << "\n";
    
    // Search with steps visualization
    std::cout << "2. INTERPOLATION SEARCH STEP-BY-STEP:\n";
    InterpolationSearch::searchWithSteps(uniformArr, 45);
    std::cout << "\n";
    InterpolationSearch::searchWithSteps(uniformArr, 99);
    std::cout << "\n";
    
    // Non-uniform data performance
    std::cout << "3. SEARCH IN NON-UNIFORM DATA:\n";
    InterpolationSearch::searchWithSteps(nonUniformArr, 200);
    std::cout << "\n";
    InterpolationSearch::searchWithSteps(nonUniformArr, 1500);
    std::cout << "\n";
    
    // Handling duplicates
    std::cout << "4. HANDLING DUPLICATES:\n";
    std::vector<int> duplicatesArr = {10, 10, 20, 20, 20, 30, 40, 40, 50, 50, 50, 50};
    printArray(duplicatesArr, "Array with Duplicates");
    
    int target3 = 20;
    int first = InterpolationSearch::findFirstOccurrence(duplicatesArr, target3);
    int last = InterpolationSearch::findLastOccurrence(duplicatesArr, target3);
    int count = InterpolationSearch::countOccurrences(duplicatesArr, target3);
    
    std::cout << "Target " << target3 << ":\n";
    std::cout << "First occurrence: " << first << "\n";
    std::cout << "Last occurrence: " << last << "\n";
    std::cout << "Total occurrences: " << count << "\n";
    
    target3 = 50;
    first = InterpolationSearch::findFirstOccurrence(duplicatesArr, target3);
    last = InterpolationSearch::findLastOccurrence(duplicatesArr, target3);
    count = InterpolationSearch::countOccurrences(duplicatesArr, target3);
    
    std::cout << "Target " << target3 << ":\n";
    std::cout << "First occurrence: " << first << "\n";
    std::cout << "Last occurrence: " << last << "\n";
    std::cout << "Total occurrences: " << count << "\n\n";
    
    // Floating point search
    std::cout << "5. FLOATING POINT INTERPOLATION SEARCH:\n";
    std::vector<double> doubleArr = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.0};
    printDoubleArray(doubleArr, "Double Array");
    
    double targetDouble = 5.5;
    int doubleResult = InterpolationSearch::searchDouble(doubleArr, targetDouble);
    std::cout << "Searching for " << targetDouble << ": ";
    if (doubleResult != -1) {
        std::cout << "Found at index " << doubleResult << "\n";
    } else {
        std::cout << "Not found\n";
    }
    
    targetDouble = 5.49999;  // Close to 5.5
    doubleResult = InterpolationSearch::searchDouble(doubleArr, targetDouble, 0.01);
    std::cout << "Searching for " << targetDouble << " (with epsilon 0.01): ";
    if (doubleResult != -1) {
        std::cout << "Found at index " << doubleResult << "\n";
    } else {
        std::cout << "Not found\n";
    }
    std::cout << "\n";
    
    // Performance comparison with different data distributions
    std::cout << "6. PERFORMANCE COMPARISON:\n";
    
    // Small uniform array
    std::vector<int> smallUniform = generateUniformData(100, 1, 1);
    InterpolationSearch::performanceComparison(smallUniform, 50);
    
    // Large uniform array
    std::vector<int> largeUniform = generateUniformData(100000, 1, 1);
    InterpolationSearch::performanceComparison(largeUniform, 75000);
    
    // Non-uniform array
    std::vector<int> largeNonUniform = generateNonUniformData(10000);
    InterpolationSearch::performanceComparison(largeNonUniform, 2500);
    
    // Worst case - skewed data
    std::cout << "7. WORST CASE SCENARIO (Skewed Data):\n";
    std::vector<int> skewedArr = {1, 2, 3, 4, 5, 1000000};
    printArray(skewedArr, "Skewed Array");
    
    std::cout << "Searching for 1000000 in skewed data:\n";
    InterpolationSearch::searchWithSteps(skewedArr, 1000000);
    std::cout << "\n";
    
    // Real-world application: Employee ID lookup
    std::cout << "8. REAL-WORLD APPLICATION - Employee Database:\n";
    struct Employee {
        int id;
        std::string name;
        std::string department;
    };
    
    // Generate employee IDs in uniform distribution
    std::vector<int> employeeIds;
    std::vector<Employee> employees;
    
    for (int i = 0; i < 20; i++) {
        int id = 1000 + i * 10;  // 1000, 1010, 1020, ...
        employeeIds.push_back(id);
        employees.push_back({id, "Employee" + std::to_string(i), "Dept" + std::to_string(i % 5)});
    }
    
    std::cout << "Employee IDs (uniform distribution): ";
    for (int i = 0; i < std::min(10, (int)employeeIds.size()); i++) {
        std::cout << employeeIds[i];
        if (i < std::min(10, (int)employeeIds.size()) - 1) std::cout << ", ";
    }
    std::cout << "...\n";
    
    int searchId = 1070;
    int empIndex = InterpolationSearch::search(employeeIds, searchId);
    
    if (empIndex != -1) {
        std::cout << "Employee found: ID=" << employees[empIndex].id 
                  << ", Name=" << employees[empIndex].name 
                  << ", Department=" << employees[empIndex].department << "\n";
    } else {
        std::cout << "Employee with ID " << searchId << " not found\n";
    }
    std::cout << "\n";
    
    // Analysis of different data distributions
    std::cout << "9. ANALYSIS OF DATA DISTRIBUTION EFFECTS:\n";
    
    // Arithmetic progression (best case)
    std::vector<int> arithmetic = generateUniformData(1000, 100, 2);
    auto start = std::chrono::high_resolution_clock::now();
    InterpolationSearch::search(arithmetic, 600);
    auto end = std::chrono::high_resolution_clock::now();
    auto arithmeticTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    // Random sorted data
    std::vector<int> randomData(1000);
    std::iota(randomData.begin(), randomData.end(), 1);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(randomData.begin(), randomData.end(), g);
    std::sort(randomData.begin(), randomData.end());
    
    start = std::chrono::high_resolution_clock::now();
    InterpolationSearch::search(randomData, 600);
    end = std::chrono::high_resolution_clock::now();
    auto randomTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "Uniform distribution (arithmetic progression): " << arithmeticTime.count() << " ns\n";
    std::cout << "Random distribution: " << randomTime.count() << " ns\n";
    std::cout << "Performance ratio: " << (double)randomTime.count() / arithmeticTime.count() << "\n\n";
    
    std::cout << "=== INTERPOLATION SEARCH SUMMARY ===\n";
    std::cout << "Advantages:\n";
    std::cout << "- O(log log n) average time complexity for uniform data\n";
    std::cout << "- Better than binary search for uniformly distributed data\n";
    std::cout << "- Adaptive positioning based on data distribution\n";
    std::cout << "- Space efficient O(1)\n";
    std::cout << "\nDisadvantages:\n";
    std::cout << "- O(n) worst case for non-uniform data\n";
    std::cout << "- Requires sorted data\n";
    std::cout << "- Performance depends heavily on data distribution\n";
    std::cout << "- More complex than binary search\n";
    std::cout << "\nBest Use Cases:\n";
    std::cout << "- Large uniformly distributed datasets\n";
    std::cout << "- Numerical data with known distribution\n";
    std::cout << "- Phone books, dictionaries with uniform entries\n";
    std::cout << "- When data access pattern is predictable\n";
    std::cout << "\nWhen to Avoid:\n";
    std::cout << "- Small datasets (overhead not worth it)\n";
    std::cout << "- Highly skewed or clustered data\n";
    std::cout << "- When data distribution is unknown\n";
    std::cout << "- String data without numeric properties\n";
    
    return 0;
}
