// tests.cpp
#include "k_dominant_characters.h"
#include <catch.hpp>

TEST_CASE("Homogeneous") { REQUIRE(1 == KDomCharFinder("aaa")()); }
TEST_CASE("Dist2") { REQUIRE(2 == KDomCharFinder("abab")()); }
TEST_CASE("Middle") { REQUIRE(4 == KDomCharFinder("abcdeab")()); }
TEST_CASE("No reps") { REQUIRE(2 == KDomCharFinder("xyz")()); }
