#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct cell {
  int x, y, z, w;
};

bool operator<(const cell& a, const cell& b) { return tie(a.w, a.z, a.y, a.x) < tie(b.w, b.z, b.y, b.x); }

int main(int argc, char** argv) {

  vector<cell> cells;
  int y = 0;
  for (string line; getline(cin, line); ++y) {
    int x = 0;
    for (auto c : line) {
      if (c == '#')
        cells.push_back(cell{x, y, 0, 0});
      ++x;
    }
  }

  for (unsigned n = 0; n < 6; ++n) {
    map<cell, pair<int, bool>> newcells;
    for (auto& oldcell : cells) {
      for (int ii = oldcell.x - 1; ii < oldcell.x + 2; ++ii)
        for (int jj = oldcell.y - 1; jj < oldcell.y + 2; ++jj)
          for (int kk = oldcell.z - 1; kk < oldcell.z + 2; ++kk)
            for (int ll = oldcell.w - 1; ll < oldcell.w + 2; ++ll) {
              auto& [c, n] = *newcells.try_emplace(cell{ii, jj, kk, ll}, pair(0, false)).first;
              ++n.first;
              if ((ii == oldcell.x && jj == oldcell.y && kk == oldcell.z && ll == oldcell.w))
                n.second = true;
            }
    }
    auto livecells = cells.size();
    cout << livecells << '\n';
    cells.clear();
    for (auto& c : newcells)
      if ((c.second.first > 2) && ((c.second.first - c.second.second) < 4))
        cells.emplace_back(c.first);
  }
  auto livecells = cells.size();
  cout << livecells << '\n';
}
