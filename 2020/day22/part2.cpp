#include <algorithm>
#include <array>
#include <charconv>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

pair<char, char> game(array<pair<array<char, 50>, char>, 2>& decks) {
  set<array<pair<array<char, 50>, char>, 2>> previous;
  while (none_of(decks.begin(), decks.end(), [](auto&& d) { return d.second == 0; })) {
    decltype(decks.begin()) loser;
    auto winner = loser;

    if (previous.count(decks))
      return {1, 0};

    if (all_of(decks.begin(), decks.end(), [](auto& d) { return d.second > d.first.front(); })) {
      auto subdecks = decks;
      for (auto& d : subdecks) {
        d.second = d.first.front();
        rotate(d.first.begin(), d.first.begin() + 1, d.first.begin() + d.second + 1);
      }
      auto [loseridx, winneridx] = game(subdecks);

      loser = next(decks.begin(), loseridx);
      winner = next(decks.begin(), winneridx);
    } else
      tie(loser, winner) = minmax_element(decks.begin(), decks.end());

    previous.insert(decks);
    rotate(winner->first.begin(), next(winner->first.begin()), winner->first.begin() + winner->second);
    winner->first[winner->second] = loser->first.front();
    ++winner->second;
    --loser->second;
    rotate(loser->first.begin(), loser->first.begin() + 1, loser->first.begin() + loser->second + 1);
  }

  auto [loser, winner] =
      minmax_element(decks.begin(), decks.end(), [](auto& a, auto& b) { return a.second < b.second; });
  return {distance(decks.begin(), loser), distance(decks.begin(), winner)};
}

int main(int argc, char** argv) {

  array<pair<array<char, 50>, char>, 2> decks;
  decks[0].second = decks[1].second = 25;
  for (string line; getline(cin, line);) {
    int i = -1;
    while (getline(cin, line) && !line.empty())
      from_chars(line.data(), line.data() + line.size(), get<0>(decks).first[++i]);
    getline(cin, line);
    i = -1;
    while (getline(cin, line) && !line.empty())
      from_chars(line.data(), line.data() + line.size(), get<1>(decks).first[++i]);
  }
  auto [loseridx, winneridx] = game(decks);

  auto winner = next(decks.begin(), winneridx);

  int score = 0;
  int m = winner->second;
  while (m > 0) {
    score += m * winner->first[winner->second - m];
    --m;
  }

  cout << score << '\n';

  return 0;
}

