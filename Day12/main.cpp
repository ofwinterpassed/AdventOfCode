#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>

using Rules = std::vector<bool>;

std::string new_gen(const std::string prev, const Rules& rules) {
	std::string next;
	next.resize(prev.size() + 2, '.');
	for (int i = 2; i < prev.size() - 2; ++i) {
		unsigned char val = 0;
		for (int k = -2; k < 3; ++k) {
			val <<= 1;
			val |= (prev[i+k] == '#');
		}
		next[i] = (rules[val] ? '#' : '.');
	}
	return next;
}

int main() {
	std::string input;
	input.resize(150, '.');
	std::cin.getline(input.data() + 10, 116);
	std::memcpy(input.data(), input.data()+125, 25);

	std::cout << input << '\n';
	std::cin.getline(input.data(), 116);

	std::string rule_str;
	
	Rules rules(32, false);
	rule_str.resize(10);
	while (std::cin.getline(rule_str.data(), 11)) {
		unsigned char val = 0;
		for (int i = 0; i < 5; ++i) {
			val <<= 1;
			val |= (rule_str[i] == '#');
		}
		rules[val] = (rule_str.back() == '#');
	}
	for (int i = 0; i < 200; ++i) {
		input = new_gen(input, rules);
		std::cout << input << '\n';
	}
	long sum = 0;
	long count = 0;
	for (int i = 0; i < input.size(); ++i) {
		sum += input[i] == '#' ? i - 25 : 0;
		count += input[i] == '#' ? 1 : 0;
	}
	std::cout << sum << '\n' << count << '\n' << sum + count * (50000000000 - 200);

	return 0;
}
