#pragma once

#include <memory>

class Value;

std::unique_ptr<Value> addition(Value const& a, Value const& b);

std::unique_ptr<Value> subtraction(Value const& a, Value const& b);

std::unique_ptr<Value> multiplication(Value const& a, Value const& b);

std::unique_ptr<Value> division(Value const& a, Value const& b);

std::unique_ptr<Value> power(Value const& a, Value const& b);
