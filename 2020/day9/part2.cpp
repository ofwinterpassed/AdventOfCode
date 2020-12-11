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

  long value = 257342611;
  auto iter = input.begin();
  while (iter != input.end()) {
    bool found = false;
    long sum = 0;
    auto iter2 = iter;
    for (; iter2 != input.end() && !found; ++iter2) {
      sum += *iter2;
      found = sum == value;
    }
    if (found) {
      auto minmaxiter = minmax_element(iter, iter2);
      cout << *minmaxiter.first + *minmaxiter.second << '\n';
      break;
    }
    ++iter;
  }

  cout << "Done\n";
}
