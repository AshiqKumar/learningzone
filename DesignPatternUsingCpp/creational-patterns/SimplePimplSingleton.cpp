// SimplePimplSingleton.cpp
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>

/**
 * Simple Pimpl Singleton Pattern Implementation
 * 
 * This demonstrates the Pimpl idiom combined with Singleton pattern
 * using C++11 features for better compatibility.
 */

// =============================================================================
// DatabaseManager with Pimpl + Singleton
// =============================================================================

class DatabaseManager {
private:
    // Forward declaration of implementation
    struct Impl;
    
    // Pointer to implementation (using C++11 compatible approach)
    std::unique_ptr<Impl> pImpl;
    
    // Private constructor for Singleton
    DatabaseManager();
    
public:
    // Destructor (must be defined in .cpp where Impl is complete)
    ~DatabaseManager();
    
    // Singleton access
    static DatabaseManager& getInstance() {
        static DatabaseManager instance;  // Thread-safe since C++11
        return instance;
    }
    
    // Public interface methods
    void connect(const std::string& connectionString);
    void disconnect();
    bool isConnected() const;
    void executeQuery(const std::string& query);
    std::string getLastResult() const;
    void enableLogging(bool enable);
    std::string getStatistics() const;
    
    // Prevent copying
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
};

// Implementation structure (hidden from header users)
struct DatabaseManager::Impl {
    std::string connectionString;
    bool connected;
    std::vector<std::string> queryHistory;
    std::string lastResult;
    bool loggingEnabled;
    
    Impl() : connected(false), loggingEnabled(false) {
        std::cout << "DatabaseManager::Impl created" << std::endl;
    }
    
    ~Impl() {
        if (connected) {
            disconnect();
        }
        std::cout << "DatabaseManager::Impl destroyed" << std::endl;
    }
    
    void connect(const std::string& connStr) {
        if (connected) {
            std::cout << "Already connected to database" << std::endl;
            return;
        }
        
        connectionString = connStr;
        connected = true;
        lastResult = "Connected successfully to " + connStr;
        
        if (loggingEnabled) {
            std::cout << "Connected to database: " << connStr << std::endl;
        }
    }
    
    void disconnect() {
        if (!connected) {
            std::cout << "Not connected to database" << std::endl;
            return;
        }
        
        connected = false;
        lastResult = "Disconnected successfully";
        
        if (loggingEnabled) {
            std::cout << "Disconnected from database" << std::endl;
        }
    }
    
    void executeQuery(const std::string& query) {
        if (!connected) {
            lastResult = "Error: Not connected to database";
            return;
        }
        
        queryHistory.push_back(query);
        lastResult = "Query executed: " + query + " [42 rows affected]";
        
        if (loggingEnabled) {
            std::cout << "Executed query: " << query << std::endl;
        }
    }
    
    std::string getStatistics() const {
        std::string stats = "=== Database Statistics ===\n";
        stats += "Connected: " + std::string(connected ? "Yes" : "No") + "\n";
        stats += "Connection String: " + connectionString + "\n";
        stats += "Queries Executed: " + std::to_string(queryHistory.size()) + "\n";
        stats += "Logging Enabled: " + std::string(loggingEnabled ? "Yes" : "No") + "\n";
        stats += "========================";
        return stats;
    }
};

// DatabaseManager implementation
DatabaseManager::DatabaseManager() {
    // Use reset() instead of make_unique for C++11 compatibility
    pImpl.reset(new Impl());
}

DatabaseManager::~DatabaseManager() {
    // Destructor automatically calls pImpl destructor
}

void DatabaseManager::connect(const std::string& connectionString) {
    pImpl->connect(connectionString);
}

void DatabaseManager::disconnect() {
    pImpl->disconnect();
}

bool DatabaseManager::isConnected() const {
    return pImpl->connected;
}

void DatabaseManager::executeQuery(const std::string& query) {
    pImpl->executeQuery(query);
}

std::string DatabaseManager::getLastResult() const {
    return pImpl->lastResult;
}

void DatabaseManager::enableLogging(bool enable) {
    pImpl->loggingEnabled = enable;
}

std::string DatabaseManager::getStatistics() const {
    return pImpl->getStatistics();
}

// =============================================================================
// ConfigManager with Pimpl + Singleton
// =============================================================================

class ConfigManager {
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
    ConfigManager();
    
public:
    ~ConfigManager();
    
    static ConfigManager& getInstance() {
        static ConfigManager instance;
        return instance;
    }
    
    void setConfig(const std::string& key, const std::string& value);
    std::string getConfig(const std::string& key) const;
    bool hasConfig(const std::string& key) const;
    void printAllConfigs() const;
    void setDefaults();
    
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
};

struct ConfigManager::Impl {
    std::map<std::string, std::string> configs;
    
    Impl() {
        std::cout << "ConfigManager::Impl created" << std::endl;
        setDefaults();
    }
    
    ~Impl() {
        std::cout << "ConfigManager::Impl destroyed" << std::endl;
    }
    
    void setDefaults() {
        configs["app_name"] = "Pimpl Singleton Demo";
        configs["version"] = "1.0.0";
        configs["debug"] = "false";
        configs["max_users"] = "100";
    }
    
    void printAllConfigs() const {
        std::cout << "\n=== Configuration Settings ===" << std::endl;
        for (std::map<std::string, std::string>::const_iterator it = configs.begin(); 
             it != configs.end(); ++it) {
            std::cout << it->first << " = " << it->second << std::endl;
        }
        std::cout << "Total configs: " << configs.size() << std::endl;
        std::cout << "==============================\n" << std::endl;
    }
};

ConfigManager::ConfigManager() {
    pImpl.reset(new Impl());
}

ConfigManager::~ConfigManager() {
    // Auto-cleanup via unique_ptr
}

void ConfigManager::setConfig(const std::string& key, const std::string& value) {
    pImpl->configs[key] = value;
}

std::string ConfigManager::getConfig(const std::string& key) const {
    std::map<std::string, std::string>::const_iterator it = pImpl->configs.find(key);
    return (it != pImpl->configs.end()) ? it->second : "";
}

bool ConfigManager::hasConfig(const std::string& key) const {
    return pImpl->configs.find(key) != pImpl->configs.end();
}

void ConfigManager::printAllConfigs() const {
    pImpl->printAllConfigs();
}

void ConfigManager::setDefaults() {
    pImpl->setDefaults();
}

// =============================================================================
// Demonstration Functions
// =============================================================================

void demonstratePimplSingleton() {
    std::cout << "🚀 Pimpl + Singleton Pattern Demonstration\n" << std::endl;
    
    // 1. Demonstrate Singleton behavior
    std::cout << "1. Singleton Behavior:" << std::endl;
    DatabaseManager& db1 = DatabaseManager::getInstance();
    DatabaseManager& db2 = DatabaseManager::getInstance();
    ConfigManager& config1 = ConfigManager::getInstance();
    ConfigManager& config2 = ConfigManager::getInstance();
    
    std::cout << "Database instances same? " << (&db1 == &db2 ? "YES" : "NO") << std::endl;
    std::cout << "Config instances same? " << (&config1 == &config2 ? "YES" : "NO") << std::endl;
    
    // 2. Demonstrate DatabaseManager
    std::cout << "\n2. DatabaseManager Functionality:" << std::endl;
    db1.enableLogging(true);
    db1.connect("postgresql://localhost:5432/myapp");
    db1.executeQuery("SELECT * FROM users WHERE active = true");
    db1.executeQuery("UPDATE users SET last_login = NOW()");
    
    std::cout << "Connected: " << (db1.isConnected() ? "Yes" : "No") << std::endl;
    std::cout << "Last result: " << db1.getLastResult() << std::endl;
    
    // 3. Demonstrate ConfigManager
    std::cout << "\n3. ConfigManager Functionality:" << std::endl;
    config1.setConfig("debug", "true");
    config1.setConfig("api_key", "secret123");
    config1.setConfig("timeout", "30");
    config1.printAllConfigs();
    
    std::cout << "Debug enabled: " << (config1.getConfig("debug") == "true" ? "Yes" : "No") << std::endl;
    std::cout << "App name: " << config1.getConfig("app_name") << std::endl;
    
    // 4. Show statistics
    std::cout << "\n4. Database Statistics:" << std::endl;
    std::cout << db1.getStatistics() << std::endl;
    
    // 5. Cleanup
    std::cout << "\n5. Cleanup:" << std::endl;
    db1.disconnect();
}

void demonstratePimplBenefits() {
    std::cout << "\n🎯 Pimpl + Singleton Benefits:" << std::endl;
    std::cout << "✅ Information Hiding: Implementation details completely hidden" << std::endl;
    std::cout << "✅ Binary Compatibility: ABI stable across implementation changes" << std::endl;
    std::cout << "✅ Faster Compilation: Reduced header dependencies" << std::endl;
    std::cout << "✅ Exception Safety: RAII with smart pointers" << std::endl;
    std::cout << "✅ Thread Safety: C++11 static local variable initialization" << std::endl;
    std::cout << "✅ Single Instance: Singleton guarantees only one instance" << std::endl;
    std::cout << "✅ Copy Prevention: Deleted copy constructors and assignment" << std::endl;
    
    std::cout << "\n📚 Key Concepts:" << std::endl;
    std::cout << "• Forward Declaration: 'struct Impl;' hides implementation details" << std::endl;
    std::cout << "• Unique Pointer: RAII ensures automatic cleanup" << std::endl;
    std::cout << "• Static Local: Thread-safe singleton instance creation" << std::endl;
    std::cout << "• Deleted Functions: Prevents copying and assignment" << std::endl;
}

int main() {
    try {
        demonstratePimplSingleton();
        demonstratePimplBenefits();
        
        std::cout << "\n✅ Pimpl Singleton demonstration completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
