#include "buffer.h"

namespace dream { namespace graphics {

	Buffer::Buffer(unsigned int size)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::Buffer(float* data, unsigned int size)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_BufferID);
	}

	void Buffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void Buffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Buffer::AddBufferElement(std::string name, ShaderDataType type, uint8_t count, bool normalized)
	{
		BufferElement* element = new BufferElement(name, type, count, normalized);
		m_BufferElements.push_back(element);
	}

	void Buffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void Buffer::CalculateStride()
	{
		size_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_BufferElements)
		{
			element->Offset = offset;
			offset += element->Size;
			m_Stride += element->Size;
		}
	}
}}
