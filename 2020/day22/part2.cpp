#include <algorithm>
#include <array>
#include <charconv>
#include <deque>
#include <iostream>
#include <set>
#include <string>
#include <tuple>

using namespace std;

pair<long, long> game(array<deque<long>, 2>& decks, long p1size, long p2size) {
  set<array<deque<long>, 2>> previous;
  while (none_of(decks.begin(), decks.end(), [](auto&& d) { return d.empty(); })) {
    decltype(decks.begin()) loser;
    auto winner = loser;

    if (previous.count(decks))
      return {1, 0};

    if (all_of(decks.begin(), decks.end(), [](auto& d) { return d.size() > d.front(); })) {
      auto subdecks = decks;
      for (auto& d : subdecks) {
        d.resize(d.front() + 1);
        d.pop_front();
      }
      auto [loseridx, winneridx] = game(subdecks, get<0>(decks).front(), get<1>(decks).front());

      loser = next(decks.begin(), loseridx);
      winner = next(decks.begin(), winneridx);
    } else
      tie(loser, winner) = minmax_element(decks.begin(), decks.end());

	previous.insert(decks);
    winner->emplace_back(winner->front());
    winner->emplace_back(loser->front());
    winner->pop_front();
    loser->pop_front();
  }

  auto [loser, winner] = minmax_element(decks.begin(), decks.end());
  return {distance(decks.begin(), loser), distance(decks.begin(), winner)};
}

int main(int argc, char** argv) {

  array<deque<long>, 2> decks;
  for (string line; getline(cin, line);) {
    while (getline(cin, line) && !line.empty())
      from_chars(line.data(), line.data() + line.size(), get<0>(decks).emplace_back());
    getline(cin, line);
    while (getline(cin, line) && !line.empty())
      from_chars(line.data(), line.data() + line.size(), get<1>(decks).emplace_back());
  }
  auto [loseridx, winneridx] = game(decks, get<0>(decks).front(), get<1>(decks).front());

  auto winner = next(decks.begin(), winneridx);

  long score = 0;
  for (int m = winner->size(); !winner->empty(); winner->pop_front(), --m)
    score += m * winner->front();

  cout << score << '\n';

  return 0;
}

