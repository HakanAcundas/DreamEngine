#include <iostream>
#include <vector>
#include "Shader.h"

using namespace dream;
using namespace utils;

namespace dream { namespace graphics {

	Shader::Shader(const char* vertexPath, const char* fragPath)
	{
		this->m_VertexPath = vertexPath;
		this->m_FragmentPath = fragPath;
		m_ShaderID = CreateProgram();
	}

	Shader::~Shader()
	{

	}

	unsigned int Shader::CreateProgram()
	{
		// Vertex Shader
		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		std::string vertexSourceString = FileUtils::read_file(m_VertexPath);
		const char* vertexShaderSource = vertexSourceString.c_str();

		glShaderSource(vertex, 1, &vertexShaderSource, NULL);
		glCompileShader(vertex);

		int result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int lenght;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &lenght);
			std::vector<char> error(lenght);
			glGetShaderInfoLog(vertex, lenght, &lenght, &error[0]);
			std::cout << "Failed to compile Vertex Shader: " << std::endl << &error[0] << std::endl;
			glDeleteShader(vertex);
		}

		// Fragment Shader
		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
		std::string fragmentSourceString = FileUtils::read_file(m_FragmentPath);
		const char* fragmentShaderSource = fragmentSourceString.c_str();

		glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragment);
		
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int lenght;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &lenght);
			std::vector<char> error(lenght);
			glGetShaderInfoLog(fragment, lenght, &lenght, &error[0]);
			std::cout << "Failed to compile Fragment Shader: " << std::endl << &error[0] << std::endl;
			glDeleteShader(fragment);
		}

		// Shader Program
		unsigned int program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		int isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			int lenght;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &lenght);

			std::vector<char> error(lenght);
			glGetProgramInfoLog(program, lenght, &lenght, &error[0]);
			std::cout << "Shader linking failed: " << std::endl << &error[0] << std::endl;

			glDeleteProgram(program);
			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return program;
	}

	void Shader::Enable()
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::Disable()
	{
		glUseProgram(0);
	}

	int Shader::GetUniformLocation(const char* name)
	{
		return glGetUniformLocation(m_ShaderID, name);
	}

#pragma region Uniform Setters
	void Shader::SetUniform1f(const char* name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1fv(const char* name, float* value, int count)
	{
		glUniform1fv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform1i(const char* name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1iv(const char* name, int* value, int count)
	{
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform2f(const char* name, const glm::vec2& vector)
	{
		glUniform2f(GetUniformLocation(name), vector.x, vector.y);
	}

	void Shader::SetUniform3f(const char* name, const glm::vec3& vector)
	{
		glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform4f(const char* name, const glm::vec4& vector)
	{
		glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniformMat4(const char* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}
#pragma endregion Uniform Setters

#pragma region Uniform Getters
	void Shader::GetUniform1f(const char* name, float* data)
	{
		int b = GetUniformLocation("a_Positionss");
		glGetUniformfv(m_ShaderID, GetUniformLocation(name), data);
	}


	void Shader::GetUniform1i(const char* name, int data)
	{
		glGetUniformiv(m_ShaderID, GetUniformLocation(name), data);
	}


	void Shader::GetUniform2f(const char* name, float data[2])
	{
		glGetnUniformfv(m_ShaderID, GetUniformLocation(name), 2, data);
	}

	void Shader::GetUniform3f(const char* name, float data[3])
	{
		glGetnUniformfv(m_ShaderID, GetUniformLocation(name), 2, data);
	}

	void Shader::GetUniform4f(const char* name, float data[4])
	{
		glGetUniformfv(m_ShaderID, GetUniformLocation(name), x);
		glGetUniformfv(m_ShaderID, GetUniformLocation(name), y);
		glGetUniformfv(m_ShaderID, GetUniformLocation(name), z);
		glGetUniformfv(m_ShaderID, GetUniformLocation(name), w);
	}
	
	void Shader::GetUniformMat4(const char* name, const glm::mat4* matrix)
	{

	}
#pragma endregion Uniform Getters
}}