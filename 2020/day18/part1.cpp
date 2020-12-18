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
    stack<long> result;
    result.push(0);
    stack<char> operations;
    operations.push('+');

    for (size_t index = 0; index < line.size(); ++index) {
      index = line.find_first_of("+*()1234567890", index);
      if (index == string::npos) {
        --index;
        break;
      }
      char token = line[index];
      switch (token) {
      case '(': {
        result.push(0);
        operations.push('+');
      } break;
      case ')': {
        auto r = result.top();
        result.pop();
        operations.pop();
        apply(operations.top(), result.top(), r);
      } break;
      case '+':
      case '*':
        operations.top() = token;
        break;
      default:
        apply(operations.top(), result.top(), token - '0');
        break;
      }
    }
    cout << result.top() << '\n';
    sum += result.top();
  }
  cout << sum << '\n';
}
