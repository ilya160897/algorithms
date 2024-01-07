#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using MaxHeapInt = std::priority_queue<int>;
using MinHeapInt = std::priority_queue<int, std::vector<int>, std::greater<int>>;

class PercentileInAStream {
public:
  PercentileInAStream(int percentile) : percentile_(percentile) {}

  void Push(int val) {
    PushRight(val);
    if (!Balanced()) {
      SiftDown();
    }
  }

  int GetPercentile() const {
    return left_segment_.empty() ? right_segment_.top() : left_segment_.top();
  }

private:
  void PushRight(int val) {
    if (left_segment_.empty() || val >= left_segment_.top()) {
      right_segment_.push(val);
      return;
    }
    right_segment_.push(left_segment_.top());
    left_segment_.pop();
    left_segment_.push(val);
  }
  void SiftDown() {
    auto right_lower = right_segment_.top();
    right_segment_.pop();
    left_segment_.push(right_lower);
  }
  bool Balanced() const {
    return left_segment_.size() * 100 <= Size() * percentile_ 
           &&  (left_segment_.size() + 1) * 100 > Size() * percentile_;
  }
  size_t Size() const {
    return left_segment_.size() + right_segment_.size();
  }
private:
  int percentile_;
  MaxHeapInt left_segment_;
  MinHeapInt right_segment_;
};
