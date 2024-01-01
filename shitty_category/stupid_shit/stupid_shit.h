#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

class StupidShit {
public:
  StupidShit(int N) : n(N) {}

  int operator()() { return n; }

private:
private:
  int n;
};
