#pragma once
#include <vector>
#include <GL/glew.h>
#include "indexBuffer.h"
#include "buffer.h"

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