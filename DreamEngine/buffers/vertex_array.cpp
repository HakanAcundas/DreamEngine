#include "vertex_array.h"

namespace dream { namespace graphics {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_arrayID);
	}

	VertexArray::~VertexArray()
	{
		for (auto it = m_buffers.begin(); it != m_buffers.end(); it++)
		{
			m_buffers.erase(it);
		}
		glDeleteVertexArrays(1, &m_arrayID);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_arrayID);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::add_buffer(Buffer *buffer)
	{
		bind();
		buffer->bind();
		const auto &buffer_elements = buffer->get_buffer_elements();
		for (auto element : buffer_elements)
		{
			glEnableVertexAttribArray(m_buffer_index);
			glVertexAttribPointer(m_buffer_index, element->count,
				GL_FLOAT, element->normalized ? GL_TRUE : GL_FALSE,
				buffer->get_stride(),
				(const void*)element->offset);
			m_buffer_index++;
		}
		m_buffers.emplace_back(buffer);
	}

	void VertexArray::set_index_buffer(IndexBuffer *index_buffer)
	{
		glBindVertexArray(m_arrayID);
		index_buffer->bind();
		m_index_buffer = index_buffer;
	}
}}
 