#pragma once

#include <glad/glad.h>

namespace dream { namespace buffer {
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(VertexArray&& other) noexcept;

		void set_sprite_layout();
		void bind();
		void unbind();

	private:
		unsigned int m_vao = 0;
	};
}}
