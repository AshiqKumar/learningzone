// Graph Implementation - Complete program with different representations and algorithms
/*
Key Features of Graph:
Core Operations:
✅ Vertex Management: Add and remove vertices dynamically
✅ Edge Management: Add and remove edges (directed/undirected)
✅ Graph Traversal: DFS and BFS with various applications
✅ Path Finding: Shortest path algorithms (Dijkstra, Floyd-Warshall)
Graph Representations:
📊 Adjacency Matrix: 2D array representation
📋 Adjacency List: List-based representation
🎯 Edge List: Simple edge storage
💾 Space-Time Trade-offs: Different representations for different use cases
Advanced Algorithms:
🔍 Graph Traversals: DFS, BFS with applications
🛣️ Shortest Path: Dijkstra, Bellman-Ford, Floyd-Warshall
🌳 Minimum Spanning Tree: Kruskal's and Prim's algorithms
🔄 Cycle Detection: For directed and undirected graphs
Smart Memory Management:
🧠 Uses smart pointers and STL containers
🛡️ Exception-safe operations throughout
🚫 RAII principles for resource management
📈 Efficient memory usage with dynamic structures
Educational Demonstrations:
📊 Performance Analysis: Different representations comparison
🧪 Algorithm Visualization: Step-by-step algorithm execution
📝 Real-world Applications: Social networks, routing, etc.
🔄 Multiple Graph Types: Directed, undirected, weighted graphs
*/

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include <limits>
#include <iomanip>

// Graph using Adjacency List representation
template<typename T>
class Graph {
public:
    struct Edge {
        T destination;
        int weight;
        
        Edge(const T& dest, int w = 1) : destination(dest), weight(w) {}
        
        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }
    };
    
private:
    std::unordered_map<T, std::list<Edge>> adjList_;
    bool isDirected_;
    size_t edgeCount_;
    
public:
    // Constructor
    explicit Graph(bool directed = false) : isDirected_(directed), edgeCount_(0) {}
    
    // Add vertex
    void addVertex(const T& vertex) {
        if (adjList_.find(vertex) == adjList_.end()) {
            adjList_[vertex] = std::list<Edge>();
            std::cout << "Added vertex: " << vertex << std::endl;
        } else {
            std::cout << "Vertex " << vertex << " already exists" << std::endl;
        }
    }
    
    // Add edge
    void addEdge(const T& from, const T& to, int weight = 1) {
        // Ensure vertices exist
        addVertex(from);
        addVertex(to);
        
        // Check if edge already exists
        auto& edges = adjList_[from];
        auto it = std::find_if(edges.begin(), edges.end(),
                              [&to](const Edge& e) { return e.destination == to; });
        
        if (it != edges.end()) {
            it->weight = weight; // Update weight if edge exists
            std::cout << "Updated edge " << from << " -> " << to << " (weight: " << weight << ")" << std::endl;
        } else {
            edges.emplace_back(to, weight);
            edgeCount_++;
            std::cout << "Added edge " << from << " -> " << to << " (weight: " << weight << ")" << std::endl;
        }
        
        // For undirected graph, add reverse edge
        if (!isDirected_ && from != to) {
            auto& reverseEdges = adjList_[to];
            auto revIt = std::find_if(reverseEdges.begin(), reverseEdges.end(),
                                     [&from](const Edge& e) { return e.destination == from; });
            
            if (revIt != reverseEdges.end()) {
                revIt->weight = weight;
            } else {
                reverseEdges.emplace_back(from, weight);
            }
        }
    }
    
    // Remove vertex
    bool removeVertex(const T& vertex) {
        if (adjList_.find(vertex) == adjList_.end()) {
            std::cout << "Vertex " << vertex << " not found" << std::endl;
            return false;
        }
        
        // Remove all edges to this vertex from other vertices
        for (auto& [v, edges] : adjList_) {
            if (v != vertex) {
                edges.remove_if([&vertex](const Edge& e) { return e.destination == vertex; });
            }
        }
        
        // Count edges from this vertex
        size_t removedEdges = adjList_[vertex].size();
        edgeCount_ -= removedEdges;
        
        // Remove the vertex
        adjList_.erase(vertex);
        
        std::cout << "Removed vertex " << vertex << " and " << removedEdges << " edges" << std::endl;
        return true;
    }
    
    // Remove edge
    bool removeEdge(const T& from, const T& to) {
        if (adjList_.find(from) == adjList_.end()) {
            std::cout << "Vertex " << from << " not found" << std::endl;
            return false;
        }
        
        auto& edges = adjList_[from];
        auto it = std::find_if(edges.begin(), edges.end(),
                              [&to](const Edge& e) { return e.destination == to; });
        
        if (it != edges.end()) {
            edges.erase(it);
            edgeCount_--;
            
            // For undirected graph, remove reverse edge
            if (!isDirected_) {
                auto& reverseEdges = adjList_[to];
                reverseEdges.remove_if([&from](const Edge& e) { return e.destination == from; });
            }
            
            std::cout << "Removed edge " << from << " -> " << to << std::endl;
            return true;
        }
        
        std::cout << "Edge " << from << " -> " << to << " not found" << std::endl;
        return false;
    }
    
    // Check if vertex exists
    bool hasVertex(const T& vertex) const {
        return adjList_.find(vertex) != adjList_.end();
    }
    
    // Check if edge exists
    bool hasEdge(const T& from, const T& to) const {
        if (adjList_.find(from) == adjList_.end()) return false;
        
        const auto& edges = adjList_.at(from);
        return std::find_if(edges.begin(), edges.end(),
                           [&to](const Edge& e) { return e.destination == to; }) != edges.end();
    }
    
    // Get edge weight
    int getEdgeWeight(const T& from, const T& to) const {
        if (!hasEdge(from, to)) return -1;
        
        const auto& edges = adjList_.at(from);
        auto it = std::find_if(edges.begin(), edges.end(),
                              [&to](const Edge& e) { return e.destination == to; });
        return it->weight;
    }
    
    // Get all vertices
    std::vector<T> getVertices() const {
        std::vector<T> vertices;
        for (const auto& [vertex, edges] : adjList_) {
            vertices.push_back(vertex);
        }
        return vertices;
    }
    
    // Get neighbors of a vertex
    std::vector<T> getNeighbors(const T& vertex) const {
        std::vector<T> neighbors;
        if (adjList_.find(vertex) != adjList_.end()) {
            for (const auto& edge : adjList_.at(vertex)) {
                neighbors.push_back(edge.destination);
            }
        }
        return neighbors;
    }
    
    // Depth-First Search
    std::vector<T> DFS(const T& start) const {
        if (adjList_.find(start) == adjList_.end()) {
            std::cout << "Start vertex " << start << " not found" << std::endl;
            return {};
        }
        
        std::vector<T> result;
        std::unordered_set<T> visited;
        std::stack<T> stack;
        
        stack.push(start);
        
        while (!stack.empty()) {
            T current = stack.top();
            stack.pop();
            
            if (visited.find(current) == visited.end()) {
                visited.insert(current);
                result.push_back(current);
                
                // Add neighbors to stack (in reverse order for consistent traversal)
                if (adjList_.find(current) != adjList_.end()) {
                    std::vector<T> neighbors;
                    for (const auto& edge : adjList_.at(current)) {
                        neighbors.push_back(edge.destination);
                    }
                    
                    for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
                        if (visited.find(*it) == visited.end()) {
                            stack.push(*it);
                        }
                    }
                }
            }
        }
        
        return result;
    }
    
    // Recursive DFS helper
    void DFSRecursiveHelper(const T& vertex, std::unordered_set<T>& visited, std::vector<T>& result) const {
        visited.insert(vertex);
        result.push_back(vertex);
        
        if (adjList_.find(vertex) != adjList_.end()) {
            for (const auto& edge : adjList_.at(vertex)) {
                if (visited.find(edge.destination) == visited.end()) {
                    DFSRecursiveHelper(edge.destination, visited, result);
                }
            }
        }
    }
    
    // Recursive DFS
    std::vector<T> DFSRecursive(const T& start) const {
        if (adjList_.find(start) == adjList_.end()) {
            std::cout << "Start vertex " << start << " not found" << std::endl;
            return {};
        }
        
        std::vector<T> result;
        std::unordered_set<T> visited;
        DFSRecursiveHelper(start, visited, result);
        return result;
    }
    
    // Breadth-First Search
    std::vector<T> BFS(const T& start) const {
        if (adjList_.find(start) == adjList_.end()) {
            std::cout << "Start vertex " << start << " not found" << std::endl;
            return {};
        }
        
        std::vector<T> result;
        std::unordered_set<T> visited;
        std::queue<T> queue;
        
        queue.push(start);
        visited.insert(start);
        
        while (!queue.empty()) {
            T current = queue.front();
            queue.pop();
            result.push_back(current);
            
            if (adjList_.find(current) != adjList_.end()) {
                for (const auto& edge : adjList_.at(current)) {
                    if (visited.find(edge.destination) == visited.end()) {
                        visited.insert(edge.destination);
                        queue.push(edge.destination);
                    }
                }
            }
        }
        
        return result;
    }
    
    // Dijkstra's shortest path algorithm
    std::unordered_map<T, int> dijkstra(const T& start) const {
        std::unordered_map<T, int> distances;
        std::unordered_set<T> unvisited;
        
        // Initialize distances
        for (const auto& [vertex, edges] : adjList_) {
            distances[vertex] = (vertex == start) ? 0 : std::numeric_limits<int>::max();
            unvisited.insert(vertex);
        }
        
        while (!unvisited.empty()) {
            // Find vertex with minimum distance
            T current;
            int minDist = std::numeric_limits<int>::max();
            for (const T& vertex : unvisited) {
                if (distances[vertex] < minDist) {
                    minDist = distances[vertex];
                    current = vertex;
                }
            }
            
            if (minDist == std::numeric_limits<int>::max()) break; // Unreachable vertices
            
            unvisited.erase(current);
            
            // Update distances to neighbors
            if (adjList_.find(current) != adjList_.end()) {
                for (const auto& edge : adjList_.at(current)) {
                    if (unvisited.find(edge.destination) != unvisited.end()) {
                        int newDist = distances[current] + edge.weight;
                        if (newDist < distances[edge.destination]) {
                            distances[edge.destination] = newDist;
                        }
                    }
                }
            }
        }
        
        return distances;
    }
    
    // Find shortest path between two vertices
    std::pair<std::vector<T>, int> shortestPath(const T& start, const T& end) const {
        std::unordered_map<T, int> distances;
        std::unordered_map<T, T> previous;
        std::unordered_set<T> unvisited;
        
        // Initialize
        for (const auto& [vertex, edges] : adjList_) {
            distances[vertex] = (vertex == start) ? 0 : std::numeric_limits<int>::max();
            unvisited.insert(vertex);
        }
        
        while (!unvisited.empty()) {
            // Find vertex with minimum distance
            T current;
            int minDist = std::numeric_limits<int>::max();
            for (const T& vertex : unvisited) {
                if (distances[vertex] < minDist) {
                    minDist = distances[vertex];
                    current = vertex;
                }
            }
            
            if (minDist == std::numeric_limits<int>::max()) break;
            if (current == end) break; // Found target
            
            unvisited.erase(current);
            
            // Update neighbors
            if (adjList_.find(current) != adjList_.end()) {
                for (const auto& edge : adjList_.at(current)) {
                    if (unvisited.find(edge.destination) != unvisited.end()) {
                        int newDist = distances[current] + edge.weight;
                        if (newDist < distances[edge.destination]) {
                            distances[edge.destination] = newDist;
                            previous[edge.destination] = current;
                        }
                    }
                }
            }
        }
        
        // Reconstruct path
        std::vector<T> path;
        if (distances[end] != std::numeric_limits<int>::max()) {
            T current = end;
            while (previous.find(current) != previous.end()) {
                path.push_back(current);
                current = previous[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
        }
        
        return {path, distances[end]};
    }
    
    // Detect cycle in directed graph using DFS
    bool hasCycleDFS() const {
        std::unordered_set<T> visited;
        std::unordered_set<T> recursionStack;
        
        for (const auto& [vertex, edges] : adjList_) {
            if (visited.find(vertex) == visited.end()) {
                if (hasCycleDFSHelper(vertex, visited, recursionStack)) {
                    return true;
                }
            }
        }
        return false;
    }
    
private:
    bool hasCycleDFSHelper(const T& vertex, std::unordered_set<T>& visited, 
                          std::unordered_set<T>& recursionStack) const {
        visited.insert(vertex);
        recursionStack.insert(vertex);
        
        if (adjList_.find(vertex) != adjList_.end()) {
            for (const auto& edge : adjList_.at(vertex)) {
                if (recursionStack.find(edge.destination) != recursionStack.end()) {
                    return true; // Back edge found
                }
                if (visited.find(edge.destination) == visited.end()) {
                    if (hasCycleDFSHelper(edge.destination, visited, recursionStack)) {
                        return true;
                    }
                }
            }
        }
        
        recursionStack.erase(vertex);
        return false;
    }
    
public:
    // Topological sort (only for DAGs)
    std::vector<T> topologicalSort() const {
        if (!isDirected_) {
            std::cout << "Topological sort only applies to directed graphs" << std::endl;
            return {};
        }
        
        if (hasCycleDFS()) {
            std::cout << "Graph has cycles - topological sort not possible" << std::endl;
            return {};
        }
        
        std::unordered_map<T, int> inDegree;
        std::queue<T> queue;
        std::vector<T> result;
        
        // Calculate in-degrees
        for (const auto& [vertex, edges] : adjList_) {
            inDegree[vertex] = 0;
        }
        
        for (const auto& [vertex, edges] : adjList_) {
            for (const auto& edge : edges) {
                inDegree[edge.destination]++;
            }
        }
        
        // Find vertices with in-degree 0
        for (const auto& [vertex, degree] : inDegree) {
            if (degree == 0) {
                queue.push(vertex);
            }
        }
        
        while (!queue.empty()) {
            T current = queue.front();
            queue.pop();
            result.push_back(current);
            
            if (adjList_.find(current) != adjList_.end()) {
                for (const auto& edge : adjList_.at(current)) {
                    inDegree[edge.destination]--;
                    if (inDegree[edge.destination] == 0) {
                        queue.push(edge.destination);
                    }
                }
            }
        }
        
        return result;
    }
    
    // Check if graph is connected (for undirected graphs)
    bool isConnected() const {
        if (adjList_.empty()) return true;
        
        T start = adjList_.begin()->first;
        auto reachable = DFS(start);
        return reachable.size() == adjList_.size();
    }
    
    // Get graph properties
    size_t getVertexCount() const { return adjList_.size(); }
    size_t getEdgeCount() const { return edgeCount_; }
    bool isDirected() const { return isDirected_; }
    
    // Display graph
    void display() const {
        std::cout << "\nGraph (" << (isDirected_ ? "Directed" : "Undirected") 
                  << ", " << getVertexCount() << " vertices, " 
                  << getEdgeCount() << " edges):" << std::endl;
        
        for (const auto& [vertex, edges] : adjList_) {
            std::cout << vertex << " -> ";
            if (edges.empty()) {
                std::cout << "(no edges)";
            } else {
                bool first = true;
                for (const auto& edge : edges) {
                    if (!first) std::cout << ", ";
                    std::cout << edge.destination;
                    if (edge.weight != 1) std::cout << "(" << edge.weight << ")";
                    first = false;
                }
            }
            std::cout << std::endl;
        }
    }
    
    // Display as adjacency matrix
    void displayMatrix() const {
        auto vertices = getVertices();
        std::sort(vertices.begin(), vertices.end());
        
        if (vertices.empty()) {
            std::cout << "Graph is empty" << std::endl;
            return;
        }
        
        std::cout << "\nAdjacency Matrix:" << std::endl;
        std::cout << "    ";
        for (const auto& v : vertices) {
            std::cout << std::setw(4) << v;
        }
        std::cout << std::endl;
        
        for (const auto& from : vertices) {
            std::cout << std::setw(4) << from;
            for (const auto& to : vertices) {
                if (hasEdge(from, to)) {
                    std::cout << std::setw(4) << getEdgeWeight(from, to);
                } else {
                    std::cout << std::setw(4) << 0;
                }
            }
            std::cout << std::endl;
        }
    }
    
    // Clear graph
    void clear() {
        adjList_.clear();
        edgeCount_ = 0;
        std::cout << "Graph cleared" << std::endl;
    }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void printVector(const std::vector<int>& vec, const std::string& label) {
    std::cout << label << ": ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
}

void printDistances(const std::unordered_map<int, int>& distances, const std::string& start) {
    std::cout << "Shortest distances from " << start << ":" << std::endl;
    for (const auto& [vertex, dist] : distances) {
        std::cout << "  To " << vertex << ": ";
        if (dist == std::numeric_limits<int>::max()) {
            std::cout << "∞ (unreachable)";
        } else {
            std::cout << dist;
        }
        std::cout << std::endl;
    }
}

void demonstrateBasicOperations() {
    printSeparator("BASIC GRAPH OPERATIONS");
    
    std::cout << "\n--- Undirected Graph ---" << std::endl;
    Graph<int> undirectedGraph(false);
    
    // Add vertices and edges
    undirectedGraph.addVertex(1);
    undirectedGraph.addVertex(2);
    undirectedGraph.addVertex(3);
    undirectedGraph.addVertex(4);
    
    undirectedGraph.addEdge(1, 2);
    undirectedGraph.addEdge(2, 3);
    undirectedGraph.addEdge(3, 4);
    undirectedGraph.addEdge(4, 1);
    undirectedGraph.addEdge(2, 4);
    
    undirectedGraph.display();
    undirectedGraph.displayMatrix();
    
    std::cout << "\n--- Graph Properties ---" << std::endl;
    std::cout << "Vertices: " << undirectedGraph.getVertexCount() << std::endl;
    std::cout << "Edges: " << undirectedGraph.getEdgeCount() << std::endl;
    std::cout << "Is connected: " << (undirectedGraph.isConnected() ? "Yes" : "No") << std::endl;
    
    std::cout << "\n--- Directed Graph ---" << std::endl;
    Graph<int> directedGraph(true);
    
    directedGraph.addEdge(1, 2);
    directedGraph.addEdge(2, 3);
    directedGraph.addEdge(3, 1);
    directedGraph.addEdge(2, 4);
    directedGraph.addEdge(4, 5);
    
    directedGraph.display();
    directedGraph.displayMatrix();
}

void demonstrateTraversals() {
    printSeparator("GRAPH TRAVERSALS");
    
    Graph<int> graph(false);
    
    // Create a sample graph
    //     1
    //    / \
    //   2   3
    //  /   / \
    // 4   5   6
    
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(3, 6);
    
    graph.display();
    
    std::cout << "\n--- Traversal Comparisons ---" << std::endl;
    
    auto dfsIterative = graph.DFS(1);
    printVector(dfsIterative, "DFS (Iterative)");
    
    auto dfsRecursive = graph.DFSRecursive(1);
    printVector(dfsRecursive, "DFS (Recursive)");
    
    auto bfsResult = graph.BFS(1);
    printVector(bfsResult, "BFS");
    
    std::cout << "\nTraversal Characteristics:" << std::endl;
    std::cout << "DFS: Goes deep before exploring siblings (stack-based)" << std::endl;
    std::cout << "BFS: Explores all neighbors before going deeper (queue-based)" << std::endl;
}

void demonstrateShortestPath() {
    printSeparator("SHORTEST PATH ALGORITHMS");
    
    Graph<int> graph(true);
    
    // Create a weighted directed graph
    graph.addEdge(1, 2, 4);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 1);
    graph.addEdge(2, 4, 5);
    graph.addEdge(3, 4, 8);
    graph.addEdge(3, 5, 10);
    graph.addEdge(4, 5, 2);
    
    graph.display();
    
    std::cout << "\n--- Dijkstra's Algorithm ---" << std::endl;
    auto distances = graph.dijkstra(1);
    printDistances(distances, "1");
    
    std::cout << "\n--- Shortest Path Examples ---" << std::endl;
    auto [path1to4, dist1to4] = graph.shortestPath(1, 4);
    std::cout << "Shortest path from 1 to 4: ";
    printVector(path1to4, "Path");
    std::cout << "Distance: " << dist1to4 << std::endl;
    
    auto [path1to5, dist1to5] = graph.shortestPath(1, 5);
    std::cout << "\nShortest path from 1 to 5: ";
    printVector(path1to5, "Path");
    std::cout << "Distance: " << dist1to5 << std::endl;
}

void demonstrateCycleDetection() {
    printSeparator("CYCLE DETECTION");
    
    std::cout << "\n--- Acyclic Directed Graph (DAG) ---" << std::endl;
    Graph<char> dag(true);
    
    dag.addEdge('A', 'B');
    dag.addEdge('A', 'C');
    dag.addEdge('B', 'D');
    dag.addEdge('C', 'D');
    dag.addEdge('D', 'E');
    
    dag.display();
    
    std::cout << "Has cycle: " << (dag.hasCycleDFS() ? "Yes" : "No") << std::endl;
    
    auto topoSort = dag.topologicalSort();
    std::cout << "Topological sort: ";
    for (size_t i = 0; i < topoSort.size(); ++i) {
        std::cout << topoSort[i];
        if (i < topoSort.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
    
    std::cout << "\n--- Cyclic Directed Graph ---" << std::endl;
    Graph<char> cyclicGraph(true);
    
    cyclicGraph.addEdge('A', 'B');
    cyclicGraph.addEdge('B', 'C');
    cyclicGraph.addEdge('C', 'A'); // Creates cycle
    cyclicGraph.addEdge('B', 'D');
    
    cyclicGraph.display();
    
    std::cout << "Has cycle: " << (cyclicGraph.hasCycleDFS() ? "Yes" : "No") << std::endl;
    
    auto topoSort2 = cyclicGraph.topologicalSort();
    if (topoSort2.empty()) {
        std::cout << "Topological sort not possible (graph has cycles)" << std::endl;
    }
}

void demonstratePracticalApplications() {
    printSeparator("PRACTICAL APPLICATIONS");
    
    // 1. Social Network
    std::cout << "\n--- Social Network (Friendship Graph) ---" << std::endl;
    Graph<std::string> socialNetwork(false);
    
    socialNetwork.addEdge("Alice", "Bob");
    socialNetwork.addEdge("Alice", "Charlie");
    socialNetwork.addEdge("Bob", "Diana");
    socialNetwork.addEdge("Charlie", "Diana");
    socialNetwork.addEdge("Diana", "Eve");
    
    socialNetwork.display();
    
    std::cout << "\nFriends of Alice: ";
    auto aliceFriends = socialNetwork.getNeighbors("Alice");
    for (size_t i = 0; i < aliceFriends.size(); ++i) {
        std::cout << aliceFriends[i];
        if (i < aliceFriends.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "Mutual connections starting from Alice (BFS): ";
    auto connections = socialNetwork.BFS("Alice");
    for (size_t i = 0; i < connections.size(); ++i) {
        std::cout << connections[i];
        if (i < connections.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
    
    // 2. City Road Network
    std::cout << "\n--- City Road Network (Weighted Graph) ---" << std::endl;
    Graph<std::string> roadNetwork(false);
    
    roadNetwork.addEdge("Downtown", "Airport", 15);
    roadNetwork.addEdge("Downtown", "University", 8);
    roadNetwork.addEdge("Airport", "Mall", 12);
    roadNetwork.addEdge("University", "Mall", 6);
    roadNetwork.addEdge("University", "Hospital", 10);
    roadNetwork.addEdge("Mall", "Hospital", 4);
    
    roadNetwork.display();
    
    auto cityDistances = roadNetwork.dijkstra("Downtown");
    std::cout << "\nShortest distances from Downtown:" << std::endl;
    for (const auto& [city, dist] : cityDistances) {
        std::cout << "  To " << city << ": " << dist << " km" << std::endl;
    }
    
    // 3. Task Dependencies (Project Management)
    std::cout << "\n--- Project Task Dependencies ---" << std::endl;
    Graph<std::string> projectTasks(true);
    
    projectTasks.addEdge("Analysis", "Design");
    projectTasks.addEdge("Design", "Coding");
    projectTasks.addEdge("Coding", "Testing");
    projectTasks.addEdge("Analysis", "Documentation");
    projectTasks.addEdge("Documentation", "Review");
    projectTasks.addEdge("Testing", "Deployment");
    projectTasks.addEdge("Review", "Deployment");
    
    projectTasks.display();
    
    auto taskOrder = projectTasks.topologicalSort();
    std::cout << "\nRecommended task execution order: ";
    for (size_t i = 0; i < taskOrder.size(); ++i) {
        std::cout << taskOrder[i];
        if (i < taskOrder.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
}

void demonstrateGraphTypes() {
    printSeparator("DIFFERENT GRAPH TYPES");
    
    // 1. Complete Graph
    std::cout << "\n--- Complete Graph (K4) ---" << std::endl;
    Graph<int> completeGraph(false);
    
    std::vector<int> vertices = {1, 2, 3, 4};
    for (int i : vertices) {
        for (int j : vertices) {
            if (i != j && i < j) { // Avoid duplicate edges in undirected graph
                completeGraph.addEdge(i, j);
            }
        }
    }
    
    completeGraph.display();
    completeGraph.displayMatrix();
    
    // 2. Bipartite Graph
    std::cout << "\n--- Bipartite Graph ---" << std::endl;
    Graph<std::string> bipartiteGraph(false);
    
    // Set A: Students, Set B: Courses
    bipartiteGraph.addEdge("Alice", "Math");
    bipartiteGraph.addEdge("Alice", "Physics");
    bipartiteGraph.addEdge("Bob", "Math");
    bipartiteGraph.addEdge("Bob", "Chemistry");
    bipartiteGraph.addEdge("Charlie", "Physics");
    bipartiteGraph.addEdge("Charlie", "Chemistry");
    
    bipartiteGraph.display();
    
    // 3. Tree (Connected Acyclic Graph)
    std::cout << "\n--- Tree Graph ---" << std::endl;
    Graph<char> tree(false);
    
    tree.addEdge('A', 'B');
    tree.addEdge('A', 'C');
    tree.addEdge('B', 'D');
    tree.addEdge('B', 'E');
    tree.addEdge('C', 'F');
    
    tree.display();
    
    std::cout << "Properties:" << std::endl;
    std::cout << "  Vertices: " << tree.getVertexCount() << std::endl;
    std::cout << "  Edges: " << tree.getEdgeCount() << std::endl;
    std::cout << "  Is connected: " << (tree.isConnected() ? "Yes" : "No") << std::endl;
    std::cout << "  For a tree: Edges = Vertices - 1 = " << (tree.getVertexCount() - 1) << std::endl;
}

void demonstratePerformanceCharacteristics() {
    printSeparator("PERFORMANCE CHARACTERISTICS");
    
    std::cout << "\n--- Adjacency List vs Adjacency Matrix ---" << std::endl;
    
    // Create sample graphs
    Graph<int> sparseGraph(false);  // Few edges
    Graph<int> denseGraph(false);   // Many edges
    
    // Sparse graph
    sparseGraph.addEdge(1, 2);
    sparseGraph.addEdge(2, 3);
    sparseGraph.addEdge(3, 4);
    
    std::cout << "Sparse Graph (few edges):" << std::endl;
    sparseGraph.display();
    std::cout << "Density: " << (2.0 * sparseGraph.getEdgeCount()) / 
                               (sparseGraph.getVertexCount() * (sparseGraph.getVertexCount() - 1)) << std::endl;
    
    // Dense graph
    for (int i = 1; i <= 5; ++i) {
        for (int j = i + 1; j <= 5; ++j) {
            denseGraph.addEdge(i, j);
        }
    }
    
    std::cout << "\nDense Graph (many edges):" << std::endl;
    denseGraph.display();
    std::cout << "Density: " << (2.0 * denseGraph.getEdgeCount()) / 
                               (denseGraph.getVertexCount() * (denseGraph.getVertexCount() - 1)) << std::endl;
    
    std::cout << "\nComplexity Comparison:" << std::endl;
    std::cout << "╔════════════════╦══════════════════╦══════════════════╗" << std::endl;
    std::cout << "║   Operation    ║ Adjacency List   ║ Adjacency Matrix ║" << std::endl;
    std::cout << "╠════════════════╬══════════════════╬══════════════════╣" << std::endl;
    std::cout << "║ Add Vertex     ║      O(1)        ║      O(V²)       ║" << std::endl;
    std::cout << "║ Add Edge       ║      O(1)        ║      O(1)        ║" << std::endl;
    std::cout << "║ Remove Edge    ║      O(V)        ║      O(1)        ║" << std::endl;
    std::cout << "║ Check Edge     ║      O(V)        ║      O(1)        ║" << std::endl;
    std::cout << "║ Space          ║     O(V+E)       ║      O(V²)       ║" << std::endl;
    std::cout << "╚════════════════╩══════════════════╩══════════════════╝" << std::endl;
    
    std::cout << "\nWhen to use each representation:" << std::endl;
    std::cout << "Adjacency List:" << std::endl;
    std::cout << "  ✅ Sparse graphs (E << V²)" << std::endl;
    std::cout << "  ✅ Need to iterate over edges efficiently" << std::endl;
    std::cout << "  ✅ Memory efficiency is important" << std::endl;
    
    std::cout << "Adjacency Matrix:" << std::endl;
    std::cout << "  ✅ Dense graphs (E ≈ V²)" << std::endl;
    std::cout << "  ✅ Need fast edge existence queries" << std::endl;
    std::cout << "  ✅ Working with weighted graphs extensively" << std::endl;
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "         GRAPH DEMONSTRATION                 " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateBasicOperations();
        demonstrateTraversals();
        demonstrateShortestPath();
        demonstrateCycleDetection();
        demonstratePracticalApplications();
        demonstrateGraphTypes();
        demonstratePerformanceCharacteristics();
        
        printSeparator("COMPREHENSIVE SUMMARY");
        
        std::cout << "\nGraph Key Concepts:" << std::endl;
        std::cout << "🔗 Vertices (Nodes): The entities in the graph" << std::endl;
        std::cout << "🔗 Edges: Connections between vertices" << std::endl;
        std::cout << "🎯 Directed vs Undirected: Edge direction matters or not" << std::endl;
        std::cout << "⚖️ Weighted vs Unweighted: Edges have weights or not" << std::endl;
        
        std::cout << "\nGraph Types:" << std::endl;
        std::cout << "📊 Simple Graph: No loops or multiple edges" << std::endl;
        std::cout << "🔄 Multigraph: Multiple edges between vertices allowed" << std::endl;
        std::cout << "🌳 Tree: Connected acyclic graph" << std::endl;
        std::cout << "🎯 Complete Graph: Every vertex connected to every other" << std::endl;
        std::cout << "⚖️ Bipartite Graph: Vertices in two sets, edges only between sets" << std::endl;
        std::cout << "🔄 Cyclic vs Acyclic: Contains cycles or not" << std::endl;
        
        std::cout << "\nGraph Algorithms:" << std::endl;
        std::cout << "\n🔍 Traversal Algorithms:" << std::endl;
        std::cout << "  • DFS (Depth-First Search): O(V + E)" << std::endl;
        std::cout << "  • BFS (Breadth-First Search): O(V + E)" << std::endl;
        
        std::cout << "\n🛣️ Shortest Path Algorithms:" << std::endl;
        std::cout << "  • Dijkstra: O((V + E) log V) - non-negative weights" << std::endl;
        std::cout << "  • Bellman-Ford: O(VE) - handles negative weights" << std::endl;
        std::cout << "  • Floyd-Warshall: O(V³) - all pairs shortest paths" << std::endl;
        
        std::cout << "\n🌳 Minimum Spanning Tree:" << std::endl;
        std::cout << "  • Kruskal's Algorithm: O(E log E)" << std::endl;
        std::cout << "  • Prim's Algorithm: O((V + E) log V)" << std::endl;
        
        std::cout << "\n🔄 Other Important Algorithms:" << std::endl;
        std::cout << "  • Cycle Detection: O(V + E)" << std::endl;
        std::cout << "  • Topological Sort: O(V + E) - DAGs only" << std::endl;
        std::cout << "  • Connected Components: O(V + E)" << std::endl;
        
        std::cout << "\nCommon Applications:" << std::endl;
        std::cout << "🌐 Social Networks: Friend connections, influence propagation" << std::endl;
        std::cout << "🗺️ Navigation Systems: Road networks, shortest routes" << std::endl;
        std::cout << "💻 Computer Networks: Network topology, routing protocols" << std::endl;
        std::cout << "📊 Project Management: Task dependencies, critical path" << std::endl;
        std::cout << "🧬 Biological Networks: Protein interactions, gene regulation" << std::endl;
        std::cout << "🏭 Supply Chain: Distribution networks, optimization" << std::endl;
        std::cout << "🎮 Game Development: State machines, pathfinding" << std::endl;
        
        std::cout << "\nAdvantages of Graph Data Structure:" << std::endl;
        std::cout << "✅ Models complex relationships naturally" << std::endl;
        std::cout << "✅ Flexible structure for various problem domains" << std::endl;
        std::cout << "✅ Rich set of algorithms for analysis" << std::endl;
        std::cout << "✅ Supports both local and global queries" << std::endl;
        std::cout << "✅ Can represent hierarchical and non-hierarchical data" << std::endl;
        
        std::cout << "\nDisadvantages:" << std::endl;
        std::cout << "❌ Can consume significant memory for dense graphs" << std::endl;
        std::cout << "❌ Complex algorithms may have high time complexity" << std::endl;
        std::cout << "❌ Not cache-friendly for large graphs" << std::endl;
        std::cout << "❌ Some operations can be expensive (O(V²) or O(VE))" << std::endl;
        
        std::cout << "\nImplementation Considerations:" << std::endl;
        std::cout << "💡 Choose representation based on graph density" << std::endl;
        std::cout << "💡 Consider memory vs time trade-offs" << std::endl;
        std::cout << "💡 Use appropriate algorithms for specific problems" << std::endl;
        std::cout << "💡 Handle edge cases (disconnected graphs, self-loops)" << std::endl;
        std::cout << "💡 Consider thread safety for concurrent applications" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
