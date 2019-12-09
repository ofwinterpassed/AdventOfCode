#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

struct node {
	node(const string& name, const string& parent)
	    : name(name), parent(parent) {}
	string name;
	string parent;
	int depth = 0;
	vector<int> children;
};

void increase_depth(int idx, vector<node>& all, int depth) {
	all[idx].depth = depth + 1;
	for (int child : all[idx].children) {
		increase_depth(child, all, depth + 1);
	}
}

int build_tree(vector<node>& all) {
	for (size_t idx = 0; idx < all.size(); ++idx) {
		auto& node = all[idx];
		if (node.parent == "null") continue;
		auto p_it = find_if(all.begin(), all.end(),
				    [& parent = node.parent](auto& node) {
					    return node.name == parent;
				    });
		if (p_it == all.end()) {
			all.emplace_back(node.parent, "null");
			p_it = all.end() - 1;
		}
		p_it->children.emplace_back(idx);
	}
	for (size_t idx = 0; idx < all.size(); ++idx) {
		auto& node = all[idx];
		if (node.parent != "null") continue;
		for (auto idx : node.children) {
			increase_depth(idx, all, 0);
		}
	}
	return accumulate(all.begin(), all.end(), 0, [](int acc, auto& node) { return acc + node.depth; });
}

int main(int argc, char** argv) {
	fstream input("input");
	vector<node> all;
	for (; !input.eof(); input.ignore(1)) {
		string parent = "xxx";
		string name = "xxx";
		input >> parent[0] >> parent[1] >> parent[2];
		input.ignore();
		input >> name[0] >> name[1] >> name[2];

		all.emplace_back(name, parent);
	}

	int result = build_tree(all);
	clog << "connections: " << result << '\n';

	auto santa = find_if(all.begin(), all.end(), [](auto& node) { return node.name == "SAN"; });
	auto you = find_if(all.begin(), all.end(), [](auto& node) { return node.name == "YOU"; });
	if (santa == all.end() || you == all.end()) {
		clog << "Crap santa " << (santa != all.end()) << " or you " << (you != all.end()) << " is missing\n";
	}

	vector<string> santa_path;
	while (santa != all.end()) {
		santa_path.emplace_back(santa->parent);
		santa = find_if(all.begin(), all.end(), [santa](auto& node) { return node.name == santa->parent; });
	}
	vector<string> you_path;
	while (you != all.end()) {
		you_path.emplace_back(you->parent);
		you = find_if(all.begin(), all.end(), [you](auto& node) { return node.name == you->parent; });
	}
	for (auto& name : santa_path) {
		clog << name << "\n";
	}
	for (auto& name : you_path) {
		clog << name << "\n";
	}
	auto unequal = mismatch(santa_path.rbegin(), santa_path.rend(), you_path.rbegin(), you_path.rend());
	int dist = distance(unequal.first, santa_path.rend()) + distance(unequal.second, you_path.rend());

	clog << "shortest path is: " << dist;
}
