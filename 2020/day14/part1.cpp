#include <algorithm>
#include <array>
#include <cassert>
#include <charconv>
#include <complex>
#include <fstream>
#include <iostream>
#include <map>
#include <numbers>
#include <numeric>
#include <ranges>
#include <regex>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
using namespace std::ranges::views;

int main(int argc, char **argv) {

  vector<string> input;
  for (string line; getline(cin, line);)
    input.emplace_back(move(line));
  map<long, long> values;
  long notmask = 0, ormask = 0;
  for (string_view line : input) {
    if (line.starts_with("mask")) {
      notmask = 0;
      ormask = 0;
      auto maskString = line.substr(7);
      for (char a : maskString) {
        notmask <<= 1;
        ormask <<= 1;
        switch (a) {
        case 'X':
          notmask += 1;
          break;
        case '1':
          notmask += 1;
          ormask += 1;
          break;
        }
      }
    } else {
      auto posbracket = line.find(']');
      long address;
      from_chars(line.data() + 4, line.data() + posbracket, address);
      long val;
      from_chars(line.data() + posbracket + 4, line.data() + line.size(), val);
      values[address] = (notmask & val) | ormask;
    }
  }

  long sum = 0;
  for (auto [address, value] : values) {
    sum += value;
  }

  cout << sum << '\n';
}
