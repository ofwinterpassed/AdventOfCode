#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

long accumulator = 0;

enum class instruction_t : char { acc, jmp, nop };

int main(int argc, char **argv) {

  vector<tuple<instruction_t, int, bool>> input;
  for (string line; getline(cin, line);) {
    int value;
    from_chars(line.data() + 5, line.data() + line.size(), value);
    if (line[4] == '-')
      value = -value;
    instruction_t instruction;
    regex r("((acc)|(jmp)|(nop)).*");
    smatch match;
    regex_match(line, match, r);
    if (match[2].matched)
      instruction = instruction_t::acc;
    if (match[3].matched)
      instruction = instruction_t::jmp;
    if (match[4].matched)
      instruction = instruction_t::nop;
    input.emplace_back(instruction, value, false);
  }

  size_t instructionToChange = 0;
  bool success = false;
  while (!success && instructionToChange < 654) {
    accumulator = 0;
    size_t position = 0;
    bool last_visited = false;
    do {
      if (position == input.size()) {
        success = true;
        break;
      }
      auto &[instruction, value, visited] = input[position];

      auto tmpInstruction = instruction;
      last_visited = visited;
      visited = true;
      if (position == instructionToChange) {
        switch (tmpInstruction) {
        case instruction_t::acc:
          break;
        case instruction_t::jmp:
          tmpInstruction = instruction_t::nop;
          break;
        case instruction_t::nop:
          tmpInstruction = instruction_t::jmp;
          break;
        }
      }

      switch (tmpInstruction) {
      case instruction_t::acc:
        accumulator += value;
        ++position;
        break;
      case instruction_t::jmp:
        position += value;
        break;
      case instruction_t::nop:
        ++position;
        break;
      }
    } while (!last_visited);
    ++instructionToChange;
    for (auto& ins : input) {
      get<2>(ins) = false;
    }
    cout << instructionToChange << '\n' << accumulator << '\n';
  }

  cout << accumulator << " " << (success ? "true" : "false") << '\n';
}
