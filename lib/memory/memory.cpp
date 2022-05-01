#include "memory.h"

#include <value/value.h>

#include <iomanip>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const Memory& memory) {
    os << "___________________\n";
    int idx = 0;
    for (auto i = memory.begin(); i != memory.end(); ++i) {
        std::stringstream ss;
        if (*i != nullptr) {
            ss << *(*i);
        }
        os << "| " << std::setw(2) << idx++ << std::setw(15) << ss.str() << " |\n";
    }
    os << "___________________\n";
    return os;
}