#include <algorithm>
#include <array>
#include <charconv>
#include <iostream>
#include <iterator>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
	int count = 0;
	bool toobig = false;
	for (int a = 1; a < 6; ++a) {
		if (toobig) break;
		for (int b = a; b < 10; ++b) {
			if (toobig) break;
			for (int c = b; c < 10; ++c) {
				if (toobig) break;
				for (int d = c; d < 10; ++d) {
					if (toobig) break;
					for (int e = d; e < 10; ++e) {
						if (toobig) break;
						for (int f = e; f < 10; ++f) {
							toobig = a * 100000 +
								     b * 10000 +
								     c * 1000 +
								     d * 100 +
								     e * 10 +
								     f >
								 576723;
							if (toobig) {
								break;
							}
							if (((a == b) &&
							     (b != c)) ||
							    ((b == c) &&
							     (a != b) &&
							     (c != d)) ||
							    ((c == d) &&
							     (b != c) &&
							     (d != e)) ||
							    ((d == e) &&
							     (c != d) &&
							     (e != f)) ||
							    ((e == f) &&
							     (d != e))) {
								++count;
							}
						}
					}
				}
			}
		}
	}

	clog << count << '\n';
}
