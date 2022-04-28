#include "value.h"

#include <numeric>

/*=======================================VALUE=======================================*/

std::ostream& operator<<(std::ostream& os, const Value& val) {
    val.print(os);
    return os;
}

/*=======================================FRACTION=======================================*/

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

void Fraction::print(std::ostream& os) const {
    if (nominator_ == 0) {
        os << 0;
    } else if (denominator_ == 1) {
        os << nominator_;
    } else if (std::abs(nominator_) > denominator_) {
        os << nominator_ / denominator_ << "_"
           << std::abs(nominator_) % denominator_ << "/" << denominator_;
    } else {
        os << nominator_ << "/" << denominator_;
    }
}

/*=======================================IRRATIONAL=======================================*/

double Irrational::value() const { return value_; }

void Irrational::print(std::ostream& os) const { os << value_; }