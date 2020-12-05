#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
int main(int argc, char **argv) {

  vector<string> values;
  for (string input; getline(cin, input);) {
    values.emplace_back(input);
  }

  auto numApproved = count_if(values.cbegin(), values.cend(), [](const auto &line) {
    auto dashPos = line.find('-');
    auto colonPos = line.find(':', dashPos);
    int minVal;
    from_chars(line.data(), line.data() + dashPos, minVal);
    int maxVal;
    from_chars(line.data() + dashPos + 1, line.data() + colonPos - 1, maxVal);
    char requiredChar = line[colonPos - 1];

    int numRequired = count(next(line.cbegin(), colonPos + 2), line.cend(), requiredChar);
    return (minVal <= numRequired) && (numRequired <= maxVal);
  });
  clog << numApproved << '\n';
}
