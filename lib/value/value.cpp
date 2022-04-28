#include "value.h"

#include <numeric>
#include <sstream>
#include <string>

/*=======================================VALUE=======================================*/

std::ostream& operator<<(std::ostream& os, const Value& val) {
    val.print(os);
    return os;
}

std::unique_ptr<Value> Value::read(std::istream& is) {
    std::string str;
    is >> str;
    if (str.find('.') != std::string::npos) {
        // Contains . so it is Irrational
        std::stringstream ss;

        ss << str;
        Irrational irrational;
        ss >> irrational;

        return std::make_unique<Irrational>(irrational);
    } else {
        std::stringstream ss;

        ss << str;
        Fraction fraction;
        ss >> fraction;

        return std::make_unique<Fraction>(fraction);
    }
}

/*=======================================FRACTION=======================================*/

std::istream& operator>>(std::istream& is, Fraction& val) {
    int a = 0, b = 0, c = 1;
    is >> a;
    char chr;
    if (is.peek() == '_') {
        is >> chr >> b;
    }
    if (is.peek() == '/') {
        is >> chr >> c;
    }

    if (b == 0) {
        val.initializeFraction(a, c);
    } else {
        if (a >= 0) {
            val.initializeFraction(a * c + b, c);
        } else {
            val.initializeFraction(a * c - b, c);
        }
    }

    return is;
}

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

std::istream& operator>>(std::istream& is, Irrational& val) {
    is >> val.value_;
    return is;
}

double Irrational::value() const { return value_; }

void Irrational::print(std::ostream& os) const { os << value_; }
