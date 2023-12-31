#include "reorg_string_no_heap.h"
#include <catch.hpp>

bool noAdjacentDuplicates(const std::string &s) {
  int n = s.length();
  for (int i = 1; i < n; ++i) {
    if (s[i] == s[i - 1]) {
      return false;
    }
  }
  return true;
}

std::string CreateLargeString(size_t size, size_t num_of_As) {
  std::string largeString(size, 'a'); // Filling half with 'a's

  // Randomly fill the other half with different symbols
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(
      0, 25); // ASCII values for lowercase letters
  for (size_t i = num_of_As; i < size; ++i) {
    char randomChar =
        'a' + distribution(gen); // Generate random lowercase letter
    if (randomChar == 'a') {
      randomChar = 'b';
    }
    largeString[i] = randomChar;
  }

  return largeString;
}

void TestStringNotFeasible(const std::string &s) {
  REQUIRE("" == reorganize_string(s));
}
void TestStringFeasible(const std::string &s) {
  std::string result = reorganize_string(s);
  REQUIRE(result != "");
  REQUIRE(noAdjacentDuplicates(result));
}

TEST_CASE("TEST_1") {
  std::string s = "aab";
  TestStringFeasible(s);
}
TEST_CASE("TEST_2") {
  std::string s = "aaaaaaaa";
  TestStringNotFeasible(s);
}
TEST_CASE("TEST_3") {
  std::string s = "aaaabbb";
  TestStringFeasible(s);
}
TEST_CASE("TEST_4") {
  std::string s = "aopdfbijadpofijasdpofij";
  TestStringFeasible(s);
}
TEST_CASE("TEST_5") {
  std::string s = "";
  TestStringNotFeasible(s);
}
TEST_CASE("TEST_6") {
  std::string s = CreateLargeString(10'000'000, 5'000'000);
  TestStringFeasible(s);
}
TEST_CASE("TEST_7") {
  std::string s = CreateLargeString(10'000'000, 5'000'001);
  TestStringNotFeasible(s);
}
TEST_CASE("TEST_8") {
  std::string s = CreateLargeString(10'000'001, 5'000'001);
  TestStringFeasible(s);
}
