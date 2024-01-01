#include "calculator.h"
#include <catch.hpp>

TEST_CASE("CornerCase") {
  // REQUIRE(eval("") == 0);
  REQUIRE(eval("(0)") == 0);
  REQUIRE(eval("1") == 1);
  REQUIRE(eval("-1") == -1);
}
TEST_CASE("Simple") {
  REQUIRE(eval("2 + 3") == 5);
  REQUIRE(eval("2 - 3") == -1);
  REQUIRE(eval("2 * 3") == 6);
  REQUIRE(eval("2 / 3") == 0);
}
TEST_CASE("Complex") {
  REQUIRE(eval("(((30 - 4) * 5) + (18 / 2)) - 3") == 136);
  REQUIRE(eval("((25 * 3) - (16 / 4)) + (10 - 2)") == 79);
  REQUIRE(eval("((40 / 2) * (6 - 2)) + ((18 - 3) + (2 * 3))") == 101);
  REQUIRE(eval("((15 + -7) * (12 - 5)) / (9 + 3)") == 4);
  REQUIRE(eval("(((24 * 3) - (12 / 2)) + 10) / 5") == 15);
  REQUIRE(eval("(11 + (2 * 23)) - ((10) * ((11) * (13 - 19)))") == 717);
  REQUIRE(eval("(((10 + 5) * (20 - 8)) / ((7 + 3) * (18 - 6))) - (((15 + 4) / "
               "(9 - 3)) + ((22 - 11) * (14 + 7)))") == -233);
}
