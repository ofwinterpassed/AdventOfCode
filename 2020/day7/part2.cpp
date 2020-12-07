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

  vector<string> input;
  for (string line; getline(cin, line);) {
    input.emplace_back(move(line));
  }

  stack<pair<string, int>> bagsToMatch;
  bagsToMatch.push(pair(string("shiny gold"), 1));
  int sum = 0;
  while (!bagsToMatch.empty()) {
    auto [color, times] = bagsToMatch.top();
    regex r(color + R"raw( bags contain (no other bags\.|(.*)\.))raw");
    bagsToMatch.pop();
    for (auto &rule : input) {
      smatch match;
      if (regex_match(rule, match, r) && match[2].matched) {
        static regex r1(R"raw(([0-9]+) ([a-z ]+) bag)raw");
        string containing = match[2].str();
        smatch match2;
        while (regex_search(containing, match2, r1)) {
          int numBags;
          from_chars(&*match2[1].first, &*match2[1].second, numBags);
          sum += numBags * times;
          bagsToMatch.push(pair(match2[2].str(), numBags * times));
		  containing = match2.suffix();
        }
      }
    }
  }

  cout << sum << '\n';
}
