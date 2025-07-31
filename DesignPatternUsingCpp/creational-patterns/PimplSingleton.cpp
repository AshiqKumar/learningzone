// PimplSingleton.cpp
#include "PimplSingleton.h"
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

// =============================================================================
// DatabaseManager Implementation
// =============================================================================

class DatabaseManager::Impl {
public:
    std::string connectionString;
    bool connected;
    std::vector<std::string> queryHistory;
    std::string lastResult;
    int maxConnections;
    int currentConnections;
    bool loggingEnabled;
    std::vector<std::string> connectionPool;
    std::map<std::string, std::string> metadata;
    
    Impl() : connected(false), maxConnections(10), currentConnections(0), loggingEnabled(false) {
        std::cout << "DatabaseManager::Impl created" << std::endl;
        metadata["created"] = getCurrentTimestamp();
        metadata["version"] = "1.0.0";
        
        // Initialize connection pool
        for (int i = 0; i < maxConnections; ++i) {
            connectionPool.push_back("connection_" + std::to_string(i));
        }
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
        currentConnections = 1;
        lastResult = "Connected successfully";
        
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
        currentConnections = 0;
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
        lastResult = "Query executed: " + query + " [Result: 42 rows affected]";
        
        if (loggingEnabled) {
            std::cout << "Executed query: " << query << std::endl;
        }
    }
    
    std::string getStatistics() const {
        std::ostringstream stats;
        stats << "=== Database Statistics ===\n";
        stats << "Connected: " << (connected ? "Yes" : "No") << "\n";
        stats << "Connection String: " << connectionString << "\n";
        stats << "Current Connections: " << currentConnections << "\n";
        stats << "Max Connections: " << maxConnections << "\n";
        stats << "Queries Executed: " << queryHistory.size() << "\n";
        stats << "Logging Enabled: " << (loggingEnabled ? "Yes" : "No") << "\n";
        stats << "Created: " << metadata.at("created") << "\n";
        stats << "Version: " << metadata.at("version") << "\n";
        stats << "========================";
        return stats.str();
    }
    
private:
    std::string getCurrentTimestamp() const {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
};

// DatabaseManager public interface implementation
DatabaseManager::DatabaseManager() : pImpl(std::make_unique<Impl>()) {}
DatabaseManager::~DatabaseManager() = default;

DatabaseManager& DatabaseManager::getInstance() {
    static DatabaseManager instance;  // Thread-safe since C++11
    return instance;
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

void DatabaseManager::setMaxConnections(int max) {
    pImpl->maxConnections = max;
}

int DatabaseManager::getCurrentConnections() const {
    return pImpl->currentConnections;
}

void DatabaseManager::enableLogging(bool enable) {
    pImpl->loggingEnabled = enable;
}

std::string DatabaseManager::getStatistics() const {
    return pImpl->getStatistics();
}

// =============================================================================
// ConfigurationManager Implementation
// =============================================================================

class ConfigurationManager::Impl {
public:
    std::map<std::string, std::string> configs;
    std::string currentFile;
    bool isDirty;
    std::vector<std::string> accessHistory;
    
    Impl() : isDirty(false) {
        std::cout << "ConfigurationManager::Impl created" << std::endl;
        setDefaults();
    }
    
    ~Impl() {
        std::cout << "ConfigurationManager::Impl destroyed" << std::endl;
    }
    
    void setDefaults() {
        configs["app_name"] = "Pimpl Singleton Demo";
        configs["version"] = "1.0.0";
        configs["debug"] = "false";
        configs["max_users"] = "100";
        configs["timeout"] = "30";
        configs["log_level"] = "INFO";
        isDirty = false;
    }
    
    void loadFromFile(const std::string& filename) {
        currentFile = filename;
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            std::cout << "Warning: Could not open config file: " << filename << std::endl;
            return;
        }
        
        configs.clear();
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                configs[key] = value;
            }
        }
        
        isDirty = false;
        std::cout << "Loaded " << configs.size() << " configurations from " << filename << std::endl;
    }
    
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            std::cout << "Error: Could not save config file: " << filename << std::endl;
            return;
        }
        
        for (const auto& pair : configs) {
            file << pair.first << "=" << pair.second << "\n";
        }
        
        std::cout << "Saved " << configs.size() << " configurations to " << filename << std::endl;
    }
    
    void setConfig(const std::string& key, const std::string& value) {
        configs[key] = value;
        accessHistory.push_back("SET: " + key + " = " + value);
        isDirty = true;
    }
    
    std::string getConfig(const std::string& key) const {
        auto it = configs.find(key);
        if (it != configs.end()) {
            accessHistory.push_back("GET: " + key);
            return it->second;
        }
        return "";
    }
    
    void printAllConfigs() const {
        std::cout << "\n=== Configuration Settings ===" << std::endl;
        for (const auto& pair : configs) {
            std::cout << pair.first << " = " << pair.second << std::endl;
        }
        std::cout << "Total configs: " << configs.size() << std::endl;
        std::cout << "Dirty: " << (isDirty ? "Yes" : "No") << std::endl;
        std::cout << "Current file: " << currentFile << std::endl;
        std::cout << "==============================\n" << std::endl;
    }
    
private:
    mutable std::vector<std::string> accessHistory;  // mutable for const methods
};

// ConfigurationManager public interface implementation
ConfigurationManager::ConfigurationManager() : pImpl(std::make_unique<Impl>()) {}
ConfigurationManager::~ConfigurationManager() = default;

ConfigurationManager& ConfigurationManager::getInstance() {
    static ConfigurationManager instance;
    return instance;
}

void ConfigurationManager::loadFromFile(const std::string& filename) {
    pImpl->loadFromFile(filename);
}

void ConfigurationManager::saveToFile(const std::string& filename) const {
    pImpl->saveToFile(filename);
}

void ConfigurationManager::setConfig(const std::string& key, const std::string& value) {
    pImpl->setConfig(key, value);
}

std::string ConfigurationManager::getConfig(const std::string& key) const {
    return pImpl->getConfig(key);
}

bool ConfigurationManager::hasConfig(const std::string& key) const {
    return pImpl->configs.find(key) != pImpl->configs.end();
}

void ConfigurationManager::removeConfig(const std::string& key) {
    pImpl->configs.erase(key);
    pImpl->isDirty = true;
}

void ConfigurationManager::setDefaults() {
    pImpl->setDefaults();
}

void ConfigurationManager::printAllConfigs() const {
    pImpl->printAllConfigs();
}

// =============================================================================
// LogManager Implementation
// =============================================================================

class LogManager::Impl {
public:
    std::string logLevel;
    std::string logFile;
    bool consoleLogging;
    std::vector<std::string> logBuffer;
    std::map<std::string, int> logCounts;
    std::ofstream fileStream;
    
    Impl() : logLevel("INFO"), consoleLogging(true) {
        std::cout << "LogManager::Impl created" << std::endl;
        logCounts["DEBUG"] = 0;
        logCounts["INFO"] = 0;
        logCounts["WARNING"] = 0;
        logCounts["ERROR"] = 0;
    }
    
    ~Impl() {
        if (fileStream.is_open()) {
            fileStream.close();
        }
        std::cout << "LogManager::Impl destroyed" << std::endl;
    }
    
    void setLogFile(const std::string& filename) {
        if (fileStream.is_open()) {
            fileStream.close();
        }
        
        logFile = filename;
        fileStream.open(filename, std::ios::app);
        
        if (fileStream.is_open()) {
            std::cout << "Log file set to: " << filename << std::endl;
        } else {
            std::cout << "Error: Could not open log file: " << filename << std::endl;
        }
    }
    
    void log(const std::string& level, const std::string& message) {
        std::string logEntry = getCurrentTimestamp() + " [" + level + "] " + message;
        
        logBuffer.push_back(logEntry);
        logCounts[level]++;
        
        if (consoleLogging) {
            std::cout << logEntry << std::endl;
        }
        
        if (fileStream.is_open()) {
            fileStream << logEntry << std::endl;
        }
    }
    
    bool shouldLog(const std::string& level) const {
        if (logLevel == "DEBUG") return true;
        if (logLevel == "INFO" && level != "DEBUG") return true;
        if (logLevel == "WARNING" && (level == "WARNING" || level == "ERROR")) return true;
        if (logLevel == "ERROR" && level == "ERROR") return true;
        return false;
    }
    
    void flush() {
        if (fileStream.is_open()) {
            fileStream.flush();
        }
    }
    
    std::string getLogStats() const {
        std::ostringstream stats;
        stats << "=== Log Statistics ===\n";
        stats << "Log Level: " << logLevel << "\n";
        stats << "Log File: " << logFile << "\n";
        stats << "Console Logging: " << (consoleLogging ? "Enabled" : "Disabled") << "\n";
        stats << "Total Log Entries: " << logBuffer.size() << "\n";
        for (const auto& pair : logCounts) {
            stats << pair.first << " Count: " << pair.second << "\n";
        }
        stats << "====================";
        return stats.str();
    }
    
private:
    std::string getCurrentTimestamp() const {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
};

// LogManager public interface implementation
LogManager::LogManager() : pImpl(std::make_unique<Impl>()) {}
LogManager::~LogManager() = default;

LogManager& LogManager::getInstance() {
    static LogManager instance;
    return instance;
}

void LogManager::setLogLevel(const std::string& level) {
    pImpl->logLevel = level;
}

void LogManager::setLogFile(const std::string& filename) {
    pImpl->setLogFile(filename);
}

void LogManager::enableConsoleLogging(bool enable) {
    pImpl->consoleLogging = enable;
}

void LogManager::log(const std::string& level, const std::string& message) {
    if (pImpl->shouldLog(level)) {
        pImpl->log(level, message);
    }
}

void LogManager::debug(const std::string& message) {
    log("DEBUG", message);
}

void LogManager::info(const std::string& message) {
    log("INFO", message);
}

void LogManager::warning(const std::string& message) {
    log("WARNING", message);
}

void LogManager::error(const std::string& message) {
    log("ERROR", message);
}

void LogManager::flush() {
    pImpl->flush();
}

std::string LogManager::getLogStats() const {
    return pImpl->getLogStats();
}
