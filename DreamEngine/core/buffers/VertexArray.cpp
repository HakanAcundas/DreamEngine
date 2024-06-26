#include "VertexArray.h"

namespace dream { namespace graphics {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ArrayID);
	}

	VertexArray::~VertexArray()
	{
		for (auto it = m_Buffers.begin(); it != m_Buffers.end(); it++)
		{
			m_Buffers.erase(it);
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
		const auto& bufferElements = buffer->GetBufferElements();
		for (auto element : bufferElements)
		{
			glEnableVertexAttribArray(m_BufferIndex);
			glVertexAttribPointer(m_BufferIndex, element->count,
				GL_FLOAT, element->normalized ? GL_TRUE : GL_FALSE,
				buffer->GetStride(),
				(const void*)element->offset);
			m_BufferIndex++;
		}
		m_Buffers.emplace_back(buffer);
	}

	void VertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
	{
		glBindVertexArray(m_ArrayID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}}
 