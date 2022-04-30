#include <program/program.h>

#include <iostream>
#include <sstream>

int main() {
    Program program;
    std::stringstream ss;

    ss << "PUSH 1_2/5" << std::endl;
    ss << "PUSH 12" << std::endl;
    ss << "PUSH 3.14159265" << std::endl;
    ss << "WRITE 0" << std::endl;
    ss << "READ 0" << std::endl;

    program.addInstruction(Command::read(ss));
    program.addInstruction(Command::read(ss));
    program.addInstruction(Command::read(ss));
    program.addInstruction(Command::read(ss));
    program.addInstruction(Command::read(ss));

    program.run();

    std::cout << program;

    return 0;
}