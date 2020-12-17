#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct cell {
  int x, y, z;
};

bool operator<(const cell& a, const cell& b) { return tie(a.z, a.y, a.x) < tie(b.z, b.y, b.x); }

int main(int argc, char** argv) {

  vector<cell> cells;
  int y = 0;
  for (string line; getline(cin, line); ++y) {
    int x = 0;
    for (auto c : line) {
      if (c == '#')
        cells.emplace_back(x, y, 0);
      ++x;
    }
  }
  {
    int y = -1000;
    int z = -1000;
    int oldx = -8;
        cout << '\n';
    for (auto c : cells) {
      if (c.y != y) {
        for (int x = oldx; x < 16; ++x)
          cout << '.';
        y = c.y;
        cout << '\n';
        oldx = -8;
      }
      if (c.z != z) {
        z = c.z;
        cout << '\n';
      }
      for (int x = oldx; x < c.x; ++x)
        cout << '.';
      cout << '#';
      oldx = c.x + 1;
    }
  }

  for (unsigned n = 0; n < 6; ++n) {
    map<cell, pair<int, bool>> newcells;
    for (auto& oldcell : cells) {
      for (int ii = oldcell.x - 1; ii < oldcell.x + 2; ++ii)
        for (int jj = oldcell.y - 1; jj < oldcell.y + 2; ++jj)
          for (int kk = oldcell.z - 1; kk < oldcell.z + 2; ++kk) {
            auto& [c, n] = *newcells.try_emplace(cell{ii, jj, kk}, pair(0, false)).first;
            ++n.first;
            if ((ii == oldcell.x && jj == oldcell.y && kk == oldcell.z))
              n.second = true;
          }
    }
    auto livecells = cells.size();
    cout << livecells << '\n';
    cells.clear();
    for (auto& c : newcells) {
      if ((c.second.first > 2) && ((c.second.first - c.second.second) < 4))
        cells.emplace_back(c.first);
    }
    int y = -1000;
    int z = -1000;
    int oldx = -8;
        cout << '\n';
    for (auto c : cells) {
      if (c.y != y) {
        for (int x = oldx; x < 16; ++x)
          cout << '.';
        y = c.y;
        cout << '\n';
        oldx = -8;
      }
      if (c.z != z) {
        z = c.z;
        cout << '\n';
      }
      for (int x = oldx; x < c.x; ++x)
        cout << '.';
      cout << '#';
      oldx = c.x + 1;
    }
  }
  auto livecells = cells.size();
  cout << livecells << '\n';
}
