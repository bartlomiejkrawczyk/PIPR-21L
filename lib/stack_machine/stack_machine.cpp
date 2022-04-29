#include "stack_machine.h"

#include <functional>
#include <iomanip>
#include <memory>
#include <sstream>
#include <vector>

#include "../value/value.h"
#include "operations.h"

// Stack Functionality

StackMachine::StackMachine() {}

// Element Access

Value& StackMachine::top() {
    if (stack.size() == 0) throw std::out_of_range("Empty Stack!");
    return *stack.back();
}

const Value& StackMachine::top() const {
    if (stack.size() == 0) throw std::out_of_range("Empty Stack!");
    return *stack.back();
}

// Iterators

auto StackMachine::begin() { return stack.begin(); }
auto StackMachine::end() { return stack.end(); }
auto StackMachine::begin() const { return stack.begin(); }
auto StackMachine::end() const { return stack.end(); }

auto StackMachine::rbegin() { return stack.rbegin(); }
auto StackMachine::rend() { return stack.rend(); }
auto StackMachine::rbegin() const { return stack.rbegin(); }
auto StackMachine::rend() const { return stack.rend(); }

// Capacity

bool StackMachine::empty() const { return stack.empty(); }
size_t StackMachine::size() const { return stack.size(); }

void StackMachine::clear() { stack.clear(); }

// Modifiers

void StackMachine::push(std::unique_ptr<Value> val) { stack.push_back(std::move(val)); }

void StackMachine::pop() {
    if (stack.size() == 0) throw std::out_of_range("Empty Stack!");
    stack.pop_back();
}

std::unique_ptr<Value> StackMachine::peekAndPop() {
    if (stack.size() == 0) throw std::out_of_range("Empty Stack!");
    std::unique_ptr<Value> val = std::move(stack.back());
    stack.pop_back();
    return val;
}

// Stack Machine funcionality

void StackMachine::performOperation(
    const std::function<std::unique_ptr<Value>(Value const& a, Value const& b)>& function) {
    if (stack.size() < 2) throw std::out_of_range("Not enough values on the stack!");

    std::unique_ptr<Value> b = peekAndPop();
    std::unique_ptr<Value> a = peekAndPop();
    try {
        stack.push_back(function(*a, *b));
    } catch (...) {
        stack.push_back(std::move(a));
        stack.push_back(std::move(b));
        throw;
    }
}

// Arithmetic opertors

inline void StackMachine::add() { performOperation(&addition); }        // a + b
inline void StackMachine::sub() { performOperation(&subtraction); }     // a - b
inline void StackMachine::mul() { performOperation(&multiplication); }  // a * b
inline void StackMachine::div() { performOperation(&division); }        // a / b
inline void StackMachine::pow() { performOperation(&power); }           // a ^ b

void StackMachine::swap() {
    if (stack.size() < 2) throw std::out_of_range("Not enough values on the stack!");
    std::unique_ptr<Value> first = std::move(stack.back());
    stack.pop_back();
    std::unique_ptr<Value> second = std::move(stack.back());
    stack.pop_back();
    stack.push_back(std::move(first));
    stack.push_back(std::move(second));
}

inline void StackMachine::dup() {
    if (stack.size() == 0) throw std::out_of_range("Empty Stack!");
    stack.push_back(stack.back()->clone());
}

// Print

std::ostream& operator<<(std::ostream& os, StackMachine const& machine) {
    for (auto i = machine.rbegin(); i != machine.rend(); ++i) {
        std::stringstream ss;
        Value& ptr = *(*i);
        ss << ptr;
        os << "| " << std::setw(15) << ss.str() << " |\n";
    }
    os << "___________________\n";

    return os;
}
