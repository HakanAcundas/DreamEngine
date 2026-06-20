#pragma once

#include <glad/glad.h>

namespace dream { namespace buffer {
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void set_sprite_layout();

	private:
		unsigned int m_vao;
	};
}}
