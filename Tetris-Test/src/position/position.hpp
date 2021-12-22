#pragma once

namespace position {

	class Position
	{
	private:
		int m_PosX;
		int m_PosY;

	public:
		Position();
		Position(int x, int y);

		inline int getXPos() const { return this->m_PosX; }
		inline int getYPos() const { return this->m_PosY; }
	};

}
