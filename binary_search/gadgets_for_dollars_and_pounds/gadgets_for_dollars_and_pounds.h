// This problem is taken from Codeforces educational round:
// https://codeforces.com/contest/609/problem/D

#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

using Int = long long;

struct TGadget {
  TGadget(Int id, Int price) : ID(id), Price(price) {}
  bool operator<(const TGadget &other) const { return Price < other.Price; }
  bool operator==(const TGadget &other) const {
    return Price == other.Price && ID == other.ID;
  }
  Int ID;
  Int Price;
};

struct {
  Int operator()(const TGadget &left, const TGadget &right) {
    return left.Price + right.Price;
  }
} TGadgetAdd;

struct TDayRate {
  TDayRate(Int day, Int rate) : Day(day), Rate(rate) {}
  bool operator<(const TDayRate &other) const { return Rate < other.Rate; }
  Int Day;
  Int Rate;
};

struct TIdDay {
  TIdDay(Int id, Int day) : ID(id), Day(day) {}

  bool operator==(const TIdDay &other) const {
    return Day == other.Day && ID == other.ID;
  }
  bool operator<(const TIdDay &other) const { return ID < other.ID; }
  Int ID;
  Int Day;
};

std::ostream &operator<<(std::ostream &os, const TIdDay &idDay) {
  os << idDay.ID << " " << idDay.Day << "\n";
  return os;
}

struct TResult {
  TResult(Int day, const std::vector<TIdDay> &idDays)
      : Day(day), IdDays(idDays) {
    std::sort(IdDays.begin(), IdDays.end());
  }
  TResult &operator=(const TResult &other) {
    Day = other.Day;
    IdDays = other.IdDays;
    return *this;
  }
  bool operator==(const TResult &other) const {
    if (Day == other.Day && IdDays.size() == other.IdDays.size()) {
      for (size_t i = 0; i < IdDays.size(); ++i) {
        if (!(IdDays[i] == other.IdDays[i])) {
          return false;
        }
      }
      return true;
    }
    return false;
  }
  Int Day;
  std::vector<TIdDay> IdDays;
};

std::ostream &operator<<(std::ostream &os, const TResult &result) {
  os << result.Day << "\n";
  for (auto idDay : result.IdDays) {
    os << idDay;
  }
  return os;
}

class GadgetsForDollarsAndPounds {
public:
  GadgetsForDollarsAndPounds(size_t days, size_t gtotal, size_t ggoal,
                             Int balance, const std::vector<TDayRate> &drate,
                             const std::vector<TDayRate> &prate,
                             const std::vector<TGadget> &dgadgets,
                             const std::vector<TGadget> &pgadgets)
      : Days(days), gTotal(gtotal), gGoal(ggoal), Balance(balance),
        dRate(drate), pRate(prate), dGadgets(dgadgets), pGadgets(pgadgets),
        dGadgetCumsums(dgadgets.size(), 0), pGadgetCumsums(pgadgets.size(), 0) {
    Init();
  }

  TResult operator()() {
    if (dGadgets.size() + pGadgets.size() < gGoal) {
      return {-1, {}};
    }
    Int day = BinarySearch();
    return BuildResult(day);
  }

private:
  void Init() {
    assert(gTotal);
    assert(dRate.size() == Days);
    assert(pRate.size() == Days);
    for (size_t i = 1; i < Days; ++i) {
      dRate[i] = std::min(dRate[i], dRate[i - 1]);
      pRate[i] = std::min(pRate[i], pRate[i - 1]);
    }
    std::sort(dGadgets.begin(), dGadgets.end());
    std::sort(pGadgets.begin(), pGadgets.end());
    Int dSum = 0;
    int pSum = 0;
    for (size_t i = 0; i < dGadgets.size(); ++i) {
      dSum += dGadgets[i].Price;
      dGadgetCumsums[i] = dSum;
    }
    for (size_t i = 0; i < pGadgets.size(); ++i) {
      pSum += pGadgets[i].Price;
      pGadgetCumsums[i] = pSum;
    }
  }
  std::pair<Int, Int> Grab(Int dollar, Int pound) {
    for (size_t i = 0; i <= gGoal; ++i) {
      size_t j = gGoal - i;
      if (i > dGadgets.size() || j > pGadgets.size()) {
        continue;
      }
      auto dSpent = (i == 0) ? 0 : dGadgetCumsums[i - 1] * dollar;
      auto pSpent = (j == 0) ? 0 : pGadgetCumsums[j - 1] * pound;
      if (dSpent + pSpent <= Balance) {
        return {i, j};
      }
    }
    return {-1, -1};
  }
  Int BinarySearch() {
    Int r = Days;
    Int l = -1;
    while (l + 1 < r) {
      Int m = (l + r) / 2;
      auto dollar = dRate[m];
      auto pound = pRate[m];
      auto grab = Grab(dollar.Rate, pound.Rate);
      if (grab.first == -1 && grab.second == -1) {
        l = m;
      } else {
        r = m;
      }
    }
    return r;
  }
  TResult BuildResult(Int day) {
    if (day == static_cast<Int>(Days)) {
      return {-1, {}};
    }
    auto dollar = dRate[day];
    auto pound = pRate[day];
    auto [dSize, pSize] = Grab(dollar.Rate, pound.Rate);
    std::vector<TIdDay> idDays;
    for (Int i = 0; i < dSize; ++i) {
      idDays.emplace_back(dGadgets[i].ID, dollar.Day);
    }
    for (Int i = 0; i < pSize; ++i) {
      idDays.emplace_back(pGadgets[i].ID, pound.Day);
    }
    return {day + 1, std::move(idDays)};
  }

private:
  size_t Days;
  size_t gTotal;
  size_t gGoal;
  Int Balance;
  std::vector<TDayRate> dRate;
  std::vector<TDayRate> pRate;
  std::vector<TGadget> dGadgets;
  std::vector<TGadget> pGadgets;
  std::vector<Int> dGadgetCumsums;
  std::vector<Int> pGadgetCumsums;
};

// int main() {
//     size_t days;
//     size_t gtotal;
//     size_t ggoal;
//     Int balance;

//     std::cin >> days >> gtotal >> ggoal >> balance;

//     std::vector<TDayRate> drate;
//     std::vector<TDayRate> prate;
//     std::vector<TGadget> dgadgets, pgadgets;

//     for (Int i = 0; i < static_cast<Int>(days); ++i) {
//         Int rate;
//         std::cin >> rate;
//         drate.emplace_back(1 + i, rate);
//     }
//     for (Int i = 0; i < static_cast<Int>(days); ++i) {
//         Int rate;
//         std::cin >> rate;
//         prate.emplace_back(1 + i, rate);
//     }
//     for (size_t i = 0; i < gtotal; ++i) {
//         Int type, price;
//         std::cin >> type >> price;
//         if (type == 1) {
//             dgadgets.emplace_back(i + 1, price);
//         } else {
//             pgadgets.emplace_back(i + 1, price);
//         }
//     }
//     auto result = GadgetsForDollarsAndPounds(
//         days, gtotal, ggoal, balance,
//         drate, prate,
//         dgadgets, pgadgets
//     )();
//     std::cout << result;
//     return 0;
// }
