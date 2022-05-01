#include <program/program.h>

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::ifstream file(argv[1]);

        Program program;
        file >> program;

        file.close();

        program.run();

        std::cout << program;
    } else {
        std::cerr << "Usage:\n" << argv[0] << " FILE" << std::endl;
    }
    return 0;
}