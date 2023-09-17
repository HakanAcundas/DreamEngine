#pragma once
#include <GL/glew.h>

namespace dream { namespace graphics {

	class Buffer
	{
	private:
		unsigned int m_BufferID;
		unsigned int m_ComponentCount;
	public:
		Buffer(unsigned int size);
		Buffer(float* data, unsigned int size);
		~Buffer();

		void Bind() const;
		void Unbind() const;

		void SetData(const void* data,  unsigned int size);

		inline unsigned int const GetCount() { return m_ComponentCount; }
	};
}}
