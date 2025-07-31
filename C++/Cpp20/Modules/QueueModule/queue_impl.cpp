// C++20 Modules - Queue Module Implementation
// This file contains implementations for non-template functions

module queue_module;

import <iostream>;
import <chrono>;
import <random>;

// ==================== PERFORMANCE COMPARISON IMPLEMENTATION ====================

void compare_queue_performance() {
    std::cout << "\n=== Queue Performance Comparison ===" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    const int num_operations = 10000;
    
    // Performance test data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    
    // Test Circular Array Queue
    {
        std::cout << "\n--- Circular Array Queue Performance ---" << std::endl;
        CircularArrayQueue<int> circularQueue(num_operations);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Enqueue operations
        for (int i = 0; i < num_operations / 2; ++i) {
            circularQueue.enqueue(dis(gen));
        }
        
        // Mixed operations
        for (int i = 0; i < num_operations / 2; ++i) {
            if (i % 3 == 0 && !circularQueue.empty()) {
                circularQueue.dequeue();
            } else {
                circularQueue.enqueue(dis(gen));
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Operations completed: " << num_operations << std::endl;
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Final queue size: " << circularQueue.size() << std::endl;
        std::cout << "Memory efficiency: Fixed size (no dynamic allocation during operations)" << std::endl;
    }
    
    // Test Dynamic Queue
    {
        std::cout << "\n--- Dynamic Queue Performance ---" << std::endl;
        DynamicQueue<int> dynamicQueue;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Enqueue operations
        for (int i = 0; i < num_operations / 2; ++i) {
            dynamicQueue.enqueue(dis(gen));
        }
        
        // Mixed operations
        for (int i = 0; i < num_operations / 2; ++i) {
            if (i % 3 == 0 && !dynamicQueue.empty()) {
                dynamicQueue.dequeue();
            } else {
                dynamicQueue.enqueue(dis(gen));
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Operations completed: " << num_operations << std::endl;
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Final queue size: " << dynamicQueue.size() << std::endl;
        std::cout << "Memory efficiency: Dynamic growth (automatic resizing)" << std::endl;
    }
    
    // Test Linked Queue
    {
        std::cout << "\n--- Linked Queue Performance ---" << std::endl;
        LinkedQueue<int> linkedQueue;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Enqueue operations
        for (int i = 0; i < num_operations / 2; ++i) {
            linkedQueue.enqueue(dis(gen));
        }
        
        // Mixed operations
        for (int i = 0; i < num_operations / 2; ++i) {
            if (i % 3 == 0 && !linkedQueue.empty()) {
                linkedQueue.dequeue();
            } else {
                linkedQueue.enqueue(dis(gen));
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Operations completed: " << num_operations << std::endl;
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Final queue size: " << linkedQueue.size() << std::endl;
        std::cout << "Memory efficiency: No wasted space (exact size allocation)" << std::endl;
    }
    
    // Summary
    std::cout << "\n--- Performance Summary ---" << std::endl;
    std::cout << "✅ Circular Array Queue: Best for fixed-size, high-performance scenarios" << std::endl;
    std::cout << "⚡ Dynamic Queue: Good balance of flexibility and performance" << std::endl;
    std::cout << "🔗 Linked Queue: Best for unknown sizes, no memory waste" << std::endl;
    
    std::cout << "\nTime Complexity:" << std::endl;
    std::cout << "• Enqueue: O(1) for all implementations" << std::endl;
    std::cout << "• Dequeue: O(1) for all implementations" << std::endl;
    std::cout << "• Search:  O(n) for all implementations" << std::endl;
    
    std::cout << "\nSpace Complexity:" << std::endl;
    std::cout << "• Circular Array: O(capacity) - fixed size" << std::endl;
    std::cout << "• Dynamic Queue: O(n) - grows as needed" << std::endl;
    std::cout << "• Linked Queue: O(n) - exact size" << std::endl;
}

/*
IMPLEMENTATION MODULE CONCEPTS:

1. MODULE DECLARATION:
   - 'module queue_module;' indicates this implements the queue_module
   - No 'export' keyword needed - this is implementation only

2. IMPORTING DEPENDENCIES:
   - Must import all dependencies needed by implementation
   - Standard library modules are imported as needed

3. NON-TEMPLATE FUNCTIONS:
   - Only non-template functions can be implemented in .cpp files
   - Template functions must be fully defined in the module interface

4. INTERNAL IMPLEMENTATION:
   - Functions defined here are not visible to importers
   - Provides true implementation hiding
   - Better encapsulation than traditional source files

5. PERFORMANCE BENEFITS:
   - This implementation is compiled once
   - Binary interface shared with all importers
   - No recompilation when used in multiple translation units

This demonstrates how modules provide clean separation between
interface and implementation, leading to faster builds and
better code organization!
*/
