#include "position.hpp"

namespace maths {

	position::position() : position(0, 0) { }
	position::position(const int x, const int y) : m_pos_x_(x), m_pos_y_(y) { }

	position& position::add(const position& other)
	{
		this->m_pos_x_ += other.m_pos_x_;
		this->m_pos_y_ += other.m_pos_y_;
		return *this;
	}

	position& position::substract(const position& other)
	{
		this->m_pos_x_ -= other.m_pos_x_;
		this->m_pos_y_ -= other.m_pos_y_;
		return *this;
	}

	bool position::operator==(const position& pos) const
	{
		return (this->m_pos_x_ == pos.m_pos_x_ && this->m_pos_y_ == pos.m_pos_y_);
	}

	bool position::operator!=(const position& pos) const
	{
		return !(*this == pos);
	}

	position& position::operator+=(const position& pos)
	{
		return this->add(pos);
	}

	position& position::operator-=(const position& pos)
	{
		return this->substract(pos);
	}

	position operator+(position a, const position& b)
	{
		return a.add(b);
	}

	position operator-(position a, const position& b)
	{
		return a.substract(b);
	}
}