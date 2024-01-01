#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

class KnuthMorrisPratt {
public:
  KnuthMorrisPratt(const std::string &haystack, const std::string &needle)
      : haystack_(needle + haystack), needle_(needle) {
    prefix_func_.assign(haystack.size() + needle.size(), 0);
  }
  size_t operator()() {
    CalcPrefixFunc();
    return FindFirstOccurrence();
  }

private:
  void CalcPrefixFunc() {
    for (size_t i = 1; i < haystack_.size(); ++i) {
      size_t j = prefix_func_[i - 1];
      while (j != 0 && haystack_[i] != haystack_[j]) {
        j = prefix_func_[j - 1];
      }
      if (haystack_[i] == haystack_[j]) {
        ++j;
      }
      prefix_func_[i] = j;
    }
  }
  size_t FindFirstOccurrence() {
    size_t target = needle_.size();
    size_t search_begin_offset = 2 * needle_.size() - 1;
    auto ptr = std::find_if(
        prefix_func_.begin() + search_begin_offset, prefix_func_.end(),
        [target](size_t element) { return element >= target; });
    if (ptr == prefix_func_.end()) {
      return std::string::npos;
    }
    size_t found_end = (ptr - prefix_func_.begin());
    return found_end - search_begin_offset;
  }

private:
  std::vector<size_t> prefix_func_;
  std::string haystack_;
  std::string needle_;
};
