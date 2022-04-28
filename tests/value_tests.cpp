#include <math.h>
#include <value/value.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <sstream>

bool areEqual(double x, double y) {
    return std::fabs(x - y) <= std::numeric_limits<double>::epsilon() * 10;
}

// Constructor

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

// Print

TEST_CASE("Check if zero fraction is printed correctly", "value-fraction") {
    Fraction fraction(0);
    std::stringstream ss;
    ss << fraction;
    REQUIRE(ss.str() == "0");
}

TEST_CASE("Check if integer fraction is printed correctly", "value-fraction") {
    Fraction fraction1(1);
    std::stringstream ss1;
    ss1 << fraction1;
    REQUIRE(ss1.str() == "1");

    Fraction fraction2(2);
    std::stringstream ss2;
    ss2 << fraction2;
    REQUIRE(ss2.str() == "2");
}

TEST_CASE("Check if integer fraction greater than 9 is printed correctly",
          "value-fraction") {
    Fraction fraction10(10);
    std::stringstream ss10;
    ss10 << fraction10;
    REQUIRE(ss10.str() == "10");

    Fraction fraction100(100);
    std::stringstream ss100;
    ss100 << fraction100;
    REQUIRE(ss100.str() == "100");
}

TEST_CASE("Check if negative integer fraction is printed correctly",
          "value-fraction") {
    Fraction fraction1(-1);
    std::stringstream ss1;
    ss1 << fraction1;
    REQUIRE(ss1.str() == "-1");

    Fraction fraction2(-2);
    std::stringstream ss2;
    ss2 << fraction2;
    REQUIRE(ss2.str() == "-2");
}

TEST_CASE(
    "Check if negative integer fraction smaller than -9 is printed correctly",
    "value-fraction") {
    Fraction fraction10(-10);
    std::stringstream ss10;
    ss10 << fraction10;
    REQUIRE(ss10.str() == "-10");

    Fraction fraction100(-100);
    std::stringstream ss100;
    ss100 << fraction100;
    REQUIRE(ss100.str() == "-100");
}

TEST_CASE("Check if fraction is printed correctly", "value-fraction") {
    Fraction fraction1(1, 2);
    std::stringstream ss1;
    ss1 << fraction1;
    REQUIRE(ss1.str() == "1/2");

    Fraction fraction2(2, 5);
    std::stringstream ss2;
    ss2 << fraction2;
    REQUIRE(ss2.str() == "2/5");
}

TEST_CASE("Check if fraction with multiple digits is printed correctly",
          "value-fraction") {
    Fraction fraction10(10, 11);
    std::stringstream ss10;
    ss10 << fraction10;
    REQUIRE(ss10.str() == "10/11");

    Fraction fraction100(100, 111);
    std::stringstream ss100;
    ss100 << fraction100;
    REQUIRE(ss100.str() == "100/111");
}

TEST_CASE("Check if negative fraction is printed correctly", "value-fraction") {
    Fraction fraction1(-1, 2);
    std::stringstream ss1;
    ss1 << fraction1;
    REQUIRE(ss1.str() == "-1/2");

    Fraction fraction2(2, -5);
    std::stringstream ss2;
    ss2 << fraction2;
    REQUIRE(ss2.str() == "-2/5");
}

TEST_CASE(
    "Check if negative fraction with multiple digits is printed correctly",
    "value-fraction") {
    Fraction fraction10(-10, 11);
    std::stringstream ss10;
    ss10 << fraction10;
    REQUIRE(ss10.str() == "-10/11");

    Fraction fraction100(100, -111);
    std::stringstream ss100;
    ss100 << fraction100;
    REQUIRE(ss100.str() == "-100/111");
}

TEST_CASE("Check if fraction greater than 1 is printed correctly",
          "value-fraction") {
    Fraction fraction1(3, 2);
    std::stringstream ss1;
    ss1 << fraction1;
    REQUIRE(ss1.str() == "1_1/2");

    Fraction fraction2(14, 5);
    std::stringstream ss2;
    ss2 << fraction2;
    REQUIRE(ss2.str() == "2_4/5");
}

TEST_CASE(
    "Check if fraction greater than 1 with multiple digits is printed "
    "correctly",
    "value-fraction") {
    Fraction fraction10(21, 11);
    std::stringstream ss10;
    ss10 << fraction10;
    REQUIRE(ss10.str() == "1_10/11");

    Fraction fraction100(3000, 111);
    std::stringstream ss100;
    ss100 << fraction100;
    REQUIRE(ss100.str() == "27_1/37");
}

TEST_CASE("Check if negative fraction smaller than -1 is printed correctly",
          "value-fraction") {
    Fraction fraction1(-3, 2);
    std::stringstream ss1;
    ss1 << fraction1;
    REQUIRE(ss1.str() == "-1_1/2");

    Fraction fraction2(7, -5);
    std::stringstream ss2;
    ss2 << fraction2;
    REQUIRE(ss2.str() == "-1_2/5");
}

TEST_CASE(
    "Check if negative fraction smaller than -1 with multiple digits is "
    "printed correctly",
    "value-fraction") {
    Fraction fraction10(-32, 11);
    std::stringstream ss10;
    ss10 << fraction10;
    REQUIRE(ss10.str() == "-2_10/11");

    Fraction fraction100(1127, -111);
    std::stringstream ss100;
    ss100 << fraction100;
    REQUIRE(ss100.str() == "-10_17/111");
}

// Read

TEST_CASE("Check if zero fraction loads from stream", "value-fraction") {
    std::stringstream ss;
    ss << "0";
    std::unique_ptr<Value> val = std::move(Value::read(ss));
    Fraction* fraction = dynamic_cast<Fraction*>(val.get());
    REQUIRE(fraction != nullptr);
    REQUIRE(fraction->nominator() == 0);
    REQUIRE(fraction->denominator() == 1);
}

TEST_CASE("Check if integer fraction loads from stream", "value-fraction") {
    std::stringstream ss;
    ss << "2";
    std::unique_ptr<Value> val = std::move(Value::read(ss));
    Fraction* fraction = dynamic_cast<Fraction*>(val.get());
    REQUIRE(fraction != nullptr);
    REQUIRE(fraction->nominator() == 2);
    REQUIRE(fraction->denominator() == 1);
}

TEST_CASE("Check if integer fraction greater than 9 loads from stream",
          "value-fraction") {
    std::stringstream ss;
    ss << "10";
    std::unique_ptr<Value> val = std::move(Value::read(ss));
    Fraction* fraction = dynamic_cast<Fraction*>(val.get());
    REQUIRE(fraction != nullptr);
    REQUIRE(fraction->nominator() == 10);
    REQUIRE(fraction->denominator() == 1);
}

TEST_CASE("Check if negative integer fraction loads from stream",
          "value-fraction") {
    std::stringstream ss;
    ss << "-2";
    std::unique_ptr<Value> val = std::move(Value::read(ss));
    Fraction* fraction = dynamic_cast<Fraction*>(val.get());
    REQUIRE(fraction != nullptr);
    REQUIRE(fraction->nominator() == -2);
    REQUIRE(fraction->denominator() == 1);
}

TEST_CASE("Check if fraction loads from stream", "value-fraction") {
    std::stringstream ss;
    ss << "1/2";
    std::unique_ptr<Value> val = std::move(Value::read(ss));
    Fraction* fraction = dynamic_cast<Fraction*>(val.get());
    REQUIRE(fraction != nullptr);
    REQUIRE(fraction->nominator() == 1);
    REQUIRE(fraction->denominator() == 2);
}

TEST_CASE("Check if fraction greater than 1 loads from stream",
          "value-fraction") {
    std::stringstream ss;
    ss << "3_1/2";
    std::unique_ptr<Value> val = std::move(Value::read(ss));
    Fraction* fraction = dynamic_cast<Fraction*>(val.get());
    REQUIRE(fraction != nullptr);
    REQUIRE(fraction->nominator() == 7);
    REQUIRE(fraction->denominator() == 2);
}

TEST_CASE("Check if fraction greater than 10 loads from stream",
          "value-fraction") {
    std::stringstream ss;
    ss << "27_11/79";
    std::unique_ptr<Value> val = std::move(Value::read(ss));
    Fraction* fraction = dynamic_cast<Fraction*>(val.get());
    REQUIRE(fraction != nullptr);
    REQUIRE(fraction->nominator() == 2144);
    REQUIRE(fraction->denominator() == 79);
}

TEST_CASE("Check if negative fraction smaller than -10 loads from stream",
          "value-fraction") {
    std::stringstream ss;
    ss << "-27_11/79";
    std::unique_ptr<Value> val = std::move(Value::read(ss));
    Fraction* fraction = dynamic_cast<Fraction*>(val.get());
    REQUIRE(fraction != nullptr);
    REQUIRE(fraction->nominator() == -2144);
    REQUIRE(fraction->denominator() == 79);
}

// ===================================================================================

// Constructor

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

// Print

TEST_CASE("Check if zero irrational is printed correctly", "value-irrational") {
    Irrational irrational(0);
    std::stringstream ss;
    ss << irrational;
    REQUIRE(ss.str() == "0");
}

TEST_CASE("Check if integer irrational is printed correctly",
          "value-irrational") {
    Irrational irrational1(1);
    std::stringstream ss1;
    ss1 << irrational1;
    REQUIRE(ss1.str() == "1");

    Irrational irrational2(2);
    std::stringstream ss2;
    ss2 << irrational2;
    REQUIRE(ss2.str() == "2");
}

TEST_CASE("Check if integer irrational greater than 9 is printed correctly",
          "value-irrational") {
    Irrational irrational10(10);
    std::stringstream ss10;
    ss10 << irrational10;
    REQUIRE(ss10.str() == "10");

    Irrational irrational100(100);
    std::stringstream ss100;
    ss100 << irrational100;
    REQUIRE(ss100.str() == "100");
}

TEST_CASE("Check if negative integer irrational is printed correctly",
          "value-irrational") {
    Irrational irrational1(-1);
    std::stringstream ss1;
    ss1 << irrational1;
    REQUIRE(ss1.str() == "-1");

    Irrational irrational2(-2);
    std::stringstream ss2;
    ss2 << irrational2;
    REQUIRE(ss2.str() == "-2");
}

TEST_CASE(
    "Check if negative integer irrational smaller than -9 is printed correctly",
    "value-irrational") {
    Irrational irrational10(-10);
    std::stringstream ss10;
    ss10 << irrational10;
    REQUIRE(ss10.str() == "-10");

    Irrational irrational100(-100);
    std::stringstream ss100;
    ss100 << irrational100;
    REQUIRE(ss100.str() == "-100");
}

TEST_CASE("Check if double irrational is printed correctly",
          "value-irrational") {
    Irrational irrational1(1.5);
    std::stringstream ss1;
    ss1 << irrational1;
    REQUIRE(ss1.str() == "1.5");

    Irrational irrational2(2.7);
    std::stringstream ss2;
    ss2 << irrational2;
    REQUIRE(ss2.str() == "2.7");
}

TEST_CASE("Check if double irrational greater than 9 is printed correctly",
          "value-irrational") {
    Irrational irrational10(10.6);
    std::stringstream ss10;
    ss10 << irrational10;
    REQUIRE(ss10.str() == "10.6");

    Irrational irrational100(100.12);
    std::stringstream ss100;
    ss100 << irrational100;
    REQUIRE(ss100.str() == "100.12");
}

TEST_CASE("Check if negative double irrational is printed correctly",
          "value-irrational") {
    Irrational irrational1(-1.5);
    std::stringstream ss1;
    ss1 << irrational1;
    REQUIRE(ss1.str() == "-1.5");

    Irrational irrational2(-2.7);
    std::stringstream ss2;
    ss2 << irrational2;
    REQUIRE(ss2.str() == "-2.7");
}

TEST_CASE(
    "Check if negative double irrational smaller than -9 is printed correctly",
    "value-irrational") {
    Irrational irrational10(-10.6);
    std::stringstream ss10;
    ss10 << irrational10;
    REQUIRE(ss10.str() == "-10.6");

    Irrational irrational100(-100.12);
    std::stringstream ss100;
    ss100 << irrational100;
    REQUIRE(ss100.str() == "-100.12");
}

TEST_CASE("Check if irrational loads from stream", "value-irrational") {
    std::stringstream ss;
    ss << "0.5";
    std::unique_ptr<Value> val = std::move(Value::read(ss));
    Irrational* irrational = dynamic_cast<Irrational*>(val.get());
    REQUIRE(irrational != nullptr);
    REQUIRE(irrational->value() == 0.5);
}

TEST_CASE("Check if negative irrational loads from stream",
          "value-irrational") {
    std::stringstream ss;
    ss << "-100.5";
    std::unique_ptr<Value> val = std::move(Value::read(ss));
    Irrational* irrational = dynamic_cast<Irrational*>(val.get());
    REQUIRE(irrational != nullptr);
    REQUIRE(irrational->value() == -100.5);
}