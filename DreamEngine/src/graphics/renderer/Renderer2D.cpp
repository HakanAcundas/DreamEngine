#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer2D.h"


namespace dream { namespace graphics {

	struct RendererData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TO DO: RenderCaps

		Buffer* RendererBuffer;
		VertexArray* RendererVertexArray;
		Shader* RendererShader;
		Texture2D* WhiteTexture;

		uint32_t renderableIndexCount = 0;
		Renderable* RenderableVertexBufferBase = nullptr;
		Renderable* RenderableVertexBufferPtr = nullptr;

		std::vector<Texture2D*> TextureSlots;
		unsigned int TextureSlotIndex = 1; // 0 = white texture

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
		s_Data.RendererVertexArray = new VertexArray();
		s_Data.RendererBuffer = new Buffer(s_Data.MaxVertices * sizeof(RendererData));
		s_Data.RendererBuffer->AddBufferElement("shader_Position", ShaderDataType::Float, 3);
		s_Data.RendererBuffer->AddBufferElement("shader_TexCoord", ShaderDataType::Float, 2);
		s_Data.RendererBuffer->AddBufferElement("shader_TexIndex", ShaderDataType::Float, 1);
		s_Data.RendererBuffer->AddBufferElement("shader_Color", ShaderDataType::Float, 4);
		s_Data.RendererBuffer->CalculateStride();

		s_Data.RendererVertexArray->AddBuffer(s_Data.RendererBuffer);
		s_Data.RenderableVertexBufferBase = new Renderable[s_Data.MaxVertices];

		int32_t* quadIndices = new int32_t[s_Data.MaxIndices];

		int32_t offset = 0;
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

		m_IndexBuffer = new IndexBuffer(quadIndices, s_Data.MaxIndices);
		s_Data.RendererVertexArray->SetIndexBuffer(m_IndexBuffer);
		delete[] quadIndices;
	}

	void Renderer2D::Begin()
	{
		s_Data.RendererBuffer->Bind();
		m_RenderableData = (RenderableData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		s_Data.RendererBuffer->Unbind();
	}

	void Renderer2D::StartBatch()
	{
		s_Data.renderableIndexCount = 0;
		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::BeginScene(Camera& camera)
	{
		StartBatch();
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

			s_Data.renderableIndexCount += 6;
		}
	}

	void Renderer2D::Flush()
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.RenderableVertexBufferPtr - (uint8_t*)s_Data.RenderableVertexBufferBase);
		s_Data.RendererBuffer->SetData(s_Data.RenderableVertexBufferBase, dataSize);

		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		s_Data.RendererVertexArray->Bind();
		glDrawElements(GL_TRIANGLES, s_Data.renderableIndexCount, GL_UNSIGNED_INT, nullptr);

		// For testing erase later.
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.5, -0.5);
		glEnd();

		s_Data.renderableIndexCount = 0;
	}
}}