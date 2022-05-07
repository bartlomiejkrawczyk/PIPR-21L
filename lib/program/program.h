#pragma once

#include <command/command.h>
#include <debugger/debugger.h>
#include <memory/memory.h>
#include <stack_machine/stack_machine.h>

#include <iostream>
#include <memory>
#include <vector>

class Value;

class Program {
    std::vector<std::unique_ptr<Command>> instructions;

public:
    Memory<std::unique_ptr<Value>> memory;
    StackMachine stack;
    size_t instruction = 0;

    void addInstruction(std::unique_ptr<Command> instruction);

    void step();

    void run();

private:
    void call(const Command& command);

public:
    friend std::ostream& operator<<(std::ostream& os, const Program& program);
    friend std::istream& operator>>(std::istream& is, Program& program);

    friend class Debugger;
};