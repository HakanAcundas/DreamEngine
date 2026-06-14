#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "shader.hpp"
#include "../utils/file_utils.hpp"

namespace dream { namespace graphics {

	Shader::Shader(const std::string& vertex_path, const std::string& frag_path)
	{
		std::string vert_src = utils::FileUtils::read_file(vertex_path);
		std::string frag_src = utils::FileUtils::read_file(frag_path);
		compile(vert_src.c_str(), frag_src.c_str());
	}

	Shader::~Shader()
	{
		if (m_shader_id)
			glDeleteProgram(m_shader_id);
	}

	unsigned int Shader::compile(const char* vert_src, const char* frag_src)
	{
		unsigned int vert = compile_stage(vert_src, GL_VERTEX_SHADER);
		unsigned int frag = compile_stage(frag_src, GL_FRAGMENT_SHADER);

		m_shader_id = glCreateProgram();
		glAttachShader(m_shader_id, vert);
		glAttachShader(m_shader_id, frag);
		glLinkProgram(m_shader_id);

		int ok;
		glGetProgramiv(m_shader_id, GL_LINK_STATUS, &ok);
		if (!ok)
		{
			char log[512]; glGetProgramInfoLog(m_shader_id, 512, nullptr, log);
			std::cerr << "[Shader] Link error: " << log << '\n';
		}

		glDeleteShader(vert);
		glDeleteShader(frag);
	}

	unsigned int Shader::compile_stage(const char* src, unsigned int type)
	{
		unsigned int s = glCreateShader(type);
		glShaderSource(s, 1, &src, nullptr);
		glCompileShader(s);

		int ok;
		glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
		if (!ok)
		{
			char log[512]; glGetShaderInfoLog(s, 512, nullptr, log);
			std::cerr << "[Shader] Compile error: " << log << '\n';
		}
		
		return s;
	}

	void Shader::enable()
	{
		glUseProgram(m_shader_id);
	}

	void Shader::disable()
	{
		glUseProgram(0);
	}

	int Shader::get_uniform_location(const std::string& name)
	{
		return glGetUniformLocation(m_shader_id, name.c_str());
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