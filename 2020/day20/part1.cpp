
#define _GLIBCXX_REGEX_STATE_LIMIT 1000000
#include <algorithm>
#include <cassert>
#include <charconv>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <vector>

using namespace std;

constexpr const int side = 12;

struct tile {
  tile(long id) : id(id) {}
  array<array<unsigned, 4>, 8> sides{
      {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
  long id;
};

struct state {
  int tileIdx = -1;
  int rot = 0;
  int flip = 2;
};

int main(int argc, char** argv) {

  vector<tile> tiles;
  for (string line; getline(cin, line);) {

    auto space = line.find(' ');
    auto colon = line.find(':', space);
    long id;
    from_chars(line.data() + space + 1, line.data() + colon, id);
    auto& t = tiles.emplace_back(id);
    unsigned north = 0;
    unsigned east = 0;
    unsigned south = 0;
    unsigned west = 0;
    unsigned rnorth = 0;
    unsigned reast = 0;
    unsigned rsouth = 0;
    unsigned rwest = 0;
    getline(cin, line);
    for (auto c : line) {
      north <<= 1;
      north += c == '#';
      rnorth >>= 1;
      rnorth += (c == '#') * 0x200;
    }
    east += line.back() == '#';
    reast += (line.back() == '#') * 0x200;
    west += line.front() == '#';
    rwest += (line.front() == '#') * 0x200;

    string last;
    for (string line; getline(cin, line) && !line.empty();) {
      east <<= 1;
      east += line.back() == '#';
      rwest >>= 1;
      rwest += (line.front() == '#') * 0x200;
      west <<= 1;
      west += line.front() == '#';
      reast >>= 1;
      reast += (line.back() == '#') * 0x200;
      swap(last, line);
    }
    for (auto c : last) {
      south <<= 1;
      south += c == '#';
      rsouth >>= 1;
      rsouth += (c == '#') * 0x200;
    }
    t.sides[0][0] = north;
    t.sides[0][1] = east;
    t.sides[0][2] = south;
    t.sides[0][3] = west;

    t.sides[1][0] = east;
    t.sides[1][1] = rsouth;
    t.sides[1][2] = west;
    t.sides[1][3] = rnorth;

    t.sides[2][0] = rsouth;
    t.sides[2][1] = rwest;
    t.sides[2][2] = rnorth;
    t.sides[2][3] = reast;

    t.sides[3][0] = rwest;
    t.sides[3][1] = north;
    t.sides[3][2] = reast;
    t.sides[3][3] = south;

    t.sides[4][0] = rnorth;
    t.sides[4][1] = west;
    t.sides[4][2] = rsouth;
    t.sides[4][3] = east;

    t.sides[5][0] = west;
    t.sides[5][1] = south;
    t.sides[5][2] = east;
    t.sides[5][3] = north;

    t.sides[6][0] = south;
    t.sides[6][1] = reast;
    t.sides[6][2] = north;
    t.sides[6][3] = rwest;

    t.sides[7][0] = reast;
    t.sides[7][1] = rnorth;
    t.sides[7][2] = rwest;
    t.sides[7][3] = rsouth;
  }

  array<state, side * side> grid;
  set<int> used;
  int coord = 0;
  auto check = [&](int i, int j) {
    bool works = true;
    auto& t = grid[i * side + j];
    if (i > 0) {
      auto& l = grid[(i - 1) * side + j];
      works &= tiles[t.tileIdx].sides[t.flip * 4 + t.rot][0] == tiles[l.tileIdx].sides[l.flip * 4 + l.rot][2];
    }
    if (j > 0) {
      auto& l = grid[i * side + (j - 1)];
      works &= tiles[t.tileIdx].sides[t.flip * 4 + t.rot][3] == tiles[l.tileIdx].sides[l.flip * 4 + l.rot][1];
    }
    return works;
  };
  for (auto& a : tiles) {
    for (auto b : a.sides)
      for (auto c : b)
        clog << c << ' ';
    clog << endl;
  }
  while (coord < grid.size()) {
    auto& current = grid[coord];
    if (current.flip == 2) {
      used.erase(current.tileIdx);
      current.flip = 0;
      current.rot = 0;
      int next = current.tileIdx + 1;
      while (used.count(next) && (next < (side * side))) {
        ++next;
      }
      if (next >= (side * side)) {
        current.tileIdx = -1;
        current.flip = 2;
        --coord;
        ++grid[coord].rot;
        for (int i = 0; i < coord; ++i)
          clog << grid[i].tileIdx << ' ';
        clog << coord << endl;
        continue;
      }
      current.tileIdx = next;
      continue;
    } else if (current.rot == 4) {
      current.rot = 0;
      ++current.flip;
      continue;
    }
    bool works = check(coord / side, coord % side);
    if (works) {
      for (int i = 0; i < coord+1; ++i)
        clog << grid[i].tileIdx << ' ';
      clog << coord << endl;
      if (coord == (side * side - 1))
        break;
      used.insert(current.tileIdx);
      ++coord;
    } else {
      ++current.rot;
    }
  }
  int d = 0;
  for (auto& a : grid) {
    for (auto b : tiles[a.tileIdx].sides)
      for (auto c : b)
        clog << c << ' ';
    clog << endl;
    clog << ++d << ' ' << a.tileIdx << ' ' << a.rot << ' ' << a.flip << endl;
  }
  long prod = tiles[grid[0].tileIdx].id * tiles[grid[side - 1].tileIdx].id * tiles[grid[side * (side - 1)].tileIdx].id *
              tiles[grid[side * side - 1].tileIdx].id;

  cout << prod << '\n';
}

