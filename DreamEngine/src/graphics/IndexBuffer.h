#pragma once
#include <GL/glew.h>

namespace dream { namespace graphics {

	class IndexBuffer
	{
	private:
		unsigned int m_IndexBufferID;
		unsigned int m_Count;
	public:
		IndexBuffer(unsigned short* data, int count);

		void bind();
		void unbind();

		inline unsigned int getCount() const { return m_Count; }
	};
}}
