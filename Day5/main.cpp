#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

std::string reduce(std::string input, char skip)
{
	input.erase(std::remove(input.begin(), input.end(), skip), input.end());
	input.erase(std::remove(input.begin(), input.end(), skip+32), input.end());
	std::size_t i = 0, k = 0, newlength = input.size();
	do
	{
		i = 0;
		k = 0;
		for(; i < newlength; ++i)
		{
			if ((i != (newlength - 1)) && ((input[i] == input[i+1] - 32) || (input[i] == input[i+1] + 32)))
			{
				++i;
			}
			else
			{
				input[k] = input[i];
				++k;
			}
		}
		newlength = k;
		input.resize(newlength);
		std::clog << input.size() << '\n';;
	} while(i != k);
	return input;
}

int main(int argc, char** argv)
{
	std::ifstream file(argv[1]);
	std::string input;
	file >> input;
	char unit = 'A';
	std::vector<std::string> result;
	std::generate_n(std::back_inserter(result), 27, [input,&unit]() { return reduce(input, unit++); });

	for (std::size_t a = 0; a < result.size() ; ++a)
	{
		std::clog << char(a + 65) << char(a + 97) << ' ' << result[a].size() << '\n';
	}

}
