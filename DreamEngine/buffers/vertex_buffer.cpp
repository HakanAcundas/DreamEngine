#include "vertex_buffer.hpp"

namespace dream { namespace buffer { 
	VertexBuffer::VertexBuffer(size_t size_bytes)
	{
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, size_bytes, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(void* data, size_t size_bytes)
	{
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, size_bytes, nullptr, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		if (m_vbo)
			glDeleteBuffers(1, &m_vbo);
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}}
