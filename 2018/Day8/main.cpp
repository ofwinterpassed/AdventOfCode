#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>


struct node {
	std::vector<node> children;
	std::vector<int> meta;
};

node new_node(std::istream& in) {
	node ret;
	int kids, metas;
	in >> kids >> metas;
	for (int kid = 0; kid < kids; ++kid) {
		ret.children.emplace_back(new_node(in));
	}
	ret.meta.resize(metas);
	for (int i = 0; i < metas; ++i) {
		in >> ret.meta[i];
	}
	return ret;
}

int meta_sum(const node& n) {
	int sum = std::accumulate(n.meta.begin(), n.meta.end(), 0);
	sum += std::accumulate(n.children.begin(), n.children.end(), 0, [](auto& sum, auto& n) { return sum + meta_sum(n); });
	return sum;
}

int meta_value(const node& n) {
	if (n.children.empty()) {
		return std::accumulate(n.meta.begin(), n.meta.end(), 0);
	}
	int ret = 0;
	for (int a : n.meta) {
		if (a > n.children.size()) {
			continue;
		}
		ret += meta_value(n.children[a-1]);
	}
	return ret;
}

int main() {
	node input = new_node(std::cin);
	std::cout << meta_sum(input) << '\n';
	std::cout << meta_value(input) << '\n';
	return 0;
}

