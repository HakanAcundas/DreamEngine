#include "vertexArray.h"

namespace dream { namespace graphics {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ArrayID);
	}

	VertexArray::~VertexArray()
	{
		for (int i = 0; i < m_Buffers.size(); i++)
		{
			delete m_Buffers[i];
		}
	}

	void VertexArray::addBuffer(Buffer* buffer, int index)
	{
		bind();
		buffer->bind();
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->getCount(), GL_FLOAT, GL_FALSE, 0, 0);
		buffer->unbind();
		unbind();
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::unbind() const

	{
		glBindVertexArray(0);
	}
}}