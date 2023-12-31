// https://codeforces.com/problemset/problem/888/C

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

class KDomCharFinder {
public:
  KDomCharFinder(const std::string &word) : Word(word) {}

  int operator()() {
    for (size_t i = 0; i < Word.size(); ++i) {
      ProcessInd(i);
    }
    Postprocess();
    auto it = std::min_element(MaxDist.begin(), MaxDist.end(),
                               [](decltype(MaxDist)::value_type &l,
                                  decltype(MaxDist)::value_type &r) -> bool {
                                 return l.second < r.second;
                               });
    return it->second;
  }

private:
  void ProcessInd(size_t i) {
    char letter = Word[i];
    if (LetterToInd.find(letter) == LetterToInd.end()) {
      MaxDist[letter] = i + 1;
      LetterToInd[letter] = i;
      return;
    }
    MaxDist[letter] = std::max(MaxDist[letter], i - LetterToInd[letter]);
    LetterToInd[letter] = i;
  }
  void Postprocess() {
    for (const auto &[letter, ind] : LetterToInd) {
      MaxDist[letter] = std::max(MaxDist[letter], Word.size() - ind);
    }
  }

private:
  const std::string &Word;
  std::map<char, size_t> LetterToInd;
  std::map<char, size_t> MaxDist;
};
