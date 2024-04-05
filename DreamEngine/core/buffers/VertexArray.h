#pragma once
#include <vector>
#include <GL/glew.h>
#include "../buffers/Buffer.h"
#include "../buffers/IndexBuffer.h"

namespace dream { namespace graphics {

	class VertexArray
	{
	private:
		unsigned int m_ArrayID;
		unsigned int m_BufferIndex = 0;
		std::vector<std::shared_ptr<Buffer>> m_Buffers;
		IndexBuffer* m_IndexBuffer;
		
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;
		void AddBuffer(Buffer* buffer);
		void SetIndexBuffer(IndexBuffer* indexBuffer);

		const std::vector<std::shared_ptr<Buffer>> GetBuffers() { return m_Buffers; }
		const IndexBuffer* GetIndexBuffers() { return m_IndexBuffer; }
	};
}}
