#pragma once

#include <algorithm> // copy
#include <iostream>  // boolalpha, cin, cout, streamsize
#include <iterator>  // back_inserter, istream_iterator
#include <limits>    // numeric_limits
#include <queue>     // queue
#include <sstream>   // istringstream
#include <string>    // getline, string
#include <vector>    // vector

struct MatrixItem {
  size_t row;
  size_t col;
  int val;
  MatrixItem(size_t r, size_t c, int v) : row(r), col(c), val(v) {}
  bool operator<(const MatrixItem &other) const { return val > other.val; }
};

class KthSmallestFinder {
public:
  using Matrix = std::vector<std::vector<int>>;
  KthSmallestFinder(const Matrix &matrix, size_t k)
      : matrix_(matrix), size_(matrix.size()), k_(k) {}
  int FindKthSmallest() {
    Init();
    for (size_t i = 0; i + 1 < k_; ++i) {
      auto item = pq_.top();
      pq_.pop();
      ProcessItem(item);
    }
    return pq_.top().val;
  }
  void Init() {
    for (size_t i = 0; i < size_; ++i) {
      pq_.emplace(i, 0, matrix_[i][0]);
    }
  }
  void ProcessItem(const MatrixItem &item) {
    size_t row = item.row;
    size_t new_col = item.col;
    ++new_col;
    if (new_col < size_) {
      pq_.emplace(row, new_col, matrix_[row][new_col]);
    }
  }

private:
  const std::vector<std::vector<int>> &matrix_;
  size_t size_;
  size_t k_;
  std::priority_queue<MatrixItem> pq_;
};

int kth_smallest(std::vector<std::vector<int>> matrix, int k) {
  return KthSmallestFinder(matrix, k).FindKthSmallest();
}
