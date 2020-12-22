#include <algorithm>
#include <charconv>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main(int argc, char** argv) {

  array<queue<long>, 2> decks;
  for (string line; getline(cin, line);) {
    while (getline(cin, line) && !line.empty())
      from_chars(line.data(), line.data() + line.size(), get<0>(decks).emplace());
    getline(cin, line);
    while (getline(cin, line) && !line.empty())
      from_chars(line.data(), line.data() + line.size(), get<1>(decks).emplace());
  }
  while (none_of(decks.begin(), decks.end(), [](auto&& d) { return d.empty(); })) {
    auto [loser, winner] = minmax_element(decks.begin(), decks.end());
    winner->emplace(winner->front());
    winner->emplace(loser->front());
	winner->pop();
    loser->pop();
  }

  auto winner = max_element(decks.begin(), decks.end());

  long score = 0;
  for (int m = winner->size(); !winner->empty(); winner->pop(), --m)
    score += m * winner->front();

  cout << score << '\n';

  return 0;
}

