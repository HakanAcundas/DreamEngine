#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer2D.h"


namespace dream { namespace graphics {

	struct RendererData
	{
		std::vector<Texture2D*> TextureSlots;
		unsigned int TextureSlotIndex = 1;

		struct CameraData
		{
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
	};

	static RendererData s_Data;

	Renderer2D::Renderer2D()
	{
		Init();
	}

	void Renderer2D::Init()
	{
		m_VertexArray = new VertexArray();
		m_Buffer = new Buffer(RENDERER_SPRITE_SIZE * sizeof(RendererData));
		m_Buffer->AddBufferElement("shader_Position", ShaderDataType::Float, 3);
		m_Buffer->AddBufferElement("shader_TexCoord", ShaderDataType::Float, 2);
		m_Buffer->AddBufferElement("shader_TexIndex", ShaderDataType::Float, 1);
		m_Buffer->AddBufferElement("shader_Color", ShaderDataType::Float, 4);
		m_Buffer->CalculateStride();

		m_VertexArray->AddBuffer(m_Buffer);
		m_RenderableVertexBufferBase = new RenderableData[RENDERER_SPRITE_SIZE];

		int32_t* quadIndices = new int32_t[RENDERER_INDICES_SIZE];
		int32_t offset = 0;
		for (unsigned int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		m_IndexBuffer = new IndexBuffer(quadIndices, RENDERER_INDICES_SIZE);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		delete[] quadIndices;
		m_VertexArray->Unbind();
	}

	void Renderer2D::Begin()
	{
		m_Buffer->Bind();
		m_RenderableData = (RenderableData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		m_Buffer->Unbind();
	}

	void Renderer2D::StartBatch()
	{
		m_RenderableIndexCount = 0;
		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::AddRenderable(Renderable* renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Renderer2D::RemoveRenderable(Renderable* renderable)
	{
		m_Renderables.erase(std::remove(m_Renderables.begin(), m_Renderables.end(), renderable), m_Renderables.end());
	}

	// TO DO convert this function into DrawQuad (its is already converted but make a base 
	// function to apply different variations of DrawQuad. Example DrawRotatedQuad etc...
	void Renderer2D::Render()
	{
		for (Renderable* renderable : m_Renderables)
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
				// Search for texture ID
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
					// Else add the new texture ID to a slot
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

			m_RenderableIndexCount += 6;
		}
	}

	void Renderer2D::Flush()
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)m_RenderableVertexBufferPtr - (uint8_t*)m_RenderableVertexBufferBase);
		m_Buffer->SetData(m_RenderableVertexBufferBase, dataSize);

		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		m_VertexArray->Bind();
		m_IndexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, m_RenderableIndexCount, GL_UNSIGNED_INT, nullptr);
		m_IndexBuffer->Unbind();
		m_VertexArray->Unbind();
		// For testing erase later.
		//glBegin(GL_TRIANGLES);
		//glVertex2f(-0.5, -0.5);
		//glVertex2f(0.0, 0.5);
		//glVertex2f(0.5, -0.5);
		//glEnd();

		m_RenderableIndexCount = 0;
	}
}}