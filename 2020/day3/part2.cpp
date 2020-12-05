#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
int main(int argc, char **argv) {

  vector<string> values;
  for (string input; getline(cin, input);) {
    values.emplace_back(input);
  }

  long hDiff = 1;
  long vDiff = 1;
  long hIndex = 0;
  long vIndex = 1;
  auto l = [&](long a, const auto &line) {
    if (vIndex % vDiff == 0) {
      ++vIndex;
      hIndex += hDiff;
      return a + long((line[hIndex % line.size()] == '#'));
    }
    ++vIndex;
    return a;
  };
  long numTrees = accumulate(next(values.cbegin()), values.cend(), 0, l);
  hDiff = 3;
  hIndex = 0;
  vIndex = 1;
  numTrees *= accumulate(next(values.cbegin()), values.cend(), 0, l);
  hDiff = 5;
  hIndex = 0;
  vIndex = 1;
  numTrees *= accumulate(next(values.cbegin()), values.cend(), 0, l);
  hDiff = 7;
  hIndex = 0;
  vIndex = 1;
  numTrees *= accumulate(next(values.cbegin()), values.cend(), 0, l);
  hDiff = 1;
  vDiff = 2;
  hIndex = 0;
  vIndex = 1;
  numTrees *= accumulate(next(values.cbegin()), values.cend(), 0, l);

  clog << numTrees << '\n';
}
