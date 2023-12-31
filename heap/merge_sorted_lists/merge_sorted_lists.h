#pragma once

#include <algorithm> // copy
#include <iostream>  // boolalpha, cin, cout, streamsize
#include <iterator>  // back_inserter, istream_iterator, ostream_iterator, prev
#include <limits>    // numeric_limits
#include <queue>     // vector
#include <sstream>   // istringstream
#include <string>    // getline, string
#include <vector>    // vector

struct Item {
  size_t list;
  size_t pos;
  int val;
  bool operator<(const Item &other) const { return val > other.val; }
};

using Lists = std::vector<std::vector<int>>;

class SortedListMerger {
public:
  SortedListMerger(const Lists &sorted_lists) : sorted_lists_(sorted_lists) {}
  std::vector<int> Merge() {
    Init();
    while (!pq_.empty()) {
      auto item = pq_.top();
      pq_.pop();
      ProcessItem(item);
    }
    return result_;
  }
  void Init() {
    for (size_t i = 0; i < sorted_lists_.size(); ++i) {
      if (sorted_lists_[i].empty()) {
        continue;
      }
      pq_.emplace(Item{i, 0, sorted_lists_[i][0]});
    }
  }
  void ProcessItem(const Item &item) {
    result_.emplace_back(item.val);
    size_t next_pos = item.pos + 1;
    auto &list = sorted_lists_[item.list];
    if (next_pos < list.size()) {
      pq_.emplace(Item{item.list, next_pos, list[next_pos]});
    }
  }

private:
  std::vector<int> result_;
  std::priority_queue<Item> pq_;
  const Lists &sorted_lists_;
};

std::vector<int> merge_k_sorted_lists(std::vector<std::vector<int>> lists) {
  return SortedListMerger(lists).Merge();
}
