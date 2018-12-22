#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

int main() {
	char input[44];
	std::vector<std::tuple<int, int, int, int>> dots;
	for (; std::cin.getline(input, 44);) {
		int posx = std::stoi(std::string(&input[10], 6));
		int posy = std::stoi(std::string(&input[18], 6));
		int velx = std::stoi(std::string(&input[36], 2));
		int vely = std::stoi(std::string(&input[40], 2));
		dots.emplace_back(posx, posy, velx, vely);
	}
	for (int i = 0; i < 10117; ++i) {
		for (auto& a : dots) {
			std::get<0>(a) += std::get<2>(a);
			std::get<1>(a) += std::get<3>(a);
		}
	}
	for (int k = 85; k < 140; ++k) {
		for (int i = 120; i < 225; ++i) {
			auto found = std::find_if(dots.begin(), dots.end(), [i,k](auto& a) { return std::get<0>(a) == i && std::get<1>(a) == k; });
			if (found != dots.end()) {
				std::cout << '#';
			} else {
				std::cout << '.';
			}
		}
		std::cout << '\n';
	}
	for (auto& a : dots) {
		std::clog << std::get<0>(a) << ',' << std::get<1>(a) << ','
				  << std::get<2>(a) << ',' << std::get<3>(a) << '\n';
	}
	auto a = std::accumulate(dots.begin(), dots.end(),
							 std::tuple<int, int, int, int>(100000, 100000, 100000, 100000),
							 [](auto a, auto b) {
								 return std::tuple<int, int, int, int>(
									 std::min(std::get<0>(a), std::get<0>(b)),
									 std::min(std::get<1>(a), std::get<1>(b)),
									 std::min(std::get<2>(a), std::get<2>(b)),
									 std::min(std::get<3>(a), std::get<3>(b)));
							 });

	std::clog << std::get<0>(a) << ',' << std::get<1>(a) << ','
			  << std::get<2>(a) << ',' << std::get<3>(a) << '\n';

	auto b = std::accumulate(dots.begin(), dots.end(),
							 std::tuple<int, int, int, int>(0, 0, 0, 0),
							 [](auto a, auto b) {
								 return std::tuple<int, int, int, int>(
									 std::max(std::get<0>(a), std::get<0>(b)),
									 std::max(std::get<1>(a), std::get<1>(b)),
									 std::max(std::get<2>(a), std::get<2>(b)),
									 std::max(std::get<3>(a), std::get<3>(b)));
							 });

	std::clog << std::get<0>(b) << ',' << std::get<1>(b) << ','
			  << std::get<2>(b) << ',' << std::get<3>(b) << '\n';

	return 0;
}
