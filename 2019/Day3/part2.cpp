#include <array>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <charconv>
#include <tuple>
#include <set>
#include <map>

using namespace std;

vector<array<int,3>> get_path()
{
	vector<array<int,3>> field;
	array<int, 3> coord = {0, 0, 0};
	for (;!cin.eof(); cin.ignore(1))
	{
		char dir;
		int val = 0;
		cin >> dir >> val;

		int axis = 0;
		int direction = 1;
		switch (dir)
		{
			case 'R': axis = 0; direction = 1; break;
			case 'L': axis = 0; direction = -1; break;
			case 'D': axis = 1; direction = 1; break;
			case 'U': axis = 1; direction = -1; break;
			default: break;
		}
		for (int i = 0; i < val; ++i)
		{
			coord[axis] += direction;
			++coord[2];
			field.emplace_back(coord);

		}
		if (cin.peek() == '\n') break;
	}
	return field;
}

int main(int argc, char** argv)
{
	vector<vector<array<int,3>>> fields;
	for (; !cin.eof(); cin.ignore(1))
	{
		fields.emplace_back(get_path());
	}

	vector<array<int,3>> crossings;
	for (auto a : fields[0])
	{
		auto found = find_if(fields[1].begin(), fields[1].end(), [a](auto b) { return a[0] == b[0] && a[1] == b[1]; });
		if (found != fields[1].end())
		{
			crossings.emplace_back(a)[2] += (*found)[2];
		}
	}

	auto min_elem = min_element(crossings.begin(), crossings.end(), [](auto a, auto b) { return a[2] < b[2]; });

	//sort(crossings.begin(), crossings.end(), [](auto a, auto b) { return abs(a[0]) + abs(a[1]) < abs(b[0]) + abs(b[1]); });

	clog << (*min_elem)[2] << '\n';

}
