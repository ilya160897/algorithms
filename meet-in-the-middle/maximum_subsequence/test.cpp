#include "maximum_subsequence.h"
#include <catch.hpp>

TEST_CASE("TEST_1") { REQUIRE(3 == MaximumSubsequence(4, {5, 2, 4, 1})()); }
TEST_CASE("TEST_2") { REQUIRE(19 == MaximumSubsequence(20, {199, 41, 299})()); }
TEST_CASE("TEST_3") {
  REQUIRE(9 == MaximumSubsequence(10, {47, 100, 49, 2, 56})());
}
TEST_CASE("TEST_4") {
  REQUIRE(917 == MaximumSubsequence(1000, {361, 847, 913, 499, 297})());
}
TEST_CASE("Single Number") { REQUIRE(15 == MaximumSubsequence(20, {15})()); }
TEST_CASE("Combine All") {
  REQUIRE(7 == MaximumSubsequence(8, {1, 1, 2, 3})());
}
TEST_CASE("Right half") { REQUIRE(5 == MaximumSubsequence(6, {1, 1, 2, 3})()); }
TEST_CASE("Combine Halfs Small Big") {
  REQUIRE(11 == MaximumSubsequence(12, {1, 32, 7, 3})());
}
TEST_CASE("Stress") {
  REQUIRE(999999999 ==
          MaximumSubsequence(
              1000000000,
              {723631245, 190720106, 931659134, 503095294, 874181352, 712517040,
               800614682, 904895364, 256863800, 39366772,  763190862, 770183843,
               774794919, 55669976,  329106527, 513566505, 207828535, 258356470,
               816288168, 657823769, 5223226,   865258331, 655737365, 278677545,
               880429272, 718852999, 810522025, 229560899, 544602508, 195068526,
               878937336, 739178504, 474601895, 54057210,  432282541})());
}
