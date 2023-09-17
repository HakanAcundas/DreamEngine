#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "../utils/FileUtils.h"

namespace dream { namespace graphics {

	class Shader
	{
	private:
		unsigned int m_ShaderID;
		const char* m_VertexPath;
		const char* m_FragmentPath;

		unsigned int CreateProgram();
		int GetUniformLocation(const char* name);
	public:
		Shader(const char* vertexPath, const char* fragPath);
		~Shader();

		void SetUniform1f(const char* name, float value);
		void SetUniform1fv(const char* name, float* value, int count);
		void SetUniform1i(const char* name, int value);
		void SetUniform1iv(const char* name, int* value, int count);
		void SetUniform2f(const char* name, const glm::vec2& vector);
		void SetUniform3f(const char* name, const glm::vec3& vector);
		void SetUniform4f(const char* name, const glm::vec4& vector);
		void SetUniformMat4(const char* name, const glm::mat4& matrix);

		void Enable();
		void Disable();
	};
}}