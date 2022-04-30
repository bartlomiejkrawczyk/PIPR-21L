#include <program/program.h>

#include <iostream>
#include <sstream>

int main() {
    Program program;
    std::stringstream ss;

    ss << "JUMP 2" << std::endl;
    program.addInstruction(Command::read(ss));

    ss << "PUSH 1_2/5" << std::endl;
    program.addInstruction(Command::read(ss));

    ss << "PUSH 12" << std::endl;
    program.addInstruction(Command::read(ss));

    ss << "PUSH 3.14159265" << std::endl;
    program.addInstruction(Command::read(ss));

    ss << "WRITE 1" << std::endl;
    program.addInstruction(Command::read(ss));

    ss << "READ 1" << std::endl;
    program.addInstruction(Command::read(ss));

    program.run();

    std::cout << program;

    return 0;
}