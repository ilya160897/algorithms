#include "knuth_morris_pratt.h"
#include <catch.hpp>

std::string generateRandomString(int length) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 3);

  std::string result;
  result.reserve(length);

  for (int i = 0; i < length; ++i) {
    char randomChar = 'a' + dis(gen);
    result.push_back(randomChar);
  }

  return result;
}

void TestRandom(size_t needle_size, size_t haystack_size) {
  auto needle = generateRandomString(needle_size);
  auto haystack = generateRandomString(haystack_size);
  size_t expected = haystack.find(needle);
  size_t result = KnuthMorrisPratt(haystack, needle)();
  REQUIRE(expected == result);
}

TEST_CASE("TEST_1") {
  std::string haystack = "abcliverpoolabc";
  std::string needle = "liverpool";
  REQUIRE(3 == KnuthMorrisPratt(haystack, needle)());
}
TEST_CASE("TEST_2") {
  std::string needle = "aaa";
  std::string haystack = "aaaaaaaaaaaaaaaaaaaaaaa";
  REQUIRE(0 == KnuthMorrisPratt(haystack, needle)());
}
TEST_CASE("TEST_RANDOM_SMALL") {
  for (size_t i = 0; i < 100; ++i) {
    TestRandom(3, 100);
  }
}
TEST_CASE("TEST_RANDOM_BIG") {
  for (size_t i = 0; i < 100; ++i) {
    TestRandom(7, 1'000'000);
  }
}
