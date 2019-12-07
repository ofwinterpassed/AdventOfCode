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
	std::vector<std::pair<int, int>> coords;
	for (std::array<char, 9> input; file.getline(&input[0], 9);)
	{
		auto comma = std::find(input.begin(), input.end(), ',');
		coords.emplace_back(std::stoi(std::string(input.begin(), comma)) - 40, std::stoi(std::string(comma + 2, input.end())) - 42);
	}
	

	int width = 315, height = 318;

	std::map<decltype(coords)::iterator, int> result;
	for (auto it = coords.begin(); it != coords.end(); ++it)
	{
		result[it] = 0;
	}
	int area = 0;
	for (int i = 0; i < width; ++i)
	{
		for (int k = 0; k < height; ++k)
		{
			auto dist = [i,k](const auto& a) { return std::abs(a.first - i) + std::abs(a.second - k); };
			std::vector<int> dists;
			std::transform(coords.begin(), coords.end(), std::back_inserter(dists), dist);
			std::sort(dists.begin(), dists.end());
			if (dists[0] != dists[1])
			{
				auto min = std::min_element(coords.begin(), coords.end(), [dist,i,k](const auto& a, const auto& b) { return dist(a) < dist(b); });
				result[min] += 1;
				if (i == 0 || i == 314 || k == 0 || k == 317)
				{
					result[min] = -10000;
				}
			}

			auto sum = std::reduce(dists.begin(), dists.end());
			if (sum < 10000)
			{
				area++;
			}
		}
	}

	std::vector<int> sizes;
	std::transform(result.begin(), result.end(), std::back_inserter(sizes), [](auto& p) {return p.second;});
	std::sort(sizes.begin(), sizes.end());

	for (auto& a : sizes)
	{
		std::clog << a << '\n';
	}
	std::clog << "The area is: " << area << '\n';

}

