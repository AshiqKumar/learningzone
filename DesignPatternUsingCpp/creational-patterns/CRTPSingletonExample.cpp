#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>

/**
 * CRTP (Curiously Recurring Template Pattern) Singleton Base Class
 * 
 * This template class provides a reusable singleton implementation
 * that can be inherited by any class to make it a singleton.
 * 
 * Key Benefits:
 * - Type-safe: Each derived class gets its own singleton instance
 * - Reusable: Single base class for multiple singletons
 * - No virtual function overhead: Compile-time polymorphism
 * - Thread-safe: Uses static local variables (C++11+)
 * - Prevents copying and assignment
 */
template<typename Derived>
class Singleton {
protected:
    // Protected constructor - only derived classes can construct
    Singleton() = default;
    
    // Protected destructor - prevents deletion through base pointer
    ~Singleton() = default;
    
public:
    /**
     * Get the singleton instance of the derived class
     * Thread-safe since C++11 (static local variable initialization)
     */
    static Derived& getInstance() {
        static Derived instance;
        return instance;
    }
    
    // Delete all copy/move operations to prevent multiple instances
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

/**
 * Logger Singleton using CRTP
 * Demonstrates how to create a logging singleton
 */
class Logger : public Singleton<Logger> {
    // Allow the base class to access private members
    friend class Singleton<Logger>;
    
private:
    std::string logLevel;
    std::mutex logMutex;
    
    // Private constructor - prevents direct instantiation
    Logger() : logLevel("INFO") {
        std::cout << "Logger instance created with level: " << logLevel << std::endl;
    }
    
public:
    void setLogLevel(const std::string& level) {
        std::lock_guard<std::mutex> lock(logMutex);
        logLevel = level;
    }
    
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex);
        std::cout << "[" << logLevel << "] " << message << std::endl;
    }
    
    void debug(const std::string& message) {
        if (logLevel == "DEBUG") {
            log("DEBUG: " + message);
        }
    }
    
    void info(const std::string& message) {
        log("INFO: " + message);
    }
    
    void error(const std::string& message) {
        log("ERROR: " + message);
    }
};

/**
 * Configuration Manager Singleton using CRTP
 * Demonstrates managing application configuration
 */
class ConfigManager : public Singleton<ConfigManager> {
    friend class Singleton<ConfigManager>;
    
private:
    std::map<std::string, std::string> config;
    mutable std::mutex configMutex;
    
    ConfigManager() {
        // Initialize with default configuration
        config["app_name"] = "CRTP Singleton Demo";
        config["version"] = "1.0.0";
        config["debug"] = "false";
        
        std::cout << "ConfigManager instance created with default config" << std::endl;
    }
    
public:
    void setConfig(const std::string& key, const std::string& value) {
        std::lock_guard<std::mutex> lock(configMutex);
        config[key] = value;
    }
    
    std::string getConfig(const std::string& key) const {
        std::lock_guard<std::mutex> lock(configMutex);
        auto it = config.find(key);
        return (it != config.end()) ? it->second : "";
    }
    
    void printAllConfig() const {
        std::lock_guard<std::mutex> lock(configMutex);
        std::cout << "\n=== Configuration Settings ===" << std::endl;
        for (const auto& pair : config) {
            std::cout << pair.first << " = " << pair.second << std::endl;
        }
        std::cout << "==============================\n" << std::endl;
    }
    
    bool isDebugEnabled() const {
        return getConfig("debug") == "true";
    }
};

/**
 * Database Connection Pool Singleton using CRTP
 * Demonstrates resource management with singleton
 */
class DatabasePool : public Singleton<DatabasePool> {
    friend class Singleton<DatabasePool>;
    
private:
    std::vector<std::string> connectionPool;
    std::mutex poolMutex;
    size_t maxConnections;
    size_t currentConnections;
    
    DatabasePool() : maxConnections(10), currentConnections(0) {
        // Initialize connection pool
        for (size_t i = 0; i < maxConnections; ++i) {
            connectionPool.push_back("Connection_" + std::to_string(i));
        }
        std::cout << "DatabasePool created with " << maxConnections << " connections" << std::endl;
    }
    
public:
    std::string getConnection() {
        std::lock_guard<std::mutex> lock(poolMutex);
        if (!connectionPool.empty()) {
            std::string conn = connectionPool.back();
            connectionPool.pop_back();
            currentConnections++;
            return conn;
        }
        return ""; // No available connections
    }
    
    void releaseConnection(const std::string& connection) {
        std::lock_guard<std::mutex> lock(poolMutex);
        connectionPool.push_back(connection);
        if (currentConnections > 0) {
            currentConnections--;
        }
    }
    
    size_t getAvailableConnections() const {
        std::lock_guard<std::mutex> lock(poolMutex);
        return connectionPool.size();
    }
    
    size_t getActiveConnections() const {
        std::lock_guard<std::mutex> lock(poolMutex);
        return currentConnections;
    }
};

/**
 * Performance Monitor Singleton using CRTP
 * Demonstrates metrics collection
 */
class PerformanceMonitor : public Singleton<PerformanceMonitor> {
    friend class Singleton<PerformanceMonitor>;
    
private:
    std::map<std::string, double> metrics;
    std::mutex metricsMutex;
    
    PerformanceMonitor() {
        std::cout << "PerformanceMonitor instance created" << std::endl;
    }
    
public:
    void recordMetric(const std::string& name, double value) {
        std::lock_guard<std::mutex> lock(metricsMutex);
        metrics[name] = value;
    }
    
    double getMetric(const std::string& name) const {
        std::lock_guard<std::mutex> lock(metricsMutex);
        auto it = metrics.find(name);
        return (it != metrics.end()) ? it->second : 0.0;
    }
    
    void printMetrics() const {
        std::lock_guard<std::mutex> lock(metricsMutex);
        std::cout << "\n=== Performance Metrics ===" << std::endl;
        for (const auto& metric : metrics) {
            std::cout << metric.first << ": " << metric.second << std::endl;
        }
        std::cout << "===========================\n" << std::endl;
    }
};

/**
 * Function to demonstrate thread safety
 */
void workerThread(int threadId) {
    // Get singleton instances (each type has its own instance)
    Logger& logger = Logger::getInstance();
    ConfigManager& config = ConfigManager::getInstance();
    DatabasePool& dbPool = DatabasePool::getInstance();
    PerformanceMonitor& monitor = PerformanceMonitor::getInstance();
    
    // Use the singletons
    logger.info("Worker thread " + std::to_string(threadId) + " started");
    
    // Get a database connection
    std::string conn = dbPool.getConnection();
    if (!conn.empty()) {
        logger.info("Thread " + std::to_string(threadId) + " got connection: " + conn);
        
        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Record performance metric
        monitor.recordMetric("thread_" + std::to_string(threadId) + "_work_time", 100.0);
        
        // Release connection
        dbPool.releaseConnection(conn);
        logger.info("Thread " + std::to_string(threadId) + " released connection: " + conn);
    } else {
        logger.error("Thread " + std::to_string(threadId) + " could not get database connection");
    }
    
    logger.info("Worker thread " + std::to_string(threadId) + " finished");
}

/**
 * Function to demonstrate CRTP Singleton benefits
 */
void demonstrateCRTPBenefits() {
    std::cout << "\n🚀 CRTP Singleton Pattern Demonstration\n" << std::endl;
    
    // 1. Demonstrate that each singleton type has its own instance
    std::cout << "1. Each singleton type has its own instance:" << std::endl;
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();
    ConfigManager& config1 = ConfigManager::getInstance();
    ConfigManager& config2 = ConfigManager::getInstance();
    
    std::cout << "Logger instances same? " << (&logger1 == &logger2 ? "YES" : "NO") << std::endl;
    std::cout << "Config instances same? " << (&config1 == &config2 ? "YES" : "NO") << std::endl;
    std::cout << "Logger and Config different? " << ((void*)&logger1 != (void*)&config1 ? "YES" : "NO") << std::endl;
    
    // 2. Demonstrate functionality
    std::cout << "\n2. Demonstrate functionality:" << std::endl;
    logger1.setLogLevel("DEBUG");
    logger1.debug("This is a debug message");
    logger1.info("Application starting up");
    
    config1.setConfig("debug", "true");
    config1.setConfig("max_users", "1000");
    config1.printAllConfig();
    
    // 3. Demonstrate database pool
    std::cout << "3. Database connection pool:" << std::endl;
    DatabasePool& dbPool = DatabasePool::getInstance();
    std::cout << "Available connections: " << dbPool.getAvailableConnections() << std::endl;
    
    std::string conn1 = dbPool.getConnection();
    std::string conn2 = dbPool.getConnection();
    std::cout << "After getting 2 connections, available: " << dbPool.getAvailableConnections() << std::endl;
    std::cout << "Active connections: " << dbPool.getActiveConnections() << std::endl;
    
    dbPool.releaseConnection(conn1);
    dbPool.releaseConnection(conn2);
    std::cout << "After releasing connections, available: " << dbPool.getAvailableConnections() << std::endl;
    
    // 4. Demonstrate thread safety
    std::cout << "\n4. Thread safety demonstration:" << std::endl;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(workerThread, i);
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    // 5. Show performance metrics
    std::cout << "\n5. Performance metrics collected:" << std::endl;
    PerformanceMonitor::getInstance().printMetrics();
}

int main() {
    try {
        demonstrateCRTPBenefits();
        
        std::cout << "\n✅ CRTP Singleton demonstration completed successfully!" << std::endl;
        
        // Show the key benefits again
        std::cout << "\n🎯 Key CRTP Singleton Benefits Demonstrated:" << std::endl;
        std::cout << "✅ Type-safe: Each class gets its own singleton instance" << std::endl;
        std::cout << "✅ Reusable: Single base template for multiple singletons" << std::endl;
        std::cout << "✅ No virtual overhead: Compile-time polymorphism" << std::endl;
        std::cout << "✅ Thread-safe: Static local variable initialization" << std::endl;
        std::cout << "✅ Copy prevention: All copy/move operations deleted" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
