#pragma once
#include <memory>

class Value;
class Fraction;
class Irrational;

class IValueVisitor {
public:
    virtual ~IValueVisitor(){};
    virtual void visit(const Fraction& fraction) = 0;
    virtual void visit(const Irrational& irrational) = 0;
};

//=================================Addition=================================

class IAdditionValueVisitor : virtual public IValueVisitor {
public:
    std::unique_ptr<Value> val;
};

class AdditionFractionVisitor : public IAdditionValueVisitor {
    const Fraction& value_;

public:
    AdditionFractionVisitor(const Fraction& f) : value_(f) {}

    virtual void visit(const Fraction& fraction) override;
    virtual void visit(const Irrational& irrational) override;
};

class AdditionIrrationalVisitor : public IAdditionValueVisitor {
    const Irrational& value_;

public:
    AdditionIrrationalVisitor(const Irrational& i) : value_(i) {}

    virtual void visit(const Fraction& fraction) override;
    virtual void visit(const Irrational& irrational) override;
};

class AdditionValueVisitor : public IAdditionValueVisitor {
    const Value& value_;

public:
    AdditionValueVisitor(const Value& val) : value_(val) {}
    virtual void visit(const Fraction& fraction) override;
    virtual void visit(const Irrational& irrational) override;
};

//=================================Subtraction=================================

class ISubtractionValueVisitor : virtual public IValueVisitor {
public:
    std::unique_ptr<Value> val;
};

class SubtractionFractionVisitor : public ISubtractionValueVisitor {
    const Fraction& value_;

public:
    SubtractionFractionVisitor(const Fraction& f) : value_(f) {}

    virtual void visit(const Fraction& fraction) override;
    virtual void visit(const Irrational& irrational) override;
};

class SubtractionIrrationalVisitor : public ISubtractionValueVisitor {
    const Irrational& value_;

public:
    SubtractionIrrationalVisitor(const Irrational& i) : value_(i) {}

    virtual void visit(const Fraction& fraction) override;
    virtual void visit(const Irrational& irrational) override;
};

class SubtractionValueVisitor : public ISubtractionValueVisitor {
    const Value& value_;

public:
    SubtractionValueVisitor(const Value& val) : value_(val) {}
    virtual void visit(const Fraction& fraction) override;
    virtual void visit(const Irrational& irrational) override;
};