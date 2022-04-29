#include "value.h"

#include <numeric>
#include <sstream>
#include <string>

#include "value_visitor.h"

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

// Addition

std::unique_ptr<Value> Value::operator+(const Value& other) const {
    AdditionValueVisitor additionVisitor(*this);
    other.accept(additionVisitor);
    return std::move(additionVisitor.val);
}

// Subtraction

std::unique_ptr<Value> Value::operator-(const Value& other) const {
    SubtractionValueVisitor subtractionVisitor(*this);
    other.accept(subtractionVisitor);
    return std::move(subtractionVisitor.val);
}

// Multiplication

std::unique_ptr<Value> Value::operator*(const Value& other) const {
    MultiplicationValueVisitor multiplicationVisitor(*this);
    other.accept(multiplicationVisitor);
    return std::move(multiplicationVisitor.val);
}

// Division

std::unique_ptr<Value> Value::operator/(const Value& other) const {
    DivisionValueVisitor divisionVisitor(*this);
    other.accept(divisionVisitor);
    return std::move(divisionVisitor.val);
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

double Fraction::value() const { return (double)nominator_ / (double)denominator_; }

int Fraction::nominator() const { return nominator_; }
int Fraction::denominator() const { return denominator_; }

Fraction::Fraction(int nominator, int denominator) { initializeFraction(nominator, denominator); }

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
        os << nominator_ / denominator_ << "_" << std::abs(nominator_) % denominator_ << "/"
           << denominator_;
    } else {
        os << nominator_ << "/" << denominator_;
    }
}

// Addition

void Fraction::accept(IAdditionValueVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Value> Fraction::operator+(const Fraction& other) const {
    int nominator = 0;
    int denominator = 0;

    nominator = nominator_ * other.denominator() + other.nominator() * denominator_;

    denominator = denominator_ * other.denominator();

    return std::make_unique<Fraction>(Fraction(nominator, denominator));
}

std::unique_ptr<Value> Fraction::operator+(const Irrational& other) const {
    return std::make_unique<Irrational>(Irrational(value() + other.value()));
}

// Subtraction

void Fraction::accept(ISubtractionValueVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Value> Fraction::operator-(const Fraction& other) const {
    int nominator = 0;
    int denominator = 0;

    nominator = nominator_ * other.denominator() - other.nominator() * denominator_;

    denominator = denominator_ * other.denominator();

    return std::make_unique<Fraction>(Fraction(nominator, denominator));
}

std::unique_ptr<Value> Fraction::operator-(const Irrational& other) const {
    return std::make_unique<Irrational>(Irrational(value() - other.value()));
}

// Multiplication

void Fraction::accept(IMultiplicationValueVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Value> Fraction::operator*(const Fraction& other) const {
    int nominator = 0;
    int denominator = 0;

    nominator = nominator_ * other.nominator();

    denominator = denominator_ * other.denominator();

    return std::make_unique<Fraction>(Fraction(nominator, denominator));
}

std::unique_ptr<Value> Fraction::operator*(const Irrational& other) const {
    return std::make_unique<Irrational>(Irrational(value() * other.value()));
}

// Division

void Fraction::accept(IDivisionValueVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Value> Fraction::operator/(const Fraction& other) const {
    int nominator = 0;
    int denominator = 0;

    nominator = nominator_ * other.denominator();

    denominator = denominator_ * other.nominator();

    return std::make_unique<Fraction>(Fraction(nominator, denominator));
}

std::unique_ptr<Value> Fraction::operator/(const Irrational& other) const {
    return std::make_unique<Irrational>(
        Irrational((double)nominator() / (double)denominator() / other.value()));
}

/*=======================================IRRATIONAL=======================================*/

std::istream& operator>>(std::istream& is, Irrational& val) {
    is >> val.value_;
    return is;
}

double Irrational::value() const { return value_; }

void Irrational::print(std::ostream& os) const { os << value_; }

// Addition

void Irrational::accept(IAdditionValueVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Value> Irrational::operator+(const Fraction& other) const {
    return std::make_unique<Irrational>(Irrational(value() + other.value()));
}

std::unique_ptr<Value> Irrational::operator+(const Irrational& other) const {
    return std::make_unique<Irrational>(Irrational(value() + other.value()));
}

// Subtraction

void Irrational::accept(ISubtractionValueVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Value> Irrational::operator-(const Fraction& other) const {
    return std::make_unique<Irrational>(Irrational(value() - other.value()));
}

std::unique_ptr<Value> Irrational::operator-(const Irrational& other) const {
    return std::make_unique<Irrational>(Irrational(value() - other.value()));
}

// Multiplication

void Irrational::accept(IMultiplicationValueVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Value> Irrational::operator*(const Fraction& other) const {
    return std::make_unique<Irrational>(Irrational(value() * other.value()));
}

std::unique_ptr<Value> Irrational::operator*(const Irrational& other) const {
    return std::make_unique<Irrational>(Irrational(value() * other.value()));
}

// Division

void Irrational::accept(IDivisionValueVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Value> Irrational::operator/(const Fraction& other) const {
    return std::make_unique<Irrational>(Irrational(value() / other.value()));
}

std::unique_ptr<Value> Irrational::operator/(const Irrational& other) const {
    return std::make_unique<Irrational>(Irrational(value() / other.value()));
}