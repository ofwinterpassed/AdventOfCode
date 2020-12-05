#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
int main(int argc, char **argv) {
  vector<int> values;
  for (array<char, 9> input; cin.getline(&input[0], 9);) {
    int val = 0;
    from_chars(input.data(), input.data() + input.size(), val);
    values.emplace_back(val);
  }

  for (auto it1 = values.cbegin(); it1 != values.cend(); ++it1) {
    if (*it1 <= 2020) {
      for (auto it2 = next(it1); it2 != values.cend(); ++it2) {
        auto partSum = *it1 + *it2;
        if (partSum <= 2020) {
          auto it3 = find_if(next(it2), values.cend(), [partSum](auto val) { return (partSum + val) == 2020; });
          if (it3 != values.cend()) {
            clog << *it1 * *it2 * *it3 << '\n';
            break;
          }
        }
      }
    }
  }
  clog << "finished\n";
}
