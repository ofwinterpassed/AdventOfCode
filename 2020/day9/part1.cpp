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

  auto iter = next(input.begin(), 25);
  while (iter != input.end()) {
    bool found = false;
      cout << *iter << endl;
    for (auto iter2 = prev(input.begin(), 25); iter2 != iter && !found; ++iter2) {
      found = find_if(next(iter2), iter, [=](auto val) { return (val + *iter2) == *iter; }) != iter;
    }
    if (!found) {
      cout << *iter << '\n';
      break;
    }
	++iter;
  }

  cout << "Done\n";
}
