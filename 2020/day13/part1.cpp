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
  int timeStamp;
  from_chars(line.data(), line.data() + line.size(), timeStamp);
  getline(cin, line);
  auto view = line | split(',');

  int maxWait = timeStamp + 1;
  int busId = 0;
  for (auto &&rng : view) {
    string_view numString(&*rng.begin(), distance(rng.begin(), rng.end()));
    if (numString == "x")
      continue;
    int val;
    from_chars(numString.begin(), numString.end(), val);
    int wait = val - timeStamp % val;
    if (wait < maxWait) {
      maxWait = wait;
      busId = val;
    }
  }
  cout << maxWait * busId << '\n';
}
