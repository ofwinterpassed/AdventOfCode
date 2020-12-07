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

  auto countTrees = [&](int hDiff, int vDiff) -> long {
    long hIndex = 0, vIndex = 1;
    return accumulate(next(values.cbegin()), values.cend(), 0, [&](long a, const auto &line) {
      if (vIndex % vDiff == 0) {
        ++vIndex;
        hIndex += hDiff;
        return a + long((line[hIndex % line.size()] == '#'));
      }
      ++vIndex;
      return a;
    });
  };

  long numTrees = countTrees(1, 1) * countTrees(3, 1) * countTrees(5, 1) * countTrees(7, 1) * countTrees(1, 2);

  clog << numTrees << '\n';
}
