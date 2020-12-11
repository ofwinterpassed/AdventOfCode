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

  auto countTaken = [&](auto row, auto column) {
    int taken = 0;
    taken += input[row - 1][column - 1] == '#';
    taken += input[row - 1][column] == '#';
    taken += input[row - 1][column + 1] == '#';
    taken += input[row][column - 1] == '#';
    taken += input[row][column + 1] == '#';
    taken += input[row + 1][column - 1] == '#';
    taken += input[row + 1][column] == '#';
    taken += input[row + 1][column + 1] == '#';
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
          if (taken >= 4) {
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
  }
  cout << transform_reduce(cp.begin(), cp.end(), 0, plus<>(), [](auto &&line) {
    return count(line.begin(), line.end(), '#');
  }) << '\n';
}
