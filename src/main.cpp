#include <stack_machine/stack_machine.h>

#include <iostream>

int main() {
    StackMachine stack;
    stack.push(std::make_unique<Fraction>(Fraction(1)));
    stack.push(std::make_unique<Fraction>(Fraction(2)));
    stack.push(std::make_unique<Fraction>(Fraction(3)));

    std::cout << stack << std::endl;

    return 0;
}