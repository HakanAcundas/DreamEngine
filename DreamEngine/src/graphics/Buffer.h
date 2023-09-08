#pragma once
#include <GL/glew.h>

namespace dream { namespace graphics {

	class Buffer
	{
	private:
		unsigned int m_BufferID;
		unsigned int m_ComponentCount;
	public:
		Buffer(float* data, int count, unsigned int componentCount);
		void Bind() const;
		void Unbind() const;

		inline unsigned int const GetCount() { return m_ComponentCount; }
	};
}}
