#include <algorithm>
#include <charconv>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {

  string line;
  getline(cin, line);
  vector<int> numbers(1000000);
  int prev = 999999;
  for (char a : line)
    prev = numbers[prev] = a - '0' - 1;
  numbers[prev] = 9;

  iota(numbers.begin() + 9, numbers.end() - 1, 10);

  int currentval = 0;
  for (int i = 0; i < 10000000; ++i) {
    int next1val = numbers[currentval];
    int next2val = numbers[next1val];
    int next3val = numbers[next2val];
    int destination = currentval;
    do {
      destination = destination == 0 ? 999999 : destination - 1;
    } while ((destination == next1val) || (destination == next2val) || (destination == next3val));
    numbers[currentval] = exchange(numbers[next3val], numbers[destination]);
    numbers[destination] = next1val;
    currentval = numbers[currentval];
  }
  int next1 = numbers[0];
  int next2 = numbers[next1];

  cout << long(next1 + 1) * long(next2 + 1) << '\n';

  return 0;
}

