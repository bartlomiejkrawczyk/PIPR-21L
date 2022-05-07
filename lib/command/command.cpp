#include "command.h"

#include <program/program.h>

#include <algorithm>

// Command

// Simple object factory
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
    } else if (command == "JUMP") {
        int address;
        is >> address;
        return std::make_unique<JumpCommand>(JumpCommand(address));
    } else if (command == "JUMP_ZERO") {
        int address;
        is >> address;
        return std::make_unique<JumpZeroCommand>(JumpZeroCommand(address));
    } else if (command == "JUMP_NOT_ZERO") {
        int address;
        is >> address;
        return std::make_unique<JumpNotZeroCommand>(JumpNotZeroCommand(address));
    } else if (command == "CALL") {
        int address;
        is >> address;
        return std::make_unique<CallCommand>(CallCommand(address));
    } else if (command == "RET") {
        return std::make_unique<ReturnCommand>(ReturnCommand());
    } else if (command == "ADD") {
        return std::make_unique<AdditionCommand>(AdditionCommand());
    } else if (command == "SUP") {
        return std::make_unique<SubtractionCommand>(SubtractionCommand());
    } else if (command == "MUL") {
        return std::make_unique<MultiplicationCommand>(MultiplicationCommand());
    } else if (command == "DIV") {
        return std::make_unique<DivisionCommand>(DivisionCommand());
    } else if (command == "POW") {
        return std::make_unique<PowerCommand>(PowerCommand());
    } else if (command == "DUP") {
        return std::make_unique<DuplicationCommand>(DuplicationCommand());
    } else if (command == "SWAP") {
        return std::make_unique<SwapCommand>(SwapCommand());
    }

    throw std::invalid_argument("Invalid instruction: " + command);
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
       << " " << *value.get() << std::endl;
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

// JUMP

void JumpCommand::performOperation(Program& program) const {
    // Note: Line count starts from 1, but instructions are indexed from 0
    program.instruction = address - 1;
}

void JumpCommand::print(std::ostream& os) const {
    os << "JUMP"
       << " " << address << std::endl;
}

// JUMP_ZERO

void JumpZeroCommand::performOperation(Program& program) const {
    // Note: Line count starts from 1, but instructions are indexed from 0
    if (program.stack.top().value() == 0.0) program.instruction = address - 1;
}

void JumpZeroCommand::print(std::ostream& os) const {
    os << "JUMP_ZERO"
       << " " << address << std::endl;
}

// JUMP_NOT_ZERO

void JumpNotZeroCommand::performOperation(Program& program) const {
    // Note: Line count starts from 1, but instructions are indexed from 0
    if (program.stack.top().value() != 0.0) program.instruction = address - 1;
}

void JumpNotZeroCommand::print(std::ostream& os) const {
    os << "JUMP_NOT_ZERO"
       << " " << address << std::endl;
}

// CALL

void CallCommand::performOperation(Program& program) const {
    program.stack.push(std::make_unique<Fraction>(Fraction(program.instruction)));
    // Note: Line count starts from 1, but instructions are indexed from 0
    program.instruction = address - 1;
}

void CallCommand::print(std::ostream& os) const {
    os << "CALL"
       << " " << address << std::endl;
}

// RET

void ReturnCommand::performOperation(Program& program) const {
    program.instruction = (int)program.stack.peekAndPop()->value();
}

void ReturnCommand::print(std::ostream& os) const { os << "RET" << std::endl; }

// ADD

void AdditionCommand::performOperation(Program& program) const { program.stack.add(); }

void AdditionCommand::print(std::ostream& os) const { os << "ADD" << std::endl; }

// SUB

void SubtractionCommand::performOperation(Program& program) const { program.stack.sub(); }

void SubtractionCommand::print(std::ostream& os) const { os << "SUB" << std::endl; }

// MUL

void MultiplicationCommand::performOperation(Program& program) const { program.stack.mul(); }

void MultiplicationCommand::print(std::ostream& os) const { os << "MUL" << std::endl; }

// DIV

void DivisionCommand::performOperation(Program& program) const { program.stack.div(); }

void DivisionCommand::print(std::ostream& os) const { os << "DIV" << std::endl; }

// POW

void PowerCommand::performOperation(Program& program) const { program.stack.pow(); }

void PowerCommand::print(std::ostream& os) const { os << "POW" << std::endl; }

// DUP

void DuplicationCommand::performOperation(Program& program) const { program.stack.dup(); }

void DuplicationCommand::print(std::ostream& os) const { os << "DUP" << std::endl; }

// SWAP

void SwapCommand::performOperation(Program& program) const { program.stack.swap(); }

void SwapCommand::print(std::ostream& os) const { os << "SWAP" << std::endl; }