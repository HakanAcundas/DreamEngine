#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer2D.h"


namespace dream { namespace graphics {

	struct RendererData
	{
		static const unsigned int MaxQuads = 20000;
		static const unsigned int MaxVertices = MaxQuads * 4;
		static const unsigned int MaxIndices = MaxQuads * 6;
		static const unsigned int MaxTextureSlots = 32; // TODO: RenderCaps

		Buffer* RenderableBuffer;
		VertexArray* RenderableVertexArray;
		Shader* RendererShader;
		Texture2D* WhiteTexture;

		unsigned int renderableIndexCount = 0;

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
		m_VertexArray = new VertexArray();
		m_Buffer = new Buffer(s_Data.MaxVertices * sizeof(RendererData));
		m_Buffer->AddBufferElement("a_Position", ShaderDataType::Float, 3);
		m_Buffer->AddBufferElement("a_TexCoord", ShaderDataType::Float, 2);
		m_Buffer->AddBufferElement("a_TexIndex", ShaderDataType::Float, 1);
		m_Buffer->AddBufferElement("a_Color", ShaderDataType::Float, 4);
		m_Buffer->CalculateStride();

		m_VertexArray->AddBuffer(m_Buffer);
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

		m_IndexBuffer = new IndexBuffer(quadIndices, s_Data.MaxIndices);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		delete[] quadIndices;

		//s_Data.RendererShader = new Shader(
		//	"../DreamEngine/src/shaders/vertex.shader",
		//	"../DreamEngine/src/shaders/fragment.shader");
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
		s_Data.renderableIndexCount = 0;
		s_Data.RenderableBuffer = nullptr;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::BeginScene(Camera& camera)
	{
		// pr_matrix * vw_matrix * ml_matrix

		//s_Data.RendererShader->SetUniformMat4("pr_matrix", camera.GetProjectionMatrix());
		//s_Data.RendererShader->SetUniformMat4("ml_matrix", glm::translate(camera.GetViewMatrix(), camera.GetPosition()));
		//s_Data.RendererShader->SetUniform2f("light_pos", glm::vec2(4.0f, 1.5f));

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

			m_IndexCount += 6;
		}
	}

	void Renderer2D::Flush()
	{
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		m_VertexArray->Bind();
		m_IndexBuffer->Bind();
		
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		m_IndexBuffer->Unbind();
		m_VertexArray->Unbind();

		m_IndexCount = 0;
	}
}}