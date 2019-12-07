#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
	int serial = std::stoi(argv[1]);
	int grid[300][300];
	for (int y = 1; y <= 300; ++y) {
		for (int x = 1; x <= 300; ++x) {
			int rackId = x + 10;
			auto powerLevel = rackId * y + serial;
			powerLevel = powerLevel * rackId;
			powerLevel /= 100;
			powerLevel %= 10;
			powerLevel -= 5;
			grid[x - 1][y - 1] = powerLevel;
			std::cout << std::setw(3) << powerLevel;
		}
		std::cout << '\n';
	}
	int max = -1000;
	int maxx = -1;
	int maxy = -1;
	int maxsq = -1;
	for (int squareSize = 1; squareSize < 301; ++squareSize) {
		for (int y = 0; y < 301 - squareSize; ++y) {
			for (int x = 0; x < 301 - squareSize; ++x) {
				int val = 0;
				for (int ys = 0; ys < squareSize; ++ys) {
					for (int xs = 0; xs < squareSize; ++xs) {
						val += grid[x+xs][y+ys];
					}
				}
				if (val > max) {
					maxx = x+1;
					maxy = y+1;
					max = val;
					maxsq = squareSize;
				}
			}
		}
	}

	std::cout << maxx << ',' << maxy << ',' << maxsq << '\n';

	return 0;
}
