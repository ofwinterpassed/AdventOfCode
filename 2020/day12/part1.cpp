#include <algorithm>
#include <array>
#include <cassert>
#include <charconv>
#include <complex>
#include <fstream>
#include <iostream>
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
      switch (val) {
      default:
        assert(false);
        break;
      case 90:
        dir *= complex<float>{0, 1};
      case 180:
        dir *= complex<float>{0, 1};
      case 270:
        dir *= complex<float>{0, 1};
      }
    } break;
    case 'L': {
      switch (val) {
      default:
        assert(false);
        break;
      case 90:
        dir *= complex<float>{0, -1};
      case 180:
        dir *= complex<float>{0, -1};
      case 270:
        dir *= complex<float>{0, -1};
      }
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
