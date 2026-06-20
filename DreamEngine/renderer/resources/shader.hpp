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

#pragma region Uniform set functions
		void set_int(const std::string& name, int v);
		void set_float(const std::string& name, float v);
		void set_vec2(const std::string& name, const glm::vec2& v);
		void set_vec4(const std::string& name, const glm::vec4& v);
		void set_mat4(const std::string& name, const glm::mat4& v);
		// Upload the texture slot array once at startup:
		// u_textures[0] = 0, u_textures[1] = 1, ... u_textures[31] = 31
		void set_int_array(const std::string& name, const int* values, int count);
#pragma endregion Uniform set functions

	private:
		unsigned int compile(const char* vert_src, const char* frag_src);
		unsigned int compile_stage(const char* src, unsigned int type);
		int get_uniform_location(const std::string& name);
	
		unsigned int m_shader_id = 0;
		std::unordered_map<std::string, int> m_uniform_cache;
	};
}}