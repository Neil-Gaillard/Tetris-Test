#include "blockComponant.hpp"

namespace block {

	BlockComponant::BlockComponant(unsigned int x, unsigned int y, bool active) : m_Pos(x, y), active(active)
	{

	}

	BlockComponant::BlockComponant(unsigned int x, unsigned int y) : BlockComponant(x, y, false)
	{

	}

	GLfloat* BlockComponant::getVertices()
	{
		GLfloat vertices[18] =
		{
			this->getPos().getYPos(),        20.0f - this->getPos().getXPos() - 1.0f, 0.0f,
			this->getPos().getYPos(),        20.0f - this->getPos().getXPos(),        0.0f,
			this->getPos().getYPos() + 1.0f, 20.0f - this->getPos().getXPos(),        0.0f,
			this->getPos().getYPos() + 1.0f, 20.0f - this->getPos().getXPos(),        0.0f,
			this->getPos().getYPos() + 1.0f, 20.0f - this->getPos().getXPos() - 1.0f, 0.0f,
			this->getPos().getYPos(),        20.0f - this->getPos().getXPos() - 1.0f, 0.0f
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