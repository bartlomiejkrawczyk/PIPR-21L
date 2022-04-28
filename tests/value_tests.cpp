#include <math.h>
#include <value/value.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

bool areEqual(double x, double y) {
    return std::fabs(x - y) <= std::numeric_limits<double>::epsilon() * 10;
}

TEST_CASE("Empty Fraction is initiated as zero", "value-fraction") {
    Fraction fraction;
    REQUIRE(fraction.value() == 0);
    REQUIRE(fraction.nominator() == 0);
    REQUIRE(fraction.denominator() == 1);
}

TEST_CASE("Fraction initiated with zero stores zero", "value-fraction") {
    Fraction fraction(0);
    REQUIRE(fraction.value() == 0);
    REQUIRE(fraction.nominator() == 0);
    REQUIRE(fraction.denominator() == 1);
}

TEST_CASE("Fraction initiated as integer stores integer", "value-fraction") {
    Fraction fraction(2);
    REQUIRE(fraction.value() == 2);
    REQUIRE(fraction.nominator() == 2);
    REQUIRE(fraction.denominator() == 1);
}

TEST_CASE("Fraction initiated as negative integer stores negative integer",
          "value-fraction") {
    Fraction fraction(-2);
    REQUIRE(fraction.value() == -2);
    REQUIRE(fraction.nominator() == -2);
    REQUIRE(fraction.denominator() == 1);
}

TEST_CASE("Fraction initiated as fraction stores fraction", "value-fraction") {
    Fraction fraction1(1, 2);
    REQUIRE(fraction1.value() == 0.5);
    REQUIRE(fraction1.nominator() == 1);
    REQUIRE(fraction1.denominator() == 2);

    Fraction fraction2(2, 3);
    REQUIRE(fraction2.value() == 2.0 / 3.0);
    REQUIRE(fraction2.nominator() == 2);
    REQUIRE(fraction2.denominator() == 3);
}

TEST_CASE(
    "Fraction initiated with negative and positive integer stores negative "
    "fraction",
    "value-fraction") {
    Fraction fraction1(-1, 2);
    REQUIRE(fraction1.value() == -0.5);
    REQUIRE(fraction1.nominator() == -1);
    REQUIRE(fraction1.denominator() == 2);

    Fraction fraction2(-5, 2);
    REQUIRE(fraction2.value() == -2.5);
    REQUIRE(fraction2.nominator() == -5);
    REQUIRE(fraction2.denominator() == 2);

    Fraction fraction3(5, -2);
    REQUIRE(fraction3.value() == -2.5);
    REQUIRE(fraction3.nominator() == -5);
    REQUIRE(fraction3.denominator() == 2);
}

TEST_CASE(
    "Fraction initiated with two negative integers stores positive fraction",
    "value-fraction") {
    Fraction fraction(-1, -2);
    REQUIRE(fraction.value() == 0.5);
}

TEST_CASE("Fraction initiated with denominator equal to zero throws error",
          "value-fraction") {
    REQUIRE_THROWS_AS(Fraction(1, 0), std::domain_error);
}

TEST_CASE(
    "Fraction initiated with two integers with common divisor are reduced",
    "value-fraction") {
    Fraction fraction(9, 6);
    REQUIRE(fraction.value() == 1.5);
    REQUIRE(fraction.nominator() == 3);
    REQUIRE(fraction.denominator() == 2);
}

TEST_CASE("Fraction initiated with zero and an integer is reduced to 0/1",
          "value-fraction") {
    Fraction fraction(0, 10);
    REQUIRE(fraction.value() == 0.0);
    REQUIRE(fraction.nominator() == 0);
    REQUIRE(fraction.denominator() == 1);
}

// ===================================================================

TEST_CASE("Empty Irrational is initiated as zero", "value-irrational") {
    Irrational irrational;
    REQUIRE(irrational.value() == 0);
}

TEST_CASE("Irrational initiated as zero is equal zero", "value-irrational") {
    Irrational irrational(0);
    REQUIRE(irrational.value() == 0);
}

TEST_CASE(
    "Irrational initiated with positive double is equal to positive double",
    "value-irrational") {
    Irrational irrational(2.5);
    REQUIRE(irrational.value() == 2.5);
}

TEST_CASE(
    "Irrational initiated with negative double is equal to negative double",
    "value-irrational") {
    Irrational irrational(-2.5);
    REQUIRE(irrational.value() == -2.5);
}