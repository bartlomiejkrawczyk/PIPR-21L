#include "command.h"

#include <algorithm>

#include "../program/program.h"

// Command

std::unique_ptr<Command> Command::read(std::istream& is) {
    std::string command;

    is >> command;

    std::transform(command.begin(), command.end(), command.begin(), ::toupper);

    if (command == "PUSH") {
        return std::make_unique<PushCommand>(PushCommand(std::move(Value::read(is))));
    } else if (command == "READ") {
        int address;
        is >> address;
        return std::make_unique<ReadCommand>(ReadCommand(address));
    } else if (command == "WRITE") {
        int address;
        is >> address;
        return std::make_unique<WriteCommand>(WriteCommand(address));
    }

    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Command& command) {
    command.print(os);
    return os;
}

// PUSH

void PushCommand::performOperation(Program& program) const {
    program.stack.push(std::move(value->clone()));
}
void PushCommand::print(std::ostream& os) const {
    os << "PUSH"
       << " " << value.get() << std::endl;
}

// READ

void ReadCommand::performOperation(Program& program) const {
    if (program.memory[address] == nullptr)
        throw std::invalid_argument("Invalid address: " + address);

    program.stack.push(std::move(program.memory[address]->clone()));
}
void ReadCommand::print(std::ostream& os) const {
    os << "READ"
       << " " << address << std::endl;
}

// WRITE

void WriteCommand::performOperation(Program& program) const {
    for (int i = program.memory.size(); i <= address; ++i) program.memory.push_back(nullptr);

    program.memory[address] = std::move(program.stack.top().clone());
}
void WriteCommand::print(std::ostream& os) const {
    os << "WRITE"
       << " " << address << std::endl;
}