#include "operations.h"

#include <value/value.h>

std::unique_ptr<Value> addition(Value const& a, Value const& b) { return a + b; }

std::unique_ptr<Value> subtraction(Value const& a, Value const& b) { return a - b; }

std::unique_ptr<Value> multiplication(Value const& a, Value const& b) { return a * b; }

std::unique_ptr<Value> division(Value const& a, Value const& b) {
    if (b.value() == 0.0) throw std::domain_error("Zero division Error!");
    return a / b;
}

std::unique_ptr<Value> power(Value const& a, Value const& b) {
    if (a.value() < 0) {
        int b_val = (int)b.value();
        if ((double)b_val != b.value())
            throw std::domain_error("Negative number to power of a fraction!");
    }
    return a.power(b);
}
