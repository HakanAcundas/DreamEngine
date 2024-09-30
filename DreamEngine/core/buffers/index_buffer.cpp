#include "index_buffer.h"

namespace dream { namespace graphics {

	IndexBuffer::IndexBuffer(unsigned int* indices, int count)
	{
		this->m_Count = count;

		glCreateBuffers(1, &m_IndexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_IndexBufferID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::IndexBuffer(unsigned short* indices, int count)
	{
		this->m_Count = count;

		glCreateBuffers(1, &m_IndexBufferID);

		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
		glBindBuffer(GL_ARRAY_BUFFER, m_IndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned short), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBufferID);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}}
