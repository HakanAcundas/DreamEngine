#include "Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../buffers/Buffer.h"
#include "../buffers/IndexBuffer.h"
#include "VertexArray.h"
#include "../Shader.h"

namespace dream { namespace graphics {
	
	struct RendererData
	{
		static const unsigned int MaxQuads = 20000;
		static const unsigned int MaxVertices = MaxQuads * 4;
		static const unsigned int MaxIndices = MaxQuads * 6;
		static const unsigned int MaxTextureSlots = 32; // TODO: RenderCaps

		Buffer* RenderableBuffer;
		VertexArray* RenderableVertexArray;
		Shader* RenderableShader;
		Texture2D* WhiteTexture;

		unsigned int renderableIndexCount = 0;
		RenderableData* RenderableData = nullptr;

		std::vector<Texture2D*> TextureSlots;
		unsigned int TextureSlotIndex = 1; // 0 = white texture
	};

	static RendererData s_Data;

	void Renderer2D::Init()
	{
		s_Data.RenderableVertexArray = new VertexArray();

		s_Data.RenderableBuffer = new Buffer(s_Data.MaxVertices * sizeof(RendererData));
		s_Data.RenderableBuffer->AddBufferElement("a_Position", ShaderDataType::Float, 3);
		s_Data.RenderableBuffer->AddBufferElement("a_Color", ShaderDataType::Float, 4);
		s_Data.RenderableBuffer->AddBufferElement("a_TexCoord", ShaderDataType::Float, 2);
		s_Data.RenderableBuffer->AddBufferElement("a_TexIndex", ShaderDataType::Float, 1);
		s_Data.RenderableVertexArray->AddBuffer(s_Data.RenderableBuffer);

		s_Data.RenderableData = new RenderableData[s_Data.MaxVertices];

		unsigned int* quadIndices = new unsigned int[s_Data.MaxIndices];

		unsigned int offset = 0;
		for (unsigned int i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
	}

	void Renderer2D::Begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
		m_RenderableData = (RenderableData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	void Renderer2D::Submit(const Renderable* renderable)
	{
		const glm::vec3& position = renderable->GetPosition();
		const glm::vec2& size = renderable->GetSize();
		const glm::vec4& color = renderable->GetColor();
		const std::vector<glm::vec2>& uv = renderable->GetUV();
		const unsigned int tid = renderable->GetTID();

		unsigned int c = 0;
		float ts = 0.0f;
		if (tid > 0)
		{
			bool found = false;
			// Seach for renderable texture ID
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == tid)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				// If the texture slots are full
				if (m_TextureSlots.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}
				// Add the new texture ID to slot
				m_TextureSlots.push_back(tid);
				ts = (float)(m_TextureSlots.size());
			}
		}
		else
		{
#pragma region Color Optimization
			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			c = a << 24 | b << 16 | g << 8 | r;
#pragma endregion
		}

		m_RenderableData->Position = position;
		m_RenderableData->TexCoord = uv[0];
		m_RenderableData->TextureID = ts;
		m_RenderableData->Color = c;
		m_RenderableData++;

		m_RenderableData->Position = glm::vec3(position.x, position.y + size.y, position.z);
		m_RenderableData->TexCoord = uv[1];
		m_RenderableData->TextureID = ts;
		m_RenderableData->Color = c;
		m_RenderableData++;

		m_RenderableData->Position = glm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_RenderableData->TexCoord = uv[2];
		m_RenderableData->TextureID = ts;
		m_RenderableData->Color = c;
		m_RenderableData++;

		m_RenderableData->Position = glm::vec3(position.x + size.x, position.y, position.z);
		m_RenderableData->TexCoord = uv[3];
		m_RenderableData->TextureID = ts;
		m_RenderableData->Color = c;
		m_RenderableData++;

		m_IndexCount += 6;
	}

	void Renderer2D::Flush()
	{
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		glBindVertexArray(m_VertexArray);
		m_IndexBuffer->Bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		m_IndexBuffer->Unbind();
		glBindVertexArray(0);

		m_IndexCount = 0;
	}
}}