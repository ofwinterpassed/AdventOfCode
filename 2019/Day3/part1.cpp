#include <array>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <charconv>
#include <tuple>
#include <set>

using namespace std;

set<array<int,2>> get_path()
{
	set<array<int,2>> field;
	array<int, 2> coord = {0, 0};
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
			field.insert(coord);
		}
		if (cin.peek() == '\n') break;
	}
	//sort(field.begin(), field.end(), [](auto a, auto b) { return tie(a[0], a[1]) < tie(b[0], b[1]); });
	return field;
}

int main(int argc, char** argv)
{
	vector<set<array<int,2>>> fields;
	for (; !cin.eof(); cin.ignore(1))
	{
		fields.emplace_back(get_path());
	}

	set<array<int,2>> crossings;
	set_intersection(fields[0].begin(), fields[0].end(), fields[1].begin(), fields[1].end(), inserter(crossings, crossings.begin()), [](auto a, auto b) { return tie(a[0], a[1]) < tie(b[0], b[1]); });

	auto min_elem = min_element(crossings.begin(), crossings.end(), [](auto a, auto b) { return abs(a[0]) + abs(a[1]) < abs(b[0]) + abs(b[1]); });

	//sort(crossings.begin(), crossings.end(), [](auto a, auto b) { return abs(a[0]) + abs(a[1]) < abs(b[0]) + abs(b[1]); });

	clog << abs((*min_elem)[0]) + abs((*min_elem)[1]) << '\n';

}
