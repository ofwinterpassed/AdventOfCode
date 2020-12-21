
#define _GLIBCXX_REGEX_STATE_LIMIT 1000000
#include <algorithm>
#include <cassert>
#include <charconv>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <vector>

using namespace std;

constexpr const int side = 12;

int main(int argc, char** argv) {

  vector<string> input;
  for (string line; getline(cin, line);)
    input.emplace_back(move(line));

  map<string, set<string>> itoa;
  map<string, set<string>> atoi;
  map<string, int> allin;
  for (auto line : input) {
    auto lp = line.find('(');
    line.back() = ',';
    size_t start = 0;
    size_t end = line.find(' ', start);
    set<string> ingredients;
    for (; end < lp; start = exchange(end, line.find(' ', end + 1)) + 1) {
      ingredients.emplace(line.substr(start, end - start));
      ++allin[line.substr(start, end - start)];
    }
    end = lp + 8;
    start = exchange(end, line.find(',', end + 1)) + 2;

    vector<string> allergens;
    for (; end < string::npos; start = exchange(end, line.find(',', end + 1)) + 2) {
      allergens.emplace_back(line.substr(start, end - start));
    }

    for (auto& al : allergens)
      if (auto [c, n] = atoi.try_emplace(al, ingredients); !n) {
        set<string> todrop;
        for (auto& in : c->second)
          if (!ingredients.contains(in))
            todrop.emplace(in);
        for (auto& in : todrop)
          c->second.erase(in);
      }
  }

  for (auto& [al, ingredients] : atoi) {
    clog << al << ":\n";
    for (auto& in : ingredients)
      clog << in << ' ';
    clog << '\n';
  }

  for (auto& [al, ingredients] : atoi)
    for (auto& in : ingredients)
      itoa[in].emplace(al);

  for (auto& [in, allergens] : itoa) {
    clog << in << " ";
    // for (auto& al : allergens)
    // clog << al << ' ';
    // clog << '\n';
  }

  vector<string> allergens;
  transform(atoi.begin(), atoi.end(), back_inserter(allergens), [](auto&& a) { return a.first; });
  auto comp = [&atoi](auto& a, auto& b) { return atoi[a].size() > atoi[b].size(); };
  while (!allergens.empty()) {
    make_heap(allergens.begin(), allergens.end(), comp);
    auto done = allergens.front();
    pop_heap(allergens.begin(), allergens.end(), comp);
    allergens.pop_back();

    for (auto& nd : allergens) {
      atoi[nd].erase(*atoi[done].begin());
    }
  }

  long sum = 0;
  for (auto& [in, count] : allin)
    if (!itoa.contains(in))
      sum += count;

  clog << itoa.size() << ' ' << atoi.size() << ' ' << sum << '\n';
  for (auto& [al, ingredients] : atoi) {
    for (auto& in : ingredients)
      clog << in << ',';
  }
  return 0;
}

