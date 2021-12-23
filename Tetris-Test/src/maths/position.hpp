#pragma once

#include <iostream>

namespace maths {

	struct Position
	{
	private:
		unsigned int m_PosX;
		unsigned int m_PosY;

	public:
		Position();
		Position(unsigned int x, unsigned int y);

		inline unsigned int getXPos() const { return this->m_PosX; }
		inline unsigned int getYPos() const { return this->m_PosY; }

		inline void setXPos(unsigned int x) { this->m_PosX = x; }
		inline void setYPos(unsigned int y) { this->m_PosY = y; }

		friend Position operator+(Position a, const Position& b);
		friend Position operator-(Position a, const Position& b);
		friend Position operator*(Position a, const Position& b);
		friend Position operator/(Position a, const Position& b);

		bool operator==(const Position& pos);
		bool operator!=(const Position& pos);

		Position& operator+=(const Position& pos);
		Position& operator-=(const Position& pos);
		Position& operator*=(const Position& pos);
		Position& operator/=(const Position& pos);

		friend std::ostream& operator<<(std::ostream& stream, const Position& pos);

	private:
		Position& add(const Position& other);
		Position& substract(const Position& other);
		Position& multiply(const Position& other);
		Position& divide(const Position& other);
	};

}