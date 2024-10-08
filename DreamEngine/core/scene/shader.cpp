#include <iostream>
#include <vector>
#include "shader.h"

using namespace dream;
using namespace utils;

namespace dream { namespace graphics {

	Shader::Shader(const char* vertexPath, const char* fragPath)
	{
		this->m_vertex_path = vertexPath;
		this->m_fragment_path = fragPath;
		m_shader_id = create_program();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_shader_id);
	}

	unsigned int Shader::create_program()
	{
		// Vertex Shader
		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		std::string v_source_string = FileUtils::read_file(m_vertex_path);
		const char* v_shader_source = v_source_string.c_str();

		glShaderSource(vertex, 1, &v_shader_source, NULL);
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
		std::string f_source_string = FileUtils::read_file(m_fragment_path);
		const char* f_shader_source = f_source_string.c_str();

		glShaderSource(fragment, 1, &f_shader_source, NULL);
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

		int is_linked;
		glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
		if (is_linked == GL_FALSE)
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

	void Shader::enable()
	{
		glUseProgram(m_shader_id);
	}

	void Shader::disable()
	{
		glUseProgram(0);
	}

	int Shader::get_uniform_location(const char *name)
	{
		return glGetUniformLocation(m_shader_id, name);
	}

#pragma region Uniform Setters
	void Shader::set_uniform1f(const char *name, float value)
	{
		glUniform1f(get_uniform_location(name), value);
	}

	void Shader::set_uniform1fv(const char *name, float *value, int count)
	{
		glUniform1fv(get_uniform_location(name), count, value);
	}

	void Shader::set_uniform1i(const char *name, int value)
	{
		glUniform1i(get_uniform_location(name), value);
	}

	void Shader::set_uniform1iv(const char *name, int *value, int count)
	{
		glUniform1iv(get_uniform_location(name), count, value);
	}

	void Shader::set_uniform2f(const char *name, const glm::vec2 &vector)
	{
		glUniform2f(get_uniform_location(name), vector.x, vector.y);
	}

	void Shader::set_uniform3f(const char *name, const glm::vec3 &vector)
	{
		glUniform3f(get_uniform_location(name), vector.x, vector.y, vector.z);
	}

	void Shader::set_uniform4f(const char *name, const glm::vec4 &vector)
	{
		glUniform4f(get_uniform_location(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::set_uniformMat4(const char *name, const glm::mat4 &matrix)
	{
		glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}
#pragma endregion Uniform Setters

#pragma region Uniform Getters
	void Shader::get_uniform1f(const char *name, float* data)
	{
		glGetnUniformfv(m_shader_id, get_uniform_location(name), 4, data);
	}

	void Shader::get_uniform1i(const char *name, int* data)
	{
		//glGetUniformfv(m_ShaderID, get_uniform_location(name), data);
	}

	void Shader::get_uniform2f(const char *name, float data[2])
	{
		glGetnUniformfv(m_shader_id, get_uniform_location(name), 8, data);
	}

	void Shader::get_uniform3f(const char *name, float data[3])
	{
		glGetnUniformfv(m_shader_id, get_uniform_location(name), 12, data);
	}

	void Shader::get_uniform4f(const char *name, float data[4])
	{
		glGetnUniformfv(m_shader_id, get_uniform_location(name), 16, data);
	}
	
	void Shader::get_uniformMat4(const char *name, float data[16])
	{
		glGetnUniformfv(m_shader_id, get_uniform_location(name), 64, data);
	}
#pragma endregion Uniform Getters
}}