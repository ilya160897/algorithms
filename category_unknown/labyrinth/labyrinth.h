// https://codeforces.com/contest/616/problem/C

#pragma once

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using Vecs = std::vector<std::string>;
using Vec = std::vector<int>;

using Coord = std::pair<int, int>;

class Labyrinth {
public:
  Labyrinth(const Vecs &table) : Table(table) {
    assert(!table.empty());
    w = table[0].size();
    h = table.size();
    CoordToComponent.assign(h * w, -1);
  }

  Vecs operator()() {
    BuildComponents();
    return DisplayCompMerges();
  }

private:
  Vecs DisplayCompMerges() {
    Vecs result = Table;
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        Coord coord{i, j};
        if (!IsFree(coord)) {
          result[i][j] = '0' + (1 + CalculateMergeSize(Neighbors(coord))) % 10;
        }
      }
    }
    return result;
  }
  int CalculateMergeSize(const std::vector<Coord> &neighbors) {
    int result = 0;
    std::unordered_set<int> comps;
    for (const Coord &coord : neighbors) {
      if (!Valid(coord) || !IsFree(coord)) {
        continue;
      }
      int comp = CoordToComponent[ID(coord)];
      if (comps.find(comp) != comps.end()) {
        continue;
      }
      comps.insert(comp);
      result += ComponentToSize[comp];
    }
    return result;
  }
  void BuildComponents() {
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        Coord coord{i, j};
        if (IsFree(coord) && CoordToComponent[ID(coord)] == -1) {
          ++CurrentComponent;
          ComponentToSize.push_back(0);
          assert(static_cast<int>(ComponentToSize.size()) ==
                 CurrentComponent + 1);
          DFS(coord);
        }
      }
    }
  }
  void DFS(const Coord &coord) {
    if (!Valid(coord) || !IsFree(coord) || CoordToComponent[ID(coord)] != -1) {
      return;
    }
    CoordToComponent[ID(coord)] = CurrentComponent;
    ++ComponentToSize[CurrentComponent];

    for (const Coord &neighbor : Neighbors(coord)) {
      DFS(neighbor);
    }
  }
  int ID(const Coord &coord) {
    int result = coord.first * w + coord.second;
    assert(result < h * w);
    return result;
  }

  bool Valid(const Coord &coord) {
    return 0 <= coord.first && coord.first < h && 0 <= coord.second &&
           coord.second < w;
  }
  std::vector<Coord> Neighbors(const Coord &coord) {
    int y = coord.first;
    int x = coord.second;
    return {{y + 1, x}, {y - 1, x}, {y, x + 1}, {y, x - 1}};
  }
  bool IsFree(const Coord &coord) {
    return Table[coord.first][coord.second] == '.';
  }

private:
  const Vecs &Table;
  int h;
  int w;

  int CurrentComponent = -1;

  Vec CoordToComponent;
  Vec ComponentToSize;
};
