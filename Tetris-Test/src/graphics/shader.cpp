#include "shader.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace graphics {
	std::string read_file(const char* filepath);

	Shader::Shader(const char* vertPath, const char* fragPath)
		: m_VertexShaderPath(vertPath), m_FragmentShaderPath(fragPath)
	{
		m_ShaderID = load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::load()
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = read_file(m_VertexShaderPath);
		std::string fragSourceString = read_file(m_FragmentShaderPath);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);

		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	void Shader::enable() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}

	void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix)
	{
		glUniformMatrix4fvARB(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	GLint Shader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(m_ShaderID, name);
	}

	std::string read_file(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt");
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);

		char* data = new char[length + 1];
		memset(data, 0, length + 1);

		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;

		return result;
	}

}