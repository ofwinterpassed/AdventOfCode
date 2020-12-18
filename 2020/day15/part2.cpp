#include <charconv>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

using namespace std;
using namespace std::ranges::views;

int main(int argc, char** argv) {

  string line("11,18,0,20,1,7,16");

  int index = 0;
  vector<int> numbers(30000000, -1);

  int lastVal = 0;
  int nextVal = 0;
  for (size_t lastEnd = 0, start = 0, end = line.find(','); lastEnd != string::npos;
       start = (lastEnd = exchange(end, line.find(',',  end + 1))) + 1) {
    from_chars(line.data() + start, line.data() + min(end, line.size()), lastVal);
    numbers[lastVal] = index;
    ++index;
  }
    nextVal = 0;

  for (; index < 30000000 - 1; ++index) {
    auto& last = numbers[nextVal];
    if (last == -1) {
      last = index;
      nextVal = 0;
    } else {
      nextVal = index - exchange(last, index);
    }
  }

  cout << nextVal << '\n';
}
