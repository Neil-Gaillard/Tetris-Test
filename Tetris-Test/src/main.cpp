#include "board/board.hpp"
#include "graphics/window.hpp"
#include "graphics/shader.hpp"

#include "maths/vec4.hpp"
#include "maths/mat4.hpp"

#define PROJECTION_MATRIX "projection_matrix"
#define COLOR_MATRIX "given_color"

int main()
{
	srand((unsigned)time(0));
	
	graphics::Window window(450, 900, "Tetris Test");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	board::Board board;
	block::Block* block = block::Block::instantiateRandomBlock();

	board.placeBlock(*block);

	std::cout << board;

	GLfloat vertices[] =
	{
		0.0f, 0.0f, 0.0f,
		8.0f, 0.0f, 0.0f,
		0.0f, 3.0f, 0.0f,
		0.0f, 3.0f, 0.0f,
		8.0f, 3.0f, 0.0f,
		8.0f, 0.0f, 0.0f
	}; 

	GLuint vbo;
	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	maths::mat4 ortho = maths::mat4::orthographic(0.0f, 9.0f, 0.0f, 20.0f, -1.0f, 1.0f);
	graphics::Shader shader("src/graphics/shaders/basic.vert", "src/graphics/shaders/basic.frag");
	shader.enable();

	shader.setUniformMat4(PROJECTION_MATRIX, ortho);
	shader.setUniform4f(COLOR_MATRIX, maths::vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed()) {
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}
	return 0;
}