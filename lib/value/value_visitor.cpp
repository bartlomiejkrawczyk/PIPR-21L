#include "value_visitor.h"

#include "value.h"

void FractionVisitor::visitAddition(const Fraction& fraction) {
    val = std::move(value_ + fraction);
}

void FractionVisitor::visitAddition(const Irrational& irrational) {
    val = std::move(value_ + irrational);
}

void IrrationalVisitor::visitAddition(const Fraction& fraction) {
    val = std::move(value_ + fraction);
}
void IrrationalVisitor::visitAddition(const Irrational& irrational) {
    val = std::move(value_ + irrational);
}

void AdditionVisitor::visitAddition(const Fraction& fraction) {
    FractionVisitor fractionVisitor(fraction);
    value_.acceptAddition(fractionVisitor);
    val = std::move(fractionVisitor.val);
}
void AdditionVisitor::visitAddition(const Irrational& irrational) {
    IrrationalVisitor irrationalVisitor(irrational);
    value_.acceptAddition(irrationalVisitor);
    val = std::move(irrationalVisitor.val);
}