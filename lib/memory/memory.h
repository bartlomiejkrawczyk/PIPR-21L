#pragma once

#include <value/value.h>

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

class Value;

template <class T>
class Memory : public std::vector<T> {
public:
    friend std::ostream& operator<<(std::ostream& os, const Memory& memory) {
        os << "_____________________\n";
        int idx = 0;
        for (auto i = memory.begin(); i != memory.end(); ++i) {
            std::stringstream ss;
            ss << *i;
            os << "| " << std::setw(2) << idx++ << std::setw(15) << ss.str() << " |\n";
        }
        os << "_____________________\n";
        return os;
    }
};

template <>
class Memory<std::unique_ptr<Value>> : public std::vector<std::unique_ptr<Value>> {
public:
    friend std::ostream& operator<<(std::ostream& os, const Memory& memory) {
        os << "_____________________\n";
        int idx = 0;
        for (auto i = memory.begin(); i != memory.end(); ++i) {
            std::stringstream ss;
            if (*i != nullptr) {
                ss << *(*i);
            }
            os << "| " << std::setw(2) << idx++ << std::setw(15) << ss.str() << " |\n";
        }
        os << "_____________________\n";
        return os;
    }
};