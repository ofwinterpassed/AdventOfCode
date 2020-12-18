#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void apply(char op, long& res, long val) {
  switch (op) {
  case '+':
  case '(':
    res += val;
    break;
  case '*':
    res *= val;
    break;
  }
}
void popapply(stack<pair<long, char>>& result) {
  auto r = result.top().first;
  result.pop();
  apply(result.top().second, result.top().first, r);
}

int main(int argc, char** argv) {

  long sum = 0;
  for (string line; getline(cin, line);) {
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    stack<pair<long, char>> result;
    result.push(pair(0l, '+'));

    for (size_t index = 0; index < line.size(); ++index) {
      char token = line[index];
      switch (token) {
      case '(': {
        result.push(pair(0l, '('));
        result.push(pair(0l, '+'));
      } break;
      case ')': {
        while (result.top().second != '(')
          popapply(result);
        popapply(result);
      } break;
      case '+':
        result.top().second = token;
        break;
      case '*':
        result.top().second = token;
        result.push(pair(0l, '+'));
        break;
      default:
        apply(result.top().second, result.top().first, token - '0');
        break;
      }
    }
    while (result.size() > 1)
      popapply(result);

    sum += result.top().first;
  }
  cout << sum << '\n';
}
