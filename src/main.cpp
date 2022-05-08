#include <program/program.h>

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::ifstream file(argv[argc - 1]);

        Program program;
        file >> program;

        file.close();

        std::string arg = argv[1];

        if (arg.compare("-d") == 0) {
            Debugger debugger(&program);

            debugger.interaction();

        } else {
            program.run();
            std::cout << program;
        }

    } else {
        std::cerr << "Usage:\n" << argv[0] << " [-d] FILE" << std::endl;
    }
    return 0;
}