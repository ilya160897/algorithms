#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <vector>

template <typename T, typename Compare = std::less<T>> class PriorityQueue {
public:
  PriorityQueue() {}
  bool Empty() const { return values_.empty(); }
  void Push(auto &&value) {
    values_.emplace_back(std::forward<decltype(value)>(value));
    SiftUp();
  }
  T &Front() { return values_.front(); }
  void Pop() {
    std::swap(values_.front(), values_.back());
    values_.pop_back();
    SiftDown();
  }

private:
  void SiftUp() {
    auto sz = values_.size();
    if (sz < 2) {
      return;
    }
    SiftUpImpl(sz - 1);
  }
  void SiftUpImpl(size_t i) {
    if (i == 0) {
      return;
    }
    auto parent = Parent(i);
    if (Compare{}(values_[parent], values_[i])) {
      std::swap(values_[parent], values_[i]);
      SiftUpImpl(parent);
    }
  }
  void SiftDown() { SiftDownImpl(0); }
  void SiftDownImpl(size_t i) {
    auto [left_child, right_child] = Children(i);
    if (left_child >= values_.size()) {
      return;
    }
    if (right_child < values_.size()) {
      SiftDownCaseTwoChildren(i);
      return;
    }
    SiftDownCaseOneChild(i);
  }
  void SiftDownCaseOneChild(size_t i) {
    auto child = 2 * i + 1;
    if (CompareVals(child, i)) {
      return;
    }
    std::swap(values_[child], values_[i]);
    SiftDownImpl(child);
  }
  void SiftDownCaseTwoChildren(size_t i) {
    auto [left_child, right_child] = Children(i);
    if (CompareVals(left_child, i) && CompareVals(right_child, i)) {
      return;
    }
    auto biggest =
        CompareVals(left_child, right_child) ? right_child : left_child;
    std::swap(values_[i], values_[biggest]);
    SiftDownImpl(biggest);
  }
  static size_t Parent(size_t i) {
    assert(i != 0);
    return (i - 1) / 2;
  }
  static std::pair<size_t, size_t> Children(size_t i) {
    return std::make_pair(2 * i + 1, 2 * i + 2);
  }
  inline bool CompareVals(size_t i, size_t j) const {
    return Compare{}(values_[i], values_[j]);
  }

private:
  std::vector<T> values_;
};
