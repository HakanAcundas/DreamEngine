#pragma once
#include <vector>
//#include <GL/glew.h>
#include <glad/glad.h>
#include "../buffers/buffer.h"
#include "../buffers/index_buffer.h"

namespace dream { namespace graphics {

	class VertexArray
	{
	private:
		unsigned int m_arrayID;
		unsigned int m_buffer_index = 0;
		std::vector<std::shared_ptr<Buffer>> m_buffers;
		IndexBuffer* m_index_buffer;
		
	public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;
		void add_buffer(Buffer *buffer);
		void set_index_buffer(IndexBuffer *index_buffer);

		const std::vector<std::shared_ptr<Buffer>> GetBuffers() { return m_buffers; }
		const IndexBuffer* GetIndexBuffers() { return m_index_buffer; }
	};
}}
