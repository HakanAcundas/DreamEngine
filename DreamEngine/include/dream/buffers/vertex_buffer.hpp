#pragma once

#include <glad/glad.h>

namespace dream { namespace buffer {
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		// Dynamic Buffer
		VertexBuffer(size_t size_bytes);
		// Static Buffer
		VertexBuffer(void* data, size_t size_bytes);
		~VertexBuffer();

		void bind();
		void unbind();
		void upload_sub(const void* data, size_t size_bytes, size_t offset = 0);

	private:
		unsigned int m_vbo = 0;
	};
}}
