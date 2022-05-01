#include "program.h"

#include <value/value.h>

void Program::addInstruction(std::unique_ptr<Command> instruction) {
    instructions.push_back(std::move(instruction));
}

void Program::step() {
    if (instructions.size() > instruction) {
        call(*instructions[instruction++]);
    }
}

void Program::run() {
    for (; instruction < instructions.size(); ++instruction) {
        call(*instructions[instruction]);
    }
}

void Program::call(const Command& command) { command.performOperation(*this); }

std::ostream& operator<<(std::ostream& os, const Program& program) {
    os << "Stack:" << std::endl;
    os << program.stack;
    os << "Memory:" << std::endl;
    os << program.memory;

    return os;
}

std::istream& operator>>(std::istream& is, Program& program) {
    std::string line;
    while (!is.eof()) {
        getline(is, line);
        if (!line.empty()) {
            std::stringstream ss(line);
            program.addInstruction(Command::read(ss));
        }
    }

    return is;
}