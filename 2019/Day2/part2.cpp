#include <array>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <charconv>

using namespace std;

int Intcode(vector<int> ints, int noun, int verb)
{
	ints[1] = noun;
	ints[2] = verb;
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

	return ints[0];
}

int FindOutput(vector<int> ints, int output)
{
	for (int noun = 0; noun < 100; ++noun)
	{
		for (int verb = 0; verb < 100; ++verb)
		{
			int result = Intcode(ints, noun, verb);
			if (result == output) {
					return 100 * noun + verb;
			}
		}
	}
	return -1;
}

int main(int argc, char** argv)
{
	vector<int> ints;
	for (; !cin.eof(); cin.ignore(1))
	{
		int val = 0;
		cin >> val;
		ints.emplace_back(val);
	}

	int result = FindOutput(ints, 19690720);
	clog << result << '\n';

}
