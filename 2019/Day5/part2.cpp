#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

using op_f = int (*)(int address, vector<int>&);

using mode_f = int& (*)(vector<int>&, int);

int& direct(vector<int>& v, int a) { return v[a]; }

int& indirect(vector<int>& v, int a) { return v[v[a]]; }

array<mode_f, 2> modes = {*indirect, *direct};

mode_f get_mode(int op, int arg) {
	return modes[(op % static_cast<int>(pow(10, arg + 2))) /
		     static_cast<int>(powf(10, arg + 1))];
}

int& get_arg(vector<int>& v, int op, int arg) {
	return get_mode(v[op], arg)(v, op + arg);
}

int add(int address, vector<int>& v) {
	get_arg(v, address, 3) =
	    get_arg(v, address, 1) + get_arg(v, address, 2);
	return 4;
}

int mul(int address, vector<int>& v) {
	get_arg(v, address, 3) =
	    get_arg(v, address, 1) * get_arg(v, address, 2);
	return 4;
}

int input(int address, vector<int>& v) {
	cin >> get_arg(v, address, 1);
	return 2;
}

int output(int address, vector<int>& v) {
	cout << get_arg(v, address, 1) << '\n';
	return 2;
}

int jump_if_true(int address, vector<int>& v) {
	if (get_arg(v, address, 1) != 0) {
		return get_arg(v, address, 2) - address;
	}
	return 3;
}

int jump_if_false(int address, vector<int>& v) {
	if (get_arg(v, address, 1) == 0) {
		return get_arg(v, address, 2) - address;
	}
	return 3;
}

int less_than(int address, vector<int>& v) {
	get_arg(v, address, 3) =
	    get_arg(v, address, 1) < get_arg(v, address, 2);
	return 4;
}

int equals(int address, vector<int>& v) {
	get_arg(v, address, 3) =
	    get_arg(v, address, 1) == get_arg(v, address, 2);
	return 4;
}

int terminate(int, vector<int>&) { return 0; }

array<op_f, 100> operations = {
    nullptr,   add,	 mul,	  input,   output,  jump_if_true, jump_if_false,
    less_than, equals,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   nullptr,	 nullptr, nullptr, nullptr, nullptr,	  nullptr,
    nullptr,   terminate};

int Intcode(vector<int> ints) {
	int step = 4;
	for (size_t command = 0; step != 0 && command < ints.size();
	     command += step) {
		step = operations[ints[command] % 100](command, ints);
	}

	return ints[0];
}

int main(int argc, char** argv) {
	fstream input("input");
	vector<int> ints;
	for (; !input.eof(); input.ignore(1)) {
		int val = 0;
		input >> val;
		ints.emplace_back(val);
	}

	int result = Intcode(ints);
	clog << result << '\n';
}
