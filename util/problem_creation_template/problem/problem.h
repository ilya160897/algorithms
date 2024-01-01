#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

class SolutionClass {
public:
  SolutionClass(int N) : n(N) {}

  int operator()() { return n; }

private:
private:
  int n;
};
