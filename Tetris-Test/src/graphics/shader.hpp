#pragma once

#include <GL/glew.h>

#include "../maths/mat4.hpp"

namespace graphics {

	class Shader
	{
	private:
		GLuint m_ShaderID;
		const char* m_VertexShaderPath;
		const char* m_FragmentShaderPath;

	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void enable();
		void disable() const;

		GLint getUniformLocation(const GLchar* name);
		
		void setUniform4f(const GLchar* name, const maths::vec4& vector);
		void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

	private:
		GLuint load();
	};
}