// PimplSingleton.h
#ifndef PIMPL_SINGLETON_H
#define PIMPL_SINGLETON_H

#include <memory>
#include <string>

/**
 * Pimpl Singleton Pattern Implementation
 * 
 * The Pimpl (Pointer to Implementation) idiom combined with Singleton
 * provides several benefits:
 * 1. Binary compatibility - Implementation changes don't require recompilation
 * 2. Faster compilation - Reduced header dependencies
 * 3. Information hiding - Private members truly hidden
 * 4. Exception safety - RAII with smart pointers
 * 5. Singleton guarantees - Only one instance exists
 */

class DatabaseManager {
private:
    // Forward declaration - implementation details hidden
    class Impl;
    
    // Smart pointer to implementation - ensures proper cleanup
    std::unique_ptr<Impl> pImpl;
    
    // Private constructor for Singleton pattern
    DatabaseManager();
    
    // Private destructor - declared in header, defined in .cpp
    ~DatabaseManager();
    
public:
    // Singleton access method
    static DatabaseManager& getInstance();
    
    // Public interface methods - implementation delegated to pImpl
    void connect(const std::string& connectionString);
    void disconnect();
    bool isConnected() const;
    void executeQuery(const std::string& query);
    std::string getLastResult() const;
    void setMaxConnections(int max);
    int getCurrentConnections() const;
    void enableLogging(bool enable);
    std::string getStatistics() const;
    
    // Prevent copying and assignment
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    
    // Prevent moving (for this singleton example)
    DatabaseManager(DatabaseManager&&) = delete;
    DatabaseManager& operator=(DatabaseManager&&) = delete;
};

class ConfigurationManager {
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
    
    ConfigurationManager();
    ~ConfigurationManager();
    
public:
    static ConfigurationManager& getInstance();
    
    // Configuration interface
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    void setConfig(const std::string& key, const std::string& value);
    std::string getConfig(const std::string& key) const;
    bool hasConfig(const std::string& key) const;
    void removeConfig(const std::string& key);
    void setDefaults();
    void printAllConfigs() const;
    
    // Prevent copying
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;
    ConfigurationManager(ConfigurationManager&&) = delete;
    ConfigurationManager& operator=(ConfigurationManager&&) = delete;
};

class LogManager {
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
    
    LogManager();
    ~LogManager();
    
public:
    static LogManager& getInstance();
    
    // Logging interface
    void setLogLevel(const std::string& level);
    void setLogFile(const std::string& filename);
    void enableConsoleLogging(bool enable);
    void log(const std::string& level, const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void flush();
    std::string getLogStats() const;
    
    // Prevent copying
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;
    LogManager(LogManager&&) = delete;
    LogManager& operator=(LogManager&&) = delete;
};

#endif // PIMPL_SINGLETON_H
