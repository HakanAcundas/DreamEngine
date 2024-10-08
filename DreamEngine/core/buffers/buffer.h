#pragma once
#include<string>
#include<vector>
//#include <GL/glew.h>
#include <glad/glad.h>
#include <memory>

namespace dream { namespace graphics {

	enum class ShaderDataType
	{
		None = 0, Float, Int, Bool
	};

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		uint32_t count = 1;
		unsigned int size;
		size_t offset = 0;
		bool normalized;

		BufferElement() = default;

		BufferElement(const std::string &name, ShaderDataType type, unsigned int count, bool normalized = false)
			: name(name), type(type), count(count), size(shader_data_type_size(type)), offset(0), normalized(normalized)
		{
		}

		uint32_t shader_data_type_size(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:    return 4 * count;
			case ShaderDataType::Int:      return 4 * count;
			case ShaderDataType::Bool:     return 1 * count;
			}

			return 0;
		}

		static GLenum shader_data_type_to_opengl_base_type(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
			}

			return 0;
		}


	};

	class Buffer
	{
	private:
		unsigned int m_bufferID;
		unsigned int m_component_count;
		std::vector<std::shared_ptr<BufferElement>> m_buffer_elements;
		uint32_t m_stride = 0;

	public:
		Buffer(unsigned int size);
		Buffer(float *data, unsigned int size);
		~Buffer();

		void bind() const;
		void unbind() const;

		void add_buffer_element(std::string name, ShaderDataType type, uint8_t count = 1, bool normalized = false);
		void set_data(const void* data, uint32_t size);
		void calculate_stride();

		inline unsigned int const get_count() { return m_component_count; }
		std::vector<std::shared_ptr<BufferElement>> get_buffer_elements() { return m_buffer_elements; }
		unsigned int get_stride() const { return m_stride; }
	};
}}
