#include <thread>  
#include <Windows.h>

#include "board/board.hpp"

#include "graphics/window.hpp"
#include "graphics/shader.hpp"

#include "maths/vec4.hpp"
#include "maths/mat4.hpp"

#define DEBUG 0

#define WINDOW_NAME "Tetris Test"

#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 450

#define VERTEX_SHADER_PATH "src/graphics/shaders/basic.vert"
#define FRAGMENT_SHADER_PATH "src/graphics/shaders/basic.frag"

void updateWindow(const board::Board* board, graphics::Window* window);

void goDown(board::Board* board, block::Block* block, bool &isThread);

int main(int argc, char* argv)
{
#if DEBUG
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#else
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
	srand((unsigned)time(0));
	
	graphics::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	glClearColor(0.9f, 0.9f, 0.9f, 0.9f);

	board::Board board;

	bool isFirstBlock = true;
	block::Block* block = block::Block::instantiateRandomBlock();

	board.placeBlock(*block);

	graphics::Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shader.enable();

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	bool isThread = false;
	bool isFirstThread = true;

	std::thread* first = new std::thread(goDown, &board, block, std::ref(isThread));

	while (!window.closed()) {
		window.update();

		if (window.isKeyPressed(GLFW_KEY_RIGHT))
			if(block->moveBlock(direction::Direction::RIGHT, &board))
				board.moveBlock(*block, direction::Direction::RIGHT);
		if (window.isKeyPressed(GLFW_KEY_LEFT))
			if (block->moveBlock(direction::Direction::LEFT, &board))
				board.moveBlock(*block, direction::Direction::LEFT);
		if (window.isKeyPressed(GLFW_KEY_DOWN))
			if (block->moveBlock(direction::Direction::DOWN, &board))
				board.moveBlock(*block, direction::Direction::DOWN);

		if (!isThread) {
			if (!isFirstBlock)
				block = block::Block::instantiateRandomBlock();
			else
				isFirstBlock = false;
			if (!isFirstThread)
				first = new std::thread(goDown, &board, block, std::ref(isThread), time);
			else
				isFirstThread = false;
			isThread = true;
		}

		updateWindow(&board, &window);
		//TODO Block collision detection and ground collision detection in the board to launch a new block
		//TODO destroy a full line of blocks and make the blocks above go down of 1
	}
	first->detach();
	return 0;
}

void updateWindow(const board::Board* board, graphics::Window* window)
{
	window->clear();
	GLfloat vertices[board::Board::HEIGHT * board::Board::WIDTH][18];
	int k = 0;
	for (int i = 0; i < board::Board::HEIGHT; i++) {
		for (int j = 0; j < board::Board::WIDTH; j++) {
			if (board->getBlockComponant(j, i)->isActive()) {
				memcpy(vertices[k], board->getBlockComponant(j, i)->getVertices(), 18 * sizeof(GLfloat));
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[k]), vertices[k], GL_STATIC_DRAW);
				++k;
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
	}
}

void goDown(board::Board* board, block::Block* block, bool &isThread)
{
	while (block->moveBlock(direction::Direction::DOWN, board)) {
		board->moveBlock(*block, direction::Direction::DOWN);
		Sleep(700);
	}
	isThread = false;
}