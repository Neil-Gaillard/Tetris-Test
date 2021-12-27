#include "blockComponant.hpp"

#include "../board/board.hpp"

namespace block {

	BlockComponant::BlockComponant(unsigned int x, unsigned int y, maths::vec4 color, bool active) : m_Pos(x, y), active(active), m_Color(color)
	{

	}

	BlockComponant::BlockComponant(unsigned int x, unsigned int y, maths::vec4 color) : BlockComponant(x, y, color, false)
	{

	}

	GLfloat* BlockComponant::getVertices()
	{
		GLfloat vertices[18] = 
		{
			(GLfloat) this->getPos().getYPos(),        board::Board::HEIGHT - (GLfloat) this->getPos().getXPos() - 1.0f, 0.0f,
			(GLfloat) this->getPos().getYPos(),        board::Board::HEIGHT - (GLfloat) this->getPos().getXPos(),        0.0f,
			(GLfloat) this->getPos().getYPos() + 1.0f, board::Board::HEIGHT - (GLfloat) this->getPos().getXPos(),        0.0f,
			(GLfloat) this->getPos().getYPos() + 1.0f, board::Board::HEIGHT - (GLfloat) this->getPos().getXPos(),        0.0f,
			(GLfloat) this->getPos().getYPos() + 1.0f, board::Board::HEIGHT - (GLfloat) this->getPos().getXPos() - 1.0f, 0.0f,
			(GLfloat) this->getPos().getYPos(),        board::Board::HEIGHT - (GLfloat) this->getPos().getXPos() - 1.0f, 0.0f
		};
		return vertices;
	}

	std::ostream& operator<<(std::ostream& stream, const BlockComponant& blockComponant)
	{
		switch (blockComponant.active) {
		case true:
			stream << "*";
			break;
		case false:
			stream << " ";
		}
		return stream;
	}
}