#pragma once

#include <GL/glew.h>

#include "../maths/mat4.hpp"

namespace graphics {

	class Shader
	{
	private:
		const char* m_VertexShaderPath;
		const char* m_FragmentShaderPath;
		GLuint m_ShaderID;

	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void enable() const;
		static void disable();

		GLint getUniformLocation(const GLchar* name) const;
		
		void setUniform4f(const GLchar* name, const maths::vec4& vector) const;
		void setUniformMat4(const GLchar* name, const maths::mat4& matrix) const;

	private:
		GLuint load() const;
	};
}