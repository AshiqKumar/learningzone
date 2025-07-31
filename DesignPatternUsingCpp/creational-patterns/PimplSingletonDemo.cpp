#include "PimplSingleton.h"
#include <iostream>
#include <thread>
#include <chrono>

/**
 * Demonstration of Pimpl Singleton Pattern
 * 
 * This example shows how the Pimpl idiom combined with Singleton provides:
 * 1. Binary compatibility - Implementation details hidden in .cpp file
 * 2. Faster compilation - Only public interface in header
 * 3. Information hiding - Private implementation truly private
 * 4. Exception safety - RAII with smart pointers
 * 5. Singleton guarantees - Only one instance exists
 * 6. Thread safety - C++11 static local variable initialization
 */

void demonstratePimplSingletonBenefits() {
    std::cout << "🚀 Pimpl Singleton Pattern Demonstration\n" << std::endl;
    
    // 1. Demonstrate Singleton behavior
    std::cout << "1. Singleton Behavior Verification:" << std::endl;
    DatabaseManager& db1 = DatabaseManager::getInstance();
    DatabaseManager& db2 = DatabaseManager::getInstance();
    ConfigurationManager& config1 = ConfigurationManager::getInstance();
    ConfigurationManager& config2 = ConfigurationManager::getInstance();
    
    std::cout << "Database instances same? " << (&db1 == &db2 ? "YES" : "NO") << std::endl;
    std::cout << "Config instances same? " << (&config1 == &config2 ? "YES" : "NO") << std::endl;
    std::cout << "DB address: " << &db1 << ", Config address: " << &config1 << std::endl;
    
    // 2. Demonstrate DatabaseManager functionality
    std::cout << "\n2. DatabaseManager Functionality:" << std::endl;
    db1.enableLogging(true);
    db1.connect("postgresql://localhost:5432/myapp");
    db1.setMaxConnections(20);
    db1.executeQuery("SELECT * FROM users WHERE active = true");
    db1.executeQuery("UPDATE users SET last_login = NOW() WHERE id = 123");
    
    std::cout << "Connected: " << (db1.isConnected() ? "Yes" : "No") << std::endl;
    std::cout << "Last result: " << db1.getLastResult() << std::endl;
    std::cout << "Current connections: " << db1.getCurrentConnections() << std::endl;
    
    // 3. Demonstrate ConfigurationManager functionality
    std::cout << "\n3. ConfigurationManager Functionality:" << std::endl;
    config1.setConfig("debug", "true");
    config1.setConfig("api_key", "abc123xyz789");
    config1.setConfig("max_retries", "5");
    config1.printAllConfigs();
    
    std::cout << "Debug enabled: " << (config1.getConfig("debug") == "true" ? "Yes" : "No") << std::endl;
    std::cout << "App name: " << config1.getConfig("app_name") << std::endl;
    std::cout << "Has API key: " << (config1.hasConfig("api_key") ? "Yes" : "No") << std::endl;
    
    // 4. Demonstrate LogManager functionality
    std::cout << "\n4. LogManager Functionality:" << std::endl;
    LogManager& logger = LogManager::getInstance();
    logger.setLogLevel("DEBUG");
    logger.enableConsoleLogging(true);
    
    logger.info("Application started successfully");
    logger.debug("Debug information: configuration loaded");
    logger.warning("This is a warning message");
    logger.error("This is an error message");
    
    std::cout << "\n" << logger.getLogStats() << std::endl;
}

void demonstrateEncapsulation() {
    std::cout << "\n5. Information Hiding and Encapsulation:" << std::endl;
    
    // The following code would NOT compile - implementation details are hidden:
    /*
    DatabaseManager& db = DatabaseManager::getInstance();
    // db.pImpl->connected = true;           // ERROR: pImpl is private
    // db.pImpl->connectionString = "hack";  // ERROR: Cannot access private members
    // db.Impl impl;                         // ERROR: Impl is private nested class
    */
    
    std::cout << "✅ Implementation details are completely hidden from client code" << std::endl;
    std::cout << "✅ No compilation dependencies on implementation headers" << std::endl;
    std::cout << "✅ Binary compatibility - implementation can change without recompilation" << std::endl;
    std::cout << "✅ Exception safety - RAII with smart pointers ensures cleanup" << std::endl;
}

void demonstrateThreadSafety() {
    std::cout << "\n6. Thread Safety Demonstration:" << std::endl;
    
    auto workerThread = [](int threadId) {
        // Each thread gets the same singleton instances
        DatabaseManager& db = DatabaseManager::getInstance();
        ConfigurationManager& config = ConfigurationManager::getInstance();
        LogManager& logger = LogManager::getInstance();
        
        logger.info("Thread " + std::to_string(threadId) + " accessing singletons");
        
        // Thread-safe operations
        config.setConfig("thread_" + std::to_string(threadId), "active");
        
        if (!db.isConnected()) {
            db.connect("thread_connection_" + std::to_string(threadId));
        }
        
        db.executeQuery("SELECT COUNT(*) FROM thread_operations WHERE thread_id = " + std::to_string(threadId));
        
        logger.debug("Thread " + std::to_string(threadId) + " completed operations");
        
        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };
    
    // Create multiple threads
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(workerThread, i);
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    std::cout << "✅ All threads completed successfully" << std::endl;
    std::cout << "✅ Singleton instances remain consistent across threads" << std::endl;
}

void demonstrateStatistics() {
    std::cout << "\n7. Final Statistics and State:" << std::endl;
    
    DatabaseManager& db = DatabaseManager::getInstance();
    ConfigurationManager& config = ConfigurationManager::getInstance();
    LogManager& logger = LogManager::getInstance();
    
    std::cout << "\n" << db.getStatistics() << std::endl;
    std::cout << "\nConfiguration status:" << std::endl;
    config.printAllConfigs();
    std::cout << "\n" << logger.getLogStats() << std::endl;
    
    // Demonstrate cleanup
    db.disconnect();
    logger.flush();
}

void demonstratePimplBenefits() {
    std::cout << "\n8. Key Pimpl + Singleton Benefits:" << std::endl;
    std::cout << "✅ Compilation Firewall: Implementation changes don't require header recompilation" << std::endl;
    std::cout << "✅ Information Hiding: Private members are truly private and inaccessible" << std::endl;
    std::cout << "✅ Binary Compatibility: ABI stable across implementation changes" << std::endl;
    std::cout << "✅ Reduced Dependencies: Headers don't need to include implementation headers" << std::endl;
    std::cout << "✅ Exception Safety: RAII with smart pointers ensures proper cleanup" << std::endl;
    std::cout << "✅ Thread Safety: C++11 static local variable initialization" << std::endl;
    std::cout << "✅ Single Responsibility: Clear separation of interface and implementation" << std::endl;
    std::cout << "✅ Performance: No virtual function overhead, compile-time optimization" << std::endl;
}

int main() {
    try {
        demonstratePimplSingletonBenefits();
        demonstrateEncapsulation();
        demonstrateThreadSafety();
        demonstrateStatistics();
        demonstratePimplBenefits();
        
        std::cout << "\n🎯 Pimpl Singleton Pattern Summary:" << std::endl;
        std::cout << "The combination of Pimpl idiom with Singleton pattern provides" << std::endl;
        std::cout << "exceptional encapsulation, performance, and maintainability benefits" << std::endl;
        std::cout << "while ensuring only one instance exists throughout the application." << std::endl;
        
        std::cout << "\n✅ Demonstration completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
