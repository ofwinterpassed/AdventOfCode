
#define _GLIBCXX_REGEX_STATE_LIMIT 1000000
#include <algorithm>
#include <cassert>
#include <charconv>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

using namespace std;

struct rule {
  char c;
  string regexp;
  vector<vector<int>> subrules;
};
static string indent;
struct indenter {
  indenter() { indent.append("\t|"); }
  ~indenter() {
    indent.pop_back();
    indent.pop_back();
  }
};

void eval(map<int, rule>& rules, int ruleno) {

  auto found = rules.find(ruleno);
  if (found == rules.end())
    assert(false);
  auto& thisrule = found->second;
  if (!thisrule.regexp.empty())
    return;
  if (thisrule.subrules.empty()) {
    thisrule.regexp.push_back(thisrule.c);
	return;
  }

  indenter i;

  if (thisrule.subrules.size() > 1)
    thisrule.regexp.append("(");
  for (auto rno : thisrule.subrules[0]) {
    eval(rules, rno);
    thisrule.regexp.append(rules[rno].regexp);
  }

  for (auto sr = 1; sr < thisrule.subrules.size(); ++sr) {
    thisrule.regexp.append("|");
    for (auto rno : thisrule.subrules[sr]) {
      eval(rules, rno);
      thisrule.regexp.append(rules[rno].regexp);
    }
  }
  if (thisrule.subrules.size() > 1)
    thisrule.regexp.append(")");
}

int main(int argc, char** argv) {

  map<int, rule> rules;
  for (string line; getline(cin, line) && !line.empty();) {
    auto colon = line.find(':');
    int ruleno;
    from_chars(line.data(), line.data() + colon, ruleno);
    auto& thisrule = rules.emplace(ruleno, rule{0,{}, {}}).first->second;
    if (line[colon + 2] == '"')
      thisrule.c = line[colon + 3];
    else {
      size_t start = colon + 2;
      size_t end = line.find('|', start);
      for (; end != string::npos; start = exchange(end, line.find('|', end + 1)) + 2) {
        auto& subrule = thisrule.subrules.emplace_back();
        auto space = line.find(' ', start);
        for (; space < end; start = exchange(space, line.find(' ', space + 1)) + 1) {
          int ruleno1;
          from_chars(line.data() + start, line.data() + space, ruleno1);
          subrule.emplace_back(ruleno1);
        }
      }
      auto& subrule = thisrule.subrules.emplace_back();
      int ruleno1;
      auto space = line.find(' ', start);
      for (; space < end; start = exchange(space, line.find(' ', space + 1)) + 1) {
        from_chars(line.data() + start, line.data() + space, ruleno1);
        subrule.emplace_back(ruleno1);
      }
      from_chars(line.data() + start, line.data() + space, ruleno1);
      subrule.emplace_back(ruleno1);
    }
  }

  eval(rules, 0);
  clog << rules[0].regexp << endl;
  regex r(rules[0].regexp);
  smatch m;

  int validmessages = 0;
  for (string line; getline(cin, line);) {
    clog << "checking message: " << line << endl;
	regex_match(line,m,r);
    validmessages += !m.empty();
  }

  cout << validmessages << '\n';
}

