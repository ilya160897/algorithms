#include "k_segments_union.h"
#include <catch.hpp>

TEST_CASE("TEST_1") {
  std::vector<SegmentEnd> expected = {{0, 0}, {2, 1}, {3, 0}, {5, 1}};
  std::vector<SegmentEnd> input = {{0, 0}, {5, 1}, {-3, 0},
                                   {2, 1}, {3, 0}, {8, 1}};
  REQUIRE(expected == KSegmentsUnion(2, input)());
}
TEST_CASE("TEST_2") {
  std::vector<SegmentEnd> expected = {{0, 0}, {5, 1}};
  std::vector<SegmentEnd> input = {{0, 0}, {5, 1}, {-3, 0},
                                   {3, 1}, {3, 0}, {8, 1}};
  REQUIRE(expected == KSegmentsUnion(2, input)());
}
TEST_CASE("TEST_3") {
  std::vector<SegmentEnd> expected = {{0, 0}, {0, 1}};
  std::vector<SegmentEnd> input = {
      {-1, 0}, {0, 1}, {-1, 0}, {0, 1}, {0, 0}, {1, 1}, {0, 0}, {1, 1},
  };
  REQUIRE(expected == KSegmentsUnion(4, input)());
}
TEST_CASE("TEST_4") {
  std::vector<SegmentEnd> expected = {};
  std::vector<SegmentEnd> input = {
      {-1, 0}, {0, 1}, {-1, 0}, {0, 1}, {0, 0}, {1, 1}, {0, 0}, {1, 1},
  };
  REQUIRE(expected == KSegmentsUnion(5, input)());
}