// https://codeforces.com/contest/616/problem/B

#pragma once

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using VVec = std::vector<std::vector<int>>;
using Vec = std::vector<int>;
class DinnerWithNatasha {
public:
  DinnerWithNatasha(const VVec &nums) : Nums(nums) {}

  int operator()() { return GetMaxiMin(); }

private:
  int GetMaxiMin() const {
    int result = INT_MIN;
    for (const auto &vec : Nums) {
      int min = *std::min_element(vec.begin(), vec.end());
      result = std::max(min, result);
    }
    return result;
  }

private:
  const VVec &Nums;
};
