#include <stack_machine/stack_machine.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Stack without params is initiated empty", "stack-machine") {
    StackMachine stack;
    REQUIRE(stack.size() == 0);
    REQUIRE(stack.empty());
}

TEST_CASE("Check if trying to lookup top value of empty stack throws error", "stack-machine") {
    StackMachine stack;
    REQUIRE(stack.size() == 0);
    REQUIRE(stack.empty());
    REQUIRE_THROWS_AS(stack.top(), std::out_of_range);
}

TEST_CASE("Check if push can append value to stack", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    REQUIRE(stack.size() == 1);
    REQUIRE(!stack.empty());
    REQUIRE(stack.top().value() == 2);
}

TEST_CASE("Check if push can append values to stack", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    REQUIRE(stack.size() == 3);
    REQUIRE(!stack.empty());
    REQUIRE(stack.top().value() == 3);
}

TEST_CASE("Check if pop removes value from stack", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top().value() == 1);

    stack.pop();
    REQUIRE(stack.size() == 0);
}

TEST_CASE("Check if pop removes values from stack in correct order", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    REQUIRE(stack.size() == 3);
    REQUIRE(stack.top().value() == 3);
    stack.pop();
    REQUIRE(stack.top().value() == 2);
    stack.pop();
    REQUIRE(stack.top().value() == 1);
    stack.pop();
    REQUIRE(stack.size() == 0);
}

TEST_CASE("Check if pop called on empty stack throws error", "stack-machine") {
    StackMachine stack;
    REQUIRE(stack.size() == 0);
    REQUIRE_THROWS_AS(stack.pop(), std::out_of_range);
}

TEST_CASE("Check if peekAndPop removes correct value from stack", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top().value() == 1);

    REQUIRE(stack.peekAndPop()->value() == 1);
    REQUIRE(stack.size() == 0);
}

TEST_CASE("Check if peekAndPop removes correct unique_ptr to value from stack", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    REQUIRE(stack.size() == 1);
    REQUIRE(stack.top().value() == 1);

    std::unique_ptr<Value> val = std::move(stack.peekAndPop());
    REQUIRE(val->value() == 1);
    REQUIRE(stack.size() == 0);
}

TEST_CASE("Check if peekAndPop removes correct values from stack", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    REQUIRE(stack.size() == 3);
    REQUIRE(stack.top().value() == 3);
    REQUIRE(stack.peekAndPop()->value() == 3);
    REQUIRE(stack.top().value() == 2);
    REQUIRE(stack.peekAndPop()->value() == 2);
    REQUIRE(stack.top().value() == 1);
    REQUIRE(stack.peekAndPop()->value() == 1);
    REQUIRE(stack.size() == 0);
}

TEST_CASE("Check if popAndPop called on empty stack throws error", "stack-machine") {
    StackMachine stack;
    REQUIRE(stack.size() == 0);
    REQUIRE_THROWS_AS(stack.peekAndPop(), std::out_of_range);
}

TEST_CASE("Check if clear clears the stack", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    REQUIRE(stack.size() == 3);
    stack.clear();
    REQUIRE(stack.size() == 0);
}

TEST_CASE("Check if iterators work correctly", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    int a = 0;
    for (auto const& i : stack) {
        REQUIRE((*i).value() == ++a);
    }
    const StackMachine sconst(stack);
    a = 0;
    for (auto i = sconst.begin(); i != sconst.end(); ++i) {
        REQUIRE(++a == (*i)->value());
    };
}

TEST_CASE("Check if reverse iterators work correctly", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    int a = 4;
    for (auto i = stack.rbegin(); i != stack.rend(); ++i) {
        REQUIRE(--a == (*i)->value());
    };
    a = 4;
    const StackMachine sconst(stack);
    for (auto i = sconst.rbegin(); i != sconst.rend(); ++i) {
        REQUIRE(--a == (*i)->value());
    };
}