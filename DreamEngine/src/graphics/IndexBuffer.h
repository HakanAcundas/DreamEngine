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

		void Bind();
		void Unbind();

		inline unsigned int GetCount() const { return m_Count; }
	};
}}
