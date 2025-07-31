// Example demonstrating vtable error and solution
#include <iostream>
#include <string>
#include <memory>

// ============================================================================
// EXAMPLE 1: Interface with vtable error (commented out to avoid compilation error)
// ============================================================================

/*
// This would cause vtable error
class AuthClientBad {
public:
    virtual ~AuthClientBad();  // Declared but not implemented - CAUSES VTABLE ERROR
    virtual void authenticate() = 0;
    virtual void connect();    // Declared but not implemented - CAUSES VTABLE ERROR
};

class ChallengeClientBad : public AuthClientBad {
public:
    void authenticate() override {
        std::cout << "Challenge authentication\n";
    }
    // Missing connect() implementation - CAUSES VTABLE ERROR
};
*/

// ============================================================================
// EXAMPLE 2: Correct implementation without vtable errors
// ============================================================================

namespace application {
    
// Base interface class - properly implemented
class AuthClient {
public:
    // Virtual destructor with implementation
    virtual ~AuthClient() {
        std::cout << "AuthClient destructor called\n";
    }
    
    // Pure virtual functions - no implementation needed
    virtual void authenticate() = 0;
    virtual void challenge(const std::string& data) = 0;
    
    // Virtual function with implementation
    virtual void connect() {
        std::cout << "Base connection established\n";
    }
    
    virtual void disconnect() {
        std::cout << "Base disconnection\n";
    }
    
    // Non-virtual helper function
    void logInfo(const std::string& message) {
        std::cout << "[INFO] " << message << std::endl;
    }
};

// Derived class - all virtual functions properly implemented
class ChallengeClient : public AuthClient {
private:
    std::string clientId;
    bool connected;
    
public:
    explicit ChallengeClient(const std::string& id) 
        : clientId(id), connected(false) {
        logInfo("ChallengeClient created with ID: " + clientId);
    }
    
    // Virtual destructor implementation
    ~ChallengeClient() override {
        if (connected) {
            disconnect();
        }
        std::cout << "ChallengeClient destructor called\n";
    }
    
    // Implementation of pure virtual function
    void authenticate() override {
        logInfo("Starting challenge-based authentication for " + clientId);
        
        // Simulate authentication process
        if (!connected) {
            connect();
        }
        
        std::cout << "Authentication successful for client: " << clientId << std::endl;
    }
    
    // Implementation of pure virtual function
    void challenge(const std::string& data) override {
        logInfo("Processing challenge data: " + data);
        
        // Simulate challenge processing
        std::string response = "CHALLENGE_RESPONSE_" + data + "_" + clientId;
        std::cout << "Challenge response: " << response << std::endl;
    }
    
    // Override virtual function with custom implementation
    void connect() override {
        if (!connected) {
            logInfo("Establishing secure connection for " + clientId);
            connected = true;
            std::cout << "Secure connection established\n";
        } else {
            std::cout << "Already connected\n";
        }
    }
    
    void disconnect() override {
        if (connected) {
            logInfo("Disconnecting client " + clientId);
            connected = false;
            std::cout << "Client disconnected\n";
        }
    }
    
    // Additional specific methods
    bool isConnected() const {
        return connected;
    }
    
    const std::string& getClientId() const {
        return clientId;
    }
};

// Another derived class to demonstrate polymorphism
class TokenClient : public AuthClient {
private:
    std::string token;
    
public:
    explicit TokenClient(const std::string& authToken) 
        : token(authToken) {
        logInfo("TokenClient created");
    }
    
    ~TokenClient() override {
        std::cout << "TokenClient destructor called\n";
    }
    
    void authenticate() override {
        logInfo("Token-based authentication starting");
        std::cout << "Authenticating with token: " << token << std::endl;
    }
    
    void challenge(const std::string& data) override {
        logInfo("Token client doesn't support challenges, ignoring: " + data);
    }
    
    void setToken(const std::string& newToken) {
        token = newToken;
        logInfo("Token updated");
    }
};

} // namespace application

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

void demonstratePolymorphism() {
    std::cout << "\n=== Polymorphism Demonstration ===\n";
    
    // Create different client types
    std::unique_ptr<application::AuthClient> challengeClient = 
        std::make_unique<application::ChallengeClient>("CLIENT_001");
        
    std::unique_ptr<application::AuthClient> tokenClient = 
        std::make_unique<application::TokenClient>("TOKEN_ABC123");
    
    // Store in array for polymorphic calls
    application::AuthClient* clients[] = {
        challengeClient.get(),
        tokenClient.get()
    };
    
    // Demonstrate polymorphic behavior
    for (int i = 0; i < 2; ++i) {
        std::cout << "\n--- Client " << (i + 1) << " ---\n";
        clients[i]->authenticate();
        clients[i]->challenge("TEST_DATA_" + std::to_string(i));
        clients[i]->connect();
        clients[i]->disconnect();
    }
}

void demonstrateVTableConcepts() {
    std::cout << "\n=== VTable Concepts Demonstration ===\n";
    
    application::ChallengeClient specificClient("SPECIFIC_CLIENT");
    application::AuthClient* basePtr = &specificClient;
    
    std::cout << "\nCalling through base pointer (virtual dispatch):\n";
    basePtr->authenticate();  // Calls derived implementation
    basePtr->challenge("VIRTUAL_CALL");  // Calls derived implementation
    
    std::cout << "\nCalling through specific object:\n";
    specificClient.authenticate();  // Direct call
    std::cout << "Client ID: " << specificClient.getClientId() << std::endl;
    std::cout << "Connected: " << (specificClient.isConnected() ? "Yes" : "No") << std::endl;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    std::cout << "VTable Error Resolution Demonstration\n";
    std::cout << "====================================\n";
    
    try {
        // Basic usage
        std::cout << "\n=== Basic Usage ===\n";
        application::ChallengeClient client("DEMO_CLIENT");
        client.authenticate();
        client.challenge("DEMO_CHALLENGE_DATA");
        
        // Polymorphism demonstration
        demonstratePolymorphism();
        
        // VTable concepts
        demonstrateVTableConcepts();
        
        std::cout << "\n=== Program completed successfully ===\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

/*
Expected Output:
================

VTable Error Resolution Demonstration
====================================

=== Basic Usage ===
[INFO] ChallengeClient created with ID: DEMO_CLIENT
[INFO] Starting challenge-based authentication for DEMO_CLIENT
[INFO] Establishing secure connection for DEMO_CLIENT
Secure connection established
Authentication successful for client: DEMO_CLIENT
[INFO] Processing challenge data: DEMO_CHALLENGE_DATA
Challenge response: CHALLENGE_RESPONSE_DEMO_CHALLENGE_DATA_DEMO_CLIENT

=== Polymorphism Demonstration ===
[INFO] ChallengeClient created with ID: CLIENT_001
[INFO] TokenClient created

--- Client 1 ---
[INFO] Starting challenge-based authentication for CLIENT_001
[INFO] Establishing secure connection for CLIENT_001
Secure connection established
Authentication successful for client: CLIENT_001
[INFO] Processing challenge data: TEST_DATA_0
Challenge response: CHALLENGE_RESPONSE_TEST_DATA_0_CLIENT_001
Already connected
[INFO] Disconnecting client CLIENT_001
Client disconnected

--- Client 2 ---
[INFO] Token-based authentication starting
Authenticating with token: TOKEN_ABC123
[INFO] Token client doesn't support challenges, ignoring: TEST_DATA_1
Base connection established
Base disconnection

=== VTable Concepts Demonstration ===
[INFO] ChallengeClient created with ID: SPECIFIC_CLIENT

Calling through base pointer (virtual dispatch):
[INFO] Starting challenge-based authentication for SPECIFIC_CLIENT
[INFO] Establishing secure connection for SPECIFIC_CLIENT
Secure connection established
Authentication successful for client: SPECIFIC_CLIENT
[INFO] Processing challenge data: VIRTUAL_CALL
Challenge response: CHALLENGE_RESPONSE_VIRTUAL_CALL_SPECIFIC_CLIENT

Calling through specific object:
[INFO] Starting challenge-based authentication for SPECIFIC_CLIENT
Already connected
Authentication successful for client: SPECIFIC_CLIENT
Client ID: SPECIFIC_CLIENT
Connected: Yes

=== Program completed successfully ===
[INFO] Disconnecting client SPECIFIC_CLIENT
Client disconnected
ChallengeClient destructor called
AuthClient destructor called
[INFO] Disconnecting client CLIENT_001
Client disconnected
ChallengeClient destructor called
AuthClient destructor called
TokenClient destructor called
AuthClient destructor called
[INFO] Disconnecting client SPECIFIC_CLIENT
Client disconnected
ChallengeClient destructor called
AuthClient destructor called

Compilation:
============
g++ -std=c++17 -Wall -Wextra vtable_demo.cpp -o vtable_demo
./vtable_demo
*/
