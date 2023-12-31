#include "permutation_sqrt.h"
#include <catch.hpp>

TEST_CASE("TEST_1") {
  std::vector<int> expected{2, 3, 1, 0};
  REQUIRE(expected == PermutationSqrt({1, 0, 3, 2})());
}
TEST_CASE("TEST_2") {
  std::vector<int> expected{-1};
  REQUIRE(expected == PermutationSqrt({1, 0, 2, 3})());
}
TEST_CASE("TEST_3") {
  std::vector<int> expected{3, 4, 0, 1, 2};
  REQUIRE(expected == PermutationSqrt({1, 2, 3, 4, 0})());
}
