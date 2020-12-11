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

int main(int argc, char **argv) {

  vector<string> input;
  input.emplace_back();
  for (string line; getline(cin, line);) {
    input.emplace_back(".").append(std::move(line)).append(".");
  }
  input.emplace_back();
  input.front().resize(input[1].size(), '.');
  input.back().resize(input[1].size(), '.');

  const size_t bottom = 0u, top = input.size() - 1, left = 0u, right = input[0].size() - 1;

  auto findInDir = [&](auto row, auto column, auto rd, auto cd) {
    row += rd;
    column += cd;
    while (row > bottom && row < top && column > left && column < right) {
      if (input[row][column] == '#')
        return true;
      else if (input[row][column] == 'L')
        return false;
      row += rd;
      column += cd;
    }
    return false;
  };
  auto countTaken = [&](auto row, auto column) {
    int taken = 0;
	array<pair<int, int>, 8> dirs{{{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}}};
    for (auto [rd, cd] : dirs) {
      taken += findInDir(row, column, rd, cd);
    }
    return taken;
  };

  auto cp = input;
  bool stable = false;
  while (!stable) {
    stable = true;
    for (size_t row = 1; row < (input.size() - 1); ++row) {
      for (size_t column = 1; column < (input[row].size() - 1); ++column) {
        int taken = countTaken(row, column);
        switch (input[row][column]) {
        case 'L': {
          if (taken == 0) {
            cp[row][column] = '#';
            stable = false;
          }
          break;
        }
        case '#': {
          if (taken >= 5) {
            cp[row][column] = 'L';
            stable = false;
          }
          break;
        }
        default:;
        }
      }
    }
    input = cp;
    for (auto &&line : input)
      clog << line << '\n';
    clog << endl;
  }
  for (auto &&line : input)
    clog << line << '\n';
  cout << transform_reduce(cp.begin(), cp.end(), 0, plus<>(), [](auto &&line) {
    return count(line.begin(), line.end(), '#');
  }) << '\n';
}
