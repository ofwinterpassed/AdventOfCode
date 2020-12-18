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

int main(int argc, char** argv) {

  long sum = 0;
  for (string line; getline(cin, line);) {
    stack<pair<long, char>> result;
    result.push(pair(0l, '+'));

    for (size_t index = 0; index < line.size(); ++index) {
      index = line.find_first_of("+*()1234567890", index);
      if (index == string::npos) {
        --index;
        break;
      }
      char token = line[index];
      switch (token) {
      case '(': {
        result.push(pair(0l, '('));
        result.push(pair(0l, '+'));
      } break;
      case ')': {
        auto r = result.top().first;
        result.pop();
        while (result.top().second != '(') {
          apply(result.top().second, result.top().first, r);
          r = result.top().first;
          result.pop();
        }
        apply(result.top().second, result.top().first, r);
        r = result.top().first;
        result.pop();
        apply(result.top().second, result.top().first, r);
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
    while (result.size() > 1) {
      auto r = result.top().first;
      result.pop();
      apply(result.top().second, result.top().first, r);
    }

    sum += result.top().first;
  }
  cout << sum << '\n';
}
