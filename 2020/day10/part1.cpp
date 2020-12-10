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

long accumulator = 0;

enum class instruction_t : char { acc, jmp, nop };

int main(int argc, char **argv) {

  vector<long> input;
  for (string line; getline(cin, line);) {
    long value;
    from_chars(line.data(), line.data() + line.size(), value);
    input.emplace_back(value);
  }

  sort(input.begin(), input.end());
  input.emplace_back(input.back() + 3);

  adjacent_difference(input.begin(), input.end(), input.begin());
  cout << count(input.begin(), input.end(), 1) *  count(input.begin(), input.end(), 3) << '\n';
}
