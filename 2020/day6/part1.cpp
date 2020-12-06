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
    while (getline(cin, line) && !line.empty()) {
      input.back().append(line);
    }
  }

  long sum = transform_reduce(input.begin(), input.end(), 0, plus<>(), [](auto &group) {
    sort(group.begin(), group.end());
    group.erase(unique(group.begin(), group.end()), group.end());
    return group.size();
  });

  clog << sum << '\n';
}
