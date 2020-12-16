#include <algorithm>
#include <charconv>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {

  vector<vector<string>> input;
  for (string line; getline(cin, line);) {
    auto& section = input.emplace_back();
    section.emplace_back(move(line));
    while (getline(cin, line) && !line.empty()) {
      section.emplace_back(move(line));
    }
  }

  vector<pair<int, int>> valid_ranges;
  for (auto& line : input[0]) {
    auto colon = line.find(':');
    auto split = line.find(" or ", colon);
    auto dash1 = line.find('-', colon);
    auto dash2 = line.find('-', split);
    int min, max;
    from_chars(line.data() + colon + 2, line.data() + dash1, min);
    from_chars(line.data() + dash1 + 1, line.data() + split, max);
    valid_ranges.emplace_back(min, max);
    from_chars(line.data() + split + 4, line.data() + dash2, min);
    from_chars(line.data() + dash2 + 1, line.data() + line.size(), max);
    valid_ranges.emplace_back(min, max);
  }

  int errorrate = 0;
  for (auto lineIter = next(input[2].begin()); lineIter != input[2].end(); ++lineIter) {
    auto& line = *lineIter;
    int val;
    for (size_t lastEnd = 0, start = 0, end = line.find(','); lastEnd != string::npos;
         start = (lastEnd = exchange(end, line.find(',', end + 1))) + 1) {
      from_chars(line.data() + start, line.data() + min(end, line.size()), val);

      if (all_of(valid_ranges.begin(), valid_ranges.end(),
                  [val](auto range) { return (val < range.first) || (val > range.second); })) {
        errorrate += val;
      }
    }
  }

  cout << errorrate << '\n';
}
