#include "merge_sorted_lists.h"
#include <catch.hpp>

TEST_CASE("Merge K Sorted Lists - Empty Input") {
  std::vector<std::vector<int>> emptyLists;
  std::vector<int> result = merge_k_sorted_lists(emptyLists);
  REQUIRE(result.empty());
}

TEST_CASE("Merge K Sorted Lists - Single List") {
  std::vector<std::vector<int>> singleList = {{1, 3, 5}};
  std::vector<int> result = merge_k_sorted_lists(singleList);
  REQUIRE(result == std::vector<int>{1, 3, 5});
}

TEST_CASE("Merge K Sorted Lists - Multiple Lists") {
  std::vector<std::vector<int>> lists = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
  std::vector<int> result = merge_k_sorted_lists(lists);
  REQUIRE(result == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
}

TEST_CASE("Merge K Sorted Lists - Large Numbers") {
  std::vector<std::vector<int>> largeLists = {
      {100, 200, 300}, {150, 250, 350}, {120, 220, 320}};
  std::vector<int> result = merge_k_sorted_lists(largeLists);
  std::vector<int> expected = {100, 120, 150, 200, 220, 250, 300, 320, 350};
  REQUIRE(result == expected);
}

TEST_CASE("Merge K Sorted Lists - Negative Numbers") {
  std::vector<std::vector<int>> lists = {{-3, -2, -1}, {-6, -5, -4}};
  std::vector<int> result = merge_k_sorted_lists(lists);
  REQUIRE(result == std::vector<int>{-6, -5, -4, -3, -2, -1});
}

TEST_CASE("Merge K Sorted Lists - Stress Test (Large Data)") {
  constexpr int numLists = 1'000;
  constexpr int listSize = 10'000;

  // Generate 1000 lists, each with 200,000 random values (sorted)
  std::vector<std::vector<int>> lists(numLists);
  for (int i = 0; i < numLists; ++i) {
    lists[i].reserve(listSize);
    for (int j = 0; j < listSize; ++j) {
      lists[i].push_back(
          rand()); // Random values (not sorted for stress testing)
    }
    std::sort(lists[i].begin(), lists[i].end()); // Sorting the individual lists
  }

  // Merge the 1000 sorted lists
  std::vector<int> result = merge_k_sorted_lists(lists);

  // Validate the size of the merged result
  REQUIRE(result.size() == numLists * listSize);

  // Check if the merged result is sorted
  bool isSorted = std::is_sorted(result.begin(), result.end());
  REQUIRE(isSorted);
}
