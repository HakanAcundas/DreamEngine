#include "VertexArray.h"

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

	void VertexArray::AddBuffer(Buffer* buffer, int index)
	{
		Bind();
		buffer->Bind();
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->GetCount(), GL_FLOAT, GL_FALSE, 0, 0);
		buffer->Unbind();
		Unbind();
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::Unbind() const

	{
		glBindVertexArray(0);
	}
}}
 