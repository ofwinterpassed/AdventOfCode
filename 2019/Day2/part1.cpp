#include <array>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <charconv>

using namespace std;

int main(int argc, char** argv)
{
	std::vector<int> ints;
	for (; !cin.eof(); cin.ignore(1))
	{
		int val = 0;
		cin >> val;
		ints.emplace_back(val);
	}

	ints[1] = 12;
	ints[2] = 2;
	for (size_t command = 0; command < ints.size(); command += 4)
	{
		switch (ints[command])
		{
			default: break;
			case 1: ints[ints[command + 3]] = ints[ints[command + 1]] + ints[ints[command + 2]]; break;
			case 2: ints[ints[command + 3]] = ints[ints[command + 1]] * ints[ints[command + 2]]; break;
			case 99: command = ints.size(); break;
		}

	}

	std::clog << ints[0] << '\n';

}
