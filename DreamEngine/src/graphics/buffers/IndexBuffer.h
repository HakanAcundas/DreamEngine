#pragma once
#include <cstdint>
#include <GL/glew.h>

namespace dream { namespace graphics {

	class IndexBuffer
	{
	private:
		unsigned int m_IndexBufferID;
		unsigned int m_Count;
	public:
		IndexBuffer(int32_t* indices, int count);
		IndexBuffer(unsigned short* data, int count);
		~IndexBuffer();

		void Bind();
		void Unbind();

		inline unsigned int GetCount() const { return m_Count; }
	};
}}
