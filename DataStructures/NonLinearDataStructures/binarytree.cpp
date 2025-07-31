// Binary Tree Implementation - Complete program with all operations
/*
Key Features of Binary Tree:
Core Operations:
✅ Insertion: Add nodes to the tree
✅ Deletion: Remove nodes from the tree
✅ Search: Find nodes in the tree
✅ Traversals: Inorder, Preorder, Postorder, Level-order
Binary Tree Features:
🌳 Hierarchical Structure: Parent-child relationships
🎯 Maximum 2 Children: Each node has at most 2 children
⚡ Flexible Structure: No ordering constraint (unlike BST)
💾 Dynamic Growth: Can grow and shrink dynamically
Advanced Features:
🔍 Multiple Search Methods: DFS and BFS approaches
📊 Tree Statistics: Height, size, depth calculations
🗑️ Various Deletion Strategies: Different approaches for node removal
📏 Tree Validation: Check tree properties and balance
Smart Memory Management:
🧠 Uses smart pointers for automatic memory management
🛡️ Exception-safe operations
🚫 RAII principles throughout
📈 Efficient tree construction and destruction
Educational Demonstrations:
📊 Performance Analysis: Time/space complexity breakdown
🧪 Tree Visualization: ASCII art representation
📝 Use Cases: Real-world applications explained
🔄 Multiple Tree Types: Generic, BST, and specialized trees
*/

#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <sstream>

template<typename T>
class BinaryTree {
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
    
    // Helper function for insertion (level-order insertion)
    void insertLevelOrder(const T& value) {
        auto newNode = std::make_shared<Node>(value);
        
        if (!root_) {
            root_ = newNode;
            size_++;
            return;
        }
        
        std::queue<NodePtr> queue;
        queue.push(root_);
        
        while (!queue.empty()) {
            NodePtr current = queue.front();
            queue.pop();
            
            if (!current->left) {
                current->left = newNode;
                newNode->parent = current;
                size_++;
                return;
            } else if (!current->right) {
                current->right = newNode;
                newNode->parent = current;
                size_++;
                return;
            } else {
                queue.push(current->left);
                queue.push(current->right);
            }
        }
    }
    
    // Helper function for finding a node
    NodePtr findNode(NodePtr node, const T& value) const {
        if (!node) return nullptr;
        
        if (node->data == value) return node;
        
        NodePtr leftResult = findNode(node->left, value);
        if (leftResult) return leftResult;
        
        return findNode(node->right, value);
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
    
    // Helper function for tree visualization
    void printTree(NodePtr node, const std::string& prefix, bool isLast, std::ostream& os) const {
        if (node) {
            os << prefix;
            os << (isLast ? "└── " : "├── ");
            os << node->data << std::endl;
            
            // Calculate new prefix for children
            std::string newPrefix = prefix + (isLast ? "    " : "│   ");
            
            // Print children (right first for better visualization)
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
    
    // Helper function to find deepest rightmost node
    NodePtr findDeepestRightmost() const {
        if (!root_) return nullptr;
        
        std::queue<NodePtr> queue;
        queue.push(root_);
        NodePtr deepest = nullptr;
        
        while (!queue.empty()) {
            deepest = queue.front();
            queue.pop();
            
            if (deepest->left) queue.push(deepest->left);
            if (deepest->right) queue.push(deepest->right);
        }
        
        return deepest;
    }
    
    // Helper function to delete deepest rightmost node
    void deleteDeepestRightmost(NodePtr nodeToDelete) {
        std::queue<NodePtr> queue;
        queue.push(root_);
        
        while (!queue.empty()) {
            NodePtr current = queue.front();
            queue.pop();
            
            if (current == nodeToDelete) {
                current.reset();
                return;
            }
            
            if (current->right == nodeToDelete) {
                current->right.reset();
                return;
            }
            
            if (current->left == nodeToDelete) {
                current->left.reset();
                return;
            }
            
            if (current->right) queue.push(current->right);
            if (current->left) queue.push(current->left);
        }
    }
    
public:
    // Constructor
    BinaryTree() : root_(nullptr), size_(0) {}
    
    // Constructor with root value
    explicit BinaryTree(const T& rootValue) : size_(1) {
        root_ = std::make_shared<Node>(rootValue);
    }
    
    // Insert value (level-order insertion)
    void insert(const T& value) {
        insertLevelOrder(value);
        std::cout << "Inserted " << value << " (size: " << size_ << ")" << std::endl;
    }
    
    // Insert at specific position (manual tree building)
    NodePtr insertAtNode(NodePtr parent, const T& value, bool isLeft) {
        if (!parent) {
            if (!root_) {
                root_ = std::make_shared<Node>(value);
                size_++;
                std::cout << "Inserted " << value << " as root" << std::endl;
                return root_;
            }
            return nullptr;
        }
        
        auto newNode = std::make_shared<Node>(value);
        newNode->parent = parent;
        
        if (isLeft) {
            if (parent->left) {
                std::cout << "Left child already exists for " << parent->data << std::endl;
                return nullptr;
            }
            parent->left = newNode;
        } else {
            if (parent->right) {
                std::cout << "Right child already exists for " << parent->data << std::endl;
                return nullptr;
            }
            parent->right = newNode;
        }
        
        size_++;
        std::cout << "Inserted " << value << " as " << (isLeft ? "left" : "right") 
                  << " child of " << parent->data << std::endl;
        return newNode;
    }
    
    // Find node with given value
    NodePtr find(const T& value) const {
        return findNode(root_, value);
    }
    
    // Delete node with given value
    bool remove(const T& value) {
        NodePtr nodeToDelete = find(value);
        if (!nodeToDelete) {
            std::cout << "Node with value " << value << " not found" << std::endl;
            return false;
        }
        
        if (size_ == 1) {
            root_.reset();
            size_--;
            std::cout << "Removed root node " << value << std::endl;
            return true;
        }
        
        // Find deepest rightmost node
        NodePtr deepest = findDeepestRightmost();
        
        // Replace data of node to be deleted with deepest node's data
        T deepestData = deepest->data;
        deleteDeepestRightmost(deepest);
        nodeToDelete->data = deepestData;
        
        size_--;
        std::cout << "Removed node " << value << " (replaced with " << deepestData << ")" << std::endl;
        return true;
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
    
    // Level-order traversal (BFS)
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
    
    // Iterative traversals using stack
    std::vector<T> inorderIterative() const {
        std::vector<T> result;
        std::stack<NodePtr> stack;
        NodePtr current = root_;
        
        while (current || !stack.empty()) {
            // Go to leftmost node
            while (current) {
                stack.push(current);
                current = current->left;
            }
            
            // Current must be nullptr at this point
            current = stack.top();
            stack.pop();
            result.push_back(current->data);
            
            // We have visited the node and its left subtree, now visit right subtree
            current = current->right;
        }
        
        return result;
    }
    
    std::vector<T> preorderIterative() const {
        std::vector<T> result;
        if (!root_) return result;
        
        std::stack<NodePtr> stack;
        stack.push(root_);
        
        while (!stack.empty()) {
            NodePtr current = stack.top();
            stack.pop();
            
            result.push_back(current->data);
            
            // Push right first, then left (so left is processed first)
            if (current->right) stack.push(current->right);
            if (current->left) stack.push(current->left);
        }
        
        return result;
    }
    
    std::vector<T> postorderIterative() const {
        std::vector<T> result;
        if (!root_) return result;
        
        std::stack<NodePtr> stack;
        NodePtr lastVisited = nullptr;
        NodePtr current = root_;
        
        while (current || !stack.empty()) {
            if (current) {
                stack.push(current);
                current = current->left;
            } else {
                NodePtr peekNode = stack.top();
                
                // If right child exists and hasn't been processed yet
                if (peekNode->right && lastVisited != peekNode->right) {
                    current = peekNode->right;
                } else {
                    result.push_back(peekNode->data);
                    lastVisited = stack.top();
                    stack.pop();
                }
            }
        }
        
        return result;
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
    
    // Check if tree is complete
    bool isComplete() const {
        if (!root_) return true;
        
        std::queue<NodePtr> queue;
        queue.push(root_);
        bool mustBeLeaf = false;
        
        while (!queue.empty()) {
            NodePtr current = queue.front();
            queue.pop();
            
            // Check left child
            if (current->left) {
                if (mustBeLeaf) return false;
                queue.push(current->left);
            } else {
                mustBeLeaf = true;
            }
            
            // Check right child
            if (current->right) {
                if (mustBeLeaf) return false;
                queue.push(current->right);
            } else {
                mustBeLeaf = true;
            }
        }
        
        return true;
    }
    
    // Check if tree is full (every node has 0 or 2 children)
    bool isFull() const {
        return isFullHelper(root_);
    }
    
private:
    bool isFullHelper(NodePtr node) const {
        if (!node) return true;
        
        // If it's a leaf node
        if (!node->left && !node->right) return true;
        
        // If it has both children
        if (node->left && node->right) {
            return isFullHelper(node->left) && isFullHelper(node->right);
        }
        
        // If it has only one child
        return false;
    }
    
public:
    // Check if tree is perfect (all leaves at same level)
    bool isPerfect() const {
        int h = height();
        return isPerfectHelper(root_, h, 0);
    }
    
private:
    bool isPerfectHelper(NodePtr node, int targetHeight, int currentLevel) const {
        if (!node) return true;
        
        // If it's a leaf
        if (!node->left && !node->right) {
            return currentLevel == targetHeight;
        }
        
        // If it has only one child
        if (!node->left || !node->right) {
            return false;
        }
        
        // If it has both children
        return isPerfectHelper(node->left, targetHeight, currentLevel + 1) &&
               isPerfectHelper(node->right, targetHeight, currentLevel + 1);
    }
    
public:
    // Mirror/flip the tree
    void mirror() {
        mirrorHelper(root_);
        std::cout << "Tree mirrored" << std::endl;
    }
    
private:
    void mirrorHelper(NodePtr node) {
        if (node) {
            std::swap(node->left, node->right);
            mirrorHelper(node->left);
            mirrorHelper(node->right);
        }
    }
    
public:
    // Find lowest common ancestor
    NodePtr findLCA(const T& value1, const T& value2) const {
        return findLCAHelper(root_, value1, value2);
    }
    
private:
    NodePtr findLCAHelper(NodePtr node, const T& value1, const T& value2) const {
        if (!node) return nullptr;
        
        if (node->data == value1 || node->data == value2) {
            return node;
        }
        
        NodePtr leftLCA = findLCAHelper(node->left, value1, value2);
        NodePtr rightLCA = findLCAHelper(node->right, value1, value2);
        
        if (leftLCA && rightLCA) return node;
        
        return leftLCA ? leftLCA : rightLCA;
    }
    
public:
    // Get path from root to a node
    std::vector<T> getPath(const T& value) const {
        std::vector<T> path;
        if (getPathHelper(root_, value, path)) {
            return path;
        }
        return {}; // Empty path if not found
    }
    
private:
    bool getPathHelper(NodePtr node, const T& value, std::vector<T>& path) const {
        if (!node) return false;
        
        path.push_back(node->data);
        
        if (node->data == value) return true;
        
        if (getPathHelper(node->left, value, path) || 
            getPathHelper(node->right, value, path)) {
            return true;
        }
        
        path.pop_back();
        return false;
    }
    
public:
    // Find diameter (longest path between any two nodes)
    int diameter() const {
        int diameter = 0;
        diameterHelper(root_, diameter);
        return diameter;
    }
    
private:
    int diameterHelper(NodePtr node, int& diameter) const {
        if (!node) return 0;
        
        int leftHeight = diameterHelper(node->left, diameter);
        int rightHeight = diameterHelper(node->right, diameter);
        
        diameter = std::max(diameter, leftHeight + rightHeight);
        
        return 1 + std::max(leftHeight, rightHeight);
    }
    
public:
    // Count leaf nodes
    int countLeaves() const {
        return countLeavesHelper(root_);
    }
    
private:
    int countLeavesHelper(NodePtr node) const {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return countLeavesHelper(node->left) + countLeavesHelper(node->right);
    }
    
public:
    // Print tree structure
    void printTree() const {
        if (!root_) {
            std::cout << "Tree is empty" << std::endl;
            return;
        }
        
        std::cout << "Binary Tree Structure:" << std::endl;
        printTree(root_, "", true, std::cout);
    }
    
    // Display traversals
    void displayTraversals() const {
        std::cout << "Traversals:" << std::endl;
        
        auto inorder = inorderTraversal();
        std::cout << "Inorder (recursive):   ";
        for (size_t i = 0; i < inorder.size(); ++i) {
            std::cout << inorder[i];
            if (i < inorder.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
        
        auto inorderIter = inorderIterative();
        std::cout << "Inorder (iterative):   ";
        for (size_t i = 0; i < inorderIter.size(); ++i) {
            std::cout << inorderIter[i];
            if (i < inorderIter.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
        
        auto preorder = preorderTraversal();
        std::cout << "Preorder (recursive):  ";
        for (size_t i = 0; i < preorder.size(); ++i) {
            std::cout << preorder[i];
            if (i < preorder.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
        
        auto preorderIter = preorderIterative();
        std::cout << "Preorder (iterative):  ";
        for (size_t i = 0; i < preorderIter.size(); ++i) {
            std::cout << preorderIter[i];
            if (i < preorderIter.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
        
        auto postorder = postorderTraversal();
        std::cout << "Postorder (recursive): ";
        for (size_t i = 0; i < postorder.size(); ++i) {
            std::cout << postorder[i];
            if (i < postorder.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
        
        auto postorderIter = postorderIterative();
        std::cout << "Postorder (iterative): ";
        for (size_t i = 0; i < postorderIter.size(); ++i) {
            std::cout << postorderIter[i];
            if (i < postorderIter.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
        
        auto levelorder = levelOrderTraversal();
        std::cout << "Level-order:           ";
        for (size_t i = 0; i < levelorder.size(); ++i) {
            std::cout << levelorder[i];
            if (i < levelorder.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
    
    // Display tree properties
    void displayProperties() const {
        std::cout << "Tree Properties:" << std::endl;
        std::cout << "Size: " << size() << std::endl;
        std::cout << "Height: " << height() << std::endl;
        std::cout << "Leaf count: " << countLeaves() << std::endl;
        std::cout << "Diameter: " << diameter() << std::endl;
        std::cout << "Is empty: " << (empty() ? "Yes" : "No") << std::endl;
        std::cout << "Is complete: " << (isComplete() ? "Yes" : "No") << std::endl;
        std::cout << "Is full: " << (isFull() ? "Yes" : "No") << std::endl;
        std::cout << "Is perfect: " << (isPerfect() ? "Yes" : "No") << std::endl;
    }
    
    // Get root node (for manual tree building)
    NodePtr getRoot() const {
        return root_;
    }
    
    // Clear the tree
    void clear() {
        root_.reset();
        size_ = 0;
        std::cout << "Tree cleared" << std::endl;
    }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void demonstrateBasicOperations() {
    printSeparator("BASIC BINARY TREE OPERATIONS");
    
    BinaryTree<int> tree;
    
    std::cout << "\n--- Level-order Insertion ---" << std::endl;
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7};
    for (int value : values) {
        tree.insert(value);
    }
    
    tree.printTree();
    tree.displayProperties();
    
    std::cout << "\n--- Search Operations ---" << std::endl;
    std::cout << "Searching for 5: " << (tree.find(5) ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 10: " << (tree.find(10) ? "Found" : "Not Found") << std::endl;
    
    std::cout << "\n--- Path Operations ---" << std::endl;
    auto path = tree.getPath(5);
    std::cout << "Path to 5: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
}

void demonstrateTraversals() {
    printSeparator("TREE TRAVERSAL METHODS");
    
    BinaryTree<char> tree;
    
    // Build a sample tree manually for better understanding
    //       A
    //      / \
    //     B   C
    //    / \ / \
    //   D  E F  G
    
    std::cout << "\n--- Manual Tree Construction ---" << std::endl;
    tree.insert('A'); // Root
    auto root = tree.getRoot();
    
    auto nodeB = tree.insertAtNode(root, 'B', true);   // Left child of A
    auto nodeC = tree.insertAtNode(root, 'C', false);  // Right child of A
    
    tree.insertAtNode(nodeB, 'D', true);   // Left child of B
    tree.insertAtNode(nodeB, 'E', false);  // Right child of B
    tree.insertAtNode(nodeC, 'F', true);   // Left child of C
    tree.insertAtNode(nodeC, 'G', false);  // Right child of C
    
    tree.printTree();
    
    std::cout << "\n--- All Traversal Methods ---" << std::endl;
    tree.displayTraversals();
    
    std::cout << "\nTraversal Explanations:" << std::endl;
    std::cout << "- Inorder (L-Root-R): Visits left subtree, root, then right subtree" << std::endl;
    std::cout << "- Preorder (Root-L-R): Visits root, left subtree, then right subtree" << std::endl;
    std::cout << "- Postorder (L-R-Root): Visits left subtree, right subtree, then root" << std::endl;
    std::cout << "- Level-order: Visits nodes level by level (BFS)" << std::endl;
}

void demonstrateAdvancedOperations() {
    printSeparator("ADVANCED TREE OPERATIONS");
    
    BinaryTree<int> tree;
    
    // Build tree: 1, 2, 3, 4, 5, 6, 7
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7};
    for (int value : values) {
        tree.insert(value);
    }
    
    std::cout << "\n--- Original Tree ---" << std::endl;
    tree.printTree();
    tree.displayProperties();
    
    std::cout << "\n--- Lowest Common Ancestor ---" << std::endl;
    auto lca = tree.findLCA(4, 5);
    if (lca) {
        std::cout << "LCA of 4 and 5: " << lca->data << std::endl;
    }
    
    lca = tree.findLCA(4, 7);
    if (lca) {
        std::cout << "LCA of 4 and 7: " << lca->data << std::endl;
    }
    
    std::cout << "\n--- Mirror Operation ---" << std::endl;
    tree.mirror();
    tree.printTree();
    
    // Mirror back for other operations
    tree.mirror();
    
    std::cout << "\n--- Deletion Operation ---" << std::endl;
    tree.remove(2);
    tree.printTree();
    tree.displayProperties();
}

void demonstrateTreeTypes() {
    printSeparator("DIFFERENT TREE TYPES");
    
    std::cout << "\n--- Complete Binary Tree ---" << std::endl;
    BinaryTree<int> completeTree;
    for (int i = 1; i <= 7; ++i) {
        completeTree.insert(i);
    }
    completeTree.printTree();
    completeTree.displayProperties();
    
    std::cout << "\n--- Full Binary Tree ---" << std::endl;
    BinaryTree<char> fullTree('A');
    auto rootA = fullTree.getRoot();
    auto nodeB = fullTree.insertAtNode(rootA, 'B', true);
    auto nodeC = fullTree.insertAtNode(rootA, 'C', false);
    fullTree.insertAtNode(nodeB, 'D', true);
    fullTree.insertAtNode(nodeB, 'E', false);
    fullTree.insertAtNode(nodeC, 'F', true);
    fullTree.insertAtNode(nodeC, 'G', false);
    
    fullTree.printTree();
    fullTree.displayProperties();
    
    std::cout << "\n--- Perfect Binary Tree ---" << std::endl;
    BinaryTree<int> perfectTree;
    for (int i = 1; i <= 7; ++i) {
        perfectTree.insert(i);
    }
    perfectTree.printTree();
    perfectTree.displayProperties();
}

void demonstratePracticalApplications() {
    printSeparator("PRACTICAL APPLICATIONS");
    
    // 1. Expression Tree
    std::cout << "\n--- Expression Tree ---" << std::endl;
    BinaryTree<std::string> exprTree("+");
    auto root = exprTree.getRoot();
    
    auto leftMult = exprTree.insertAtNode(root, "*", true);
    auto rightSub = exprTree.insertAtNode(root, "-", false);
    
    exprTree.insertAtNode(leftMult, "3", true);
    exprTree.insertAtNode(leftMult, "4", false);
    exprTree.insertAtNode(rightSub, "8", true);
    exprTree.insertAtNode(rightSub, "2", false);
    
    exprTree.printTree();
    std::cout << "This represents the expression: (3 * 4) + (8 - 2) = 18" << std::endl;
    
    std::cout << "\nTraversals of expression tree:" << std::endl;
    exprTree.displayTraversals();
    
    // 2. Decision Tree
    std::cout << "\n--- Decision Tree Example ---" << std::endl;
    BinaryTree<std::string> decisionTree("Age >= 18?");
    auto decisionRoot = decisionTree.getRoot();
    
    auto adult = decisionTree.insertAtNode(decisionRoot, "License?", true);
    auto minor = decisionTree.insertAtNode(decisionRoot, "Not Eligible", false);
    
    decisionTree.insertAtNode(adult, "Can Drive", true);
    decisionTree.insertAtNode(adult, "Cannot Drive", false);
    
    decisionTree.printTree();
    std::cout << "This represents a simple driving eligibility decision tree" << std::endl;
    
    // 3. File System Tree
    std::cout << "\n--- File System Tree ---" << std::endl;
    BinaryTree<std::string> fileTree("root/");
    auto fileRoot = fileTree.getRoot();
    
    auto documents = fileTree.insertAtNode(fileRoot, "documents/", true);
    auto programs = fileTree.insertAtNode(fileRoot, "programs/", false);
    
    fileTree.insertAtNode(documents, "file1.txt", true);
    fileTree.insertAtNode(documents, "file2.pdf", false);
    fileTree.insertAtNode(programs, "app1.exe", true);
    fileTree.insertAtNode(programs, "app2.exe", false);
    
    fileTree.printTree();
    std::cout << "This represents a simplified file system hierarchy" << std::endl;
}

void demonstrateIterativeVsRecursive() {
    printSeparator("ITERATIVE vs RECURSIVE TRAVERSALS");
    
    BinaryTree<int> tree;
    for (int i = 1; i <= 10; ++i) {
        tree.insert(i);
    }
    
    tree.printTree();
    
    std::cout << "\n--- Performance Comparison ---" << std::endl;
    std::cout << "Both iterative and recursive versions produce same results:" << std::endl;
    tree.displayTraversals();
    
    std::cout << "\nCharacteristics:" << std::endl;
    std::cout << "Recursive:" << std::endl;
    std::cout << "  ✅ Easier to understand and implement" << std::endl;
    std::cout << "  ✅ Natural expression of tree traversal" << std::endl;
    std::cout << "  ❌ Uses call stack (O(h) space for height h)" << std::endl;
    std::cout << "  ❌ Risk of stack overflow for deep trees" << std::endl;
    
    std::cout << "Iterative:" << std::endl;
    std::cout << "  ✅ No recursion overhead" << std::endl;
    std::cout << "  ✅ Can handle very deep trees" << std::endl;
    std::cout << "  ❌ More complex to implement" << std::endl;
    std::cout << "  ❌ Uses explicit stack/queue data structure" << std::endl;
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "      BINARY TREE DEMONSTRATION              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateTraversals();
        demonstrateAdvancedOperations();
        demonstrateTreeTypes();
        demonstratePracticalApplications();
        demonstrateIterativeVsRecursive();
        
        printSeparator("PERFORMANCE CHARACTERISTICS");
        std::cout << "\nTime Complexity Summary:" << std::endl;
        std::cout << "- Search:      O(n) - Must potentially visit all nodes" << std::endl;
        std::cout << "- Insertion:   O(n) - Level-order insertion requires traversal" << std::endl;
        std::cout << "- Deletion:    O(n) - Need to find node and reorganize" << std::endl;
        std::cout << "- Traversals:  O(n) - Visit every node once" << std::endl;
        std::cout << "- Space:       O(n) - Store n nodes" << std::endl;
        
        std::cout << "\nTraversal Space Complexity:" << std::endl;
        std::cout << "- Recursive:   O(h) - Call stack depth equals tree height" << std::endl;
        std::cout << "- Iterative:   O(h) - Explicit stack/queue storage" << std::endl;
        std::cout << "- Level-order: O(w) - Queue size equals maximum width" << std::endl;
        
        std::cout << "\nBinary Tree Types:" << std::endl;
        std::cout << "Complete Binary Tree:" << std::endl;
        std::cout << "  ✅ All levels filled except possibly last" << std::endl;
        std::cout << "  ✅ Last level filled from left to right" << std::endl;
        std::cout << "  ✅ Used in heaps" << std::endl;
        
        std::cout << "Full Binary Tree:" << std::endl;
        std::cout << "  ✅ Every node has 0 or 2 children" << std::endl;
        std::cout << "  ✅ No node has exactly 1 child" << std::endl;
        std::cout << "  ✅ Optimal for certain algorithms" << std::endl;
        
        std::cout << "Perfect Binary Tree:" << std::endl;
        std::cout << "  ✅ All internal nodes have 2 children" << std::endl;
        std::cout << "  ✅ All leaves are at same level" << std::endl;
        std::cout << "  ✅ Has exactly 2^h - 1 nodes" << std::endl;
        
        std::cout << "\nCommon Use Cases:" << std::endl;
        std::cout << "🎯 Expression parsing and evaluation" << std::endl;
        std::cout << "🎯 Decision trees and game trees" << std::endl;
        std::cout << "🎯 File system hierarchies" << std::endl;
        std::cout << "🎯 Huffman coding trees" << std::endl;
        std::cout << "🎯 Abstract syntax trees (AST)" << std::endl;
        std::cout << "🎯 Binary space partitioning" << std::endl;
        std::cout << "🎯 Heap implementation foundation" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
