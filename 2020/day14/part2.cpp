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

int main(int argc, char** argv) {

  vector<string> input;
  for (string line; getline(cin, line);)
    input.emplace_back(move(line));
  map<long, long> values;
  vector<pair<long, long>> masks;
  for (string_view line : input) {
    if (line.starts_with("mask")) {
      masks.clear();
      masks.emplace_back(pair(0l, 0l));
      auto maskString = line.substr(7);
      for (char a : maskString) {
        for (auto& mask : masks) {
          mask.first <<= 1;
          mask.second <<= 1;
        }
        switch (a) {
        case 'X': {
          auto mcp = masks;
          for (auto [notmask, ormask] : mcp) {
            masks.emplace_back(pair(notmask, ormask + 1));
          }
        } break;
        case '1':
          for (auto& [notmask, ormask] : masks) {
            ++ormask;
          }
          break;
        case '0':
          for (auto& [notmask, ormask] : masks) {
            ++notmask;
          }
          break;
        }
      }
    } else {
      auto posbracket = line.find(']');
      long address;
      from_chars(line.data() + 4, line.data() + posbracket, address);
      long val;
      from_chars(line.data() + posbracket + 4, line.data() + line.size(), val);
      for (auto [notmask, ormask] : masks) {
        auto maskedaddress = (notmask & address) | ormask;
        values[maskedaddress] = val;
      }
    }
  }

  long sum = 0;
  for (auto [address, value] : values) {
    sum += value;
  }

  cout << sum << '\n';
}
