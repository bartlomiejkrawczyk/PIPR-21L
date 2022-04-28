#pragma once

#include <iostream>
#include <memory>

class Value {
public:
    Value(){};
    virtual ~Value(){};

    virtual double value() const = 0;
};

class Fraction : public Value {
private:
    int nominator_, denominator_;

public:
    Fraction(int nominator = 0, int denominator = 1);

    virtual double value() const override;

    int nominator() const;
    int denominator() const;

private:
    void initializeFraction(int nominator, int denominator);
};

class Irrational : public Value {
private:
    double value_;

public:
    Irrational(double value = 0.0) : value_(value) {}
    virtual double value() const override;
};