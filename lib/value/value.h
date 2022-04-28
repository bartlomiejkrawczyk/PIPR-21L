#pragma once

#include <iostream>
#include <memory>

/*=======================================VALUE=======================================*/

class Value {
public:
    Value(){};
    virtual ~Value(){};

    virtual double value() const = 0;

    // virtual std::unique_ptr<Value> operator+(Value const& other) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Value& val);
    virtual void print(std::ostream& os) const = 0;

    static std::unique_ptr<Value> read(std::istream& is);
};

/*=======================================FRACTION=======================================*/

class Fraction : public Value {
private:
    int nominator_, denominator_;

public:
    Fraction(int nominator = 0, int denominator = 1);

    virtual double value() const override;

    int nominator() const;
    int denominator() const;

    virtual void print(std::ostream& os) const override;

    friend std::istream& operator>>(std::istream& is, Fraction& val);

private:
    void initializeFraction(int nominator, int denominator);
};

/*=======================================IRRATIONAL=======================================*/

class Irrational : public Value {
private:
    double value_;

public:
    Irrational(double value = 0.0) : value_(value) {}

    virtual double value() const override;

    void print(std::ostream& os) const;

    friend std::istream& operator>>(std::istream& is, Irrational& val);
};