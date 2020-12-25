#include <algorithm>
#include <charconv>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>

using namespace std;

int main(int argc, char** argv) {

  set<pair<int, int>> tiles;
  for (string line; getline(cin, line);) {
    auto coord = pair(0, 0);
    for (size_t i = 0; i < line.size(); ++i) {
      switch (line[i]) {
      case 'w':
        --coord.first;
        break;
      case 'e':
        ++coord.first;
        break;
      case 'n': {
        coord.first -= abs(coord.second % 2);
        --coord.second;
        if (line[++i] == 'e')
          ++coord.first;
      } break;
      case 's': {
        coord.first -= abs(coord.second % 2);
        ++coord.second;
        if (line[++i] == 'e')
          ++coord.first;
      } break;
      }
    }
    auto it = tiles.find(coord);
    if (it == tiles.end())
      tiles.insert(coord);
    else
      tiles.erase(it);
  }

  vector<pair<int, int>> oldtiles;
  oldtiles.reserve(tiles.size());
  for (auto& a : tiles)
    oldtiles.emplace_back(move(a));
  tiles.clear();

  for (int i = 0; i < 100; ++i) {
    map<pair<int, int>, pair<int, bool>> next;
    for (auto& old : oldtiles) {
      {
        auto [it, added] = next.try_emplace(old, pair(1, true));
        if (!added) {
          ++it->second.first;
          it->second.second = true;
        }
      }

      {
        auto w = old;
        --w.first;
        auto [it, added] = next.try_emplace(w, pair(1, false));
        if (!added)
          ++it->second.first;
      }

      {
        auto e = old;
        ++e.first;
        auto [it, added] = next.try_emplace(e, pair(1, false));
        if (!added)
          ++it->second.first;
      }

      {
        auto nw = old;
        nw.first -= abs(old.second % 2);
        --nw.second;
        auto [it, added] = next.try_emplace(nw, pair(1, false));
        if (!added)
          ++it->second.first;
      }

      {
        auto ne = old;
        ne.first -= abs(old.second % 2);
        --ne.second;
        ++ne.first;
        auto [it, added] = next.try_emplace(ne, pair(1, false));
        if (!added)
          ++it->second.first;
      }

      {
        auto sw = old;
        sw.first -= abs(old.second % 2);
        ++sw.second;
        auto [it, added] = next.try_emplace(sw, pair(1, false));
        if (!added)
          ++it->second.first;
      }

      {
        auto se = old;
        se.first -= abs(old.second % 2);
        ++se.second;
        ++se.first;
        auto [it, added] = next.try_emplace(se, pair(1, false));
        if (!added)
          ++it->second.first;
      }
    }
    oldtiles.clear();
    for (auto& [coord, state] : next) {
      if ((state.first > 1) && ((state.first - state.second) < 3))
        oldtiles.emplace_back(coord);
    }
  }

  cout << oldtiles.size() << '\n';

  return 0;
}

