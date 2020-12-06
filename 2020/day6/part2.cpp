#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;
int main(int argc, char **argv) {

  vector<vector<string>> input;
  for (string line; getline(cin, line);) {
    input.emplace_back();
    input.back().emplace_back(move(line));
    while (getline(cin, line) && !line.empty()) {
      input.back().emplace_back(move(line));
    }
  }

  long sum = transform_reduce(input.begin(), input.end(), 0, plus<>(), [](auto &group) {
    unsigned int groupresult = transform_reduce(group.cbegin(), group.cend(), ~0, bit_and<>(), [](const auto &person) {
      return transform_reduce(person.cbegin(), person.cend(), 0, bit_or<>(),
                               [](char c) -> unsigned int { return (1 << (c - 'a')); });
    });
    return popcount(groupresult);
  });

  clog << sum << '\n';
}
