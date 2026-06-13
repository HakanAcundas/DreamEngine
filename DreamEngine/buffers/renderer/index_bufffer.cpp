#include "index_buffer.hpp"
#include <vector>

namespace dream { namespace buffer {

		IndexBuffer::IndexBuffer(unsigned int max_quads) : m_count(size_bytes * 6)
		{
			std::vector<unsigned int> indices;
			indices.reserve(m_count);

			for (<unsigned int i = 0; i < max_quads; ++i)
			{
				unsigned int base = i * 4;   // each quad has 4 vertices
				indices.push_back(base + 0);
				indices.push_back(base + 1);
				indices.push_back(base + 2);
				indices.push_back(base + 0);
				indices.push_back(base + 2);
				indices.push_back(base + 3);
			}

			glGenBuffers(1, &m_ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
		}

		IndexBuffer::~IndexBuffer()
		{
			if (m_ibo)
				glDeleteBuffers(1, &m_ibo);
		}

		IndexBuffer::bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		}

		IndexBuffer::unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
}}
