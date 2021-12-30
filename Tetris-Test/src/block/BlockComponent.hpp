#pragma once

#include "../maths/position.hpp"
#include "../maths/vec4.hpp"

#include "GL/glew.h"

namespace block {

	struct BlockComponent
	{
	private:
		maths::position m_Pos;
		maths::vec4 m_Color;
		bool m_Active;

		GLfloat* m_Vertices;

	public:
		BlockComponent(int x, int y, maths::vec4 color, bool active);
		BlockComponent(int x, int y, maths::vec4 color);

		inline maths::position getPos() const { return this->m_Pos; }

		inline bool isActive() const { return this->m_Active; }

		inline maths::vec4 getColor() const { return this->m_Color; }

		inline GLfloat* getVertices() const { return this->m_Vertices; }

		inline void setPosX(const int x) { this->m_Pos.set_x_pos(x); }
		inline void setPosY(const int y) { this->m_Pos.set_y_pos(y); }

		inline void setActive(const bool active) { this->m_Active = active; }

		inline void setColor(const maths::vec4 color) { this->m_Color = color; }
	};
}