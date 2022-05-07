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
    PushCommand(std::unique_ptr<Value> val) : value(std::move(val)) {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class ReadCommand : public Command {
    int address;

public:
    ReadCommand(int adr) : address(adr) {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class WriteCommand : public Command {
    int address;

public:
    WriteCommand(int adr) : address(adr) {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class JumpCommand : public Command {
    int address;

public:
    JumpCommand(int adr) : address(adr) {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class JumpZeroCommand : public Command {
    int address;

public:
    JumpZeroCommand(int adr) : address(adr) {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class JumpNotZeroCommand : public Command {
    int address;

public:
    JumpNotZeroCommand(int adr) : address(adr) {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class CallCommand : public Command {
    int address;

public:
    CallCommand(int adr) : address(adr) {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class ReturnCommand : public Command {
public:
    ReturnCommand() {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class AdditionCommand : public Command {
public:
    AdditionCommand() {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class SubtractionCommand : public Command {
public:
    SubtractionCommand() {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class MultiplicationCommand : public Command {
public:
    MultiplicationCommand() {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class DivisionCommand : public Command {
public:
    DivisionCommand() {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class PowerCommand : public Command {
public:
    PowerCommand() {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class DuplicationCommand : public Command {
public:
    DuplicationCommand() {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};

class SwapCommand : public Command {
public:
    SwapCommand() {}

    virtual void performOperation(Program& program) const override;
    virtual void print(std::ostream& os) const override;
};