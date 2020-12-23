#include <algorithm>
#include <charconv>
#include <iostream>
#include <iterator>
#include <list>
#include <string>

using namespace std;

int main(int argc, char** argv) {

  list<int> numbers;
  string line;
  getline(cin, line);
  transform(line.begin(), line.end(), inserter(numbers, numbers.begin()), [](char c) { return c - '0'; });

  auto currentIter = numbers.begin();
  for (int i = 0; i < 100; ++i) {
    for (auto a : numbers)
      clog << a;
    clog << endl;
    int destination = *currentIter - 1;
    auto next1 = next(currentIter);
    if (next1 == numbers.end())
      next1 = numbers.begin();
    auto next2 = next(next1);
    if (next2 == numbers.end())
      next2 = numbers.begin();
    auto next3 = next(next2);
    if (next3 == numbers.end())
      next3 = numbers.begin();
    if (destination == 0)
      destination = 9;
    while ((destination == *next1) || (destination == *next2) ||
           (destination == *next3)) {
      destination = destination - 1;
      if (destination == 0)
        destination = 9;
    }
    auto destIter = find(numbers.begin(), numbers.end(), destination);
    numbers.splice(++destIter, numbers, next1, next(next1));
    for (auto a : numbers)
      clog << a;
    clog << endl;
    numbers.splice(destIter, numbers, next2, next(next2));
    for (auto a : numbers)
      clog << a;
    clog << endl;
    numbers.splice(destIter, numbers, next3, next(next3));
    for (auto a : numbers)
      clog << a;
    clog << endl;
    ++currentIter;
    if (currentIter == numbers.end())
      currentIter = numbers.begin();
  }
  transform(numbers.begin(), numbers.end(), line.begin(), [](int i) { return i + '0'; });
  auto oneIter = find(line.begin(), line.end(), '1');
  rotate(line.begin(), oneIter, line.end());

  cout << line << '\n';

  return 0;
}

