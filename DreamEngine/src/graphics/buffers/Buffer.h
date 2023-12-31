#pragma once
#include<string>
#include<vector>
#include <GL/glew.h>

namespace dream { namespace graphics {

	static enum class ShaderDataType
	{
		None = 0, Float, Int, Bool
	};

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		uint32_t count = 1;
		unsigned int size;
		size_t offset = 0;
		bool normalized;

		BufferElement() = default;

		BufferElement(const std::string& name, ShaderDataType type, unsigned int count, bool normalized = false)
			: name(name), type(type), count(count), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
		{
		}

		uint32_t ShaderDataTypeSize(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:    return 4 * count;
			case ShaderDataType::Int:      return 4 * count;
			case ShaderDataType::Bool:     return 1 * count;
			}

			return 0;
		}

		static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
			}

			return 0;
		}


	};

	class Buffer
	{
	private:
		unsigned int m_BufferID;
		unsigned int m_ComponentCount;
		std::vector<BufferElement*> m_BufferElements;
		uint32_t m_Stride = 0;

	public:
		Buffer(unsigned int size);
		Buffer(float* data, unsigned int size);
		~Buffer();

		void Bind() const;
		void Unbind() const;

		void AddBufferElement(std::string name, ShaderDataType type, uint8_t count = 1, bool normalized = false);
		void SetData(const void* data, uint32_t size);
		void CalculateStride();

		inline unsigned int const GetCount() { return m_ComponentCount; }
		std::vector<BufferElement*> GetBufferElements() { return m_BufferElements; }
		unsigned int GetStride() const { return m_Stride; }
	};
}}
