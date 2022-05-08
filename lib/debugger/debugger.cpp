#include "debugger.h"

void Debugger::displayState(std::ostream& os) { os << program; }

void Debugger::run(std::ostream& os) {
    std::function<void()> func = std::bind(&Program::run, &program);
    handleExceptions(os, func);
}

void Debugger::step(std::ostream& os) {
    size_t i = program.instruction;
    if (program.instructions.size() > i) {
        os << "Instruction:" << std::endl;
        printCommand(i, os);
        std::function<void()> func = std::bind(&Program::step, &program);
        handleExceptions(os, func);
    } else {
        os << "Program has ended!\nTry \"restart\"" << std::endl;
    }
}

void Debugger::restart() {
    program.instruction = 0;
    program.stack.clear();
    program.memory.clear();
}

void Debugger::interaction(std::istream& is, std::ostream& os) {
    if (program.instructions.size() == 0) {
        os << "No instruction loaded!" << std::endl;
        return;
    }

    std::string command;

    while (true) {
        os << "> ";
        is >> command;

        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command.compare("help") == 0)
            os << "Available commands:\n"
                  " - help\n"
                  " - run\n"
                  " - step\n"
                  " - display\n"
                  " - instructions\n"
                  " - restart\n"
                  " - exit"
               << std::endl;
        else if (command.compare("run") == 0)
            run(os);
        else if (command.compare("step") == 0) {
            step(os);
        } else if (command.compare("display") == 0)
            displayState(os);
        else if (command.compare("instructions") == 0) {
            for (size_t i = 0; i < program.instructions.size(); ++i) printCommand(i, os);
        } else if (command.compare("restart") == 0)
            restart();
        else if (command.compare("exit") == 0)
            break;
        else {
            os << "Unknown Command!\nTry \"help\" to get list of available commands!" << std::endl;
        };
    };
}

void Debugger::printCommand(size_t i, std::ostream& os) {
    os << i + 1 << ") " << *program.instructions[i];
}

void Debugger::handleExceptions(std::ostream& os, std::function<void()> func) {
    try {
        func();
    } catch (std::exception& e) {
        os << "The instruction was stopped during execution:" << std::endl;
        os << e.what() << std::endl;
    } catch (...) {
        os << "Unexpected exception!";
        throw;
    }
}
