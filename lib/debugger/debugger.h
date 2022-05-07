#pragma once

#include <program/program.h>

#include <functional>
#include <iostream>

class Debugger {
    Program& program;

public:
    Debugger(Program* p) : program(*p) {}

    void displayState(std::ostream& os);

    void run(std::ostream& os);
    void step(std::ostream& os);
    void restart();

    void interaction(std::istream& is = std::cin, std::ostream& os = std::cout);

private:
    void printCommand(size_t i, std::ostream& os);

    void handleExceptions(std::ostream& os, std::function<void()> func);
};