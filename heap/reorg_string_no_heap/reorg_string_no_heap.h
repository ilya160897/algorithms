#pragma once

#include <algorithm>     // std::sort
#include <iostream>      // cin
#include <string>        // getline, string
#include <unordered_map> // unordered_map
#include <vector>        // unordered_map

class EvenThenOddIterator {
public:
  EvenThenOddIterator(size_t size) : size_(size) {}
  size_t GetNext() {
    size_t result;
    if (current_ < size_) {
      result = current_;
      current_ += 2;
      return result;
    }
    if (current_ % 2) {
      throw std::logic_error("Iterator out of bound");
    }
    current_ = 3;
    return 1;
  }

private:
  size_t current_ = 0;
  size_t size_;
};

struct CharWithCount {
  char character;
  size_t count;
  CharWithCount(char chr, size_t cnt) : character(chr), count(cnt) {}
  bool operator<(const CharWithCount &other) const {
    return count < other.count;
  }
};

std::vector<CharWithCount> BuildCharsWithCounts(const std::string &s) {
  std::unordered_map<char, size_t> char_to_count;
  for (char symbol : s) {
    ++char_to_count[symbol];
  }
  std::vector<CharWithCount> result;
  for (auto [symbol, count] : char_to_count) {
    result.emplace_back(symbol, count);
  }
  return result;
}

std::string BuildReorgString(const std::string &s) {
  size_t size = s.size();
  std::string result;
  result.resize(size);
  auto char_with_count = BuildCharsWithCounts(s);
  std::sort(char_with_count.rbegin(), char_with_count.rend());
  auto iter = EvenThenOddIterator(s.size());
  for (auto [symbol, count] : char_with_count) {
    if (2 * count > size + (size % 2)) {
      return "";
    }
    for (size_t i = 0; i < count; ++i) {
      auto j = iter.GetNext();
      result[j] = symbol;
    }
  }
  return result;
}

std::string reorganize_string(std::string s) {
  if (s.empty()) {
    return "";
  }
  return BuildReorgString(s);
}
