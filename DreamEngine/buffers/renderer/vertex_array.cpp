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

		void VertexArray::set_sprite_layout()
		{
			constexpr size_t stride = 36; // sizeof(Vertex)

			// position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (const void*)0);

			// color
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const void*)0);

			// uv
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (const void*)0);

			// texture index
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, (const void*)0);
		}
}}
