#include <memory/memory.h>
#include <value/value.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <sstream>

TEST_CASE("Check if empty is printed correctly - int", "memory-int") {
    Memory<int> memory;

    std::stringstream ss;

    ss << memory;
    REQUIRE(ss.str() == "_____________________\n_____________________\n");
}

TEST_CASE("Check if with one item is printed correctly - int", "memory-int") {
    Memory<int> memory;
    memory.push_back(1);

    std::stringstream ss;

    ss << memory;
    REQUIRE(ss.str() == "_____________________\n|  0              1 |\n_____________________\n");
}

TEST_CASE("Check if with multiple items is printed correctly - int", "memory-int") {
    Memory<int> memory;
    memory.push_back(1);
    memory.push_back(2);
    memory.push_back(3);

    std::stringstream ss;

    ss << memory;
    REQUIRE(ss.str() ==
            "_____________________\n|  0              1 |\n"
            "|  1              2 |\n|  2              3 |\n"
            "_____________________\n");
}

TEST_CASE("Check if empty is printed correctly - value", "memory-value") {
    Memory<std::unique_ptr<Value>> memory;

    std::stringstream ss;

    ss << memory;
    REQUIRE(ss.str() == "_____________________\n_____________________\n");
}

TEST_CASE("Check if with one item is printed correctly - value", "memory-value") {
    Memory<std::unique_ptr<Value>> memory;
    memory.push_back(std::make_unique<Fraction>(Fraction(1)));

    std::stringstream ss;

    ss << memory;
    REQUIRE(ss.str() == "_____________________\n|  0              1 |\n_____________________\n");
}

TEST_CASE("Check if with multiple items is printed correctly - value", "memory-value") {
    Memory<std::unique_ptr<Value>> memory;
    memory.push_back(std::make_unique<Fraction>(Fraction(1)));
    memory.push_back(std::make_unique<Fraction>(Fraction(2)));
    memory.push_back(std::make_unique<Fraction>(Fraction(3)));

    std::stringstream ss;

    ss << memory;
    REQUIRE(ss.str() ==
            "_____________________\n|  0              1 |\n"
            "|  1              2 |\n|  2              3 |\n"
            "_____________________\n");
}

TEST_CASE("Check if nullptr items are printed correctly - value", "memory-value") {
    Memory<std::unique_ptr<Value>> memory;
    memory.push_back(std::make_unique<Fraction>(Fraction(1)));
    memory.push_back(nullptr);
    memory.push_back(std::make_unique<Fraction>(Fraction(3)));

    std::stringstream ss;

    ss << memory;
    REQUIRE(ss.str() ==
            "_____________________\n|  0              1 |\n"
            "|  1                |\n|  2              3 |\n"
            "_____________________\n");
}