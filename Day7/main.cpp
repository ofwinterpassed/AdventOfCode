#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

int main(int argc, char** argv) {
	std::ifstream file(argv[1]);
	std::string order;
	std::map<char, std::set<char>> less_map;
	for (std::array<char, 49> input; file.getline(&input[0], 49);) {
		auto small = input[5];
		auto big = input[36];
		less_map.try_emplace(small, std::set<char>{});
		less_map[big].emplace(small);
		std::clog << '[' << small << '<' << big << ']' << '\n';
	}

	auto map_cp = less_map;
	while (!less_map.empty()) {
		auto found = std::find_if(less_map.begin(), less_map.end(),
								  [](auto& p) { return p.second.empty(); });
		order += found->first;
		for (auto& a : less_map) {
			a.second.erase(found->first);
		}
		less_map.erase(found);
	}

	std::clog << order << '\n';

	std::array<std::pair<char, char>, 5> workers = {
		std::pair{0, 0}, std::pair{0, 0}, std::pair{0, 0}, std::pair{0, 0}, std::pair{0, 0}};
	int time = 0;
	bool done = false;
	std::string finished;
	while (!map_cp.empty() || !done) {
		int idle = 5;
		std::clog << std::setw(5) << time << ' ';
		for (auto& worker : workers) {
			std::clog << std::setw(1);
			if (worker.second > 0) {
				worker.second--;
			}
			if (worker.second == 0) {
				for (auto& a : map_cp) {
					a.second.erase(worker.first);
				}
				finished += worker.first;
				worker.first = 0;
			}
			if (worker.second > 0) {
				--idle;
			}
		}
		for (auto& worker : workers) {
			if (worker.second <= 0) {
				auto found = std::find_if(map_cp.begin(), map_cp.end(),
								  [](auto& p) { return p.second.empty(); });
				if (found != map_cp.end()) {
					worker.first = found->first;
					worker.second = found->first - 4;
					map_cp.erase(found);
					--idle;
					std::clog << worker.first;
				} else {
					std::clog << '.';
				}
			} else {
				std::clog << worker.first;
			}
		}
		std::clog << ' ' << finished << '\n';
		done = idle == 5;
		time++;
	}

	std::clog << time << '\n';
	std::clog << finished << '\n';

	return 0;
}
