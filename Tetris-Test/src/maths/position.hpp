#pragma once

#include <iostream>

namespace maths {

	struct Position
	{
	private:
		int m_PosX;
		int m_PosY;

	public:
		Position();
		Position(int x, int y);

		inline int getXPos() const { return this->m_PosX; }
		inline int getYPos() const { return this->m_PosY; }

		inline void setXPos(int x) { this->m_PosX = x; }
		inline void setYPos(int y) { this->m_PosY = y; }

		friend Position operator+(Position a, const Position& b);
		friend Position operator-(Position a, const Position& b);

		bool operator==(const Position& pos);
		bool operator!=(const Position& pos);

		Position& operator+=(const Position& pos);
		Position& operator-=(const Position& pos);

	private:
		Position& add(const Position& other);
		Position& substract(const Position& other);
	};

}