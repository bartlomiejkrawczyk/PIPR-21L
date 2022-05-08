#include <debugger/debugger.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <sstream>

TEST_CASE("Debugger displays state correctly", "debugger") {
    Program program;
    Debugger debugger(&program);

    std::stringstream ss;

    debugger.displayState(ss);
    REQUIRE(ss.str() ==
            "Stack:\n___________________\nMemory:\n_____________________\n_____________________\n");
}

TEST_CASE("Debugger steps by program correctly", "debugger") {
    Program program;
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(1)))));
    Debugger debugger(&program);

    std::stringstream ss1;
    std::stringstream ss2;
    REQUIRE(program.instruction == 0);
    debugger.step(ss1);
    REQUIRE(program.stack.top().value() == 1);
    REQUIRE(program.stack.size() == 1);
    REQUIRE(program.instruction == 1);
    REQUIRE(ss1.str() == "Instruction:\n1) PUSH 1\n");
    debugger.step(ss2);
    REQUIRE(ss2.str() == "Program has ended!\nTry \"restart\"\n");
}

TEST_CASE("Debugger handles exceptions correctly", "debugger") {
    Program program;
    program.addInstruction(std::make_unique<WriteCommand>(WriteCommand(0)));
    Debugger debugger(&program);

    std::stringstream ss;
    REQUIRE(program.instruction == 0);
    debugger.step(ss);
    REQUIRE(ss.str() ==
            "Instruction:\n1) WRITE 0\nThe instruction was stopped during execution:\nEmpty "
            "Stack!\n");
}

TEST_CASE("Debugger runs program correctly", "debugger") {
    Program program;
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(1)))));
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(2)))));
    Debugger debugger(&program);

    std::stringstream ss;
    REQUIRE(program.instruction == 0);
    debugger.run(ss);
    REQUIRE(program.stack.top().value() == 2);
    REQUIRE(program.stack.size() == 2);
    REQUIRE(program.instruction == 2);
}

TEST_CASE("Debugger restarts program correctly", "debugger") {
    Program program;
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(1)))));
    program.addInstruction(
        std::make_unique<PushCommand>(PushCommand(std::make_unique<Fraction>(Fraction(2)))));
    program.addInstruction(std::make_unique<WriteCommand>(WriteCommand(0)));
    Debugger debugger(&program);

    std::stringstream ss;
    debugger.run(ss);
    REQUIRE(program.stack.size() == 2);
    REQUIRE(program.memory.size() == 1);
    REQUIRE(program.instruction == 3);
    debugger.restart();
    REQUIRE(program.stack.size() == 0);
    REQUIRE(program.memory.size() == 0);
    REQUIRE(program.instruction == 0);
}