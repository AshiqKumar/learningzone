/*
 * Linear Search Algorithm Implementation
 * 
 * Linear Search (Sequential Search):
 * - Searches for a target element by checking each element one by one
 * - Works on both sorted and unsorted arrays
 * - Time Complexity: O(n)
 * - Space Complexity: O(1)
 * 
 * Applications:
 * - Small datasets
 * - Unsorted data
 * - When simplicity is preferred over efficiency
 * - First occurrence finding
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>

class LinearSearch {
public:
    // Basic linear search for integers
    static int search(const std::vector<int>& arr, int target) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) {
                return i;  // Return index of found element
            }
        }
        return -1;  // Element not found
    }
    
    // Linear search with all occurrences
    static std::vector<int> searchAll(const std::vector<int>& arr, int target) {
        std::vector<int> indices;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) {
                indices.push_back(i);
            }
        }
        return indices;
    }
    
    // Template version for any comparable type
    template<typename T>
    static int searchGeneric(const std::vector<T>& arr, const T& target) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) {
                return i;
            }
        }
        return -1;
    }
    
    // Linear search with custom comparator
    template<typename T, typename Compare>
    static int searchWithComparator(const std::vector<T>& arr, const T& target, Compare comp) {
        for (int i = 0; i < arr.size(); i++) {
            if (comp(arr[i], target)) {
                return i;
            }
        }
        return -1;
    }
    
    // Count occurrences
    static int countOccurrences(const std::vector<int>& arr, int target) {
        int count = 0;
        for (const int& element : arr) {
            if (element == target) {
                count++;
            }
        }
        return count;
    }
    
    // Find minimum element
    static int findMin(const std::vector<int>& arr) {
        if (arr.empty()) return -1;
        
        int minVal = arr[0];
        int minIndex = 0;
        
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] < minVal) {
                minVal = arr[i];
                minIndex = i;
            }
        }
        return minIndex;
    }
    
    // Find maximum element
    static int findMax(const std::vector<int>& arr) {
        if (arr.empty()) return -1;
        
        int maxVal = arr[0];
        int maxIndex = 0;
        
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > maxVal) {
                maxVal = arr[i];
                maxIndex = i;
            }
        }
        return maxIndex;
    }
    
    // Search in 2D array
    static std::pair<int, int> search2D(const std::vector<std::vector<int>>& matrix, int target) {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] == target) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }
    
    // Performance analysis
    static void performanceAnalysis(const std::vector<int>& arr, int target) {
        auto start = std::chrono::high_resolution_clock::now();
        
        int result = search(arr, target);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Linear Search Performance:\n";
        std::cout << "Array size: " << arr.size() << "\n";
        std::cout << "Target: " << target << "\n";
        std::cout << "Result: " << (result != -1 ? "Found at index " + std::to_string(result) : "Not found") << "\n";
        std::cout << "Time taken: " << duration.count() << " microseconds\n";
        std::cout << "Comparisons made: " << (result != -1 ? result + 1 : arr.size()) << "\n\n";
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

void printIndices(const std::vector<int>& indices, int target) {
    if (indices.empty()) {
        std::cout << "Target " << target << " not found\n";
    } else {
        std::cout << "Target " << target << " found at indices: ";
        for (int i = 0; i < indices.size(); i++) {
            std::cout << indices[i];
            if (i < indices.size() - 1) std::cout << ", ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::cout << "=== LINEAR SEARCH ALGORITHM DEMONSTRATION ===\n\n";
    
    // Test data
    std::vector<int> arr = {64, 25, 12, 22, 11, 90, 25, 77, 34, 25};
    std::vector<int> sortedArr = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
    
    printArray(arr, "Original Array");
    printArray(sortedArr, "Sorted Array");
    std::cout << "\n";
    
    // Basic linear search
    std::cout << "1. BASIC LINEAR SEARCH:\n";
    int target1 = 25;
    int result1 = LinearSearch::search(arr, target1);
    std::cout << "Searching for " << target1 << ": ";
    if (result1 != -1) {
        std::cout << "Found at index " << result1 << "\n";
    } else {
        std::cout << "Not found\n";
    }
    
    int target2 = 99;
    int result2 = LinearSearch::search(arr, target2);
    std::cout << "Searching for " << target2 << ": ";
    if (result2 != -1) {
        std::cout << "Found at index " << result2 << "\n";
    } else {
        std::cout << "Not found\n";
    }
    std::cout << "\n";
    
    // Search all occurrences
    std::cout << "2. FIND ALL OCCURRENCES:\n";
    std::vector<int> allOccurrences = LinearSearch::searchAll(arr, 25);
    printIndices(allOccurrences, 25);
    
    int count = LinearSearch::countOccurrences(arr, 25);
    std::cout << "Total occurrences of 25: " << count << "\n\n";
    
    // Template search with strings
    std::cout << "3. GENERIC TEMPLATE SEARCH (Strings):\n";
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Eve"};
    std::cout << "Names: [";
    for (int i = 0; i < names.size(); i++) {
        std::cout << names[i];
        if (i < names.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    
    std::string targetName = "Charlie";
    int nameIndex = LinearSearch::searchGeneric(names, targetName);
    std::cout << "Searching for '" << targetName << "': ";
    if (nameIndex != -1) {
        std::cout << "Found at index " << nameIndex << "\n";
    } else {
        std::cout << "Not found\n";
    }
    std::cout << "\n";
    
    // Find min and max
    std::cout << "4. FIND MIN AND MAX ELEMENTS:\n";
    int minIndex = LinearSearch::findMin(arr);
    int maxIndex = LinearSearch::findMax(arr);
    std::cout << "Minimum element: " << arr[minIndex] << " at index " << minIndex << "\n";
    std::cout << "Maximum element: " << arr[maxIndex] << " at index " << maxIndex << "\n\n";
    
    // 2D array search
    std::cout << "5. 2D ARRAY SEARCH:\n";
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    std::cout << "Matrix:\n";
    for (const auto& row : matrix) {
        std::cout << "[";
        for (int i = 0; i < row.size(); i++) {
            std::cout << row[i];
            if (i < row.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }
    
    int target2D = 7;
    auto result2D = LinearSearch::search2D(matrix, target2D);
    std::cout << "Searching for " << target2D << ": ";
    if (result2D.first != -1) {
        std::cout << "Found at position (" << result2D.first << ", " << result2D.second << ")\n";
    } else {
        std::cout << "Not found\n";
    }
    std::cout << "\n";
    
    // Performance analysis
    std::cout << "6. PERFORMANCE ANALYSIS:\n";
    
    // Best case (element at first position)
    std::vector<int> bestCase = {25, 64, 12, 22, 11};
    LinearSearch::performanceAnalysis(bestCase, 25);
    
    // Worst case (element at last position or not found)
    std::vector<int> worstCase = {64, 12, 22, 11, 25};
    LinearSearch::performanceAnalysis(worstCase, 25);
    
    // Large dataset
    std::vector<int> largeArray(10000);
    std::iota(largeArray.begin(), largeArray.end(), 1);
    LinearSearch::performanceAnalysis(largeArray, 9999);
    
    // Real-world application: Finding student by ID
    std::cout << "7. REAL-WORLD APPLICATION - Student Database:\n";
    struct Student {
        int id;
        std::string name;
        double gpa;
        
        bool operator==(const Student& other) const {
            return id == other.id;
        }
    };
    
    std::vector<Student> students = {
        {101, "Alice", 3.8},
        {102, "Bob", 3.2},
        {103, "Charlie", 3.9},
        {104, "David", 3.5},
        {105, "Eve", 3.7}
    };
    
    // Custom comparator to find by ID
    auto findById = [](const Student& student, const Student& target) {
        return student.id == target.id;
    };
    
    Student targetStudent = {103, "", 0.0};  // Looking for student with ID 103
    int studentIndex = LinearSearch::searchWithComparator(students, targetStudent, findById);
    
    if (studentIndex != -1) {
        std::cout << "Student found: ID=" << students[studentIndex].id 
                  << ", Name=" << students[studentIndex].name 
                  << ", GPA=" << students[studentIndex].gpa << "\n";
    } else {
        std::cout << "Student not found\n";
    }
    
    std::cout << "\n=== LINEAR SEARCH SUMMARY ===\n";
    std::cout << "Advantages:\n";
    std::cout << "- Simple to implement and understand\n";
    std::cout << "- Works on unsorted data\n";
    std::cout << "- No additional memory required\n";
    std::cout << "- Can find all occurrences easily\n";
    std::cout << "\nDisadvantages:\n";
    std::cout << "- O(n) time complexity - inefficient for large datasets\n";
    std::cout << "- No early termination optimization possible\n";
    std::cout << "\nBest Use Cases:\n";
    std::cout << "- Small datasets (< 100 elements)\n";
    std::cout << "- Unsorted data\n";
    std::cout << "- When simplicity is more important than performance\n";
    std::cout << "- Finding all occurrences of an element\n";
    
    return 0;
}
