// https://codeforces.com/problemset/problem/888/E

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_set>
#include <vector>

class MaximumSubsequence {
public:
  MaximumSubsequence(int N, const std::vector<int> &Nums) : n(N), nums(Nums) {}

  int operator()() {
    if (nums.size() == 1) {
      return nums.front() % n;
    }
    auto delimeter = nums.begin() + (nums.size() / 2);
    std::vector<int> leftHalf{nums.begin(), delimeter};
    std::vector<int> rightHalf{delimeter, nums.end()};

    auto sumsLeft = GetSortedSumsModuloN(leftHalf);
    auto sumsRight = GetSortedSumsModuloN(rightHalf);
    ConsiderMixedSums(sumsLeft, sumsRight);
    return result;
  }

private:
  int GetMaskSumModuloN(int maskNum, const std::vector<int> &values) {
    assert(!values.empty());
    int pow = values.size();
    int sum = 0;
    for (int i = 0; i < pow; ++i) {
      if (maskNum % 2 == 1) {
        sum += values[i];
        sum %= n;
      }
      maskNum /= 2;
    }
    return sum;
  }
  std::vector<int> GetSortedSumsModuloN(const std::vector<int> &values) {
    std::unordered_set<int> subsums;
    int pow = values.size();
    for (int maskNum = 0; maskNum < (1 << pow); ++maskNum) {
      int subsum = GetMaskSumModuloN(maskNum, values);
      UpdateResult(subsum);
      subsums.insert(subsum);
    }
    std::vector<int> resultVector;
    resultVector.insert(resultVector.end(), subsums.begin(), subsums.end());
    std::sort(resultVector.begin(), resultVector.end());
    return resultVector;
  }
  void ConsiderMixedSums(const std::vector<int> &sumsLeft,
                         const std::vector<int> &sumsRight) {
    for (int sumRight : sumsRight) {
      UpdateResult((sumRight + sumsLeft.back()) % n);
      auto iter =
          std::lower_bound(sumsLeft.begin(), sumsLeft.end(), n - sumRight);
      if (iter != sumsLeft.begin()) {
        iter = prev(iter);
        UpdateResult((sumRight + *iter) % n);
      }
    }
  }
  void UpdateResult(int candidate) { result = std::max(result, candidate); }

private:
  int n;
  int result = 0;
  const std::vector<int> &nums;
};
