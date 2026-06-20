#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace dream { namespace graphics {
	class Shader
	{
	public:
		Shader() = default;
		Shader(const std::string& vertex_path, const std::string& frag_path);
		~Shader();

		void bind();
		void unbind();

		void enable();
		void disable();

#pragma region Uniform Setters
#pragma endregion Uniform Setters

#pragma region Uniform Getters;
#pragma endregion Uniform Getters

	private:
		unsigned int compile(const char* vert_src, const char* frag_src);
		unsigned int compile_stage(const char* src, unsigned int type);
		int get_uniform_location(const std::string& name);
	
		unsigned int m_shader_id = 0;
		std::unordered_map<std::string, unsigned int> m_uniform_cache;
	};
}}