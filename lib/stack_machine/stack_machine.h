#pragma once

#include <functional>
#include <memory>
#include <vector>

class Value;

class StackMachine {
    std::vector<std::unique_ptr<Value>> stack;

public:
    StackMachine();

    // Stack funcionality

    // Element access

    // Get reference to the top element
    Value& top();
    const Value& top() const;

    // Iterators
    auto begin();
    auto end();
    auto begin() const;
    auto end() const;

    auto rbegin();
    auto rend();
    auto rbegin() const;
    auto rend() const;

    // Capacity

    // Check if the container has no elements
    bool empty() const;
    // Return the number of elements
    size_t size() const;

    void clear();

    // Modifiers

    // Save on top of the stack
    void push(std::unique_ptr<Value> val);

    // Remove element from top of the stack
    void pop();
    // Remove element from top of the stack and return it
    std::unique_ptr<Value> peekAndPop();

private:
    // Pops two arguments from the top of the stack
    // Performs a function on them
    // Result pushes on top of the stack
    void performOperation(
        const std::function<std::unique_ptr<Value>(Value const& a, Value const& b)>& function);

public:
    // Stack Machine funcionality

    // Arithmetic opertors

    // a + b
    inline void add();
    // a - b
    inline void sub();
    // a * b
    inline void mul();
    // a / b
    inline void div();
    // a ^ b
    inline void pow();

    // Swap positions of the top two elements
    void swap();
    // Duplicate top value
    inline void dup();

    friend std::ostream& operator<<(std::ostream& os, StackMachine const& machine);
};