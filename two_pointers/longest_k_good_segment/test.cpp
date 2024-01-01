#include "longest_k_good_segment.h"
#include <catch.hpp>

TEST_CASE("TEST_1") {
  REQUIRE(std::vector<size_t>{1, 5} ==
          LongestKGoodSegment(5, {1, 2, 3, 4, 5})());
}
TEST_CASE("TEST_2") {
  REQUIRE(std::vector<size_t>{3, 7} ==
          LongestKGoodSegment(3, {6, 5, 1, 2, 3, 2, 1, 4, 5})());
}
TEST_CASE("TEST_3") {
  REQUIRE(std::vector<size_t>{1, 1} == LongestKGoodSegment(1, {1, 2, 3})());
}
