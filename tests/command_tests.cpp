#include <command/command.h>
#include <program/program.h>
#include <value/value.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <sstream>

// PUSH

TEST_CASE("Check if PUSH is printed correctly", "command") {
    PushCommand command(std::make_unique<Fraction>(Fraction(1)));
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "PUSH 1\n");
}

TEST_CASE("Check if PUSH works correctly", "command") {
    Program program;
    PushCommand command(std::make_unique<Fraction>(Fraction(1)));

    REQUIRE(program.stack.size() == 0);
    command.performOperation(program);
    REQUIRE(program.stack.size() == 1);
    REQUIRE(program.stack.top().value() == 1);
}

// READ

TEST_CASE("Check if READ is printed correctly", "command") {
    ReadCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "READ 1\n");
}

TEST_CASE("Check if READ works correctly", "command") {
    Program program;
    program.memory.push_back(std::make_unique<Fraction>(Fraction(1)));
    ReadCommand command(0);

    REQUIRE(program.stack.size() == 0);
    command.performOperation(program);
    REQUIRE(program.stack.size() == 1);
    REQUIRE(program.stack.top().value() == 1);
}

TEST_CASE("Check if READ nullptr works correctly", "command") {
    Program program;
    program.memory.push_back(nullptr);
    ReadCommand command(0);

    REQUIRE(program.stack.size() == 0);
    REQUIRE_THROWS_AS(command.performOperation(program), std::invalid_argument);
}

// WRITE

TEST_CASE("Check if WRITE is printed correctly", "command") {
    WriteCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "WRITE 1\n");
}

TEST_CASE("Check if WRITE works correctly", "command") {
    Program program;
    program.stack.push(std::make_unique<Fraction>(Fraction(1)));
    WriteCommand command(2);

    REQUIRE(program.memory.size() == 0);
    command.performOperation(program);
    REQUIRE(program.memory.size() == 3);
    REQUIRE(program.memory[2]->value() == 1);
    REQUIRE(program.memory[1] == nullptr);
    REQUIRE(program.memory[0] == nullptr);
}

// JUMP

TEST_CASE("Check if JUMP is printed correctly", "command") {
    JumpCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "JUMP 1\n");
}

TEST_CASE("Check if JUMP works correctly", "command") {
    Program program;
    JumpCommand command(4);

    REQUIRE(program.instruction == 0);
    command.performOperation(program);
    // Note: Line count starts from 1, but instructions are indexed from 0
    REQUIRE(program.instruction == 3);
}

// JUMP_ZERO

TEST_CASE("Check if JUMP_ZERO is printed correctly", "command") {
    JumpZeroCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "JUMP_ZERO 1\n");
}

TEST_CASE("Check if JUMP_ZERO works correctly", "command") {
    Program program;
    program.stack.push(std::make_unique<Fraction>(Fraction(1)));
    JumpZeroCommand command(4);

    REQUIRE(program.instruction == 0);
    command.performOperation(program);
    REQUIRE(program.instruction == 0);

    program.stack.push(std::make_unique<Fraction>(Fraction(0)));
    command.performOperation(program);
    // Note: Line count starts from 1, but instructions are indexed from 0
    REQUIRE(program.instruction == 3);
}

TEST_CASE("Check if JUMP_ZERO on empty stack works correctly", "command") {
    Program program;
    JumpZeroCommand command(4);

    REQUIRE_THROWS_AS(command.performOperation(program), std::out_of_range);
}

// JUMP_NOT_ZERO

TEST_CASE("Check if JUMP_NOT_ZERO is printed correctly", "command") {
    JumpNotZeroCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "JUMP_NOT_ZERO 1\n");
}

TEST_CASE("Check if JUMP_NOT_ZERO works correctly", "command") {
    Program program;
    program.stack.push(std::make_unique<Fraction>(Fraction(1)));
    JumpNotZeroCommand command(4);

    REQUIRE(program.instruction == 0);
    command.performOperation(program);
    // Note: Line count starts from 1, but instructions are indexed from 0
    REQUIRE(program.instruction == 3);

    program.stack.push(std::make_unique<Fraction>(Fraction(0)));
    command.performOperation(program);
    REQUIRE(program.instruction == 3);
}

TEST_CASE("Check if JUMP_NOT_ZERO on empty stack works correctly", "command") {
    Program program;
    JumpNotZeroCommand command(4);

    REQUIRE_THROWS_AS(command.performOperation(program), std::out_of_range);
}

// CALL

TEST_CASE("Check if CALL is printed correctly", "command") {
    CallCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "CALL 1\n");
}

TEST_CASE("Check if CALL works correctly", "command") {
    Program program;
    CallCommand command(4);

    REQUIRE(program.instruction == 0);
    command.performOperation(program);
    // Note: Line count starts from 1, but instructions are indexed from 0
    REQUIRE(program.instruction == 3);
    REQUIRE(program.stack.size() == 1);
    REQUIRE(program.stack.top().value() == 0);
}

// RET

TEST_CASE("Check if RET is printed correctly", "command") {
    ReturnCommand command;
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "RET\n");
}

TEST_CASE("Check if RET works correctly", "command") {
    Program program;
    program.stack.push(std::make_unique<Fraction>(Fraction(10)));
    ReturnCommand command;

    REQUIRE(program.instruction == 0);
    command.performOperation(program);
    REQUIRE(program.instruction == 10);
    REQUIRE(program.stack.size() == 0);
}

TEST_CASE("Check if RET on empty stack works correctly", "command") {
    Program program;
    ReturnCommand command;

    REQUIRE_THROWS_AS(command.performOperation(program), std::out_of_range);
}

// ADD

TEST_CASE("Check if ADD is printed correctly", "command") {
    AdditionCommand command;
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "ADD\n");
}

// SUB

TEST_CASE("Check if SUB is printed correctly", "command") {
    SubtractionCommand command;
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "SUB\n");
}

// MUL

TEST_CASE("Check if MUL is printed correctly", "command") {
    MultiplicationCommand command;
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "MUL\n");
}

// DIV

TEST_CASE("Check if DIV is printed correctly", "command") {
    DivisionCommand command;
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "DIV\n");
}

// POW

TEST_CASE("Check if POW is printed correctly", "command") {
    PowerCommand command;
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "POW\n");
}

// DUP

TEST_CASE("Check if DUP is printed correctly", "command") {
    DuplicationCommand command;
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "DUP\n");
}

// SWAP

TEST_CASE("Check if SWAP is printed correctly", "command") {
    SwapCommand command;
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "SWAP\n");
}