#pragma once

#include <glad/glad.h>

namespace dream { namespace buffer {
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		~VertexBuffer();

		// Dynamic Buffer
		VertexBuffer(size_t size_bytes);
		// Static Buffer
		VertexBuffer(void* data, size_t size_bytes);

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;

		void bind();
		void unbind();
		void upload_sub(const void* data, size_t size_bytes, size_t offset = 0);

	private:
		unsigned int m_vbo = 0;
	};
}}
