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
		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddBuffer(Buffer* buffer)
	{
		Bind();
		buffer->Bind();
		for (BufferElement* element : buffer->GetBufferElements())
		{
			glEnableVertexAttribArray(m_BufferIndex);
			glVertexAttribPointer(m_BufferIndex, element->Count,
				GL_FLOAT, element->Normalized ? GL_TRUE : GL_FALSE,
				buffer->GetStride(),
				(const void*)element->Offset);
			m_BufferIndex++;
		}
		m_Buffers.push_back(buffer);
	}

	void VertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
	{
		glBindVertexArray(m_ArrayID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}}
 