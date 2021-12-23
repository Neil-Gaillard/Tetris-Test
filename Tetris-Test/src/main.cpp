#include "board/board.hpp"
#include "graphics/window.hpp"
#include "graphics/shader.hpp"

#include "maths/vec4.hpp"
#include "maths/mat4.hpp"

#include <algorithm>

#define VERTEX_SHADER_PATH "src/graphics/shaders/basic.vert"
#define FRAGMENT_SHADER_PATH "src/graphics/shaders/basic.frag"

#define PROJECTION_MATRIX "projection_matrix"
#define COLOR_MATRIX "given_color"

#define LEFT 0.0F
#define RIGHT 10.0F
#define BOTTOM 0.0F
#define TOP 20.0F
#define NEAR -1.0F
#define FAR 1.0F

int main()
{
	srand((unsigned)time(0));
	
	graphics::Window window(450, 900, "Tetris Test");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	board::Board board;
	block::Block* block = block::Block::instantiateRandomBlock();

	board.placeBlock(*block);

	std::cout << board;

	GLfloat vertices[18];
	memcpy(vertices, board.getBlockComponant(0, 0)->getVertices(), 18 * sizeof(GLfloat));

	GLuint vbo;
	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	maths::mat4 orthographic = maths::mat4::orthographic(LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR);
	graphics::Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shader.enable();

	shader.setUniformMat4(PROJECTION_MATRIX, orthographic);
	shader.setUniform4f(COLOR_MATRIX, maths::vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed()) {
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}
	return 0;
}