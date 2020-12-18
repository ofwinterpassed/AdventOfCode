#include <algorithm>
#include <bit>
#include <charconv>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

vector<int> ticket(string line) {
  vector<int> ret;
  int val;
  for (size_t lastEnd = 0, start = 0, end = line.find(','); lastEnd != string::npos;
       start = (lastEnd = exchange(end, line.find(',', end + 1))) + 1) {
    from_chars(line.data() + start, line.data() + min(end, line.size()), val);
    ret.emplace_back(val);
  }
  return ret;
}

template <unsigned... ints>
long long product(unsigned mask, vector<int>& ticket, std::integer_sequence<unsigned, ints...>) {
  return (1l * ... * ((mask >> ints) % 2 ? ticket[ints] : 1u));
}

template <unsigned... ints> unsigned maskor(const vector<tuple<string, int, int, int, int, unsigned>>& valid_ranges, integer_sequence<unsigned, ints...>) {
  return (get<unsigned>(valid_ranges[ints]) | ...) & 0xfffff;
}

int main(int argc, char** argv) {

  vector<tuple<string, int, int, int, int, unsigned>> valid_ranges;
  vector<int> myticket;
  int maxR = 0, minR = 1000;
  string line;
  while (getline(cin, line) && !line.empty()) {
    auto colon = line.find(':');
    auto split = line.find(" or ", colon);
    auto dash1 = line.find('-', colon);
    auto dash2 = line.find('-', split);
    int mi1, ma1;
    from_chars(line.data() + colon + 2, line.data() + dash1, mi1);
    from_chars(line.data() + dash1 + 1, line.data() + split, ma1);
    minR = min(mi1, minR);
    maxR = max(ma1, maxR);
    int mi2, ma2;
    from_chars(line.data() + split + 4, line.data() + dash2, mi2);
    from_chars(line.data() + dash2 + 1, line.data() + line.size(), ma2);
    valid_ranges.emplace_back(line.substr(0, colon), mi1, ma1, mi2, ma2, ~0);
    minR = min(mi2, minR);
    maxR = max(ma2, maxR);
  }
  getline(cin, line);
  getline(cin, line);
  myticket = ticket(line);

  getline(cin, line);
  getline(cin, line);
  while (getline(cin, line) && !line.empty()) {
    auto nearby = ticket(line);
    if (any_of(nearby.begin(), nearby.end(), [minR, maxR](auto val) { return (val < minR) || (val > maxR); })) {
      continue;
    }
    for (unsigned index = 0; index < nearby.size(); ++index) {
      auto val = nearby[index];
      for (auto& [name, mi1, ma1, mi2, ma2, mask] : valid_ranges) {
        bool invalid = (val < mi1) || ((val > ma1) && (val < mi2)) || (val > ma2);
        mask &= ~(static_cast<unsigned>(invalid) << index);
      }
    }
  }
  for (unsigned index = 0; index < myticket.size(); ++index) {
    auto val = myticket[index];
    for (auto& [name, mi1, ma1, mi2, ma2, mask] : valid_ranges) {
      bool invalid = (val < mi1) || ((val > ma1) && (val < mi2)) || (val > ma2);
      mask &= ~(static_cast<unsigned>(invalid) << index);
    }
  }
  bool notdone = true;
  while (notdone) {
    notdone = false;
    for (size_t i = 0; i < valid_ranges.size(); ++i) {
      auto validmask = get<unsigned>(valid_ranges[i]) & 0xfffff;
      if (popcount(validmask) == 1) {
        for (size_t j = 0; j < valid_ranges.size(); ++j) {
          if (i != j) {
            auto& mask = get<unsigned>(valid_ranges[j]);
            notdone |= validmask & mask;
            mask &= ~validmask;
          }
        }
      }
    }
  }

  unsigned mask = maskor(valid_ranges, make_integer_sequence<unsigned, 6>{});
  long long prod = product(mask, myticket, make_integer_sequence<unsigned, 20>{});

  cout << prod << '\n';
}
