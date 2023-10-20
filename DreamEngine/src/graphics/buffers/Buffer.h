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
		uint32_t Count = 1;
		unsigned int Size;
		size_t Offset = 0;
		bool Normalized;

		BufferElement() = default;

		BufferElement(const std::string& name, ShaderDataType type, unsigned int count, bool normalized = false)
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
