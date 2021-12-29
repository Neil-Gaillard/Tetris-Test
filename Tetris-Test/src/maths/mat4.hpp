#pragma once

#include "vec4.hpp"

namespace maths {
	
	struct mat4
	{
		union 
		{
			float elements[4 * 4]{};
			vec4 columns[4];
		};

		mat4();
		explicit mat4(const float diagonal);

		static mat4 identity();

		mat4& multiply(const mat4& other);

		friend mat4 operator*(mat4 left, const mat4& right);
		mat4& operator*=(const mat4& other);

		static mat4 orthographic(const float left, const float right, const float bottom, const float top, const float near, const float far);
	};

}