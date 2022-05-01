#include <memory/memory.h>
#include <value/value.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <sstream>

TEST_CASE("Check if empty is printed correctly", "memory") {
    Memory memory;

    std::stringstream ss;

    ss << memory;
    REQUIRE(ss.str() == "___________________\n___________________\n");
}

TEST_CASE("Check if with one item is printed correctly", "memory") {
    Memory memory;
    memory.push_back(std::make_unique<Fraction>(Fraction(1)));

    std::stringstream ss;

    ss << memory;
    REQUIRE(ss.str() == "___________________\n|  0              1 |\n___________________\n");
}

TEST_CASE("Check if with multiple items is printed correctly", "memory") {
    Memory memory;
    memory.push_back(std::make_unique<Fraction>(Fraction(1)));
    memory.push_back(std::make_unique<Fraction>(Fraction(2)));
    memory.push_back(std::make_unique<Fraction>(Fraction(3)));

    std::stringstream ss;

    ss << memory;
    REQUIRE(ss.str() ==
            "___________________\n|  0              1 |\n"
            "|  1              2 |\n|  2              3 |\n"
            "___________________\n");
}
