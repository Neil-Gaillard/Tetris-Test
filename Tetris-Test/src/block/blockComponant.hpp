#pragma once

#include "../maths/position.hpp"

#include "GL/glew.h"

namespace block {

	struct BlockComponant
	{
	private:
		maths::Position m_Pos;
		bool active;

	public:
		BlockComponant(unsigned int x, unsigned int y, bool active);
		BlockComponant(unsigned int x, unsigned int y);

		inline maths::Position getPos() const { return this->m_Pos; }

		inline bool isActive() const { return this->active; }

		inline void setPosX(const unsigned int x) { this->m_Pos.setXPos(x); }
		inline void setPosY(const unsigned int y) { this->m_Pos.setYPos(y); }

		GLfloat* getVertices();

		inline void setActive(const bool active) { this->active = active; }

		friend std::ostream& operator<<(std::ostream& stream, const BlockComponant& blockComponant);
	};
}