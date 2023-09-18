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
		std::string Name;
		ShaderDataType Type;
		uint8_t Count = 1;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(const std::string& name, ShaderDataType type, uint8_t count, bool normalized = false)
			: Name(name), Type(type), Count(count), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t ShaderDataTypeSize(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:    return 4 * Count;
			case ShaderDataType::Int:      return 4 * Count;
			case ShaderDataType::Bool:     return 1 * Count;
			}

			return 0;
		}

		GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) const
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
	public:
		Buffer(unsigned int size);
		Buffer(float* data, unsigned int size);
		~Buffer();

		void Bind() const;
		void Unbind() const;

		void AddBufferElement(std::string name, ShaderDataType type, uint8_t count = 1, bool normalized = false);
		void SetData(const void* data,  unsigned int size);

		inline unsigned int const GetCount() { return m_ComponentCount; }
	};
}}
