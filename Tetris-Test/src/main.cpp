#include "board/board.hpp"

int main()
{
	srand((unsigned)time(0));

	board::Board board;
	block::Block* block = block::Block::instantiateRandomBlock();

	board.placeBlock(*block);

	std::cout << board;
	return 0;
}