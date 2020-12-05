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

  int index = 0;
  auto numTrees = accumulate(next(values.cbegin()), values.cend(), 0, [&](int a, const auto &line) {
    index += 3;
    return a + int(line[index % line.size()] == '#');
  });

  clog << numTrees << '\n';
}
