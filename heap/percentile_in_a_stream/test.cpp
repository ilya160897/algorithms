#include "percentile_in_a_stream.h"
#include <catch.hpp>
#include <random>

bool IsPercentile(int percentile, int val, const std::vector<int>& sorted_list) {
  auto lower_bound = std::lower_bound(sorted_list.begin(), sorted_list.end(), val);
  auto upper_bound = std::upper_bound(sorted_list.begin(), sorted_list.end(), val);
  size_t lb_ind = lower_bound - sorted_list.begin();
  size_t ub_ind = upper_bound - sorted_list.begin();
  size_t sz = sorted_list.size();
  return lb_ind * 100 <= sz * percentile && sz * percentile <= ub_ind * 100;
}

void TestIsPercentile(int percentile, size_t array_size) {
    // Step 1: Create 1'000'000 random integer numbers from -100'000 to 100'000
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-100000, 100000);
    
    std::vector<int> randomNumbers;
    for (int i = 0; i < array_size; ++i) {
        randomNumbers.push_back(dist(gen));
    }

    // Step 2: Push them into PercentileInAStream
    PercentileInAStream quantile(percentile); // Assuming you want to check the 50th percentile
    
    for (int num : randomNumbers) {
        quantile.Push(num);
    }

    // Step 3: Check that GetPercentile gives valid percentile using IsPercentile
    std::vector<int> sortedNumbers = randomNumbers;
    std::sort(sortedNumbers.begin(), sortedNumbers.end());

    int result = quantile.GetPercentile();
    // bool validPercentile = IsPercentile(percentile, result, sortedNumbers);
    REQUIRE(IsPercentile(percentile, result, sortedNumbers));
}

void TestIsPercentileWithCout(int percentile, size_t array_size) {
    // Step 1: Create 'array_size' random integer numbers from -100'000 to 100'000
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-100000, 100000);
    
    std::vector<int> randomNumbers;
    for (int i = 0; i < array_size; ++i) {
        randomNumbers.push_back(dist(gen));
    }

    // Step 2: Push them into PercentileInAStream
    PercentileInAStream quantile(percentile); // Assuming you want to check a certain percentile
    
    for (int num : randomNumbers) {
        quantile.Push(num);
    }

    // Step 3: Check that GetPercentile gives valid percentile using IsPercentile
    std::vector<int> sortedNumbers = randomNumbers;
    std::sort(sortedNumbers.begin(), sortedNumbers.end());

    int result = quantile.GetPercentile();
    bool validPercentile = IsPercentile(percentile, result, sortedNumbers);
    if (validPercentile) {
        std::cout << "Percentile " << percentile << ": " << result << std::endl;
    } else {
        std::cout << "Invalid percentile " << percentile << " calculated: " << result << std::endl;
    }

    // Output the 100 random numbers
    std::cout << "Sorted random numbers: ";
    for (int num : sortedNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

TEST_CASE("STRESS_TEST") {
    size_t array_size = 10'000;
    size_t small_array_size = 100;
    for (int i = 0; i <= 100; ++i) {
        TestIsPercentile(i, array_size);
    }
    for (int i = 0; i <= 100; i += 10) {
        TestIsPercentileWithCout(i, small_array_size);
    }
}
