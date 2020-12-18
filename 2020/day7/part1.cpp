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
	string toMatch = move(bagsToMatch.top());
    bagsToMatch.pop();
    for (auto &rule : input) {
			auto del = rule.find(" bags contain ");
      if ((rule.find(toMatch, del) != string::npos) && find(matching.cbegin(), matching.cend(), rule.substr(0, del)) == matching.cend()) {
        matching.emplace_back(rule.substr(0, del));
        bagsToMatch.emplace(rule.substr(0, del));
      }
    }
  }
  //for (auto bag : matching) {
    //clog << bag << "\n";
  //}

  cout << matching.size() << '\n';
}
