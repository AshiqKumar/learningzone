# Microsoft Senior Software Engineer C++ Interview Questions (2025)

This document summarizes common C++-focused questions asked in the 2nd and 3rd rounds of interviews for Senior Software Engineer roles at Microsoft, based on recent candidate experiences. Each question includes a brief explanation and sample answer.

---

## 1. Design & Problem Solving

### Q: Design a thread-safe singleton in C++.
**A:**
```cpp
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
private:
    Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
```
*Explanation: Uses C++11 static local variable initialization for thread safety.*

### Q: Implement an LRU cache using STL containers.
**A:** Use `std::list` for order and `std::unordered_map` for fast lookup. Move accessed items to the front; evict from the back.

---

## 2. Core C++ Concepts

### Q: Explain the Rule of Three/Five/Zero.
**A:**
- **Three:** If you define one of destructor, copy constructor, or copy assignment, define all three.
- **Five:** Also include move constructor and move assignment (C++11).
- **Zero:** Prefer types that manage resources automatically (e.g., smart pointers).

### Q: What is RAII? Give examples from the STL.
**A:** RAII means resources are acquired and released by object lifetime. Examples: `std::vector`, `std::lock_guard`.

---

## 3. Concurrency & Multithreading

### Q: How do you avoid deadlocks in multi-threaded code?
**A:** Acquire locks in a consistent order, minimize lock scope, use try-locks, prefer higher-level primitives.

### Q: How does `std::future` and `std::promise` work in C++11?
**A:** `std::promise` sets a value; `std::future` retrieves it asynchronously.

---

## 4. STL & Algorithms

### Q: How does `std::unordered_map` work internally?
**A:** Uses a hash table; average O(1) operations, worst-case O(n) if many collisions.

### Q: What is the difference between `std::sort` and `std::stable_sort`?
**A:** `std::sort` may reorder equal elements; `std::stable_sort` preserves their order.

---

## 5. Code Quality & Best Practices

### Q: How do you ensure exception safety in your code?
**A:** Use RAII, smart pointers, maintain invariants, prefer standard containers.

### Q: How do you debug a memory leak in a production system?
**A:** Use tools like Valgrind, AddressSanitizer, Visual Studio diagnostics; analyze heap usage and ownership.

### Manual Memory Management Pitfalls in C++

- **Memory Leaks:** Forgetting to `delete` memory allocated with `new`.
- **Double Free:** Calling `delete` twice on the same pointer, leading to undefined behavior.
- **Dangling Pointers:** Using pointers after the memory they point to has been freed.
- **Buffer Overflows:** Writing past the end of allocated memory.
- **Uninitialized Pointers:** Using pointers that have not been initialized, which may point to random memory.
- **Mismatched Allocation/Deallocation:** Using `delete[]` for memory allocated with `new`, or vice versa.
- **Resource Ownership Confusion:** Not clearly defining which part of code is responsible for freeing memory.
- **Failure to Handle Exceptions:** Not freeing memory if an exception is thrown before `delete` is called.

*Best Practice: Prefer smart pointers (`std::unique_ptr`, `std::shared_ptr`) and RAII to avoid these issues.*

---

## 6. Scenario & System Design

### Q: How would you design a distributed logging system in C++?
**A:** Use asynchronous logging, batching, network protocols, and ensure thread safety and fault tolerance.

### Q: How do you handle cross-platform builds and dependencies in a large C++ project?
**A:** Use CMake, package managers, and abstract platform-specific code.

---

*Tip: Be ready to discuss your solutions, edge cases, and performance trade-offs. Expect follow-up questions and code writing during interviews.*
