#pragma once
#include <vector>
#include <GL/glew.h>
#include "IndexBuffer.h"
#include "Buffer.h"

namespace dream { namespace graphics {

	class VertexArray
	{
	private:
		unsigned int m_ArrayID;
		std::vector<Buffer*> m_Buffers;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer* buffer, int index);
		void bind() const;
		void unbind() const;
	};
}}
