#include "gadgets_for_dollars_and_pounds.h"
#include <catch.hpp>

TEST_CASE("TEST_1") {
  auto expected = TResult{3, {{1, 1}, {2, 3}}};
  auto result = GadgetsForDollarsAndPounds(
      5, 4, 2, 2, {{1, 1}, {2, 2}, {3, 3}, {4, 2}, {5, 1}},
      {{1, 3}, {2, 2}, {3, 1}, {4, 2}, {5, 3}}, {{1, 1}, {3, 2}},
      {{2, 1}, {4, 2}})();
  REQUIRE(expected == result);
}
TEST_CASE("TEST_2") {
  auto expected = TResult{-1, {}};
  auto result = GadgetsForDollarsAndPounds(
      4, 3, 2, 200, {{1, 67}, {2, 70}, {3, 71}, {4, 72}},
      {{1, 104}, {2, 105}, {3, 106}, {4, 107}}, {{1, 1}, {3, 2}}, {{2, 2}})();
  REQUIRE(expected == result);
}
TEST_CASE("TEST_3") {
  auto expected = TResult{-1, {}};
  auto result = GadgetsForDollarsAndPounds(
      4, 3, 1, 1000000000, {{1, 900000}, {2, 900000}, {3, 900000}, {4, 900000}},
      {{1, 990000}, {2, 999000}, {3, 999900}, {4, 999990}},
      {{1, 87654}, {3, 65432}}, {{2, 76543}})();
  REQUIRE(expected == result);
}
TEST_CASE("TEST_4") {
  auto expected = TResult{1, {{1, 1}, {2, 1}}};
  auto result = GadgetsForDollarsAndPounds(
      1, 2, 2, 1000000, {{1, 778}}, {{1, 62}}, {}, {{1, 119}, {2, 220}})();
  REQUIRE(expected == result);
}
