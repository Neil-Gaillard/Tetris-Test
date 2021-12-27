#pragma once

#include "../maths/position.hpp"
#include "../maths/vec4.hpp"

#include "GL/glew.h"

namespace block {

	struct BlockComponant
	{
	private:
		maths::Position m_Pos;
		maths::vec4 m_Color;
		bool active;

	public:
		BlockComponant(unsigned int x, unsigned int y, maths::vec4 color, bool active);
		BlockComponant(unsigned int x, unsigned int y, maths::vec4 color);

		inline maths::Position getPos() const { return this->m_Pos; }

		inline bool isActive() const { return this->active; }

		inline maths::vec4 getColor() const { return this->m_Color; }

		GLfloat* getVertices();

		inline void setPosX(const unsigned int x) { this->m_Pos.setXPos(x); }
		inline void setPosY(const unsigned int y) { this->m_Pos.setYPos(y); }

		inline void setActive(const bool active) { this->active = active; }

		inline void setColor(const maths::vec4 color) { this->m_Color = color; }

		friend std::ostream& operator<<(std::ostream& stream, const BlockComponant& blockComponant);
	};
}