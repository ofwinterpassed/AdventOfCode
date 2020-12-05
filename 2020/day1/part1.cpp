#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
int main(int argc, char** argv) {

	vector<int> values;
	for (array<char, 9> input; cin.getline(&input[0], 9);) {
		int val = 0;
		from_chars(input.data(), input.data() + input.size(), val);
		values.emplace_back(val);
	}

	for(auto it1 = values.begin(); it1 != values.end(); ++it1) {
			auto it2 = find_if(next(it1), values.end(), [&it1](auto val) { return (*it1 + val) == 2020; });
			if (it2 != values.end()) {
					clog << *it1 * *it2 << '\n';
					break;
			}
	}

}
