#include <algorithm>
#include <array>
#include <cassert>
#include <charconv>
#include <complex>
#include <fstream>
#include <iostream>
#include <numbers>
#include <numeric>
#include <regex>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  complex<float> pos{0, 0};
  complex<float> dir{1, 0};

  for (string line; getline(cin, line);) {
    int val;
    from_chars(line.data() + 1, line.data() + line.size(), val);
    float value = static_cast<float>(val);
    switch (line[0]) {
    case 'F': {
      pos += value * dir;
    } break;
    case 'R': {
      dir *= polar(1.f, -value * numbers::pi_v<float> / 180.f);
    } break;
    case 'L': {
      dir *= polar(1.f, value * numbers::pi_v<float> / 180.f);
    } break;
    case 'E': {
      pos += value;
    } break;
    case 'W': {
      pos -= value;
    } break;
    case 'S': {
      pos -= complex<float>{0, value};
    } break;
    case 'N': {
      pos += complex<float>{0, value};
    } break;
    }
  }
  cout << std::abs(pos.real()) + std::abs(pos.imag()) << '\n';
}
