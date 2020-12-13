#include <algorithm>
#include <array>
#include <cassert>
#include <charconv>
#include <complex>
#include <fstream>
#include <iostream>
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

  string line;
  getline(cin, line);
  getline(cin, line);

  long index = -1;
  auto view = line | split(',') | ranges::views::transform([&index](auto &&rng) {
                string_view numString(&*rng.begin(), distance(rng.begin(), rng.end()));
                long val = 1;
                if (numString != "x") {
                  from_chars(numString.begin(), numString.end(), val);
                  cout << val << '\n';
                }
                return tuple(++index, val);
              });

  long value = 13;
  long acc = 1;
  for (auto [index, val] : view) {
    while ((value + index) % val != 0) {
      value += acc;
    }
    acc *= val;
    clog << value << ' ' << acc << endl;
  }

  cout << value << '\n';
}
