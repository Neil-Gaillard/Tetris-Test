#include <iostream>
#include <thread>  
#include <Windows.h>

#include "board/board.hpp"

#include "graphics/window.hpp"
#include "graphics/shader.hpp"

#define DEBUG 0
#define MUSIC 1

#define WINDOW_NAME "Tetris"

#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 450

#if DEBUG
#define VERTEX_SHADER_PATH "src/graphics/shaders/basic.vert"
#define FRAGMENT_SHADER_PATH "src/graphics/shaders/basic.frag"
#else
#define VERTEX_SHADER_PATH "shaders/basic.vert"
#define FRAGMENT_SHADER_PATH "shaders/basic.frag"
#endif

#define AUDIO_MUSIC_PATH L"audio/tetris-theme-officiel_01.wav"

#define COLOR_MATRIX "given_color"

#define INPUT_DELAY 40

#define BLOCK_SPAWN_TIME 300
#define BLOCK_FALL_TIME 700
#define BLOCK_SETUP_TIME 300

void update_window(const board::Board* board, const graphics::Window* window, const graphics::Shader* shader);

void go_down(const board::Board* board, block::Block* block, bool &is_thread, int &score);

int main()
{
#if DEBUG
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#else
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
	srand(static_cast<unsigned>(time(nullptr)));

	const auto window = new graphics::Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	glClearColor(0.8f, 0.8f, 0.8f, 0.8f);

	board::Board board;

	bool is_first_block = true;
	block::Block* block = block::Block::instantiateRandomBlock();

	board.placeBlock(*block);

	const auto* shader = new graphics::Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shader->enable();

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	bool isThread = false;
	bool isFirstThread = true;

#if MUSIC
	PlaySound(AUDIO_MUSIC_PATH, nullptr, SND_FILENAME | SND_LOOP | SND_ASYNC);
#endif

	int score = 0;

	auto* first = new std::thread(go_down, &board, block, std::ref(isThread), std::ref(score));

	while (!window->closed()) {
		if (!isThread) {
			if (!is_first_block) {
				block = block::Block::instantiateRandomBlock();
				board.placeBlock(*block);
			}
			else
				is_first_block = false;
			if (!isFirstThread)
				first = new std::thread(go_down, &board, block, std::ref(isThread), std::ref(score));
			else
				isFirstThread = false;
			isThread = true;
		}
		if (window->isKeyPressed(GLFW_KEY_RIGHT) && block->moveBlock(direction::Direction::RIGHT, &board))
				board.moveBlock(*block, direction::Direction::RIGHT);
		if (window->isKeyPressed(GLFW_KEY_LEFT) && block->moveBlock(direction::Direction::LEFT, &board))
				board.moveBlock(*block, direction::Direction::LEFT);
		if (window->isKeyPressed(GLFW_KEY_DOWN) && block->moveBlock(direction::Direction::DOWN, &board))
				board.moveBlock(*block, direction::Direction::DOWN);
		if (window->isKeyPressed(GLFW_KEY_UP) && block->rotateBlock(&board))
				board.placeBlock(*block);
		Sleep(INPUT_DELAY);

		update_window(&board, window, shader);
	}
	first->detach();
	graphics::Shader::disable();
	return 0;
}

void update_window(const board::Board* board, const graphics::Window* window, const graphics::Shader* shader)
{
	graphics::Window::clear();
	int k = 0;
	for (int i = 0; i < board::Board::HEIGHT; i++) {
		for (int j = 0; j < board::Board::WIDTH; j++) {
			if (board->getBlockComponent(j, i)->isActive()) {
				GLfloat vertices[board::Board::HEIGHT * board::Board::WIDTH][18];
				memcpy(vertices[k], board->getBlockComponent(j, i)->getVertices(), 18 * sizeof(GLfloat));
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[k]), vertices[k], GL_STATIC_DRAW);
				shader->setUniform4f(COLOR_MATRIX, board->getBlockComponent(j, i)->getColor());
				++k;
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
	}
	window->update();
}

void go_down(const board::Board* board, block::Block* block, bool& is_thread, int &score)
{
	Sleep(BLOCK_SPAWN_TIME);
	while (block->moveBlock(direction::Direction::DOWN, board)) {
		board->moveBlock(*block, direction::Direction::DOWN);
		Sleep(BLOCK_FALL_TIME);
	}
	Sleep(BLOCK_SETUP_TIME);
	board->lineVerification(*block, score);
	std::cout << score << std::endl;
	is_thread = false;
}