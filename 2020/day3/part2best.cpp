#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <tuple>
#include <type_traits>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  vector<string> values;
  for (string input; getline(cin, input);) {
    values.emplace_back(input);
  }

  auto countTrees = [&](int hDiff, int vDiff) -> long {
    auto view =
        views::iota(0, int((values.size()) / vDiff + min(int(values.size() % vDiff), 1))) | views::filter([&](auto a) {
          auto &line = values[a * vDiff];
          return line[(a * hDiff) % line.size()] == '#';
        });
    return distance(view.begin(), view.end());
  };

  long numTrees = countTrees(1, 1) * countTrees(3, 1) * countTrees(5, 1) * countTrees(7, 1) * countTrees(1, 2);

  cout << numTrees << '\n';
}
