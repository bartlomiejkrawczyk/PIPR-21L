#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Check if true is true", "sanity_check") { REQUIRE(true); }

TEST_CASE("Check addition", "sanity_check") { REQUIRE(2 + 2 == 4); }