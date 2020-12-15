#include <charconv>
#include <iostream>
#include <map>
#include <ranges>
#include <string>

using namespace std;
using namespace std::ranges::views;

int main(int argc, char** argv) {

  long index = 0;
  map<long, pair<long, long>> numbers;
  string line;
  getline(cin, line);

  long lastVal = 0;
  for (auto a : line | split(',') | ranges::views::transform([&lastVal](auto&& rng) {
                  from_chars(&*rng.begin(), &*rng.begin() + distance(rng.begin(), rng.end()), lastVal);
                  return lastVal;
                })) {
    numbers[a] = pair(index, 0l);
    ++index;
  }

  while (index < 2020) {
    auto last = numbers.find(lastVal);
    if (last == numbers.end()) {
      lastVal = 0;
    } else {
      lastVal = last->second.second;
    }
    auto next = numbers.find(lastVal);
    if (next == numbers.end()) {
      numbers[lastVal] = pair(index, 0l);
    } else {
      next->second.second = index - next->second.first;
      next->second.first = index;
    }
    ++index;
  }

  cout << lastVal << '\n';
}
