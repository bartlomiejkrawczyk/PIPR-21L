#include "value.h"

#include <numeric>

double Fraction::value() const {
    return (double)nominator_ / (double)denominator_;
}

int Fraction::nominator() const { return nominator_; }
int Fraction::denominator() const { return denominator_; }

Fraction::Fraction(int nominator, int denominator) {
    initializeFraction(nominator, denominator);
}

void Fraction::initializeFraction(int nominator, int denominator) {
    if (denominator == 0) throw std::domain_error("Zero Division Error!");

    int divisor = std::gcd(nominator, denominator);

    if (denominator < 0) {
        nominator = -nominator;
        denominator = -denominator;
    }

    nominator_ = nominator / divisor;
    denominator_ = denominator / divisor;
}

double Irrational::value() const { return value_; }