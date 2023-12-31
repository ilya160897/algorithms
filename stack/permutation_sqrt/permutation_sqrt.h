// https://codeforces.com/problemset/problem/612/E

#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using Vec = std::vector<int>;

class PermutationSqrt {
public:
  PermutationSqrt(const Vec &square)
      : Square(square), Used(square.size(), false) {}

  Vec operator()() {
    InitializeCycles();
    DoCycleTransformations();
    InitializeRoot();
    return Root;
  }

private:
  void DoCycleTransformations() {
    for (size_t i = 0; i < OddCycles.size(); ++i) {
      OddCycles[i] = SquareRootFromOddCycle(OddCycles[i]);
    }
    for (const auto &cycleIt : EvenCycles) {
      const std::vector<Vec> &cycles = cycleIt.second;
      size_t sz = cycles.size();
      if (sz & 1) {
        RootExists = false;
        return;
      }
      for (size_t i = 0; i + 1 < sz; i += 2) {
        Vec mergedCycle =
            MergeEvenCyclesOfSameLength(cycles.at(i), cycles.at(i + 1));
        MergedEvenCycles.emplace_back(std::move(mergedCycle));
      }
    }
  }

private:
  void InitializeCycles() {
    for (int i : Square) {
      auto cycle = CreateCycleFrom(i);
      size_t sz = cycle.size();
      if (sz == 0) {
        continue;
      }
      if (sz & 1) {
        OddCycles.emplace_back(std::move(cycle));
        continue;
      }
      EvenCycles[sz].push_back(std::move(cycle));
    }
  }
  Vec CreateCycleFrom(size_t i) {
    assert(0 <= i && i < Square.size());
    Vec result;
    while (!Used[i]) {
      Used[i] = true;
      result.push_back(i);
      i = Square[i];
    }
    return result;
  }
  Vec SquareRootFromOddCycle(const Vec &nums) {
    assert(nums.size() & 1);
    Vec result;
    int current = 0;
    int len = nums.size();
    do {
      result.push_back(nums[current]);
      current = (current + (len + 1) / 2);
      current = current < len ? current : current - len;
    } while (current != 0);

    return result;
  }
  Vec MergeEvenCyclesOfSameLength(const Vec &left, const Vec &right) {
    assert(left.size() == right.size());
    Vec result;
    size_t sz = left.size();
    result.reserve(2 * sz);

    for (size_t i = 0; i < sz; ++i) {
      result.push_back(left[i]);
      result.push_back(right[i]);
    }
    return result;
  }
  void InitializeRoot() {
    Root.resize(Square.size());
    if (!RootExists) {
      Root = {-1};
      return;
    }
    for (const Vec &cycle : OddCycles) {
      InitRootFrom(cycle);
    }
    for (const Vec &cycle : MergedEvenCycles) {
      InitRootFrom(cycle);
    }
  }
  void InitRootFrom(const Vec &cycle) {
    assert(!cycle.empty());
    for (size_t i = 0; i + 1 < cycle.size(); ++i) {
      Root[cycle[i]] = cycle[i + 1];
    }
    Root[cycle.back()] = cycle.front();
  }

private:
  std::unordered_map<int, std::vector<Vec>> EvenCycles;
  std::vector<Vec> MergedEvenCycles;
  std::vector<Vec> OddCycles;
  const Vec &Square;
  bool RootExists = true;
  Vec Root;
  std::vector<bool> Used;
};
