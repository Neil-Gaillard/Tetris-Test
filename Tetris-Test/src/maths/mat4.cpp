#include "mat4.hpp"

namespace maths {

	mat4::mat4()
	{
		for (float& element : elements)
			element = 0.0f;
	}

	mat4::mat4(const float diagonal)
	{
		for (float& element : elements)
			element = 0.0f;

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	mat4 mat4::identity()
	{
		return mat4(1.0f);
	}

	mat4& mat4::multiply(const mat4& other)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[i + e * 4] * (other.elements[e + j * 4]);
				}
				elements[i + j * 4] = sum;
			}
		}
		return *this;
	}

	mat4 operator*(mat4 left, const mat4& right)
	{
		return left.multiply(right);
	}

	mat4& mat4::operator*=(const mat4& other)
	{
		return multiply(other);
	}

	mat4 mat4::orthographic(const float left, const float right, const float bottom, const float top, const float near, const float far)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}
}