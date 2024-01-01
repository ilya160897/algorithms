#include "labyrinth.h"
#include <catch.hpp>

TEST_CASE("TEST_1") {
  Vecs result = {"3.3", ".5.", "3.3"};
  REQUIRE(result == Labyrinth({"*.*", ".*.", "*.*"})());
}
TEST_CASE("TEST_2") {
  Vecs result = {"46..3", "..732", ".6.4.", "5.4.3"};
  REQUIRE(result == Labyrinth({"**..*", "..***", ".*.*.", "*.*.*"})());
}
