#pragma once

#include "../position/position.hpp"

namespace block {

	struct BlockComponant
	{
	private:
		position::Position m_Pos;
		bool active;

	public:
		BlockComponant(unsigned int x, unsigned int y);

		inline position::Position getPos() const { return this->m_Pos; }

		inline void setPosX(const unsigned int x) { this->m_Pos.setXPos(x); }
		inline void setPosY(const unsigned int y) { this->m_Pos.setYPos(y); }

		friend std::ostream& operator<<(std::ostream& stream, const BlockComponant& blockComponant);
	};
}