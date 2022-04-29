#pragma once
#include <memory>

class Value;
class Fraction;
class Irrational;

//=================================Addition=================================

class IAdditionValueVisitor {
public:
    virtual ~IAdditionValueVisitor(){};
    virtual void visit(const Fraction& fraction) = 0;
    virtual void visit(const Irrational& irrational) = 0;
};

class AdditionFractionVisitor : public IAdditionValueVisitor {
    const Fraction& value_;

public:
    std::unique_ptr<Value> val;

    AdditionFractionVisitor(const Fraction& f) : value_(f) {}

    virtual void visit(const Fraction& fraction) override;
    virtual void visit(const Irrational& irrational) override;
};

class AdditionIrrationalVisitor : public IAdditionValueVisitor {
    const Irrational& value_;

public:
    std::unique_ptr<Value> val;

    AdditionIrrationalVisitor(const Irrational& i) : value_(i) {}

    virtual void visit(const Fraction& fraction) override;
    virtual void visit(const Irrational& irrational) override;
};

class AdditionValueVisitor : public IAdditionValueVisitor {
    const Value& value_;

public:
    std::unique_ptr<Value> val;

    AdditionValueVisitor(const Value& val) : value_(val) {}
    virtual void visit(const Fraction& fraction) override;
    virtual void visit(const Irrational& irrational) override;
};