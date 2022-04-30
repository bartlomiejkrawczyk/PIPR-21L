#pragma once

#include <iostream>
#include <memory>
#include <vector>

class Value;

class Memory : public std::vector<std::unique_ptr<Value>> {
public:
    friend std::ostream& operator<<(std::ostream& os, const Memory& memory);
};