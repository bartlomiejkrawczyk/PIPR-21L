#include <stack_machine/stack_machine.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <sstream>

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

// Iterators

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

// Print

TEST_CASE("Check if stack is printed correctly", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    std::stringstream ss;

    ss << stack;

    REQUIRE(ss.str() ==
            "|               3 |\n|               2 |\n|               1 |\n___________________\n");
}

// Addition

TEST_CASE("Check addition", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    REQUIRE(stack.top().value() == 3);
    stack.add();
    REQUIRE(stack.top().value() == 5);
    stack.add();
    REQUIRE(stack.top().value() == 6);
    REQUIRE(stack.size() == 1);
}

TEST_CASE("Check addition on empty stack", "stack-machine") {
    StackMachine stack;
    REQUIRE_THROWS_AS(stack.add(), std::out_of_range);
}

TEST_CASE("Check addition on stack with one value", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    REQUIRE_THROWS_AS(stack.add(), std::out_of_range);
}

// Subtraction

TEST_CASE("Check subtraction", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    REQUIRE(stack.top().value() == 3);
    stack.sub();
    REQUIRE(stack.top().value() == -1);
    stack.sub();
    REQUIRE(stack.top().value() == 2);
    REQUIRE(stack.size() == 1);
}

TEST_CASE("Check subtraction on empty stack", "stack-machine") {
    StackMachine stack;
    REQUIRE_THROWS_AS(stack.sub(), std::out_of_range);
}

TEST_CASE("Check subtraction on stack with one value", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    REQUIRE_THROWS_AS(stack.sub(), std::out_of_range);
}

// Multiplication

TEST_CASE("Check multiplication", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    stack.push(std::make_unique<Fraction>(Fraction(4)));
    REQUIRE(stack.top().value() == 4);
    stack.mul();
    REQUIRE(stack.top().value() == 12);
    stack.mul();
    REQUIRE(stack.top().value() == 24);
    REQUIRE(stack.size() == 1);
}

TEST_CASE("Check multiplication on empty stack", "stack-machine") {
    StackMachine stack;
    REQUIRE_THROWS_AS(stack.mul(), std::out_of_range);
}

TEST_CASE("Check multiplication on stack with one value", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    REQUIRE_THROWS_AS(stack.mul(), std::out_of_range);
}

// Division

TEST_CASE("Check division", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    stack.push(std::make_unique<Fraction>(Fraction(4)));
    REQUIRE(stack.top().value() == 4);
    stack.div();
    REQUIRE(stack.top().value() == 0.75);
    stack.div();
    REQUIRE(stack.top().value() == 8.0 / 3.0);
    REQUIRE(stack.size() == 1);
}

TEST_CASE("Check division by zero", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(0)));
    REQUIRE(stack.top().value() == 0);
    REQUIRE(stack.size() == 2);
    REQUIRE_THROWS_AS(stack.div(), std::domain_error);
    REQUIRE(stack.top().value() == 0);
    REQUIRE(stack.size() == 2);
}

TEST_CASE("Check division on empty stack", "stack-machine") {
    StackMachine stack;
    REQUIRE_THROWS_AS(stack.div(), std::out_of_range);
}

TEST_CASE("Check division on stack with one value", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    REQUIRE_THROWS_AS(stack.div(), std::out_of_range);
}

// Power

TEST_CASE("Check power", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    REQUIRE(stack.top().value() == 3);
    stack.pow();
    REQUIRE(stack.top().value() == 8);
    stack.pow();
    REQUIRE(stack.top().value() == 256);
    REQUIRE(stack.size() == 1);
}

TEST_CASE("Check negative number to fraction power", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(-2)));
    stack.push(std::make_unique<Fraction>(Fraction(1, 3)));
    REQUIRE_THROWS_AS(stack.pow(), std::domain_error);
    REQUIRE(stack.top().value() == 1.0 / 3.0);
    REQUIRE(stack.size() == 2);
}

TEST_CASE("Check power on empty stack", "stack-machine") {
    StackMachine stack;
    REQUIRE_THROWS_AS(stack.pow(), std::out_of_range);
}

TEST_CASE("Check power on stack with one value", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    REQUIRE_THROWS_AS(stack.pow(), std::out_of_range);
}

// Swap

TEST_CASE("Check swap", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));
    REQUIRE(stack.top().value() == 3);
    stack.swap();
    REQUIRE(stack.top().value() == 2);
    stack.pop();
    REQUIRE(stack.top().value() == 3);
    stack.swap();
    REQUIRE(stack.top().value() == 1);
    stack.pop();
    REQUIRE(stack.top().value() == 3);
}

TEST_CASE("Check swap on empty stack", "stack-machine") {
    StackMachine stack;
    REQUIRE_THROWS_AS(stack.swap(), std::out_of_range);
}

TEST_CASE("Check swap on stack with one value", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    REQUIRE_THROWS_AS(stack.swap(), std::out_of_range);
}

// Duplication
TEST_CASE("Check duplication", "stack-machine") {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    REQUIRE(stack.top().value() == 2);
    REQUIRE(stack.size() == 1);
    stack.dup();
    REQUIRE(stack.top().value() == 2);
    REQUIRE(stack.size() == 2);
    stack.pop();
    REQUIRE(stack.top().value() == 2);
    REQUIRE(stack.size() == 1);
}

TEST_CASE("Check duplication on empty stack", "stack-machine") {
    StackMachine stack;
    REQUIRE_THROWS_AS(stack.dup(), std::out_of_range);
}
