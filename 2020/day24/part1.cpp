#include <algorithm>
#include <charconv>
#include <iostream>
#include <iterator>
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

  cout << tiles.size() << '\n';

  return 0;
}

