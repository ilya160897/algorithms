#include "kth_smallest_in_matrix.h"
#include <algorithm>
#include <catch.hpp>
#include <cmath>
#include <random>

int getRandomNumber(int lowerBound, int upperBound) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(lowerBound, upperBound);
  return distribution(gen);
}

void sortRows(std::vector<std::vector<int>> &matrix) {
  for (auto &row : matrix) {
    std::sort(row.begin(), row.end());
  }
}

void StressTest(size_t random_seed, std::vector<int> &numbers) {
  int N = numbers.size();
  int n = sqrt(numbers.size());
  std::vector<std::vector<int>> largeMatrix(n, std::vector<int>(n, 0));

  std::mt19937 gen(random_seed);
  std::shuffle(numbers.begin(), numbers.end(), gen);

  int it = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      largeMatrix[i][j] = numbers[it++];
    }
    std::sort(largeMatrix[i].begin(), largeMatrix[i].end());
  }

  for (int i = 0; i < 10; ++i) {
    auto target = getRandomNumber(n, N);
    REQUIRE(target - 1 == kth_smallest(largeMatrix, target));
  }
}

TEST_CASE("STRESS_TEST") {
  // Create a vector of size N
  std::vector<int> numbers(1'000 * 1'000);

  // Fill the vector with numbers from 0 to N-1
  for (size_t i = 0; i < numbers.size(); ++i) {
    numbers[i] = i;
  }

  for (size_t seed = 0; seed < 10; ++seed) {
    StressTest(seed, numbers);
  }
}
