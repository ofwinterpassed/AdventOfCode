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
    int index1;
    from_chars(line.data(), line.data() + dashPos, index1);
    int index2;
    from_chars(line.data() + dashPos + 1, line.data() + colonPos - 1, index2);
    char requiredChar = line[colonPos - 1];

    return (line[colonPos + 1 + index1] == requiredChar) != (line[colonPos + 1 + index2] == requiredChar);
  });
  clog << numApproved << '\n';
}
