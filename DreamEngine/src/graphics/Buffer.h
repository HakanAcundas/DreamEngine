#pragma once
#include <GL/glew.h>

namespace dream { namespace graphics {

	class Buffer
	{
	private:
		unsigned int m_BufferID;
		unsigned int m_Count;
	public:
		Buffer(float* data, int count);
		void bind() const;
		void unbind() const;

		inline unsigned int const getCount() { return m_Count; }
	};
}}
