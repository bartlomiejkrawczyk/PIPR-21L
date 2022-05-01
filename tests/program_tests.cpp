#include <program/program.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <sstream>

TEST_CASE("Check default values of Program", "program") {
    Program program;
    REQUIRE(program.memory.size() == 0);
    REQUIRE(program.stack.size() == 0);
    REQUIRE(program.instruction == 0);
}

TEST_CASE("Check instruction shouldn't increment if no next instruction is available", "program") {
    Program program;
    REQUIRE(program.instruction == 0);
    program.step();
    REQUIRE(program.instruction == 0);
}

TEST_CASE("Check instruction increment after step", "program") {
    Program program;
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(1)))));
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(2)))));
    REQUIRE(program.instruction == 0);
    program.step();
    REQUIRE(program.instruction == 1);
    program.step();
    REQUIRE(program.instruction == 2);
    program.step();
    REQUIRE(program.instruction == 2);
}

TEST_CASE("After program runs instruction should point to the numer of instructions available",
          "program") {
    Program program;
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(1)))));
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(2)))));
    REQUIRE(program.instruction == 0);
    program.run();
    REQUIRE(program.instruction == 2);
}

TEST_CASE("Command call may impact the stack", "program") {
    Program program;
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(1)))));
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(2)))));
    REQUIRE(program.stack.size() == 0);
    program.run();
    REQUIRE(program.stack.size() == 2);
    REQUIRE(program.stack.top().value() == 2);
}

TEST_CASE("Command call may impact the memory", "program") {
    Program program;
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(1)))));
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(2)))));
    program.addInstruction(std::make_unique<WriteCommand>(WriteCommand(0)));
    REQUIRE(program.memory.size() == 0);
    program.run();
    REQUIRE(program.memory.size() == 1);
    REQUIRE(program.memory[0]->value() == 2.0);
}

TEST_CASE("Check if program data is displayed correctly", "program") {
    Program program;
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(1)))));
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(2)))));
    program.addInstruction(std::make_unique<WriteCommand>(WriteCommand(0)));
    program.run();

    std::stringstream ss;
    ss << program;
    REQUIRE(ss.str() ==
            "Stack:\n|               2 |\n|               1 "
            "|\n___________________\nMemory:\n_____________________\n|  0              2 "
            "|\n_____________________\n");
}

TEST_CASE("Check if program is read correctly from stream", "program") {
    Program program;

    std::stringstream ss;
    ss << "PUSH 1" << std::endl;
    ss << "PUSH 2" << std::endl;
    ss << "WRITE 0" << std::endl;

    ss >> program;

    program.run();

    REQUIRE(program.stack.size() == 2);
    REQUIRE(program.stack.top().value() == 2);
    REQUIRE(program.memory.size() == 1);
    REQUIRE(program.memory[0]->value() == 2.0);
}
