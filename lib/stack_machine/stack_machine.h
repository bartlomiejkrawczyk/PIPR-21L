#pragma once

#include <value/value.h>

#include <functional>
#include <memory>
#include <vector>

#include "operations.h"

class StackMachine {
    std::vector<std::unique_ptr<Value>> stack;

public:
    StackMachine();
    StackMachine(const StackMachine& stackMachine);

    // Stack funcionality

    // Element access

    // Get reference to the top element
    Value& top();
    const Value& top() const;

    // Iterators
    std::vector<std::unique_ptr<Value>>::iterator begin();
    std::vector<std::unique_ptr<Value>>::iterator end();
    std::vector<std::unique_ptr<Value>>::const_iterator begin() const;
    std::vector<std::unique_ptr<Value>>::const_iterator end() const;

    std::reverse_iterator<std::vector<std::unique_ptr<Value>>::iterator> rbegin();
    std::reverse_iterator<std::vector<std::unique_ptr<Value>>::iterator> rend();
    std::reverse_iterator<std::vector<std::unique_ptr<Value>>::const_iterator> rbegin() const;
    std::reverse_iterator<std::vector<std::unique_ptr<Value>>::const_iterator> rend() const;

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
    void add();
    // a - b
    void sub();
    // a * b
    void mul();
    // a / b
    void div();
    // a ^ b
    void pow();

    // Swap positions of the top two elements
    void swap();
    // Duplicate top value
    void dup();

    friend std::ostream& operator<<(std::ostream& os, StackMachine const& machine);
};