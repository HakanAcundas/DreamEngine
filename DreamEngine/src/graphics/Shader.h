#pragma once
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

#pragma region Uniform Setters
		void SetUniform1f(const char* name, float value);
		void SetUniform1fv(const char* name, float* value, int count);
		void SetUniform1i(const char* name, int value);
		void SetUniform1iv(const char* name, int* value, int count);
		void SetUniform2f(const char* name, const glm::vec2& vector);
		void SetUniform3f(const char* name, const glm::vec3& vector);
		void SetUniform4f(const char* name, const glm::vec4& vector);
		void SetUniformMat4(const char* name, const glm::mat4& matrix);
#pragma endregion Uniform Setters

		// TO DO Change the second parameter for each data type
#pragma region Uniform Getters
		void GetUniform1f(const char* name, float* data);
		void GetUniform1i(const char* name, int value);
		void GetUniform2f(const char* name, float data[2]);
		void GetUniform3f(const char* name, float data[3]);
		void GetUniform4f(const char* name, float data[4]);
		void GetUniformMat4(const char* name, const glm::mat4* matrix);
#pragma endregion Uniform Getters

		void Enable();
		void Disable();
	};
}}