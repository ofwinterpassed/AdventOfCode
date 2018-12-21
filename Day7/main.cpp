#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

int main(int argc, char** argv)
{
	std::ifstream file(argv[1]);
	std::string input;
	std::map<char, std::vector<char>> less_map;
	for (std::array<char, 49> input; file.getline(&input[0], 49);)
	{
		auto small = input[5];
		auto big = input[36];
		less_map.try_emplace(small, 0);
		less_map.try_emplace(big, 0);
		less_map[small].emplace_back(big);
	}

	std::string order;
	std::transform(less_map.begin(), less_map.end(), std::back_inserter(order), [](auto& p) { return std::get<0>(p); });
	

}


