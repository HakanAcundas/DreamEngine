#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "shader.hpp"
#include "../utils/log.hpp"
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
			DREAM_LOG_TAG_ERROR("[SHADER]", " Compiler error: {}", log);
		}

		return s;
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
			DREAM_LOG_TAG_ERROR("[SHADER]", " Link error: {}", log);
		}

		glDeleteShader(vert);
		glDeleteShader(frag);
	}

	void Shader::bind()
	{
		glUseProgram(m_shader_id);
	}

	void Shader::unbind()
	{
		glUseProgram(0);
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
		auto it = m_uniform_cache.find(name);
		if (it != m_uniform_cache.end())
			return it->second;

		int location = glGetUniformLocation(m_shader_id, name.c_str());
		m_uniform_cache[name] = location;
		return location;
	}

#pragma region Uniform set functions
	void Shader::set_int(const std::string& name, int v)
	{
		glUniform1i(get_uniform_location(name), v);
	}

	void Shader::set_float(const std::string& name, float v)
	{
		glUniform1f(get_uniform_location(name), v);
	}

	void Shader::set_vec2(const std::string& name, const glm::vec2& v)
	{
		glUniform2fv(get_uniform_location(name), 1, glm::value_ptr(v));
	}

	void Shader::set_vec4(const std::string& name, const glm::vec4& v)
	{
		glUniform4fv(get_uniform_location(name), 1, glm::value_ptr(v));
	}

	void Shader::set_mat4(const std::string& name, const glm::mat4& v)
	{
		glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(v));
	}

	void Shader::set_int_array(const std::string& name, const int* values, int count)
	{
		glUniform1iv(get_uniform_location(name), count, values);
	}
#pragma endregion Uniform set functions
}}