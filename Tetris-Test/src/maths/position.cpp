#include "position.hpp"

namespace maths {

	Position::Position() : Position::Position(0, 0) { }
	Position::Position(unsigned int x, unsigned int y) : m_PosX(x), m_PosY(y) { }

	Position& Position::add(const Position& other)
	{
		this->m_PosX += other.m_PosX;
		this->m_PosY += other.m_PosY;
		return *this;
	}

	Position& Position::substract(const Position& other)
	{
		this->m_PosX -= other.m_PosX;
		this->m_PosY -= other.m_PosY;
		return *this;
	}

	Position& Position::multiply(const Position& other)
	{
		this->m_PosX *= other.m_PosX;
		this->m_PosY *= other.m_PosY;
		return *this;
	}

	Position& Position::divide(const Position& other)
	{
		this->m_PosX /= other.m_PosX;
		this->m_PosY /= other.m_PosY;
		return *this;
	}

	bool Position::operator==(const Position& pos)
	{
		return (this->m_PosX == pos.m_PosX && this->m_PosY == pos.m_PosY);
	}

	bool Position::operator!=(const Position& pos)
	{
		return !(*this == pos);
	}

	Position& Position::operator+=(const Position& pos)
	{
		return this->add(pos);
	}

	Position& Position::operator-=(const Position& pos)
	{
		return this->substract(pos);
	}

	Position& Position::operator*=(const Position& pos)
	{
		return this->multiply(pos);
	}

	Position& Position::operator/=(const Position& pos)
	{
		return this->divide(pos);
	}

	Position operator+(Position a, const Position& b)
	{
		return a.add(b);
	}

	Position operator-(Position a, const Position& b)
	{
		return a.substract(b);
	}

	Position operator*(Position a, const Position& b)
	{
		return a.multiply(b);
	}

	Position operator/(Position a, const Position& b)
	{
		return a.divide(b);
	}

	std::ostream& operator<<(std::ostream& stream, const Position& pos)
	{
		stream << "Position : (" << pos.m_PosX << "," << pos.m_PosY << ")";
		return stream;
	}
}