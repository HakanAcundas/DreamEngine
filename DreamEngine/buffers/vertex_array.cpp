#include "vertex_array.hpp"

namespace dream { namespace buffer {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_vao);
	}

	VertexArray::~VertexArray()
	{
		if (m_vao)
			glDeleteVertexArrays(1, &m_vao);
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept
		: m_vao(other.m_vao)
	{
		other.m_vao = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		if (this != &other)
		{
			if (m_vao)
				glDeleteVertexArrays(1, &m_vao);

			m_vao = other.m_vao;
			other.m_vao = 0;
		}
		return *this;
	}

	void VertexArray::bind()
	{
		glBindVertexArray(m_vao);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::set_sprite_layout()
	{
		constexpr size_t stride = 36; // sizeof(Vertex)

		// position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (const void*)0);

		// uv
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (const void*)0);
		
		// texture index
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, stride, (const void*)0);

		// color
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride, (const void*)0);
	}
}}
