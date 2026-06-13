#pragma once

#include <glad/glad.h>

namespace dream { namespace buffer {
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;

		// Dynamic Buffer
		VertexBuffer(size_t size size_bytes);

		// Static Buffer
		VertexBuffer(void* data, size_t size_bytes);

		~VertexBuffer();

		void bind();
		void unbind();

	private:
		unsigned int m_vbo = 0;
	};
}}
