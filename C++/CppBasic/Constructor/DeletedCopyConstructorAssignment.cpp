/*
DELETED COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR - COMPREHENSIVE GUIDE
=====================================================================

WHY DELETE COPY OPERATIONS?
===========================

1. RESOURCE MANAGEMENT: When objects manage unique resources (files, network connections, etc.)
2. PERFORMANCE: Avoid expensive deep copies of large objects
3. CORRECTNESS: Prevent logical errors from accidental copying
4. SINGLETON PATTERN: Ensure only one instance exists
5. THREAD SAFETY: Avoid race conditions from copying shared resources
6. MOVE-ONLY SEMANTICS: Force efficient move operations instead of copies

WHEN TO DELETE COPY OPERATIONS?
==============================

- Classes managing unique resources (RAII)
- Singleton classes
- Classes with expensive copy operations
- Thread-related classes (mutexes, threads)
- Smart pointer implementations
- Stream classes
- Classes representing unique entities (database connections, etc.)

This file demonstrates various scenarios where deleted copy operations are beneficial.
*/

#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

// ============================================================================
// EXAMPLE 1: UNIQUE RESOURCE MANAGEMENT (FILE HANDLE)
// ============================================================================

class FileManager {
private:
    string filename;
    FILE* file_handle;
    
public:
    explicit FileManager(const string& fname) : filename(fname), file_handle(nullptr) {
        file_handle = fopen(filename.c_str(), "w");
        if (file_handle) {
            cout << "FileManager: Opened file '" << filename << "'" << endl;
        } else {
            cout << "FileManager: Failed to open file '" << filename << "'" << endl;
        }
    }
    
    ~FileManager() {
        if (file_handle) {
            fclose(file_handle);
            cout << "FileManager: Closed file '" << filename << "'" << endl;
        }
    }
    
    // DELETE COPY OPERATIONS
    // WHY: File handles are unique resources. Copying would lead to:
    // - Double closing of the same file handle (undefined behavior)
    // - Resource leaks if one copy is destroyed before another
    // - Confusion about which object "owns" the file
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    
    // ALLOW MOVE OPERATIONS (transfer ownership)
    FileManager(FileManager&& other) noexcept 
        : filename(move(other.filename)), file_handle(other.file_handle) {
        other.file_handle = nullptr;  // Transfer ownership
        cout << "FileManager: Moved file '" << filename << "'" << endl;
    }
    
    FileManager& operator=(FileManager&& other) noexcept {
        if (this != &other) {
            // Close current file if open
            if (file_handle) {
                fclose(file_handle);
            }
            
            // Move from other
            filename = move(other.filename);
            file_handle = other.file_handle;
            other.file_handle = nullptr;
            
            cout << "FileManager: Move assigned file '" << filename << "'" << endl;
        }
        return *this;
    }
    
    void writeData(const string& data) {
        if (file_handle) {
            fprintf(file_handle, "%s\n", data.c_str());
            fflush(file_handle);
            cout << "FileManager: Wrote data to '" << filename << "'" << endl;
        }
    }
    
    bool isValid() const { return file_handle != nullptr; }
    const string& getFilename() const { return filename; }
};

// ============================================================================
// EXAMPLE 2: SINGLETON PATTERN
// ============================================================================

class Logger {
private:
    static Logger* instance;
    string log_file;
    
    // Private constructor
    Logger() : log_file("application.log") {
        cout << "Logger: Singleton instance created" << endl;
    }
    
public:
    static Logger& getInstance() {
        if (!instance) {
            instance = new Logger();
        }
        return *instance;
    }
    
    // DELETE COPY OPERATIONS
    // WHY: Singleton pattern requires exactly one instance
    // Copying would violate the singleton principle and create multiple loggers
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    // Also delete move operations for strict singleton
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    
    void log(const string& message) {
        cout << "Logger: [LOG] " << message << endl;
    }
    
    ~Logger() {
        cout << "Logger: Singleton instance destroyed" << endl;
    }
};

Logger* Logger::instance = nullptr;

// ============================================================================
// EXAMPLE 3: EXPENSIVE RESOURCE (LARGE DATA SET)
// ============================================================================

class BigDataProcessor {
private:
    vector<double> massive_dataset;
    string dataset_name;
    
public:
    explicit BigDataProcessor(const string& name, size_t size = 1000000) 
        : dataset_name(name) {
        massive_dataset.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            massive_dataset.push_back(static_cast<double>(i) * 3.14159);
        }
        cout << "BigDataProcessor: Created dataset '" << name 
             << "' with " << size << " elements" << endl;
    }
    
    // DELETE COPY OPERATIONS
    // WHY: Copying large datasets is:
    // - Extremely expensive (time and memory)
    // - Usually unnecessary (most operations can work on original)
    // - Error-prone (accidental copies can cause performance issues)
    BigDataProcessor(const BigDataProcessor&) = delete;
    BigDataProcessor& operator=(const BigDataProcessor&) = delete;
    
    // ALLOW MOVE OPERATIONS for efficient transfers
    BigDataProcessor(BigDataProcessor&& other) noexcept
        : massive_dataset(move(other.massive_dataset)), 
          dataset_name(move(other.dataset_name)) {
        cout << "BigDataProcessor: Moved dataset '" << dataset_name << "'" << endl;
    }
    
    BigDataProcessor& operator=(BigDataProcessor&& other) noexcept {
        if (this != &other) {
            massive_dataset = move(other.massive_dataset);
            dataset_name = move(other.dataset_name);
            cout << "BigDataProcessor: Move assigned dataset '" << dataset_name << "'" << endl;
        }
        return *this;
    }
    
    ~BigDataProcessor() {
        cout << "BigDataProcessor: Destroyed dataset '" << dataset_name 
             << "' with " << massive_dataset.size() << " elements" << endl;
    }
    
    double processData() {
        double sum = 0.0;
        for (const auto& value : massive_dataset) {
            sum += value;
        }
        cout << "BigDataProcessor: Processed '" << dataset_name 
             << "', sum = " << sum << endl;
        return sum;
    }
    
    size_t getSize() const { return massive_dataset.size(); }
    const string& getName() const { return dataset_name; }
};

// ============================================================================
// EXAMPLE 4: NETWORK SOCKET WRAPPER (SIMPLIFIED)
// ============================================================================

class NetworkSocket {
private:
    int socket_fd;
    string host_address;
    bool is_connected;
    
public:
    explicit NetworkSocket(const string& host, int port = 80) 
        : socket_fd(-1), host_address(host), is_connected(false) {
        // Simulate socket creation
        socket_fd = 12345;  // Fake file descriptor
        is_connected = true;
        cout << "NetworkSocket: Connected to " << host << ":" << port 
             << " (fd: " << socket_fd << ")" << endl;
    }
    
    ~NetworkSocket() {
        if (is_connected && socket_fd != -1) {
            cout << "NetworkSocket: Closed connection to " << host_address 
                 << " (fd: " << socket_fd << ")" << endl;
        }
    }
    
    // DELETE COPY OPERATIONS
    // WHY: Network sockets are:
    // - System resources with unique file descriptors
    // - Stateful (connection state, buffers, etc.)
    // - Expensive to establish
    // - Should have clear ownership for proper cleanup
    NetworkSocket(const NetworkSocket&) = delete;
    NetworkSocket& operator=(const NetworkSocket&) = delete;
    
    // ALLOW MOVE OPERATIONS for socket transfer
    NetworkSocket(NetworkSocket&& other) noexcept
        : socket_fd(other.socket_fd),
          host_address(move(other.host_address)),
          is_connected(other.is_connected) {
        // Transfer ownership
        other.socket_fd = -1;
        other.is_connected = false;
        cout << "NetworkSocket: Moved connection to " << host_address << endl;
    }
    
    NetworkSocket& operator=(NetworkSocket&& other) noexcept {
        if (this != &other) {
            // Close current socket
            if (is_connected && socket_fd != -1) {
                cout << "NetworkSocket: Closing current connection" << endl;
            }
            
            // Move from other
            socket_fd = other.socket_fd;
            host_address = move(other.host_address);
            is_connected = other.is_connected;
            
            // Reset other
            other.socket_fd = -1;
            other.is_connected = false;
            
            cout << "NetworkSocket: Move assigned connection to " << host_address << endl;
        }
        return *this;
    }
    
    void sendData(const string& data) {
        if (is_connected) {
            cout << "NetworkSocket: Sent '" << data << "' to " << host_address << endl;
        } else {
            cout << "NetworkSocket: Cannot send - not connected" << endl;
        }
    }
    
    bool isConnected() const { return is_connected; }
    const string& getHost() const { return host_address; }
    int getSocketFd() const { return socket_fd; }
};

// ============================================================================
// EXAMPLE 5: SMART POINTER IMPLEMENTATION
// ============================================================================

template<typename T>
class UniquePtr {
private:
    T* ptr;
    
public:
    explicit UniquePtr(T* p = nullptr) : ptr(p) {
        cout << "UniquePtr: Taking ownership of resource" << endl;
    }
    
    ~UniquePtr() {
        if (ptr) {
            cout << "UniquePtr: Deleting managed resource" << endl;
            delete ptr;
        }
    }
    
    // DELETE COPY OPERATIONS
    // WHY: Unique ownership means:
    // - Only one UniquePtr can own a resource at a time
    // - Copying would create multiple owners (violates uniqueness)
    // - Would lead to double deletion when both copies are destroyed
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    
    // ALLOW MOVE OPERATIONS (transfer ownership)
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
        cout << "UniquePtr: Ownership transferred via move constructor" << endl;
    }
    
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;  // Delete current resource
            ptr = other.ptr;
            other.ptr = nullptr;
            cout << "UniquePtr: Ownership transferred via move assignment" << endl;
        }
        return *this;
    }
    
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }
    
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        cout << "UniquePtr: Ownership released" << endl;
        return temp;
    }
    
    void reset(T* new_ptr = nullptr) {
        delete ptr;
        ptr = new_ptr;
        cout << "UniquePtr: Resource reset" << endl;
    }
    
    explicit operator bool() const { return ptr != nullptr; }
};

// ============================================================================
// EXAMPLE 6: DATABASE CONNECTION (SIMULATION)
// ============================================================================

class DatabaseConnection {
private:
    string connection_string;
    bool is_connected;
    int connection_id;
    static int next_id;
    
public:
    explicit DatabaseConnection(const string& conn_str) 
        : connection_string(conn_str), is_connected(false), connection_id(++next_id) {
        // Simulate connection establishment
        is_connected = true;
        cout << "DatabaseConnection: Established connection #" << connection_id 
             << " to '" << connection_string << "'" << endl;
    }
    
    ~DatabaseConnection() {
        if (is_connected) {
            cout << "DatabaseConnection: Closed connection #" << connection_id << endl;
        }
    }
    
    // DELETE COPY OPERATIONS
    // WHY: Database connections are:
    // - Expensive to establish
    // - Limited in number (connection pools)
    // - Stateful (transactions, cursors, etc.)
    // - Should have clear ownership semantics
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    
    // ALLOW MOVE OPERATIONS for connection pooling
    DatabaseConnection(DatabaseConnection&& other) noexcept
        : connection_string(move(other.connection_string)),
          is_connected(other.is_connected),
          connection_id(other.connection_id) {
        other.is_connected = false;
        cout << "DatabaseConnection: Moved connection #" << connection_id << endl;
    }
    
    DatabaseConnection& operator=(DatabaseConnection&& other) noexcept {
        if (this != &other) {
            // Close current connection
            if (is_connected) {
                cout << "DatabaseConnection: Closing current connection #" << connection_id << endl;
            }
            
            // Move from other
            connection_string = move(other.connection_string);
            is_connected = other.is_connected;
            connection_id = other.connection_id;
            other.is_connected = false;
            
            cout << "DatabaseConnection: Move assigned connection #" << connection_id << endl;
        }
        return *this;
    }
    
    void executeQuery(const string& query) {
        if (is_connected) {
            cout << "DatabaseConnection: Executing query on connection #" 
                 << connection_id << ": " << query << endl;
        } else {
            cout << "DatabaseConnection: Cannot execute query - not connected" << endl;
        }
    }
    
    bool isConnected() const { return is_connected; }
    int getId() const { return connection_id; }
};

int DatabaseConnection::next_id = 0;

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

void demonstrateFileManager() {
    cout << "\n=== FILE MANAGER DEMONSTRATION ===\n";
    
    cout << "\n1. Creating FileManager:\n";
    FileManager fm("test_file.txt");
    fm.writeData("Hello, World!");
    
    cout << "\n2. Move operations (allowed):\n";
    FileManager fm2 = move(fm);
    fm2.writeData("Moved successfully!");
    
    cout << "\n3. Copy operations would cause compilation error:\n";
    cout << "// FileManager fm3 = fm2;  // ERROR: copy constructor deleted\n";
    cout << "// FileManager fm4; fm4 = fm2;  // ERROR: copy assignment deleted\n";
    
    cout << "\n4. FileManager objects will be destroyed automatically:\n";
}

void demonstrateSingleton() {
    cout << "\n=== SINGLETON DEMONSTRATION ===\n";
    
    cout << "\n1. Getting singleton instances:\n";
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();
    
    cout << "Logger1 address: " << &logger1 << endl;
    cout << "Logger2 address: " << &logger2 << endl;
    cout << "Same instance? " << (&logger1 == &logger2 ? "Yes" : "No") << endl;
    
    logger1.log("Message from logger1");
    logger2.log("Message from logger2");
    
    cout << "\n2. Copy operations would cause compilation error:\n";
    cout << "// Logger logger3 = logger1;  // ERROR: copy constructor deleted\n";
    cout << "// Logger logger4; logger4 = logger1;  // ERROR: copy assignment deleted\n";
}

void demonstrateBigDataProcessor() {
    cout << "\n=== BIG DATA PROCESSOR DEMONSTRATION ===\n";
    
    cout << "\n1. Creating large dataset:\n";
    BigDataProcessor processor("dataset1", 10000);  // Smaller for demo
    
    cout << "\n2. Processing data:\n";
    processor.processData();
    
    cout << "\n3. Move operations (efficient):\n";
    BigDataProcessor processor2 = move(processor);
    processor2.processData();
    
    cout << "\n4. Copy operations would cause compilation error:\n";
    cout << "// BigDataProcessor processor3 = processor2;  // ERROR: copy constructor deleted\n";
    cout << "// BigDataProcessor processor4(\"copy\"); processor4 = processor2;  // ERROR: copy assignment deleted\n";
    
    cout << "\n5. Objects will be destroyed automatically:\n";
}

void demonstrateNetworkSocket() {
    cout << "\n=== NETWORK SOCKET DEMONSTRATION ===\n";
    
    cout << "\n1. Creating network socket:\n";
    NetworkSocket socket("example.com", 80);
    
    cout << "\n2. Using the socket:\n";
    socket.sendData("GET / HTTP/1.1");
    socket.sendData("Host: example.com");
    
    cout << "\n3. Move operations (socket transfer):\n";
    NetworkSocket socket2 = move(socket);
    socket2.sendData("Connection transferred");
    
    cout << "\n4. Original socket after move:\n";
    cout << "Original socket connected? " << (socket.isConnected() ? "Yes" : "No") << endl;
    
    cout << "\n5. Copy and move operations would cause compilation error:\n";
    cout << "// NetworkSocket socket3 = socket2;  // ERROR: copy constructor deleted\n";
    cout << "// NetworkSocket socket4(\"host\"); socket4 = socket2;  // ERROR: copy assignment deleted\n";
    
    cout << "\n6. Sockets will be closed automatically:\n";
}

void demonstrateUniquePtr() {
    cout << "\n=== UNIQUE POINTER DEMONSTRATION ===\n";
    
    cout << "\n1. Creating UniquePtr:\n";
    UniquePtr<int> ptr1(new int(42));
    cout << "Value: " << *ptr1 << endl;
    
    cout << "\n2. Move operations (transfer ownership):\n";
    UniquePtr<int> ptr2 = move(ptr1);
    cout << "Value in ptr2: " << *ptr2 << endl;
    cout << "ptr1 is now empty: " << (ptr1.get() == nullptr ? "Yes" : "No") << endl;
    
    cout << "\n3. Copy operations would cause compilation error:\n";
    cout << "// UniquePtr<int> ptr3 = ptr2;  // ERROR: copy constructor deleted\n";
    cout << "// UniquePtr<int> ptr4; ptr4 = ptr2;  // ERROR: copy assignment deleted\n";
    
    cout << "\n4. UniquePtr will automatically delete managed resource:\n";
}

void demonstrateDatabaseConnection() {
    cout << "\n=== DATABASE CONNECTION DEMONSTRATION ===\n";
    
    cout << "\n1. Creating database connection:\n";
    DatabaseConnection db("postgresql://localhost:5432/mydb");
    db.executeQuery("SELECT * FROM users");
    
    cout << "\n2. Move operations (connection transfer):\n";
    DatabaseConnection db2 = move(db);
    db2.executeQuery("SELECT * FROM products");
    
    cout << "\n3. Original connection is now invalid:\n";
    cout << "Original connection still connected? " << (db.isConnected() ? "Yes" : "No") << endl;
    
    cout << "\n4. Copy operations would cause compilation error:\n";
    cout << "// DatabaseConnection db3 = db2;  // ERROR: copy constructor deleted\n";
    cout << "// DatabaseConnection db4(\"another_db\"); db4 = db2;  // ERROR: copy assignment deleted\n";
    
    cout << "\n5. Connections will be closed automatically:\n";
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    cout << "DELETED COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR DEMONSTRATION\n";
    cout << "==============================================================\n";
    
    try {
        demonstrateFileManager();
        demonstrateSingleton();
        demonstrateBigDataProcessor();
        demonstrateNetworkSocket();
        demonstrateUniquePtr();
        demonstrateDatabaseConnection();
        
        cout << "\n=== PROGRAM COMPLETED SUCCESSFULLY ===\n";
        cout << "\nKEY TAKEAWAYS:\n";
        cout << "1. Delete copy operations when objects manage unique resources\n";
        cout << "2. Use move semantics for efficient resource transfer\n";
        cout << "3. Deleted operations prevent accidental expensive copies\n";
        cout << "4. Move-only types force explicit ownership transfer\n";
        cout << "5. Consider the Rule of Five for resource-managing classes\n";
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

/*
COMPILATION AND BEST PRACTICES:
===============================

Compile with:
g++ -std=c++17 -Wall -Wextra -pthread DeletedCopyConstructorAssignment.cpp -o deleted_copy_demo

WHEN TO DELETE COPY OPERATIONS:
==============================

1. RESOURCE MANAGEMENT CLASSES:
   - File handles, network connections
   - Memory managers, custom allocators
   - Thread objects, mutexes

2. UNIQUE OWNERSHIP CLASSES:
   - Smart pointers (unique_ptr style)
   - Singleton patterns
   - Resource handles

3. EXPENSIVE-TO-COPY CLASSES:
   - Large data containers
   - Heavy computational objects
   - Graphics/media resources

4. THREAD-SAFETY CONCERNS:
   - Classes with internal synchronization
   - Objects with shared state
   - Non-copyable standard library objects

BEST PRACTICES:
==============

1. Use "= delete" explicitly rather than private declarations
2. If you delete copy, consider if move should be allowed
3. Document WHY copy operations are deleted
4. Provide alternative methods for sharing if needed
5. Consider the Rule of Five:
   - Destructor
   - Copy constructor (often deleted)
   - Copy assignment (often deleted)  
   - Move constructor (often provided)
   - Move assignment (often provided)

BENEFITS:
========

1. Compile-time error prevention
2. Clear ownership semantics
3. Performance optimization
4. Resource safety
5. Thread safety
6. Cleaner API design
*/
