#pragma once

#include <glad/glad.h>

namespace dream { namespace buffer {
	class IndexBuffer
	{
	public:
		IndexBuffer() = default;

		// Generate indices for `max_quads` quads upfront
		IndexBuffer(unsigned int max_quads);
		~IndexBuffer();

		void bind();
		void unbind();

	private:
		unsigned int   m_ibo = 0;
		unsigned int   m_count = 0;
	};
}}
