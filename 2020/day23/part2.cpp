#include <algorithm>
#include <charconv>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {

  list<int> numbers;
  string line;
  getline(cin, line);
  transform(line.begin(), line.end(), inserter(numbers, numbers.begin()), [](char c) { return c - '0'; });
  vector<list<int>::iterator> map(1000000);
  auto it = numbers.begin();
  for (; it != numbers.end(); ++it)
    map[*it] = it;
  --it;

  for (int i = 10; i < 1000001; ++i) {
    numbers.push_back(i);
    map[i] = ++it;
  }

  auto currentIter = numbers.begin();
  for (int i = 0; i < 10000000; ++i) {
    auto next1 = next(currentIter);
    if (next1 == numbers.end())
      next1 = numbers.begin();
    auto next2 = next(next1);
    if (next2 == numbers.end())
      next2 = numbers.begin();
    auto next3 = next(next2);
    if (next3 == numbers.end())
      next3 = numbers.begin();
    int destination = *currentIter - 1;
    if (destination == 0)
      destination = 1000000;
    while ((destination == *next1) || (destination == *next2) || (destination == *next3)) {
      destination = destination - 1;
      if (destination == 0)
        destination = 1000000;
    }
    auto destIter = map[destination];
    numbers.splice(++destIter, numbers, next1, next(next1));
    numbers.splice(destIter, numbers, next2, next(next2));
    numbers.splice(destIter, numbers, next3, next(next3));
    ++currentIter;
    if (currentIter == numbers.end())
      currentIter = numbers.begin();
  }
  auto oneIter = map[1];
  auto next1 = next(oneIter);
  if (next1 == numbers.end())
    next1 = numbers.begin();
  auto next2 = next(next1);
  if (next2 == numbers.end())
    next2 = numbers.begin();

  cout << long(*next1) * long(*next2) << '\n';

  return 0;
}

