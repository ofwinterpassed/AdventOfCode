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
  vector<string> matching;
  stack<string> bagsToMatch;
  bagsToMatch.push("shiny gold");
  while (!bagsToMatch.empty()) {
    regex r(string("(.*) bags contain .*") + bagsToMatch.top() + ".*");
    bagsToMatch.pop();
    for (auto &rule : input) {
      smatch match;
      if (regex_match(rule, match, r) && find(matching.cbegin(), matching.cend(), match[1].str()) == matching.cend()) {
        matching.emplace_back(match[1].str());
        bagsToMatch.push(match[1].str());
      }
    }
  }
  for (auto bag : matching) {
    clog << bag << "\n";
  }

  cout << matching.size() << '\n';
}
