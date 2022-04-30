#pragma once

#include <iostream>
#include <memory>

class StackMachine;
class Value;
class Program;

class Command {
public:
    virtual ~Command(){};

    virtual void performOperation(Program& program) const = 0;

    static std::unique_ptr<Command> read(std::istream& is);

    virtual void print(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Command& command);
};

class PushCommand : public Command {
    std::unique_ptr<Value> value;

public:
    PushCommand() {}
    PushCommand(std::unique_ptr<Value> val) : value(std::move(val)) {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class ReadCommand : public Command {
    int address;

public:
    ReadCommand() {}
    ReadCommand(int adr) : address(adr) {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class WriteCommand : public Command {
    int address;

public:
    WriteCommand() {}
    WriteCommand(int adr) : address(adr) {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};