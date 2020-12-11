#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  vector<long> input;
  for (string line; getline(cin, line);) {
    long value;
    from_chars(line.data(), line.data() + line.size(), value);
    input.emplace_back(value);
  }

  sort(input.begin(), input.end());
  input.emplace_back(input.back() + 3);

  vector<long long> paths;
  for (auto iter = input.begin(); iter != input.end(); ++iter) {
    long long numpaths = *iter <= 3;
    auto riter = prev(iter);
    for (auto biter = paths.rbegin(); (biter != paths.rend()) && (*riter >= *iter - 3); ++biter, --riter) {
      numpaths += *biter;
    }
    paths.emplace_back(numpaths);
    clog << *iter << ' ' << numpaths << '\n';
  }
  cout << paths.back() << '\n';
}
