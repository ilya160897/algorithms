#include "dinner_with_natasha.h"
#include <catch.hpp>

TEST_CASE("TEST_1") {
  REQUIRE(2 == DinnerWithNatasha({{4, 1, 3, 5}, {2, 2, 2, 2}, {5, 4, 5, 1}})());
}
TEST_CASE("TEST_2") {
  REQUIRE(1 == DinnerWithNatasha({{1, 2, 3}, {2, 3, 1}, {3, 1, 2}})());
}
