# Elementary Data Structures in C++ - Complete Guide

## Table of Contents
1. [Introduction to Data Structures](#introduction)
2. [Array](#array)
3. [Linked List](#linked-list)
4. [Stack](#stack)
5. [Queue](#queue)
6. [Binary Tree](#binary-tree)
7. [Hash Table](#hash-table)
8. [Heap](#heap)
9. [Graph Basics](#graph-basics)
10. [Time and Space Complexity](#complexity-analysis)
11. [Choosing the Right Data Structure](#choosing-data-structure)

---

## Introduction

**Data Structures** are ways of organizing and storing data in a computer so that it can be accessed and modified efficiently. They provide a means to manage large amounts of data efficiently for uses such as large databases and internet indexing services.

### Why Data Structures Matter:
✅ **Efficient Data Access** - Fast retrieval and modification  
✅ **Memory Optimization** - Better memory usage  
✅ **Algorithm Performance** - Enable efficient algorithms  
✅ **Problem Solving** - Foundation for complex solutions  
✅ **Code Organization** - Structure and organize code better  

---

## 1. Array

### Definition
An **array** is a collection of elements stored at contiguous memory locations. Elements can be accessed using their index.

### Characteristics:
- **Fixed size** (in static arrays)
- **Random access** - O(1) access time
- **Contiguous memory** - Elements stored next to each other
- **Homogeneous** - All elements of same type

### Key Operations:
- **Access**: Direct access to elements using index
- **Insertion**: Add elements at specific positions
- **Deletion**: Remove elements from specific positions
- **Search**: Find elements within the array
- **Traversal**: Visit all elements in sequence

#### Static vs Dynamic Arrays:
- **Static Arrays**: Fixed size determined at compile time
- **Dynamic Arrays**: Can grow and shrink during runtime

### Array Types:
1. **One-dimensional**: Simple list of elements
2. **Multi-dimensional**: Arrays of arrays (matrices)
3. **Jagged Arrays**: Arrays with rows of different lengths

### Time Complexity:
| Operation     | Complexity                          | Notes                                |
|:------------- |:----------------------------------- |:------------------------------------ |
| **Access**    | O(1)                               | Direct index-based access           |
| **Search**    | O(n)                               | Linear search through elements       |
| **Insertion** | O(n) worst case, O(1) at end      | Shifting elements for middle insert  |
| **Deletion**  | O(n) worst case, O(1) at end      | Shifting elements after deletion     |

---

### 🧠 Key Differences: C vs C++ Dynamic Arrays

| Feature          | C (malloc/realloc)        | C++ (std::vector)         |
|:---------------- |:------------------------- |:------------------------- |
| **Manual memory**| Yes                       | No (automatic)            |
| **Syntax**       | Verbose                   | Cleaner and safer         |
| **Flexibility**  | Medium                    | High                      |
| **Safety**       | Low (risk of leaks)       | High (RAII principles)    |


## 2. Linked List

### Definition
A **linked list** is a linear data structure where elements are stored in nodes, and each node contains data and a pointer/reference to the next node.

### Types:
1. **Singly Linked List** - Each node points to the next
2. **Doubly Linked List** - Each node has pointers to both next and previous
3. **Circular Linked List** - Last node points back to the first

### Types:
1. **Singly Linked List** - Each node points to the next node
2. **Doubly Linked List** - Each node has pointers to both next and previous nodes
3. **Circular Linked List** - Last node points back to the first node

### Key Operations:
- **Insertion**: Add nodes at beginning, end, or specific position
- **Deletion**: Remove nodes from beginning, end, or specific position
- **Traversal**: Visit all nodes in sequence
- **Search**: Find a specific value in the list

### Advantages:
- **Dynamic size**: Can grow or shrink during runtime
- **Efficient insertion/deletion**: O(1) at known positions
- **Memory efficient**: Only allocates memory as needed

### Disadvantages:
- **No random access**: Must traverse from head to reach elements
- **Extra memory**: Requires storage for pointers
- **Cache performance**: Poor due to non-contiguous memory layout

### Node Structure Concept:
Each node contains:
- **Data**: The actual value stored
- **Pointer(s)**: Reference to next (and previous in doubly linked) node(s)

### Time Complexity:
| Operation     | Complexity                               | Notes                                     |
|:------------- |:---------------------------------------- |:----------------------------------------- |
| **Access**    | O(n)                                    | Must traverse from head to reach element |
| **Search**    | O(n)                                    | Linear search through nodes               |
| **Insertion** | O(1) at known position, O(n) arbitrary | Direct insertion if node reference known  |
| **Deletion**  | O(1) at known position, O(n) arbitrary | Direct deletion if node reference known   |

---

## 3. Stack

### Definition
A **stack** is a linear data structure that follows the **LIFO** (Last In, First Out) principle. Elements are added and removed from the same end, called the "top."

### Key Operations:
- **Push**: Add element to top
- **Pop**: Remove element from top
- **Top/Peek**: View top element without removing
- **Empty**: Check if stack is empty

### Key Operations:
- **Push**: Add element to top of stack
- **Pop**: Remove and return top element  
- **Top/Peek**: View top element without removing it
- **Empty**: Check if stack is empty
- **Size**: Get number of elements in stack

### Real-world Applications:
- **Function call management**: System call stack
- **Undo operations**: Text editors, applications
- **Expression evaluation**: Mathematical expressions, compilers
- **Backtracking algorithms**: Maze solving, tree traversal
- **Browser history**: Back button functionality

### Stack Principle - LIFO:
Think of a stack of plates - you can only:
- Add a plate to the top (Push)
- Remove the top plate (Pop)
- Look at the top plate (Peek)

### Implementation Approaches:
1. **Array-based**: Fixed size, fast operations
2. **Dynamic array**: Resizable, flexible
3. **Linked list**: Dynamic size, efficient memory usage

### Time Complexity:
- **Push**: O(1)
- **Pop**: O(1)
- **Top**: O(1)
- **Empty**: O(1)

---

## 4. Queue

### Definition
A **queue** is a linear data structure that follows the **FIFO** (First In, First Out) principle. Elements are added at the rear and removed from the front.

### Key Operations:
- **New**: creates an empty queue
- **Enqueue**: Add element to rear
- **Dequeue**: Remove element from front
- **Front**: View front element
- **Rear**: View rear element
- **Empty**: Check if queue is empty

### Key Operations:
- **Enqueue**: Add element to the rear of the queue
- **Dequeue**: Remove element from the front of the queue
- **Front**: View the front element without removing it
- **Rear**: View the rear element without removing it
- **Empty**: Check if queue is empty
- **Size**: Get number of elements in queue

### Queue Principle - FIFO:
Think of a line at a store:
- People join at the back (Enqueue)
- People leave from the front (Dequeue)
- First person in line is first to be served

### Types of Queues:
1. **Simple Queue**: Basic FIFO structure
2. **Circular Queue**: Rear connects back to front when space available
3. **Double-ended Queue (Deque)**: Can add/remove from both ends
4. **Priority Queue**: Elements have priorities, highest priority served first

### Real-world Applications:
- **Operating systems**: Process scheduling, buffer management
- **Network systems**: Packet queues in routers
- **Print queues**: Managing print jobs
- **Breadth-first search**: Graph and tree traversal
- **Customer service**: Call centers, help desk systems

### Implementation Approaches:
1. **Array-based**: Simple but may waste space
2. **Circular array**: Efficient space utilization
3. **Linked list**: Dynamic size, no space waste

### Time Complexity:
- **Enqueue**: O(1)
- **Dequeue**: O(1)
- **Front/Rear**: O(1)
- **Empty**: O(1)

---

## 5. Binary Tree

### Definition
A **binary tree** is a hierarchical data structure where each node has at most two children, referred to as the left child and right child.

### Types:
1. **Full Binary Tree** - Every node has either 0 or 2 children
2. **Complete Binary Tree** - All levels filled except possibly the last
3. **Binary Search Tree (BST)** - Left subtree < root < right subtree

### Key Operations:
- **Insert**: Add a new node to the tree
- **Search**: Find a specific value in the tree
- **Delete**: Remove a node from the tree
- **Traversals**: Visit nodes in specific orders
  - **In-order**: Left → Root → Right (gives sorted order for BST)
  - **Pre-order**: Root → Left → Right
  - **Post-order**: Left → Right → Root
  - **Level-order**: Visit level by level (breadth-first)

### Binary Tree Concepts:
- **Root**: Top node of the tree
- **Leaf**: Node with no children
- **Height**: Longest path from root to leaf
- **Depth**: Distance from root to a specific node
- **Binary Search Tree (BST)**: Left child < Parent < Right child

### Tree Properties:
- **Complete Binary Tree**: All levels filled except possibly the last, filled left to right
- **Full Binary Tree**: Every node has either 0 or 2 children
- **Perfect Binary Tree**: All internal nodes have two children, all leaves at same level
- **Balanced Tree**: Height difference between left and right subtrees ≤ 1

### Advantages:
- **Efficient searching**: O(log n) in balanced trees
- **Sorted data**: In-order traversal gives sorted sequence
- **Hierarchical data**: Natural representation of hierarchical relationships
- **Efficient insertion/deletion**: O(log n) in balanced trees

### Disadvantages:
- **Space overhead**: Extra memory for pointers
- **Balance issues**: Can degenerate to linked list (O(n) operations)
- **No constant time access**: Cannot access by index like arrays

### Applications:
- **Expression evaluation**: Mathematical expressions parsing
- **File systems**: Directory structure representation
- **Decision trees**: Machine learning and AI
- **Database indexing**: B-trees for database indices
## 6. Hash Table

### Definition
A **hash table** is a data structure that maps keys to values using a hash function to compute an index into an array of buckets.

### Key Operations:
- **Insert**: Store key-value pair in the table
- **Search**: Find value associated with a key
- **Delete**: Remove key-value pair from table
- **Hash Function**: Convert key to array index

### Hash Function Properties:
- **Deterministic**: Same key always produces same hash
- **Uniform distribution**: Keys spread evenly across buckets
- **Fast computation**: Hash calculation should be quick
- **Avalanche effect**: Small key changes produce large hash changes

### Collision Resolution Methods:
1. **Chaining**: Use linked lists at each bucket
2. **Open addressing**: Find alternative positions
   - Linear probing: Check next position
   - Quadratic probing: Use quadratic function
   - Double hashing: Use second hash function

### Load Factor:
- **Definition**: Number of elements / Number of buckets
- **Optimal range**: 0.75 or lower for good performance
- **Rehashing**: Resize table when load factor becomes too high

### Advantages:
- **Fast access**: O(1) average case for operations
- **Space efficient**: Direct indexing without extra pointers
- **Flexible keys**: Can use various key types
- **Dynamic size**: Can grow/shrink as needed

### Disadvantages:
- **Hash collisions**: Multiple keys can hash to same index
- **Worst case O(n)**: When many collisions occur
- **No ordering**: Elements not stored in any particular order
- **Space overhead**: May have unused buckets

### Applications:
- **Databases**: Fast record retrieval
- **Caching**: Web browsers, CPU caches
- **Symbol tables**: Compilers and interpreters
- **Sets and maps**: Programming language implementations
- **Cryptography**: Digital signatures and checksums

### Time Complexity (Average/Worst):
- **Search**: O(1) / O(n)
- **Insertion**: O(1) / O(n)
- **Deletion**: O(1) / O(n)

---

## 7. Heap

### Definition
A **heap** is a specialized tree-based data structure that satisfies the heap property. It's a complete binary tree where parent nodes have a specific relationship with their children.

### Key Operations:
- **Insert**: Add new element while maintaining heap property
- **Extract-Min/Max**: Remove root element (minimum in min-heap, maximum in max-heap)
- **Peek**: View root element without removing it
- **Heapify**: Restore heap property after modification
- **Build Heap**: Convert array to heap structure

### Heap Types:
1. **Min Heap**: Parent ≤ Children (root is minimum)
2. **Max Heap**: Parent ≥ Children (root is maximum)
3. **Binary Heap**: Each parent has at most 2 children
4. **d-ary Heap**: Each parent has at most d children

### Heap Properties:
- **Complete Binary Tree**: All levels filled except possibly the last
- **Heap Property**: Parent-child relationship maintained
- **Array Representation**: Efficient storage using array indices
- **Parent-Child Relations**: Parent at i, children at 2i+1 and 2i+2

### Advantages:
- **Fast extrema access**: O(1) to find min/max element
- **Efficient insertion**: O(log n) to maintain heap property
- **Space efficient**: Array-based implementation, no pointers needed
- **Priority operations**: Natural fit for priority queue operations

### Disadvantages:
- **No arbitrary search**: O(n) to find specific element
- **Not sorted**: Elements not in complete sorted order
- **Limited operations**: Mainly supports min/max operations
- **No efficient deletion**: O(log n) to delete arbitrary element

### Applications:
- **Priority queues**: Operating system process scheduling
- **Heap sort algorithm**: Efficient O(n log n) sorting
- **Graph algorithms**: Dijkstra's shortest path, Prim's MST
- **Memory management**: Heap allocation in programming languages
- **Event simulation**: Managing events by timestamp

### Time Complexity:
- **Insertion**: O(log n)
- **Extract Min/Max**: O(log n)
- **Get Min/Max**: O(1)
- **Build Heap**: O(n)

---

## 8. Graph

### Definition
A **graph** is a collection of vertices (nodes) connected by edges. Graphs are used to represent relationships between objects and are fundamental in computer science.

### Key Operations:
- **Add Vertex**: Insert a new node into the graph
- **Add Edge**: Create connection between two vertices
- **Remove Vertex**: Delete node and all its edges
- **Remove Edge**: Delete connection between two vertices
- **Traversal**: Visit vertices in systematic order (DFS, BFS)
- **Path Finding**: Find route between two vertices

### Graph Types:
1. **Directed vs Undirected**: Whether edges have direction
2. **Weighted vs Unweighted**: Whether edges have associated costs
3. **Cyclic vs Acyclic**: Whether the graph contains cycles
4. **Connected vs Disconnected**: Whether all vertices are reachable
5. **Simple vs Multi**: Single edge vs multiple edges between vertices

### Graph Representations:
1. **Adjacency Matrix**: 2D array showing connections
   - Space: O(V²) where V is number of vertices
   - Edge lookup: O(1)
   - Add/Remove edge: O(1)

2. **Adjacency List**: Array of lists for each vertex
   - Space: O(V + E) where E is number of edges  
   - Edge lookup: O(degree)
   - Add edge: O(1), Remove edge: O(degree)

3. **Edge List**: List of all edges in graph
   - Space: O(E)
   - Good for algorithms that process all edges

### Traversal Algorithms:
- **Depth-First Search (DFS)**: Goes deep before wide
- **Breadth-First Search (BFS)**: Explores level by level

### Advantages:
- **Relationship modeling**: Natural representation of connections
- **Flexible structure**: Can model many real-world problems
- **Rich algorithms**: Many well-established algorithms available
- **Network analysis**: Can analyze connectivity patterns

### Disadvantages:
- **Space complexity**: Can require significant memory
- **Algorithm complexity**: Many operations are computationally expensive
- **Implementation complexity**: More complex than linear data structures

### Applications:
- **Social networks**: Friend connections, influence analysis
- **Transportation**: Road networks, flight routes
- **Computer networks**: Internet topology, routing
- **Dependency resolution**: Software packages, task scheduling
- **Game theory**: State transitions, decision trees

---

## Time and Space Complexity

### Understanding Big O Notation

In algorithms and data structures, **Big O notation** is used to describe the time or space complexity of an algorithm — that is, how the performance of an algorithm changes as the size of the input (n) grows.

Big O notation helps us:
✅ **Compare algorithms** - Which is more efficient?  
✅ **Predict performance** - How will it scale with larger inputs?  
✅ **Make informed decisions** - Choose the right approach for your needs  
✅ **Optimize code** - Identify bottlenecks and improvement opportunities  

### Common Big O Complexities

#### 🔹 **O(1) — Constant Time Complexity**
- **Description**: The time taken is constant, no matter how large the input is
- **Performance**: Fastest possible complexity
- **Examples**: 
  - Accessing an array element by index: `arr[5]`
  - Hash table lookup (average case)
  - Stack push/pop operations
  - Getting the size of a data structure

#### 🔹 **O(log n) — Logarithmic Time Complexity**
- **Description**: Time grows slowly even as input grows large
- **Performance**: Very efficient, grows much slower than linear
- **Examples**:
  - Binary search in sorted array
  - Binary tree operations (balanced)
  - Heap insert/delete operations

#### 🔹 **O(n) — Linear Time Complexity**
- **Description**: The time taken grows linearly with the size of the input
- **Performance**: Reasonable for most applications
- **Examples**:
  - Traversing an array or linked list
  - Linear search
  - Finding min/max in unsorted array

#### 🔹 **O(n log n) — Linearithmic Time Complexity**
- **Description**: Time grows as n times log n
- **Performance**: Efficient for sorting and divide-and-conquer algorithms
- **Examples**:
  - Merge sort, quick sort (average case), heap sort
  - Building a heap from unsorted data

#### 🔹 **O(n²) — Quadratic Time Complexity**
- **Description**: Time grows with the square of input size
- **Performance**: Can become slow for large inputs
- **Examples**:
  - Nested loops over the same data
  - Bubble sort, insertion sort, selection sort
  - Comparing all pairs in a dataset

#### 🔹 **O(2^n) — Exponential Time Complexity**
- **Description**: Time doubles with each additional input element
- **Performance**: Very slow, often impractical for large inputs
- **Examples**:
  - Naive recursive Fibonacci
  - Solving traveling salesman with brute force
  - Generating all subsets of a set

### Complexity Comparison Chart

```
Input Size (n)  | O(1) | O(log n) | O(n) | O(n log n) | O(n²) | O(2^n)
----------------|------|----------|------|------------|-------|--------
1               | 1    | 1        | 1    | 1          | 1     | 2
10              | 1    | 3        | 10   | 33         | 100   | 1,024
100             | 1    | 7        | 100  | 664        | 10K   | 10^30
1,000           | 1    | 10       | 1K   | 9,966      | 1M    | Huge!
10,000          | 1    | 13       | 10K  | 132,877    | 100M  | Impossible
```

### Space Complexity

Big O also applies to **space complexity** - how much memory an algorithm uses:

- **O(1) space**: Constant extra memory (only uses loop variables)
- **O(n) space**: Memory grows with input size (creating new arrays, recursive call stack)
- **O(log n) space**: Logarithmic space usage (balanced recursion trees)

### Best, Average, and Worst Case

Many algorithms have different complexities depending on the input:

- **Best case**: Most favorable input scenario
- **Average case**: Expected performance over all possible inputs  
- **Worst case**: Most unfavorable input scenario

**Example - Quick Sort**:
- Best case: O(n log n) - pivot always divides array evenly
- Average case: O(n log n) - pivot is reasonably balanced
- Worst case: O(n²) - pivot is always smallest or largest element

### Summary Table:

| Notation      | Name                | Description                                   | Examples                        |
|:------------- |:------------------- |:--------------------------------------------- |:------------------------------- |
| **O(1)**      | Constant time       | Fastest, time doesn't depend on input size   | Array access, hash lookup       |
| **O(log n)**  | Logarithmic time    | Very efficient, grows slowly                 | Binary search, balanced tree ops|
| **O(n)**      | Linear time         | Time grows proportionally with input size    | Array traversal, linear search  |
| **O(n log n)**| Linearithmic time   | Efficient for complex operations             | Merge sort, heap sort           |
| **O(n²)**     | Quadratic time      | Time grows with square of input size         | Nested loops, bubble sort       |
| **O(2^n)**    | Exponential time    | Very slow, often impractical                 | Naive recursion, brute force    |

### Best, Average, and Worst Case

Many algorithms have different complexities depending on the input:

- **Best case**: Most favorable input scenario
- **Average case**: Expected performance over all possible inputs  
- **Worst case**: Most unfavorable input scenario

**Example - Quick Sort**:
- Best case: O(n log n) - pivot always divides array evenly
- Average case: O(n log n) - pivot is reasonably balanced
- Worst case: O(n²) - pivot is always smallest or largest element

### Big O Notation Summary:

| Data Structure | Access | Search | Insertion | Deletion | Space |
|----------------|--------|--------|-----------|----------|-------|
| **Array**      | O(1)   | O(n)   | O(n)      | O(n)     | O(n)  |
| **Linked List**| O(n)   | O(n)   | O(1)*     | O(1)*    | O(n)  |
| **Stack**      | O(n)   | O(n)   | O(1)      | O(1)     | O(n)  |
| **Queue**      | O(n)   | O(n)   | O(1)      | O(1)     | O(n)  |
| **Binary Tree**| O(n)   | O(n)   | O(n)      | O(n)     | O(n)  |
| **BST (avg)**  | O(log n)| O(log n)| O(log n) | O(log n) | O(n)  |
| **BST (worst)**| O(n)   | O(n)   | O(n)      | O(n)     | O(n)  |
| **Hash Table** | N/A    | O(1)*  | O(1)*     | O(1)*    | O(n)  |
| **Heap**       | N/A    | O(n)   | O(log n)  | O(log n) | O(n)  |

*Average case, may degrade under certain conditions

---

## Choosing the Right Data Structure

### Decision Guide:

#### **Use Array when:**
- ✅ Need random access to elements
- ✅ Memory usage is a concern
- ✅ Simple iteration is primary operation
- ✅ Size is relatively fixed

#### **Use Linked List when:**
- ✅ Frequent insertions/deletions at arbitrary positions
- ✅ Size varies significantly
- ✅ Don't need random access
- ✅ Memory is fragmented

#### **Use Stack when:**
- ✅ Need LIFO behavior
- ✅ Function call management
- ✅ Expression evaluation
- ✅ Undo operations

#### **Use Queue when:**
- ✅ Need FIFO behavior
- ✅ Breadth-first search
- ✅ Task scheduling
- ✅ Buffer for data streams

#### **Use Binary Search Tree when:**
- ✅ Need sorted data with fast search
- ✅ Frequent insertions and deletions
- ✅ Range queries needed
- ✅ In-order traversal gives sorted order

#### **Use Hash Table when:**
- ✅ Need very fast lookups
- ✅ Key-value associations
- ✅ Checking membership
- ✅ Caching/memoization

#### **Use Heap when:**
- ✅ Need to find min/max quickly
- ✅ Priority queue implementation
- ✅ Heap sort algorithm
- ✅ Graph algorithms (Dijkstra's)

---

## Conclusion

Elementary data structures are the building blocks of efficient algorithms and software systems. Understanding their characteristics, trade-offs, and appropriate use cases is crucial for:

✅ **Writing Efficient Code** - Choose the right structure for the job  
✅ **Optimizing Performance** - Understand time/space complexity  
✅ **Solving Complex Problems** - Combine structures for advanced solutions  
✅ **System Design** - Make informed architectural decisions  
✅ **Interview Preparation** - Master fundamental concepts  

### Key Takeaways:

1. **No one-size-fits-all** - Each structure has strengths and weaknesses
2. **Analyze requirements** - Consider access patterns, performance needs
3. **Understand trade-offs** - Memory vs. speed, simplicity vs. flexibility
4. **Practice implementation** - Build from scratch to understand internals
5. **Study real-world usage** - See how they're used in standard libraries

### Next Steps:
- Study advanced data structures (AVL trees, Red-Black trees, B-trees)
- Learn about graph algorithms and advanced tree structures
- Practice implementing these structures from memory
- Solve algorithmic problems using these data structures
- Study how standard libraries implement these structures

---

*Last updated: July 19, 2025*
