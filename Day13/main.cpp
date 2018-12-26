#include <algorithm>
#include <array>
#include <iostream>
#include <tuple>
#include <vector>

enum turn { left, straight, right };

struct Cart {
	Cart(int y, int x, char dir) : y(y), x(x), dir(dir) {}
	bool operator==(const Cart& other) {
		return std::tie(this->y, this->x) == std::tie(other.y, other.x);
	}
	bool operator<(const Cart& other) {
		return std::tie(this->y, this->x) < std::tie(other.y, other.x);
	}
	int y;
	int x;
	char dir;
	turn last = right;
};

template<class Board>
void from_surroundings(int y, int x, Board board) {
	char connections = 0;
	std::string above = "|\\/+";
	std::string right = "-\\/+";
	connections |= (above.find(board[y-1][x]) != std::string::npos) ? 1 : 0;
	connections |= (above.find(board[y+1][x]) != std::string::npos) ? 4 : 0;
	connections |= (right.find(board[y][x-1]) != std::string::npos) ? 8 : 0;
	connections |= (right.find(board[y][x+1]) != std::string::npos) ? 2 : 0;

	if (connections == 15) {
		board[y][x] = '+';
	} else if (connections == 12) {
		board[y][x] = '\\';
	} else if (connections == 10) {
		board[y][x] = '-';
	} else if (connections == 9) {
		board[y][x] = '/';
	} else if (connections == 6) {
		board[y][x] = '/';
	} else if (connections == 5) {
		board[y][x] = '|';
	} else if (connections == 3) {
		board[y][x] = '\\';
	}

}

int main() {
	char board[152][152];
	int current = 0;
	std::fill_n(std::begin(*board), 152*152, ' ');
	while (std::cin.getline(&board[++current][1], 151)) {
		board[current][151] = ' ';
	}

	std::vector<Cart> carts;
	for (int y = 1; y < 151; ++y) {
		for (int x = 1; x < 151; ++x) {
			switch (board[y][x]) {
			default:
				break;
			case '^':
			case '>':
			case 'v':
			case '<':
				carts.emplace_back(y, x, board[y][x]);
				from_surroundings(y, x, board);
				break;
			}
			std::cout << board[y][x];
		}
		std::cout << '\n';
	}

	auto duplicate = std::adjacent_find(carts.begin(), carts.end());
	while (carts.size() > 1) {
		for (int id = 0; id < carts.size(); ++id) {
			auto& cart = carts[id];
			switch (cart.dir) {
				case '^':
					cart.y--;
					if (board[cart.y][cart.x] == '+') {
						cart.last = static_cast<turn>((cart.last + 1) % 3);
						switch (cart.last) {
							case left:
								cart.dir = '<';
								break;
							case right:
								cart.dir = '>';
								break;
						}
					} else if (board[cart.y][cart.x] == '/') {
						cart.dir = '>';
					} else if (board[cart.y][cart.x] == '\\') {
						cart.dir = '<';
					}
					break;
				case '>':
					cart.x++;
					if (board[cart.y][cart.x] == '+') {
						cart.last = static_cast<turn>((cart.last + 1) % 3);
						switch (cart.last) {
							case left:
								cart.dir = '^';
								break;
							case right:
								cart.dir = 'v';
								break;
						}
					} else if (board[cart.y][cart.x] == '/') {
						cart.dir = '^';
					} else if (board[cart.y][cart.x] == '\\') {
						cart.dir = 'v';
					}
					break;
				case 'v':
					cart.y++;
					if (board[cart.y][cart.x] == '+') {
						cart.last = static_cast<turn>((cart.last + 1) % 3);
						switch (cart.last) {
							case left:
								cart.dir = '>';
								break;
							case right:
								cart.dir = '<';
								break;
						}
					} else if (board[cart.y][cart.x] == '/') {
						cart.dir = '<';
					} else if (board[cart.y][cart.x] == '\\') {
						cart.dir = '>';
					}
					break;
				case '<':
					cart.x--;
					if (board[cart.y][cart.x] == '+') {
						cart.last = static_cast<turn>((cart.last + 1) % 3);
						switch (cart.last) {
							case left:
								cart.dir = 'v';
								break;
							case right:
								cart.dir = '^';
								break;
						}
					} else if (board[cart.y][cart.x] == '/') {
						cart.dir = 'v';
					} else if (board[cart.y][cart.x] == '\\') {
						cart.dir = '^';
					}
					break;
			}
			if (std::count(carts.begin(), carts.begin() + id, cart) > 0) {
				carts.erase(std::remove(carts.begin(), carts.end(), cart), carts.end());
				id -= 2;
			} else if (std::count(carts.begin() + id, carts.end(), cart) > 1) {
				carts.erase(std::remove(carts.begin(), carts.end(), cart), carts.end());
				--id;
			}
		}
		std::sort(carts.begin(), carts.end());
	}
	std::cout << carts.begin()->dir << " at " << carts.begin()->x - 1 << ',' << carts.begin()->y - 1 << '\n';
}
