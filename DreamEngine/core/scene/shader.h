#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "../utils/file_utils.h"

namespace dream { namespace graphics {

	class Shader
	{
	private:
		unsigned int m_shader_id;
		const char *m_vertex_path;
		const char *m_fragment_path;

		unsigned int create_program();
		int get_uniform_location(const char *name);
	public:
		Shader(const char *vertex_path, const char *frag_path);
		~Shader();

#pragma region Uniform Setters
		void set_uniform1f(const char *name, float value);
		void set_uniform1fv(const char *name, float *value, int count);
		void set_uniform1i(const char *name, int value);
		void set_uniform1iv(const char *name, int *value, int count);
		void set_uniform2f(const char *name, const glm::vec2 &vector);
		void set_uniform3f(const char *name, const glm::vec3 &vector);
		void set_uniform4f(const char *name, const glm::vec4 &vector);
		void set_uniformMat4(const char* name, const glm::mat4 &matrix);
#pragma endregion Uniform Setters

#pragma region Uniform Getters
		void get_uniform1f(const char *name, float *data);
		void get_uniform1i(const char *name, int *data);
		void get_uniform2f(const char *name, float data[2]);
		void get_uniform3f(const char *name, float data[3]);
		void get_uniform4f(const char *name, float data[4]);
		void get_uniformMat4(const char *name, float data[16]);
#pragma endregion Uniform Getters

		void enable();
		void disable();
	};
}}