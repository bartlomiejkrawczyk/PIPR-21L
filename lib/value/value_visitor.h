#pragma once
#include <memory>

class Value;
class Fraction;
class Irrational;

class ValueVisitor {
public:
    virtual ~ValueVisitor(){};
    virtual void visitAddition(const Fraction& fraction) = 0;
    virtual void visitAddition(const Irrational& irrational) = 0;
};

class FractionVisitor : public ValueVisitor {
    const Fraction& value_;

public:
    std::unique_ptr<Value> val;

    FractionVisitor(const Fraction& f) : value_(f) {}

    virtual void visitAddition(const Fraction& fraction) override;
    virtual void visitAddition(const Irrational& irrational) override;
};

class IrrationalVisitor : public ValueVisitor {
    const Irrational& value_;

public:
    std::unique_ptr<Value> val;

    IrrationalVisitor(const Irrational& i) : value_(i) {}

    virtual void visitAddition(const Fraction& fraction) override;
    virtual void visitAddition(const Irrational& irrational) override;
};

class AdditionVisitor : public ValueVisitor {
    const Value& value_;

public:
    std::unique_ptr<Value> val;

    AdditionVisitor(const Value& val) : value_(val) {}
    virtual void visitAddition(const Fraction& fraction) override;
    virtual void visitAddition(const Irrational& irrational) override;
};