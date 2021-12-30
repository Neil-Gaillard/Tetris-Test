#include "BlockComponent.hpp"

#include "../board/board.hpp"

namespace block {

	BlockComponent::BlockComponent(const int x, const int y, const maths::vec4 color, const bool active) : m_Pos(x, y), m_Color(color), m_Active(active),
		m_Vertices(new GLfloat[18])
	{
		const GLfloat vertices[18] =
		{
			static_cast<GLfloat>(this->getPos().get_y_pos()),        board::Board::HEIGHT - static_cast<GLfloat>(this->getPos().get_x_pos()) - 1.0f, 0.0f,
			static_cast<GLfloat>(this->getPos().get_y_pos()),        board::Board::HEIGHT - static_cast<GLfloat>(this->getPos().get_x_pos()),        0.0f,
			static_cast<GLfloat>(this->getPos().get_y_pos()) + 1.0f, board::Board::HEIGHT - static_cast<GLfloat>(this->getPos().get_x_pos()),        0.0f,
			static_cast<GLfloat>(this->getPos().get_y_pos()) + 1.0f, board::Board::HEIGHT - static_cast<GLfloat>(this->getPos().get_x_pos()),        0.0f,
			static_cast<GLfloat>(this->getPos().get_y_pos()) + 1.0f, board::Board::HEIGHT - static_cast<GLfloat>(this->getPos().get_x_pos()) - 1.0f, 0.0f,
			static_cast<GLfloat>(this->getPos().get_y_pos()),        board::Board::HEIGHT - static_cast<GLfloat>(this->getPos().get_x_pos()) - 1.0f, 0.0f
		};
		memcpy(this->m_Vertices, vertices, sizeof(GLfloat) * 18);
	}

	BlockComponent::BlockComponent(const int x, const int y, const maths::vec4 color) : BlockComponent(x, y, color, false)
	{

	}
}