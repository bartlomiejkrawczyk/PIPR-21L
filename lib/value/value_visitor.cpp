#include "value_visitor.h"

#include "value.h"

//=================================Addition=================================

void AdditionFractionVisitor::visit(const Fraction& fraction) {
    val = std::move(value_ + fraction);
}

void AdditionFractionVisitor::visit(const Irrational& irrational) {
    val = std::move(value_ + irrational);
}

void AdditionIrrationalVisitor::visit(const Fraction& fraction) {
    val = std::move(value_ + fraction);
}
void AdditionIrrationalVisitor::visit(const Irrational& irrational) {
    val = std::move(value_ + irrational);
}

void AdditionValueVisitor::visit(const Fraction& fraction) {
    AdditionFractionVisitor fractionVisitor(fraction);
    value_.accept(fractionVisitor);
    val = std::move(fractionVisitor.val);
}
void AdditionValueVisitor::visit(const Irrational& irrational) {
    AdditionIrrationalVisitor irrationalVisitor(irrational);
    value_.accept(irrationalVisitor);
    val = std::move(irrationalVisitor.val);
}