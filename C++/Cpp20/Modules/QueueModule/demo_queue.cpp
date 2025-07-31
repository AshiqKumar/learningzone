// C++20 Modules - Queue Module Demonstration
// This program demonstrates the usage of the queue module

import queue_module;    // Import our custom queue module
import <iostream>;      // Import standard library
import <string>;
import <vector>;

int main() {
    std::cout << "=== C++20 Queue Module Demonstration ===" << std::endl;
    std::cout << "Showcasing modular design with data structures" << std::endl << std::endl;
    
    // ==================== CIRCULAR ARRAY QUEUE DEMO ====================
    std::cout << "1. CIRCULAR ARRAY QUEUE" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    CircularArrayQueue<int> circularQueue(5);  // Fixed capacity of 5
    
    std::cout << "Created circular queue with capacity 5" << std::endl;
    std::cout << "Initial state - Empty: " << (circularQueue.empty() ? "Yes" : "No") << std::endl;
    std::cout << "Size: " << circularQueue.size() << " / " << circularQueue.capacity() << std::endl << std::endl;
    
    // Fill the queue
    std::cout << "--- Filling the queue ---" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        circularQueue.enqueue(i * 10);
    }
    circularQueue.display();
    
    std::cout << "Queue full: " << (circularQueue.is_full() ? "Yes" : "No") << std::endl;
    std::cout << "Attempting to add to full queue:" << std::endl;
    circularQueue.enqueue(60);  // Should fail
    
    std::cout << "\n--- Dequeue and enqueue operations ---" << std::endl;
    circularQueue.dequeue();
    circularQueue.dequeue();
    circularQueue.display();
    
    circularQueue.enqueue(60);
    circularQueue.enqueue(70);
    circularQueue.display();
    
    // ==================== DYNAMIC QUEUE DEMO ====================
    std::cout << "\n\n2. DYNAMIC QUEUE" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    DynamicQueue<std::string> dynamicQueue;
    
    std::cout << "Created dynamic queue (grows automatically)" << std::endl;
    std::cout << "Initial size: " << dynamicQueue.size() << std::endl << std::endl;
    
    // Add string elements
    std::cout << "--- Adding string elements ---" << std::endl;
    std::vector<std::string> tasks = {"Task1", "Task2", "Task3", "Task4", "Task5"};
    for (const auto& task : tasks) {
        dynamicQueue.enqueue(task);
    }
    dynamicQueue.display();
    
    std::cout << "\nProcessing tasks:" << std::endl;
    while (!dynamicQueue.empty()) {
        std::cout << "Processing: " << dynamicQueue.front() << std::endl;
        dynamicQueue.dequeue();
        if (!dynamicQueue.empty()) {
            dynamicQueue.display();
        }
    }
    
    // ==================== LINKED QUEUE DEMO ====================
    std::cout << "\n\n3. LINKED QUEUE" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    LinkedQueue<char> linkedQueue;
    
    std::cout << "Created linked queue (no size limit)" << std::endl;
    std::cout << "Initial empty: " << (linkedQueue.empty() ? "Yes" : "No") << std::endl << std::endl;
    
    // Add character elements
    std::cout << "--- Adding character elements ---" << std::endl;
    std::string alphabet = "ABCDEFGHIJ";
    for (char c : alphabet) {
        linkedQueue.enqueue(c);
    }
    linkedQueue.display();
    
    std::cout << "\nSearching in queue:" << std::endl;
    char searchChar = 'E';
    int position = linkedQueue.search(searchChar);
    if (position != -1) {
        std::cout << "Found '" << searchChar << "' at position " << position << " from front" << std::endl;
    }
    
    searchChar = 'Z';
    position = linkedQueue.search(searchChar);
    std::cout << "Search for '" << searchChar << "': " << (position != -1 ? "Found" : "Not found") << std::endl;
    
    // ==================== TEMPLATE DEMONSTRATION ====================
    std::cout << "\n\n4. TEMPLATE DEMONSTRATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Show that templates work with different types
    CircularArrayQueue<double> doubleQueue(3);
    demonstrate_queue(doubleQueue, "Circular Queue<double>");
    
    DynamicQueue<int> intQueue;
    demonstrate_queue(intQueue, "Dynamic Queue<int>");
    
    // ==================== TYPE ALIASES DEMONSTRATION ====================
    std::cout << "\n\n5. TYPE ALIASES" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Using the exported type aliases
    CircularQueue<int> aliasCircular(4);    // Using alias
    DynamicArrayQueue<char> aliasDynamic;   // Using alias
    ListQueue<std::string> aliasList;       // Using alias
    
    std::cout << "Type aliases make code more readable:" << std::endl;
    std::cout << "• CircularQueue<int> instead of CircularArrayQueue<int>" << std::endl;
    std::cout << "• DynamicArrayQueue<char> instead of DynamicQueue<char>" << std::endl;
    std::cout << "• ListQueue<string> instead of LinkedQueue<string>" << std::endl << std::endl;
    
    aliasCircular.enqueue(100);
    aliasDynamic.enqueue('X');
    aliasList.enqueue("Hello");
    
    std::cout << "All aliases work identically to the original classes!" << std::endl;
    
    // ==================== PERFORMANCE COMPARISON ====================
    std::cout << "\n\n6. PERFORMANCE ANALYSIS" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Call the performance comparison function from the module
    compare_queue_performance();
    
    // ==================== MODULE BENEFITS DEMONSTRATION ====================
    std::cout << "\n\n7. MODULE BENEFITS" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "🚀 C++20 Modules Benefits Demonstrated:" << std::endl << std::endl;
    
    std::cout << "✅ FAST COMPILATION:" << std::endl;
    std::cout << "   • No preprocessor overhead from #include" << std::endl;
    std::cout << "   • Binary module interfaces reused across files" << std::endl;
    std::cout << "   • Template instantiation optimized" << std::endl << std::endl;
    
    std::cout << "🔒 STRONG ENCAPSULATION:" << std::endl;
    std::cout << "   • Private functions truly private to module" << std::endl;
    std::cout << "   • Only exported items visible to importers" << std::endl;
    std::cout << "   • Implementation details completely hidden" << std::endl << std::endl;
    
    std::cout << "📦 CLEAN INTERFACES:" << std::endl;
    std::cout << "   • Explicit exports define public API" << std::endl;
    std::cout << "   • No accidental dependencies on internals" << std::endl;
    std::cout << "   • Clear module boundaries" << std::endl << std::endl;
    
    std::cout << "⚡ TEMPLATE SUPPORT:" << std::endl;
    std::cout << "   • Templates work seamlessly with modules" << std::endl;
    std::cout << "   • Type aliases exported correctly" << std::endl;
    std::cout << "   • Template specializations supported" << std::endl << std::endl;
    
    std::cout << "🛠️ BETTER TOOLING:" << std::endl;
    std::cout << "   • IDEs understand module boundaries" << std::endl;
    std::cout << "   • Cleaner dependency graphs" << std::endl;
    std::cout << "   • Improved debugging experience" << std::endl << std::endl;
    
    // ==================== COMPILATION NOTES ====================
    std::cout << "8. COMPILATION INFORMATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "To compile this queue module example:" << std::endl << std::endl;
    
    std::cout << "GCC (11+):" << std::endl;
    std::cout << "  g++ -std=c++20 -fmodules-ts -c queue_interface.cppm" << std::endl;
    std::cout << "  g++ -std=c++20 -fmodules-ts -c queue_impl.cpp" << std::endl;
    std::cout << "  g++ -std=c++20 -fmodules-ts demo_queue.cpp *.o -o queue_demo" << std::endl << std::endl;
    
    std::cout << "Clang (14+):" << std::endl;
    std::cout << "  clang++ -std=c++20 -fmodules --precompile queue_interface.cppm -o queue.pcm" << std::endl;
    std::cout << "  clang++ -std=c++20 -fmodules queue_impl.cpp demo_queue.cpp -fprebuilt-module-path=. -o queue_demo" << std::endl << std::endl;
    
    std::cout << "MSVC (2019+):" << std::endl;
    std::cout << "  cl /std:c++20 /experimental:module /c queue_interface.cppm" << std::endl;
    std::cout << "  cl /std:c++20 /experimental:module /c queue_impl.cpp" << std::endl;
    std::cout << "  cl /std:c++20 /experimental:module demo_queue.cpp *.obj" << std::endl << std::endl;
    
    // ==================== CONCLUSION ====================
    std::cout << "🎉 CONCLUSION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "This demonstration shows how C++20 modules provide:" << std::endl;
    std::cout << "• Better performance through binary interfaces" << std::endl;
    std::cout << "• Stronger encapsulation than traditional headers" << std::endl;
    std::cout << "• Cleaner code organization" << std::endl;
    std::cout << "• Seamless template support" << std::endl;
    std::cout << "• Future-ready C++ development" << std::endl << std::endl;
    
    std::cout << "🌟 Welcome to the future of C++ with modules!" << std::endl;
    
    return 0;
}

/*
DEMONSTRATION KEY POINTS:

1. MODULE IMPORTING:
   - import queue_module;    // Clean, simple import
   - import <iostream>;      // Standard library modules
   - No #include overhead or header guards needed

2. SEAMLESS USAGE:
   - Module classes work exactly like traditional classes
   - Templates instantiate normally
   - Type aliases work across module boundaries

3. ENCAPSULATION:
   - Cannot access internal module functions
   - Strong boundaries between interface and implementation
   - Better than traditional header-based encapsulation

4. PERFORMANCE:
   - Faster compilation due to binary interfaces
   - No repeated template instantiation
   - Efficient incremental builds

5. MAINTAINABILITY:
   - Clear module boundaries
   - Explicit interface definition
   - Better dependency management

This real-world example shows modules are ready for production use
and provide significant benefits over traditional headers!
*/
