#include "board/board.hpp"

#include "graphics/window.hpp"
#include "graphics/shader.hpp"

#include "maths/vec4.hpp"
#include "maths/mat4.hpp"

#include <thread>  
#include <Windows.h>

#define WINDOW_NAME "Tetris Test"

#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 450

#define VERTEX_SHADER_PATH "src/graphics/shaders/basic.vert"
#define FRAGMENT_SHADER_PATH "src/graphics/shaders/basic.frag"

void updateWindow(const board::Board* board, graphics::Window* window);

void goDown(board::Board* board, block::Block* block);

int main(int argc, char* argv)
{
	srand((unsigned)time(0));
	
	graphics::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	board::Board board;
	block::Block* block = block::Block::instantiateRandomBlock();

	//TODO Place the block in a file, only the last one is the one moving (active block)
	board.placeBlock(*block);

	graphics::Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shader.enable();

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	std::thread first(goDown, &board, block);

	while (!window.closed()) {
		updateWindow(&board, &window);
		if (window.isKeyPressed(GLFW_KEY_RIGHT))
			if(block->moveBlock(direction::Direction::RIGHT))
				board.moveBlock(*block, direction::Direction::RIGHT);
		if (window.isKeyPressed(GLFW_KEY_LEFT))
			if (block->moveBlock(direction::Direction::LEFT))
				board.moveBlock(*block, direction::Direction::LEFT);
		//TODO Block collision detection and ground collision detection in the board to launch a new block
		//TODO destroy a full line of blocks and make the blocks above go down of 1
	}
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
	window->update();
}

void goDown(board::Board* board, block::Block* block)
{
	while (block->moveBlock(direction::Direction::DOWN)) {
		Sleep(1000);
		board->moveBlock(*block, direction::Direction::DOWN);
	}
}