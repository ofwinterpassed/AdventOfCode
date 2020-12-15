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

  auto last = numbers.find(lastVal);
  while (index < 30000000) {
    if (last == numbers.end()) {
      lastVal = 0;
    } else {
      lastVal = last->second.second;
    }
    last = numbers.find(lastVal);
    if (last == numbers.end()) {
      last = numbers.insert(pair(lastVal, pair(index, 0l))).first;
    } else {
      last->second.second = index - last->second.first;
      last->second.first = index;
    }
    ++index;
  }

  cout << lastVal << '\n';
}
