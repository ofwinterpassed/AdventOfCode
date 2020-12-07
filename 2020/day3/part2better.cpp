#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  vector<string> values;
  for (string input; getline(cin, input);) {
    values.emplace_back(input);
  }

  auto countTrees = [&](int hDiff, int vDiff) -> long {
    return get<2>(accumulate(next(values.cbegin()), values.cend(), tuple{0, 1, 0},
                             [=](auto acc, const auto &line) {
                               auto &[hIndex, vIndex, sum] = acc;
                               if (vIndex++ % vDiff == 0) {
                                 hIndex += hDiff;
                                 sum += line[hIndex % line.size()] == '#';
                               }
                               return acc;
                             }));
  };

  long numTrees = countTrees(1, 1) * countTrees(3, 1) * countTrees(5, 1) * countTrees(7, 1) * countTrees(1, 2);

  clog << numTrees << '\n';
}
