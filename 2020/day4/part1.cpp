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

  vector<string> values;
  for (string input; getline(cin, input);) {
    values.emplace_back(move(input));
    while (getline(cin, input) && !input.empty()) {
      values.back().append(" ");
      values.back().append(input);
    }
  }

  auto numValid = count_if(values.cbegin(), values.cend(), [&](const auto &line) {
    return line.find("byr:", 0) != string::npos && line.find("iyr:", 0) != string::npos &&
           line.find("eyr:", 0) != string::npos && line.find("hgt:", 0) != string::npos &&
           line.find("hcl:", 0) != string::npos && line.find("ecl:", 0) != string::npos &&
           line.find("pid:", 0) != string::npos;
  });

  clog << numValid << '\n';
}
