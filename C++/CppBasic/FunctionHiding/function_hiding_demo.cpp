// function_hiding_demo.cpp - Demonstrates Function Hiding in C++
// Compile: g++ -std=c++17 -Wall -Wextra function_hiding_demo.cpp -o function_hiding

#include <iostream>
#include <string>
#include <memory>
#include <vector>

// 1. Basic Function Hiding Example
class Base {
public:
    // Non-virtual functions
    void display() {
        std::cout << "Base::display() called" << std::endl;
    }
    
    void show(int x) {
        std::cout << "Base::show(int): " << x << std::endl;
    }
    
    void show(double x) {
        std::cout << "Base::show(double): " << x << std::endl;
    }
    
    void show(const std::string& s) {
        std::cout << "Base::show(string): " << s << std::endl;
    }
    
    // Virtual function for comparison
    virtual void virtualFunc() {
        std::cout << "Base::virtualFunc() called" << std::endl;
    }
    
    void processData() {
        std::cout << "Base::processData() - basic processing" << std::endl;
    }
    
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    // Function hiding - hides ALL overloads of Base::show()
    void show(char c) {
        std::cout << "Derived::show(char): " << c << std::endl;
    }
    
    // Function hiding - hides Base::display()
    void display() {
        std::cout << "Derived::display() called" << std::endl;
    }
    
    // Virtual function override (not hiding)
    void virtualFunc() override {
        std::cout << "Derived::virtualFunc() called" << std::endl;
    }
    
    // Function hiding with different signature
    void processData(int level) {
        std::cout << "Derived::processData(int) - advanced processing, level: " << level << std::endl;
    }
};

// 2. Function Hiding with Different Return Types
class Calculator {
public:
    int add(int a, int b) {
        std::cout << "Calculator::add(int, int)" << std::endl;
        return a + b;
    }
    
    double add(double a, double b) {
        std::cout << "Calculator::add(double, double)" << std::endl;
        return a + b;
    }
    
    void compute() {
        std::cout << "Calculator::compute() - basic computation" << std::endl;
    }
    
    virtual void calculate() {
        std::cout << "Calculator::calculate() - virtual calculation" << std::endl;
    }
    
    virtual ~Calculator() = default;
};

class ScientificCalculator : public Calculator {
public:
    // Function hiding - hides ALL add() overloads from base class
    std::string add(const std::string& a, const std::string& b) {
        std::cout << "ScientificCalculator::add(string, string)" << std::endl;
        return a + b;
    }
    
    // Function hiding with different return type
    std::string compute() {  // Hides Calculator::compute()
        std::cout << "ScientificCalculator::compute() - returns string" << std::endl;
        return "Advanced computation result";
    }
    
    // Virtual function override (not hiding)
    void calculate() override {
        std::cout << "ScientificCalculator::calculate() - advanced calculation" << std::endl;
    }
    
    // Accessing hidden base functions using 'using' declaration
    using Calculator::add;  // Brings back base class add() overloads
};

// 3. Function Hiding in Multiple Inheritance
class A {
public:
    void func() {
        std::cout << "A::func()" << std::endl;
    }
    
    void common(int x) {
        std::cout << "A::common(int): " << x << std::endl;
    }
};

class B {
public:
    void func() {
        std::cout << "B::func()" << std::endl;
    }
    
    void common(double x) {
        std::cout << "B::common(double): " << x << std::endl;
    }
};

class MultiDerived : public A, public B {
public:
    // Function hiding in multiple inheritance
    void func() {
        std::cout << "MultiDerived::func() - hides both A::func() and B::func()" << std::endl;
    }
    
    // To access hidden functions, need explicit qualification
    void callParentFunctions() {
        A::func();  // Explicitly call A's version
        B::func();  // Explicitly call B's version
    }
};

// 4. Function Hiding vs Name Lookup
class NameLookupBase {
public:
    void process() {
        std::cout << "NameLookupBase::process()" << std::endl;
    }
    
    void process(int x) {
        std::cout << "NameLookupBase::process(int): " << x << std::endl;
    }
    
    void process(double x) {
        std::cout << "NameLookupBase::process(double): " << x << std::endl;
    }
};

class NameLookupDerived : public NameLookupBase {
public:
    // This hides ALL process() functions from base class
    void process(const std::string& s) {
        std::cout << "NameLookupDerived::process(string): " << s << std::endl;
    }
    
    // To make base class overloads available
    using NameLookupBase::process;  // Brings back all base class process() overloads
};

// 5. Static Function Hiding
class StaticBase {
public:
    static void staticFunc() {
        std::cout << "StaticBase::staticFunc()" << std::endl;
    }
    
    static void utility(int x) {
        std::cout << "StaticBase::utility(int): " << x << std::endl;
    }
};

class StaticDerived : public StaticBase {
public:
    // Static function hiding
    static void staticFunc() {
        std::cout << "StaticDerived::staticFunc() - hides base static function" << std::endl;
    }
    
    // Different signature - also hides base function
    static void utility(double x) {
        std::cout << "StaticDerived::utility(double): " << x << std::endl;
    }
};

// Demonstration functions
void demonstrateBasicFunctionHiding() {
    std::cout << "\n=== BASIC FUNCTION HIDING ===" << std::endl;
    
    Base base;
    Derived derived;
    
    std::cout << "Direct calls on base object:" << std::endl;
    base.display();
    base.show(42);
    base.show(3.14);
    base.show("Hello");
    base.processData();
    
    std::cout << "\nDirect calls on derived object:" << std::endl;
    derived.display();           // Calls Derived::display() - hiding
    derived.show('A');           // Calls Derived::show(char)
    
    // These would cause compilation errors because base overloads are hidden:
    // derived.show(42);         // ERROR: no matching function
    // derived.show(3.14);       // ERROR: no matching function
    // derived.show("Hello");    // ERROR: no matching function
    // derived.processData();    // ERROR: no matching function
    
    std::cout << "Accessing hidden functions with explicit qualification:" << std::endl;
    derived.Base::show(42);      // Explicitly call base class version
    derived.Base::show(3.14);
    derived.Base::show("Hello");
    derived.Base::processData();
    
    std::cout << "\nThrough base pointer (early binding for non-virtual):" << std::endl;
    Base* ptr = &derived;
    ptr->display();              // Calls Base::display() - early binding
    ptr->show(42);              // Calls Base::show(int)
    ptr->virtualFunc();         // Calls Derived::virtualFunc() - late binding
}

void demonstrateFunctionHidingWithUsing() {
    std::cout << "\n=== FUNCTION HIDING WITH 'using' DECLARATION ===" << std::endl;
    
    ScientificCalculator calc;
    
    std::cout << "After 'using' declaration, base overloads are available:" << std::endl;
    
    // These work because of 'using Calculator::add;'
    int intResult = calc.add(5, 3);              // Calculator::add(int, int)
    double doubleResult = calc.add(2.5, 1.5);    // Calculator::add(double, double)
    std::string stringResult = calc.add("Hello", " World");  // ScientificCalculator::add(string, string)
    
    std::cout << "Int result: " << intResult << std::endl;
    std::cout << "Double result: " << doubleResult << std::endl;
    std::cout << "String result: " << stringResult << std::endl;
    
    std::cout << "\nFunction hiding still occurs for compute():" << std::endl;
    std::string computeResult = calc.compute();  // Calls derived version
    std::cout << "Compute result: " << computeResult << std::endl;
    
    // To call base version:
    calc.Calculator::compute();
}

void demonstrateNameLookup() {
    std::cout << "\n=== NAME LOOKUP AND FUNCTION HIDING ===" << std::endl;
    
    NameLookupDerived obj;
    
    std::cout << "With 'using' declaration, all overloads are available:" << std::endl;
    obj.process();               // NameLookupBase::process()
    obj.process(42);            // NameLookupBase::process(int)
    obj.process(3.14);          // NameLookupBase::process(double)
    obj.process("Hello");       // NameLookupDerived::process(string)
}

void demonstrateMultipleInheritance() {
    std::cout << "\n=== FUNCTION HIDING IN MULTIPLE INHERITANCE ===" << std::endl;
    
    MultiDerived obj;
    
    std::cout << "Derived function hides both parent versions:" << std::endl;
    obj.func();  // Calls MultiDerived::func()
    
    std::cout << "\nExplicitly calling parent versions:" << std::endl;
    obj.callParentFunctions();
    
    std::cout << "\nDirect explicit calls:" << std::endl;
    obj.A::func();
    obj.B::func();
    
    std::cout << "\nOverload resolution works across parents:" << std::endl;
    obj.A::common(42);      // A::common(int)
    obj.B::common(3.14);    // B::common(double)
}

void demonstrateStaticFunctionHiding() {
    std::cout << "\n=== STATIC FUNCTION HIDING ===" << std::endl;
    
    std::cout << "Static function hiding:" << std::endl;
    StaticBase::staticFunc();       // Base version
    StaticDerived::staticFunc();    // Derived version (hides base)
    
    std::cout << "\nStatic overload hiding:" << std::endl;
    StaticBase::utility(42);        // Base version with int
    StaticDerived::utility(3.14);   // Derived version with double
    
    // This would cause error because int version is hidden:
    // StaticDerived::utility(42);  // ERROR: no matching function
    
    std::cout << "\nExplicit qualification for hidden static functions:" << std::endl;
    StaticDerived::StaticBase::utility(42);  // Explicitly call base version
}

void demonstratePolymorphismVsHiding() {
    std::cout << "\n=== POLYMORPHISM VS FUNCTION HIDING ===" << std::endl;
    
    std::vector<std::unique_ptr<Base>> objects;
    objects.push_back(std::make_unique<Base>());
    objects.push_back(std::make_unique<Derived>());
    
    std::cout << "Virtual functions (polymorphism):" << std::endl;
    for (const auto& obj : objects) {
        obj->virtualFunc();  // Runtime polymorphism
    }
    
    std::cout << "\nNon-virtual functions (function hiding/early binding):" << std::endl;
    for (const auto& obj : objects) {
        obj->display();  // Early binding - always calls Base::display()
    }
    
    std::cout << "\nDirect object calls show the difference:" << std::endl;
    Base base;
    Derived derived;
    
    base.display();      // Base::display()
    derived.display();   // Derived::display() - function hiding
    
    base.virtualFunc();     // Base::virtualFunc()
    derived.virtualFunc();  // Derived::virtualFunc() - overriding
}

int main() {
    std::cout << "=== FUNCTION HIDING IN C++ ===" << std::endl;
    std::cout << "Function hiding occurs when derived class functions hide base class functions" << std::endl;
    std::cout << "with the same name, regardless of signature differences." << std::endl;
    
    // 1. Basic function hiding demonstration
    demonstrateBasicFunctionHiding();
    
    // 2. Using declaration to bring back hidden functions
    demonstrateFunctionHidingWithUsing();
    
    // 3. Name lookup and function hiding
    demonstrateNameLookup();
    
    // 4. Multiple inheritance and function hiding
    demonstrateMultipleInheritance();
    
    // 5. Static function hiding
    demonstrateStaticFunctionHiding();
    
    // 6. Polymorphism vs function hiding
    demonstratePolymorphismVsHiding();
    
    std::cout << "\n=== FUNCTION HIDING KEY CONCEPTS ===" << std::endl;
    std::cout << "✅ Function hiding applies to non-virtual functions" << std::endl;
    std::cout << "✅ Derived function hides ALL base overloads with same name" << std::endl;
    std::cout << "✅ Resolved at compile-time (early binding)" << std::endl;
    std::cout << "✅ Different from method overriding (virtual functions)" << std::endl;
    std::cout << "✅ Use 'using' declaration to bring back hidden overloads" << std::endl;
    std::cout << "✅ Explicit qualification can access hidden functions" << std::endl;
    
    std::cout << "\n=== FUNCTION HIDING RULES ===" << std::endl;
    std::cout << "1. Name lookup stops at first scope that contains the name" << std::endl;
    std::cout << "2. ALL overloads in outer scopes are hidden" << std::endl;
    std::cout << "3. Signature differences don't matter for hiding" << std::endl;
    std::cout << "4. Static and non-static functions can hide each other" << std::endl;
    std::cout << "5. Virtual functions use overriding, not hiding" << std::endl;
    std::cout << "6. 'using' declaration brings hidden names back into scope" << std::endl;
    
    std::cout << "\n=== BEST PRACTICES ===" << std::endl;
    std::cout << "⚠️  Be aware of function hiding when designing inheritance" << std::endl;
    std::cout << "⚠️  Use 'using' declarations to avoid unexpected hiding" << std::endl;
    std::cout << "⚠️  Consider making functions virtual for polymorphic behavior" << std::endl;
    std::cout << "⚠️  Use explicit qualification when needed" << std::endl;
    std::cout << "⚠️  Document when function hiding is intentional" << std::endl;
    std::cout << "⚠️  Prefer composition over inheritance to avoid hiding issues" << std::endl;
    
    std::cout << "\n=== COMMON PITFALLS ===" << std::endl;
    std::cout << "❌ Accidentally hiding useful base class overloads" << std::endl;
    std::cout << "❌ Expecting polymorphic behavior from non-virtual functions" << std::endl;
    std::cout << "❌ Forgetting that hiding affects ALL overloads" << std::endl;
    std::cout << "❌ Confusion between hiding and overriding" << std::endl;
    std::cout << "❌ Not using 'using' declarations when appropriate" << std::endl;
    
    return 0;
}

/*
Function Hiding Summary:

1. Definition:
   - When a derived class function with the same name as a base class function
   - Makes the base class function inaccessible without explicit qualification
   - Applies to non-virtual functions (virtual functions use overriding)

2. Characteristics:
   - Compile-time resolution (early binding)
   - Name-based hiding (signature doesn't matter)
   - Hides ALL overloads with the same name
   - Different from method overriding

3. Key Differences from Overriding:
   - Hiding: Non-virtual functions, early binding, name-based
   - Overriding: Virtual functions, late binding, signature-based

4. Solutions:
   - 'using' declarations to bring back hidden functions
   - Explicit qualification (Base::function())
   - Make functions virtual for polymorphic behavior
   - Careful inheritance design

5. When Function Hiding Occurs:
   - Non-virtual function in derived class with same name as base
   - Different signatures still cause hiding
   - Static functions can hide non-static and vice versa
   - Multiple inheritance can create complex hiding scenarios

6. Best Practices:
   - Use virtual functions for polymorphic behavior
   - Use 'using' declarations to avoid accidental hiding
   - Be explicit about inheritance design intentions
   - Consider composition over inheritance for complex cases
*/
