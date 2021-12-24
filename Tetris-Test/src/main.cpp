#include "board/board.hpp"

#include "graphics/window.hpp"
#include "graphics/shader.hpp"

#include "maths/vec4.hpp"
#include "maths/mat4.hpp"

#define WINDOW_NAME "Tetris Test"

#define HEIGHT 900
#define WIDTH 450

#define VERTEX_SHADER_PATH "src/graphics/shaders/basic.vert"
#define FRAGMENT_SHADER_PATH "src/graphics/shaders/basic.frag"

int main(int argc, char* argv)
{
	srand((unsigned)time(0));
	
	graphics::Window window(WIDTH, HEIGHT, WINDOW_NAME);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	board::Board board;
	block::Block* block = block::Block::instantiateRandomBlock();

	board.placeBlock(*block);

	graphics::Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shader.enable();

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	while (!window.closed()) {
		window.clear();
		GLfloat vertices[20 * 10][18];
		int k = 0;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				if (board.getBlockComponant(j, i)->isActive()) {
					memcpy(vertices[k], board.getBlockComponant(j, i)->getVertices(), 18 * sizeof(GLfloat));
					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[k]), vertices[k], GL_STATIC_DRAW);
					++k;
					glDrawArrays(GL_TRIANGLES, 0, 6);
				}
			}
		}
		window.update();
	}
	return 0;
}