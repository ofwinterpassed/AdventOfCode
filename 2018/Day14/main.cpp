#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <vector>

void back(std::list<int>& list, std::list<int>::iterator& it) {
	if (it == list.begin()) {
		it = list.end();
	}
	--it;
}

int main(int argc, char** argv) {
	std::list<int> board;
	board.insert(board.begin(), 7);
	board.insert(board.begin(), 3);
	std::list<int>::iterator elves[2] = { board.begin(), std::next(board.begin()) };
	int numRecipies = 2;
	std::string tmp(argv[1]);
	std::reverse(tmp.begin(), tmp.end());
	//int turns;
 	//std::from_chars(tmp.data(), tmp.data()+tmp.size(), turns);
	while (true) {
		auto recipy0 = *elves[0];
		auto recipy1 = *elves[1];
		auto sum = recipy0 + recipy1;
		std::array<char, 3> chars = {0};
		std::to_chars(chars.data(), chars.data() + chars.size(), sum);
		board.insert(board.end(), chars[0] - 48);
		++numRecipies;
		auto end = std::next(board.rbegin(), tmp.size());
		if (std::equal(board.rbegin(), end, tmp.begin(), tmp.end(), [](auto a, auto b) { return a + 48 == b; })) {
			break;
		}
		if (sum > 9) {
			board.insert(board.end(), chars[1] - 48);
			++numRecipies;
			auto end = std::next(board.rbegin(), tmp.size());
			if (std::equal(board.rbegin(), end, tmp.begin(), tmp.end(), [](auto a, auto b) { return a + 48 == b; })) {
				break;
			}
		}
		for (auto& elf : elves) {
			auto steps = *elf + 1;
			for (int a = 0; a < steps; ++a) {
				++elf;
				if (elf == std::end(board)) {
					elf = std::begin(board);
				}
			}
		}
	}
	//std::string result;
	//auto iter = board.rbegin();
	//if (numRecipies != turns+10) {
		//std::advance(iter, 1);
	//}
	//std::transform(iter, std::next(iter, 10), std::back_inserter(result), [](auto val) { return val + 48; });
	//std::reverse(result.begin(), result.end());

	std::cout << numRecipies - tmp.size() << '\n';

	return 0;
}



