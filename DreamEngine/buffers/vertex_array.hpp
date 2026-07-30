#pragma once

#include <glad/glad.h>

namespace dream { namespace buffer {
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void set_sprite_layout();
		void bind();
		void unbind();

	private:
		unsigned int m_vao;
	};
}}
