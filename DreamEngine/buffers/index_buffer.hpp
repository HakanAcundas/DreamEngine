#pragma once
#include <cstdint>
//#include <GL/glew.h>
#include <glad/glad.h>

namespace dream { namespace graphics {

	class IndexBuffer
	{
	private:
		unsigned int m_index_bufferID;
		unsigned int m_count;
	public:
		IndexBuffer(unsigned int *indices, int count);
		IndexBuffer(unsigned short *indices, int count);
		~IndexBuffer();

		void bind();
		void unbind();

		inline unsigned int get_count() const { return m_count; }
	};
}}
