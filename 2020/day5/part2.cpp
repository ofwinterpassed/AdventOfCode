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

  vector<string> input;
  for (string line; getline(cin, line);) {
    input.emplace_back(move(line));
  }

  vector<unsigned int> seatids;
  transform(input.cbegin(), input.cend(), back_inserter(seatids), [](const auto &line) {
    unsigned int seatid = 0;
    for (auto c : line) {
      seatid <<= 1;
      if (c == 'B' || c == 'R')
        ++seatid;
    }
    return seatid;
  });

  sort(seatids.begin(), seatids.end());
  auto nexttomine = adjacent_find(seatids.cbegin(), seatids.cend(), [](auto a, auto b) { return b - a == 2; });

  clog << *nexttomine + 1 << '\n';
}
