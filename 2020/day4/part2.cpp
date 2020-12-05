#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <utility>
#include <vector>

using namespace std;

bool validatebyr(const string &pass) {
  static regex r("byr:([12][09][0-9]{2})( |$)");

  smatch match;
  if (regex_search(pass, match, r)) {
    int year;
    from_chars(&*match[1].first, &*match[1].second, year);
    return 1920 <= year && year <= 2002;
  }
  return false;
}

bool validateiyr(const string &pass) {
  static regex r("iyr:(20[12][0-9])( |$)");

  smatch match;
  if (regex_search(pass, match, r)) {
    int year;
    from_chars(&*match[1].first, &*match[1].second, year);
    return 2010 <= year && year <= 2020;
  }
  return false;
}

bool validateeyr(const string &pass) {
  static regex r("eyr:(20[23][0-9])( |$)");

  smatch match;
  if (regex_search(pass, match, r)) {
    int year;
    from_chars(&*match[1].first, &*match[1].second, year);
    return 2020 <= year && year <= 2030;
  }
  return false;
}

bool validatehgt(const string &pass) {
  static regex r("hgt:([15-7][0-9]{1,2})(cm|in)( |$)");

  smatch match;
  if (regex_search(pass, match, r)) {
    int height;
    from_chars(&*match[1].first, &*match[1].second, height);
    if (match[2] == "cm") {
      return 150 <= height && height <= 193;
    }
    return 59 <= height && height <= 76;
  }
  return false;
}

bool validatehcl(const string &pass) {
  static regex r("hcl:#[0-9a-f]{6}( |$)");

  smatch match;
  return regex_search(pass, match, r);
}

bool validateecl(const string &pass) {
  static regex r("ecl:(amb|blu|brn|gry|grn|hzl|oth)( |$)");

  smatch match;
  return regex_search(pass, match, r);
}

bool validatepid(const string &pass) {
  static regex r("pid:[0-9]{9}( |$)");

  smatch match;
  return regex_search(pass, match, r);
}

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
    return validatebyr(line) && validateiyr(line) && validateeyr(line) && validatehgt(line) && validatehcl(line) &&
           validateecl(line) && validatepid(line);
  });

  clog << numValid << '\n';
}
