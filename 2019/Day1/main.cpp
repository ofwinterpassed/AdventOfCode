#include <array>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <charconv>

int main(int argc, char** argv)
{
	int result = 0;
	for (std::array<char, 9> input; std::cin.getline(&input[0], 9);)
	{
		int mass = 0;
		std::from_chars(input.data(), input.data() + input.size(), mass);
		while (true) {
			mass = mass / 3 - 2;
			if (mass < 1) {
				break;
			}
			result += mass;
		}
	}

	std::clog << result << '\n';

}
