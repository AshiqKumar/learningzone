# Non-Linear Data Structures

This directory contains comprehensive C++ implementations of essential non-linear data structures. Each implementation is a complete, standalone program with educational demonstrations and real-world applications.

## 📁 Structure Overview

```
NonLinearDataStructures/
├── binarytree.cpp          # Complete Binary Tree implementation
├── binarysearchtree.cpp    # Binary Search Tree with all operations
├── hashtable.cpp           # Hash Table with collision resolution
├── graph.cpp               # Graph with multiple algorithms
├── heap.cpp                # Min/Max Heap and Priority Queue
├── trie.cpp                # Trie (Prefix Tree) implementation
└── README.md               # This file
```

## 🌳 Data Structures Included

### 1. Binary Tree (`binarytree.cpp`)
- **Features**: General binary tree structure
- **Operations**: Insert, search, delete, traversals (DFS/BFS)
- **Advanced**: Tree validation, mirroring, LCA, diameter
- **Applications**: Expression trees, decision trees, file systems
- **Complexity**: Search O(n), Insert/Delete O(n)

### 2. Binary Search Tree (`binarysearchtree.cpp`)
- **Features**: Ordered binary tree with BST property
- **Operations**: Insert, search, delete, min/max, predecessor/successor
- **Advanced**: Range queries, kth element, validation
- **Applications**: Symbol tables, database indexing, sorted sequences
- **Complexity**: Average O(log n), Worst O(n)

### 3. Hash Table (`hashtable.cpp`)
- **Features**: Two implementations - Chaining & Open Addressing
- **Operations**: Insert, search, delete with O(1) average time
- **Advanced**: Dynamic resizing, collision statistics, load factor management
- **Applications**: Caches, dictionaries, databases, frequency counting
- **Complexity**: Average O(1), Worst O(n)

### 4. Graph (`graph.cpp`)
- **Features**: Adjacency list representation, directed/undirected
- **Operations**: Add/remove vertices/edges, DFS/BFS traversals
- **Advanced**: Shortest paths (Dijkstra), cycle detection, topological sort
- **Applications**: Social networks, routing, dependency resolution
- **Complexity**: Various depending on algorithm (O(V+E) to O(V³))

### 5. Heap (`heap.cpp`)
- **Features**: Min-heap and Max-heap with array representation
- **Operations**: Insert, extract, peek, build heap, heap sort
- **Advanced**: Priority queue, custom comparators, heap validation
- **Applications**: Priority queues, scheduling, graph algorithms
- **Complexity**: Insert/Extract O(log n), Build O(n)

### 6. Trie (`trie.cpp`)
- **Features**: Prefix tree for string storage and retrieval
- **Operations**: Insert, search, delete, prefix search, autocomplete
- **Advanced**: Pattern matching, word frequency, longest common prefix
- **Applications**: Autocomplete, spell checkers, IP routing, DNA analysis
- **Complexity**: Operations O(m) where m is string length

## 🚀 Getting Started

### Compilation
Each file is a complete standalone program. To compile and run:

```bash
# For any specific data structure (example with binary tree)
g++ -std=c++17 -O2 binarytree.cpp -o binarytree
./binarytree

# Or with more detailed output
g++ -std=c++17 -Wall -Wextra -O2 binarytree.cpp -o binarytree
./binarytree
```

### System Requirements
- **C++ Standard**: C++17 or later
- **Compiler**: GCC 7+, Clang 5+, MSVC 2017+
- **Features Used**: Smart pointers, STL containers, modern C++ features

## 📊 Performance Comparison

| Data Structure | Insert | Search | Delete | Space | Best Use Case |
|----------------|--------|--------|--------|-------|---------------|
| Binary Tree | O(n) | O(n) | O(n) | O(n) | Hierarchical data |
| BST | O(log n)* | O(log n)* | O(log n)* | O(n) | Ordered operations |
| Hash Table | O(1)* | O(1)* | O(1)* | O(n) | Key-value lookups |
| Graph | O(1) | O(V+E) | O(V+E) | O(V+E) | Relationships |
| Heap | O(log n) | O(n) | O(log n) | O(n) | Priority operations |
| Trie | O(m) | O(m) | O(m) | O(alphabet×n×m) | String prefixes |

*Average case. Worst case may be different.

## 🎯 Key Features

### Educational Value
- **Comprehensive Examples**: Each implementation includes multiple demonstration functions
- **Visual Output**: Tree structures displayed in ASCII art
- **Step-by-step Explanations**: Operations explained with output
- **Performance Analysis**: Time/space complexity discussions

### Modern C++ Practices
- **Smart Pointers**: Automatic memory management with `std::shared_ptr`
- **RAII**: Resource Acquisition Is Initialization principles
- **STL Integration**: Uses standard library containers and algorithms
- **Exception Safety**: Proper error handling throughout
- **Template Programming**: Generic implementations where applicable

### Real-World Applications
- **Practical Examples**: Each structure includes real-world use cases
- **Complete Implementations**: Production-ready code patterns
- **Performance Monitoring**: Statistics and analysis tools
- **Extensible Design**: Easy to modify and extend

## 🧪 What Each Program Demonstrates

### Binary Tree
- Level-order and manual tree construction
- All traversal methods (recursive and iterative)
- Tree properties (complete, full, perfect)
- Advanced operations (LCA, diameter, path finding)

### Binary Search Tree
- BST property maintenance during operations
- Deletion with three cases (leaf, one child, two children)
- Range queries and statistical operations
- Performance comparison with different insertion orders

### Hash Table
- Two collision resolution strategies comparison
- Dynamic resizing and load factor management
- Hash function quality analysis
- Practical applications (phone book, caching)

### Graph
- Different graph representations and algorithms
- Traversal algorithms (DFS, BFS) with applications
- Shortest path algorithms (Dijkstra)
- Cycle detection and topological sorting

### Heap
- Min-heap and max-heap implementations
- Heap sort algorithm demonstration
- Priority queue applications
- Custom comparators and advanced operations

### Trie
- Prefix-based operations and autocomplete
- Pattern matching with wildcards
- Word frequency tracking
- Practical applications (spell checker, routing)

## 🎓 Learning Objectives

After studying these implementations, you will understand:

1. **Data Structure Selection**: When to use each structure
2. **Algorithm Complexity**: Time/space trade-offs
3. **Implementation Techniques**: Modern C++ best practices
4. **Real-World Applications**: Practical use cases
5. **Performance Analysis**: Benchmarking and optimization
6. **Problem Solving**: How structures solve specific problems

## 🔧 Customization

Each implementation is designed to be:
- **Modifiable**: Easy to add new features
- **Extensible**: Template-based where appropriate
- **Educational**: Well-commented and explained
- **Practical**: Ready for real-world adaptation

## 📈 Advanced Topics Covered

- **Memory Management**: Smart pointers and RAII
- **Generic Programming**: Templates and type safety
- **Algorithm Visualization**: ASCII tree displays
- **Performance Profiling**: Statistics and analysis
- **Error Handling**: Exception safety
- **Design Patterns**: Iterator, Factory patterns

## 🎯 Next Steps

1. **Run Each Program**: Compile and execute to see demonstrations
2. **Modify Examples**: Change input data to see different behaviors
3. **Implement Variations**: Add your own features and improvements
4. **Benchmark Performance**: Test with different data sizes
5. **Combine Structures**: Use multiple structures in larger projects

## 📚 Additional Resources

For deeper understanding, consider studying:
- Algorithm design and analysis
- Advanced data structures (Red-Black trees, B-trees)
- Graph theory and network algorithms
- Computational complexity theory
- System design and architecture

---

**Note**: These implementations prioritize educational clarity while maintaining production-quality code standards. They serve as excellent foundations for understanding fundamental computer science concepts and building more complex systems.
