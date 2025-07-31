// This file demonstrates the exact vtable error and its solution
// Compile with: g++ -std=c++17 -Wall -Wextra vtable_error_example.cpp -o vtable_error

#include <iostream>
#include <string>
#include <memory>

// ============================================================================
// PART 1: CODE THAT CAUSES VTABLE ERROR (commented out)
// ============================================================================

/*
// This header-only definition would cause vtable error
namespace application {
    class AuthClient {
    public:
        virtual ~AuthClient();  // PROBLEM: Declared but not defined
        virtual void authenticate() = 0;
        virtual void connect();    // PROBLEM: Declared but not defined
    };

    class ChallengeClient : public AuthClient {
    public:
        void authenticate() override {
            std::cout << "Challenge authentication\n";
        }
        // PROBLEM: connect() is inherited but not implemented in base class
        // This would cause: undefined reference to `vtable for application::AuthClient::ChallengeClient'
    };
}

// Trying to use this would cause linker error:
// int main() {
//     application::ChallengeClient client;  // ERROR HERE
//     client.authenticate();
//     return 0;
// }
*/

// ============================================================================
// PART 2: CORRECTED VERSION - NO VTABLE ERRORS
// ============================================================================

namespace application {

// Solution 1: Pure abstract interface (no implementation needed)
class AuthClient {
public:
    // Virtual destructor with default implementation
    virtual ~AuthClient() = default;
    
    // Pure virtual functions - no implementation needed
    virtual void authenticate() = 0;
    virtual void connect() = 0;  // Made pure virtual
    virtual void disconnect() = 0;
};

// Solution 2: All virtual functions properly implemented
class ChallengeClient : public AuthClient {
private:
    std::string clientId;
    bool isConnected;
    
public:
    ChallengeClient() : clientId("default"), isConnected(false) {}
    
    explicit ChallengeClient(const std::string& id) 
        : clientId(id), isConnected(false) {}
    
    // Destructor implementation (can be defaulted)
    ~ChallengeClient() override = default;
    
    // All pure virtual functions must be implemented
    void authenticate() override {
        std::cout << "Challenge-based authentication for: " << clientId << std::endl;
        if (!isConnected) {
            connect();
        }
    }
    
    void connect() override {
        if (!isConnected) {
            std::cout << "Connecting client: " << clientId << std::endl;
            isConnected = true;
        }
    }
    
    void disconnect() override {
        if (isConnected) {
            std::cout << "Disconnecting client: " << clientId << std::endl;
            isConnected = false;
        }
    }
    
    // Additional methods
    bool connected() const { return isConnected; }
    const std::string& getId() const { return clientId; }
};

} // namespace application

// ============================================================================
// PART 3: ALTERNATIVE SOLUTION - CONCRETE BASE CLASS
// ============================================================================

namespace alternative {

// Alternative: Concrete base class with default implementations
class AuthClient {
public:
    virtual ~AuthClient() {
        std::cout << "AuthClient destructor\n";
    }
    
    virtual void authenticate() {
        std::cout << "Default authentication\n";
    }
    
    virtual void connect() {
        std::cout << "Default connection\n";
    }
    
    virtual void disconnect() {
        std::cout << "Default disconnection\n";
    }
};

class ChallengeClient : public AuthClient {
public:
    ~ChallengeClient() override {
        std::cout << "ChallengeClient destructor\n";
    }
    
    void authenticate() override {
        std::cout << "Challenge authentication (overridden)\n";
    }
    
    // connect() and disconnect() use default implementations
    // This is perfectly valid - no vtable error
};

} // namespace alternative

// ============================================================================
// PART 4: TEMPLATE-BASED SOLUTION (NO VTABLES)
// ============================================================================

namespace template_solution {

// CRTP-based solution - no virtual functions, no vtables
template<typename Derived>
class AuthClientCRTP {
public:
    void authenticate() {
        static_cast<Derived*>(this)->doAuthenticate();
    }
    
    void connect() {
        static_cast<Derived*>(this)->doConnect();
    }
    
    void disconnect() {
        static_cast<Derived*>(this)->doDisconnect();
    }
};

class ChallengeClient : public AuthClientCRTP<ChallengeClient> {
public:
    void doAuthenticate() {
        std::cout << "CRTP Challenge authentication\n";
    }
    
    void doConnect() {
        std::cout << "CRTP Challenge connection\n";
    }
    
    void doDisconnect() {
        std::cout << "CRTP Challenge disconnection\n";
    }
};

} // namespace template_solution

// ============================================================================
// MAIN DEMONSTRATION
// ============================================================================

int main() {
    std::cout << "VTable Error Solution Demonstration\n";
    std::cout << "===================================\n\n";
    
    // Test Solution 1: Pure interface
    std::cout << "1. Pure Interface Solution:\n";
    {
        application::ChallengeClient client("CLIENT_001");
        client.authenticate();
        client.connect();
        std::cout << "Connected: " << (client.connected() ? "Yes" : "No") << "\n";
        client.disconnect();
        std::cout << "Connected: " << (client.connected() ? "Yes" : "No") << "\n\n";
    }
    
    // Test Solution 2: Concrete base class
    std::cout << "2. Concrete Base Class Solution:\n";
    {
        alternative::ChallengeClient client;
        client.authenticate();
        client.connect();      // Uses default implementation
        client.disconnect();   // Uses default implementation
        std::cout << "\n";
    }
    
    // Test Solution 3: Template-based (CRTP)
    std::cout << "3. Template-Based Solution (CRTP):\n";
    {
        template_solution::ChallengeClient client;
        client.authenticate();
        client.connect();
        client.disconnect();
        std::cout << "\n";
    }
    
    // Test polymorphism with Solution 1
    std::cout << "4. Polymorphism Test:\n";
    {
        std::unique_ptr<application::AuthClient> client = 
            std::make_unique<application::ChallengeClient>("POLY_CLIENT");
        
        client->authenticate();
        client->connect();
        client->disconnect();
        std::cout << "\n";
    }
    
    std::cout << "All solutions work without vtable errors!\n";
    
    return 0;
}

/*
COMPILATION AND EXPECTED OUTPUT:
===============================

Compilation:
g++ -std=c++17 -Wall -Wextra vtable_error_example.cpp -o vtable_error_example

Expected Output:
VTable Error Solution Demonstration
===================================

1. Pure Interface Solution:
Challenge-based authentication for: CLIENT_001
Connecting client: CLIENT_001
Connected: Yes
Disconnecting client: CLIENT_001
Connected: No

2. Concrete Base Class Solution:
Challenge authentication (overridden)
Default connection
Default disconnection
ChallengeClient destructor
AuthClient destructor

3. Template-Based Solution (CRTP):
CRTP Challenge authentication
CRTP Challenge connection
CRTP Challenge disconnection

4. Polymorphism Test:
Challenge-based authentication for: POLY_CLIENT
Connecting client: POLY_CLIENT
Disconnecting client: POLY_CLIENT

All solutions work without vtable errors!

KEY POINTS FOR FIXING YOUR ERROR:
================================

1. If you see "undefined reference to vtable for application::AuthClient::ChallengeClient",
   it means one of these issues:
   
   a) Virtual destructor declared but not implemented
   b) Virtual function declared in base class but not implemented
   c) Pure virtual function in base class not overridden in derived class
   d) Implementation file not being compiled/linked

2. Quick fixes:
   - Make sure all virtual functions are either pure virtual (= 0) or implemented
   - Implement virtual destructor: virtual ~ClassName() = default;
   - Check that .cpp files are being compiled and linked
   - Use nm or objdump to check for missing symbols

3. Best practices:
   - Use pure virtual functions for true interfaces
   - Always implement virtual destructors
   - Use override keyword to catch signature mismatches
   - Consider CRTP for performance-critical code without inheritance needs
*/
