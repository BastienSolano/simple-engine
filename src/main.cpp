#include <iostream>
#include <Board.hpp>

int main(void) {
	Board board = Board();
	std::cout << board.getFen() << std::endl;

	return 0;
}