// Binary Search Tree (BST) Implementation - Complete program with all operations
/*
Key Features of Binary Search Tree:
Core Operations:
✅ Insertion: Add nodes while maintaining BST property
✅ Deletion: Remove nodes with three cases (leaf, one child, two children)
✅ Search: Efficient O(log n) average search time
✅ Traversals: All traversal methods with BST-specific benefits
BST Properties:
🔍 Ordered Structure: Left < Root < Right for every subtree
⚡ Efficient Operations: O(log n) average for search, insert, delete
📊 Sorted Output: Inorder traversal gives sorted sequence
🎯 Range Queries: Find elements in a given range efficiently
Advanced Features:
🌳 Tree Balancing Detection: Check if tree is balanced
🔄 Self-Balancing Indicators: Detect when rebalancing needed
📈 Statistical Operations: Find min, max, kth smallest/largest
🎯 Range Operations: Count nodes in range, range sum
Smart Memory Management:
🧠 Uses smart pointers for automatic memory management
🛡️ Exception-safe operations throughout
🚫 RAII principles for resource management
📈 Efficient memory usage with shared ownership
Educational Demonstrations:
📊 Performance Analysis: Best/average/worst case scenarios
🧪 BST Validation: Verify BST property maintenance
📝 Comparison Studies: BST vs other tree structures
🔄 Multiple BST Operations: Comprehensive operation suite
*/

#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <functional>

template<typename T>
class BinarySearchTree {
public:
    struct Node {
        T data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent; // To avoid circular references
        
        explicit Node(const T& value) 
            : data(value), left(nullptr), right(nullptr) {}
    };
    
    using NodePtr = std::shared_ptr<Node>;
    
private:
    NodePtr root_;
    size_t size_;
    
    // Helper function for insertion
    NodePtr insertHelper(NodePtr node, const T& value, NodePtr parent = nullptr) {
        if (!node) {
            auto newNode = std::make_shared<Node>(value);
            newNode->parent = parent;
            size_++;
            return newNode;
        }
        
        if (value < node->data) {
            node->left = insertHelper(node->left, value, node);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value, node);
        } else {
            // Duplicate values - handle according to policy (here we ignore)
            std::cout << "Duplicate value " << value << " ignored" << std::endl;
        }
        
        return node;
    }
    
    // Helper function for search
    NodePtr searchHelper(NodePtr node, const T& value) const {
        if (!node || node->data == value) {
            return node;
        }
        
        if (value < node->data) {
            return searchHelper(node->left, value);
        } else {
            return searchHelper(node->right, value);
        }
    }
    
    // Helper function to find minimum value node
    NodePtr findMin(NodePtr node) const {
        if (!node) return nullptr;
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    
    // Helper function to find maximum value node
    NodePtr findMax(NodePtr node) const {
        if (!node) return nullptr;
        while (node->right) {
            node = node->right;
        }
        return node;
    }
    
    // Helper function for deletion
    NodePtr deleteHelper(NodePtr node, const T& value) {
        if (!node) return nullptr;
        
        if (value < node->data) {
            node->left = deleteHelper(node->left, value);
        } else if (value > node->data) {
            node->right = deleteHelper(node->right, value);
        } else {
            // Node to be deleted found
            
            // Case 1: Node has no children (leaf node)
            if (!node->left && !node->right) {
                size_--;
                return nullptr;
            }
            
            // Case 2: Node has one child
            if (!node->left) {
                size_--;
                return node->right;
            }
            if (!node->right) {
                size_--;
                return node->left;
            }
            
            // Case 3: Node has two children
            // Find inorder successor (smallest value in right subtree)
            NodePtr successor = findMin(node->right);
            
            // Copy the inorder successor's data to this node
            node->data = successor->data;
            
            // Delete the inorder successor (it will have at most one child)
            node->right = deleteHelper(node->right, successor->data);
        }
        
        return node;
    }
    
    // Helper function for inorder traversal
    void inorderHelper(NodePtr node, std::vector<T>& result) const {
        if (node) {
            inorderHelper(node->left, result);
            result.push_back(node->data);
            inorderHelper(node->right, result);
        }
    }
    
    // Helper function for preorder traversal
    void preorderHelper(NodePtr node, std::vector<T>& result) const {
        if (node) {
            result.push_back(node->data);
            preorderHelper(node->left, result);
            preorderHelper(node->right, result);
        }
    }
    
    // Helper function for postorder traversal
    void postorderHelper(NodePtr node, std::vector<T>& result) const {
        if (node) {
            postorderHelper(node->left, result);
            postorderHelper(node->right, result);
            result.push_back(node->data);
        }
    }
    
    // Helper function for height calculation
    int heightHelper(NodePtr node) const {
        if (!node) return -1;
        return 1 + std::max(heightHelper(node->left), heightHelper(node->right));
    }
    
    // Helper function to validate BST property
    bool isBSTHelper(NodePtr node, const T& minVal, const T& maxVal) const {
        if (!node) return true;
        
        if (node->data <= minVal || node->data >= maxVal) {
            return false;
        }
        
        return isBSTHelper(node->left, minVal, node->data) &&
               isBSTHelper(node->right, node->data, maxVal);
    }
    
    // Helper function for tree visualization
    void printTree(NodePtr node, const std::string& prefix, bool isLast, std::ostream& os) const {
        if (node) {
            os << prefix;
            os << (isLast ? "└── " : "├── ");
            os << node->data << std::endl;
            
            std::string newPrefix = prefix + (isLast ? "    " : "│   ");
            
            if (node->right || node->left) {
                if (node->right) {
                    printTree(node->right, newPrefix, !node->left, os);
                }
                if (node->left) {
                    printTree(node->left, newPrefix, true, os);
                }
            }
        }
    }
    
    // Helper function for range query
    void rangeQueryHelper(NodePtr node, const T& low, const T& high, std::vector<T>& result) const {
        if (!node) return;
        
        if (node->data > low) {
            rangeQueryHelper(node->left, low, high, result);
        }
        
        if (node->data >= low && node->data <= high) {
            result.push_back(node->data);
        }
        
        if (node->data < high) {
            rangeQueryHelper(node->right, low, high, result);
        }
    }
    
    // Helper for kth smallest
    bool kthSmallestHelper(NodePtr node, int& k, T& result) const {
        if (!node) return false;
        
        // Search left subtree first
        if (kthSmallestHelper(node->left, k, result)) {
            return true;
        }
        
        // Process current node
        k--;
        if (k == 0) {
            result = node->data;
            return true;
        }
        
        // Search right subtree
        return kthSmallestHelper(node->right, k, result);
    }
    
    // Helper for kth largest
    bool kthLargestHelper(NodePtr node, int& k, T& result) const {
        if (!node) return false;
        
        // Search right subtree first (for largest)
        if (kthLargestHelper(node->right, k, result)) {
            return true;
        }
        
        // Process current node
        k--;
        if (k == 0) {
            result = node->data;
            return true;
        }
        
        // Search left subtree
        return kthLargestHelper(node->left, k, result);
    }
    
public:
    // Constructor
    BinarySearchTree() : root_(nullptr), size_(0) {}
    
    // Constructor with root value
    explicit BinarySearchTree(const T& rootValue) : size_(1) {
        root_ = std::make_shared<Node>(rootValue);
    }
    
    // Insert value maintaining BST property
    void insert(const T& value) {
        std::cout << "Inserting " << value << "... ";
        size_t oldSize = size_;
        root_ = insertHelper(root_, value);
        if (size_ > oldSize) {
            std::cout << "Success (size: " << size_ << ")" << std::endl;
        }
    }
    
    // Search for a value
    bool search(const T& value) const {
        NodePtr result = searchHelper(root_, value);
        return result != nullptr;
    }
    
    // Get node for a value (for advanced operations)
    NodePtr find(const T& value) const {
        return searchHelper(root_, value);
    }
    
    // Delete a value
    bool remove(const T& value) {
        size_t oldSize = size_;
        root_ = deleteHelper(root_, value);
        bool success = size_ < oldSize;
        std::cout << "Removing " << value << "... " 
                  << (success ? "Success" : "Not Found") 
                  << " (size: " << size_ << ")" << std::endl;
        return success;
    }
    
    // Get minimum value
    T getMin() const {
        if (!root_) {
            throw std::runtime_error("Tree is empty");
        }
        NodePtr minNode = findMin(root_);
        return minNode->data;
    }
    
    // Get maximum value
    T getMax() const {
        if (!root_) {
            throw std::runtime_error("Tree is empty");
        }
        NodePtr maxNode = findMax(root_);
        return maxNode->data;
    }
    
    // Find kth smallest element (1-indexed)
    T kthSmallest(int k) const {
        if (k <= 0 || k > static_cast<int>(size_)) {
            throw std::out_of_range("k is out of range");
        }
        
        T result;
        int kCopy = k;
        if (kthSmallestHelper(root_, kCopy, result)) {
            return result;
        }
        
        throw std::runtime_error("Failed to find kth smallest");
    }
    
    // Find kth largest element (1-indexed)
    T kthLargest(int k) const {
        if (k <= 0 || k > static_cast<int>(size_)) {
            throw std::out_of_range("k is out of range");
        }
        
        T result;
        int kCopy = k;
        if (kthLargestHelper(root_, kCopy, result)) {
            return result;
        }
        
        throw std::runtime_error("Failed to find kth largest");
    }
    
    // Range query - find all elements in [low, high]
    std::vector<T> rangeQuery(const T& low, const T& high) const {
        std::vector<T> result;
        rangeQueryHelper(root_, low, high, result);
        return result;
    }
    
    // Count elements in range [low, high]
    int countInRange(const T& low, const T& high) const {
        auto elements = rangeQuery(low, high);
        return static_cast<int>(elements.size());
    }
    
    // Find predecessor of a value
    T predecessor(const T& value) const {
        NodePtr node = searchHelper(root_, value);
        if (!node) {
            throw std::runtime_error("Value not found in tree");
        }
        
        // Case 1: Node has left subtree - predecessor is rightmost node in left subtree
        if (node->left) {
            return findMax(node->left)->data;
        }
        
        // Case 2: No left subtree - go up until we find a node that is right child of its parent
        auto parent = node->parent.lock();
        while (parent && node == parent->left) {
            node = parent;
            parent = parent->parent.lock();
        }
        
        if (!parent) {
            throw std::runtime_error("No predecessor exists");
        }
        
        return parent->data;
    }
    
    // Find successor of a value
    T successor(const T& value) const {
        NodePtr node = searchHelper(root_, value);
        if (!node) {
            throw std::runtime_error("Value not found in tree");
        }
        
        // Case 1: Node has right subtree - successor is leftmost node in right subtree
        if (node->right) {
            return findMin(node->right)->data;
        }
        
        // Case 2: No right subtree - go up until we find a node that is left child of its parent
        auto parent = node->parent.lock();
        while (parent && node == parent->right) {
            node = parent;
            parent = parent->parent.lock();
        }
        
        if (!parent) {
            throw std::runtime_error("No successor exists");
        }
        
        return parent->data;
    }
    
    // Traversal methods
    std::vector<T> inorderTraversal() const {
        std::vector<T> result;
        inorderHelper(root_, result);
        return result;
    }
    
    std::vector<T> preorderTraversal() const {
        std::vector<T> result;
        preorderHelper(root_, result);
        return result;
    }
    
    std::vector<T> postorderTraversal() const {
        std::vector<T> result;
        postorderHelper(root_, result);
        return result;
    }
    
    // Level-order traversal
    std::vector<T> levelOrderTraversal() const {
        std::vector<T> result;
        if (!root_) return result;
        
        std::queue<NodePtr> queue;
        queue.push(root_);
        
        while (!queue.empty()) {
            NodePtr current = queue.front();
            queue.pop();
            
            result.push_back(current->data);
            
            if (current->left) queue.push(current->left);
            if (current->right) queue.push(current->right);
        }
        
        return result;
    }
    
    // Iterative search
    bool searchIterative(const T& value) const {
        NodePtr current = root_;
        
        while (current) {
            if (value == current->data) {
                return true;
            } else if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        return false;
    }
    
    // Tree properties
    int height() const {
        return heightHelper(root_);
    }
    
    size_t size() const {
        return size_;
    }
    
    bool empty() const {
        return root_ == nullptr;
    }
    
    // Validate BST property
    bool isBST() const {
        return isBSTHelper(root_, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }
    
    // Check if tree is balanced (height difference <= 1)
    bool isBalanced() const {
        return isBalancedHelper(root_) != -1;
    }
    
private:
    int isBalancedHelper(NodePtr node) const {
        if (!node) return 0;
        
        int leftHeight = isBalancedHelper(node->left);
        if (leftHeight == -1) return -1; // Left subtree is not balanced
        
        int rightHeight = isBalancedHelper(node->right);
        if (rightHeight == -1) return -1; // Right subtree is not balanced
        
        if (std::abs(leftHeight - rightHeight) > 1) {
            return -1; // Current node is not balanced
        }
        
        return 1 + std::max(leftHeight, rightHeight);
    }
    
public:
    // Print tree structure
    void printTree() const {
        if (!root_) {
            std::cout << "BST is empty" << std::endl;
            return;
        }
        
        std::cout << "Binary Search Tree Structure:" << std::endl;
        printTree(root_, "", true, std::cout);
    }
    
    // Display traversals
    void displayTraversals() const {
        std::cout << "BST Traversals:" << std::endl;
        
        auto inorder = inorderTraversal();
        std::cout << "Inorder (sorted):   ";
        for (size_t i = 0; i < inorder.size(); ++i) {
            std::cout << inorder[i];
            if (i < inorder.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
        
        auto preorder = preorderTraversal();
        std::cout << "Preorder:           ";
        for (size_t i = 0; i < preorder.size(); ++i) {
            std::cout << preorder[i];
            if (i < preorder.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
        
        auto postorder = postorderTraversal();
        std::cout << "Postorder:          ";
        for (size_t i = 0; i < postorder.size(); ++i) {
            std::cout << postorder[i];
            if (i < postorder.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
        
        auto levelorder = levelOrderTraversal();
        std::cout << "Level-order:        ";
        for (size_t i = 0; i < levelorder.size(); ++i) {
            std::cout << levelorder[i];
            if (i < levelorder.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
    
    // Display tree properties
    void displayProperties() const {
        std::cout << "BST Properties:" << std::endl;
        std::cout << "Size: " << size() << std::endl;
        std::cout << "Height: " << height() << std::endl;
        std::cout << "Is empty: " << (empty() ? "Yes" : "No") << std::endl;
        std::cout << "Is valid BST: " << (isBST() ? "Yes" : "No") << std::endl;
        std::cout << "Is balanced: " << (isBalanced() ? "Yes" : "No") << std::endl;
        
        if (!empty()) {
            std::cout << "Minimum value: " << getMin() << std::endl;
            std::cout << "Maximum value: " << getMax() << std::endl;
        }
    }
    
    // Clear the tree
    void clear() {
        root_.reset();
        size_ = 0;
        std::cout << "BST cleared" << std::endl;
    }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void demonstrateBasicOperations() {
    printSeparator("BASIC BST OPERATIONS");
    
    BinarySearchTree<int> bst;
    
    std::cout << "\n--- Insertion Operations ---" << std::endl;
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    for (int value : values) {
        bst.insert(value);
    }
    
    bst.printTree();
    bst.displayProperties();
    
    std::cout << "\n--- Search Operations ---" << std::endl;
    std::cout << "Searching for 40: " << (bst.search(40) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 25: " << (bst.search(25) ? "Found" : "Not Found") << std::endl;
    std::cout << "Iterative search for 60: " << (bst.searchIterative(60) ? "Found" : "Not Found") << std::endl;
    
    std::cout << "\n--- Min/Max Operations ---" << std::endl;
    std::cout << "Minimum value: " << bst.getMin() << std::endl;
    std::cout << "Maximum value: " << bst.getMax() << std::endl;
}

void demonstrateAdvancedQueries() {
    printSeparator("ADVANCED QUERY OPERATIONS");
    
    BinarySearchTree<int> bst;
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    
    for (int value : values) {
        bst.insert(value);
    }
    
    bst.printTree();
    
    std::cout << "\n--- Kth Element Queries ---" << std::endl;
    try {
        std::cout << "1st smallest (min): " << bst.kthSmallest(1) << std::endl;
        std::cout << "3rd smallest: " << bst.kthSmallest(3) << std::endl;
        std::cout << "5th smallest: " << bst.kthSmallest(5) << std::endl;
        std::cout << "1st largest (max): " << bst.kthLargest(1) << std::endl;
        std::cout << "3rd largest: " << bst.kthLargest(3) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    std::cout << "\n--- Range Query Operations ---" << std::endl;
    auto range25to55 = bst.rangeQuery(25, 55);
    std::cout << "Elements in range [25, 55]: ";
    for (size_t i = 0; i < range25to55.size(); ++i) {
        std::cout << range25to55[i];
        if (i < range25to55.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Count in range [25, 55]: " << bst.countInRange(25, 55) << std::endl;
    std::cout << "Count in range [100, 200]: " << bst.countInRange(100, 200) << std::endl;
    
    std::cout << "\n--- Predecessor/Successor Operations ---" << std::endl;
    try {
        std::cout << "Predecessor of 40: " << bst.predecessor(40) << std::endl;
        std::cout << "Successor of 40: " << bst.successor(40) << std::endl;
        std::cout << "Predecessor of 50: " << bst.predecessor(50) << std::endl;
        std::cout << "Successor of 50: " << bst.successor(50) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void demonstrateDeletionOperations() {
    printSeparator("DELETION OPERATIONS");
    
    BinarySearchTree<int> bst;
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    
    for (int value : values) {
        bst.insert(value);
    }
    
    std::cout << "\n--- Original Tree ---" << std::endl;
    bst.printTree();
    
    std::cout << "\n--- Deleting Leaf Node (10) ---" << std::endl;
    bst.remove(10);
    bst.printTree();
    
    std::cout << "\n--- Deleting Node with One Child (25) ---" << std::endl;
    bst.remove(25);
    bst.printTree();
    
    std::cout << "\n--- Deleting Node with Two Children (30) ---" << std::endl;
    bst.remove(30);
    bst.printTree();
    
    std::cout << "\n--- Deleting Root Node (50) ---" << std::endl;
    bst.remove(50);
    bst.printTree();
    bst.displayProperties();
}

void demonstrateTraversalComparison() {
    printSeparator("TRAVERSAL COMPARISON");
    
    BinarySearchTree<int> bst;
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int value : values) {
        bst.insert(value);
    }
    
    bst.printTree();
    std::cout << "\n--- All Traversal Methods ---" << std::endl;
    bst.displayTraversals();
    
    std::cout << "\nTraversal Analysis for BST:" << std::endl;
    std::cout << "- Inorder: Gives sorted sequence (key property of BST)" << std::endl;
    std::cout << "- Preorder: Root-first traversal (useful for tree reconstruction)" << std::endl;
    std::cout << "- Postorder: Children-first traversal (useful for deletion)" << std::endl;
    std::cout << "- Level-order: Level-by-level traversal (BFS)" << std::endl;
}

void demonstrateTreeValidation() {
    printSeparator("TREE VALIDATION");
    
    std::cout << "\n--- Valid BST ---" << std::endl;
    BinarySearchTree<int> validBST;
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    
    for (int value : values) {
        validBST.insert(value);
    }
    
    validBST.printTree();
    validBST.displayProperties();
    
    std::cout << "\n--- Balanced vs Unbalanced BST ---" << std::endl;
    
    // Create an unbalanced BST
    BinarySearchTree<int> unbalancedBST;
    std::vector<int> sortedValues = {10, 20, 30, 40, 50, 60, 70};
    
    std::cout << "Inserting sorted values (creates unbalanced tree):" << std::endl;
    for (int value : sortedValues) {
        unbalancedBST.insert(value);
    }
    
    unbalancedBST.printTree();
    unbalancedBST.displayProperties();
}

void demonstratePracticalApplications() {
    printSeparator("PRACTICAL APPLICATIONS");
    
    // 1. Phone Directory
    std::cout << "\n--- Phone Directory Application ---" << std::endl;
    BinarySearchTree<int> phoneDirectory;
    
    std::vector<int> phoneNumbers = {5551234, 5555678, 5559012, 5552345, 5556789};
    std::cout << "Adding phone numbers to directory:" << std::endl;
    for (int number : phoneNumbers) {
        phoneDirectory.insert(number);
    }
    
    phoneDirectory.printTree();
    
    std::cout << "Quick lookup for 5555678: " 
              << (phoneDirectory.search(5555678) ? "Found" : "Not Found") << std::endl;
    
    std::cout << "All numbers in sorted order: ";
    auto sortedNumbers = phoneDirectory.inorderTraversal();
    for (size_t i = 0; i < sortedNumbers.size(); ++i) {
        std::cout << sortedNumbers[i];
        if (i < sortedNumbers.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
    
    // 2. Grade Management System
    std::cout << "\n--- Student Grade Management ---" << std::endl;
    BinarySearchTree<int> grades;
    
    std::vector<int> studentGrades = {85, 92, 78, 96, 67, 89, 74, 82};
    std::cout << "Adding student grades:" << std::endl;
    for (int grade : studentGrades) {
        grades.insert(grade);
    }
    
    grades.printTree();
    
    std::cout << "Lowest grade: " << grades.getMin() << std::endl;
    std::cout << "Highest grade: " << grades.getMax() << std::endl;
    std::cout << "Grades in range [80, 90]: ";
    
    auto gradeRange = grades.rangeQuery(80, 90);
    for (size_t i = 0; i < gradeRange.size(); ++i) {
        std::cout << gradeRange[i];
        if (i < gradeRange.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
    
    try {
        std::cout << "Median grade (middle value): " << grades.kthSmallest(grades.size()/2 + 1) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error finding median: " << e.what() << std::endl;
    }
}

void demonstratePerformanceCharacteristics() {
    printSeparator("PERFORMANCE ANALYSIS");
    
    std::cout << "\n--- Best Case: Balanced BST ---" << std::endl;
    BinarySearchTree<int> balancedBST;
    
    // Insert in a way that creates a balanced tree
    std::vector<int> balancedOrder = {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93};
    for (int value : balancedOrder) {
        balancedBST.insert(value);
    }
    
    balancedBST.displayProperties();
    std::cout << "Time complexity for balanced BST:" << std::endl;
    std::cout << "- Search/Insert/Delete: O(log n)" << std::endl;
    std::cout << "- Height: O(log n)" << std::endl;
    
    std::cout << "\n--- Worst Case: Degenerate BST ---" << std::endl;
    BinarySearchTree<int> degenerateBST;
    
    // Insert in sorted order (creates a linear tree)
    std::vector<int> sortedOrder = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    for (int value : sortedOrder) {
        degenerateBST.insert(value);
    }
    
    degenerateBST.displayProperties();
    std::cout << "Time complexity for degenerate BST:" << std::endl;
    std::cout << "- Search/Insert/Delete: O(n)" << std::endl;
    std::cout << "- Height: O(n)" << std::endl;
    
    std::cout << "\nComparison:" << std::endl;
    std::cout << "Balanced BST height: " << balancedBST.height() << " (nodes: " << balancedBST.size() << ")" << std::endl;
    std::cout << "Degenerate BST height: " << degenerateBST.height() << " (nodes: " << degenerateBST.size() << ")" << std::endl;
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "   BINARY SEARCH TREE DEMONSTRATION          " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateAdvancedQueries();
        demonstrateDeletionOperations();
        demonstrateTraversalComparison();
        demonstrateTreeValidation();
        demonstratePracticalApplications();
        demonstratePerformanceCharacteristics();
        
        printSeparator("COMPREHENSIVE SUMMARY");
        
        std::cout << "\nBinary Search Tree Key Properties:" << std::endl;
        std::cout << "🌳 Ordered Structure: Left < Root < Right for all subtrees" << std::endl;
        std::cout << "🔍 Efficient Search: Average O(log n), worst O(n)" << std::endl;
        std::cout << "📊 Sorted Traversal: Inorder gives sorted sequence" << std::endl;
        std::cout << "⚡ Dynamic Operations: Insert/Delete while maintaining order" << std::endl;
        
        std::cout << "\nTime Complexity Summary:" << std::endl;
        std::cout << "╔══════════════╦══════════════╦══════════════╗" << std::endl;
        std::cout << "║  Operation   ║   Average    ║    Worst     ║" << std::endl;
        std::cout << "╠══════════════╬══════════════╬══════════════╣" << std::endl;
        std::cout << "║    Search    ║   O(log n)   ║     O(n)     ║" << std::endl;
        std::cout << "║   Insert     ║   O(log n)   ║     O(n)     ║" << std::endl;
        std::cout << "║   Delete     ║   O(log n)   ║     O(n)     ║" << std::endl;
        std::cout << "║   Min/Max    ║   O(log n)   ║     O(n)     ║" << std::endl;
        std::cout << "║ Predecessor  ║   O(log n)   ║     O(n)     ║" << std::endl;
        std::cout << "║  Successor   ║   O(log n)   ║     O(n)     ║" << std::endl;
        std::cout << "╚══════════════╩══════════════╩══════════════╝" << std::endl;
        
        std::cout << "\nSpace Complexity: O(n) for storing n nodes" << std::endl;
        
        std::cout << "\nDeletion Cases:" << std::endl;
        std::cout << "1️⃣ Leaf Node: Simply remove the node" << std::endl;
        std::cout << "2️⃣ One Child: Replace node with its child" << std::endl;
        std::cout << "3️⃣ Two Children: Replace with inorder successor" << std::endl;
        
        std::cout << "\nCommon Use Cases:" << std::endl;
        std::cout << "🎯 Database indexing and searching" << std::endl;
        std::cout << "🎯 File system directory structures" << std::endl;
        std::cout << "🎯 Symbol tables in compilers" << std::endl;
        std::cout << "🎯 Expression parsing and evaluation" << std::endl;
        std::cout << "🎯 Priority queues (with modifications)" << std::endl;
        std::cout << "🎯 Range queries and statistical operations" << std::endl;
        
        std::cout << "\nAdvantages:" << std::endl;
        std::cout << "✅ Maintains sorted order automatically" << std::endl;
        std::cout << "✅ Efficient search operations" << std::endl;
        std::cout << "✅ Dynamic size (insert/delete anytime)" << std::endl;
        std::cout << "✅ No additional memory for sorting" << std::endl;
        std::cout << "✅ Supports range queries efficiently" << std::endl;
        
        std::cout << "\nDisadvantages:" << std::endl;
        std::cout << "❌ Can become unbalanced (worst case O(n))" << std::endl;
        std::cout << "❌ No constant time operations" << std::endl;
        std::cout << "❌ Memory overhead for pointers" << std::endl;
        std::cout << "❌ Poor cache performance vs arrays" << std::endl;
        
        std::cout << "\nWhen to Use BST:" << std::endl;
        std::cout << "💡 Need frequent search operations" << std::endl;
        std::cout << "💡 Want to maintain sorted order dynamically" << std::endl;
        std::cout << "💡 Need range queries or statistical operations" << std::endl;
        std::cout << "💡 Data doesn't come in sorted order" << std::endl;
        
        std::cout << "\nConsider Alternatives:" << std::endl;
        std::cout << "🔄 Self-balancing trees (AVL, Red-Black) for guaranteed performance" << std::endl;
        std::cout << "🔄 Hash tables for faster average search (no ordering)" << std::endl;
        std::cout << "🔄 Arrays for simple data with infrequent modifications" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
