#include "board/board.hpp"
#include "graphics/window.hpp"

int main()
{
	srand((unsigned)time(0));
	
	graphics::Window window(960, 540, "Tetris Test");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	board::Board board;
	block::Block* block = block::Block::instantiateRandomBlock();

	board.placeBlock(*block);

	std::cout << board;

	while (!window.closed()) {
		window.clear();

		//
		//
		//

		window.update();
	}
	return 0;
}