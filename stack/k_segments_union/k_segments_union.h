// https://codeforces.com/problemset/problem/612/D

#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// Second field shows if this SegmentEnd is the rightmost point of the segment.
using SegmentEnd = std::pair<int, int>;

class KSegmentsUnion {
public:
  KSegmentsUnion(int k, std::vector<SegmentEnd> &ends) : Ends(ends), K(k) {}

  std::vector<SegmentEnd> &operator()() {
    Init();
    Iterate();
    return Result;
  }

private:
  void Init() {
    std::sort(Ends.begin(), Ends.end());
    Result.reserve(Ends.size());
  }
  void Iterate() {
    for (const auto &end : Ends) {
      if (end.second == 1) {
        --Layers;
        if (Layers == K - 1) {
          Result.emplace_back(end.first, 1);
        }
        continue;
      }
      ++Layers;
      if (Layers == K) {
        Result.emplace_back(end.first, 0);
      }
    }
  }

private:
  std::vector<SegmentEnd> Result;
  std::vector<SegmentEnd> &Ends;
  int Layers = 0;
  int K;
};
