#include <algorithm>
#include <array>
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

int main() {
	std::array<long, 464> players = {0};
	std::list<int> board;
	board.insert(board.begin(), 0);
	auto current = board.begin();
	for (int round = 1, player = 0; round <= 7173000; ++round) {
		if (round % 23 == 0) {
			for (int i = 0; i < 7; ++i) {
				back(board, current);
			}
			players[player] += round + *current;
			current = board.erase(current);
			if (current == board.end()) {
				current == board.begin();
			}
		} else {
			++current;
			if (current == board.end()) {
				current = board.begin();
			}
			current = board.insert(++current, round);
		}
		if (round < 25) {
			std::clog << '[' << player << ']';
			for (int a : board) {
				std::clog << ' ' << a << ' ';
			}
			std::clog << '\n';
		}
		player = ++player % players.size();
		//std::clog << round << '\n';
	}
	std::clog << -2 % 3 << '\n';
	std::cout << *std::max_element(players.begin(), players.end()) << '\n';


	return 0;
}


