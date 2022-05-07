#include <command/command.h>
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

// READ

TEST_CASE("Check if READ is printed correctly", "command") {
    ReadCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "READ 1\n");
}

// WRITE

TEST_CASE("Check if WRITE is printed correctly", "command") {
    WriteCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "WRITE 1\n");
}

// JUMP

TEST_CASE("Check if JUMP is printed correctly", "command") {
    JumpCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "JUMP 1\n");
}

// JUMP_ZERO

TEST_CASE("Check if JUMP_ZERO is printed correctly", "command") {
    JumpZeroCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "JUMP_ZERO 1\n");
}

// JUMP_NOT_ZERO

TEST_CASE("Check if JUMP_NOT_ZERO is printed correctly", "command") {
    JumpNotZeroCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "JUMP_NOT_ZERO 1\n");
}

// CALL

TEST_CASE("Check if CALL is printed correctly", "command") {
    CallCommand command(1);
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "CALL 1\n");
}

// RET

TEST_CASE("Check if RET is printed correctly", "command") {
    ReturnCommand command;
    std::stringstream ss;

    ss << command;

    REQUIRE(ss.str() == "RET\n");
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