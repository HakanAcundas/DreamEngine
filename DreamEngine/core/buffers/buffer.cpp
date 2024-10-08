#include "buffer.h"

namespace dream { namespace graphics {

	Buffer::Buffer(unsigned int size)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::Buffer(float *data, unsigned int size)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_bufferID);
	}

	void Buffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	}

	void Buffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Buffer::add_buffer_element(std::string name, ShaderDataType type, uint8_t count, bool normalized)
	{
		BufferElement* element = new BufferElement(name, type, count, normalized);
		m_buffer_elements.emplace_back(element);
	}

	void Buffer::set_data(const void *data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void Buffer::calculate_stride()
	{
		size_t offset = 0;
		m_stride = 0;
		for (auto &element : m_buffer_elements)
		{
			element->offset = offset;
			offset += element->size;
			m_stride += element->size;
		}
	}
}}
