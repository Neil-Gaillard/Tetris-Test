#include "vec4.hpp"

namespace maths {

	vec4::vec4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	vec4::vec4(const float& x, const float& y, const float &z, const float &w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vec4& vec4::add(const vec4& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;
		return *this;
	}

	vec4& vec4::substract(const vec4& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		this->w -= other.w;
		return *this;
	}

	vec4 operator+(vec4 left, const vec4& right)
	{
		return left.add(right);
	}

	vec4 operator-(vec4 left, const vec4& right)
	{
		return left.substract(right);
	}

	vec4& vec4::operator+=(const vec4& other)
	{
		return add(other);
	}

	vec4& vec4::operator-=(const vec4& other)
	{
		return substract(other);
	}

	bool vec4::operator==(const vec4& other)
	{
		return (x == other.x && y == other.y && z == other.z && w == other.w);
	}

	bool vec4::operator!=(const vec4& other)
	{
		return !(*this == other);
	}
}